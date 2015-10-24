#pragma once
#include <map>
#include <string>

typedef std::map<unsigned int, std::string> MAP_UINT_STR;

class CShowData
{
public:
	CShowData(void);
	~CShowData(void);

protected:
    CListCtrl   *m_plstUnasm;
    CListCtrl   *m_plstMemory;
    CListCtrl   *m_plstRegister;

    unsigned long m_dwIconPos;

public:
    bool Init(CListCtrl *plstUnasm, CListCtrl *plstMemory, CListCtrl *plstRegister);

    void UpdateRegList(unsigned short wAx);
    void UpdateUnasm(unsigned char *pbyMem, MAP_UINT_STR *pmapAsm, unsigned long dwPos, unsigned long dwLen);
    void UpdateMemory(unsigned char *pbyMem, unsigned long dwPos, unsigned long dwLen);
    void UpdateUnasmIcon(unsigned long dwCS, unsigned long dwIP);
};
