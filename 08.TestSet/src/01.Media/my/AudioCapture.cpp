#include "stdafx.h"
#include "WaveIn.h"
#include <math.h>
#pragma comment(lib,"Winmm")

/*
线程    状态    退出码

录音    正常    500
录音    强闭    501
录音    异常    502
*/


//用户实例数据
DWORD CWaveIn::s_dwInstance = 0;

//线程处理
DWORD WINAPI CWaveIn::AudioInThreadProc(LPVOID lpParameter)
{
    CWaveIn *pWaveIn;
    pWaveIn = (CWaveIn *)lpParameter;

#ifdef G729_ENCODE
    CG729* pG729 = &(pWaveIn->m_G729);
    
    if (NULL == pG729)
        AfxMessageBox(_T("CWaveIn 参数错误!"), MB_OK);
#endif  

    //缓存
    char szBuf[16000] = {""};
    DWORD dwLen = 0;

    //消息处理主循环
    MSG msg;

    try
    {
        while (GetMessage(&msg, 0, 0, 0))
        {
            switch (msg.message )
            {
                //打开录音设备
            case MM_WIM_OPEN:
                break;

                //关闭录音设备
            case MM_WIM_CLOSE:
                break;

                //录音设备返回数据
            case MM_WIM_DATA:
                //录音格式
                WAVEHDR* pWH = (WAVEHDR*)msg.lParam;

                //释放缓存
                waveInUnprepareHeader((HWAVEIN)msg.wParam, pWH, sizeof(WAVEHDR));

                //非法数据
                if (pWH->dwBytesRecorded != SIZE_AUDIO_FRAME)
                    break;
#ifdef G729_ENCODE
                //G729编码
                pG729->Encode(pWH->lpData, pWH->dwBytesRecorded, szBuf, (int*)&dwLen);
#else
                dwLen = pWH->dwBytesRecorded;
                memcpy(szBuf, pWH->lpData, dwLen);
#endif

#ifdef PLAY
                //直接播放
                pWaveIn->m_WaveOut.Play(szBuf, dwLen);
#else
                //处理数据
                pWaveIn->ProcAudio(szBuf, dwLen);
#endif

                //为音频设备增加一个缓存,准备继续录音
                waveInPrepareHeader((HWAVEIN)msg.wParam, pWH, sizeof(WAVEHDR));
                waveInAddBuffer((HWAVEIN)msg.wParam, pWH, sizeof(WAVEHDR));
                break;
            }
        }// end while
    }
    catch(...)
    {
        TRACE(_T("CWaveIn.ProcAudio Error %d\n"), ::GetLastError());
        return 502;
    }   

    //返回
    return (DWORD)msg.wParam;
}
//构造函数
CWaveIn::CWaveIn()
    :m_wChannel(1),
    m_dwSample (WISA_POOR),//WISA_MIN
    m_wBit(16),
    m_hIn(NULL),
    m_mmr(0),
    m_dwAudioInId(0),
    m_hAudioIn(NULL),
    m_pHdr(NULL),
    m_bThreadStart(FALSE),
    m_bDevOpen(FALSE),
    m_bAllocBuffer(FALSE),
    m_bRecord(FALSE)
{
    s_dwInstance++;
}
//构析函数
CWaveIn::~CWaveIn()
{
    StopRec();
}

