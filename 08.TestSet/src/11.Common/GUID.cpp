#include "stdafx.h"
#include "GUID.h"


/*

0                ~                127

1 2 3  4 5  6 7  8 9  A B C D E F *
E57153E1-EE6E-40C7-A6E0-9ED9A6937F1B

f81d4fae-7dec-11d0-a765-00a0c91e6bf6 


一,时间戳(共60位)

时间戳低(00~31,32位),如上是f81d4fae
时间戳中(32~47,16位),如上是7dec
时间戳高(52~63,12位),如上是11d0的1d0

二,版本号(48~51,共4位),第7个节点的前4位,如上是11d0的第一个1

0001 以时间为基础
0010 保留给DCE,嵌入式POSIX的UID
0011 以名称为基础
0100 随机或伪随机生成

三,GUID变体类型(64~66,共3位),位于第9个字节的前3位a765的a

000 保留,新生的向后兼容
100 在本文指定的变体
101 
110 保留,微软公司向后兼容
111 保留,为将来的定义

四,时钟序号(67~79,共14位)

时钟序号高(67~71,5位)
时钟序号低(72~78,8位)

五,NODE地址标识(80~127,48位)

//------------------------------------------------------------------

一,版本为1时
时间戳,距1582-10-15 00:00:00.00以100纳秒的计数
时钟序,如果先前时钟序列已知,加1即可,否则随机产生
NODE,采用主机MAC地址,如果没有则随机产生

二,版本为3时
时间戳,由名字空间产生一个60位数
时钟序,由名字空间产生一个14位数
NODE,由名字空间产生一个48位数

三,版本为4时
时间戳,随机产生一个60位数
时钟序,随机产生一个14位数
NODE,随机产生一个48位数

*/


CGUID::CGUID()
:m_LastTime(0),
m_wThisTick(GUIDS_PER_TICK)
{
}

CGUID::~CGUID()
{
}


/* get-current_time -- get time as 60 bit 100ns ticks since whenever.
Compensate for the fact that real clock resolution is
less than 100ns. */
void CGUID::GetCurTimestamp(GUIDTIME *pTimestamp)
{
    if (NULL == pTimestamp) return;

    GUIDTIME TimeNow = 0;

    while (1)
    {
        this->GetSystemTime(&TimeNow);

        /* if clock reading changed since last UUID generated... */
        if (m_LastTime != TimeNow)
        {
            /* reset count of uuids gen'd with this clock reading */
            m_wThisTick = 0;
            break;
        }

        if (m_wThisTick < GUIDS_PER_TICK)
        {
            m_wThisTick++;
            break;
        }
        /* going too fast for our clock; spin */
    }

    /* add the count of guids to low order bits of the clock reading */
    *pTimestamp = m_LastTime = TimeNow + m_wThisTick;
}

// 得到距1582-10-15 00:00:00.00以100纳秒的计数
void CGUID::GetSystemTime(GUIDTIME *pTimestamp)
{
    if (NULL == pTimestamp) return;

    ULARGE_INTEGER time = {0};

    GetSystemTimeAsFileTime((FILETIME*)&time);

    /* NT keeps time in FILETIME format which is 100ns ticks since
    Jan 1, 1601.  UUIDs use time in 100ns ticks since Oct 15, 1582.
    The difference is 17 Days in Oct + 30 (Nov) + 31 (Dec)
    + 18 years and 5 leap days.
    */

    time.QuadPart +=
        (unsigned __int64) (1000*1000*10)       // seconds
        * (unsigned __int64) (60 * 60 * 24)       // days
        * (unsigned __int64) (17+30+31+365*18+5); // # of days

    *pTimestamp = time.QuadPart;
}

// 数得到48位随机
void CGUID::GetRandomNode(BYTE *pbyData)
{
    RANDOM_NESS r;

    /* memory usage stats */
    GlobalMemoryStatus(&r.m);
    /* random system stats */
    GetSystemInfo(&r.s);
    /* 100ns resolution (nominally) time of day */
    GetSystemTimeAsFileTime(&r.t);
    /* high resolution performance counter */
    QueryPerformanceCounter(&r.pc);
    /* milliseconds since last boot */
    r.tc = GetTickCount();
    /* local host name  */
    r.l = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerName(r.szHostName, &r.l);

    memset(pbyData, 0, 6);

    m_MD5.Reset();
    m_MD5.Add(&r, sizeof(r));
    m_MD5.Finish();

    memcpy(pbyData, m_MD5.m_nState, 6);
};

// 得到14位随机数
void CGUID::GetRandomClockSeq(WORD *pwData)
{
    GUIDTIME TimeNow = 0;
    GetSystemTime(&TimeNow);
    TimeNow /= GUIDS_PER_TICK;
    srand((unsigned int)(((TimeNow >> 32) ^ TimeNow)&0xffffffff));

    *pwData = (WORD)rand();
}

