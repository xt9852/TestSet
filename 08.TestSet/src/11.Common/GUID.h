
#pragma once
#include "Base/MD5.h"

#define GUIDS_PER_TICK 1024

typedef __int64 GUIDTIME;

typedef struct
{
    BYTE nodeID[6];

} GUID_NODE;

typedef struct
{
    DWORD       dwTimeLow;
    WORD        wTimeMid;
    WORD        wTimeHighAndVersion;
    BYTE        byClockSeqHighAndReserved;
    BYTE        byClockSeqLow;
    GUID_NODE   Node;

} tGUID;

/* data type for UUID generator persistent state */
typedef struct
{
    GUIDTIME    ts;    /* saved timestamp */
    GUID_NODE   node;  /* saved node ID */
    WORD        cs;    /* saved clock sequence */

} GUID_DATA;

typedef struct
{
    LARGE_INTEGER   pc;
    MEMORYSTATUS    m;
    SYSTEM_INFO     s;
    FILETIME        t;
    DWORD           tc;
    DWORD           l;
    char szHostName[MAX_COMPUTERNAME_LENGTH + 1];

} RANDOM_NESS;

class CGUID
{
public:
    CGUID();
    ~CGUID();

protected:
    GUIDTIME    m_LastTime;
    WORD        m_wThisTick;
    CMD5        m_MD5;

    void GetRandomNode(BYTE *pbyData);
    void GetRandomClockSeq(WORD *pwData);    
    void GetSystemTime(GUIDTIME *pTimestamp);
    void GetCurTimestamp(GUIDTIME *pTimestamp);
    void FormatGUIDv1(tGUID *pGUID, GUID_DATA *pGuidData);
    void FormatGUIDv3(tGUID *pGUID, BYTE *pbyData);
    void FormatGUIDv4(tGUID *pGUID, WORD *pwData);

public:

    BOOL CreateGUIDv1(tGUID *pGUID);
    BOOL CreateGUIDv4(tGUID *pGUID);
    BOOL CraateGUIDv3(tGUID *pGUID, tGUID Nsid, void *pName, int nNameLen);
    int CompareGUID(tGUID *u1, tGUID *u2);
};