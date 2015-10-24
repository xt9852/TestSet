// Dlg_Meta.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg_Meta.h"
#include <Shlobj.h>
#include <direct.h>
#include "rm\rmparser.h"
#include "rm\parser.h"
#include "wmv\asfparser.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int SelectFolder(HWND hParent, CString &strFolder)
{
	strFolder.Empty();

	LPMALLOC lpMalloc;

	if (::SHGetMalloc(&lpMalloc) != NOERROR) return 0;

	CString strDisplayName;
	CString strBuffer;
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = hParent;
	browseInfo.pidlRoot = NULL; // set root at Desktop
	browseInfo.pszDisplayName = (LPTSTR)(LPCTSTR)strDisplayName;
	browseInfo.lpszTitle = _T("Select a folder");
	browseInfo.ulFlags = BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;

	LPITEMIDLIST lpItemIDList;
	if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) != NULL)
	{
		// Get the path of the selected folder from the    item ID list.
		if (::SHGetPathFromIDList(lpItemIDList, (LPTSTR)(LPCTSTR)strBuffer))
		{
			// At this point, szBuffer contains the path the user chose.
			//if (szBuffer[0] == '\0') return 0;

			if (strBuffer.GetLength() == 0) return 0;

			// We have a path in szBuffer! Return it.
			strFolder = strBuffer;
			return 1;
		}
		else return 1; // strResult is empty

		lpMalloc->Free(lpItemIDList);
		lpMalloc->Release();
	}

	return 1;
}

