/********************************************************************
File Name:  SCreenCluterDlg.h
Desc:   	Full screen culter h file.
*********************************************************************/
#pragma once

#include "resource.h"
#include <atlimage.h>


class CSCreenCluterDlg : public CDialog
{
    DECLARE_DYNAMIC(CSCreenCluterDlg)

public:
    CSCreenCluterDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CSCreenCluterDlg();

    // 对话框数据
    enum { IDD = IDD_DLG_SCREEN_CLUTER };

    virtual BOOL OnInitDialog();

    CImage m_imgResult;

protected:
    DWORD m_dwWidth;
    DWORD m_dwHeight;

    CDC *m_pDCScr;
    ATL::CImage m_imgScr;

    CPoint m_ptStart;
    CPoint m_ptEnd;

    CPoint m_ptHintPosition;
    CString m_strHintString;

    DWORD m_dwStage;
    enum enuStage
    {
        NOT_SEL,
        SEL_START,
        SEL_END,
    };

    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void PreInitDialog();

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
    virtual void OnOK();
};
