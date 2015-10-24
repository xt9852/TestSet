#pragma once


typedef struct _DATAPACKET_HEADER {
    WORD			m_nTotalLength;
    WORD			m_nSeqNum;
    DWORD			m_nTimeStamp;
    DWORD			m_nSecond;
    BYTE			m_nChanID;
    BYTE			m_nPayloadType;
    BYTE			m_nDataType;
    BYTE			m_bKeyFrame;
    WORD			m_nDataLen;
} DATAPACKET_HEADER;


class Parser
{
public:
	Parser( CString );
	virtual ~Parser(void);

	virtual BOOL	Initial() = 0;
	virtual CString GetSDP() = 0;
	virtual DWORD	GetDuration() =0;
	virtual DWORD *	GetLengthTable() =0;
	virtual DWORD	GetSecondNum() = 0;
    
public:
	CString filename;
    CString sdp;
    DWORD   duration;

};
