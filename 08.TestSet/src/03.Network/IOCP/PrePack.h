
#pragma once
#define WIN32_LEAN_AND_MEAN	// 去除winsock.h包含
#include <Windows.h>

namespace XT_IOCP
{

	typedef struct tagClientContext *PCLIENT;
	class PackQueue;
	class BuffPool;

#pragma pack(push, 1)
	
	static const int packFlag = 0x12345678; // 包标记

	/**
	 *\struct tagPACKHEAD
	 *\brief  数据包头信息
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	typedef struct tagPACKHEAD
	{
		long          flag;		// 包标记(0x12345678)
		unsigned long dataLen;	// 包数据长度
		unsigned long protoId;	// 协议ID
		unsigned char data[1];	// 包内容（和其后的 dataLen - 1 个字都是消息内容）

		/**
		 *\fn         clear()
		 *\brief      清空数据包全部数据。
	     */
		void clear(unsigned long id = 0)
		{
			flag = packFlag;
			dataLen = 0;
            protoId = id;
		}

		/**
		 *\fn         getData()
		 *\brief      返回数据。
		 *\return     数据指针
	     */
		unsigned char * getData() { return data; }

		/**
		 *\fn         setData(int begin, void *buff, int len)
		 *\brief      拷贝数据。
		 *\param[in]  begin 位置。
		 *\param[in]  buff  数据指针。
		 *\param[in]  len   数据长度。
	     */
		void setData(int begin, void *buff, int len)
		{
			memcpy(&data[begin], buff, len);
			dataLen = begin + len;
		}
		
		/**
		 *\fn         getPackLen()
		 *\brief      得到整个数据包长度(包含数据长)。
		 *\return	  整个数据包长度
	     */
		long getPackLen()
		{
			return (dataLen + sizeof(PACK) - sizeof(char));
		}

		/**
		 *\fn         getCheckNum()
		 *\brief      得到校验码。
		 *\return	  校验码
	     */
		short getCheckNum()
		{
			return getCheckNum(data, dataLen);
		}

		/**
		 *\fn         getCheckNum(unsigned char *data, unsigned long len)
		 *\brief      得到校验码。
		 *\param[in]  data 数据指针。
		 *\param[in]  len  数据长度。
		 *\return	  校验码
	     */
		static short getCheckNum(unsigned char *data, unsigned long len)
		{
			short checkSum = 0;

			for(unsigned long i = 0; i < len; i += 10)
			{
				checkSum += data[i];
			}

			return checkSum;
		}

	}PACK, *PPACK;

#pragma pack(pop)

	/**
	 *\enum   CMDTYPE
	 *\brief  数据包头信息
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	enum
	{
		CMD_TYPE_MMS,	// MMS协议
		CMD_TYPE_HTTP,	// HTTP协议
		CMD_TYPE_MYSELF	// 自定义协议
	};

	/**
	 *\class  PrePack
	 *\brief  该类主要是对数据包进行预处理（拼接和拆分），向输入队列输入一个完整的正确的包
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	class PrePack
	{
	public:
		/**
		 *\fn         PrePack()
		 *\brief      缺省构造函数。
	     */
		PrePack();

		/**
		 *\fn         ~PrePack()
		 *\brief      析构函数。
	     */
		~PrePack();

	private:
		CRITICAL_SECTION	csUsed_;	// 临界区
		PackQueue			*inQueue_;	// 输入队列
		BuffPool			*buffPool_; // 内存池
		int				cmdType_;	// 协议 类型

		long				oneBuffSize_;// 一个缓冲区的长度
		long				dataLen_;	// 数据长
		long				buffSize_;	// 当前缓冲区的长度
		char				*buff_;		// 缓冲区

	public:
		/**
		 *\fn         Init(int cmdType, PackQueue *inQueue, BuffPool *buffPool)
		 *\brief      初使化预处理包。
		 *\param[in]  cmdType  命令类型。
		 *\param[in]  inQueue  数据包输入队列。
		 *\param[in]  buffPool 内存池。
		 *\return     是否成功
		 */
		bool Init(int cmdType, PackQueue *inQueue, BuffPool *buffPool);
		
		/**
		 *\fn         Add(PCLIENT client, long len, void *buffer)
		 *\brief      添加一个数据包。
		 *\param[in]  client  客户端对象。
		 *\param[in]  len     数据长。
		 *\param[in]  buffer  数据包。
		 *\return     是否成功
		 */
		bool Add(PCLIENT client, long len, void *buffer);
	};

}

/*
typedef struct tagSingleMessage{// 报文内消息体
    BYTE        bVersion;       // 消息版本
    WORD        wType;          // 消息类型
    DWORD       dwId;           // 消息编号
    DWORD       dwSenderId;     // 发送者编号
    DWORD       dwReceiverId;   // 接收者编号
    time_t      tSendTime;      // 发送时间
    time_t      tDropTime;      // 留存时间
    char        cSendType;      // 发送类型：0-一对一；1-一对多；2-其它
    char        cStatus;        // 消息转发状态：
                                // 0-直接发送；
                                // 1-通过服务器转发；
                                // 2-离线消息转发；
                                // 3-其它。
    WORD        wMessageLen;    // 消息内容长度
    WORD        wMsgNum;        // 包的序号
    char        acMessageText[1];// 消息内容：原消息报文内容（最长1400字节）
}SINGLEMESSAGE, *PSINGLEMESSAGE;

typedef struct tagRawMessagePacketHeader{// 报文头部
    DWORD       dwHeader;       // 报文引导符（0x12345678）
    DWORD       dwSenderId;     // 发送者编号
    WORD        wSenderType;    // 发送者类型
    WORD        wServerAId;     // 服务器ID(S-C)
    WORD        wReceiverType;  // 接收者编号
    WORD        wServerBId;     // 接受者所在的服务器ID(C-S)
    WORD        wNumOfMsg;      // 报文中消息数
    WORD        wPacketLen;     // 报文内容长度
    short       sCheckSum;      // 报文头校验码
}RAWMESSAGEPACKETHEADER, *PRAWMESSAGEPACKETHEADER;
*/