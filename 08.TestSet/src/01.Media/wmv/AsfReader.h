
#pragma once

#include "RtpPacket.h"
#include "AsfPacket.h"
#include "AsfHeadObject.h"


class AsfReader
{
public:
	CFile	fp;					//文件句柄
	CString filename;
	AsfHeadObject *pHeadObj;

	//QWORD	packetCounts;		//packet 个数
	//WORD	packetSize;			//文件的包大小
	QWORD	packetInitOffset;

public:
	AsfReader(void);
	~AsfReader(void);
	int Initial(CString  filename); //初始化 文件句柄，包缓冲去 和 元数据

	int Locate(WORD i);
	BYTE* ReadNextPacket();
	RtpPacket* ReadNextRtpPacket();	//读取下一个Packet ，并将其转化为RtpPacket

private:
	DWORD PacketsRead;

    //将Packet转换成RtpPacket 的函数
	static RtpPacket* Packet2Rtp(AsfPacket* pa); 		
};


