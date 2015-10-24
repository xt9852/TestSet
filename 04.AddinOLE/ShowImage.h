// ShowImage.h : CShowImage 的声明
#pragma once
#include "resource.h"       // 主符号
#include <atlctl.h>
#include "AddinOLE.h"
#include "_IAddinOLEEvents_CP.h"
#include <atlstr.h>
#include <map>
#include "04.UI/GIF.h"
#include "04.UI/Ctrl/XTDC.h"


class CShowImage;

typedef std::map<UINT, CShowImage*> THISMAP;    // 索引为时间ID

THISMAP g_mapThis;                              // 指向全部控件

void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime); // 由于不是窗体没有时间消息,只能用这个方法


// 由于OLE是单线程对象，不能直接在其它线程中调用，现在只能发消息

// CShowImage
class ATL_NO_VTABLE CShowImage : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IShowImage, &IID_IShowImage, &LIBID_AddinOLELib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CShowImage>,
	public IOleControlImpl<CShowImage>,
	public IOleObjectImpl<CShowImage>,
	public IOleInPlaceActiveObjectImpl<CShowImage>,
	public IViewObjectExImpl<CShowImage>,
	public IOleInPlaceObjectWindowlessImpl<CShowImage>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CShowImage>,
	public CProxy_IShowImageEvents<CShowImage>, 
	public IPersistStorageImpl<CShowImage>,
	public ISpecifyPropertyPagesImpl<CShowImage>,
	public IQuickActivateImpl<CShowImage>,
	public IDataObjectImpl<CShowImage>,
	public IProvideClassInfo2Impl<&CLSID_ShowImage, &__uuidof(_IShowImageEvents), &LIBID_AddinOLELib>,
	public CComCoClass<CShowImage, &CLSID_ShowImage>,
	public CComControl<CShowImage>
{
public:

	CShowImage()
		:dc_(NULL),
		compDC_(NULL),
		imageDC_(NULL),
		type_(0),
		icon_(NULL),
		font_(NULL),
		font1_(NULL),
		fileLen_(0),
		progress_(-1),
        lastTime_(0),
        startTime_(0),
		drawIcon_(false),
		update_(false),
		frameCount_(0),
		curFrame_(0),
		timerId_(0),
		delayTime_(NULL)		
	{
		memset(&wndSize_, 0, sizeof(wndSize_));

		dc_ = xtDC_.Init(NULL, m_hWnd);
		compDC_ = xtDC_.AddCompDC();
		imageDC_ = xtDC_.AddBmpDC(0, IDB_BMP_PROGRESS);

		//-----------------------------------------------------------------------------------------
		LOGFONT lf = {0};													// 字符的结构		
		::GetObject(::GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);	// 获取当前系统的字体.
		lf.lfWeight = FW_NORMAL;			
		_tcscpy(lf.lfFaceName, "新宋体");									// 设置为宋体.

        lf.lfHeight = 12;
        lf.lfWidth = 6;
		font_ = ::CreateFont(lf.lfHeight, lf.lfWidth,						// 显示文件信息字体
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight, 
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, 
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, 
			lf.lfPitchAndFamily, lf.lfFaceName);		

		lf.lfHeight = 12;
		lf.lfWidth = 5;
		font1_ = ::CreateFont(lf.lfHeight, lf.lfWidth,						// 进度条字体
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight, 
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, 
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, 
			lf.lfPitchAndFamily, lf.lfFaceName);

		//-----------------------------------------------------------------------------------------

		brush_ = ::CreateSolidBrush(RGB(255,255,255));
	}

	~CShowImage()
	{
		if (NULL != dc_)      ::ReleaseDC(m_hWnd, dc_);
		if (NULL != compDC_)  ::DeleteDC(compDC_);
		if (NULL != imageDC_) ::DeleteDC(imageDC_);
		if (NULL != font_)    ::DeleteObject(font_);
		if (NULL != font1_)   ::DeleteObject(font1_);
		if (NULL != brush_)   ::DeleteObject(brush_);
	}

	//------------------------------------------------------------
	HDC			dc_;		// 窗体DC
	HDC			compDC_;	// 兼容DC
	HDC			imageDC_;	// 图片DC

	CXTDC		xtDC_;		// 双缓冲区DC
	
	SIZE		wndSize_;	// 窗体大小

	int			type_;		// 是显示图片还是传输文件

	enum { TRANSFILE = 1, SHOWIMAGE };

	/**
	 *\fn         DrawCtrl(HDC dc, RECT& rc)
	 *\brief      显示控件。
	 */
	void DrawCtrl(HDC dc, RECT& rc);

	/**
	 *\fn         GetContainerWindow()
	 *\brief      得到子空体。
	 *\return     窗体句柄。
	 */
	HWND GetContainerWindow();

	//------------------------------------------------------------

	HICON		icon_;
	HFONT		font_;
	HFONT		font1_;
	HBRUSH		brush_;

	std::string	message_;
	
	UINT64		fileLen_;   // 文件长度
	UINT64		progress_;  // 进度
    DWORD       lastTime_;  // 时间
    DWORD       startTime_; // 开始时间
	bool		drawIcon_;	// 是否显示图标
	bool		update_;	// 是否更新

	enum{TRANS_STATE_BEGIN, TRANS_STATE_TANSING, TRANS_STATE_END};

	/**
	 *\fn         DrawTransFileIcon()
	 *\brief      显示传输图标。
	 */
	void DrawTransFileIcon();

	/**
	 *\fn         DrawProgress()
	 *\brief      显示进度条。
	 */
	void DrawProgress();

	//------------------------------------------------------------
	CGIF		gif_;		// GIF文件

	WORD		frameCount_;// 帧数
	WORD		curFrame_;	// 当前显示的帧ID
	UINT		timerId_;	// 记时器
	WORD		*delayTime_;// 延时

	/**
	 *\fn         AddTimer(CShowImage* pthis, UINT elapse)
	 *\brief      添加时钟记时器。
	 *\param[in]  pthis   指向CShowImage。
	 *\param[in]  elapse  时间间隔。
	 */
	static void AddTimer(CShowImage* pthis, UINT elapse)
	{
		if (NULL == pthis) return;

		if (pthis->timerId_ != 0) ::KillTimer(pthis->m_hWnd, pthis->timerId_);

		pthis->timerId_ = ::SetTimer(pthis->m_hWnd, 1, elapse, TimerProc);

		g_mapThis[pthis->timerId_] = pthis;
	}

	/**
	 *\fn         DelTimer(HWND wnd, UINT timerId)
	 *\brief      删除时钟记时器。
	 *\param[in]  wnd     窗体句柄。
	 *\param[in]  timerId 时钟ID。
	 */
	static void DelTimer(HWND wnd, UINT timerId)
	{
		::KillTimer(wnd, timerId);
		g_mapThis.erase(timerId);
	}

	/**
	 *\fn         GetThis(UINT m_nTimerId)
	 *\brief      得到CShowImage类的this指针。
	 *\param[in]  nTimerId 时钟ID。
	 *\return     CShowImage类的this指针。
	 */
	static CShowImage* GetThis(UINT timerId)
	{
		THISMAP::iterator iter = g_mapThis.find(timerId);
		if (g_mapThis.end() != iter)
		{
			return (*iter).second;
		}
		return NULL;
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_SHOWIMAGE)

BEGIN_COM_MAP(CShowImage)
	COM_INTERFACE_ENTRY(IShowImage)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CShowImage)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// 示例项
	// PROP_ENTRY("Property Description", showid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CShowImage)
	CONNECTION_POINT_ENTRY(__uuidof(_IShowImageEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CShowImage)
	CHAIN_MSG_MAP(CComControl<CShowImage>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// 处理程序原型: 
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IShowImage,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)


public:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;

		// 将剪辑区域设置为 di.prcBounds 指定的矩形
		HRGN hRgnOld = NULL;

		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1) hRgnOld = NULL;

		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);	

		if (hRgnNew != NULL) bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);

		DrawCtrl(di.hdcDraw, rc);

		if (NULL != hRgnOld) ::DeleteObject(hRgnOld);

		if (NULL != hRgnNew) ::DeleteObject(hRgnNew);

		return S_OK;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{
	}

public:
	STDMETHOD(LoadFileTrans)(BSTR filename, UINT64 fileLen, BSTR iconFilename);
	STDMETHOD(SetFileTrans)(BSTR msg, DWORD state, UINT64 param);
	STDMETHOD(LoadGif)(BSTR filename);
	LRESULT OnTimer();
};

OBJECT_ENTRY_AUTO(__uuidof(ShowImage), CShowImage)
