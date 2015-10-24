#pragma once

/*
AsfPacket 类用于解析从asf文件中读出的packet 原数据。
得到timestamp  ，duration 和payload
AsfPacket 类不修改原数据，不管理内存的分配和释放。
*/

class AsfPacket
{
public:
    const BYTE* buf;		//packet 数据指针
    DWORD PacketSize;		//packet 大小， 对于同一个文件PacketSize 是个常数

    BYTE ErrorFlags;		//packet数据的第一项

    const BYTE *ErrorData;
    BYTE  ErrorDataLen;

    BYTE LenFlags;

    BYTE PropFlags;

    DWORD	PacketLen;
    DWORD	Sequence;
    DWORD	PadLen;
    DWORD	Time;
    WORD	Duration;
    const	BYTE*	Payload;
    DWORD   PayloadSize;			//不包括填充数据
public:
    AsfPacket( const BYTE * , DWORD );
	BOOL	Initial();

public:
    ~AsfPacket(void);
	static AsfPacket* CreatePacket( const BYTE*, DWORD );
};
