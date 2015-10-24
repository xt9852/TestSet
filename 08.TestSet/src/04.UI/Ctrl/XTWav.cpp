
#include "stdafx.h"
#include "XTEdit.h"
#include ".\xtedit.h"


UINT WM_EDIT_RETURN  = RegisterWindowMessage(_T("WM_EDIT_RETURN"));


IMPLEMENT_DYNAMIC(CXTEdit, CEdit)
CXTEdit::CXTEdit()
{
	m_clrBkg = RGB(187,223,246);
	m_hBrush = (HBRUSH)CreateSolidBrush(m_clrBkg);
}

CXTEdit::~CXTEdit()
{
}


BEGIN_MESSAGE_MAP(CXTEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


void CXTEdit::PreSubclassWindow(void)
{
	ModifyStyle(0, BS_OWNERDRAW);
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	CEdit::PreSubclassWindow();
}

BOOL CXTEdit::PreTranslateMessage(MSG *pMsg)
{
	if ((WM_KEYDOWN == pMsg->message) && (VK_RETURN == pMsg->wParam))
	{
		GetOwner()->PostMessage(WM_EDIT_RETURN, this->GetDlgCtrlID(), NULL);
		return TRUE;
	}

	return CEdit::PreTranslateMessage(pMsg);
}

HBRUSH CXTEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);
	return m_hBrush;
}

void CXTEdit::SetBkgColor(COLORREF clrBkg)
{
	m_clrBkg = clrBkg;
	::DeleteObject(m_hBrush);
	m_hBrush = (HBRUSH)CreateSolidBrush(m_clrBkg);
	this->Invalidate();
}

#include "AV/WaveIn.h"

void CXTEdit::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CFile file;
	if (file.Open("E:\\Downloads\\mp3\\µç²¨.wav", CFile::modeReadWrite))
	{
		RIFF_HEADER riff_header = {0};
		FMT_BLOCK   fmt_block   = {0};
		DATA_BLOCK  data_block  = {0};

		file.Read(&riff_header, sizeof(RIFF_HEADER));
		file.Read(&fmt_block, sizeof(FMT_BLOCK));
		file.Read(&data_block, sizeof(DATA_BLOCK));

		char *pszData = new char[data_block.dwDataSize];
		file.Read(pszData, data_block.dwDataSize);
		file.Close();

		lpDrawItemStruct->rcItem.right = data_block.dwDataSize*2;

		HDC hdc = lpDrawItemStruct->hDC;
		POINT pt = {0,0};

		::MoveToEx(hdc, lpDrawItemStruct->rcItem.right, 128, &pt);
		::LineTo(hdc, 0, 128);

		for (int i = 0; i < data_block.dwDataSize; i++)
		{
			::LineTo(hdc, i*2, (BYTE)(pszData[i+450]));
		}

		delete[] pszData;
	}
}