BOOL GetFiles(CStringList& fileList, CString filePath, int nFileType)
{
	BOOL bRet = TRUE;
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch;
	BOOL fFinished = FALSE; 

	chdir(filePath);							// 设置当前目录
	hSearch = FindFirstFile(_T("*.*"), &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
	{
		bRet = FALSE;
	} 

	while (!fFinished && bRet) 
	{
		if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)	// 是文件
		{
			CString sFileName = FileData.cFileName;
			int nAt = sFileName.ReverseFind('.');
			if (nAt > 0)
			{
				CString sExtName = sFileName.Mid(nAt + 1);

                if (nFileType == RM_RMVB_FILE)
                {
                    if (sExtName.CompareNoCase(_T("rm") ) == 0 || sExtName.CompareNoCase(_T("rmvb") ) == 0)
                    {
                        CString sFile;
                        sFile.Format(_T("%s\\%s"),  filePath, FileData.cFileName);
                        fileList.AddTail(sFile);
                    }
                }
                else if (nFileType == WMV_ASF_FILE)
                {
                    if (sExtName.CompareNoCase(_T("wmv")) == 0 || sExtName.CompareNoCase(_T("asf")) == 0)
                    {
                        CString sFile;
                        sFile.Format(_T("%s\\%s"),  filePath, FileData.cFileName);
                        fileList.AddTail(sFile);
                    }
                }
                else if (nFileType == AVI_FILE)
                {
                    if (sExtName.CompareNoCase(_T("avi")) == 0)
                    {
                        CString sFile;
                        sFile.Format(_T("%s\\%s"),  filePath, FileData.cFileName);
                        fileList.AddTail(sFile);
                    }
                }
                else if (nFileType == MPEG_FILE)
                {
                    if (sExtName.CompareNoCase(_T("mpeg")) == 0)
                    {
                        CString sFile;
                        sFile.Format(_T("%s\\%s"),  filePath, FileData.cFileName);
                        fileList.AddTail(sFile);
                    }
                }
			}		
		}
		else	// 是目录
		{
			CString sPath;
			sPath = FileData.cFileName;
			if ( sPath.CompareNoCase(_T(".")) && sPath.CompareNoCase(_T("..")))
			{
				sPath.Empty();
				sPath.Format(_T("%s\\%s"),  filePath, FileData.cFileName);
				GetFiles(fileList, sPath, nFileType);		// 递归调用
			}
		}

		if (!FindNextFile(hSearch, &FileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
			{ 
				fFinished = TRUE; 
			} 
			else 
			{ 
				bRet = FALSE;
			} 
		}
	} 

	FindClose(hSearch);

	return bRet;
}

void MakeMeta(void* p)
{
	//CMetaMakerDlg* pDlg = (CMetaMakerDlg*)p;
	CDlg_Meta* pDlg = (CDlg_Meta*)p;

	int nTotal = 0;
	int nSuccess = 0;
	int nFail = 0;
	Parser* rp = NULL;
	pDlg->m_sInfo.Empty();
	pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
	((CButton*)pDlg->GetDlgItem(IDC_META_BTN_BROWSE))->EnableWindow(FALSE);
	((CButton*)pDlg->GetDlgItem(IDC_META_BTN_MAKE))->EnableWindow(FALSE);
	if (pDlg->m_FileRadioButton.GetCheck())
	{
		nTotal = 1;
		pDlg->m_sInfo.AppendFormat(_T("开始索引文件....文件个数:%d个\r\n"), nTotal);
		pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);

        if (pDlg->m_nFileType == RM_RMVB_FILE)
		    rp = (Parser*)new RmParser(pDlg->m_sFile);
        else if (pDlg->m_nFileType == WMV_ASF_FILE)
            rp = (Parser*)new AsfParser(pDlg->m_sFile);
        else
            rp = NULL;
        
        if (rp != NULL)
        {
            pDlg->m_sInfo.AppendFormat(_T("正在索引文件: %s "), pDlg->m_sFile);
            pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
            if (rp->Initial())
            {
                pDlg->m_sInfo.AppendFormat(_T("  成功！\r\n"));
                pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
                nSuccess++;
            }
            else
            {
                pDlg->m_sInfo.AppendFormat(_T("  失败！\r\n"));
                pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
                nFail++;
            }
            delete rp;
            rp = NULL;
            pDlg->m_sInfo.AppendFormat(_T("索引完成....成功:%d个，失败:%d个\r\n"), nSuccess, nFail);
            pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
        }
        else
        {
            pDlg->m_sInfo.AppendFormat(_T("索引失败!!\r\n"));
            pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
        }
	}
	else
	{
		CStringList	fileList;

		GetFiles(fileList, pDlg->m_sFile, pDlg->m_nFileType);

		nTotal = (int)fileList.GetCount();
		if (nTotal > 0)
		{
			pDlg->m_sInfo.AppendFormat(_T("开始索引文件....文件个数:%d个\r\n"), nTotal);
			pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
			for (POSITION pos = fileList.GetHeadPosition(); pos;)
			{
				CString sFile = fileList.GetNext(pos);
				pDlg->m_sInfo.AppendFormat(_T("正在索引文件: %s "), sFile);
				pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);

                if (pDlg->m_nFileType == RM_RMVB_FILE)
                    rp = (Parser*)new RmParser(sFile);
                else if (pDlg->m_nFileType == WMV_ASF_FILE)
                    rp = (Parser*)new AsfParser(sFile);
                else
                    rp = NULL;

                if (rp != NULL)
                {
                    if (rp->Initial())
                    {
                        pDlg->m_sInfo.AppendFormat(_T("   成功！\r\n"));
                        pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
                        nSuccess++;
                    }
                    else
                    {
                        pDlg->m_sInfo.AppendFormat(_T("   失败！\r\n"));
                        pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo);
                        nFail++;
                    }
                }
                else
                    nFail++;

				delete rp;
				rp = NULL;
			}
			pDlg->m_sInfo.AppendFormat(_T("索引完成....成功:%d个，失败:%d个\r\n"), nSuccess, nFail);
			pDlg->m_InfoEdit.SetWindowText(pDlg->m_sInfo );
		}
		else
		{
			pDlg->m_sInfo.AppendFormat(_T("没有找到符合格式的文件！\r\n"));
			pDlg->m_InfoEdit.SetWindowText( pDlg->m_sInfo );
		}
	}

	((CButton*)pDlg->GetDlgItem(IDC_META_BTN_BROWSE))->EnableWindow(TRUE);
	((CButton*)pDlg->GetDlgItem(IDC_META_BTN_MAKE))->EnableWindow(TRUE);
}


CDlg_Meta::CDlg_Meta(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Meta::IDD, pParent)
{
	m_bReady = false;
}

