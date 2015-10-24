
#pragma once

class CComPrint
{

public:
	CComPrint();
	~CComPrint();

private:
	HANDLE			m_hCom;
	DCB				m_dcb;
	COMMTIMEOUTS	m_CommTimeouts;
	BOOL			m_bPortReady;	
	BOOL			m_bWriteRC;
	BOOL			m_bReadRC;
	DWORD			m_dwBytesWritten;
	DWORD			m_dwBytesRead;
	CString			m_sComPort;

public:
	int  OpenCOM(int nCmdNum);
	void CloseCOM();

	void Print(CString csText);
	void WinPrint(CString csText);
	void PrintBmp(UINT nBmpId);
};


