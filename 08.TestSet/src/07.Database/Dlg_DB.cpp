// Dlg_DB.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_DB.h"


IMPLEMENT_DYNAMIC(CDlg_DB, CDialog)
CDlg_DB::CDlg_DB(CWnd* pParent /*=NULL*/)
: CDialog(CDlg_DB::IDD, pParent)
{
}

CDlg_DB::~CDlg_DB()
{
}

void CDlg_DB::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_DB_COMBO_TYPE, m_comboType);
}


BEGIN_MESSAGE_MAP(CDlg_DB, CDialog)
    ON_BN_CLICKED(IDC_DB_BTN_CONN_DB,  OnBnClickedBtnConnDb)
    ON_BN_CLICKED(IDC_DB_BTN_EXEC_SQL, OnBnClickedBtnExecSql)
    ON_BN_CLICKED(IDC_DB_BTN_SQLITE,   OnBnClickedBtnSqlite)
END_MESSAGE_MAP()


BOOL CDlg_DB::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_comboType.SetCurSel(5);

    m_adoDB.InitDB();

    return TRUE;
}

void CDlg_DB::OnBnClickedBtnConnDb()
{
    CString strDbType, strHost,strPort,strDbName,strUserName,strPassword;

    GetDlgItem(IDC_DB_IPADDRESS)->GetWindowText(strHost);
    GetDlgItem(IDC_DB_EDIT_PORT)->GetWindowText(strPort);
    GetDlgItem(IDC_DB_EDIT_DB_NAME)->GetWindowText(strDbName);
    GetDlgItem(IDC_DB_EDIT_USER_NAME)->GetWindowText(strUserName);
    GetDlgItem(IDC_DB_EDIT_USER_PASSWORD)->GetWindowText(strPassword);	

    m_comboType.GetLBText(m_comboType.GetCurSel(), strDbType);

    HRESULT hRet = S_OK;
    INT nRet = 0;

    if (0 == strDbType.CompareNoCase("Access"))
    {
        hRet = m_adoDB.OpenAccessDB(strDbName, strPassword);
    }
    else if (0 == strDbType.CompareNoCase("Excel")) // select * from [Sheet1$A1:B10] //指定范围A1~B10
    {
        hRet = m_adoDB.OpenExcelDB(strDbName);
    }
    else if (0 == strDbType.CompareNoCase("Oralce"))
    {
        hRet = m_adoDB.OpenOralceDB(strHost, strPort, strDbName, strUserName, strPassword);
    }
    else if (0 == strDbType.CompareNoCase("SQLServer"))
    {
        hRet = m_adoDB.OpenSQLServerDB(strHost/* + _T(":") + strPort*/, strDbName, strUserName, strPassword);
    }
    else if (0 == strDbType.CompareNoCase("MySQL"))
    {
        nRet = m_mysqlDB.OpenDB(strHost, atoi((LPCSTR)(LPCTSTR)strPort), strDbName, strUserName, strPassword);
    }
    else if (0 == strDbType.CompareNoCase("SQLite"))
    {
        m_sqliteDB.open(strDbName);
    }

    if (0 == nRet || SUCCEEDED(hRet))
    {
        GetDlgItem(IDC_DB_BTN_CONN_DB)->EnableWindow(FALSE);
    }
    else
    {
        MessageBox("db connection error");
    }
}

void CDlg_DB::OnBnClickedBtnExecSql()
{
    CString strSQL, strDbType;

    GetDlgItem(IDC_DB_EDIT_SQL)->GetWindowText(strSQL);
    m_comboType.GetLBText(m_comboType.GetCurSel(), strDbType);
    try
    {
        if (0 == strDbType.CompareNoCase("MySQL"))
        {
            m_mysqlDB.Exec(strSQL);
            std::string data = m_mysqlDB.GetDataStr();
            MessageBox(data.c_str());
        }
        else if (0 == strDbType.CompareNoCase("SQLite"))
        {
            m_sqliteDB.execDML(strSQL);
        }
        else
        {
            _RecordsetPtr pRecordset = m_adoDB.ExecuteSQL(strSQL);
            CString strData = m_adoDB.GetDataStr(pRecordset);
            this->MessageBox(strData);
        }
    }
    catch (...)
    {
        TRACE("ExecuteSQL error:%d %s\n", ::GetLastError(), strSQL);
    }
}

