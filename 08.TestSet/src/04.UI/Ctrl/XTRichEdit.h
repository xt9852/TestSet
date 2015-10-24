
#pragma once
#include <map>
#include <RichOle.h>


class _AFX_RICHEDITEX_STATE
{
public:
	_AFX_RICHEDITEX_STATE();
	virtual ~_AFX_RICHEDITEX_STATE();
	HINSTANCE m_hInstRichEdit20;
};


//------------------------------------------------------
// 由于OLE是单线程对象，不能直接在其它线程中调用，现在只能发消息
#ifdef _DEBUG
#import "..\Debug\ShowImageOle.dll" no_namespace
#else
#import "..\Release\ShowImageOle.dll" no_namespace
#endif


enum enTransFile
{
	TRANS_LINK_ACCEPT  = 0x01,
	TRANS_LINK_SAVEAS  = 0x02,
	TRANS_LINK_REFUSE  = 0x03,
	TRANS_PROCCESSBAR  = 0x04,
	TRANS_ERROR		   = 0x05,
};

enum enKeyAreaType
{
	KEY_TYPE_TEXT	   = 0x00,
	KEY_TYPE_LINK	   = 0x01,
	KEY_TYPE_GIF	   = 0x02,
	KEY_TYPE_IMAGE	   = 0x03,
	KEY_TYPE_TRANSFILE = 0x04,
};

struct KEY_AREA
{
	int					type;
	int					id;
	CHARRANGE			pos;
	LPVOID				data;
	CComPtr<IShowImage>	ctrl;
};

typedef std::map<int, KEY_AREA*> KEY_AREA_MAP;


// 在窗体调用前应先调用 AfxInitRichEdit(); 否则将不显示窗体
class CXTRichEdit : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CXTRichEdit)

public:
	CXTRichEdit();
	virtual ~CXTRichEdit();

protected:
	HWND					parentWnd_; //父窗体句柄
	CHARFORMAT2				charfmt_;	// 默认字符格式
	CComPtr<IRichEditOle>	richEditOle_;

