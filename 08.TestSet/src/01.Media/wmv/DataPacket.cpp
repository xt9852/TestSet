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

#include "StdAfx.h"
#include "DataPacket.h"
#include "Buffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define  SHOW_DATA_PACKET 1

//////////////////////////////////////////////////////////////////////

/* Packet types */
#define RDT_ASMACTIION_PACKET               0xff00
#define RDT_BANDWIDTHREPORT_PACKET          0xff01
#define RDT_ACK_PACKET                      0xff02
#define RDT_RTTREQUEST_PACKET               0xff03
#define RDT_RTTRESPONSE_PACKET              0xff04
#define RDT_CONGESTION_PACKET               0xff05
#define RDT_STREAMEND_PACKET                0xff06
#define RDT_REPORT_PACKET                   0xff07
#define RDT_LATENCYREPORT_PACKET            0xff08
#define RDT_TRANSPORTINFO_PACKET            0xff09
#define RDT_TRANSPORTINFORESPONSE_PACKET    0xff0a
#define RDT_BWPROBING_PACKET                0xff0b



#define RTP_TIME_OFFSET		3

#define RDT_FLAG_OFFSET     3
#define RDT_TIME_OFFSET		4
#define RDT_PAD_OFFSET		8
#define RDT_HEAD_LEN        10






//
// CPNPacket 默认的构造函数和析构函数
//
CDataPacket::CDataPacket() : CPacket( PROTOCOL_DATA )
{

}

CDataPacket::~CDataPacket()
{

}


//生成一个空数据
CDataPacket*		CDataPacket::MakeEmptyPacket()
{
	CDataPacket * pPacket = new CDataPacket();
	
	BYTE pEmptyData[8];
	BYTE pData[10];
	pData[0] = 0x42;
	pData[1] = 0x00;
	pData[2] = 0x00;
	pData[3] = 0x41;
	pData[4] = 0x00;
	pData[5] = 0x00;
	pData[6] = 0x00;
	pData[7] = 0x00;
	pData[8] = 0x00;
	pData[9] = 0x00;

	pEmptyData[0] = '$';
	pEmptyData[1] = 0;
	*(unsigned short * )(pEmptyData + 2) = htons(10);

	pPacket->Write( pEmptyData, 4 );
	pPacket->Write( pData, 10);

	return pPacket;
}

//////////////////////////////////////////////////////////////////////////

//
//	针对RTP类型进行相应的处理
//
CDataPacket *	CDataPacket::HandleRTPDataPacket(BYTE * pBuf)
{
	CDataPacket * pPacket = new CDataPacket();

	pPacket->m_nDataType	= RTP_PACKET;

	//OVER TCP HEADER
	WORD nDataLen		= ntohs( *(WORD *)(pBuf + 2) );
	pPacket->m_nDataLen	= nDataLen;
	pPacket->m_nChanID	= * (pBuf+1);

	//写数据
	pPacket->Write(pBuf, nDataLen + 4);

	pPacket->m_pData	= pPacket->m_pBuffer + 4;

	//RTP DATA HEADER
	pPacket->m_nSeqNum		= ntohs( *(WORD *)( pPacket->m_pData + 1) );
	pPacket->m_nTimeStamp	= ntohl( *(UINT32 *)( pPacket->m_pData + 3) );

	//是否为关键帧
	pPacket->m_bKeyFrame	= !(0x01 & pPacket->m_pData[3]);

	//根据时间搓算出该数据包属于哪一秒
	pPacket->m_nSecond		= pPacket->m_nTimeStamp / 1000;

	//初始化PayLoad 类型
	if( pPacket->m_nChanID == 0)
		pPacket->m_nPayloadType = AUDIO_TYPE;

	if( pPacket->m_nChanID == 1)
		pPacket->m_nPayloadType = VIDEO_TYPE;	

	return pPacket;
}

