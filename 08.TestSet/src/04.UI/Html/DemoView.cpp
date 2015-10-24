#include "stdafx.h"
//#include "ReusingBrowser.h"
#include "DemoView.h"
#include <MsHTML.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT WM_HTMLVIEW_CLICK = ::RegisterWindowMessage(_T("WM_HTMLVIEW_CLICK"));

CString GetAppPath()
{
    CString strRet;
    TCHAR szBuff[_MAX_PATH];
    VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, szBuff, _MAX_PATH));
    strRet=szBuff;
    int pos=strRet.ReverseFind('\\');
    strRet=strRet.Left(pos);
    return strRet;
}

BOOL IsLeapYear(int year)
{
    return ((((year%4==0)&&(year%100!=0))||(year%400 == 0))?TRUE:FALSE);
}

int GetMonthDays(int year,int month)
{
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
        month == 10 || month == 12)
        return 31;
    else if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else if(month == 2)
        return (IsLeapYear(year)?29:28);

    ASSERT(FALSE);
    return -1;
}

CString ToStr(_variant_t var)
{
    CString strValue;
    _variant_t var_t;
    _bstr_t bst_t;
    COleCurrency var_currency;
    COleDateTime dt;
    switch(var.vt)
    {
    case VT_EMPTY:strValue=_T("");break;
    case VT_UI1:strValue.Format ("%d",var.bVal);break;
    case VT_UI2:strValue.Format ("%d",var.uiVal);break;
    case VT_UI4:strValue.Format ("%d",var.ulVal);break;
    case VT_UINT:strValue.Format("%d",var.uintVal);break;
    case VT_I2:strValue.Format ("%d",var.iVal );break;
    case VT_I4:strValue.Format ("%d",var.lVal);break;
    case VT_R4:strValue.Format ("%f",var.fltVal);break;
    case VT_R8:strValue.Format ("%f",var.dblVal);break;
    case VT_INT:strValue.Format ("%d",var.intVal);break;
    case VT_DECIMAL:
        {
            VARIANT newvar;
            VariantInit(&newvar);
            VariantChangeType(&newvar,&var,VARIANT_NOVALUEPROP,VT_BSTR);
            return ToStr(newvar);
        }
        break;
    case VT_CY:
        var_currency=var;
        strValue=var_currency.Format(0);
        break;
    case VT_BSTR:
        var_t=var;
        bst_t=var_t;
        strValue.Format ("%s",(const char*)bst_t);
        break;
    case VT_NULL: strValue=_T(""); break;
    case VT_DATE:
        dt = COleDateTime(var.date);
        strValue.Format("%d年%d月%d日%d时%d分%d秒",dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), dt.GetMinute(), dt.GetSecond());
        break;
    case VT_BOOL: strValue.Format ("%d",var.boolVal ); break;
    default:
        ASSERT(FALSE);
        strValue=_T("");
        break;
    }
    //ASSERT(!strValue.IsEmpty());
    return strValue;
}

//-------------------------------------------------------------------------------
/*
CString GetAppPath();
BOOL IsLeapYear(int year);
int GetMonthDays(int year,int month);
CString ToStr(_variant_t var);
*/


IMPLEMENT_DYNCREATE(CDemoView, CHtmlViewEx)

BEGIN_MESSAGE_MAP(CDemoView, CHtmlViewEx)
    ON_COMMAND(ID_FILE_PRINT, CHtmlViewEx::OnFilePrint)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDemoView, CHtmlViewEx)
    DISP_FUNCTION(CDemoView, "WobbleWnd", WobbleWnd, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

CDemoView::CDemoView()
{
}

CDemoView::~CDemoView()
{
}

void CDemoView::OnInitialUpdate()
{
    CHtmlViewEx::OnInitialUpdate();

    SetContextMenuMode(CustomMenu);

    // 定制消息框默认标题
    SetDefaultMsgBoxTitle("默认标题要改！");
}

void CDemoView::WobbleWnd()
{
    CRect WndRect,NewRect;

    CWnd* pFrame = AfxGetMainWnd();
    if( !(pFrame && IsWindow(pFrame->m_hWnd)) )
        return;

    pFrame->GetWindowRect(&WndRect);

    int XOffset,YOffset;

    for(int i=0; i<50; i++)
    {
        XOffset = (rand() % 40) - 20;// 在-20 - 19之间的随机数
        YOffset = (rand() % 40) - 20;
        NewRect = WndRect;
        NewRect.OffsetRect(XOffset, YOffset);
        pFrame->MoveWindow(NewRect);
        Sleep(50);
    }
}

DROPEFFECT CDemoView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
    TRACE("OnDragEnter\n");
    if(pDataObject->IsDataAvailable(CF_HDROP))
        return DROPEFFECT_MOVE;


    return CHtmlViewEx::OnDragEnter(pDataObject, dwKeyState, point);
}

DROPEFFECT CDemoView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
    TRACE("OnDragOver\n");
    if(pDataObject->IsDataAvailable(CF_HDROP))
        return DROPEFFECT_MOVE;

    return CHtmlViewEx::OnDragOver(pDataObject, dwKeyState, point);
}