// 得到1版GUID
void CGUID::FormatGUIDv1(tGUID *pGUID, GUID_DATA *pGuidData)
{
    // Construct a version 1 uuid with the information we've gathered
    // plus a few constants.

    pGUID->dwTimeLow = (DWORD)(pGuidData->ts & 0xFFFFFFFF);
    pGUID->wTimeMid = (WORD)((pGuidData->ts >> 32) & 0xFFFF);
    pGUID->wTimeHighAndVersion = (WORD)((pGuidData->ts >> 48) & 0x0FFF) | (1 << 12);
    pGUID->byClockSeqHighAndReserved = ((pGuidData->cs & 0x1F00) >> 8) | 0x80;
    pGUID->byClockSeqLow = pGuidData->cs & 0xFF;

    memcpy(&pGUID->Node, &pGuidData->node, 6);
}

// 得到3版GUID
void CGUID::FormatGUIDv3(tGUID *pGUID, BYTE *pbyData)
{
    // Construct a version 3 uuid with the (pseudo-)random number
    // plus a few constants.

    tGUID HashGUID = {0};
    memcpy(pGUID, pbyData, 16);
    memcpy(&HashGUID, pbyData, 16);

    /* convert UUID to local byte order */
    pGUID->dwTimeLow = ntohl(HashGUID.dwTimeLow);
    pGUID->wTimeMid = ntohs(HashGUID.wTimeMid);
    pGUID->wTimeHighAndVersion = ntohs(HashGUID.wTimeHighAndVersion);

    /* put in the variant and version bits */
    pGUID->wTimeHighAndVersion &= 0x0FFF;
    pGUID->wTimeHighAndVersion |= (3 << 12);
    pGUID->byClockSeqHighAndReserved &= 0x1F;
    pGUID->byClockSeqHighAndReserved |= 0x80;
}

// 得到4版GUID
void CGUID::FormatGUIDv4(tGUID *pGUID, WORD *pwData)
{
    // Construct a version 4 uuid with the all random number
    // plus a few constants.

    memcpy(pGUID, pwData, 16);

    /* put in the variant and version bits */
    pGUID->wTimeHighAndVersion &= 0x0FFF;
    pGUID->wTimeHighAndVersion |= (4 << 12);
    pGUID->byClockSeqHighAndReserved &= 0x1F;
    pGUID->byClockSeqHighAndReserved |= 0x80;
}

// 得到1版GUID
BOOL CGUID::CreateGUIDv1(tGUID *pGUID)
{
    if (NULL == pGUID) return FALSE;

    GUID_DATA Data = {0};

    /* get current time */
    GetCurTimestamp(&Data.ts);

    /* get node ID */
    GetRandomNode((BYTE*)&Data.node);

    /* get clock sequence */
    GetRandomClockSeq(&Data.cs);

    /* format guid data */
    FormatGUIDv1(pGUID, &Data);

    return TRUE;
}

// 得到3版GUID
BOOL CGUID::CraateGUIDv3(tGUID *pGUID, tGUID Nsid, void *pName, int nNameLen)
{
    if (NULL == pGUID) return FALSE;

    tGUID NetNsid = Nsid;      /* context GUID in network byte order */

    /* put name space ID in network byte order so it hashes the same
    no matter what endian machine we're on */

    NetNsid.dwTimeLow = htonl(Nsid.dwTimeLow);
    NetNsid.wTimeMid = htons(Nsid.wTimeMid);
    NetNsid.wTimeHighAndVersion = htons(Nsid.wTimeHighAndVersion);

    BYTE byData[16] = {0};

    m_MD5.Reset();
    m_MD5.Add(&NetNsid, sizeof(NetNsid));
    m_MD5.Add(pName, nNameLen);
    m_MD5.Finish();
   // memcpy(byData, m_MD5.getHash(), 16);

    /* the hash is in network byte order at this point */
    FormatGUIDv3(pGUID, byData);

    return TRUE;
}

// 得到4版GUID
BOOL CGUID::CreateGUIDv4(tGUID *pGUID)
{
    if (NULL == pGUID) return FALSE;

    WORD wData[8] = {0};

    for (int i = 0; i < 8; i++)
    {
        wData[i] = rand();
    }
   
    /* format guid data */
    FormatGUIDv4(pGUID, wData);

    return TRUE;
}

#define MY_CHECK(f1, f2) if (f1 != f2) return f1 < f2 ? -1 : 1;

int CGUID::CompareGUID(tGUID *u1, tGUID *u2)
{
    MY_CHECK(u1->dwTimeLow, u2->dwTimeLow);
    MY_CHECK(u1->wTimeMid, u2->wTimeMid);
    MY_CHECK(u1->wTimeHighAndVersion, u2->wTimeHighAndVersion);
    MY_CHECK(u1->byClockSeqHighAndReserved, u2->byClockSeqHighAndReserved);
    MY_CHECK(u1->byClockSeqLow, u2->byClockSeqLow);

    for (int i = 0; i < 6; i++)
    {
        if (u1->Node.nodeID[i] < u2->Node.nodeID[i])
            return -1;
        if (u1->Node.nodeID[i] > u2->Node.nodeID[i])
            return 1;
    }

    return 0;
}