//
//	针对RDT类型进行相应的处理
//
CDataPacket *	CDataPacket::HandleRDTDataPacket(BYTE * pBuf)
{
	CDataPacket * pPacket = new CDataPacket();

	pPacket->m_nDataType	= RDT_PACKET;

	WORD nDataLen		= ntohs( *(WORD *)(pBuf + 2) );
	pPacket->m_nDataLen	= nDataLen;

	//写数据
	pPacket->Write(pBuf, nDataLen + 4);
	
	pPacket->m_pData		= pPacket->m_pBuffer + 4;

	pPacket->m_nChanID		= ((* pPacket->m_pData) & 0x3e) >> 1;
	pPacket->m_nSeqNum		= ntohs( *(WORD *)( pPacket->m_pData + 1) );
	
	//是否为关键帧
	if( 0x01 & pPacket->m_pData[3] )
		pPacket->m_bKeyFrame	=  0;
	else
		pPacket->m_bKeyFrame	=  1;
	
	pPacket->m_nTimeStamp	= ntohl( *(UINT32 *)( pPacket->m_pData + 4) );

	//根据时间搓算出该数据包属于哪一秒
	pPacket->m_nSecond		= pPacket->m_nTimeStamp / 1000;

	//初始化PayLoad 类型
	if( pPacket->m_nChanID == 0)
		pPacket->m_nPayloadType = AUDIO_TYPE;

	if( pPacket->m_nChanID == 1)
		pPacket->m_nPayloadType = VIDEO_TYPE;	

	return pPacket;
}

//
//	
//
CDataPacket *	CDataPacket::HandleAsmActionPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_ASMACTIION_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleBandwidthReportPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_BANDWIDTHREPORT_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleAckPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_ACK_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleRTTRequestPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_RTTREQUEST_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleRTTResponsePacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_RTTRESPONSE_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleCongestionPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_CONGESTION_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleStreamEndPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_STREAMEND_PACKET");
	
	CDataPacket * pPacket = new CDataPacket();

	pPacket->m_nDataType	= END_PACKET;

	WORD nDataLen		= ntohs( *(WORD *)(pBuf + 2) );
	pPacket->m_nDataLen	= nDataLen;

	pPacket->m_nChanID	= ((* (pBuf + 4)) & 0x7c) >> 2;

	//初始化PayLoad 类型
	if( pPacket->m_nChanID == 0)
		pPacket->m_nPayloadType = AUDIO_TYPE;
	
	if( pPacket->m_nChanID == 1)
		pPacket->m_nPayloadType = VIDEO_TYPE;	


	return pPacket;
}

//
//
//
CDataPacket *	CDataPacket::HandleReportPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_REPORT_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleLatencyReportPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_LATENCYREPORT_PACKET");

	CDataPacket * pPacket	= new CDataPacket();

	pPacket->m_nDataType	= RDT_PACKET;

	//OVER TCP HEADER
	WORD nDataLen		=  *(WORD *)(pBuf + 2);
	nDataLen			=  ntohs(nDataLen);
	pPacket->m_nDataLen	=  nDataLen - 9;

	//Save OVER TCP HEADER
	pPacket->Write(pBuf, 4);

	//Skip  Latency Report Packet Header
	pBuf = pBuf + 4 + 9;

	//写数据
	pPacket->Write(pBuf, nDataLen - 9);
	
	//Modify OVER TCP HEADER
	*(WORD *)(pPacket->m_pBuffer + 2) = htons( nDataLen - 9);

	pPacket->m_pData		= pPacket->m_pBuffer + 4;

	pPacket->m_nChanID	=  ( *pPacket->m_pData & 0x3e) >> 1;
	pPacket->m_nSeqNum		= ntohs( *(WORD *)( pPacket->m_pData + 1) );

	//是否为关键帧
	if( 0x01 & pPacket->m_pData[3] )
		pPacket->m_bKeyFrame	=  0;
	else
		pPacket->m_bKeyFrame	=  1;

	pPacket->m_nTimeStamp	= ntohl( *(UINT32 *)( pPacket->m_pData + 4) );

	//根据时间搓算出该数据包属于哪一秒
	pPacket->m_nSecond	= pPacket->m_nTimeStamp / 1000;

	//初始化PayLoad 类型
	if( pPacket->m_nChanID == 0)
		pPacket->m_nPayloadType = AUDIO_TYPE;

	if( pPacket->m_nChanID == 1)
		pPacket->m_nPayloadType = VIDEO_TYPE;	

	return pPacket;	

}

//
//
//
CDataPacket *	CDataPacket::HandleTransportInfoPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_TRANSPORTINFO_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleTransportInfoResponsePacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_TRANSPORTINFORESPONSE_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleBwpRobingPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"RDT_BWPROBING_PACKET");

	return NULL;
}

//
//
//
CDataPacket *	CDataPacket::HandleUnKnownPacket(BYTE * pBuf)
{
	//theApp.Message(MSG_DATAPACKET,"UNKOWN_PACKET");

	return NULL;
}


//////////////////////////////////////////////////////////////////////