//关闭录音设备
BOOL CWaveIn::CloseDev()
{
    //设备已经关闭
    if (!m_bDevOpen)
    {
        //返回
        return FALSE;
    }

    //设备句柄无效
    if (!m_hIn)
    {
        //返回
        return FALSE;
    }

    //关闭录音设备
    m_mmr = waveInClose(m_hIn);
    //出错
    if (m_mmr)
    {
        //设置设备句柄无效
        m_hIn = 0;
        //设置设备启动标记
        m_bDevOpen = FALSE;
        //返回
        return FALSE;
    }

    //设置设备句柄无效
    m_hIn = 0;
    //设置设备启动标记
    m_bDevOpen = FALSE;

    //返回
    return TRUE;
}
//打开录音设备
BOOL CWaveIn::OpenDev()
{
    //已经打开录音设备
    if (m_bDevOpen)
    {
        //返回
        return FALSE;
    }

    //设置录音设备输出格式
    WAVEFORMATEX wfx = {0};
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = m_wChannel;
    wfx.nSamplesPerSec = m_dwSample;
    wfx.nAvgBytesPerSec = m_wChannel * m_dwSample * m_wBit / 8;
    wfx.nBlockAlign = m_wBit * m_wChannel / 8;
    wfx.wBitsPerSample = m_wBit;
    wfx.cbSize = 0;

    //检查录音设备是否支持设定的输出格式
    m_mmr = waveInOpen(0, WAVE_MAPPER, &wfx, 0, 0, WAVE_FORMAT_QUERY);
    //出错
    if (m_mmr)
    {
        //返回
        return FALSE;
    }

    //打开录音设备
    m_mmr = waveInOpen(&m_hIn, WAVE_MAPPER, &wfx, m_dwAudioInId, s_dwInstance, CALLBACK_THREAD);
    //出错
    if (m_mmr)
    {
        //返回
        return FALSE;
    }

    //设置设备打开标记
    m_bDevOpen = TRUE;

    //返回
    return TRUE;
}
//启动线程
BOOL CWaveIn::StartThread()
{
    //线程已经启动
    if (m_bThreadStart)
    {
        //返回
        return FALSE;
    }

    //创建线程
    m_hAudioIn = CreateThread(0, 0, AudioInThreadProc, this, 0, &m_dwAudioInId);
    //出错
    if (!m_hAudioIn)
    {
        //返回
        return FALSE;
    }

    //设置线程启动标记
    m_bThreadStart = TRUE;

    //返回
    return TRUE;
}
//关闭线程
BOOL CWaveIn::StopThread()
{
    //线程已经停止
    if (!m_bThreadStart)
    {
        //返回
        return FALSE;
    }

    //线程句柄有效
    if (m_hAudioIn)
    {
        //循环变量
        int t = 50;
        //线程结束状态信息
        DWORD ExitCode;
        //线程结束标记
        BOOL bEnd=FALSE;

        //发送WM_QUIT消息
        PostThreadMessage(m_dwAudioInId,WM_QUIT,0,0);

        //主循环
        while (t)
        {
            //获取线程结束状态信息
            GetExitCodeThread(m_hAudioIn,&ExitCode);
            //尚未结束
            if (ExitCode!= STILL_ACTIVE)
            {
                //设置线程结束
                bEnd=TRUE;
                break;
            }
            //休眠10毫秒
            else
            {
                Sleep(10);
            }
            //修改循环变量
            t--;
        }

        //线程尚未结束
        if (!bEnd)
        {
            //终止线程
            TerminateThread(m_hAudioIn,501);
        }

        //录音设备句柄无效
        m_hAudioIn=0;
    }

    //设置线程结束标记
    m_bThreadStart = FALSE;
    //返回
    return TRUE;
}

//启动录音
BOOL CWaveIn::StartRec()
{
#ifdef PLAY
    //开始播放
    m_WaveOut.StartPlay();
#endif

    //返回值
    BOOL bRet = FALSE;	

    //启动线程失败
    if (!StartThread())           
    {
        goto Exit;
    }

    //打开录音设备失败
    if (!OpenDev())
    {
        goto Exit1;
    }

    //准备缓存失败
    if (!PerPareBuffer())
    {
        goto Exit2;
    }
/*
    //开始录音
    if (!OpenRecord())
    {
        goto Exit3;
    }
*/
    //设置返回值
    bRet = TRUE;
    goto Exit;
/*
    Exit3:
    //释放缓存
    FreeBuffer();
*/
Exit2:
    //关闭录音设备
    CloseDev();

Exit1:
    //停止线程
    StopThread();

Exit:
    //返回
    return bRet;
}

