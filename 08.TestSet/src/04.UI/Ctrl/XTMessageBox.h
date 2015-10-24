#pragma once
#include "resource.h"
#include "UI/Ctrl/XTDialog.h"
#include "UI/Ctrl/XTButton.h"
#include <string>

#define MB_CANCELTRYCONTINUE	0x00000006L
#define IDTRYAGAIN				10
#define IDCONTINUE				11


int XTMessageBox(LPCTSTR lpText, LPCTSTR lpCaption = NULL, UINT uType = 0);


class CMessageDlg : public CXTDialog
{
	DECLARE_DYNAMIC(CMessageDlg)

public:
	CMessageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMessageDlg();

// 对话框数据
	enum { IDD = IDD_DLG_MESSAGE };

	CFont		font_;
	HGDIOBJ		oldFont_;
	HBRUSH		color1_;
	HBRUSH		color2_;
	HBRUSH		fill1_;
	HBRUSH		fill2_;
	HDC			fileDc_;
	HBITMAP		fillBmp1_;
	HBITMAP		fillBmp2_;

	CXTButton	btnClose_;
	CXTButton	btn1_;
	CXTButton	btn2_;
	CXTButton	btn3_;

	std::string	text_;
	std::string	caption_;
	int			type_;
	int			return_;
	bool		icon_;

	void SetDlg(int btnNum, int ny1, int ny2, int ny3, 
		const char *btn1Name, const char *btn2Name, const char *btn3Name);

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();
	afx_msg void OnBnClickedBtn3();
};