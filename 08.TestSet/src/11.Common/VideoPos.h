
#pragma once


typedef struct _tagVideoPos
{    
    int     x;
    int     y;
    DWORD   dwChanId;
    DWORD   dwUserId;
    bool    bSaveAV;
    bool    bUsed;
    CString strFile;
}VIDEOPOS, *PVIDEOPOS;


class CVideoPos
{
public:
    CVideoPos();
    ~CVideoPos();

private:
    UINT        m_nCount;
    VIDEOPOS    *m_pVideoPos;

public:
    void Init(UINT nCount, int *pnPos);    
    bool UseVideoPos(DWORD dwChanId, DWORD dwUserId, int &x, int &y, UINT &nIndex);
    bool UseVideoPos(DWORD dwChanId, DWORD dwUserId, int &x, int &y);
    bool UseVideoPos(DWORD dwChanId, LPCTSTR strFile, int &x, int &y);
    bool RelVideoPosChan(DWORD dwChanId);
    bool RelVideoPosUser(DWORD dwUserId);
    bool SetSaveAV(UINT nIndex, bool bSave);
    bool GetXY(UINT nIndex, int &x, int &y);
    bool IsUse(UINT nIndex);
    bool IsSaveAV(UINT nIndex);
    int  GetIndexChan(DWORD dwChanId);
    int  GetIndexUser(DWORD dwUserId);
    DWORD GetUserId(UINT nIndex);
    DWORD GetChanId(UINT nIndex);    
    DWORD GetChanId(LPCTSTR strFile);
    DWORD GetChanIdUser(DWORD dwUserId);
    CString GetFileName(DWORD dwChanId);
};