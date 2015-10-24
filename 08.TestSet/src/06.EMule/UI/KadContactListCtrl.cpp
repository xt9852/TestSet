//this file is part of eMule
//Copyright (C)2002-2006 Merkur ( strEmail.Format("%s@%s", "devteam", "emule-project.net") / http://www.emule-project.net )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#include "stdafx.h"
//#include "emule.h"
//#include "KademliaWnd.h"
#include "KadContactListCtrl.h"
//#include "Ini2.h"
//#include "OtherFunctions.h"
//#include "emuledlg.h"
#include "../../UI/Memdc.h"

//#include "../IP2Country.h"
//CIP2Country g_IP2Country;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CONContactListCtrl
enum ECols
{
	colID = 1,
	colType,
	colDistance
};


IMPLEMENT_DYNAMIC(CKadContactListCtrl, CMuleListCtrl)

BEGIN_MESSAGE_MAP(CKadContactListCtrl, CMuleListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_WM_DESTROY()
	ON_WM_SYSCOLORCHANGE()
END_MESSAGE_MAP()

CKadContactListCtrl::CKadContactListCtrl()
{
	SetGeneralPurposeFind(true);
	SetName(_T("ONContactListCtrl"));

	m_pImageList = NULL;
	m_pCoutryFlagImageList = NULL;
}

CKadContactListCtrl::~CKadContactListCtrl()
{
}

void CKadContactListCtrl::Init()
{
	SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);
/*
	InsertColumn(colID,GetResString(IDS_ID),LVCFMT_LEFT,100);
	InsertColumn(colType,GetResString(IDS_TYPE) ,LVCFMT_LEFT,50);
	InsertColumn(colDistance,GetResString(IDS_KADDISTANCE),LVCFMT_LEFT,50);
*/	
	//---------------------------------------------->xt
	InsertColumn(0, _T("Addr"), LVCFMT_LEFT, 60);
	InsertColumn(1, _T("ID"), LVCFMT_LEFT, 110);
	InsertColumn(2, _T("Type"), LVCFMT_LEFT, 40);
	InsertColumn(3, _T("Distance"), LVCFMT_LEFT, 110);
	InsertColumn(4, _T("IP"), LVCFMT_LEFT, 90);
	InsertColumn(5, _T("TCP_PORT"), LVCFMT_LEFT, 50);
	InsertColumn(6, _T("UDP_PORT"), LVCFMT_LEFT, 50);
	InsertColumn(7, _T("CreateTime"), LVCFMT_LEFT, 60);
	InsertColumn(8, _T("ExpireTime"), LVCFMT_LEFT, 60);
	//----------------------------------------------<

	//SetAllIcons();
	Localize();

	LoadSettings();
	int iSortItem = GetSortItem();
	bool bSortAscending = GetSortAscending();

	SetSortArrow(iSortItem, bSortAscending);
	SortItems(SortProc, MAKELONG(iSortItem, (bSortAscending ? 0 : 0x0001)));	
}

void CKadContactListCtrl::SetImageList(CImageList* pCountryImageList, CImageList* pImageList)
{
	m_pCoutryFlagImageList = pCountryImageList;
	m_pImageList = pImageList;
}

void CKadContactListCtrl::SaveAllSettings()
{
	SaveSettings();
}

void CKadContactListCtrl::OnSysColorChange()
{
	//CMuleListCtrl::OnSysColorChange();
	CListCtrl::OnSysColorChange();
	SetAllIcons();
}

void CKadContactListCtrl::SetAllIcons()
{
/*	CImageList iml;	
	iml.Create(16,16,theApp.m_iDfltImageListColorFlags|ILC_MASK,0,1);
	iml.SetBkColor(CLR_NONE);
	iml.Add(CTempIconLoader(_T("Contact0")));
	iml.Add(CTempIconLoader(_T("Contact1")));
	iml.Add(CTempIconLoader(_T("Contact2")));
	iml.Add(CTempIconLoader(_T("Contact3")));
	iml.Add(CTempIconLoader(_T("Contact4")));
	ASSERT( (GetStyle() & LVS_SHAREIMAGELISTS) == 0 );
	HIMAGELIST himl = ApplyImageList(iml.Detach());
	if (himl)
		ImageList_Destroy(himl);
*/
}

