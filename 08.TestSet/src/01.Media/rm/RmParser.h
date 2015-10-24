
#pragma once

#include "os.h"
#include "Parser.h"
#include "RmReader.h"

typedef struct index_type {			//	自定义的索引结构（下标表示时间，以秒为单位) 
		uint32_t offset;			//	从文件头到当前时刻所对应的包的 偏移
		uint16_t num_of_packets;	//	这一秒所包含的包个数
		DWORD	 length_of_data;	//	这一秒所包含的数据的总长度
	}  INDEX;						//	

class RmParser : public Parser
{
public:
	RmParser( CString );
	virtual ~RmParser(void);
private:
	CString		sdp;

	WORD		numOfIndex;

	WORD		streamCount;
	WORD		audioTrackID;
	WORD		videoTrackID;
	WORD		flags;

	DWORD		avgBitRate, avgAudioBitRate, avgVideoBitRate;
	DWORD		maxBitRate, maxAudioBitRate, maxVideoBitRate;
	DWORD		avgPacketSize, avgAudioPacketSize, avgVideoPacketSize;
	DWORD		maxPacketSize, maxAudioPacketSize, maxVideoPacketSize;

	DWORD		duration,audioDuration,videoDuration;
	DWORD		preroll,audioPreroll,videoPreroll;

	DWORD		audioStartTime,videoStartTime;
	CString		audioMimeType,videoMimeType;
	CString		audioTrackName,videoTrackName;

	CString		title;
	CString		copyright;
	CString		comment;
	
	CString		audioOpaque;
	CString		videoOpaque;

	DWORD		*pTimeSlotLenTable;

	INDEX		*index;

	RmReader	*mediaFile;
	BOOL		bSuccess;

public :
	BOOL		Initial();
	CString		GetSDP();
	DWORD		GetDuration();
	DWORD		GetOffset( WORD );
	WORD		GetPacketCounts( WORD );

	DWORD *		GetLengthTable();
	DWORD		GetSecondNum();

	BOOL		SeekIndex( WORD second );
	DWORD		GetNextFrame( UCHAR *pBuf );

private:
	BOOL		MakeSDP();
	BOOL		MakeIndex();
    BOOL        MakeHead();

	void		Serialize(CArchive& ar);
	BOOL		Load(CFile *pFile);
	BOOL		Save();
};
