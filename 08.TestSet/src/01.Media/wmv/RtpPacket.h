#pragma once


/*
	RtpPacket 类用于操作RtpPacket ，为修改和获取rtpPacket 的相关成员提供
	函数。本类根据Rtp的大小分配内存，并填充相应的项生成一个 Rtppacket 。

*/

class RtpPacket
{
public:
    enum
    {
        RTP_VERSION_OFFSET	    =	0,
        RTP_PAYLOADTYPE_OFFSET	=	1,
        RTP_SEQ_NUM_OFFSET		=	2,
        RTP_TIME_STAMP_OFFSET	=	4,
        RTP_SSRC_OFFSET			=	8,

        RTP_HEAD_LEN			=	12,
        RTP_PAYLOAD_OFFSET      =   12,

        RTP_VERSION_CONST	    =	0x80,	
        RTP_PAYLOADTYPE_CONST   =	0xe0,
        RTP_SSRC_CONST			=	3202321672
    };

    BYTE * buffer;
    WORD  bufferSize;

    BYTE * payload;
    WORD  payloadSize;

    WORD	trackID;				//在Asf文件中 没有提供
    BOOL	isKeyFrame;				//在Asf 文件中须 深一层的解析

public:
    RtpPacket( WORD );				//参数为rtppacket 的大小
    ~RtpPacket(void);
    int SetPayLoad(const BYTE * pData,DWORD size );

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
	BYTE	GetVersion();
	int		SetVersion( BYTE );
	BYTE	GetPayLoadType();
	int		SetPayLoadType( BYTE );
	WORD	GetSeqNum();
	int		SetSeqNum( WORD );
	DWORD	GetTimeStamp();
	int		SetTimeStamp( DWORD );
	DWORD   GetSSRC() ;
	int     SetSSRC( DWORD );

#ifdef  DEBUG
	int		PacketOut() ;
	static int Test();
#endif
	BOOL SetFirstFlag(void);
};
