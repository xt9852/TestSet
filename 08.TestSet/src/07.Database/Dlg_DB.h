
#pragma once
#include "resource.h"
#include "ADODB.h"
#include "MySQLDB.h"
#include "CppSQLite3.h"



class CDlg_DB : public CDialog
{
    DECLARE_DYNAMIC(CDlg_DB)

public:
    CDlg_DB(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_DB();

    enum { IDD = IDD_DLG_5_DB };

private:
    CADODB          m_adoDB;
    CMySQLDB        m_mysqlDB;
    CppSQLite3DB    m_sqliteDB;

    CComboBox       m_comboType;

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedBtnConnDb();
    afx_msg void OnBnClickedBtnExecSql();
    afx_msg void OnBnClickedBtnSqlite();
};
