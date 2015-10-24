
#pragma once


typedef struct _tagBlockEx
{
	DWORD dwFrameLen;  // 帧数据长
	WORD  wFrameCheck; // 帧数据校验码
	WORD  wBlockCount; // 子块数
	DWORD dwTime;      // 播放时间
}BLOCKEX,*PBLOCKEX;

typedef struct _tagPackEx
{
	DWORD dwTime;       // 播放时间

}PACKEX,*PPACKEX;