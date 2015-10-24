#pragma once

#include "UI\Shape.h"
// CDlg_Shape 对话框

class CDlg_Shape : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Shape)

public:
    CDlg_Shape(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_Shape();

    // 对话框数据
    enum { IDD = IDD_DLG_SHAPE };

private:
    CShape	m_Shape;
	int		m_nDlgHeight;
    CWnd    *m_pDesktopWnd;
    CDC     *m_pDeskTopDC;

    static unsigned __stdcall WorkThread(LPVOID pParam);
    void Line(CDC *pdc, int x1, int y1, int x2, int y2);

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButShape();
    afx_msg void OnBnClickedButFace();
	afx_msg void OnBnClickedButLine();
    afx_msg void OnBnClickedButScaleBmp();
	afx_msg void OnBnClickedBut3d();
    afx_msg void OnBnClickedButTree();
};