#define FILE_NAME_LENGTH 2048

BOOL CDemoView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
    if(pDataObject->IsDataAvailable(CF_HDROP))
    {
        CStringList FileList;

        CString sMsg = "文件：";

        char szFileName[FILE_NAME_LENGTH];
        HGLOBAL hData = pDataObject->GetGlobalData(CF_HDROP);
        DROPFILES* pDropFiles = (DROPFILES*)GlobalLock((HGLOBAL)hData);
        HDROP hFilesInfo = (HDROP)pDropFiles;
        UINT wTotalFiles = DragQueryFile(hFilesInfo, -1, NULL, 0);
        for (UINT wIndex = 0; wIndex < wTotalFiles; wIndex++)
        {
            DragQueryFile(hFilesInfo, wIndex, (LPSTR)szFileName, FILE_NAME_LENGTH);
            FileList.AddTail(szFileName);
            sMsg += "\r\n";
            sMsg += szFileName;
        }
        GlobalUnlock(hData);

        MessageBox(sMsg);

        return TRUE;
    }

    return CHtmlViewEx::OnDrop(pDataObject, dropEffect, point);
}

#define ID_RED		1000
#define ID_GREEN	1001
#define ID_BLUE		1002
#define ID_NONE		1003

HRESULT CDemoView::OnShowCustomContextMenu(LPPOINT ppt, LPUNKNOWN pcmdtReserved,LPDISPATCH pdispReserved)
{
    if ((ppt==NULL)||(pcmdtReserved==NULL)||(pcmdtReserved==NULL))
        return S_OK;

    HRESULT hr=0;
    IOleWindow *oleWnd=NULL;
    hr=pcmdtReserved->QueryInterface(IID_IOleWindow, (void**)&oleWnd);
    if((hr != S_OK)||(oleWnd == NULL))
        return S_OK;

    HWND hwnd=NULL;
    hr=oleWnd->GetWindow(&hwnd);
    if((hr!=S_OK)||(hwnd==NULL))
    {
        oleWnd->Release();
        return S_OK;
    }

    IHTMLElement *pElem=NULL;
    hr = pdispReserved->QueryInterface(IID_IHTMLElement, (void**)&pElem);
    if(hr != S_OK)
    {
        oleWnd->Release();
        return S_OK;
    }

    //IHTMLElementPtr	pParentElem=NULL;
	IHTMLElement *pParentElem=NULL;

    _bstr_t	tagID;
    BOOL go=TRUE;

    pElem->get_id(&tagID.GetBSTR());

    while(go && tagID.length()==0)
    {
        hr=pElem->get_parentElement(&pParentElem);
        if(hr==S_OK && pParentElem!=NULL)
        {
            pElem->Release();
            pElem=pParentElem;
            pElem->get_id(&tagID.GetBSTR());
        }
        else
            go=FALSE;
    };
    if(tagID.length()==0)
        tagID="no id";

    CMenu Menu,SubMenu;
    Menu.CreatePopupMenu();


    CString strTagID = ToStr(tagID);

    if(strTagID == "red")
        Menu.AppendMenu(MF_BYPOSITION, ID_RED, "您点击的是红色");
    else if(strTagID == "green")
        Menu.AppendMenu(MF_BYPOSITION, ID_GREEN, "您点击的是绿色");
    else if(strTagID == "blue")
        Menu.AppendMenu(MF_BYPOSITION, ID_BLUE, "您点击的是蓝色");
    else
        Menu.AppendMenu(MF_BYPOSITION, ID_NONE, "你点了也白点，请在指定的地方点击");

    int MenuID=Menu.TrackPopupMenu(TPM_RETURNCMD|TPM_LEFTALIGN|TPM_RIGHTBUTTON,ppt->x, ppt->y, this);
    switch(MenuID)
    {
    case ID_RED:
        MessageBox("红色");
        break;
    case ID_GREEN:
        MessageBox("红色");
        break;
    case ID_BLUE:
        MessageBox("红色");
        break;
    case ID_NONE:
        MessageBox("haha");
        break;
    }

    oleWnd->Release();
    pElem->Release();

    return S_OK;
}

void CDemoView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName,
                                  CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel)
{
    CString strUrl(lpszURL);
    int nIndex = strUrl.Find(_T("image://"));
    if (-1 != nIndex)
    {
        *pbCancel = TRUE;

        CString strFileName = strUrl.Mid(nIndex + 8, strUrl.GetLength() - 8 - 1);
        CString strExName = strFileName.Right(3);

        int nType = 0;
        if (strExName.CompareNoCase(_T("gif")) == 0)
            nType = FILE_GIF;
        else if (strExName.CompareNoCase(_T("jpg")) == 0)
            nType = FILE_JPG;
        else if (strExName.CompareNoCase(_T("bmp")) == 0)
            nType = FILE_BMP;

        ::SendMessage(m_hParentWnd, WM_HTMLVIEW_CLICK, (WPARAM)(LPCTSTR)strFileName, (LPARAM)nType);
    }
}