public:
	/**
	 *\fn         Init()
	 *\brief      初使化。
	 */
	void Init();

	/**
	 *\fn         AddText(const char *text)
	 *\brief      添加文本。
	 *\param[in]  text  文本数据。
	 */
	void AddText(const char *text);

	/**
	 *\fn         AddText(const char *text, CHARFORMAT2 &format)
	 *\brief      添加格式文本。
	 *\param[in]  text  文本数据。
	 */
	void AddText(const char *text, CHARFORMAT2 &format);
	
	/**
	 *\fn         AddText(const char *text, COLORREF color, int weight)
	 *\brief      添加文本。
	 *\param[in]  text   文本数据。
	 *\param[in]  color  文本颜色。
	 *\param[in]  weight 文本字号。
	 */
	void AddText(const char *text, COLORREF color, int weight);

	/**
	 *\fn         AddLink(const char *text, COLORREF color, int weight)
	 *\brief      添加超连接文本。
	 *\param[in]  text   文本数据。
	 *\param[in]  data   附加数据。
	 */
	KEY_AREA* AddLink(const char *text, void *data);

	/**
	 *\fn         SetLink(int id, const char *text)
	 *\brief      添加超连接文本。
	 *\param[in]  id     按件ID。
	 *\param[in]  text   文本数据。
	 */
	KEY_AREA* SetLink(int id, const char *text);

	/**
	 *\fn         SetLink(KEY_AREA *key, const char *text)
	 *\brief      添加超连接文本。
	 *\param[in]  key    关键点。
	 *\param[in]  text   文本数据。
	 */
	KEY_AREA* SetLink(KEY_AREA *key, const char *text);

	/**
	 *\fn         AddImage(HBITMAP bitmap, void *data)
	 *\brief      添加图片关键点。
	 *\param[in]  bitmap    BITMAP句柄。
	 *\param[in]  data      附加数据。
	 *\return     键指针。
	 */
	KEY_AREA* AddImage(HBITMAP bitmap, void *data);

	/**
	 *\fn         AddImage(HBITMAP bitmap, void *data)
	 *\brief      添加图片关键点。
	 *\param[in]  filename  BITMAP文件路径名。
	 *\param[in]  data      附加数据。
	 *\return     键指针。
	 */
	KEY_AREA* AddImage(const char *filename, void *data);
	
	/**
	 *\fn         AddImage(const char *filename, CHARRANGE range, void *data)
	 *\brief      添加图片关键点。
	 *\param[in]  filename  BITMAP文件路径名。
	 *\param[in]  range     位置。
	 *\param[in]  data      附加数据。
	 *\return     键指针。
	 */
	KEY_AREA* AddImage(const char *filename, CHARRANGE range, void *data);

	/**
	 *\fn         SetImage(KEY_AREA *key, HBITMAP bitmap)
	 *\brief      设置图片关键点。
	 *\param[in]  key		关键点。
	 *\param[in]  bitmap    位图。
	 *\return     键指针。
	 */
	KEY_AREA* SetImage(KEY_AREA *key, HBITMAP bitmap);

	/**
	 *\fn         SetImage(KEY_AREA *key, HBITMAP bitmap)
	 *\brief      设置图片关键点。
	 *\param[in]  id		关键点ID。
	 *\param[in]  bitmap    位图。
	 *\return     键指针。
	 */
	KEY_AREA* SetImage(int id, HBITMAP bitmap);

	/**
	 *\fn         SetImage(KEY_AREA *key, const char *filename)
	 *\brief      设置图片关键点。
	 *\param[in]  key		关键点。
	 *\param[in]  filename  位图文件名。
	 *\return     键指针。
	 */
	KEY_AREA* SetImage(KEY_AREA *key, const char *filename);

	/**
	 *\fn         SetImage(int id, const char *filename)
	 *\brief      设置图片关键点。
	 *\param[in]  id		关键点ID。
	 *\param[in]  filename  位图文件名。
	 *\return     键指针。
	 */
	KEY_AREA* SetImage(int id, const char *filename);

	/**
	 *\fn         AddGif(const char *filename, void data)
	 *\brief      添加GIF文件。
	 *\param[in]  filename	文件名。
	 *\param[in]  data      附加数据。
	 *\return     键指针。
	 */
	KEY_AREA* AddGif(const char *filename, void *data);


	/**
	 *\fn         SetGif(KEY_AREA *key, const char *filename)
	 *\brief      设置GIF文件。
	 *\param[in]  key	    关键点。
	 *\param[in]  filename	文件名。
	 *\return     键指针。
	 */
	KEY_AREA* SetGif(KEY_AREA *key, const char *filename);

	/**
	 *\fn         SetGif(int id, const char *filename)
	 *\brief      设置GIF文件。
	 *\param[in]  id	    关键点ID。
	 *\param[in]  filename	文件名。
	 *\return     键指针。
	 */
	KEY_AREA* SetGif(int id, const char *filename);

	/**
	 *\fn         AddTransFile(const char *filename,
	 *\fn					  UINT64  fileLen,
	 *\fn        			  const char *iconFilename,
	 *\fn        			  const char *text,
	 *\fn        			  void* data)
	 *\brief      添加传输文件控件。
	 *\param[in]  filename		文件名。
	 *\param[in]  fileLen		文件长。
	 *\param[in]  iconFilename	图标文件名。
	 *\param[in]  text			文本信息。
	 *\param[in]  data			附加数据。
	 *\return     键指针。
	 */
	KEY_AREA * CXTRichEdit::AddTransFile(const char *filename,
		UINT64  fileLen,
		const char *iconFilename,
		const char *text,
		void* data);

	/**
	 *\fn         SetTransFile(KEY_AREA *key, const char *text, int state, UINT64 param)
	 *\brief      设置传输文件控件。
	 *\param[in]  key		关键点。
	 *\param[in]  text		文信息。
	 *\param[in]  state		状态。(0-显示文件名和文件大小,1-显示进度,2-显示文件传输完成和用时)
	 *\param[in]  param		参数。
	 */
	void SetTransFile(KEY_AREA *key, const char *text, int state, UINT64 param);

	/**
	 *\fn         GetCtrlInfo(LONG index, int &id, LONG &pos)
	 *\brief      得到控件信息。
	 *\param[in]  index		序号。
	 *\param[out] id		控件ID。
	 *\param[out] pos		控件位置。
	 *\return     是否成功。
	 */
	bool GetCtrlInfo(LONG index, int &id, LONG &pos);
	
	/**
	 *\fn         getCtrlCount()
	 *\brief      得到ole对象数。
	 *\return     返回ole对象数。
	 */
	LONG getCtrlCount() { richEditOle_->GetObjectCount(); }
	