/*  OVER TCP  Header
 *	|	$	   | StreamID |	Data Length		|   RTP  HEADER | RTP DATA |
 *	|  byte    | byte     |   word          |   RDT  HEADER | RDT DATA |
 *
 *  RTP		  Header
 *	| PayLoad Type (BYTE) | Seq Num         |  TimeStamp               | 
 *  | byte                | word  16Bit     |  32 Bit                  |
 * 
 *
 *  RDT       Header      
 *  | FLAG + STREAM ID |  PACKET TYPE (WORD) (SeqNum) |  flag (BYTE)    |timestamp  32 Bit |
 *  |
 */


//
//	从Buffer中构建一个DATA包
//
CDataPacket* CDataPacket::CreatePacket(BYTE * pData, DATA_TYPE nDataType)
{
	ASSERT( *pData == '$' );

	//根据提供的类型解析数据	
	switch( nDataType )
	{
	case  RTP_PACKET:
		return HandleRTPDataPacket(pData);
	
	case  RDT_PACKET:		
		{
			//处理RDT类型的数据包，根据不同的RDT类型进行相应的处理
			UINT16  packetType		=  ntohs( *(UINT16 *)( pData + 5) );

			if (packetType < 0xff00)
			{
				return HandleRDTDataPacket(pData);
			}
			else
			{
				switch (packetType)
				{
				case RDT_ASMACTIION_PACKET:
					return HandleAsmActionPacket(pData);
					
				case RDT_BANDWIDTHREPORT_PACKET:
					return HandleBandwidthReportPacket(pData);
					
				case RDT_ACK_PACKET:
					return HandleAckPacket(pData);
					
				case RDT_RTTREQUEST_PACKET:
					return HandleRTTRequestPacket(pData);
					
				case RDT_RTTRESPONSE_PACKET:
					return HandleRTTResponsePacket(pData);
					
				case RDT_CONGESTION_PACKET:
					return HandleCongestionPacket(pData);
					
				case RDT_STREAMEND_PACKET:
					return HandleStreamEndPacket(pData);
					
				case RDT_REPORT_PACKET:
					return HandleReportPacket(pData);
					
				case RDT_LATENCYREPORT_PACKET:
					return HandleLatencyReportPacket(pData);
					
				case RDT_TRANSPORTINFO_PACKET:
					return HandleTransportInfoPacket(pData);
					
				case RDT_TRANSPORTINFORESPONSE_PACKET:
					return HandleTransportInfoResponsePacket(pData);
					
				case RDT_BWPROBING_PACKET:
					return HandleBwpRobingPacket(pData);

				default:
					return HandleUnKnownPacket(pData);
				}
			}
		}
	}

	return NULL;
}
//////////////////////////////////////////////////////////////////////

/*  OVER TCP  Header
 *	|	$	   | StreamID |	Data Length		|   RTP  HEADER | RTP DATA |
 *	|  byte    | byte     |   word          |   RDT  HEADER | RDT DATA |
 *
 *  RTP		  Header
 *	| PayLoad Type (BYTE) | Seq Num         |  TimeStamp               | 
 *  | byte                | word  16Bit     |  32 Bit                  |
 * 
 *
 *  RDT       Header      
 *  | FLAG + STREAM ID |  PACKET TYPE (WORD) (SeqNum) |  flag (BYTE)    |timestamp  32 Bit |
 *  |
 */
