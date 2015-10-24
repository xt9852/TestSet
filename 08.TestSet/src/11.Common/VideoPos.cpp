
#include "stdafx.h"
#include "VideoPos.h"


CVideoPos::CVideoPos()
    :m_nCount(0),
    m_pVideoPos(NULL)
{
}

CVideoPos::~CVideoPos()
{
    if (NULL != m_pVideoPos) delete[] m_pVideoPos;
}


void CVideoPos::Init(UINT nCount, int *pnPos)
{
    if (NULL != m_pVideoPos) delete[] m_pVideoPos;

    m_pVideoPos = new VIDEOPOS[nCount];
    m_nCount = nCount;

    for (UINT i = 0; i < nCount; i++)
    {
        m_pVideoPos[i].bSaveAV = false;
        m_pVideoPos[i].bUsed = false;
        m_pVideoPos[i].x = *pnPos++;
        m_pVideoPos[i].y = *pnPos++;
        m_pVideoPos[i].dwChanId = 0;
        m_pVideoPos[i].dwUserId = 0;
    }
}

int CVideoPos::GetIndexChan(DWORD dwChanId)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            m_pVideoPos[i].dwChanId == dwChanId)
        {
            return i;
        }
    }

    return -1;
}

int CVideoPos::GetIndexUser(DWORD dwUserId)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            m_pVideoPos[i].dwUserId == dwUserId)
        {
            return i;
        }
    }
    return -1;
}

bool CVideoPos::UseVideoPos(DWORD dwChanId, DWORD dwUserId, int &x, int &y, UINT &nIndex)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            dwChanId == m_pVideoPos[i].dwChanId &&
            dwUserId == m_pVideoPos[i].dwUserId)
        {
            return false;
        }
        else if (!m_pVideoPos[i].bUsed)
        {
            m_pVideoPos[i].bUsed = true;
            m_pVideoPos[i].dwChanId = dwChanId;
            m_pVideoPos[i].dwUserId = dwUserId;

            x = m_pVideoPos[i].x;
            y = m_pVideoPos[i].y;
            nIndex = i;
            return true;
        }
    }

    return false;
}

bool CVideoPos::UseVideoPos(DWORD dwChanId, DWORD dwUserId, int &x, int &y)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            dwChanId == m_pVideoPos[i].dwChanId &&
            dwUserId == m_pVideoPos[i].dwUserId)
        {
            return false;
        }
        else if (!m_pVideoPos[i].bUsed)
        {
            m_pVideoPos[i].bUsed = true;
            m_pVideoPos[i].dwChanId = dwChanId;
            m_pVideoPos[i].dwUserId = dwUserId;

            x = m_pVideoPos[i].x;
            y = m_pVideoPos[i].y;
            return true;
        }
    }
    return false;
}

bool CVideoPos::UseVideoPos(DWORD dwChanId, LPCTSTR strFile, int &x, int &y)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            m_pVideoPos[i].strFile.Compare(strFile) == 0)
        {
            return false;
        }
        else if (!m_pVideoPos[i].bUsed)
        {
            m_pVideoPos[i].bUsed = true;
            m_pVideoPos[i].strFile = strFile;
            m_pVideoPos[i].dwChanId = dwChanId;

            x = m_pVideoPos[i].x;
            y = m_pVideoPos[i].y;
            return true;
        }
    }

    return false;
}

bool CVideoPos::RelVideoPosChan(DWORD dwChanId)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            dwChanId == m_pVideoPos[i].dwChanId)
        {
            m_pVideoPos[i].bUsed = false;
            m_pVideoPos[i].bSaveAV = false;
            m_pVideoPos[i].dwChanId = 0;
            m_pVideoPos[i].dwUserId = 0;
            m_pVideoPos[i].strFile.Empty();
            return true;
        }
    }
    return false;
}

bool CVideoPos::RelVideoPosUser(DWORD dwUserId)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            dwUserId == m_pVideoPos[i].dwUserId)
        {
            m_pVideoPos[i].bUsed = false;
            m_pVideoPos[i].bSaveAV = false;
            m_pVideoPos[i].dwChanId = 0;
            m_pVideoPos[i].dwUserId = 0;
            m_pVideoPos[i].strFile.Empty();
            return true;
        }
    }
    return false;
}

bool CVideoPos::SetSaveAV(UINT nIndex, bool bSave)
{
    if (nIndex > m_nCount) return false;

    m_pVideoPos[nIndex].bSaveAV = bSave;
    return true;
}

bool CVideoPos::GetXY(UINT nIndex, int &x, int &y)
{
    if (nIndex > m_nCount) return false;

    x = m_pVideoPos[nIndex].x;
    y = m_pVideoPos[nIndex].y;
    return true;
}

bool CVideoPos::IsUse(UINT nIndex)
{
    if (nIndex > m_nCount) return false;

    return  m_pVideoPos[nIndex].bUsed;
}

bool CVideoPos::IsSaveAV(UINT nIndex)
{
    if (nIndex > m_nCount) return false;

    return  m_pVideoPos[nIndex].bSaveAV;
}

DWORD CVideoPos::GetUserId(UINT nIndex)
{
    if (nIndex > m_nCount) return 0;

    return  m_pVideoPos[nIndex].dwUserId;
}

DWORD CVideoPos::GetChanId(UINT nIndex)
{
    if (nIndex > m_nCount) return 0;

    return  m_pVideoPos[nIndex].dwChanId;
}

DWORD CVideoPos::GetChanId(LPCTSTR strFile)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            m_pVideoPos[i].strFile.Compare(strFile) == 0)
        {
            return m_pVideoPos[i].dwChanId;
        }
    }

    return 0;
}

DWORD CVideoPos::GetChanIdUser(DWORD dwUserId)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            dwUserId == m_pVideoPos[i].dwUserId)
        {
            return m_pVideoPos[i].dwChanId;
        }
    }

    return 0;
}

CString CVideoPos::GetFileName(DWORD dwChanId)
{
    for (UINT i = 0; i < m_nCount; i++)
    {
        if (m_pVideoPos[i].bUsed &&
            dwChanId == m_pVideoPos[i].dwChanId)
        {
            return m_pVideoPos[i].strFile;
        }
    }

    return _T("");
}

