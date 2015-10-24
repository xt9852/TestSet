
#include "stdafx.h"
#include "XTTreeCtrl.h"
#include ".\xttreectrl.h"


UINT WM_CLK_TREE = ::RegisterWindowMessage(_T("WM_CLK_TREE"));
UINT WM_DBCLK_TREE = ::RegisterWindowMessage(_T("WM_DBCLK_TREE"));


IMPLEMENT_DYNAMIC(CXTTreeCtrl, CTreeCtrl)
CXTTreeCtrl::CXTTreeCtrl(void)
    :m_hRoot(NULL)
{    
}

CXTTreeCtrl::~CXTTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CXTTreeCtrl, CTreeCtrl)
    ON_WM_LBUTTONDBLCLK()
    ON_WM_LBUTTONDOWN()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// 设备图标列表
// uImageId    [IN] 图标列表ID
// uImageCount [IN] 图标数量
bool CXTTreeCtrl::SetImage(UINT uImageId, UINT uImageCount)
{
    // 创建图像列表控件
    m_ImageList.Create(uImageId, 16, uImageCount, RGB(255,0,255));
    m_ImageList.SetBkColor(RGB(255,255,255));

    this->SetImageList(&m_ImageList, TVSIL_NORMAL); 
    return true;
}

// 单击
void CXTTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    TVHITTESTINFO HitTestInfo = {0};
    HitTestInfo.pt = point;

    HTREEITEM hSelItem = this->HitTest(&HitTestInfo);

    if (NULL != hSelItem)
    {
        DWORD dwItemData = (DWORD)GetItemData(hSelItem);
        CWnd *ParentWnd = this->GetParent();

        ParentWnd->PostMessage(WM_CLK_TREE, (WPARAM)hSelItem, (LPARAM)dwItemData);
    }

    CTreeCtrl::OnLButtonDown(nFlags, point);
}

// 双击
void CXTTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    HTREEITEM hSelItem = this->GetSelectedItem();
    DWORD dwItemData = (DWORD)GetItemData(hSelItem);
    CWnd *ParentWnd = this->GetParent();

    ParentWnd->PostMessage(WM_DBCLK_TREE, (WPARAM)hSelItem, (LPARAM)dwItemData);

    CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

// 添加节点
// hParent [IN] 父节点
// sName   [IN] 节点名
// dwData  [IN] 节点名
// dwIcon  [IN] 节点图标
HTREEITEM CXTTreeCtrl::AddNode(HTREEITEM hParent, CString sName, DWORD dwData, DWORD dwIcon)
{
    HTREEITEM hItem = InsertItem(sName, dwIcon, dwIcon, hParent, TVI_LAST);
    SetItemData(hItem, dwData);

    return hItem;
}

// 删除节点
// dwData [IN] 节点数据
void CXTTreeCtrl::DelNode(DWORD dwData)
{
    if (NULL == m_hRoot) m_hRoot = this->GetRootItem();

    HTREEITEM hItem = this->FindNode(m_hRoot, NULL, dwData);

    if (NULL != hItem) this->DeleteItem(hItem);
}

// 设置节点名字
// hItem  [IN] 节点句柄
// sParam [IN] 名字
BOOL CXTTreeCtrl::SetNode(HTREEITEM hItem, LPCTSTR sParam, ...)
{
    if (NULL == sParam) return FALSE;

    va_list argptr;
    va_start(argptr, sParam);

    char szName[1000] = {""};
    
    int nRet = _vsntprintf(szName, sizeof(szName), sParam, argptr);

    if (nRet >= 0) this->SetItemText(hItem, szName);

    va_end(argptr);

    return TRUE;
}

// 只查两层
HTREEITEM CXTTreeCtrl::GetNode(DWORD dwData)
{
    if (NULL == m_hRoot) m_hRoot = this->GetRootItem();

    return FindNode(m_hRoot, NULL, dwData);
}

// 只查两层
HTREEITEM CXTTreeCtrl::GetNode(LPCTSTR sName)
{
    if (NULL == m_hRoot) m_hRoot = this->GetRootItem();

    return FindNode(m_hRoot, sName, 0);
}

// 遍历节点
HTREEITEM CXTTreeCtrl::FindNode(HTREEITEM hItem, LPCTSTR sName, DWORD dwData)
{
    while (hItem != NULL)
    {
        if ((NULL != sName) && (this->GetItemText(hItem).Compare(sName) == 0)) return hItem;

        if (this->GetItemData(hItem) == dwData) return hItem;

        if (this->ItemHasChildren(hItem))
        {
            HTREEITEM hSubItem = this->GetChildItem(hItem);

            HTREEITEM hFand = FindNode(hSubItem, sName, dwData);
            if (NULL != hFand) return hFand;
        }

        hItem = this->GetNextItem(hItem, TVGN_NEXT);
    }

    return NULL;
}