#define CHAN_ID_CONST 0x02
BOOL	CDataPacket::SetFirstFlag()
{
	*(m_pData+RtpPacket::RTP_PAYLOAD_OFFSET)|=0x80;
	return TRUE;
}
CDataPacket *	CDataPacket::CreatePacket(RtpPacket *  packet ){
	if ( packet == NULL ) return NULL;

	CDataPacket * pPacket = new CDataPacket();

	pPacket->m_nDataType = RTP_PACKET;

	
	pPacket->m_nDataLen	= packet->bufferSize;				//数据长度为RDT 头长度和媒体数据长度

	

	BYTE headBuf[4];
	memset( headBuf, 0, 4 );										//写入OVER TCP 头
	pPacket->Write( headBuf, 4);


	pPacket->Write(packet->buffer, packet->bufferSize );						//写入媒体数据
	
	pPacket->m_pData		= pPacket->m_pBuffer + 4;				//数据指针指向RTP 头
	
	
	pPacket->m_nChanID		= 0;							//设置Stream Id 
	
	
	//是否为关键帧
	pPacket->m_bKeyFrame		= packet->isKeyFrame;
	
	pPacket->m_nTimeStamp = packet->GetTimeStamp();
	

	//根据时间搓算出该数据包属于哪一秒
	pPacket->m_nSecond		= pPacket->m_nTimeStamp / 1000;

	//初始化PayLoad 类型
	if( pPacket->m_nChanID == 1)
		pPacket->m_nPayloadType = AUDIO_TYPE;

	if( pPacket->m_nChanID == 2)
		pPacket->m_nPayloadType = VIDEO_TYPE;	
															//以网络字节顺序设置buffer中的相应字段
	pPacket->SetDefault();
	pPacket->SetTimeStamp( pPacket->m_nTimeStamp );
	pPacket->SetChanID(CHAN_ID_CONST );
	pPacket->SetDataLen ( pPacket->m_nDataLen );
	//pPacket->SetFlags ( frame->flags );

	return pPacket;
	
}
CDataPacket *	CDataPacket::CreatePacket( rmff_frame_t * frame) {	//从rm frame 中创建一个Data packet

	
	if ( frame == NULL ) return NULL;

	CDataPacket * pPacket = new CDataPacket();

	pPacket->m_nDataType = RDT_PACKET;

	
	pPacket->m_nDataLen	= RDT_HEAD_LEN + frame->size;				//数据长度为RDT 头长度和媒体数据长度

	

	BYTE headBuf[14];
	memset( headBuf, 0, 14 );										//写入OVER TCP 头,写入RDT 头
	pPacket->Write( headBuf, 14);


	pPacket->Write(frame->data, frame->size );						//写入媒体数据
	
	pPacket->m_pData		= pPacket->m_pBuffer + 4;				//数据指针指向RDT 头
	
	
	pPacket->m_nChanID		= frame->id;							//设置Stream Id 
	
	
	//是否为关键帧
	pPacket->m_bKeyFrame		= frame->flags & 0x01;
	
	pPacket->m_nTimeStamp = frame->timecode;
	

	//根据时间搓算出该数据包属于哪一秒
	pPacket->m_nSecond		= pPacket->m_nTimeStamp / 1000;

	//初始化PayLoad 类型
	if( pPacket->m_nChanID == 0)
		pPacket->m_nPayloadType = AUDIO_TYPE;

	if( pPacket->m_nChanID == 1)
		pPacket->m_nPayloadType = VIDEO_TYPE;	
															//以网络字节顺序设置buffer中的相应字段
	pPacket->SetDefault();
	//pPacket->SetTimeStamp( pPacket->m_nTimeStamp );
	pPacket->SetChanID( pPacket->m_nChanID );
	pPacket->SetDataLen ( pPacket->m_nDataLen );
	//pPacket->SetFlags ( frame->flags );

	return pPacket;
}

//CDataPacket *	CDataPacket::CreatePacket(  RtpPacket* frame ) {	//从rm frame 中创建一个Data packet
//
//	
//	if ( frame == NULL ) return NULL;
//
//	CDataPacket * pPacket = new CDataPacket();
//
//	pPacket->m_nDataType = RTP_PACKET;
//
//	
//	pPacket->m_nDataLen	= RTP_HEAD_LEN + frame->size;				//数据长度为RDT 头长度和媒体数据长度
//
//	
//
//	BYTE headBuf[4];
//	memset( headBuf, 0, 4 );										//写入OVER TCP 头
//	pPacket->Write( headBuf, 4);
//
//
//	pPacket->Write(frame->data, frame->size );						//写入媒体数据
//	
//	pPacket->m_pData		= pPacket->m_pBuffer + 4;				//数据指针指向RDT 头
//	
//	
//	pPacket->m_nChanID		= frame->id;							//设置Stream Id 
//	
//	
//	//是否为关键帧
//	pPacket->m_bKeyFrame		= frame->flags & 0x01;
//	
//	pPacket->m_nTimeStamp = frame->timecode;
//	
//
//	//根据时间搓算出该数据包属于哪一秒
//	pPacket->m_nSecond		= pPacket->m_nTimeStamp / 1000;
//
//	//初始化PayLoad 类型
//	if( pPacket->m_nChanID == 0)
//		pPacket->m_nPayloadType = AUDIO_TYPE;
//
//	if( pPacket->m_nChanID == 1)
//		pPacket->m_nPayloadType = VIDEO_TYPE;	
//															//以网络字节顺序设置buffer中的相应字段
//	pPacket->SetDefault();
//	pPacket->SetTimeStamp( pPacket->m_nTimeStamp );
//	pPacket->SetChanID( pPacket->m_nChanID );
//	pPacket->SetDataLen ( pPacket->m_nDataLen );
//	pPacket->SetFlags ( frame->flags );
//
//	return pPacket;
//}

