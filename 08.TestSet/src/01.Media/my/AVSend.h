
#pragma once
#include "AV/PackHead.h"
#include "Common/KeyList.h"
#include <vector>
//#include "Network/DefineClientContext.h"


namespace XT_IOCP
{

	typedef struct tagClientContext*  PCLIENT;
	typedef struct _tagPackEx*        PPACKEX;
	class PackQueue;
	class BuffPool;


	typedef struct _tagSendInfo
	{
		PCLIENT	pClient; // 发送对象(UDP)
		int     ip;		 // IP地址
		short   port;	 // 端口地址
	}SenderInfo,*PSenderInfo;

	typedef std::vector<SenderInfo> SENDINFOERS;

	/**
	将音视频数据发送给指定的用户,视频包拆分成1024个字节
	音频和视频的ID是在一起顺序的
	*/
	class CAVSend
	{
	public:
		CAVSend();
		~CAVSend();

	protected:
		int         mtuSize_;		// 最小传输单元
		int         maxSize_;		// 能发送的最大的数据,其实是由缓冲区大小而定    
		int         channceId_;		// 这一路音视频的ID
		int         lastTime_;		// 上一个包的时间,不能有相同的
		int         packId_;		// 包ID
		int         audioProto_;	// 音频协议
		int         videoProto_;	// 视频协议
		int         addrSize_;		// IPV4地址结构大小
		int         addrSize6_;		// IPV6地址结构大小

		PackQueue  *outputQueue_;	// 发送队列
		BuffPool   *buffPool_;		// 缓冲区
		CKeyList    avData_;		// 音频频包队列

		SENDINFOERS audioSenders_;	// 向这些对象发送音频数据
		SENDINFOERS videoSenders_;	// 向这些对象发送视频数据

	protected:
		void DelPack(int id);

	public:
		void Init(int channceId, int mtuSize, int buffSize,
			int audioProto, int videoProto,
			PackQueue *outputQueue, BuffPool *buffPool);

		void AddAudioSender(PCLIENT client, int ip, unsigned short port);
		void AddVideoSender(PCLIENT client, int ip, unsigned short port);
		void DelAudioSender(PCLIENT client, int ip, unsigned short port);
		void DelVideoSender(PCLIENT client, int ip, unsigned short port);

		void DelAllSend();

		void SendAudio(char *data, int len);
		void SendVideo(char *data, int len);
		void ResendAV(PCLIENT client, int id, int ip, unsigned short port);

		int getAudioSenderCount() { return audioSenders_.size(); }
		int getVideoSenderCount() { return videoSenders_.size(); }
	};
}