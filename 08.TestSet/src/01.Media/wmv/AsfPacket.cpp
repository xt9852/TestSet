#include "StdAfx.h"
#include "AsfPacket.h"


AsfPacket::AsfPacket(const BYTE* buffer,  DWORD packetSize)
{
	buf  = buffer;
	PacketSize = packetSize;
}

BOOL	AsfPacket::Initial()
{
    const BYTE* pBuf;
    pBuf = buf;

    ErrorFlags = *pBuf;
    pBuf += 1;

    ErrorDataLen = ErrorFlags&0x0f;			//errorflags 的低四位为纠错数据的长度
    BOOL isOpaque = ErrorFlags&0x10 ? TRUE : FALSE;
    BOOL hasErrorData = ErrorFlags&0x80 ?TRUE : FALSE;
    WORD errorLenType = ErrorFlags&0x60 ;   //B 0110 0000


    if( (ErrorFlags&0xf0) != (BYTE)0x80 )   // assert that it has error data and no Opaque data
    {
        printf("error flag");
        return FALSE;
    }

    ErrorData = pBuf;
    pBuf += ErrorDataLen;


    LenFlags = *pBuf;
    pBuf += 1;

    PropFlags  = *pBuf;
    pBuf += 1;

    int a,b;
    a = (LenFlags&0x02)>>1;
    b = (LenFlags&0x04)>>2;
    int seqLen = b*2 + a + a*b;				//seqLen 表示 SeqLen 成员在文件中占的数据长度

    a = (LenFlags&0x08)>>3;
    b = (LenFlags&0x10)>>4;
    int padLen = b*2 + a + a*b;

    a = (LenFlags&0x20)>>5;
    b = (LenFlags&0x40)>>6;
    int packetLen = b*2 + a + a*b;


    int lenOffset = 1+ ErrorDataLen + 2;
    switch ( packetLen ) {
            case 0 : PacketLen = 0; break;
            case 1 : PacketLen = *pBuf; pBuf += 1; break;
            case 2 : PacketLen = *(WORD*) (pBuf); pBuf += 2;  break;
            case 4 : PacketLen = *(DWORD * ) ( pBuf); pBuf += 4; break;
    }
    switch ( seqLen ) {
            case 0 : Sequence = 0; break;
            case 1 : Sequence = *pBuf; pBuf += 1; break;
            case 2 : Sequence = *(WORD*) (pBuf); pBuf += 2;  break;
            case 4 : Sequence = *(DWORD * ) ( pBuf); pBuf += 4; break;
    }
    switch ( padLen ) {
            case 0 : PadLen = 0; break;
            case 1 : PadLen =  *pBuf; pBuf += 1; break;
            case 2 : PadLen = *(WORD*) (pBuf); pBuf += 2;  break;
            case 4 : PadLen = *(DWORD * ) ( pBuf); pBuf += 4; break;
    }


    Time = *(DWORD*) (pBuf );
    pBuf += 4;
    Duration =*(WORD*)( pBuf );
    pBuf += 2;
    Payload  = pBuf;
    PayloadSize  = PacketSize - (pBuf - buf) - PadLen; // not include  the pad length;
    return TRUE;
}


AsfPacket* AsfPacket::CreatePacket( const BYTE* buffer, DWORD len )
{
	AsfPacket* pack = new AsfPacket( buffer, len );
	BOOL ret = pack->Initial();
	if( !ret )
	{
		delete pack;
		return NULL;
	} else {
		return pack;
	}
}

AsfPacket::~AsfPacket(void)
{
}