void CDataPacket::SetDefault() {							//设置缺省字段 ，在ＯＶＥＲ　ＴＣＰ　头中
	m_pBuffer[0] = '$';
	if( m_nDataType == RDT_PACKET ) {

		*( WORD* )( m_pData + RDT_PAD_OFFSET ) = 0;
	}
	//*(UINT16 *)(buf + 12) = 0;
}

void CDataPacket::SetTimeStamp( UINT32 time) {				//设置buffer中的Timestamp 字段，包括RTP头或RDT头
	if( m_nDataType == RTP_PACKET ) {
		*(UINT32*) ( m_pData + RTP_TIME_OFFSET ) = htonl( time );
	
	}
	if( m_nDataType == RDT_PACKET ) {
		*(UINT32*)( m_pData + RDT_TIME_OFFSET ) = htonl( time );
	}
}

void CDataPacket::SetChanID( BYTE chanID) {					//设置StreamId字段，包括OVER TCP 头和RDT 头				
	*(m_pBuffer+1) = chanID;
	if(  m_nDataType == RDT_PACKET ) {						//stream ID 的格式
		// *( m_pData )&= 0xc1 ;								// | ++-- ---+ |
		//chanID <<=1 ;
		//chanID &= 0x3e ;
		//*( m_pData ) |= chanID;

		char m	= chanID;
		m = m << 1;
		m |= 0x40;
		*( m_pData ) = m;
	}
}

void CDataPacket::SetDataLen ( WORD len ) {					//设置DataLen 字段，在OVER TCP 头中
	*(WORD*)( m_pBuffer + 2) = htons( len );
}

void CDataPacket::SetFlags( BYTE flags) {					//设置Flag字段 ，在RDT头中 
	ASSERT (m_nDataType == RDT_PACKET ) ;
	BYTE  m;
	if( flags )
		m = 0;
	else
		m = 1;

	m |= 0xc0;
	*(m_pData + RDT_FLAG_OFFSET) = m;
}








//
//	复制一个相同内容的DataPacket
//
CDataPacket* CDataPacket::Clone()
{
	CDataPacket* pPacket		= new CDataPacket();

	//初始化头部
	pPacket->m_nSeqNum			= m_nSeqNum;
	pPacket->m_nTimeStamp		= m_nTimeStamp;
	pPacket->m_nChanID			= m_nChanID;
	pPacket->m_nPayloadType		= m_nPayloadType;
	pPacket->m_nSecond			= m_nSecond;
	pPacket->m_nDataType		= m_nDataType;	
	pPacket->m_bKeyFrame		= m_bKeyFrame;

	//读数据内容
	pPacket->Write( &m_pBuffer, (DWORD)m_nBuffer );

	return pPacket;		
}

//
//	将数据放到一个Buffer中
//
void CDataPacket::ToBuffer(CBuffer* pBuffer) const
{
	pBuffer->Add( m_pBuffer, m_nLength );
}

CDataPacket * CDataPacket::ReadFromPacket( CPacket * pIn )
{
	//判断头部的长度是否够了
	if( pIn->GetRemaining() < sizeof(DATAPACKET_HEADER) ) return NULL;


    //PEEK头部信息
	DATAPACKET_HEADER  *pHeader = ( DATAPACKET_HEADER * ) (pIn->m_pBuffer + pIn->m_nPosition);

	//检查总的长度是否够了
	if( pIn->GetRemaining() < pHeader->m_nTotalLength ) return NULL;


	//创建一个新的DataPacket
	CDataPacket *pDataPacket = new CDataPacket();

	//读取头部信息
	DATAPACKET_HEADER header;
	pIn->Read( (BYTE*)&header, sizeof(DATAPACKET_HEADER));

	pDataPacket->m_nSeqNum		=	header.m_nSeqNum;
	pDataPacket->m_nTimeStamp	=	header.m_nTimeStamp;
	pDataPacket->m_nSecond		=	header.m_nSecond;
	pDataPacket->m_nChanID		=	header.m_nChanID;
	pDataPacket->m_nPayloadType	=	(PAYLOAD_TYPE)header.m_nPayloadType;
	pDataPacket->m_nDataType	=	(DATA_TYPE)header.m_nDataType;
	pDataPacket->m_nDataLen		=	header.m_nDataLen;
	pDataPacket->m_bKeyFrame	=	header.m_bKeyFrame;


	//读内容信息
	pDataPacket->Write( pIn->m_pBuffer + pIn->m_nPosition, header.m_nTotalLength - sizeof(DATAPACKET_HEADER));

	//读取数据后，移动指针位置
	pIn->m_nPosition += header.m_nTotalLength - sizeof(DATAPACKET_HEADER);

	//设置DataPacket的内容指针
	pDataPacket->m_pData		=	pDataPacket->m_pBuffer + 4;

	return pDataPacket;

}

