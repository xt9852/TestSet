// CheckComboBox.h: interface for the CCheckComboBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKCOMBOBOX_H__181012A7_43A3_48DE_8C1E_F8D91E503439__INCLUDED_)
#define AFX_CHECKCOMBOBOX_H__181012A7_43A3_48DE_8C1E_F8D91E503439__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _WTL_NO_CSTRING
#include <atlstr.h>
#include <atlcrack.h>
//#include <atlstr.h>
#define _WTL_NO_CSTRING
#include <atlstr.h>

extern "C" LRESULT WINAPI ComboBoxListBoxProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

class CCheckComboBox : public CWindowImpl<CCheckComboBox, CComboBox>,
    public COwnerDraw<CCheckComboBox>
{
public:    
    DECLARE_WND_SUPERCLASS(_T("check_combobox"), CButton::GetWndClassName())

    CCheckComboBox()
    {
        listbox_ = NULL;
        text_updated_ = FALSE;
        item_height_set_ = FALSE;
    }
    ~CCheckComboBox(){}

    CCheckComboBox& operator =(HWND hWnd)
    {
        CWindowImpl<CCheckComboBox, CComboBox>::SubclassWindow(hWnd); 

        CheckStyle();

        return *this;
    }

    BEGIN_MSG_MAP(CCheckComboBox)    
        MSG_WM_CREATE(OnCreate)
        MSG_WM_CTLCOLORLISTBOX(OnCtlColorListBox)
        MSG_WM_GETTEXT(OnGetText)
        MSG_WM_GETTEXTLENGTH(OnGetTextLength)
        REFLECTED_COMMAND_CODE_HANDLER_EX(CBN_DROPDOWN,OnDropDown)
        CHAIN_MSG_MAP_ALT(COwnerDraw<CCheckComboBox>, 1)
        DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    LRESULT OnCreate(LPCREATESTRUCT /*lpCreateStruct*/)
    {
        CheckStyle();

        return 0;
    }

    void CheckStyle()
    {
        DWORD style = GetStyle();

        // Make sure to use the CBS_DROPDOWNLIST style
        ATLASSERT(style & CBS_DROPDOWNLIST);
        // Make sure to use the CBS_OWNERDRAWVARIABLE style
        ATLASSERT(style & CBS_OWNERDRAWVARIABLE);
        // Use default strings. We need the itemdata to store checkmarks
        ATLASSERT(style & CBS_HASSTRINGS);
    }

    void DrawItem(LPDRAWITEMSTRUCT lpdis)
    {        
        CRect check_rect = lpdis->rcItem;
        CRect text_rect = lpdis->rcItem;

        CString text;

        // 0 - No check, 1 - Empty check, 2 - Checked
        int check = 0;

        // Check if we are drawing the static portion of the combobox
        if ((LONG)lpdis->itemID < 0) 
        {
            // Make sure the m_strText member is updated
            RecalcText();

            // Get the text
            text = text_;

            // Don't draw any boxes on this item
            check = 0;
        }

        // Otherwise it is one of the items
        else 
        {
            GetLBText(lpdis->itemID, text);
            check = 1 + (GetItemData(lpdis->itemID) != 0);

            TEXTMETRIC metrics;
            GetTextMetrics(lpdis->hDC, &metrics);

            check_rect.left       = 0;
            check_rect.right     = check_rect.left + metrics.tmHeight + metrics.tmExternalLeading + 6;
            check_rect.top       += 1;
            check_rect.bottom -= 1;

            text_rect.left = check_rect.right;
        }

        if (check > 0) 
        {
            SetBkColor(lpdis->hDC, GetSysColor(COLOR_WINDOW));
            SetTextColor(lpdis->hDC, GetSysColor(COLOR_WINDOWTEXT));

            UINT state = DFCS_BUTTONCHECK;

            if (check > 1)
                state |= DFCS_CHECKED;

            // Draw the checkmark using DrawFrameControl
            DrawFrameControl(lpdis->hDC, check_rect, DFC_BUTTON, state);
        }

        if (lpdis->itemState & ODS_SELECTED) 
        {
            SetBkColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHT));
            SetTextColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
        }
        else 
        {
            SetBkColor(lpdis->hDC, GetSysColor(COLOR_WINDOW));
            SetTextColor(lpdis->hDC, GetSysColor(COLOR_WINDOWTEXT));
        }

        // Erase and draw
        ExtTextOut(lpdis->hDC, 0, 0, ETO_OPAQUE, &text_rect, 0, 0, 0);
        DrawText(lpdis->hDC, ' ' + text, text.GetLength() + 1, &text_rect, DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

        if ((lpdis->itemState & (ODS_FOCUS|ODS_SELECTED)) == (ODS_FOCUS|ODS_SELECTED))
            DrawFocusRect(lpdis->hDC, &text_rect);
    }

    void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
    {
        CClientDC dc(m_hWnd);
        HFONT font = dc.SelectFont((HFONT)::SendMessage(m_hWnd, WM_GETFONT, 0, 0));
        if (font)
        {
            TEXTMETRIC metrics;
            dc.GetTextMetrics(&metrics);

            lpMeasureItemStruct->itemHeight = metrics.tmHeight + metrics.tmExternalLeading;

            // An extra height of 2 looks good I think. 
            // Otherwise the list looks a bit crowded...
            lpMeasureItemStruct->itemHeight += 2;


            // This is needed since the WM_MEASUREITEM message is sent before
            // ATL hooks everything up if used in i dialog. So adjust the
            // static portion of the combo box now
            if (!item_height_set_) 
            {
                item_height_set_ = TRUE;
                SetItemHeight(-1, lpMeasureItemStruct->itemHeight);
            }

            dc.SelectFont(font);
        }
    }

    LRESULT OnCtlColorListBox(HDC hdc, HWND hwnd)
    {
        if (NULL == listbox_)
        {
            if (hwnd != 0 && hwnd != m_hWnd)
            {
                // Save the listbox handle
                listbox_ = hwnd;

                // Do the subclassing
                sWndProc_ = (WNDPROC)::GetWindowLong(listbox_, GWL_WNDPROC);
                ::SetWindowLong(listbox_, GWL_WNDPROC, (LONG)ComboBoxListBoxProc);
            }

        }
        return DefWindowProc();
    }

    //
    // Make sure the combobox window handle is updated since
    // there may be many CCheckComboBox windows active
    //
    LRESULT OnDropDown(UINT /*uNotifyCode*/, int /*nID*/, CWindow /*wndCtl*/)
    {
        DefWindowProc();
        Invalidate();

        sComboBox_ = this;

        return 0;
    }    

    //
    // By adding this message handler, we may use CWindow::GetText()
    //
    LRESULT OnGetText(int len, LPTSTR str)
    {
        // Make sure the text is updated
        RecalcText();

        if (NULL == str)
            return -1;

        // Copy the 'fake' window text
        lstrcpyn(str, text_, len);
        return text_.GetLength();
    }    

    //
    // By adding this message handler, we may use CWindow::GetTextLength()
    //
    LRESULT OnGetTextLength()
    {
        // Make sure the text is updated
        RecalcText();
        return text_.GetLength();
    }

    //
    // This routine steps through all the items and builds
    // a string containing the checked items
    //
    void RecalcText()
    {
        if (!text_updated_) 
        {
            CString all_text;

            // Get the list count
            int count = GetCount();

            // Get the list separator
            TCHAR buf[10] = {0};
            GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SLIST, buf, sizeof(TCHAR)*10);

            CString separator = buf;

            // If none found, the the ';'
            if (separator.GetLength() == 0)
                separator = _T(';');

            // Trim extra spaces
            separator.TrimRight();

            // And one...
            separator += _T(' ');

            for (int i = 0; i < count; i++) 
            {
                if (GetItemData(i)) 
                {
                    CString item_text;
                    GetLBText(i, item_text);

                    if (!all_text.IsEmpty())
                        all_text += separator;

                    all_text += item_text;
                }
            }

            // Set the text
            text_ = all_text;

            text_updated_ = TRUE;
        }
    }

    // Selects /unselects the specified item
    int SetCheck(int index, BOOL flag)
    {
        int ret = SetItemData(index, flag);
        if (ret == CB_ERR)
        {
            return -1;
        }

        // Signal that the text need updating
        text_updated_ = FALSE;

        // Redraw the window
        Invalidate(FALSE);

        return ret;
    }

    // Returns checked state
    BOOL GetCheck(int index)
    {
        return GetItemData(index);
    }

    // Selects all/unselects all
    void SelectAll(BOOL bCheck = TRUE)
    {
        for (int i = 0; i < GetCount(); i++)
            SetCheck(i, bCheck);
    }

