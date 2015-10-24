/*------------------------------------------------------------------------------*\
 [模块名称]
	CWaveOut

 [文件名称]
	CWaveOut.h

 [相关文件]
	CWaveOut.cpp

 [目的] 
     方便音频播放
     	  
 [描述]		
	封装 waveout api
	只使用了 pcm 方式
                                               
\*------------------------------------------------------------------------------*/

#ifndef _WAVEOUT_H_
#define _WAVEOUT_H_

#define WOSA_POOR	8000
#define WOSA_LOW	11025
#define WOSA_NORMAL	22050
#define WOSA_HIGH	44100

#define PLAY_DELAY 10
#define SIZE_AUDIO_FRAME 15840

#include <mmsystem.h>
#include <afxmt.h>

//#define G729_DECODE
#ifdef G729_DECODE
#include "G729.h"
#endif

class CWaveOut  
{
public:
	//线程处理
	static DWORD WINAPI AudioOutThreadProc(LPVOID lpParameter);

public:
	//根据文件设置格式
	BOOL SetFormatByFile(CString file);
	//播音
	BOOL Play(char *pszBuf, DWORD dwLen);

	//开始播音
	BOOL StartPlay();
	//停止播音
	BOOL StopPlay();	

	//获取缓存数目
	inline int GetBufferNum();
	//减少缓存数目
	inline void BufferSub();
	//增加缓存数目
	inline void BufferAdd();

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
	//设置频道数
	inline void SetChannel(WORD wChannel);

	//获取错误信息
	inline MMRESULT GetLastMMError();
	CString GetLastErrorString();

	//构造函数
	CWaveOut();
	//析构函数
	virtual ~CWaveOut();

#ifdef G729_DECODE
	//G729压缩
	CG729 m_G729;
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
	//函数调用返回信息
	MMRESULT m_mmr;
	//播音设备句柄
	HWAVEOUT m_hOut;
	//线程句柄
	HANDLE m_hAudioOut;
	//回调函数指针
	DWORD m_dwAudioOutId;

	//缓存数目
	int m_iBufferNum;
	//重要部分(critical section)
	CCriticalSection m_csLock;

	//线程启动标志
	BOOL m_bThreadStart;
	//播音设备打开标志
	BOOL m_bDevOpen;

	//线程处理
	friend DWORD WINAPI AudioOutThreadProc(LPVOID lpParameter);
};

#endif
