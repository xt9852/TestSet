// ADODB.h: INTerface for the CADODB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ADODB_H__)
#define _ADODB_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#import "C:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "EndOfFile")
#import "C:\Program Files\Common Files\System\ADO\msadox.dll" 

//#include <afxtempl.h>

class CADOParameters;

class CADODB
{
	// Operation
public:
	// This two function just set com state for the thread
	// you can CALL the Function in your self style;
	static void InitDB(void);
	static void UninitDB(void);

	HRESULT OpenExcelDB(LPCTSTR strFileName);
	HRESULT OpenOralceDB(LPCTSTR strServer, LPCTSTR strPort, LPCTSTR strDatabase, LPCTSTR strUser, LPCTSTR strPwd);
	
	HRESULT OpenAccessDB(LPCTSTR strFileName, LPCTSTR strPWD = NULL) /*throw(_com_error &)*/;
	HRESULT OpenSQLServerDB(LPCTSTR strServer, LPCTSTR strDatabase,	LPCTSTR strUser, LPCTSTR strPwd) /*throw(_com_error &)*/;
	void CloseDB(void) /*throw(_com_error &)*/;

	_RecordsetPtr ExecuteStoredPoc(LPCTSTR strStroredProc, ...) /*throw(_com_error &)*/;
	_RecordsetPtr ExecuteSQL(LPCTSTR strSQL,  _Parameter **pParams,
		const INT iParamsCount, VARIANT *pEffect = NULL) /*throw(_com_error &)*/;
	_RecordsetPtr ExecuteSQL(LPCTSTR strSQL, CADOParameters &params,
		VARIANT *pEffect = NULL) /*throw(_com_error &)*/;

	_RecordsetPtr ExecuteSQL(LPCTSTR strSQL, VARIANT *pEffect = NULL) /*throw(_com_error &)*/;

	HRESULT CreateAccessDB(LPCTSTR strFileName, LPCTSTR strPwd = NULL);
	HRESULT ChangeAccessPassword(LPCTSTR strFileName, LPCTSTR strNewPassword, LPCTSTR strOldPassword);

    CString GetDataStr(_RecordsetPtr pRecordset);

	// Constructor & Destructor
public:
	CADODB();
	virtual ~CADODB();

	// Protected data
protected:
	_ConnectionPtr  m_pConnection;
//	_CommandPtr		m_pCommand;
	_bstr_t m_bstrCnn;

private:
	void PeekVar(_Parameter *param, va_list varlist) /*throw(_com_error &)*/;
};

typedef CArray<_Parameter *, _Parameter *> ParametersArray;

class CADOParameters : public ParametersArray
{
public:
	~CADOParameters(void);

	// Basic add
	INT Add(_Parameter* pParam);

	// Add map
	virtual INT Add(const VARIANT &vValue);
	virtual INT Add(Field *pField);

	// overload adding
	INT Add(BYTE byValue);
	INT Add(SHORT sValue);
	INT Add(INT iValue);
	INT Add(bool bValue);
	INT Add(LPCSTR strValue);
	INT Add(LPCWSTR bstrValue);
	INT Add(FLOAT fValue);
	INT Add(DOUBLE dbValue);
	INT Add(const __time64_t &time);
	INT Add(const COleDateTime &datetime);
	INT Add(const BYTE *pBytes, INT iLen);
	INT Add(const CByteArray &arrBytes);
	INT Add(const CURRENCY &curValue);

	void RemoveAll();
};

inline _variant_t GetSafeField(_RecordsetPtr &rs, LPCTSTR strFieldName)
{
	// Be sure must not be VT_NULL
	_variant_t varRet(rs->GetCollect(strFieldName));
	if (VT_NULL == varRet.vt)
		varRet.Clear();

	ASSERT(varRet.vt != VT_DATE);
	return varRet;
}

inline _variant_t GetSafeField(_RecordsetPtr &rs, LONG lIndex)
{
	// Be sure must not be VT_NULL
	_variant_t varRet(rs->GetCollect((LONG)lIndex));
	if (VT_NULL == varRet.vt)
		varRet.Clear();

	ASSERT(varRet.vt != VT_DATE);
	return varRet;
}

inline __time64_t GetTimeField(_RecordsetPtr &rs, LPCTSTR strFieldName)
{
	// Get safe VARIANT type
	_variant_t varTmp(rs->GetCollect(strFieldName));
	if (VT_NULL == varTmp.vt)
		varTmp.Clear();

	// Use SYSTEMTIME manual change time to _time64_t
	//COleDateTime timeTmp(varTmp);
	SYSTEMTIME st;
	::VariantTimeToSystemTime(varTmp, &st);
	CTime timeRet(st);

	return timeRet.GetTime();
}

// Return copied lens
inline DWORD GetSmallBinaryField(_RecordsetPtr &rs, LPCTSTR strFieldName,
								 BYTE *pBuffer, DWORD dwLen)
{
	// Get safe VARIANT type
	FieldPtr fld = rs->Fields->Item[strFieldName];
	if (fld->Value.vt != (VT_ARRAY | VT_UI1))
		return 0;

	ADO_LONGPTR iMinLen = min((LONG)dwLen, fld->ActualSize);

	for (LONG l = 0; l < iMinLen; l++)
		SafeArrayGetElement(fld->Value.parray, &l, &pBuffer[l]);

	return (DWORD)iMinLen;
}

// Return copied lens
inline DWORD GetSmallBinaryField(_RecordsetPtr &rs, LPCTSTR strFieldName,
								 CByteArray &arrBuffer)
{
	// Get safe VARIANT type
	FieldPtr fld = rs->Fields->Item[strFieldName];
	if (fld->Value.vt != (VT_ARRAY | VT_UI1))
		return 0;

	ADO_LONGPTR iMinLen = fld->ActualSize;

	arrBuffer.SetSize(iMinLen);
	for (LONG l = 0; l < iMinLen; l++)
		SafeArrayGetElement(fld->Value.parray, &l, &arrBuffer[l]);

	return (DWORD)iMinLen;
}

#endif // !defined(_ADODB_H__)
