
#pragma once

#include "resource.h"
#include "Finger.h"


class CDlg_Finger : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Finger)

public:
    CDlg_Finger(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_Finger();

    enum { IDD = IDD_0_FINGER };

private:
    FEATURE feature_[2];        // 指纹特征数据
    FingerIdentify finger_;     // 指纹识别

    CStatic bmp1_;
    CStatic bmp2_;

    HBITMAP hImage1_;
    HBITMAP hImage2_;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedFingerBtnBmp1();
    afx_msg void OnBnClickedFingerBtnBmp2();
    afx_msg void OnBnClickedFingerBtnComp();
};