void CDlg_Meta::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_META_RADIO_RM, m_RMRadioButton);
	DDX_Control(pDX, IDC_META_RADIO_WMV, m_WMVRadioButton);
	DDX_Control(pDX, IDC_META_RADIO_AVI, m_AVIRadioButton);
	DDX_Control(pDX, IDC_META_RADIO_MPEG, m_MPEGRadioButton);
	DDX_Control(pDX, IDC_META_RADIO_FILE, m_FileRadioButton);
	DDX_Control(pDX, IDC_META_RADIO_DIR, m_DirRadioButton);
	DDX_Control(pDX, IDC_META_EDIT_FILE, m_FilePathEdit);
	DDX_Control(pDX, IDC_META_EDIT_INFO, m_InfoEdit);

	DDX_Control(pDX, IDC_META_TREE1, m_Tree);
	DDX_Control(pDX, IDC_META_LIST1, m_List);
}

BEGIN_MESSAGE_MAP(CDlg_Meta, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_META_BTN_MAKE, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_META_BTN_BROWSE, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_META_BUT_GETINFO, OnBnClickedButGetinfo)
	ON_NOTIFY(TVN_SELCHANGED, IDC_META_TREE1, OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// CRM_TestDlg 消息处理程序

BOOL CDlg_Meta::OnInitDialog()
{
	CDialog::OnInitDialog();

	//---------------------------------------------------------------
	// 暂时不支持这三种
	m_AVIRadioButton.EnableWindow(FALSE);
	m_MPEGRadioButton.EnableWindow(FALSE);

	m_RMRadioButton.SetCheck(BST_CHECKED);
	m_FileRadioButton.SetCheck(BST_CHECKED);

    m_nFileType = RM_RMVB_FILE;

	//---------------------------------------------------------------

	m_List.InsertColumn(0, _T("字段"), LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, _T("偏移"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, _T("值"),   LVCFMT_LEFT, 100);
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDlg_Meta::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CDlg_Meta::OnBnClickedButton2()
{
	_beginthread(&MakeMeta, 0, (void*)this);
}

void CDlg_Meta::OnBnClickedButton1()
{
	CString sFilter;
	if (m_RMRadioButton.GetCheck())
	{
		sFilter.Format(_T("Real Media Files (*.rm;*.rmvb)|*.rm;*.rmvb|"));
        m_nFileType = RM_RMVB_FILE;
	}
	else if (m_WMVRadioButton.GetCheck())
	{
		sFilter.Format(_T("WMV Files (*.wmv;*.asf)|*.wmv;*.asf|"));
        m_nFileType = WMV_ASF_FILE;
	}
	else if (m_AVIRadioButton.GetCheck())
	{
		sFilter.Format(_T("ASF Files (*.avi)|*.avi|"));
        m_nFileType = AVI_FILE;
	}
	else if (m_MPEGRadioButton.GetCheck())
	{
		sFilter.Format(_T("MPEG Files (*.mpeg)|*.mpeg|"));
        m_nFileType = MPEG_FILE;
	}

	if (m_FileRadioButton.GetCheck())
	{
		CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_ENABLESIZING, (LPCTSTR)sFilter, this);

		if (dlg.DoModal() != IDOK) return;

		m_FilePathEdit.SetWindowText(dlg.GetPathName());
		
		m_sFile.Empty();

		m_FilePathEdit.GetWindowText(m_sFile);
	}
	else
	{
		m_sFile.Empty();

		SelectFolder(this->m_hWnd, m_sFile);
		m_FilePathEdit.SetWindowText(m_sFile);
	}
}
void CDlg_Meta::OnBnClickedButGetinfo()
{	
	// if( m_rmRead.GetFileInfo(this))
	//	 m_bReady = true;


	//GetFileInfo((LPCSTR)m_sFile, &RmInfo);//m_rmRead.
}

void CDlg_Meta::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);	
	*pResult = 0;

	if (m_bReady)
	{
		switch(pNMTreeView->itemNew.lParam)
		{
		case 1:
			{
				m_List.DeleteAllItems();
				m_List.DeleteColumn(0);
				m_List.DeleteColumn(1);

				m_List.DeleteColumn(0);
				m_List.DeleteColumn(1);
				break;
			}
		case 10:break;
		case 11:break;
		default:
			break;
		}
	}
}