protected:
    KEY_AREA_MAP keyMap_;

	/**
	 *\fn         MakeID()
	 *\brief      生成一个唯一的ID。
	 *\return     唯一的ID。
	 */
	DWORD MakeID();

	/**
	 *\fn         getKey(int id)
	 *\brief      得到键指针。
	 *\return     键指针。
	 */
	KEY_AREA* getKey(int id);

	/**
	 *\fn         getKey(CHARRANGE range)
	 *\brief      得到键指针。
	 *\param[in]  range    字符位置。
	 *\return     键指针。
	 */
	KEY_AREA* getKey(CHARRANGE range);

	/**
	 *\fn         DeleteKey(KEY_AREA* key)
	 *\brief      删除键。
	 *\param[in]  key    键指针。
	 */
	void DeleteKey(KEY_AREA* key);

	/**
	 *\fn         DeleteAll()
	 *\brief      删除键节点。
	 */
	void DeleteAll();

	/**
	 *\fn         KeyOffset(KEY_AREA *key, int offset)
	 *\brief      设置关键点位置。
	 *\param[in]  key    键指针。
	 *\param[in]  offset 偏移。
	 */
	void KeyOffset(KEY_AREA *key, int offset);

	/**
	 *\fn         InsertImage(const char *fileame, int id)
	 *\brief      添加图片。
	 *\param[in]  fileame	文件名。
	 *\param[in]  id		ID。
	 *\return     是否成功,0成功其它失败
	 */
	int InsertImage(const char *fileame, int id);

	/**
	 *\fn         InsertImage(HANDLE image, int id)
	 *\brief      添加图片。
	 *\param[in]  image		文件句柄。
	 *\param[in]  id		ID。
	 *\return     是否成功,0成功其它失败
	 */
	int InsertImage(HANDLE image, int id);

	/**
	 *\fn         InsertGif(KEY_AREA *key, const char *filename)
	 *\brief      添加GIF图片。
	 *\param[in]  key		关键点。
	 *\param[in]  image		文件句柄。
	 *\return     是否成功,0成功其它失败
	 */
	int InsertGif(KEY_AREA *key, const char *filename);

	/**
	 *\fn         InsertTransFileCtrl(KEY_AREA *key, 
	 *\fn					  const char *filename,
	 *\fn					  UINT64  fileLen,
	 *\fn					  const char *iconFilename,
	 *\fn					  const char *text)
	 *\brief      添加传输文件控件。
	 *\param[in]  key			关键点。
	 *\param[in]  filename		文件名。
	 *\param[in]  fileLen		文件长。
	 *\param[in]  iconFilename	图标文件名。
	 *\param[in]  text			文本信息。
	 *\return     是否成功。
	 */
	int CXTRichEdit::InsertTransFileCtrl(KEY_AREA *key, 
		const char *filename,
		UINT64  fileLen,
		const char *iconFilename,
		const char *text);

	/**
	 *\fn         LoadOleCtrl(int id)
	 *\brief      添加控件。
	 *\param[in]  id		关键点ID。
	 *\param[in]  showImage	控件指针。
	 *\return     是否成功。
	 */
	bool LoadOleCtrl(int id, IShowImage **showImage);

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnMsgfilter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnLink(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnDropfiles(NMHDR *pNMHDR, LRESULT *pResult);
};