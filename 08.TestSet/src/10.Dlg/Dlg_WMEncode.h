
#pragma once
#include "wmv\WMEncode.h"
#include "resource.h"


class CDlg_WMEncode : public CDialog
{
    DECLARE_DYNAMIC(CDlg_WMEncode)

public:
    CDlg_WMEncode(CWnd* pParent = NULL);
    virtual ~CDlg_WMEncode();

    enum { IDD = IDD_DLG_WMENCODE };

    CEdit			m_edAudioFile;
    CEdit			m_edVideoFile;
    CComboBox		m_cbbAudioDev;
    CComboBox		m_cbbVideoDev;
    CComboBox		m_cbbProfile;

    CWMEncode		m_WMEncode;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBtnCaptureParam();
    afx_msg void OnBtnStartCapture();
    afx_msg void OnBtnSaveProfile();	
};
