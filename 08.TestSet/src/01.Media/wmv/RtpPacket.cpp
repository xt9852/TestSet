#include "StdAfx.h"
#include "RtpPacket.h"

RtpPacket::RtpPacket( WORD size )
{
	ASSERT( size > RTP_HEAD_LEN );
	buffer = new BYTE[ size ];
	bufferSize = size;

	payload = buffer + RTP_HEAD_LEN;
	payloadSize = bufferSize - RTP_HEAD_LEN;
	SetVersion( RTP_VERSION_CONST);
	SetPayLoadType( RTP_PAYLOADTYPE_CONST);
	SetSSRC( RTP_SSRC_CONST);
}

RtpPacket::~RtpPacket(void)
{
	if( buffer != NULL ) {
		delete[] buffer;
	}

}



int RtpPacket::SetPayLoad(const BYTE * pData,DWORD size ) {
	ASSERT ( size == payloadSize );
	memcpy( payload ,pData, size );
	return 0;
}


BYTE	RtpPacket::GetVersion() {
	return buffer[RTP_VERSION_OFFSET];
}

int		RtpPacket::SetVersion(BYTE version) {
	buffer[RTP_VERSION_OFFSET] = version ;
	return 0;
}

BYTE  RtpPacket::GetPayLoadType() {
	return	buffer[RTP_PAYLOADTYPE_OFFSET];
}


int  RtpPacket::SetPayLoadType(BYTE payLoadType ) {
	buffer[RTP_PAYLOADTYPE_OFFSET ] =  payLoadType  ;
	return 0;
}

WORD RtpPacket::GetSeqNum () {
	return ntohs( *(WORD*)(buffer+RTP_SEQ_NUM_OFFSET )  );
}

int		RtpPacket::SetSeqNum(WORD seqNum) {
	*(WORD*)(buffer+RTP_SEQ_NUM_OFFSET) = htons(seqNum);
	return 0;
}

DWORD  RtpPacket::GetTimeStamp( ) {
	return  ntohl( *( DWORD* )( buffer+RTP_TIME_STAMP_OFFSET ) );
}

int RtpPacket::SetTimeStamp( DWORD timeStamp ) {
	*(DWORD*)(buffer+RTP_TIME_STAMP_OFFSET) = htonl(timeStamp);
	return 0;
}


DWORD  RtpPacket::GetSSRC()  {
	return  ntohl( *( DWORD* )( buffer+RTP_SSRC_OFFSET ) );
}

int RtpPacket::SetSSRC( DWORD ssrc ) {
	*(DWORD*)(buffer+RTP_SSRC_OFFSET) = htonl(ssrc);
	return 0;
}

BOOL RtpPacket::SetFirstFlag(void)
{
	payload[0]|=0x80;
	return TRUE;
}
#ifdef  DEBUG

//extern int printf(LPCTSTR pszFormat, ...);


int RtpPacket::Test() {				// for Debug
	RtpPacket packet( 50 );
	packet.SetVersion( 20 );
	packet.SetPayLoadType( 96);
	packet.SetTimeStamp( 1000 );
	BYTE pay[50-12];
	packet.SetPayLoad(pay, 50-12);
	packet.PacketOut();
	return 0;
}

int RtpPacket::PacketOut() {
	CString str;
	for(int i = 0; i < 32; i++ ) {
		str.AppendFormat( "%02x ",payload[ i ] );
		if( i%16 == 15 ) str.AppendFormat( "\n" );
	}
	return 0;
}



# endif 







