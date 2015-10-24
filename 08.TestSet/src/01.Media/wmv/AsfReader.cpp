#include "stdafx.h"
#include "AsfReader.h"

AsfReader::AsfReader(void)
{
	pHeadObj = NULL;
}

AsfReader::~AsfReader (void)
{
	delete pHeadObj;
	fp.Abort();
}

BOOL AsfReader::Initial( CString name ) 
{	
	//初始化 文件句柄，包缓冲去 和 元数据
	filename = name;
	BOOL ret = fp.Open( filename, CFile::modeRead|CFile::shareDenyNone );
	if ( !ret )  return FALSE;

	OBJECT obj;
	fp.Read( &obj, sizeof(obj) );
	if(obj.ObjectID != HEAD_OBJECT_ID) return FALSE;

#pragma warning(disable : 4244)
	BYTE * buf;
	buf = new BYTE[obj.ObjectSize];

	fp.Seek( 0, CFile::begin );
	fp.Read( buf, obj.ObjectSize );

	pHeadObj = new AsfHeadObject( buf, obj.ObjectSize );
#pragma warning(default : 4244)
	ret = pHeadObj->Initial();
	delete[] buf;
	if( !ret ) 
	{
		return FALSE;
	}

	DATA_OBJECT dataObj;
	fp.Read( &dataObj, sizeof( DATA_OBJECT) );
	ASSERT( dataObj.ObjectID == DATA_OBJECT_ID );
	packetInitOffset  = fp.GetPosition();

	PacketsRead = 0;
	
	return TRUE;
}

BYTE * AsfReader::ReadNextPacket()					//读取下一个Packet ，并将其转化为RtpPacket
{
	if( PacketsRead >= pHeadObj->PacketCounts) return NULL;

	BYTE* buf = new BYTE[ pHeadObj->PacketSize];
	int readLen = fp.Read( buf, pHeadObj->PacketSize );
	if( readLen != pHeadObj->PacketSize ) {
		return  NULL;
	} else {
		PacketsRead ++;
		return buf;
	}
}

RtpPacket * AsfReader::ReadNextRtpPacket()					//读取下一个Packet ，并将其转化为RtpPacket
{
	while(1)
	{
		BYTE* buf = ReadNextPacket();
		if( buf == NULL ) return NULL;
		AsfPacket* asfPack = AsfPacket::CreatePacket( buf, pHeadObj->PacketSize );
		if( asfPack == NULL ) continue;
		RtpPacket * pa = Packet2Rtp( asfPack );

		delete  asfPack;
		delete[] buf;
		return pa;
	}

}

int AsfReader::Locate( WORD i )	//将文件指针定位到第i 个包
{
	ASSERT( i>=0 && i<pHeadObj->PacketCounts );
	fp.Seek( packetInitOffset + i*pHeadObj->PacketSize, CFile::begin );
	PacketsRead = i;
	return 0;
}


RtpPacket * AsfReader::Packet2Rtp(AsfPacket * pa) 
{
	//将从文件读出的packet 转换成 RtpPacket  包 , 用Packet 中的time设置其Timestamp 值
	ASSERT( pa != NULL);

	DWORD rtpSize;
	if( pa->PadLen == 0 ) {
		rtpSize = RtpPacket::RTP_HEAD_LEN + 4 + pa->PacketSize;
#pragma warning(disable : 4244)
		RtpPacket* rtpPa = new RtpPacket ( rtpSize );
#pragma warning(default : 4244)
		BYTE * p = rtpPa->payload;

		*(WORD*) p = htons(0x4000);
		//if( isFirstPacket ) p|= 0x10;
		p += 2;

		*(WORD*) p = htons(rtpPa->payloadSize);
		p += 2;

		memcpy( p, pa->buf, pa->PacketSize );
		ASSERT ( pa->PacketSize + 4 == rtpPa->payloadSize );
		rtpPa->SetTimeStamp( pa->Time );
		return rtpPa;
	}
		
	
	else {
		rtpSize = RtpPacket::RTP_HEAD_LEN + 4 + 7 + 6 + pa->PayloadSize;
#pragma warning(disable : 4244)
		RtpPacket* rtpPa = new RtpPacket ( rtpSize );
#pragma warning(default : 4244)
		BYTE * buf = new BYTE [ rtpPa->payloadSize ];
		BYTE* p = buf;

		*(WORD*) p = htons(0x4000);
		p += 2;

		*(WORD*) p = htons(rtpPa->payloadSize);
		p += 2;

		(*p) = pa->ErrorFlags;
		p +=1;
		for(int i=0; i<pa->ErrorDataLen; i++) {
			(*p) = pa->ErrorData[i];
			p+=1;
		}

		(*p) = 0x40;
		if( (pa->LenFlags&0x01) != 0 ) {
			(*p)|=0x01;
		}
		p+=1;

		(*p) = pa->PropFlags;
		p+=1;

		*(WORD*)p =  rtpPa->payloadSize - 4 ;
		p+=2;

		*(DWORD*) p = pa->Time;
		p+=4;

		*(WORD*) p = pa->Duration;
		p+=2;

		memcpy( p, pa->Payload, pa->PayloadSize );
		p+=pa->PayloadSize;
		
		ASSERT( p - buf == rtpPa->payloadSize );


		rtpPa->SetPayLoad( buf, rtpPa->payloadSize );
		rtpPa->SetTimeStamp( pa->Time );
		delete buf;
		return rtpPa;

	}
	
}





