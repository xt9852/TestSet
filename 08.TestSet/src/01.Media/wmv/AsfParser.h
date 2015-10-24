#pragma once
#include "rm\parser.h"
#include "AsfReader.h"

class AsfParser : public Parser
{
typedef DWORD INDEX;

public:
	AsfReader reader;

	INDEX * index;
	DWORD	numOfIndex;
	DWORD *  pTimeSlotLenTable;	

	DWORD PacketSize;

	WORD audioNumber;
	WORD videoNumber;

	DWORD   audioBitrate;
	DWORD   videoBitrate;
	CString Title;
	CString Author;
	CString Copyright;
	DWORD   Bitrate;
	DWORD   Start_Time;
	DWORD	End_Time;

public:
	AsfParser(CString );
	virtual ~AsfParser(void);
	
    BOOL        Initial();
	CString     GetSDP();
	DWORD	    GetDuration();
	DWORD		GetSecondNum();
	DWORD *		GetLengthTable();

private:
	BOOL		MakeIndex();
	BOOL		MakeSDP();

	BOOL	    GetMetaData ();
	CString		GetPgmpu();
	CString		PgmpuConvert( const CString str);
	CString		GetPgmpu2();

	void		Serialize(CArchive& ar);
	BOOL		Load(CFile *pFile);
	BOOL		Save();
};
