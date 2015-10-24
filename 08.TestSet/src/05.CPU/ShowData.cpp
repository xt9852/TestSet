#include "StdAfx.h"
#include "ShowData.h"



CShowData::CShowData(void)
:m_plstUnasm(NULL),
m_plstMemory(NULL),
m_plstRegister(NULL),
m_dwIconPos(0)
{
}

CShowData::~CShowData(void)
{
}

bool CShowData::Init(CListCtrl *plstUnasm, CListCtrl *plstMemory, CListCtrl *plstRegister)
{
	if ((NULL == plstUnasm) || (NULL == plstMemory) || (NULL == plstRegister)) return false;

    m_plstUnasm = plstUnasm;
    m_plstMemory = plstMemory;
	m_plstRegister = plstRegister;

    return true;
}

void CShowData::UpdateRegList(unsigned short wAx)
{
}

// ÏÔÊ¾»ã±à
void CShowData::UpdateUnasm(unsigned char *pbyMem, MAP_UINT_STR *pmapAsm, unsigned long dwPos, unsigned long dwLen)
{
    if ((NULL == m_plstUnasm) || (NULL == pbyMem) || (0 == dwLen)) return;

    int nItemId = 0;
    char szText[100] = "";

    m_plstUnasm->DeleteAllItems();

    for (unsigned long i = dwPos; i < dwPos + dwLen; )
    {
        nItemId = m_plstUnasm->GetItemCount();
        m_plstUnasm->InsertItem(nItemId, _T(""), -1);

        sprintf(szText, _T("%04X:%04X"), ((i&0xFFFF0000) >> 16), i&0x0000FFFF); // ÉèÖÃµØÖ·
        m_plstUnasm->SetItemText(nItemId, 1, szText);

        if ((0x05 == pbyMem[i]) ||
            (pbyMem[i] >= 0x2B) && (pbyMem[i] <= 0x37))
        {
            sprintf(szText, _T("%02X %02X %02X"), pbyMem[i], pbyMem[i+1], pbyMem[i+2]);                 // col 2 code
            m_plstUnasm->SetItemText(nItemId, 2, szText);
            sprintf(szText, _T("%s%02X%02X"), (*pmapAsm)[pbyMem[i]].c_str(), pbyMem[i+2], pbyMem[i+1]); // col 3 asm
            m_plstUnasm->SetItemText(nItemId, 3, szText);
            i += 3;
        }
        else
        {
            sprintf(szText, _T("%02X"), pbyMem[i]);
            m_plstUnasm->SetItemText(nItemId, 2, szText);
            m_plstUnasm->SetItemText(nItemId, 3, (*pmapAsm)[pbyMem[i]].c_str());
            i++;
        }
    }
}
void CShowData::UpdateMemory(unsigned char *pbyMem, unsigned long dwPos, unsigned long dwLen)
{
    if ((NULL == m_plstMemory) || (NULL == pbyMem) || (0 == dwLen)) return;

    int nItemId = 0;
    char szTemp[10] = "";
    char szText[100] = "";    

    m_plstMemory->DeleteAllItems();

    for (unsigned long i = dwPos; i < dwPos + dwLen; i += 16)
    {
        nItemId = m_plstMemory->GetItemCount();
        m_plstMemory->InsertItem(nItemId, _T(""), -1);

        sprintf(szText, _T("%04X:%04X"), ((i&0xFFFF0000) >> 16), i&0x0000FFFF);	// col 1 address

        m_plstMemory->SetItemText(nItemId, 0, szText);

        szText[0] = '\0';

        for (int j = 0; j < 16; j++)
        {
            sprintf(szTemp, _T("%02X%s"), pbyMem[i+j], (j == 7)?"----":" ");    // col 2 code
            strcat(szText, szTemp);
        }

        m_plstMemory->SetItemText(nItemId, 1, szText);
/*
        for (int j = 0; j < 16; j++)
        {
            sprintf(szText, _T("%c "), m_pbyMem[i+j]);                          // col 3 ascii
        }

        m_plstMemory->SetItemText(nItemId, 2, szText);
*/
    }
}

void CShowData::UpdateUnasmIcon(unsigned long dwCS, unsigned long dwIP)
{
    if (NULL == m_plstUnasm) return;

    m_plstUnasm->SetItem(m_dwIconPos, 0, LVIF_IMAGE, _T(""), -1, NULL, NULL, NULL);

    char szTemp[100] = "";
    char szAddr[100] = "";
    sprintf(szAddr, _T("%04X:%04X"), dwCS, dwIP);

    int nCount = m_plstUnasm->GetItemCount();
    for (int i = 0; i < nCount; i++)
    {
        m_plstUnasm->GetItemText(i, 1, szTemp, sizeof(szTemp)-1);
        if (0 == strcmp(szTemp, szAddr))
        {
            m_plstUnasm->SetItem(i, 0, LVIF_IMAGE | LVIF_STATE, _T(""), 4, LVIS_SELECTED, LVIS_SELECTED, NULL);
            m_dwIconPos = i;
            break;
        }
    }
}
