#pragma once
#include "resource.h"
#include "DataStruct/B+Tree.h"

// CDlg_DataStruct 对话框

class CDlg_DataStruct : public CDialog
{
	DECLARE_DYNAMIC(CDlg_DataStruct)

public:
	CDlg_DataStruct(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_DataStruct();

// 对话框数据
	enum { IDD = IDD_DLG_DATASTRUCT };

	CBTree BTree;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedCode();
    afx_msg void OnBnClickedDatastructBtnCdma();
    afx_msg void OnBnClickedDatastructBtnBigMatch();
};
