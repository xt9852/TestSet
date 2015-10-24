// ADODB.cpp: implementation of the CADODB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Ado.h"
//#include <Afx.h>
//#include <atlbase.h>
//#include <atlcomtime.h >
#include "ADODB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CADODB::CADODB()
{

}

CADODB::~CADODB()
{
	try
	{
		CloseDB();
	}
	catch (...)
	{
		// ignore
	}
}

//static
void CADODB::InitDB(void)
{
	if (FAILED(CoInitialize(NULL)))
		ASSERT(FALSE);
}

//static
void CADODB::UninitDB(void)
{
	CoUninitialize();
}


// 不能直接打开带有密码的Excel,但可手动打开Excel再用Ado去操作
HRESULT CADODB::OpenExcelDB(LPCTSTR strFileName)
{
	CString strcnn;
	strcnn.Format(_T("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=%s; Extended Properties = \"Excel 8.0;HDR=Yes;IMEX=1\""), strFileName);
	m_bstrCnn = strcnn;

	HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
		_com_issue_error(hr);
	m_pConnection->CursorLocation = adUseClient;

	return m_pConnection->Open(m_bstrCnn, "", "", adConnectUnspecified);
}

HRESULT CADODB::OpenOralceDB(LPCTSTR strServer, LPCTSTR strPort, LPCTSTR strDatabase, LPCTSTR strUser, LPCTSTR strPwd)
{
	LPCTSTR ORALCEDBCNNTEMPLATE = _T("Provider=MSDAORA.1;Password=%s;User ID=%s;")
		_T("Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=%s)(PORT=%s))(CONNECT_DATA=%s;")
		_T("Persist Security Info=True");

	CString strcnn;
	strcnn.Format(ORALCEDBCNNTEMPLATE,strPwd, strUser, strServer, strPort, strDatabase);

	m_bstrCnn = strcnn;

	HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
		_com_issue_error(hr);
	m_pConnection->CursorLocation = adUseClient;

	return m_pConnection->Open(m_bstrCnn, "", "", adConnectUnspecified);

}

