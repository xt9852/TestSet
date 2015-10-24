
#include "stdafx.h"
#include "WaveOut.h"
#pragma comment(lib,"Winmm")

/*
线程    状态    退出码

播音    正常    600
播音    强闭    601
播音    异常    602
*/


DWORD CWaveOut::s_dwInstance = 0;

//线程处理
DWORD WINAPI CWaveOut::AudioOutThreadProc(LPVOID lpParameter)
{
	CWaveOut *pWaveIn;
	pWaveIn = (CWaveOut*)lpParameter;

	MSG msg;
	//消息处理主循环
	while (GetMessage(&msg, 0, 0, 0))
	{
		switch (msg.message)
		{
		//打开播音设备
		case WOM_OPEN:
			break;

		//关闭播音设备
		case WOM_CLOSE:
			break;

		//播音完毕
		case WOM_DONE:
			//播音格式
			WAVEHDR* pwh = (WAVEHDR*)msg.lParam;
			//释放播音缓存
			waveOutUnprepareHeader((HWAVEOUT)msg.wParam, pwh, sizeof(WAVEHDR));
			//减少播音缓存数目
			pWaveIn->BufferSub();
			//删除Play调用时分配的内存
			delete[] pwh->lpData;
			//删除播音格式
			delete pwh;
			break;
		}
	}

	//返回
	return (DWORD)(msg.wParam);
}
//构造函数，用于初始化
CWaveOut::CWaveOut():
	 m_wChannel(1),
	 m_dwSample(WOSA_POOR),//WISA_MIN
	 m_wBit(16),
     m_mmr(0),
     m_hOut(NULL),
     m_hAudioOut(NULL),
     m_dwAudioOutId(0),
     m_bThreadStart(FALSE),
     m_bDevOpen(FALSE)
{
    s_dwInstance++;
}
//构析函数
CWaveOut::~CWaveOut()
{
	StopPlay();
}
//启动线程
BOOL CWaveOut::StartThread()
{
	//线程已经启动
	if (m_bThreadStart)
	{
		//返回
		return FALSE;
	}

	//创建线程
	m_hAudioOut = CreateThread(0, 0, AudioOutThreadProc, this, 0, &m_dwAudioOutId);
	//出错
	if (!m_hAudioOut)
	{
		//返回
		return FALSE;
	}

	//设置线程启动标记
	m_bThreadStart = TRUE;
	//返回
	return TRUE;
}
//停止线程
BOOL CWaveOut::StopThread()
{
	//线程已经停止
	if (!m_bThreadStart)
	{
		//返回
		return FALSE;
	}

	//线程句柄有效
	if (m_hAudioOut)
	{
		//循环变量
		int t=50;
		//线程结束状态
		DWORD ExitCode;
		//线程结束标记
		BOOL bEnd = FALSE;

		//发送WM_QUIT消息
		PostThreadMessage(m_dwAudioOutId, WM_QUIT, 0, 0);
		while(t)
		{
			//获取线程结束状态信息
			GetExitCodeThread(m_hAudioOut, &ExitCode);
			//线程结束
			if (ExitCode!= STILL_ACTIVE)
			{
				//设置线程尚未结束标记
				bEnd = TRUE;
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
		if(!bEnd)
		{
			//结束线程
			TerminateThread(m_hAudioOut, 601);
		}
		//设置音频设备句柄无效
		m_hAudioOut = 0;
	}

	//设置线程停止标记
	m_bThreadStart = FALSE;
	//返回
	return TRUE;
}
//打开播音设备
BOOL CWaveOut::OpenDev()
{
	//设备已经打开
	if (m_bDevOpen)
	{
		//返回
		return FALSE;
	}

	//设置播音输出格式
	WAVEFORMATEX wfx = {0};
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = m_wChannel;
	wfx.nSamplesPerSec = m_dwSample;
	wfx.nAvgBytesPerSec = m_wChannel * m_dwSample * m_wBit / 8;
	wfx.nBlockAlign = m_wBit * m_wChannel / 8;
	wfx.wBitsPerSample = m_wBit;
	wfx.cbSize = 0;

	//检查播音设备是否支持上述格式
	m_mmr = waveOutOpen (0,WAVE_MAPPER, &wfx, 0, 0, WAVE_FORMAT_QUERY);
	//出错
	if (m_mmr)
	{
		//返回
		return FALSE;
	}

	//打开播音设备
	m_mmr = waveOutOpen(&m_hOut, WAVE_MAPPER, &wfx, m_dwAudioOutId, s_dwInstance, CALLBACK_THREAD);
	//出错
	if(m_mmr)
	{
		//返回
		return FALSE;
	}

	//设置设备打开标记
	m_bDevOpen = TRUE;
	//初始化播音缓存数目
	m_iBufferNum = 0;
	//返回
	return TRUE;
}
//关闭播音设备
BOOL CWaveOut::CloseDev()
{
	//播音设备已经关闭
	if (!m_bDevOpen)
	{
		//返回
		return FALSE;
	}

	//播音设备句柄无效
	if (!m_hOut)
	{
		//返回
		return FALSE;
	}

	//关闭播音设备
	m_mmr = waveOutClose(m_hOut);
	//出错
	if (m_mmr)
	{
		//返回
		return FALSE;
	}

	//设置播音设备句柄无效
	m_hOut = 0;

	//设置播音设备打开标记
	m_bDevOpen = FALSE;
	//返回
	return TRUE;
}
//开始播音
BOOL CWaveOut::StartPlay()
{
	//函数返回标志
	BOOL bRet=FALSE;

	//启动线程失败
	if (!StartThread())           
	{
		goto Exit;
	}

	//打开播音设备失败
	if (!OpenDev())
	{
		goto Exit1;
	}

	//设置函数返回标志
	bRet = TRUE;
	goto Exit;
Exit1:
	//停止线程
	StopThread();
Exit:
	//返回
	return bRet;
}
//停止播音
BOOL CWaveOut::StopPlay()
{
	//关闭播音设备
	CloseDev();
	//关闭线程
	StopThread();
	//返回
	return TRUE;
}

MMRESULT CWaveOut::GetLastMMError()
{
	return m_mmr;
}

CString CWaveOut::GetLastErrorString()
{
	TCHAR buffer[256];
	memset(buffer,0,sizeof(buffer));
	waveOutGetErrorText(m_mmr,buffer,256);
	return CString(buffer);
}

void CWaveOut::SetChannel(WORD wChannel)
{
	m_wChannel = wChannel;//(m_wChannel == wChannel) ? 2:1;
}

void CWaveOut::SetSample(DWORD dwSample)
{
	m_dwSample = dwSample;
}

void CWaveOut::SetBit(WORD wBit)
{
	m_wBit = (wBit == 8) ? 8:16;
}

DWORD CWaveOut::GetInstance()
{
	return s_dwInstance;
}

WORD CWaveOut::GetBit()
{
	return m_wBit;
}

DWORD CWaveOut::GetSample()
{
	return m_dwSample;
}

WORD CWaveOut::GetChannel()
{
	return m_wChannel;
}
//播放
BOOL CWaveOut::Play(char *pszBuf, DWORD dwLen)
{
	try
	{
		//播音设备未打开
		if (!m_bDevOpen)
		{
			//返回
			return FALSE;
		}

		//延时太大
		if (GetBufferNum () > PLAY_DELAY)
		{
			//返回
			return TRUE;
		}

		//新建WAVEHDR结构，用于接收播音格式
		LPWAVEHDR pwh = new WAVEHDR;
		//出错
		if (!pwh)
		{
			//返回
			return FALSE;
		}

        memset(pwh, 0, sizeof(WAVEHDR));
		pwh->lpData = new char[SIZE_AUDIO_FRAME];
		memset(pwh->lpData, 0, SIZE_AUDIO_FRAME);

#ifdef G729_DECODE
        m_G729.Decode(pszBuf, dwLen, pwh->lpData, (int*)&(pwh->dwBufferLength));
#else
        memcpy(pwh->lpData, pszBuf, dwLen);
        pwh->dwBufferLength = dwLen;
#endif		

		//为回放数据作好准备
		m_mmr = waveOutPrepareHeader(m_hOut, pwh, sizeof(WAVEHDR));
		//出错
		if (m_mmr)
		{
			//返回
			return FALSE;
		}

		//将数据发往播音设备
		m_mmr = waveOutWrite(m_hOut, pwh, sizeof(WAVEHDR));
		//出错
		if (m_mmr)
		{
			//返回
			return FALSE;
		}

		//缓存数目增1
		m_iBufferNum++;
		//返回
	}
	catch(...)
	{
		TRACE("CWaveOut ERROR\n");
	}
	return TRUE;
}
//增加缓存数目
void CWaveOut::BufferAdd()
{
	//锁住内存
	m_csLock.Lock();
	//缓存数目增1
	m_iBufferNum++;
	//解除锁定
	m_csLock.Unlock();
}
//减少缓存数目
void CWaveOut::BufferSub()
{
	//锁住内存
	m_csLock.Lock();
	//缓存数目减1
	m_iBufferNum--;
	//解除锁定
	m_csLock.Unlock();
}
//获取缓存数目
int CWaveOut::GetBufferNum()
{
	//中间变量
	int iTemp;
	//锁住内存
	m_csLock.Lock();
	//获得缓存数目
	iTemp = m_iBufferNum;
	//解除锁定
	m_csLock.Unlock();
	//返回
	return iTemp;
}

BOOL CWaveOut::SetFormatByFile(CString file)
{
	#pragma pack(push, 1)
	struct FileHeader
	{
		char cFlagFiff[4];
		unsigned __int32 iFileLen;
		char cFlagWave[4];
		char cFlagFmt[4];
		char cResove[4];
		unsigned __int16 cFormat;
		unsigned __int16 cChannel;
		unsigned __int32 cSample;
		unsigned __int32 cBytePerSec;
		unsigned __int16 cByteprocess;
		unsigned __int16 cBit;
		char cFlagDat[4];
		unsigned __int32 iLenData;
	};
	#pragma pack(pop)

	CFile fi;
	if (!fi.Open(file, CFile::modeRead,NULL))
	{
		return FALSE;
	};
	struct FileHeader head;
	fi.Read((void *)&head,sizeof (head));
	fi.Close();

	this->SetChannel(head.cChannel);
	this->SetSample(head.cSample);
	this->SetBit(head.cBit);
	return TRUE;
}
