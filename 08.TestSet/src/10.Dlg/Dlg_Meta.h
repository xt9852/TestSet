// Dlg_Meta.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "resource.h"

#include "rm\RmReader.h"
//#include "librmff.h"

enum
{
    RM_RMVB_FILE,
    WMV_ASF_FILE,
    AVI_FILE,
    MPEG_FILE
};
/*
typedef struct _tagRM_Header
{
	ULONG	lOffset;

	ULONG	lId;
	ULONG	lSize;
	USHORT	sVersion;

	// if( sVersion == 0 || sVersion == 1 )
	ULONG	lFormatVersion;
	ULONG	lNumHeaders;

}RM_HEADER;

typedef struct _tagRM_Prop
{
	ULONG	lOffset;

	ULONG	lId;
	ULONG	lSize;
	USHORT	sVersion;

	// if sVersion == 0
	USHORT	lMaxBitRate;
	USHORT	lAvgBitRate;
	USHORT	lMaxPacketSize;
	USHORT	lAvgPacketSize;
	USHORT	lNumPackets;
	USHORT	lDuration;
	USHORT	lPreroll;
	USHORT	lIndexOffset;
	USHORT	lDataOffset;
	USHORT	lNumStreams;
	USHORT	lFlags;

}RM_PROP;

// media data prop
typedef struct _tagRM_MDPR	
{
	ULONG	lOffset;

	ULONG	lId;
	ULONG	lSize;
	USHORT	sVersion;

	// if sVersion == 0
	USHORT	lMDPRId;			// 子序号
	ULONG	lMaxBitRate;
	ULONG	lAvgBitRate;
	ULONG	lMaxPacketSize;
	ULONG	lAvgPacketSize;
	ULONG	lStartTime;
	ULONG	lPreroll;
	ULONG	lDuration;

	ULONG	lStreamNameSize;
	char	*pszName;

	ULONG	lMimeTypeSize;
	char	*pszMimeType;

	ULONG	lTypeSpecificSize;
	unsigned char *pszTypeSpecificData;

}RM_MDPR;

typedef struct _tagRM_Cont
{
	ULONG	lOffset;

	ULONG	lId;
	ULONG	lSize;
	USHORT	sVersion;

	// if sVersion == 0
	ULONG	lTitleSize;
	char	*pszTitle;
	ULONG	LAuthorSize;
	char	*pszAuthor;
	ULONG	lCopyrightSize;
	char	*pszCopyright;
	ULONG	lCommentSize;
	char	*pszComment;

}RM_CONT;

typedef struct _tagRM_Packet
{
	ULONG	lOffset;

	USHORT	sVersion;

	// if sVersion == 0 || sVersion == 1

	USHORT	sLength;
	USHORT	sStreamNumber;
	ULONG	lTimestamp;

	// if sVersion == 0
	// UCHAR	cPacketGroup;
	// UCHAR	cFlags;

	// if sVersion == 1
	USHORT	sAsmRule;
	UCHAR	cAsmFlags;

	UCHAR	*pcData;

}RM_PACKET;

typedef struct _tagRM_Data
{
	ULONG	lOffset;

	ULONG	lId;
	ULONG	lSize;
	USHORT	sVersion;

	// if sVersion == 0
	ULONG	lNumPackets;			
	ULONG	lNextDataHeaderOffset;

	RM_PACKET *pRmPacket;

}RM_DATA;

typedef struct _tagRM_IndexRecord
{
	//ULONG	lOffset;

	USHORT	sVersion;

	// if sVersion == 0
	ULONG	lTimestamp;
	ULONG	lOffset;
	ULONG	lPacketCountForThisPacket;

}RM_INDEX_RECORD;

typedef struct _tagRM_Indx
{
	ULONG	lOffset;

	ULONG	lId;
	ULONG	lSize;
	USHORT	sVersion;

	// if sVersion == 0
	ULONG	lCountIndx;
	USHORT	sStreamNumber;	// RM_MDPR.lId
	ULONG	lNextIndexHeader;

	RM_INDEX_RECORD *pIndexRecord;

}RM_INDX;

typedef struct _tagRM_Info
{
	RM_HEADER	Header;

	RM_PROP		Prop;

	ULONG		lNumMdpr;
	RM_MDPR		*pMdpr;

	RM_CONT		Cont;

	ULONG		lDataNum;
	RM_DATA		*pData;

	ULONG		lNumIndx;
	RM_INDX		*pIndx;

}RM_INFO;

*/


// CRM_TestDlg 对话框
class CDlg_Meta : public CDialog
{
// 构造
public:
	CDlg_Meta(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DLG_META };
	
	int      m_nFileType;

	RmReader m_rmRead;
	bool	 m_bReady;

	//RM_INFO  RmInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持	

// 实现
protected:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	CButton m_RMRadioButton;
	CButton m_WMVRadioButton;
	CButton m_AVIRadioButton;
	CButton m_MPEGRadioButton;
	CButton m_FileRadioButton;
	CButton m_DirRadioButton;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CEdit m_FilePathEdit;
	CEdit m_InfoEdit;
	CString	m_sInfo;
	CString m_sFile;
	// -----------------------------------------------

	CListCtrl m_List;
	CTreeCtrl m_Tree;
	afx_msg void OnBnClickedButGetinfo();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
