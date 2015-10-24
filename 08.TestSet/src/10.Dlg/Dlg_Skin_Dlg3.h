#pragma once

#include "UI/Ctrl/XTDC.h"
#include "UI/Ctrl/XTButton.h"
#include "UI/Ctrl/XTRichEdit.h"
#include "UI/Ctrl/XTComboBox.h"
#include "UI/Ctrl/XTListCtrl.h"

#include <MMSYSTEM.h>
#pragma comment(lib, "WINMM.lib")

// CDlg_Skin_Dlg3 对话框

class CDlg_Skin_Dlg3 : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Skin_Dlg3)

public:
    CDlg_Skin_Dlg3(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_Skin_Dlg3();

    // 对话框数据
    enum { IDD = IDD_DLG_UI_GA };

private:
    HDC				m_hDC;
    HDC				m_hCompDC;
    HDC				m_hBmpDC;
    CXTDC			m_xtDC;

    CXTButton		m_btnMin;
    CXTButton		m_btnClose;
    CXTButton		m_btnSet;
    CXTButton		m_btnHelp;	
    CXTButton		m_btnCamera[3];
    CXTButton		m_btnVidicon[3];
    CXTButton		m_btnCameraBig;
    CXTButton		m_btnVidiconBig;
    CXTButton		m_btnStart;
    CXTButton		m_btnSend;	
    CXTButton		m_btnSendSecret;

    CXTRichEdit		m_reInput;
    CXTRichEdit		m_reInputSecret;
    CXTComboBox		m_cbMessage;
    CXTComboBox		m_cbSecretMessage;
    CXTListCtrl		m_lstUser;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPaint();

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedClose();
    afx_msg void OnBnClickedSet();
};
