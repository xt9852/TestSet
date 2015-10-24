/*********************************************************************
  * 文件名	  :	DataPacket.h
  *	功能描述  :	媒体数据包的基类
  *
  *
  *	作者	  : 程斌
  * 当前版本  : Version 1.0
  * 修改记录  : 
  *
  *
  *
  *
*****************************************************************/

#if !defined	_DATAPACKET_H__
#define			_DATAPACKET_H__

#pragma once

#include "Packet.h"
#include "librmff.h"
#include "Rtppacket.h"
typedef struct _DATAPACKET_HEADER {

	WORD			m_nTotalLength;
	WORD			m_nSeqNum;
	DWORD			m_nTimeStamp;
	DWORD			m_nSecond;
	BYTE			m_nChanID;
	BYTE			m_nPayloadType;
	BYTE			m_nDataType;
	WORD			m_nDataLen;
	BYTE			m_bKeyFrame;
} DATAPACKET_HEADER;

typedef enum {
	VIDEO_TYPE = 1,
	AUDIO_TYPE = 2
} PAYLOAD_TYPE;

typedef enum{
	RTP_PACKET	= 11,
	RDT_PACKET	= 12,
	END_PACKET	= 13
} DATA_TYPE;

class CDataPacket : public CPacket
{
// Construction
public:
	CDataPacket();
	virtual ~CDataPacket();
	
// Attributes
public:

	//头部信息
	WORD			m_nSeqNum;
	UINT32			m_nTimeStamp;
	DWORD			m_nSecond;
	BYTE			m_nChanID;

	PAYLOAD_TYPE	m_nPayloadType;
	DATA_TYPE		m_nDataType;
	WORD			m_nDataLen;
	BYTE			m_bKeyFrame;

	//实际的数据内容
	BYTE*			m_pData;	//不含 OVER TCP的头部

// Operations
public:
	//////////////////////////////
	//从Buffer中构建一个DATA包
	static CDataPacket*		CreatePacket(BYTE * pData, DATA_TYPE nDataType);

	static CDataPacket *	CreatePacket(rmff_frame_t * frame) ;//从rm frame中创建一个DATA包
	static CDataPacket *	CreatePacket(RtpPacket *  packet );
	BOOL	SetFirstFlag();

private:

	virtual void SetTimeStamp ( UINT32 );						//设置buffer中的Timestamp 字段，包括RTP头或RDT头
	virtual void SetChanID	  ( BYTE );							//设置StreamId字段，包括OVER TCP 头和RDT 头
	virtual void SetDataLen	  (WORD );							//设置DataLen 字段，在OVER TCP 头中
	virtual void SetFlags	  ( BYTE );							//设置Flag字段 ，在RDT头中 
	virtual void SetDefault   ();								//设置缺省字段 ，在ＯＶＥＲ　ＴＣＰ　头中
	///////////////////////////////
public:

	//获取类型：音频包 还是 视频包 
	virtual PAYLOAD_TYPE	GetPayLoadType() const;

	//类型 RTP Packet OR RDT Packet
	virtual DATA_TYPE		GetDataType() const;

	//属于第几秒
	virtual DWORD			GetSecond() const;

	//时间搓
	virtual DWORD			GetTimeStamp() const;

	//序列号
	virtual WORD			GetSeqNum() const;

	//获取数据的指针(除去OVERTCP的头部)
	virtual BYTE*			GetData() const;

	//获取数据的长度(除去OVERTCP的头部)
	virtual WORD			GetDataLen() const;
	
	//设置序号
	virtual	void			SetSeqNum(WORD nSeqNum);

	//返回Channel ID
	virtual WORD			GetChanID();

	//	是否为关键帧
	virtual	BYTE			IsKeyFrame() const;

	//打印数据包的关键内容信息
	virtual void			SmartDump() const;

	//生成一个空数据
	static CDataPacket*		MakeEmptyPacket();

	//复制一个相同内容的DataPacket
	virtual	CDataPacket*	Clone();
	
	//将整个数据打包到一个Buffer中
	virtual void	ToBuffer(CBuffer* pBuffer) const;

	//从Buffer中恢复该DataPacket的结构
	static  CDataPacket * ReadFromPacket( CPacket * pIn);
	
	//将包结构的内容放入Buffer中
	virtual void	MakePacket(CPacket * pOut);

	//析构自身
	virtual inline void Delete()
	{
		delete this;
	}

private:
	//针对RDT类型进行相应的处理

	static  CDataPacket *	HandleRTPDataPacket(BYTE * pBuf);

	static  CDataPacket *	HandleRDTDataPacket(BYTE * pBuf);
	static  CDataPacket *	HandleAsmActionPacket(BYTE * pBuf);
	static  CDataPacket *	HandleBandwidthReportPacket(BYTE * pBuf);
	static  CDataPacket *	HandleAckPacket(BYTE * pBuf);
	static  CDataPacket *	HandleRTTRequestPacket(BYTE * pBuf);
	static  CDataPacket *	HandleRTTResponsePacket(BYTE * pBuf);
	static  CDataPacket *	HandleCongestionPacket(BYTE * pBuf);
	static  CDataPacket *	HandleStreamEndPacket(BYTE * pBuf);
	static  CDataPacket *	HandleReportPacket(BYTE * pBuf);
	static  CDataPacket *	HandleLatencyReportPacket(BYTE * pBuf);
	static  CDataPacket *	HandleTransportInfoPacket(BYTE * pBuf);
	static  CDataPacket *	HandleTransportInfoResponsePacket(BYTE * pBuf);
	static  CDataPacket *	HandleBwpRobingPacket(BYTE * pBuf);
	static  CDataPacket *	HandleUnKnownPacket(BYTE * pBuf);

};


#endif 