//
//	将包结构的内容放入Buffer中
//
void	CDataPacket::MakePacket(CPacket * pOut )
{
	//计算长度
	WORD	nLen = (WORD)( m_nLength + sizeof(DATAPACKET_HEADER));

	//写头部
	DATAPACKET_HEADER header;

	header.m_nTotalLength	=	nLen;		//头部数据长度和媒体数据长度
	header.m_nSeqNum		=   m_nSeqNum;
	header.m_nTimeStamp		=	m_nTimeStamp;
	header.m_nSecond		=	m_nSecond;
	header.m_nChanID		=	m_nChanID;
	header.m_nPayloadType	=	m_nPayloadType;
	header.m_nDataType		=	m_nDataType;
	header.m_nDataLen		=	m_nDataLen;
	header.m_bKeyFrame		=   m_bKeyFrame;

	pOut->Write( (BYTE *)&header, sizeof(DATAPACKET_HEADER) );

	//写数据
	pOut->Write( m_pBuffer, m_nLength );

}

//
//	获取类型：音频包 还是 视频包 
//
PAYLOAD_TYPE CDataPacket::GetPayLoadType() const
{
	return m_nPayloadType;
}

//
//	类型 RTP Packet OR RDT Packet
//
DATA_TYPE CDataPacket::GetDataType() const
{
	return m_nDataType;
}

//
//	属于第几秒
//
DWORD CDataPacket::GetSecond() const
{
	return m_nSecond;
}


//
//	时间搓
//
DWORD CDataPacket::GetTimeStamp() const
{
	return m_nTimeStamp;
}

//
//	序列号
//
WORD CDataPacket::GetSeqNum() const
{
	return m_nSeqNum;
}

//
//	是否为关键帧
//
BYTE CDataPacket::IsKeyFrame() const
{
	return m_bKeyFrame;
}


//
//	取得数据的指针(出去头部)
//
BYTE* CDataPacket::GetData() const
{
	return m_pData;
}

//
//	取得除去头部后数据的长度
//
WORD CDataPacket::GetDataLen() const
{
	return m_nDataLen;
}

//
//	设置序号
//
void CDataPacket::SetSeqNum(WORD nSeqNum)
{
	m_nSeqNum = nSeqNum;
	
	//修改RTP包中的序列号（待写）
	if(m_nDataType == RTP_PACKET) 
	{
		*(WORD*)(m_pData +RtpPacket::RTP_SEQ_NUM_OFFSET) = htons( m_nSeqNum);
	}
	if(m_nDataType == RDT_PACKET)
	{
		*(WORD * ) (m_pData + 1) = htons( m_nSeqNum );
	}

}

//
//返回Channel ID
//
WORD CDataPacket::GetChanID()
{
	return m_nChanID;
}

//////////////////////////////////////////////////////////////////////

//
//	CPNPacket 打印包的内容，做调试用
//
void CDataPacket::SmartDump() const
{
	CString strPlayLoad;
	
	switch( m_nPayloadType )
	{
	case VIDEO_TYPE:
		strPlayLoad = "Video";
		break;
	case AUDIO_TYPE:
		strPlayLoad = "Audio";
		break;
	default:
		strPlayLoad = "Unkown";
	}

#if SHOW_DATA_PACKET	
	/*theApp.Message(MSG_DATAPACKET,"Type:%s, Seq = %lu, timestamp = %lu, KeyFrame = %d, Length=%d",
								strPlayLoad,
								this->m_nSeqNum,
								this->m_nTimeStamp,
								this->m_bKeyFrame,
								this->m_nDataLen);*/
		
			CString str;
				
					for( int i = 0; i<32; i++)
					{
						
						str.AppendFormat("%02x ",this->m_pBuffer[i]);
						if( i%16 == 15 ) str.AppendFormat( "\n");
					}
					theApp.Message(MSG_DEFAULT,str);
#endif

}