//终止录音
BOOL CWaveIn::StopRec()
{
    //停止录音
    CloseRecord();
    //休眠1500毫秒
    Sleep(800);
    //释放缓存
    FreeBuffer();
    //关闭录音设备
    if (CloseDev())
    {
        //停止线程
        StopThread();
    }
    //返回
    return TRUE;
}
//分配内存
BOOL CWaveIn::PerPareBuffer()
{
    //已经分配内存
    if (m_bAllocBuffer)
    {
        //返回
        return FALSE;
    }

    //重置录音设备
    m_mmr = waveInReset(m_hIn);
    //出错
    if (m_mmr)
    {
        //返回
        return FALSE;
    }

    //循环变量
    UINT i;
    //新建WAVEHDR结构
    m_pHdr = new WAVEHDR[NUM_BUF];

    for (i = 0; i < NUM_BUF; i++)
    {
        //初始化
        ZeroMemory(&m_pHdr[i], sizeof(WAVEHDR));
        //波形缓存
        m_pHdr[i].lpData = new char[SIZE_AUDIO_FRAME];
        //缓存大小
        m_pHdr[i].dwBufferLength = SIZE_AUDIO_FRAME;
        m_pHdr[i].dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
        m_pHdr[i].dwLoops = 1;

        //准备缓存
        m_mmr = waveInPrepareHeader(m_hIn, &m_pHdr[i], sizeof(WAVEHDR));
        //出错
        if (m_mmr)
        {
            //返回
            return FALSE;
        }

        //添加缓存到录音设备
        m_mmr = waveInAddBuffer(m_hIn, &m_pHdr[i], sizeof(WAVEHDR));
        //出错
        if (m_mmr)
        {
            //返回
            return FALSE;
        }
    }

    //设置内存分配标记
    m_bAllocBuffer = TRUE;

    //返回
    return TRUE;
}

//释放缓存
BOOL CWaveIn::FreeBuffer()
{
    //内存分配标记为假
    if (!m_bAllocBuffer)
    {
        //返回
        return FALSE;
    }

    //循环标记
    UINT i;
    //内存已经释放
    if (!m_pHdr)
    {
        //返回
        return FALSE;
    }

    for (i = 0; i < NUM_BUF; i++)
    {
        //注销录音设备
        m_mmr = waveInUnprepareHeader(m_hIn, &m_pHdr[i], sizeof(WAVEHDR));

        //出错
/*		if (m_mmr)
        {
        //休眠100毫秒
        Sleep(100);
        //跳过
        continue;
        }
*/		
        //释放数据内存单元
        if (m_pHdr[i].lpData)
        {
            delete[] m_pHdr[i].lpData;
            m_pHdr[i].lpData = NULL;
        }
    }

    //释放WAVEHDR结构
    delete []m_pHdr;
    m_pHdr = NULL;

    //设置内存分配标记
    m_bAllocBuffer = FALSE;

    //返回
    return TRUE;
}
//开始录音
BOOL CWaveIn::OpenRecord()
{
    //已经开始录音
    if (m_bRecord)
    {
        //返回
        return FALSE;
    }

    //录音设备句柄无效
    if(!m_hIn)
    {
        //返回
        return FALSE;
    }

    //开始录音
    m_mmr = waveInStart(m_hIn);
    //出错
    if (m_mmr)
    {
        //返回
        return FALSE;
    }

    //设置录音开始标记
    m_bRecord = TRUE;

    //返回
    return TRUE;
}

//停止录音
BOOL CWaveIn::CloseRecord()
{
    //已经停止录音
    if (!m_bRecord)
    {
        //返回
        return FALSE;
    }

    //录音设备句柄无效
    if(!m_hIn)
    {
        //返回
        return FALSE;
    }

    //重置录音设备，停止录音
    m_mmr = waveInReset(m_hIn);

    //出错
    if (m_mmr)
    {
        //返回
        return FALSE;
    }

    //设置录音停止标记
    m_bRecord = FALSE;

    //返回
    return TRUE;
}
/*
void CWaveIn::GetData(char *pBuffer,int iLen)
{
static int i = 0;
static SYSTEMTIME time,time1;
static long l = 0;
if (i == 0)
{
::GetLocalTime (&time);
}
::GetLocalTime (&time1);

int j = time1.wSecond - time.wSecond;
if (abs(j) >= 1 )
{
memcpy(&time,&time1,sizeof(time));
TRACE("Len / second %d \n",l);
l = 0;
}
l = l + iLen;
i++;
}
*/

MMRESULT CWaveIn::GetLastMMError()
{
    return m_mmr;
}

CString CWaveIn::GetLastErrorString()
{
    TCHAR buffer[256];
    memset(buffer,0,sizeof(buffer));
    waveInGetErrorText(m_mmr,buffer,256);
    return CString(buffer);
}