void CKadContactListCtrl::Localize()
{
	CHeaderCtrl* pHeaderCtrl = GetHeaderCtrl();
	HDITEM hdi;
	hdi.mask = HDI_TEXT;
	CString strRes;

	for (int icol=0;icol< pHeaderCtrl->GetItemCount() ;icol++) 
	{
		switch (icol) 
		{
			/*
			case colID: strRes = GetResString(IDS_ID); break;
			case colType: strRes = GetResString(IDS_TYPE); break;
			case colDistance: strRes = GetResString(IDS_KADDISTANCE); break;
			*/

			//---------------------------------------------->xt
			case 0: strRes = _T("Addr"); break;
			case 1: strRes = _T("ID"); break;
			case 2: strRes = _T("Type"); break;
			case 3: strRes = _T("Distance"); break;
			case 4: strRes = _T("IP"); break;
			case 5: strRes = _T("TCP_PORT"); break;
			case 6: strRes = _T("UDP_PORT"); break;
			case 7: strRes = _T("CreateTime"); break;
			case 8: strRes = _T("ExpireTime"); break;
			//----------------------------------------------<
		}
	
		hdi.pszText = const_cast<LPTSTR>((LPCTSTR)strRes);
		pHeaderCtrl->SetItem(icol, &hdi);
	}

	int iItems = GetItemCount();
	for (int i = 0; i < iItems; i++)
		UpdateContact(i, (Kademlia::CContact*)GetItemData(i), true);
}
	
void CKadContactListCtrl::UpdateContact(int iItem, const Kademlia::CContact* contact, bool bLocalize)
{
	CString id;
	if (!bLocalize) // update the following fields only if really needed (it's quite expensive to always update them)
	{
		contact->GetClientID(&id);
		SetItemText(iItem,colID,id);

		id.Format(_T("%i(%u)"),contact->GetType(), contact->GetVersion());
		SetItemText(iItem,colType,id);

		//---------------------------------------------->xt

		//contact->GetDistance(&id);
		contact->GetHexDistance(&id);
		SetItemText(iItem,colDistance,id);

		CString strIP;
		CString strTcpPort;
		CString strUdpPort;
		CString strCreatTime;
		CString strExpireTime;		
		CString strAddr;
		
		contact->GetAddr(&strAddr);
		contact->GetIPAddress(&strIP);
		contact->GetTCPPort(&strTcpPort);
		contact->GetUDPPort(&strUdpPort);
		time_t ct = contact->GetCreatedTime();
		time_t et = contact->GetExpireTime();

		CTime ctt(ct);
		CTime ett(et);

		strCreatTime.Format(_T("%d:%d:%d"), ctt.GetHour(), ctt.GetMinute(), ctt.GetSecond());
		strExpireTime.Format(_T("%d:%d:%d"), ett.GetHour(), ett.GetMinute(), ett.GetSecond());

		SetItemText(iItem, 0, strAddr);
		SetItemText(iItem, 4, strIP);
		SetItemText(iItem, 5, strTcpPort);
		SetItemText(iItem, 6, strUdpPort);
		SetItemText(iItem, 7, strCreatTime);
		SetItemText(iItem, 8, strExpireTime);
		//----------------------------------------------<

		//SetItem(iItem,0,LVIF_IMAGE,0,contact->GetType()>4?4:contact->GetType(),0,0,0,0);
	}
}

void CKadContactListCtrl::UpdateKadContactCount()
{

	CString id;
//	id.Format(_T("%s (%i)"), GetResString(IDS_KADCONTACTLAB), GetItemCount());
//	theApp.emuledlg->kademliawnd->GetDlgItem(IDC_KADCONTACTLAB)->SetWindowText(id);
}

bool CKadContactListCtrl::ContactAdd(const Kademlia::CContact* contact)
{
	bool bResult = false;
	try
	{
		ASSERT( contact != NULL );
		int iItem = InsertItem(LVIF_TEXT|LVIF_PARAM, GetItemCount(),NULL,0,0,0,(LPARAM)contact);
		if (iItem >= 0)
		{
			bResult = true;
	//		Trying to update all the columns causes one of the connection freezes in win98
	//		ContactRef(contact);
			// If it still doesn't work under Win98, uncomment the '!afxData.bWin95' term
//--------> xt	if (!afxData.bWin95 && iItem >= 0)
				UpdateContact(iItem, contact);
			UpdateKadContactCount();
		}
	}
	catch(...){ASSERT(0);}
	return bResult;
}

void CKadContactListCtrl::ContactRem(const Kademlia::CContact* contact)
{
	try
	{
		ASSERT( contact != NULL );
		LVFINDINFO find;
		find.flags = LVFI_PARAM;
		find.lParam = (LPARAM)contact;
		int iItem = FindItem(&find);
		if (iItem != -1)
		{
			DeleteItem(iItem);
			UpdateKadContactCount();
		}
	}
	catch(...){ASSERT(0);}
}

