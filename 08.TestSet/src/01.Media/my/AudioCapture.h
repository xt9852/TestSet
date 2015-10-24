/*------------------------------------------------------------------------------*\
 [模块名称]
	CWaveIn

 [文件名称]
	WaveIn.h

 [相关文件]
	WaveIn.cpp

 [目的] 
     方便音频采集  
                                            
\*------------------------------------------------------------------------------*/

#ifndef _WAVEIN_H_
#define _WAVEIN_H_

typedef struct _tagRIFF_HEADER
{
    char  szRiffID[4];     // 'R','I','F','F'
    DWORD dwRiffSize;      // file size - 8
    char  szRiffFormat[4]; // 'W','A','V','E'
}RIFF_HEADER;

typedef struct _tagWAVE_FORMAT
{
    WORD  wFormatTag;
    WORD  wChannels;
    DWORD dwSamplesPerSec;
    DWORD dwAvgBytesPerSec;
    WORD  wBlockAlign;
    WORD  wBitsPerSample;
}WAVE_FORMAT;

typedef struct _tagFMT_BLOCK
{
    char  szFmtID[4];		// 'f','m','t',' '
    DWORD dwFmtSize;		// 数值为16或18，18则最后又附加信息
    WAVE_FORMAT wavFormat;
}FMT_BLOCK;

typedef struct _tagFACT_BLOCK// 可选
{
	char  szFactID[4];		// 'f','a','c','t'
	DWORD dwFactSize;
	DWORD dwDataSize;
}FACT_BLOCK; 

typedef struct _tagDATA_BLOCK
{
    char szDataID[4];		// 'd','a','t','a'
    DWORD dwDataSize;
}DATA_BLOCK;

#define WISA_POOR	8000
#define WISA_LOW	11025
#define WISA_NORMAL	22050
#define WISA_HIGH	44100

#define NUM_BUF 10
//#define SIZE_AUDIO_FRAME 960
//#define SIZE_AUDIO_PACKED 60
#define SIZE_AUDIO_FRAME 15840
#define SIZE_AUDIO_PACKED 990
#include <mmsystem.h>

//#define G729_ENCODE
#ifdef G729_ENCODE
#include "G729.h"
#endif

//#define PLAY
#ifdef PLAY
#include "WaveOut.h"
#endif

class CWaveIn
{
public:
	//线程处理
	static DWORD WINAPI AudioInThreadProc(LPVOID lpParameter);	

	//获取数据
	virtual void ProcAudio(char *pszData, DWORD dwLen) = 0;

public:	
	//启动录音
	BOOL StartRec();
	//停止录音
	BOOL StopRec();

	//开始录音
	BOOL OpenRecord();
	//结束录音
	BOOL CloseRecord();

	//获取实例
	inline DWORD GetInstance();
	//获取采样位数
	inline WORD GetBit();
	//获取采样速率
	inline DWORD GetSample();
	//获取频道数
	inline WORD GetChannel();

	//设置采样位数
	inline void SetBit(WORD wBit);
	//设置采样速率
	inline void SetSample(DWORD dwSample);
	//设置采样频道数
	inline void SetChannel(WORD wChannel);

	//获取错误信息
	inline MMRESULT GetLastMMError();
	CString GetLastErrorString();

    //保存成wav文件
    void SaveFile(LPCSTR strFileName, bool bCreate, char *pszData, DWORD dwLen);

	//构造函数
	CWaveIn();
	//析构函数
	virtual ~CWaveIn();	

#ifdef G729_ENCODE
	//G729压缩
	CG729 m_G729;
#endif

#ifdef PLAY
	//播放声音
	CWaveOut m_WaveOut;
#endif

protected:
	//打开设备
	BOOL OpenDev();
	//关闭设备
	BOOL CloseDev();

	//停止线程
	BOOL StopThread();
	//启动线程
	BOOL StartThread();

	//准备缓存
	BOOL PerPareBuffer();
	//释放缓存
	BOOL FreeBuffer();

protected:
	//用户实例数据
	static DWORD s_dwInstance;	

protected:
	//频道数
	WORD m_wChannel;
	//采样速率
	DWORD m_dwSample;
	//采样位数
	WORD m_wBit;

protected:
	//音频输入设备句柄
	HWAVEIN m_hIn;
	//函数调用返回信息
	MMRESULT m_mmr;
	//回调函数指针
	DWORD m_dwAudioInId;
	//线程句柄
	HANDLE m_hAudioIn;
	//WAVEHDR结构缓存指针
	WAVEHDR* m_pHdr;

	//线程启动标志
	BOOL m_bThreadStart;
	//设备打开标记
	BOOL m_bDevOpen;
	//内存分配标记
	BOOL m_bAllocBuffer;
	//录音开始标记
	BOOL m_bRecord;
};

#endif