void CDlg_DB::OnBnClickedBtnSqlite()
{
    try
    {
        int i, fld;
        time_t tmStart, tmEnd;
        const char* szFile = "test.db";
        CppSQLite3DB db;

        TRACE("%s\n", db.SQLiteVersion());

        remove(szFile);
        db.open(szFile);

        TRACE("Creating emp table\n");

        db.execDML("create table emp(empno int, empname char(20));");

        ////////////////////////////////////////////////////////////////////////////////
        // Execute some DML, and print number of rows affected by each one
        ////////////////////////////////////////////////////////////////////////////////

        TRACE("DML tests-----------------------------\n");

        int nRows = db.execDML("insert into emp values (7, 'David Beckham');");
        TRACE(" table emp rows %d inserted\n", nRows);

        nRows = db.execDML("update emp set empname = 'Christiano Ronaldo' where empno = 7;");
        TRACE(" table emp rows %d updated\n", nRows);

        nRows = db.execDML("delete from emp where empno = 7;");
        TRACE(" table emp rows %d deleted\n", nRows);

        ////////////////////////////////////////////////////////////////////////////////
        // Transaction Demo
        // The transaction could just as easily have been rolled back
        ////////////////////////////////////////////////////////////////////////////////
        int nRowsToCreate(50000);

        TRACE("Transaction test-----------------------------\n");
        TRACE(" to insert rows %d please wait...\n", nRowsToCreate);
        tmStart = time(0);
        db.execDML(" begin transaction;");

        for (i = 0; i < nRowsToCreate; i++)
        {
            char buf[128];
            sprintf(buf, "insert into emp values (%d, 'Empname_%06d');", i, i);
            db.execDML(buf);
        }

        db.execDML(" commit transaction;");
        tmEnd = time(0);

        ////////////////////////////////////////////////////////////////////////////////
        // Demonstrate CppSQLite3DB::execScalar()
        ////////////////////////////////////////////////////////////////////////////////
        TRACE(" now rows %d\n", db.execScalar("select count(*) from emp;"));
        TRACE(" time %d seconds (that was fast!)\n", tmEnd-tmStart);

        ////////////////////////////////////////////////////////////////////////////////
        // Re-create emp table with auto-increment field
        ////////////////////////////////////////////////////////////////////////////////
        TRACE("Auto increment test-----------------------------\n");
        db.execDML("drop table emp;");
        db.execDML("create table emp(empno integer primary key, empname char(20));");
        TRACE(" rows %d deleted\n", nRows);

        for (i = 0; i < 5; i++)
        {
            char buf[128];
            sprintf(buf, "insert into emp (empname) values ('Empname_%06d');", i+1);
            db.execDML(buf);
            TRACE(" primary key: %d\n", db.lastRowId());
        }

        ////////////////////////////////////////////////////////////////////////////////
        // Query data and also show results of inserts into auto-increment field
        ////////////////////////////////////////////////////////////////////////////////
        TRACE("Select statement test-----------------------------\n");
        CppSQLite3Query q = db.execQuery("select * from emp order by 1;");

        for (fld = 0; fld < q.numFields(); fld++)
        {
            TRACE("%s(%s)|", q.fieldName(fld), q.fieldDeclType(fld));
        }

        TRACE("\n");

        while (!q.eof())
        {
            TRACE(q.fieldValue(0));
            TRACE("|");
            TRACE(q.fieldValue(1));
            TRACE("\n");
            q.nextRow();
        }

        ////////////////////////////////////////////////////////////////////////////////
        // SQLite's printf() functionality. Handles embedded quotes and NULLs
        ////////////////////////////////////////////////////////////////////////////////

        TRACE("SQLite sprintf test-----------------------------\n");
        CppSQLite3Buffer bufSQL;
        bufSQL.format("insert into emp (empname) values (%Q);", "He's bad");
        TRACE("%s\n", bufSQL);
        db.execDML(bufSQL);

        bufSQL.format("insert into emp (empname) values (%Q);", NULL);
        TRACE("%s\n", bufSQL);
        db.execDML(bufSQL);

        ////////////////////////////////////////////////////////////////////////////////
        // Fetch table at once, and also show how to use CppSQLite3Table::setRow() method
        ////////////////////////////////////////////////////////////////////////////////

        TRACE("getTable() test-----------------------------\n");
        CppSQLite3Table t = db.getTable("select * from emp order by 1;");

        for (fld = 0; fld < q.numFields(); fld++)
        {
            TRACE("%s(%s)|", q.fieldName(fld), q.fieldDeclType(fld));
        }

        TRACE("\n");

        for (int row = 0; row < t.numRows(); row++)
        {
            t.setRow(row);
            for (int fld = 0; fld < t.numFields(); fld++)
            {
                if (!t.fieldIsNull(fld))
                {
                    TRACE(t.fieldValue(fld));
                    TRACE("|");
                }
                else
                {
                    TRACE("NULL|");
                }
            }
            TRACE("\n");
        }

        ////////////////////////////////////////////////////////////////////////////////
        // Test CppSQLite3Binary by storing/retrieving some binary data, checking
        // it afterwards to make sure it is the same
        ////////////////////////////////////////////////////////////////////////////////

        TRACE("Binary data test-----------------------------\n");
        db.execDML("create table bindata(desc char(10), data blob);");

        unsigned char bin[256];
        CppSQLite3Binary blob;

        for (i = 0; i < sizeof bin; i++)
        {
            bin[i] = i;
        }

        blob.setBinary(bin, sizeof bin);

        bufSQL.format("insert into bindata values ('testing', %Q);", blob.getEncoded());
        db.execDML(bufSQL);
        TRACE(" Stored binary Length: %d\n", sizeof(bin));

        q = db.execQuery("select data from bindata where desc = 'testing';");

        if (!q.eof())
        {
            blob.setEncoded((unsigned char*)q.fieldValue("data"));
            TRACE(" Retrieved binary Length: %d\n", blob.getBinaryLength());
        }

        const unsigned char* pbin = blob.getBinary();
        for (i = 0; i < sizeof bin; i++)
        {
            if (pbin[i] != i)
            {
                TRACE(" Problem: i=%d, bin[i]=%d\n", i, pbin[i]);
            }
        }

        q.finalize();

        ////////////////////////////////////////////////////////////////////////////////
        // Pre-compiled Statements Demo
        ////////////////////////////////////////////////////////////////////////////////

        TRACE("Transaction test, creating-----------------------------\n");
        TRACE(" rows=%d to create please wait...\n", nRowsToCreate);

        db.execDML("drop table emp;");
        db.execDML("create table emp(empno int, empname char(20));");
        tmStart = time(0);
        db.execDML("begin transaction;");

        CppSQLite3Statement stmt = db.compileStatement("insert into emp values (?, ?);");
        for (i = 0; i < nRowsToCreate; i++)
        {
            char buf[16];
            sprintf(buf, "EmpName_%06d", i);
            stmt.bind(1, i);
            stmt.bind(2, buf);
            stmt.execDML();
            stmt.reset();
        }

        db.execDML("commit transaction;");
        tmEnd = time(0);

        TRACE(" %d rows in emp table in, %d seconds (that was even faster!)\nEnd of tests\n",
            db.execScalar("select count(*) from emp;"),
            tmEnd-tmStart);
    }
    catch (CppSQLite3Exception& e)
    {
        TRACE(e.errorMessage());
    }

    TRACE("Press enter to quit: ");
}