public:
    static WNDPROC sWndProc_;
    static CCheckComboBox* sComboBox_;

protected:
    // The subclassed COMBOLBOX window (notice the 'L')
    HWND listbox_;

    // The string containing the text to display
    CString text_;
    BOOL text_updated_;

    // A flag used in MeasureItem, see comments there
    BOOL item_height_set_;
};

WNDPROC CCheckComboBox::sWndProc_ = NULL;
CCheckComboBox* CCheckComboBox::sComboBox_ = NULL;

extern "C" LRESULT FAR PASCAL ComboBoxListBoxProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch (nMsg) 
    {
    case WM_RBUTTONDOWN: 
        {
            // If you want to select all/unselect all using the
            // right button, remove this ifdef. Personally, I don't really like it
#if FALSE
            if (CCheckComboBox::sComboBox_ != 0) 
            {
                int count = CCheckComboBox::sComboBox_->GetCount();
                int sel_count = 0;

                for (int i = 0; i < count; i++) 
                {
                    if (CCheckComboBox::sComboBox_->GetCheck(i))
                        sel_count++;
                }   
                CCheckComboBox::sComboBox->SelectAll(sel_count!= count);

                // Make sure to invalidate this window as well
                InvalidateRect(hWnd, 0, FALSE);
                SendMessage(CCheckComboBox::sComboBox_->GetParent(), WM_COMMAND, MAKELONG(GetWindowLong(CCheckComboBox::sComboBox_->m_hWnd, GWL_ID), CBN_SELCHANGE), (LPARAM)(CCheckComboBox::sComboBox_->m_hWnd));

            }
#endif

            break;
        }

        // Make the combobox always return -1 as the current selection. This
        // causes the lpDrawItemStruct->itemID in DrawItem() to be -1
        // when the always-visible-portion of the combo is drawn
    case LB_GETCURSEL:
        {
            return -1;
        }        

    case WM_CHAR: 
        {
            if (wParam == VK_SPACE) 
            {
                // Get the current selection
                int nIndex = CallWindowProc(CCheckComboBox::sWndProc_, hWnd, LB_GETCURSEL, wParam, lParam);

                CRect rcItem;
                SendMessage(hWnd, LB_GETITEMRECT, nIndex, (LONG)(VOID *)&rcItem);
                InvalidateRect(hWnd, rcItem, FALSE);

                // Invert the check mark
                CCheckComboBox::sComboBox_->SetCheck(nIndex, !CCheckComboBox::sComboBox_->GetCheck(nIndex));

                // Notify that selection has changed
                SendMessage(CCheckComboBox::sComboBox_->GetParent(), WM_COMMAND, MAKELONG(GetWindowLong(CCheckComboBox::sComboBox_->m_hWnd, GWL_ID), CBN_SELCHANGE), (LPARAM)(CCheckComboBox::sComboBox_->m_hWnd));
                return 0;
            }

            break;
        }        

    case WM_LBUTTONDOWN:
        {
            CRect rcClient;
            GetClientRect(hWnd, rcClient);

            CPoint pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);


            if (PtInRect(rcClient, pt)) 
            {
                int nItemHeight = SendMessage(hWnd, LB_GETITEMHEIGHT, 0, 0);
                int nTopIndex   = SendMessage(hWnd, LB_GETTOPINDEX, 0, 0);

                // Compute which index to check/uncheck
                int nIndex = nTopIndex + pt.y / nItemHeight;

                CRect rcItem;
                SendMessage(hWnd, LB_GETITEMRECT, nIndex, (LONG)(VOID *)&rcItem);

                if (PtInRect(rcItem, pt)) 
                {
                    // Invalidate this window
                    InvalidateRect(hWnd, rcItem, FALSE);
                    CCheckComboBox::sComboBox_->SetCheck(nIndex, !CCheckComboBox::sComboBox_->GetCheck(nIndex));

                    // Notify that selection has changed
                    SendMessage(CCheckComboBox::sComboBox_->GetParent(), WM_COMMAND, MAKELONG(GetWindowLong(CCheckComboBox::sComboBox_->m_hWnd, GWL_ID), CBN_SELCHANGE), (LPARAM)(CCheckComboBox::sComboBox_->m_hWnd));                                        
                }
            }

            // Do the default handling now (such as close the popup
            // window when clicked outside)
            break;
        }

    case WM_LBUTTONUP: 
        {
            // Don't do anything here. This causes the combobox popup
            // windows to remain open after a selection has been made
            return 0;
        }
    }

    return CallWindowProc(CCheckComboBox::sWndProc_, hWnd, nMsg, wParam, lParam);
}

#endif // !defined(AFX_CHECKCOMBOBOX_H__181012A7_43A3_48DE_8C1E_F8D91E503439__INCLUDED_)