HRESULT CADODB::OpenAccessDB(LPCTSTR strFileName,
							 LPCTSTR strPWD /* = NULL */) /*throw(_com_error &)*/
{
	if (NULL == strPWD)
		strPWD = _T("");

	// ODBC Driver
	//LPCTSTR ACCESSDBCNNTEMPLATE = _T("DBQ=%s;PWD=%s;DRIVER={Microsoft Access Driver (*.mdb)};");

	// Jet OLEDB (recommend)
	LPCTSTR ACCESSDBCNNTEMPLATE = _T("Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=%s;")
		_T("Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";")
		_T("Jet OLEDB:Registry Path=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=0;")
		_T("Jet OLEDB:Database Password=%s;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;")
		_T("Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;")
		_T("Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False");
	CString strcnn;
	strcnn.Format(ACCESSDBCNNTEMPLATE, strFileName, strPWD);
	m_bstrCnn = strcnn;

	HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
		_com_issue_error(hr);
	m_pConnection->CursorLocation = adUseClient;

	return m_pConnection->Open(m_bstrCnn, "", "", adConnectUnspecified);
}

HRESULT CADODB::OpenSQLServerDB(LPCTSTR strServer, LPCTSTR strDatabase,
								LPCTSTR strUser,
								LPCTSTR strPwd) /*throw(_com_error &)*/
{
	if (NULL == strPwd)
		strPwd = _T("");

	LPCTSTR CNNTMP = _T("Provider=SQLOLEDB.1;Persist Security Info=False;")
		_T("Initial Catalog=%s;Data Source=%s;Use Procedure for Prepare=1;")
		_T("Auto Translate=True;Packet Size=4096;Use Encryption for Data=False;")
		_T("Tag with column collation when possible=False");
	CString strCnn;
	strCnn.Format(CNNTMP, strDatabase, strServer);
	m_bstrCnn = strCnn;
	strCnn.Empty();

	HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
		_com_issue_error(hr);
	m_pConnection->CursorLocation = adUseClient;

	return m_pConnection->Open(m_bstrCnn, strUser, strPwd, adConnectUnspecified);;
}

void CADODB::CloseDB() /*throw(_com_error &)*/
{
	// if Connection created
	if (m_pConnection != NULL)
	{
		// if Connection is opened
		if (adStateOpen == m_pConnection->State)
			m_pConnection->Close();

		// Release ptr
		m_pConnection.Release();

		m_bstrCnn = _T("");
	}
}

_RecordsetPtr CADODB::ExecuteStoredPoc(LPCTSTR strStroredProc,
									   ...) /*throw(_com_error &)*/
{
	_CommandPtr pCommand;
	HRESULT hr = pCommand.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
		_com_issue_error(hr);

	// Setting for the command
	pCommand->ActiveConnection = m_pConnection;
	pCommand->CommandText = strStroredProc;
	pCommand->CommandType = adCmdStoredProc;

	// Analyze SQL
	pCommand->Parameters->Refresh();
	va_list var;
	va_start(var, strStroredProc);
	for (long l=0; l<pCommand->Parameters->Count; l++)
	{
		_ParameterPtr pParamItem = pCommand->Parameters->GetItem(l);
		PeekVar(pParamItem, var);
	}
	va_end(var);

	return pCommand->Execute(NULL, NULL, adCmdStoredProc);
}

_RecordsetPtr CADODB::ExecuteSQL(LPCTSTR strSQL,
								 _Parameter **pParams,
								 const INT iParamsCount,
								 VARIANT *pEffect /* = NULL */)  /*throw(_com_error &)*/
{
	_CommandPtr pCommand;
	HRESULT hr = pCommand.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
		_com_issue_error(hr);

	// Setting for the command
	pCommand->ActiveConnection = m_pConnection;
	pCommand->CommandText = strSQL;
	pCommand->CommandType = adCmdText;

	// Analyze SQL
	for (INT i=0; i<iParamsCount; i++)
		pCommand->Parameters->Append(pParams[i]);

	return pCommand->Execute(pEffect, NULL, adCmdText);
}

_RecordsetPtr CADODB::ExecuteSQL(LPCTSTR strSQL,
								 VARIANT *pEffect /* = NULL */)
{
	_CommandPtr pCommand;
	HRESULT hr = pCommand.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
		_com_issue_error(hr);


	// Setting for the command
	pCommand->ActiveConnection = m_pConnection;
	pCommand->CommandText = strSQL;
	pCommand->CommandType = adCmdText;

	return pCommand->Execute(pEffect, NULL, adCmdText);
}

_RecordsetPtr CADODB::ExecuteSQL(LPCTSTR strSQL,
								 CADOParameters &params,
								 VARIANT *pEffect /* = NULL */)  /*throw(_com_error &)*/
{
	_CommandPtr pCommand;
	HRESULT hr = pCommand.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
		_com_issue_error(hr);

	// Setting for the command
	pCommand->ActiveConnection = m_pConnection;
	pCommand->CommandText = strSQL;
	pCommand->CommandType = adCmdText;

	// Analyze SQL
	for (INT i=0; i<params.GetSize(); i++)
	{
		pCommand->Parameters->Append(params[i]);
	};

	return pCommand->Execute(pEffect, NULL, adCmdText);
}

void CADODB::PeekVar(_Parameter *param, va_list varlist)  /*throw(_com_error &)*/
{
	switch (param->GetType())
	{
	case adChar:
	case adVarChar:
		param->Value = va_arg(varlist, LPCTSTR);
		break;
	case adBSTR:
	case adVarWChar:
		param->Value = va_arg(varlist, BSTR);
		break;

	case adInteger:
		param->Value = (long)va_arg(varlist, INT);
		break;
	case adSmallInt:
		param->Value = va_arg(varlist, short);
		break;
	case adTinyInt:
		param->Value = va_arg(varlist, BYTE);
		break;

	case adBoolean:
		param->Value = va_arg(varlist, bool);
		break;

	case adSingle:
		param->Value = va_arg(varlist, float);
		break;
	case adDouble:
		param->Value = va_arg(varlist, double);
		break;

	case adDate:
		{
			COleDateTime dtNow(va_arg(varlist, __time64_t));
			param->Value = (DATE)dtNow;
		}
		break;

	case adCurrency:
		param->Value = va_arg(varlist, CURRENCY);
		break;

	default:
		ASSERT(FALSE);
		break;
	}

	return;
}

HRESULT CADODB::CreateAccessDB( LPCTSTR strFileName, LPCTSTR strPwd /*= NULL*/ )
{
	if (NULL == strPwd)
		strPwd = _T("");

	HRESULT hr;

	LPCTSTR ACCESSDBCNNTEMPLATE = _T("Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=%s;")
		_T("Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";")
		_T("Jet OLEDB:Registry Path=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=0;")
		_T("Jet OLEDB:Database Password=%s;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;")
		_T("Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;")
		_T("Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False");

	CString strCnnString;
	strCnnString.Format(ACCESSDBCNNTEMPLATE, strFileName, strPwd);

	ADOX::_CatalogPtr pCatalog;
	hr = pCatalog.CreateInstance(__uuidof(ADOX::Catalog));
	if (FAILED(hr))
		_com_issue_error(hr);

	pCatalog->Create(_bstr_t(strCnnString));

	pCatalog.Release();
	
	return S_OK;
	
}

HRESULT CADODB::ChangeAccessPassword(LPCTSTR strFileName,
									 LPCTSTR strNewPassword,
									 LPCTSTR strOldPassword)
{
	_ConnectionPtr cnn;
	HRESULT hr = cnn.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
		_com_issue_error(hr);

	CString strOldPasswordCpy;
	CString strNewPasswordCpy;

	// Safe parameter
	if (strNewPassword)
		strNewPasswordCpy = strNewPassword;
	if (strOldPassword)
		strOldPasswordCpy = strOldPassword;
	if (strNewPasswordCpy.IsEmpty())
		strNewPasswordCpy = _T("NULL");
	if (strOldPasswordCpy.IsEmpty())
		strOldPasswordCpy = _T("NULL");

	cnn->Provider = _T("Microsoft.Jet.OLEDB.4.0"); 
	cnn->Mode = adModeShareExclusive;
	cnn->Properties->Item["Data Source"]->Value = _bstr_t(strFileName);
	cnn->Properties->Item["Jet OLEDB:Database Password"]->Value = _bstr_t(strOldPassword);
	cnn->Open(_T(""), _T(""), _T(""), adConnectUnspecified);

	CString strAlterSQL;
	strAlterSQL.Format(_T("ALTER DATABASE PASSWORD %s %s"), strNewPasswordCpy, strOldPasswordCpy);
	// Can't use parameter
	cnn->Execute(_bstr_t(strAlterSQL), NULL, adOptionUnspecified);

	cnn->Close();
	cnn.Release();

	return S_OK;
}

CString CADODB::GetDataStr(_RecordsetPtr pRecordset)
{
    if (NULL == pRecordset) return _T("");

    CString strData;
    int nFieldsCount = pRecordset->Fields->GetCount(); // 字段数;
    for (int i = 0; i < nFieldsCount; i++)
    {
        char *pszName = _com_util::ConvertBSTRToString(pRecordset->Fields->GetItem((long)i)->GetName()); // 字段名

        strData += pszName;
        strData += _T("\t");

        delete[] pszName;
    }

    strData += _T("\n");

    while (!pRecordset->EndOfFile)  //遍历所有记录
    {
        for (int i = 0; i < nFieldsCount; i++)
        {
            strData += pRecordset->GetCollect((long)i);
            strData += _T("\t");
        }
        strData += _T("\n");

        pRecordset->MoveNext();
    }

    return strData;
}

// Add _Parameter*
INT CADOParameters::Add(_Parameter* pParam)
{
	pParam->AddRef();

	return (INT)CArray<_Parameter*, _Parameter*>::Add(pParam);
}

//----------------------------------------------------------------------
// Name: CADOParameters::Add(const VARIANT &vValue)
// Desc: Add Variant to parameters, any one can override this function
//		 to build owner db and data type map! like SQL SERVER text and
//		 ntext data format can be BSTR and STR, etc.
//----------------------------------------------------------------------
INT CADOParameters::Add(const VARIANT &vValue)
{
	_ParameterPtr pParam;

	// Create Parameter
	HRESULT hr = pParam.CreateInstance(__uuidof(Parameter));
	if (FAILED(hr))
		 _com_issue_error(hr);

	// Set param for the value;
	pParam->Direction = adParamInput;

	// parse the type and size
	switch (vValue.vt)
	{
		// I1-I8
	case VT_UI1:
	case VT_I1:
		pParam->Type = adTinyInt;
		pParam->Size = 1;
		break;
	case VT_UI2:
	case VT_I2:
		pParam->Type = adSmallInt;
		pParam->Size = 2;
		break;
	case VT_UI4:
	case VT_I4:
	case VT_INT:
	case VT_UINT:
		pParam->Type = adInteger;
		pParam->Size = 4;
		break;
	case VT_UI8:
	case VT_I8:
		pParam->Type = adBigInt;
		pParam->Size = 8;
		break;

		// BSTR
	case VT_BSTR:
		pParam->Type = adVarWChar;
		{
			pParam->Size = (ADO_LONGPTR)wcslen(vValue.bstrVal);
		}

		if (pParam->Size == 0)
			pParam->Size = -1;
		break;

		// STR
	case  VT_LPSTR:
	case VT_BYREF|VT_I1:
		pParam->Type = adVarChar;
		pParam->Size = (ADO_LONGPTR)strlen(vValue.pcVal);
		//if (pParam->Size == 0)
			pParam->Size = -1;
		break;

		// Boolean
	case VT_BOOL:
		pParam->Type = adBoolean;
		pParam->Size = 2;
		break;

		// Date time
	case VT_DATE:
		pParam->Type = adDate;
		pParam->Size = 8;
		break;

		// Real
	case VT_R4:
		pParam->Type = adSingle;
		pParam->Size = 4;
		break;
	case VT_R8:
		pParam->Type = adDouble;
		pParam->Size = 8;
		break;

	case VT_CY:
		pParam->Type = adCurrency;
		pParam->Size = 8;
		break;

	case VT_DECIMAL:
		pParam->Type = adDecimal;
		pParam->Size = 4;
		pParam->NumericScale = 10;
		pParam->Precision = 28;
		ASSERT(FALSE);
		break;

	case VT_NULL:
		pParam->Type = adEmpty;
		pParam->Size = 0;
		ASSERT(FALSE);
		break;

	default:
		ASSERT(FALSE);
		break;
	}

	// Put the value
	pParam->put_Value(vValue);

	return Add((_Parameter*)pParam);
}

// Add C++ type
INT CADOParameters::Add(BYTE byValue)
{
	return Add(_variant_t(byValue));
}
INT CADOParameters::Add(SHORT sValue)
{
	return Add(_variant_t(sValue));
}
INT CADOParameters::Add(INT iValue)
{
	return Add(_variant_t((long)iValue));
}
INT CADOParameters::Add(bool bValue)
{
	return Add(_variant_t(bValue));
}
INT CADOParameters::Add(LPCSTR strValue)
{
	return Add(_variant_t(strValue));
}
INT CADOParameters::Add(LPCWSTR bstrValue)
{
	return Add(_variant_t(bstrValue));
}
INT CADOParameters::Add(FLOAT fValue)
{
	return Add(_variant_t(fValue));
}
INT CADOParameters::Add(DOUBLE dbValue)
{
	return Add(_variant_t(dbValue));
}
INT CADOParameters::Add(const __time64_t &time)
{
	// The database value use DATE(double) format so we
	// must transform time64 format to DATE by COleDateTime
	// and also we support such a override Add function whose
	// parameter is COleDateTime!
	COleDateTime datetime(time);
	return Add(datetime);
}
INT CADOParameters::Add(const COleDateTime &datetime)
{
	return Add(_variant_t((DATE)datetime, VT_DATE));
}
INT CADOParameters::Add(const BYTE *pBytes, INT iLen)
{
	_ParameterPtr pParam;

	// Create Parameter
	HRESULT hr = pParam.CreateInstance(__uuidof(Parameter));
	if (FAILED(hr))
		_com_issue_error(hr);

	// Set param for the value;
	pParam->Direction = adParamInput;

	pParam->Type = adBinary;
	pParam->Size = iLen;
	_variant_t var;
	SAFEARRAY *psa = NULL;
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0L;
	rgsabound[0].cElements = iLen;
	psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
	if (NULL == psa)
		_com_issue_error(E_OUTOFMEMORY);
	for (LONG l=0; l<iLen; l++)
		SafeArrayPutElement(psa, &l, (LPVOID)&pBytes[l]);
	var.vt = VT_ARRAY|VT_UI1;
	var.parray = psa;

	pParam->AppendChunk(var);

	return Add((_Parameter*)pParam);
}
INT CADOParameters::Add(const CByteArray &arrBytes)
{
	return Add((arrBytes.GetData()), (INT)arrBytes.GetSize());
}

INT CADOParameters::Add(const CURRENCY &curValue)
{
	return Add(_variant_t(curValue));
}

INT CADOParameters::Add(Field *pField)
{
	_ParameterPtr pParam;

	// Create Parameter
	HRESULT hr = pParam.CreateInstance(__uuidof(Parameter));
	if (FAILED(hr))
		_com_issue_error(hr);

	// Set param for the value;
	pParam->Direction = adParamInput;

	// parse the type and size
	pParam->Size = pField->DefinedSize;
	pParam->Type = pField->Type;
	pParam->NumericScale = pField->NumericScale;
	pParam->Precision = pField->Precision;

	// Put the value
	pParam->put_Value(pField->Value);

	return Add((_Parameter*)pParam);
}
void CADOParameters::RemoveAll()
{
	for (INT i=0; i<m_nSize; i++)
	{
		GetAt(i)->Release();
	}

	CArray<_Parameter*, _Parameter*>::RemoveAll();
}

CADOParameters::~CADOParameters(void)
{
	RemoveAll();
}