void CWaveIn::SetChannel(WORD wChannel)
{
    m_wChannel = (m_wChannel == wChannel) ? 2:1;
}

void CWaveIn::SetSample(DWORD dwSample)
{
    m_dwSample = dwSample;
}

void CWaveIn::SetBit(WORD wBit)
{
    m_wBit = (wBit == 8) ? 8:16;
}

DWORD CWaveIn::GetInstance()
{
    return s_dwInstance;
}

WORD CWaveIn::GetBit()
{
    return m_wBit;
}

DWORD CWaveIn::GetSample()
{
    return m_dwSample;
}

WORD CWaveIn::GetChannel()
{
    return m_wChannel;
}


void CWaveIn::SaveFile(LPCSTR strFileName, bool bCreate, char *pszData, DWORD dwLen)
{
    if (bCreate)
    {
        CFile file;
        if (file.Open(strFileName, CFile::modeCreate | CFile::modeReadWrite))
        {
            RIFF_HEADER riff_header = {0};
            FMT_BLOCK   fmt_block   = {0};
            DATA_BLOCK  data_block  = {0};

            memcpy(riff_header.szRiffID, "RIFF", 4);
            memcpy(riff_header.szRiffFormat, "WAVE", 4);
            riff_header.dwRiffSize = sizeof(RIFF_HEADER) + sizeof(FMT_BLOCK) + sizeof(DATA_BLOCK) + dwLen - 8;

            memcpy(fmt_block.szFmtID, "fmt ", 4);
            fmt_block.dwFmtSize = sizeof(WAVE_FORMAT);
            fmt_block.wavFormat.wFormatTag = WAVE_FORMAT_PCM;
            fmt_block.wavFormat.wChannels = m_wChannel;
            fmt_block.wavFormat.dwSamplesPerSec = m_dwSample;
            fmt_block.wavFormat.dwAvgBytesPerSec = m_wChannel * m_dwSample * m_wBit / 8;
            fmt_block.wavFormat.wBlockAlign = m_wBit * m_wChannel / 8;
            fmt_block.wavFormat.wBitsPerSample = m_wBit;

            memcpy(data_block.szDataID, "data", 4);
            data_block.dwDataSize = dwLen;

            file.Write(&riff_header, sizeof(RIFF_HEADER));
            file.Write(&fmt_block, sizeof(FMT_BLOCK));
            file.Write(&data_block, sizeof(DATA_BLOCK));
            file.Write(pszData, dwLen);
            file.Close();
        }
    }
    else
    {
        CFile file;
        if (file.Open(strFileName, CFile::modeReadWrite))
        {
            RIFF_HEADER riff_header = {0};
            FMT_BLOCK   fmt_block   = {0};
            DATA_BLOCK  data_block  = {0};
			FACT_BLOCK  fat_block   = {0};
			WORD		wData		= 0;
			BOOL		bHaveFact	= FALSE;

            file.Read(&riff_header, sizeof(RIFF_HEADER));
            file.Read(&fmt_block, sizeof(FMT_BLOCK));

			if (18 == fmt_block.dwFmtSize)	// 18 多2个字节的扩展数据
				file.Read(&wData, 2);

			file.Read(&fat_block, sizeof(FACT_BLOCK));

			if (0 != strncmp(fat_block.szFactID, "fact", 4))	// FACT_BLOCK是可选的
				file.Seek(-12, CFile::current);
			else
				bHaveFact = TRUE;

			file.Read(&data_block, sizeof(DATA_BLOCK));

            riff_header.dwRiffSize += dwLen;
            fat_block.dwDataSize += dwLen;
			data_block.dwDataSize += dwLen;

            file.SeekToBegin();
            file.Write(&riff_header, sizeof(RIFF_HEADER));
            file.Write(&fmt_block, sizeof(FMT_BLOCK));
			if (18 == fmt_block.dwFmtSize) file.Seek(2, CFile::current);
			if (bHaveFact) file.Write(&fmt_block, sizeof(FMT_BLOCK));
            file.Write(&data_block, sizeof(DATA_BLOCK));
            file.SeekToEnd();
            file.Write(pszData, dwLen);
            file.Close();
        }
    }
}