void CKadContactListCtrl::ContactRef(const Kademlia::CContact* contact)
{
	try
	{
		ASSERT( contact != NULL );
		LVFINDINFO find;
		find.flags = LVFI_PARAM;
		find.lParam = (LPARAM)contact;
		int iItem = FindItem(&find);
		if (iItem != -1)
			UpdateContact(iItem, contact);
	}
	catch(...){ASSERT(0);}
}

BOOL CKadContactListCtrl::OnCommand(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	// ???
	return TRUE;
}

void CKadContactListCtrl::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	// Determine ascending based on whether already sorted on this column
	int iSortItem = GetSortItem();
	bool bOldSortAscending = GetSortAscending();
	bool bSortAscending = (iSortItem != pNMListView->iSubItem) ? true : !bOldSortAscending;

	// Item is column clicked
	iSortItem = pNMListView->iSubItem;

	// Sort table
	UpdateSortHistory(MAKELONG(iSortItem, (bSortAscending ? 0 : 0x0001)));
	SetSortArrow(iSortItem, bSortAscending);
	SortItems(SortProc, MAKELONG(iSortItem, (bSortAscending ? 0 : 0x0001)));

	*pResult = 0;
}

int CKadContactListCtrl::SortProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	Kademlia::CContact* item1 = (Kademlia::CContact*)lParam1;
	Kademlia::CContact* item2 = (Kademlia::CContact*)lParam2; 
	if((item1 == NULL) || (item2 == NULL))
		return 0;

	int iResult;
	switch(LOWORD(lParamSort))
	{
		case colID:
		{
			Kademlia::CUInt128 i1;
			Kademlia::CUInt128 i2;
			item1->GetClientID(&i1);
			item2->GetClientID(&i2);
			iResult = i1.CompareTo(i2);
			break;
		}
		case colType:
			iResult = item1->GetType() - item2->GetType();
			break;
		case colDistance:
		{
			Kademlia::CUInt128 distance1, distance2;
			item1->GetDistance(&distance1);
			item2->GetDistance(&distance2);
			iResult = distance1.CompareTo(distance2);
			break;
		}
		//------------------------------------------------------->xt
		case 0:
			{
				CString strAddr1;
				CString strAddr2;

				item1->GetAddr(&strAddr1);
				item2->GetAddr(&strAddr2);
				iResult = strAddr1.Compare(strAddr2);
				break;
			}
		case 4:
			{
				uint32 nIP1 = item1->GetIPAddress();
				uint32 nIP2 = item2->GetIPAddress();

				byte *pbyIP1 = (byte*)&nIP1;
				byte *pbyIP2 = (byte*)&nIP2;
			
				if (pbyIP1[3] > pbyIP2[3])
					iResult = 1;
				else if (pbyIP1[3] < pbyIP2[3])
					iResult = -1;
				else if (pbyIP1[2] > pbyIP2[2])
					iResult = 1;
				else if (pbyIP1[2] < pbyIP2[2])
					iResult = -1;
				else if (pbyIP1[1] > pbyIP2[1])
					iResult = 1;
				else if (pbyIP1[1] < pbyIP2[1])
					iResult = -1;
				else if (pbyIP1[0] > pbyIP2[0])
					iResult = 1;
				else if (pbyIP1[0] < pbyIP2[0])
					iResult = -1;
				else
					iResult = 0;

				break;
			}
		case 5:
			{
				iResult = item1->GetTCPPort() - item2->GetTCPPort();
				break;
			}
		case 6:
			{
				iResult = item1->GetUDPPort() - item2->GetUDPPort();
				break;
			}
		case 7:
			{
#pragma warning(disable : 4244)
				iResult = item1->GetCreatedTime() - item2->GetCreatedTime();
				break;
			}
		case 8:
			{
				iResult = item1->GetExpireTime() - item2->GetExpireTime();
#pragma warning(default : 4244)
				break;
			}

		//-------------------------------------------------------<
		default:
			return 0;
	}
	if (HIWORD(lParamSort))
		iResult = -iResult;
	return iResult;
}

//----------------------------------------------------------------------------------------------------------------->

void CKadContactListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//if (!Kademlia::CKademlia::IsRunning())
	//	return;
	if (!lpDrawItemStruct->itemData)
		return;

	CDC* odc = CDC::FromHandle(lpDrawItemStruct->hDC);
	BOOL bCtrlFocused = ((GetFocus() == this ) || (GetStyle() & LVS_SHOWSELALWAYS));

	if( (lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED ))
	{
		if(bCtrlFocused)
			odc->SetBkColor(m_crHighlight);
		else
			odc->SetBkColor(m_crNoHighlight);
	}
	else
		odc->SetBkColor(GetBkColor());

	//const CServer* server = (CServer*)lpDrawItemStruct->itemData;
	const Kademlia::CContact* contact = (Kademlia::CContact*)lpDrawItemStruct->itemData;

	CRect rcItem(lpDrawItemStruct->rcItem);
	CMemeryDC dc(CDC::FromHandle(lpDrawItemStruct->hDC), &rcItem);
	CFont* pOldFont = dc.SelectObject(GetFont());
	RECT cur_rec = rcItem;
	COLORREF crOldTextColor = dc.SetTextColor(m_crWindowText);

	int iOldBkMode;
	if (m_crWindowTextBk == CLR_NONE)
	{
		DefWindowProc(WM_ERASEBKGND, (WPARAM)(HDC)dc, 0);
		iOldBkMode = dc.SetBkMode(TRANSPARENT);
	}
	else
		iOldBkMode = OPAQUE;

	CString Sbuffer;

	CHeaderCtrl *pHeaderCtrl = GetHeaderCtrl();
	int iCount = pHeaderCtrl->GetItemCount();
	cur_rec.right = cur_rec.left - 8;
	cur_rec.left += 4;

	for(int iCurrent = 0; iCurrent < iCount; iCurrent++)
	{
		int iColumn = pHeaderCtrl->OrderToIndex(iCurrent);
		if( !IsColumnHidden(iColumn) )
		{
			cur_rec.right += GetColumnWidth(iColumn);
			RECT	cur_backup = cur_rec;
			Sbuffer = GetItemText(lpDrawItemStruct->itemID, iColumn);
			switch(iColumn)
			{
			case 0:
				{
					POINT point = {cur_rec.left, cur_rec.top};
					if (NULL != m_pCoutryFlagImageList && NULL != m_pCoutryFlagImageList->m_hImageList)
					m_pCoutryFlagImageList->DrawIndirect(dc, contact->GetCountryFlag(), point, CSize(18,16), CPoint(0,0), ILD_NORMAL);	
					cur_rec.left += 20;
					break;
				}
			case 1:
				{
					POINT point = {cur_rec.left, cur_rec.top};
					m_pImageList->Draw(dc,contact->GetType()>4?4:contact->GetType(), point, ILD_NORMAL | INDEXTOOVERLAYMASK(1));
					cur_rec.left += 20;
					break;
				}

			case 2:
				{
					/*
					::Rectangle(dc, cur_rec.left, cur_rec.top, cur_rec.left + 50, cur_rec.top + 15);

					HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255,0,0));
					HPEN open = (HPEN)::SelectObject(dc, pen);

					HBRUSH br = ::CreateSolidBrush(RGB(255,0,0));
					HBRUSH obr = (HBRUSH)::SelectObject(dc, br);

					::Rectangle(dc, cur_rec.left + 1, cur_rec.top + 1, cur_rec.left + rand() % 49, cur_rec.top + 14);

					::SelectObject(dc, obr);
					::SelectObject(dc, open);

					cur_rec.left += 51;
					*/
					break;
				}
			default:
				break;
			}
			//get the text justification
			LV_COLUMN lvc;
			lvc.mask = LVCF_FMT | LVCF_WIDTH;
			GetColumn(iColumn, &lvc);
			UINT nJustify = DT_LEFT;
			switch(lvc.fmt & LVCFMT_JUSTIFYMASK) 
			{
			case LVCFMT_RIGHT:
				nJustify = DT_RIGHT;
				break;
			case LVCFMT_CENTER:
				nJustify = DT_CENTER;
				break;
			default:
				break;
			}
#define MLC_DT_TEXT (DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS)

			dc->DrawText(Sbuffer,Sbuffer.GetLength(),&cur_rec,MLC_DT_TEXT | nJustify);
			cur_rec = cur_backup;
			cur_rec.left += GetColumnWidth(iColumn);
		}
	}
	//draw rectangle around selected item(s)
	if ((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		RECT outline_rec = lpDrawItemStruct->rcItem;

		outline_rec.top--;
		outline_rec.bottom++;
		dc->FrameRect(&outline_rec, &CBrush(GetBkColor()));
		outline_rec.top++;
		outline_rec.bottom--;
		outline_rec.left++;
		outline_rec.right--;

		if(bCtrlFocused)
			dc->FrameRect(&outline_rec, &CBrush(m_crFocusLine));
		else
			dc->FrameRect(&outline_rec, &CBrush(m_crNoFocusLine));
	}

	if (m_crWindowTextBk == CLR_NONE)
		dc.SetBkMode(iOldBkMode);
	dc.SelectObject(pOldFont);
	dc.SetTextColor(crOldTextColor);
}

