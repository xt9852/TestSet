//+-------------------------------------------------------------------------
//
//  dulib - DirectUI Library
//  Copyright (C) BodSoft
//
//  File:       dulib.h
//
//--------------------------------------------------------------------------
#ifndef __DIRECTUI_LIB__
#define __DIRECTUI_LIB__

#include <Windows.h>
#include <tchar.h>
#include <oaidl.h>

#define DULIB_API __declspec(dllimport)

class duWindowManager;
class duResManager;
class duPlugin;
class duResBase;
class duStyleBase;
class duStyleGroup;
//////////////////////////////////////////////////////////////////////////
// ScrollBarAction 
enum ScrollBarAction
{
	SCROLL_NO_WHERE = 0,
	SCROLL_UP = 1,
	SCROLL_DOWN = 2,
	SCROLL_TRACK = 3,
	SCROLL_PAGEUP = 4,
	SCROLL_PAGEDOWN = 5,
	SCROLL_WHEEL_UP = 6,
	SCROLL_WHEEL_DOWN = 7
};

//////////////////////////////////////////////////////////////////////////
// control state
#define DU_STATE_NORMAL			    0x0001
#define DU_STATE_OVER				0x0002
#define DU_STATE_PRESS			    0x0004
#define DU_STATE_FOCUS			    0x0008
#define DU_STATE_DISABLE			0x0010
#define DU_STATE_NORMAL_ALL		    0x001F
#define DU_STATE_CHECKED			0x0100
#define DU_STATE_CHECKEDOVER		0x0400
#define DU_STATE_CHECKEDPRESS		0x0800
#define DU_STATE_CHECKEDFOCUS		0x1000
#define DU_STATE_CHECKEDDISABLE	    0x2000
#define DU_STATE_CHECKED_ALL		0x3D00
#define DU_STATE_ALL				0x3D1F

#define IS_STATE_CHECKED(x)			((x) & 0x0000FF00)

//////////////////////////////////////////////////////////////////////////
// style type
#define STYLE_UNKNOWN			0
#define STYLE_IMAGE				1
#define STYLE_TEXT				2
#define STYLE_RECT				3

//////////////////////////////////////////////////////////////////////////
// resource type
#define DU_RES_UNKNOWN			 0
#define DU_RES_IMAGE			 1
#define DU_RES_FONT				 2
#define DU_RES_CURSOR			 3
#define DU_RES_RGN				 4
#define DU_RES_STYLEGROUP		 5

//////////////////////////////////////////////////////////////////////////
// notify message
#define DUM_RESIZE					0x0001
#define DUM_SHOWCONTROL				0x0002
#define DUM_MOUSEIN					0x0003
#define DUM_MOUSELEAVE				0x0004
#define DUM_MOUSELDOWN				0x0005
#define DUM_MOUSELUP				0x0006
#define DUM_MOUSERDOWN				0x0007
#define DUM_MOUSERUP				0x0008
#define DUM_MOUSEHOVER				0x0009
#define DUM_MOUSEDBCLICK			0x000A
#define DUM_KILLFOCUS				0x000B
#define DUM_SETFOCUS				0x000C
#define DUM_BTNCLICK    			0x000D
#define DUM_BTNDBCLICK				0x000E

#define DUM_CKCLICK					0x000F
#define DUM_COMBOSELCHANGE			0x0010
#define DUM_IMPEXPAND				0x0011
#define DUM_LBSELCHANGED			0x0012
#define DUM_LBHOVER					0x0013
#define DUM_LBRBUTTONDOWN			0x0014
#define DUM_LBLBUTTONDBCLICK		0x0015
#define DUM_LBEXSELCHANGED			0x0016
#define DUM_LBEXDBCLICK				0x0017
#define DUM_LBEXHOVER				0x0018
#define DUM_LBEXCONTENTMENU			0x0019
#define DUM_MENUPOPUP				0x001A
#define DUM_RADIOCLICK				0x001B
#define DUM_VSCROLL					0x001C
#define DUM_HSCROLL					0x001D
#define DUM_TBBSELECTED				0x001E
#define DUM_SLIDERCHANGED			0x0020
#define DUM_LKCLICK					0x0021
#define DUM_GIFCLICK				0x0022
#define DUM_SPINCHANGE				0x0023
#define DUM_SPLITTERMOVED			0x0024
#define DUM_SCROLLCONTAINTERSIZE	0x0025
#define DUM_EDITCHANGE				0x0026
#define DUM_XMLSTATICHREFCLICK	    0x0027
#define DUM_TREEITEMCLICK           0x0028
#define DUM_TREEITEMDBCLICK         0x0029
#define DUM_TREEITEMRBUTTONCLICK    0x002A
#define DUM_TREEITEMHOVER			0x002B
#define DUM_PAGECHANGED				0x002C
#define DUM_HEADERSORT				0x002D
#define DUM_HEADERCKCLICK			0x002E
#define DUM_TREELISTITEMCHECKED		0x002F
#define DUM_MENUITEMINIT			0x0030
#define DUM_MENUCLICK				0x0031
#define DUM_MENUSIZE				0x0032
#define DUM_MENUINIT				0x0033
#define DUM_LISTBOXEXUPDOWN			0x0034

#define WM_DIRECTUI_NOTIFY WM_USER + 0x188

//////////////////////////////////////////////////////////////////////////
// notify message struct
typedef struct duNotify
{
	UINT    uMsg;
	WPARAM  wParam;
	LPARAM  lParam;
}duNotify;

//////////////////////////////////////////////////////////////////////////
// Message Map
template<class T>
struct _du_MESSAGE_MAP
{
	typedef LRESULT (T::*TMFP)(duPlugin *pPlugin, WPARAM wParam, LPARAM lParam);

	const TCHAR *szName;
	UINT uMsg;
	TMFP func;
};

#define duBEGIN_MESSAGE_MAP(dispClass, __wParam, __lParam) \
	typedef dispClass _du_disp_classype; \
	duPlugin *__pPlugin = (duPlugin *)__wParam; \
	duNotify *__pNotify = (duNotify *)__lParam; \
	static _du_MESSAGE_MAP<_du_disp_classype> __du_message_map[] = \
{ \

#define duON_MESSAGE(name, msg, func) \
{ _T(#name), msg, (LRESULT (_du_disp_classype::*)(duPlugin *pPlugin, WPARAM, LPARAM))func}, \

#define duEND_MESSAGE_MAP() \
{ NULL, NULL, NULL } \
}; \
	LRESULT lResult = 0; \
	_du_MESSAGE_MAP<_du_disp_classype> *pMessageMap = __du_message_map; \
	while ( pMessageMap->szName ) { \
		if ( (MatchString(pMessageMap->szName, __pPlugin->GetName())) && (pMessageMap->uMsg == __pNotify->uMsg) )  { \
			lResult = (this->*pMessageMap->func)(__pPlugin, __pNotify->wParam, __pNotify->lParam); \
			return lResult; \
		} \
		pMessageMap++; \
	} \
	return lResult; \

//////////////////////////////////////////////////////////////////////////
// duObject interface
class duObject : public IDispatch
{
public:
	virtual void WINAPI FinalRelease();
	virtual LPCTSTR WINAPI GetTypeInfoName();
};

//////////////////////////////////////////////////////////////////////////
// duWindowManager interface
class duWindowManager : public duObject
{
public:
	virtual BOOL WINAPI Attach(HWND hWnd, LPCTSTR lpWindowName);
	virtual LPCTSTR WINAPI GetSkinPath();
	virtual duResManager *WINAPI GetResManager();
	virtual duPlugin *WINAPI CreateControl(LPCTSTR lpszType, LPCTSTR lpszName, duPlugin *pParent);
	virtual BOOL WINAPI ExecScript(LPCTSTR lpszFuncName, int nParamCount, VARIANT *pParams);
	virtual int WINAPI GetWindowCount();
	virtual HWND WINAPI GetWindowAt(int nIndex);
	virtual PBYTE WINAPI GetResource(LPCTSTR lpszResName, HANDLE &hMem, IStream *&pStream);
	virtual void WINAPI ReleaseResource(HANDLE hMem, IStream *pStream);
	virtual void WINAPI OutputDebugString(LPCTSTR lpszOutput);
	virtual BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow);
	virtual BOOL WINAPI DestroyWindow(HWND hWnd);
	virtual void WINAPI PostQuitMessage(int nExitCode);
	virtual BOOL WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
	virtual int WINAPI GetRed(int color);
	virtual int WINAPI GetGreen(int color);
	virtual int WINAPI GetBlue(int color);
	virtual BOOL WINAPI ChangeSkin(LPCTSTR lpszFile);
	virtual void WINAPI Redraw(duPlugin *pPlugin);
};

//////////////////////////////////////////////////////////////////////////
// duResManager interface
class duResManager : public duObject
{
public:
	virtual BOOL WINAPI AddResObj(duResBase *pNewRes);
	virtual BOOL WINAPI DeleteResObj(LPCTSTR lpszResName, UINT uResType);
	virtual duResBase *WINAPI GetResObj(LPCTSTR lpszResName, UINT uResType);
	virtual duResBase *WINAPI CreateResObj(LPCTSTR lpszResName, UINT uResType);
	virtual duStyleBase *WINAPI CreateStyle(UINT uStyleType);
	virtual int WINAPI GetResObjCount(UINT uResType);
	virtual duResBase *WINAPI GetResObjByIndex(int iIndex, UINT uResType);
	virtual BOOL WINAPI ResRename(LPCTSTR lpszResName, UINT uResType, LPCTSTR lpszResNewName);
	virtual BOOL WINAPI EraseResObjFromMap(LPCTSTR lpszResName, UINT uResType);
	virtual duStyleBase *WINAPI CloneChildStyle(duStyleBase *pStyleBase);
	virtual duStyleGroup *WINAPI CloneStyle(duStyleGroup *pStyleGroup, LPCTSTR lpszResName);
	
};

//////////////////////////////////////////////////////////////////////////
// duResBase interface
class duResBase : public duObject
{
public:
	virtual LPCTSTR WINAPI GetName();
	virtual void WINAPI SetName(LPCTSTR lpszName);
	virtual UINT WINAPI GetType();
	virtual BOOL WINAPI OnCreate(void *pElement); // internal,reserved
};

//////////////////////////////////////////////////////////////////////////
// duStyleBase interface
class duStyleBase : public duObject
{
public:
	virtual int WINAPI GetType();
	virtual void WINAPI Draw(HDC hDC, LPRECT lpDstRect, LPCTSTR lpszText, int nAlpha);
	virtual BOOL WINAPI OnCreate(void *pElement);
	
	virtual int WINAPI GetLeft();
	virtual void WINAPI SetLeft(int nLeft);
	virtual int WINAPI GetTop();
	virtual void WINAPI SetTop(int nTop);
	virtual int WINAPI GetRight();
	virtual void WINAPI SetRight(int nRight);
	virtual int WINAPI GetBottom();
	virtual void WINAPI SetBottom(int nBottom);
	virtual int WINAPI GetWidth();
	virtual void WINAPI SetWidth(int nWidth);
	virtual int WINAPI GetHeight();
	virtual void WINAPI SetHeight(int nHeight);
	virtual UINT WINAPI GetState();
	virtual void WINAPI SetState(UINT uState);
};

//////////////////////////////////////////////////////////////////////////
// duImageStyle interface
class duImageStyle : public duStyleBase
{
public:
	virtual UINT WINAPI GetLeftPart();
	virtual void WINAPI SetLeftPart(UINT uLeftPart);
	virtual UINT WINAPI GetTopPart();
	virtual void WINAPI SetTopPart(UINT uTopPart);
	virtual UINT WINAPI GetRightPart();
	virtual void WINAPI SetRightPart(UINT uRightPart);
	virtual UINT WINAPI GetBottomPart();
	virtual void WINAPI SetBottomPart(UINT uBottomPart);

	virtual UINT WINAPI GetSelectLeft();
	virtual void WINAPI SetSelectLeft(UINT uSelectLeft);
	virtual UINT WINAPI GetSelectTop();
	virtual void WINAPI SetSelectTop(UINT uSelectTop);
	virtual UINT WINAPI GetSelectWidth();
	virtual void WINAPI SetSelectWidth(UINT uSelectWidth);
	virtual UINT WINAPI GetSelectHeight();
	virtual void WINAPI SetSelectHeight(UINT uSelectHeight);
	
	virtual LPCTSTR WINAPI GetPicFile();
	virtual void WINAPI SetPicFile(LPCTSTR lpszName);

	virtual LPCTSTR WINAPI GetPaintMode();
	virtual void WINAPI SetPaintMode(LPCTSTR lpszPaintMode);
};

//////////////////////////////////////////////////////////////////////////
// duTextStyle interface
class duTextStyle : public duStyleBase
{ 
public:	
	virtual HFONT WINAPI GetHFont();
	virtual void WINAPI CalcTextRect(LPCTSTR lpszText, LPSIZE lpOutSize);

	virtual LPCTSTR WINAPI GetFont();
	virtual void WINAPI SetFont(LPCTSTR lpszFontName);
	virtual COLORREF WINAPI GetTextColor();
	virtual void WINAPI SetTextColor(COLORREF clrText);
	virtual BOOL WINAPI IsSingleLine();
	virtual void WINAPI SetSingleLine(BOOL fSingleLine);
	virtual LPCTSTR WINAPI GetHAlign();
	virtual void WINAPI SetHAlign(LPCTSTR lpszHorzAlign);
	virtual LPCTSTR WINAPI GetVAlign();
	virtual void WINAPI SetVAlign(LPCTSTR lpszVertAlign);
};

//////////////////////////////////////////////////////////////////////////
// duRectStyle interface
class duRectStyle : public duStyleBase
{
public:
	virtual COLORREF WINAPI GetFillColor();
	virtual void WINAPI SetFillColor(COLORREF clr);
	virtual COLORREF WINAPI GetBorderColor();
	virtual void WINAPI SetBorderColor(COLORREF clr);
	virtual BOOL WINAPI IsFillRect();
	virtual void WINAPI SetFillRect(BOOL fFill);
	virtual BOOL WINAPI IsDrawBorder();
	virtual void WINAPI SetDrawBorder(BOOL fBorder);
	virtual LPCTSTR WINAPI GetBorderType();
	virtual void WINAPI SetBorderType(LPCTSTR lpszBorderType);
	virtual UINT WINAPI GetBorderWidth();
	virtual void WINAPI SetBorderWidth(UINT uBorderWidth);
};

//////////////////////////////////////////////////////////////////////////
// duLineStyle interface
class duLineStyle : public duStyleBase
{
public:	
	virtual COLORREF WINAPI GetLineColor();
	virtual void WINAPI SetLineColor(COLORREF clr);
	virtual UINT WINAPI GetLineWidth();
	virtual void WINAPI SetLineWidth(UINT uLineWidth);
	virtual LPCTSTR WINAPI GetLineType();
	virtual void WINAPI SetLineType(LPCTSTR lpszLineType);
	virtual BOOL WINAPI GetStartPoint(LPPOINT lpOutPoint);
	virtual void WINAPI SetStartPoint(LPPOINT lpStartPoint);
	virtual BOOL WINAPI GetEndPoint(LPPOINT lpOutPoint);
	virtual void WINAPI SetEndPoint(LPPOINT lpEndPoint);
};

//////////////////////////////////////////////////////////////////////////
// duFont interface
class duFont : public duResBase
{
public:
	virtual int WINAPI GetHeight();
	virtual void WINAPI SetHeight(int nHeight);
	virtual int WINAPI GetWeight();
	virtual void WINAPI SetWeight(int nWeight);
	virtual BOOL WINAPI IsItalic();
	virtual void WINAPI SetItalic(BOOL fItalic);
	virtual BOOL WINAPI IsUnderline();
	virtual void WINAPI SetUnderline(BOOL fUnderline);
	virtual BOOL WINAPI IsStrikeOut();
	virtual void WINAPI SetStrikeOut(BOOL fStrikeOut);
	virtual LPCTSTR WINAPI GetFontFace();
	virtual void WINAPI SetFontFace(LPCTSTR lpszFace);
	virtual HFONT WINAPI GetHFont();
	virtual void WINAPI SetHFont(HFONT hFont);
	virtual HFONT WINAPI CreateFont();
};

//////////////////////////////////////////////////////////////////////////
// duImage interface
class duImage : public duResBase
{
public:
	virtual BOOL WINAPI CreateImage(int nWidth, int nHeight);
	virtual BOOL WINAPI LoadFromFile(LPCTSTR lpszFile);
	virtual BOOL WINAPI LoadFromMemory(PBYTE pData, int nSize);
	virtual BOOL WINAPI LoadFromStream(IStream *pStream);
	virtual PBYTE WINAPI GetBits();
	virtual HBITMAP WINAPI GetBitmap();
	virtual int WINAPI GetWidth();
	virtual int WINAPI GetHeight();
	
	virtual int WINAPI GetFrameCount();
	virtual HBITMAP WINAPI GetFrameBitmap(int nIndex);
	virtual PBYTE WINAPI GetFrameBits(int nIndex);
	virtual UINT WINAPI GetFrameDelay(int nIndex);
	
	virtual BOOL WINAPI BeginHSLConvert();
	virtual BOOL WINAPI AdjustHSL(int nHua, int nPerSat, int nPerLum);
	virtual void WINAPI EndHSLConvert();
	
	virtual LPCTSTR WINAPI GetValue();
	virtual void WINAPI SetValue(LPCTSTR strImagePath);
	
	virtual duImage *WINAPI CreateGrayImage();
	virtual duImage *WINAPI CreateStretchSmooth(int nWidth, int nHeight);
	virtual BOOL WINAPI LoadFromHICON(HICON hIcon);
};

//////////////////////////////////////////////////////////////////////////
// duCursor interface
class duCursor : public duResBase
{
public:
	virtual LPCTSTR WINAPI GetValue();
	virtual void WINAPI SetValue(LPCTSTR lpszCursor);
	virtual HCURSOR WINAPI GetHCursor();
	virtual void WINAPI SetHCursor(HCURSOR hCursor);
	virtual HCURSOR WINAPI LoadFromFile(LPCTSTR lpszFile);
	virtual HCURSOR WINAPI LoadFromMemory(PBYTE pData, int nSize);
};

//////////////////////////////////////////////////////////////////////////
// duRgn interface
class duRgn : public duResBase
{
public:
	virtual LPCTSTR WINAPI GetRgnType();
	virtual void WINAPI SetRgnType(LPCTSTR lpszType);
	virtual int WINAPI GetRoundX();
	virtual void WINAPI SetRoundX(int nRoundX);
	virtual int WINAPI GetRoundY();
	virtual void WINAPI SetRoundY(int nRoundY);
	virtual LPCTSTR WINAPI GetStyle();
	virtual void WINAPI SetStyle(LPCTSTR lpszStyle);
	virtual HRGN WINAPI GetHRgn(int nWidth, int nHeight);
};

//////////////////////////////////////////////////////////////////////////
// duStyleGroup interface
class duStyleGroup : public duResBase
{
public:
	virtual void WINAPI Draw(HDC hDC, LPRECT lpDstRect, UINT uState, LPCTSTR lpszText, int nAlpha);
	virtual void WINAPI DrawNotText(HDC hDC, LPRECT lpDstRect, UINT uState, LPCTSTR lpszText, int nAlpha);
	virtual void WINAPI DrawOnlyText(HDC hDC, LPRECT lpDstRect, UINT uState, LPCTSTR lpszText, int nAlpha);
	virtual void WINAPI GrayDrawByStyle(HDC hDC, LPRECT lpDstRect, UINT uState, LPCTSTR lpszText, int nAlpha);
	virtual int WINAPI GetStyleCount();
	virtual void WINAPI AddStyle(duStyleBase *pStyleBase);
	virtual BOOL WINAPI RemoveStyle(int nIndex);
	virtual duStyleBase *WINAPI GetStyle(int nIndex);
	virtual void WINAPI CalcTextRect(UINT uState, LPCTSTR lpszText, LPSIZE lpOutSize);
	virtual BOOL WINAPI MoveUp(int nIndex);
	virtual BOOL WINAPI MoveDown(int nIndex);
};



//////////////////////////////////////////////////////////////////////////
// duPlugin interface

class duPlugin : public duObject
{
public:
	virtual LPCTSTR WINAPI GetType();
	virtual LPCTSTR WINAPI GetName();
	virtual LPCTSTR WINAPI GetStyle();
	virtual int WINAPI GetTextLength();
	virtual LPCTSTR WINAPI GetText();
	virtual LPCTSTR WINAPI GetCursor();
	virtual BOOL WINAPI IsVisible();
	virtual BOOL WINAPI IsFocus();
	virtual BOOL WINAPI IsDisable();
	virtual BOOL WINAPI IsCached();
	virtual BOOL WINAPI IsOpaque();
	virtual HWND WINAPI GetHwnd();
	virtual UINT WINAPI GetState();
	virtual int WINAPI GetZorder();
	virtual void WINAPI GetRect(LPRECT lpRect);
	virtual int WINAPI GetPosTop();
	virtual int WINAPI GetPosLeft();
	virtual int WINAPI GetPosRight();
	virtual int WINAPI GetPosBottom();
	virtual int WINAPI GetPosHorzAnchor();
	virtual int WINAPI GetPosVertAnchor();
	virtual int WINAPI GetPosWidth();
	virtual int WINAPI GetPosHeight();
	virtual int WINAPI GetAlpha();
	virtual duPlugin *WINAPI GetParent();
	virtual duPlugin *WINAPI GetFirstChild();
	virtual duPlugin *WINAPI GetLastChild();
	virtual duPlugin *WINAPI GetPreSibling();
	virtual duPlugin *WINAPI GetNextSibling();
	virtual INT_PTR WINAPI GetParam();
	virtual HBITMAP WINAPI GetCachedBitmap();
	
	virtual void WINAPI SetName(LPCTSTR lpszName);
	virtual void WINAPI SetStyle(LPCTSTR lpszStyle);
	virtual void WINAPI SetText(LPCTSTR lpszText);
	virtual void WINAPI SetCursor(LPCTSTR lpszCursor);
	virtual void WINAPI SetVisible(BOOL fVisible);
	virtual void WINAPI SetFocus(BOOL fFocus);
	virtual void WINAPI SetDisable(BOOL fDisable);
	virtual void WINAPI SetCached(BOOL fCached);
	virtual void WINAPI SetOpaque(BOOL fOpaque);
	virtual void WINAPI SetHwnd(HWND hWnd);
	virtual void WINAPI SetState(UINT uState);
	virtual void WINAPI SetZorder(int nZorder);
	virtual void WINAPI SetRect(LPRECT lpRect);
	virtual void WINAPI SetPosTop(int nTop);
	virtual void WINAPI SetPosLeft(int nLeft);
	virtual void WINAPI SetPosRight(int nRight);
	virtual void WINAPI SetPosBottom(int nBottom);
	virtual void WINAPI SetPosHorzAnchor(int nHorzanchor);
	virtual void WINAPI SetPosVertAnchor(int nVertanchor);
	virtual void WINAPI SetPosWidth(int nWidth);
	virtual void WINAPI SetPosHeight(int nHeight);
	virtual void WINAPI SetAlpha(int nAlpha);
	virtual void WINAPI SetParent(duPlugin *pParent);
	virtual void WINAPI SetFirstChild(duPlugin *pFirstChild);
	virtual void WINAPI SetLastChild(duPlugin *pLastChild);
	virtual void WINAPI SetPreSibling(duPlugin *pPreSibling);
	virtual void WINAPI SetNextSibling(duPlugin *pNextSibling);
	virtual void WINAPI SetParam(INT_PTR lParam);
	virtual void WINAPI SetCachedBitmap(HBITMAP hBitmap);
	
	
public:
	virtual void WINAPI Resize(LPRECT lpRect);
	virtual duPlugin *WINAPI GetPluginByName(LPCTSTR lpszName);
	
	virtual void WINAPI OnMouseIn(LPPOINT ppt);
	virtual void WINAPI OnMouseLeave(LPPOINT ppt);
	virtual void WINAPI OnMouseLDown(LPPOINT ppt);
	virtual void WINAPI OnMouseLUp(LPPOINT ppt);
	virtual void WINAPI OnMouseRDown(LPPOINT ppt);
	virtual void WINAPI OnMouseRUp(LPPOINT ppt);
	virtual void WINAPI OnMouseHover(LPPOINT ppt);
	virtual void WINAPI OnMouseMove(LPPOINT ppt);
	virtual void WINAPI OnMouseDbClick(LPPOINT ppt);
	virtual void WINAPI OnMouseWheel(UINT fwKeys, int zDelta, LPPOINT ppt);
	virtual void WINAPI OnCaptureChanged(duPlugin *newCaptured);
	virtual BOOL WINAPI OnKillFocus(duPlugin *pNewFocus);
	virtual BOOL WINAPI OnSetFocus(duPlugin *pOldFocus);
	virtual void WINAPI OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void WINAPI OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void WINAPI OnTimer(UINT nEventId);
	virtual void WINAPI OnChildShow(duPlugin *pChild, BOOL fVisible);
	virtual void WINAPI OnChildResize(duPlugin *pChild);
	virtual void WINAPI OnRedraw();
	virtual void WINAPI OnVScroll(ScrollBarAction sbAction, int nPos);
	virtual void WINAPI OnHScroll(ScrollBarAction sbAction, int nPos);
	virtual LRESULT WINAPI OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL WINAPI OnSetCursor();
	virtual void WINAPI OnChildDelete(duPlugin *pChild);
	
	virtual void WINAPI RegisterControlProperty();
	virtual void WINAPI OnCreate();
	virtual void WINAPI DrawObject(HDC hDC);
};

class duButton : public duPlugin
{
public:	
	virtual BOOL WINAPI IsAutoSize();
	virtual void WINAPI SetAutoSize(BOOL fAutoSize);
	virtual int WINAPI GetFixLeft();
	virtual void WINAPI SetFixLeft(int nFixLeft);
	virtual int WINAPI GetFixRight();
	virtual void WINAPI SetFixRight(int nFixRight);
	virtual int WINAPI GetIconX();
	virtual void WINAPI SetIconX(int nIconX);
	virtual int WINAPI GetIconY();
	virtual void WINAPI SetIconY(int nIconY);
	virtual int WINAPI GetIconWidth();
	virtual void WINAPI SetIconWidth(int nIconWidth);
	virtual int WINAPI GetIconHeight();
	virtual void WINAPI SetIconHeight(int nIconHeight);
	virtual LPCTSTR WINAPI GetIcon();
	virtual void WINAPI SetIcon(LPCTSTR lpszIconName);
	virtual BOOL WINAPI IsFade();
	virtual void WINAPI SetFade(BOOL fFade);
	virtual int WINAPI GetFadeInSpeed();
	virtual void WINAPI SetFadeInSpeed(int nFadeInSpeed);
	virtual int WINAPI GetFadeOutSpeed();
	virtual void WINAPI SetFadeOutSpeed(int nFadeOutSpeed);
	virtual LPCTSTR WINAPI GetTooltipText();
	virtual void WINAPI SetTooltipText(LPCTSTR lpszText);
	virtual int WINAPI GetStatusIconX();
	virtual void WINAPI SetStatusIconX(int nStatusIconX);
	virtual int WINAPI GetStatusIconY();
	virtual void WINAPI SetStatusIconY(int nStatusIconY);
	virtual int WINAPI GetStatusIconWidth();
	virtual void WINAPI SetStatusIconWidth(int nStatusIconWidth);
	virtual int WINAPI GetStatusIconHeight();
	virtual void WINAPI SeStatustIconHeight(int nStatusIconHeight);
	virtual LPCTSTR WINAPI GetStatusIcon();
	virtual void WINAPI SetStatusIcon(LPCTSTR lpszStatusIconName);
	virtual BOOL WINAPI IsGrayDisable();
	virtual void WINAPI SetGrayDisable(BOOL fGrayDisable);
};

class duScrollView : public duPlugin
{
public:	
	virtual LPCTSTR WINAPI GetHorzScroll();
	virtual LPCTSTR WINAPI GetVertScroll();
	virtual BOOL WINAPI UpdateScroll();
	virtual void WINAPI DrawView(HDC hDC);
	virtual void WINAPI GetViewSize(LPSIZE lpSize);
	virtual void WINAPI OnViewMouseLDown(LPPOINT lppt);
	virtual void WINAPI OnViewMouseLUp(LPPOINT lppt);
	virtual void WINAPI OnViewMouseRDown(LPPOINT lppt);
	virtual void WINAPI OnViewMouseRUp(LPPOINT lppt);
	virtual void WINAPI OnViewMouseHover(LPPOINT lppt);
	virtual void WINAPI OnViewMouseMove(LPPOINT lppt);
	virtual void WINAPI OnViewMouseDbClick(LPPOINT lppt);
	virtual BOOL WINAPI OnViewSetCursor(LPPOINT lppt);
	virtual void WINAPI SetHorzScrollBar(LPCTSTR lpszScroll);
	virtual void WINAPI SetVertScrollBar(LPCTSTR lpszScroll);
};

class duScroll : public duPlugin
{
public:
	virtual void WINAPI RefreshScrollBar();
	virtual int  WINAPI GetMaxPos();
	virtual void WINAPI SetMaxPos(int nMaxPos);
	virtual int  WINAPI GetPos();
	virtual void WINAPI SetPos(int nPos);
	virtual int  WINAPI GetPage();
	virtual void WINAPI SetPage(int nPage);
	virtual int  WINAPI GetArrowHeight();
	virtual void WINAPI SetArrowHeight(int nArrowHeight);
	virtual BOOL WINAPI IsVert();
	virtual void WINAPI SetVert(BOOL bVert);
	virtual int  WINAPI GetStep();
	virtual void WINAPI SetStep(int nStep);
	virtual LPCTSTR WINAPI GetUpStyle();
	virtual void WINAPI SetUpStyle(LPCTSTR lpszStyle);
	virtual LPCTSTR WINAPI GetDownStyle();
	virtual void WINAPI SetDownStyle(LPCTSTR lpszStyle);
	virtual LPCTSTR WINAPI GetThumbStyle();
	virtual void WINAPI SetThumbStyle(LPCTSTR lpszStyle);
};


class TreeCtrlItem;
enum TCHitTestCode
{
	tc_hit_empty = 1,
	tc_hit_indentspace = 2,
	tc_hit_indent = 3,
	tc_hit_indenticonspace = 4,
	tc_hit_icon = 5,
	tc_hit_icontextspace = 6,
	tc_hit_text = 7,
	tc_hit_textspace = 8
};

#define TCVI_ROOT ((TreeCtrlItem *)(ULONG_PTR)-0x10000)
#define TCVI_FIRST ((TreeCtrlItem *)(ULONG_PTR)-0x0FFFF)
#define TCVI_LAST ((TreeCtrlItem *)(ULONG_PTR)-0x0FFFE)

class duTreeCtrl : public duScrollView
{
public:
	virtual TreeCtrlItem *WINAPI GetRootItem();
	virtual TreeCtrlItem *WINAPI InsertItem(LPCTSTR lpszText, LPCTSTR lpszImage, TreeCtrlItem *pParent, TreeCtrlItem *pInsertAfter);
	virtual BOOL WINAPI DeleteItem(TreeCtrlItem *pItem);
	virtual BOOL WINAPI ItemHasChildren(TreeCtrlItem *pItem);
	virtual LPCTSTR WINAPI GetItemStyle();
	virtual void WINAPI SetItemStyle(LPCTSTR lpszStyle);
	virtual LPCTSTR WINAPI GetIndentStyle();
	virtual void WINAPI SetIndentStyle(LPCTSTR lpszStyle);
	virtual LPCTSTR WINAPI GetFont();
	virtual void WINAPI SetFont(LPCTSTR lpszFont);
	virtual int WINAPI GetIndentWidth();
	virtual void WINAPI SetIndentWidth(int nIndentWidth);
	virtual int WINAPI GetIndentHeight();
	virtual void WINAPI SetIndentHeight(int nIndentHeight);
	virtual int WINAPI GetItemHeight();
	virtual void WINAPI SetItemHeight(int nItemHeight);
	virtual int WINAPI GetIconWidth();
	virtual void WINAPI SetIconWidth(int nIconWidth);
	virtual int WINAPI GetIconHeight();
	virtual void WINAPI SetIconHeight(int nIconHeight);
	virtual int WINAPI GetIndentIconSpace();
	virtual void WINAPI SetIndentIconSpace(int nIndentIconSpace);
	virtual int WINAPI GetIconTextSpace();
	virtual void WINAPI SetIconTextSpace(int nIconTextSpace);
	virtual COLORREF WINAPI GetTextColor();
	virtual void WINAPI SetTextColor(COLORREF clrText);
	virtual int WINAPI GetLastHitCode();
	virtual TreeCtrlItem *WINAPI GetNextItem(TreeCtrlItem *pItem);
	virtual LPCTSTR WINAPI GetItemText(TreeCtrlItem *pItem);
	virtual void WINAPI SetItemText(TreeCtrlItem *pItem, LPCTSTR lpszText);
	virtual LPCTSTR WINAPI GetItemIcon(TreeCtrlItem *pItem);
	virtual void WINAPI SetItemIcon(TreeCtrlItem *pItem, LPCTSTR lpszIcon);
	virtual int WINAPI GetItemLevel(TreeCtrlItem *pItem);
	virtual BOOL WINAPI IsExpand(TreeCtrlItem *pItem);
	virtual void WINAPI Expand(TreeCtrlItem *pItem, BOOL fExpand);
	virtual TreeCtrlItem *WINAPI GetParent(TreeCtrlItem *pItem);
	virtual TreeCtrlItem *WINAPI GetNextSibling(TreeCtrlItem *pItem);
	virtual TreeCtrlItem *WINAPI GetFirstChild(TreeCtrlItem *pItem);
	virtual TreeCtrlItem *WINAPI GetCurSelItem();
	virtual void WINAPI DeleteAllItems();
	virtual INT_PTR WINAPI GetItemData(TreeCtrlItem *pItem);
	virtual BOOL WINAPI SetItemData(TreeCtrlItem *pItem, INT_PTR pData);
	virtual BOOL WINAPI IsAutoShowTooltip();
	virtual void WINAPI SetAutoShowTooltip(BOOL fAutoShowTooltip);
	virtual TreeCtrlItem * WINAPI HitTest(LPPOINT lppt);
};

class duCheckBox : public duPlugin
{
public:	
	virtual BOOL WINAPI IsChecked();
	virtual void WINAPI SetChecked(BOOL fChecked);
	virtual BOOL WINAPI IsAutoSize();
	virtual void WINAPI SetAutoSize(BOOL fAutoSize);
	virtual int WINAPI GetFixLeft();
	virtual void WINAPI SetFixLeft(int nFixLeft);
	virtual int WINAPI GetFixRight();
	virtual void WINAPI SetFixRight(int nFixRight);
	virtual int WINAPI GetIconX();
	virtual void WINAPI SetIconX(int nIconX);
	virtual int WINAPI GetIconY();
	virtual void WINAPI SetIconY(int nIconY);
	virtual int WINAPI GetIconWidth();
	virtual void WINAPI SetIconWidth(int nIconWidth);
	virtual int WINAPI GetIconHeight();
	virtual void WINAPI SetIconHeight(int nIconHeight);
	virtual LPCTSTR WINAPI GetIcon();
	virtual void WINAPI SetIcon(LPCTSTR lpszIconName);
	virtual BOOL WINAPI IsFade();
	virtual void WINAPI SetFade(BOOL fFade);
	virtual int WINAPI GetFadeInSpeed();
	virtual void WINAPI SetFadeInSpeed(int nFadeInSpeed);
	virtual int WINAPI GetFadeOutSpeed();
	virtual void WINAPI SetFadeOutSpeed(int nFadeOutSpeed);
	virtual LPCTSTR WINAPI GetTooltipText();
	virtual void WINAPI SetTooltipText(LPCTSTR lpszText);
};

class duEdit : public duPlugin
{
public:	
	virtual int WINAPI CharFromPos(int x, int y);
	virtual UINT WINAPI GetLimitText();
	virtual TCHAR WINAPI GetPasswordChar();
	virtual DWORD WINAPI GetSel();
	virtual void WINAPI PosFromChar(int nIndex, LPPOINT lppt);
	virtual void WINAPI SetLimitText(UINT uMax);
	virtual void WINAPI ReplaceSel(LPCTSTR lpszNewText, BOOL fCanUndo);
	virtual BOOL WINAPI IsReadOnly();
	virtual BOOL WINAPI IsPassword();
	virtual BOOL WINAPI IsNumber();
	virtual void WINAPI SetSel(int nStartChar, int nEndChar);
	virtual void WINAPI OnPaste();
	virtual void WINAPI OnCopy();
	virtual void WINAPI OnClear();
	virtual void WINAPI OnCut();
	virtual void WINAPI SetReadOnly(BOOL fReadOnly);
	virtual void WINAPI SetPassword(BOOL fPassword);
	virtual void WINAPI SetNumber(BOOL fNumber);
	virtual LPCTSTR WINAPI GetFont();
	virtual void WINAPI SetFont(LPCTSTR lpszFont);
	virtual COLORREF WINAPI GetTextColor();
	virtual void WINAPI SetTextColor(COLORREF clrText);
	virtual COLORREF WINAPI GetSelectColor();
	virtual void WINAPI SetSelectColor(COLORREF clrSelect);
	virtual int WINAPI GetLeftBorder();
	virtual void WINAPI SetLeftBorder(int nLeftBorder);
	virtual int WINAPI GetTopBorder();
	virtual void WINAPI SetTopBorder(int nTopBorder);
	virtual int WINAPI GetRightBorder();
	virtual void WINAPI SetRightBorder(int nRightBorder);
	virtual int WINAPI GetBottomBorder();
	virtual void WINAPI SetBottomBorder(int nBottomBorder);
};

class duComboBox : public duEdit
{
public:	
	virtual BOOL WINAPI IsEnd();
	virtual void WINAPI SetEnd(BOOL fEnd);
	virtual int WINAPI GetItemCount();
	virtual BOOL WINAPI InsertItem(int nIndex, LPCTSTR lpszText, LPCTSTR lpszIcon);
	virtual BOOL WINAPI DeleteItem(int nIndex);
	virtual void WINAPI DeleteAll();
	virtual LPCTSTR WINAPI GetItemText(int nIndex);
	virtual BOOL WINAPI SetItemText(int nIndex, LPCTSTR lpszText);
	virtual LPCTSTR WINAPI GetItemIcon(int nIndex);
	virtual BOOL WINAPI SetItemIcon(int nIndex, LPCTSTR lpszIcon);
	virtual UINT WINAPI GetItemIconX(int nIndex);
	virtual BOOL WINAPI SetItemIconX(int nIndex, UINT uIconX);
	virtual UINT WINAPI GetItemIconY(int nIndex);
	virtual BOOL WINAPI SetItemIconY(int nIndex, UINT uIconY);
	virtual UINT WINAPI GetItemIconWidth(int nIndex);
	virtual BOOL WINAPI SetItemIconWidth(int nIndex, UINT uIconWidth);
	virtual UINT WINAPI GetItemIconHeight(int nIndex);
	virtual BOOL WINAPI SetItemIconHeight(int nIndex, UINT uIconHeight);
	virtual int WINAPI GetCurSel();
	virtual void WINAPI SetCurSel(int nIndex);
	virtual INT_PTR WINAPI GetItemData(int nIndex);
	virtual void WINAPI SetItemData(int nIndex, INT_PTR pData);
	virtual int WINAPI AddItem(LPCTSTR lpszText, LPCTSTR lpszIcon);
	virtual int WINAPI FindItem(LPCTSTR lpszText);
	virtual int WINAPI SelectItem(LPCTSTR lpszText);
	virtual BOOL WINAPI IsItemDisable(int nIndex);
	virtual BOOL WINAPI SetItemDisable(int nIndex, BOOL fDisable);
};

class duGifCtrl : public duPlugin
{
public:
	virtual void WINAPI Play();
	virtual void WINAPI StopPlay();
	virtual LPCTSTR WINAPI GetGif();
	virtual void WINAPI SetGif(LPCTSTR lpszName);
};

class duHwndObj : public duPlugin
{
public:
	virtual BOOL WINAPI IsDisable();
	virtual void WINAPI SetDisable(BOOL fDisable);
	virtual BOOL WINAPI IsFocus();
	virtual void WINAPI SetFocus(BOOL fFocus);
	virtual BOOL WINAPI Attach(HWND hWnd);
	virtual HWND WINAPI GetAttach();
};

class duIMPanelNode : public duPlugin
{
public:
	virtual void WINAPI Expand(BOOL fExpand);
	virtual BOOL WINAPI IsExpand();
	virtual int WINAPI GetLevel();
};

#define LAYOUT_NORMAL				 0
#define LAYOUT_LEFTTORIGHT			 1
#define LAYOUT_RIGHTTOLEFT			 2 
#define LAYOUT_TOPTOBOTTOM			 3 
#define LAYOUT_BOTTOMTOTOP			 4
#define LAYOUT_HORZ_BRIMMING		 5
#define LAYOUT_VERT_BRIMMING		 6
#define LAYOUT_GRID					 7

class duLayout : public duPlugin
{
public:
	virtual int WINAPI GetLayoutType();
	virtual void WINAPI SetLayoutType(int nLayoutType);
	virtual int WINAPI GetStartX();
	virtual void WINAPI SetStartX(int nStartX);
	virtual int WINAPI GetStartY();
	virtual void WINAPI SetStartY(int nStartY);
	virtual int WINAPI GetXSpace();
	virtual void WINAPI SetXSpace(int nXSpace);
	virtual int  WINAPI GetYSpace();
	virtual void WINAPI SetYSpace(int nYSpace);
	virtual void WINAPI AdjustChilds();
};

class duLEDTimer : public duPlugin
{
public:
	virtual LPCTSTR WINAPI GetImageFont();
	virtual void WINAPI SetImageFont(LPCTSTR lpszImageFont);
};

class duLink : public duPlugin
{
public:
	virtual LPCTSTR WINAPI GetURL();
	virtual void WINAPI SetURL(LPCTSTR lpszURL);
	virtual void WINAPI OpenURL();
};

class duListBox : public duPlugin
{
public:	
	virtual BOOL WINAPI UpdateScroll();
	virtual int WINAPI GetSel();
	virtual void WINAPI SetSel(int nIndex);
	virtual int WINAPI GetItemCount();
	virtual BOOL WINAPI InsertItem(int nIndex, LPCTSTR lpszText, LPCTSTR lpszIcon);
	virtual BOOL WINAPI DeleteItem(int nIndex);
	virtual void WINAPI DeleteAll();
	virtual LPCTSTR WINAPI GetItemText(int nIndex);
	virtual BOOL WINAPI SetItemText(int nIndex, LPCTSTR lpszText);
	virtual LPCTSTR WINAPI GetItemIcon(int nIndex);
	virtual BOOL WINAPI SetItemIcon(int nIndex, LPCTSTR lpszIcon);
	virtual UINT WINAPI GetItemIconX(int nIndex);
	virtual BOOL WINAPI SetItemIconX(int nIndex, UINT uIconX);
	virtual UINT WINAPI GetItemIconY(int nIndex);
	virtual BOOL WINAPI SetItemIconY(int nIndex, UINT uIconY);
	virtual UINT WINAPI GetItemIconWidth(int nIndex);
	virtual BOOL WINAPI SetItemIconWidth(int nIndex, UINT uIconWidth);
	virtual UINT WINAPI GetItemIconHeight(int nIndex);
	virtual BOOL WINAPI SetItemIconHeight(int nIndex, UINT uIconHeight);
	virtual BOOL WINAPI IsItemDisable(int nIndex);
	virtual BOOL WINAPI SetItemDisable(int nIndex, BOOL fDisable);
	virtual duScroll *WINAPI GetVertScrollBar();
	virtual void WINAPI SetVertScrollBar(LPCTSTR lpszScroll);
};

class duListBoxEx : public duPlugin
{
public:
	virtual LPCTSTR WINAPI GetItemStyle();
	virtual void WINAPI SetItemStyle(LPCTSTR pStyle);
	virtual duScroll *WINAPI GetVertScrollBar();
	virtual duPlugin *WINAPI GetHotItem();
	virtual duPlugin *WINAPI GetSelItem();
	virtual duPlugin *WINAPI GetPressItem();
	virtual void WINAPI SetHotItem(duPlugin *pPlugin);
	virtual void WINAPI SetSelItem(duPlugin *pPlugin);
	virtual void WINAPI SetPressItem(duPlugin *pPlugin);
	virtual void WINAPI RefreshPane();
	virtual void WINAPI SetVertScrollBar(LPCTSTR lpszScroll);
};

class duMenuBar : public duPlugin
{
public:
	virtual LPCTSTR WINAPI GetItemStyle();
	virtual void WINAPI SetItemStyle(LPCTSTR lpszItemStyle);
	virtual int WINAPI GetItemFixWidth();
	virtual void WINAPI SetItemFixWidth(int nFixWidth);
	virtual HMENU WINAPI GetHMenu();
	virtual void WINAPI SetHMenu(HMENU hMenu);
	virtual int WINAPI GetMenuItemCount();
	virtual void  WINAPI RefreshMenuBar();
};

class duOutlookBar : public duPlugin
{	
public:
	virtual int WINAPI GetItemCount();
	virtual BOOL WINAPI InsertItem(int nIndex, LPCTSTR lpszText, duPlugin *pChild);
	virtual LPCTSTR WINAPI GetItemText(int nIndex);
	virtual void WINAPI SetItemText(int nIndex, LPCTSTR lpszText);
	virtual duPlugin * WINAPI GetItem(int nIndex);
	virtual void WINAPI SetItem(int nIndex, duPlugin *pChild);
	virtual BOOL WINAPI DeleteItem(int nIndex);
	virtual int WINAPI GetSelectedItem();
	virtual void WINAPI SetSelectedItem(int nIndex);
};

class duProgress : public duPlugin
{
public:
	virtual int WINAPI GetPos();
	virtual void WINAPI SetPos(int nPos);
	virtual int WINAPI GetLeftBorder();
	virtual void WINAPI SetLeftBorder(int nLeftBorder);
	virtual int WINAPI GetRightBorder();
	virtual void WINAPI SetRightBorder(int nRightBorder);
	virtual int WINAPI GetTopBorder();
	virtual void WINAPI SetTopBorder(int nTopBorder);
	virtual int WINAPI GetBottomBorder();
	virtual void WINAPI SetBottomBorder(int nBottomBorder);
	virtual LPCTSTR WINAPI GetProgressStyle();
	virtual void WINAPI SetProgressStyle(LPCTSTR lpszStyle);
	virtual float WINAPI GetPosfloat();
	virtual void WINAPI SetPosfloat(float nPos);
};

class duRadio : public duPlugin
{
public:
	virtual BOOL WINAPI IsChecked();
	virtual void WINAPI SetChecked(BOOL fChecked);
	virtual int WINAPI GetGroupId();
	virtual int WINAPI GetIconX();
	virtual void WINAPI SetIconX(int nIconX);
	virtual int WINAPI GetIconY();
	virtual void WINAPI SetIconY(int nIconY);
	virtual int WINAPI GetIconWidth();
	virtual void WINAPI SetIconWidth(int nIconWidth);
	virtual int WINAPI GetIconHeight();
	virtual void WINAPI SetIconHeight(int nIconHeight);
	virtual LPCTSTR WINAPI GetIcon();
	virtual void WINAPI SetIcon(LPCTSTR lpszIconName);
	virtual LPCTSTR WINAPI GetTooltipText();
	virtual void WINAPI SetTooltipText(LPCTSTR lpszText);
};

class duReportView : public duScrollView
{
public:	
	virtual BOOL WINAPI InsertColumn(int nCol, int nWidth, LPCTSTR lpszText);
	virtual int WINAPI GetLineCount();
	virtual int WINAPI InsertLine(int nLine, int nHeight);
	virtual int WINAPI GetColumnCount();
	virtual int WINAPI GetColumnWidth(int nCol);
	virtual void WINAPI GetHeaderRect(LPRECT lpRect);
	virtual BOOL WINAPI DeleteColumn(int nCol);
	virtual BOOL WINAPI DeleteLine(int nLine);
	virtual LPCTSTR WINAPI GetCellText(int nLine, int nCol);
	virtual void WINAPI SetCellText(int nLine, int nCol, LPCTSTR lpszText);
	virtual LPCTSTR WINAPI GetCellStyle();
	virtual void WINAPI SetCellStyle(LPCTSTR lpszStyle);
	virtual int WINAPI GetHeaderHeight();
	virtual LPCTSTR WINAPI GetLineStyle();
	virtual void WINAPI SetLineStyle(LPCTSTR lpszStyle);
	virtual BOOL WINAPI IsMultiSel();
	virtual void WINAPI SetMultiSel(BOOL fMultiSel);
	virtual int WINAPI GetFirstSelLine();
};

class duScrollContainer : public duPlugin
{
public:
	virtual LPCTSTR WINAPI GetHorzScroll();
	virtual LPCTSTR WINAPI GetVertScroll();
	virtual LPCTSTR GetView();
	virtual BOOL WINAPI UpdateScroll();
	virtual void WINAPI GetViewSize(LPSIZE lpSize);
	virtual void WINAPI SetHorzScrollBar(LPCTSTR lpszScroll);
	virtual void WINAPI SetVertScrollBar(LPCTSTR lpszScroll);
};

class duSlider : public duPlugin
{
public:
	virtual int  WINAPI GetPos();
	virtual void WINAPI SetPos(int nPos);
	virtual int  WINAPI GetMaxPos();
	virtual void WINAPI SetMaxPos(int nMaxPos);
	virtual int  WINAPI GetThumbWidth();
	virtual void WINAPI SetThumbWidth(int nWidth);
	virtual int  WINAPI GetThumbHeight();
	virtual void WINAPI SetThumbHeight(int nHeight);
	virtual BOOL  WINAPI IsVert();
	virtual void  WINAPI SetVert(BOOL bVert);
	virtual LPCTSTR WINAPI GetForeStyle();
	virtual void WINAPI SetForeStyle(LPCTSTR lpszStyle);
	virtual LPCTSTR WINAPI GetThumbStyle();
	virtual void WINAPI SetThumbStyle(LPCTSTR lpszStyle);
	virtual int WINAPI GetStep();
	virtual void WINAPI SetStep(int nStep);
};

class duSpin : public duEdit
{
public:
	virtual int WINAPI GetValue();
	virtual void WINAPI SetValue(int nVal);
};

class duSplitter : public duPlugin
{
public:
	virtual void WINAPI MoveHorz(int nDistance);
	virtual void WINAPI MoveVert(int nDistance);
};

class duStatic : public duPlugin
{
public:
	virtual BOOL WINAPI IsShowToolTip();
	virtual void WINAPI SetShowToolTip(BOOL fShow);

	virtual LPCTSTR WINAPI GetToolTipText();
	virtual void WINAPI SetToolTipText(LPCTSTR lpszToolTip);
};

class duStaticEx : public duPlugin
{
public:
	virtual void WINAPI SetText(LPCTSTR lpszText);
	virtual void WINAPI Resize(LPRECT lpRect);
	virtual LPCTSTR WINAPI GetFont();
	virtual void WINAPI SetFont(LPCTSTR lpszFont);
	virtual COLORREF WINAPI GetTextColor();
	virtual void WINAPI SetTextColor(COLORREF clrText);
	virtual int WINAPI GetLineSpace();
	virtual void WINAPI SetLineSpace(int nLineSpace);
	virtual int WINAPI CalcTextCache();
	virtual int WINAPI GetLineCount(); 
	virtual LPCTSTR WINAPI GetLineText(int index);
	virtual void WINAPI GetLineTextRect(int index, LPSIZE lpOutSize);
};

// 
class duTabButton : public duPlugin
{
public:
	virtual BOOL WINAPI IsSelected();
	virtual void WINAPI SetSelected(BOOL fSel);
	virtual BOOL WINAPI IsAutoSize();
	virtual void WINAPI SetAutoSize(BOOL fAutoSize);
	virtual int WINAPI GetFixLeft();
	virtual void WINAPI SetFixLeft(int nFixLeft);
	virtual int WINAPI GetFixRight();
	virtual void WINAPI SetFixRight(int nFixRight);
	virtual int WINAPI GetIconX();
	virtual void WINAPI SetIconX(int nIconX);
	virtual int WINAPI GetIconY();
	virtual void WINAPI SetIconY(int nIconY);
	virtual int WINAPI GetIconWidth();
	virtual void WINAPI SetIconWidth(int nIconWidth);
	virtual int WINAPI GetIconHeight();
	virtual void WINAPI SetIconHeight(int nIconHeight);
	virtual LPCTSTR WINAPI GetIcon();
	virtual void WINAPI SetIcon(LPCTSTR lpszIconName);
	virtual BOOL WINAPI IsFade();
	virtual void WINAPI SetFade(BOOL fFade);
	virtual int WINAPI GetFadeInSpeed();
	virtual void WINAPI SetFadeInSpeed(int nFadeInSpeed);
	virtual int WINAPI GetFadeOutSpeed();
	virtual void WINAPI SetFadeOutSpeed(int nFadeOutSpeed);
	virtual LPCTSTR WINAPI GetTooltipText();
	virtual void WINAPI SetTooltipText(LPCTSTR lpszText);
	virtual LPCTSTR WINAPI GetTabPage();
	virtual void WINAPI SetTabPage(LPCTSTR lpszTabPage);
    virtual void WINAPI SetResponseDirect(BOOL bTrue);
    virtual BOOL WINAPI IsResponseDirect();

};

class duWindow : public duPlugin
{
public:
	virtual int WINAPI GetCaptionHeight();
	virtual void WINAPI SetCaptionHeight(int nCaptionHeight);
	virtual UINT WINAPI GetMinWidth();
	virtual void WINAPI SetMinWidth(UINT uMinWidth);
	virtual UINT WINAPI GetMinHeight();
	virtual void WINAPI SetMinHeight(UINT uMinHeight);
	virtual UINT WINAPI GetMaxWidth();
	virtual void WINAPI SetMaxWidth(UINT uMaxWidth);
	virtual UINT WINAPI GetMaxHeight();
	virtual void WINAPI SetMaxHeight(UINT uMaxHeight);
	virtual int WINAPI GetStartX();
	virtual void WINAPI SetStartX(int nStartX);
	virtual int WINAPI GetStartY();
	virtual void WINAPI SetStartY(int nStartY);
	virtual UINT WINAPI GetBorderSize();
	virtual void WINAPI SetBorderSize(UINT uBorderSize);
	virtual LPCTSTR WINAPI GetRgnName();
	virtual void WINAPI SetRgnName(LPCTSTR lpszRgnName);
	virtual void WINAPI SetCaptionLeft(int nCaptionLeft);
	virtual void WINAPI SetCaptionRight(int nCaptionRight);
	virtual void WINAPI SetCaptionTop(int nCaptionTop);
};
class duMenu;
class duMenuItem : public duPlugin
{
public:
    virtual LPCTSTR WINAPI GetChildMenu();
    virtual void WINAPI SetChildMenu(LPCTSTR lpszMenu);
    virtual LPCTSTR WINAPI GetIcon();
    virtual void WINAPI SetIcon(LPCTSTR lpszIcon);
    virtual int WINAPI GetIconX();
    virtual void WINAPI SetIconX(int nIconX);
    virtual int WINAPI GetIconY();
    virtual void WINAPI SetIconY(int nIconY);
    virtual int WINAPI GetIconWidth();
    virtual void WINAPI SetIconWidth(int nIconWidth);
    virtual int WINAPI GetIconHeight();
    virtual void WINAPI SetIconHeight(int nIconHeight);
    virtual BOOL WINAPI IsPopupItem();
    virtual duMenu *WINAPI GetPopupMenu();
    virtual void WINAPI SetPopupMenu(duMenu *pMenu);
    virtual LPCTSTR WINAPI GetPopupWindow();
    virtual void WINAPI SetPopupWindow(LPCTSTR lpszWin);
	virtual void WINAPI SetDisable(BOOL fDisable);
};

class duMenu : public duPlugin
{
public:
	virtual void WINAPI AdjustChild();
	virtual HWND WINAPI GetMenuHandle();
	virtual void WINAPI SetMenuHandle(HWND hWndMenu);
	virtual duMenu *WINAPI GetParentMenu();
	virtual void WINAPI SetParentMenu(duMenu *pMenu);
	virtual HWND WINAPI GetOwnerHwnd();
	virtual void WINAPI SetOwnerHwnd(HWND hWndOwner);
	virtual duMenuItem *WINAPI MenuItemFromClientPoint(LPPOINT ppt);
	virtual duMenu *WINAPI GetNextPopupMenu();
	virtual duMenuItem *WINAPI GetHotMenu();
};




class duPage : public duPlugin
{
public:	
	virtual int WINAPI GetPageCount();
	virtual int WINAPI GetSel();
	virtual void WINAPI SetSel(int nSel);
	virtual int WINAPI GetTotal();
	virtual void WINAPI SetTotal(int nTotal);
	virtual int WINAPI GetPerPage();
	virtual void WINAPI SetPerPage(int nPerPage);

	virtual int WINAPI GetPerPageLine();
	virtual void WINAPI SetPerPageLine(int nPerPageLine);

	virtual int WINAPI GetPerPageLineSpace();
	virtual void WINAPI SetPerPageLineSpace(int nPerPageLineYSpace);
	virtual int WINAPI GetArrowWidth();
	virtual void WINAPI SetArrowWidth(int nArrowWidth);
	virtual int WINAPI GetArrowHeight();
	virtual void WINAPI SetArrowHeight(int nArrowHeight);
	virtual int WINAPI GetArrowButtonSpace();
	virtual void WINAPI SetArrowButtonSpace(int nSpace);
	virtual int WINAPI GetButtonWidth();
	virtual void WINAPI SetButtonWidth(int nButtonWidth);
	virtual int WINAPI GetButtonHeight();
	virtual void WINAPI SetButtonHeight(int nButtonHeight);
	virtual int WINAPI GetButtonSpace();
	virtual void WINAPI SetButtonSpace(int nSpace);
	virtual LPCTSTR WINAPI GetLeftArrowStyle();
	virtual void WINAPI SetLeftArrowStyle(LPCTSTR lpszStyle);
	virtual LPCTSTR WINAPI GetRightArrowStyle();
	virtual void WINAPI SetRightArrowStyle(LPCTSTR lpszStyle);
	virtual LPCTSTR WINAPI GetButtonStyle();
	virtual void WINAPI SetButtonStyle(LPCTSTR lpszStyle);
	virtual BOOL WINAPI MoveLeft(BOOL fRedraw);
	virtual BOOL WINAPI MoveRight(BOOL fRedraw);
};

class duAnimation: public duPlugin
{	
public:
	virtual void WINAPI Play();
	virtual void WINAPI StopPlay();
	virtual LPCTSTR WINAPI GetAnimation();
	virtual void WINAPI SetAnimation(LPCTSTR lpszName);
	virtual int WINAPI GetFrameCount();
	virtual void WINAPI SetFrameCount(int nFrameCount);
	virtual int WINAPI GetTime();
	virtual void WINAPI SetTime(int nTime);
	virtual int WINAPI GetStopFrame();
	virtual void WINAPI SetStopFrame(int nStopFrame);
	
};
class duPie : public duPlugin
{
public:
	virtual float WINAPI GetPercent();
	virtual void WINAPI SetPercent(float fPercent);
	
	virtual COLORREF WINAPI GetAllColor();
	virtual void WINAPI SetAllColor(COLORREF clrAll);
	
	virtual COLORREF WINAPI GetPercentColor();
	virtual void WINAPI SetPercentColor(COLORREF clrPercent);
};


class duListCtrl : public duScrollView
{
public:
	virtual duPlugin *WINAPI InsertLine(int nIndex, LPCTSTR lpszTemplate);
	virtual duPlugin *WINAPI GetLine(int nIndex);
	virtual int WINAPI GetLineCount();
	virtual int WINAPI GetTotalHeight();
	virtual duPlugin *WINAPI GetFirstVisibleLine();
	virtual BOOL WINAPI MoveLine(int nIndex, int nNewIndex);
	virtual BOOL WINAPI DeleteLine(int nIndex, BOOL fAdjust);
	virtual void WINAPI ResetLine();

	virtual void WINAPI VertScroll(int nPos);
	virtual void WINAPI HorzScroll(int nPos);
	virtual void WINAPI AdjustColumn();
	virtual void WINAPI AdjustColumnWidth(int nCol, int nWidth);
	virtual int WINAPI GetSel();
	virtual void WINAPI SetSel(int nSel);
	virtual LPCTSTR WINAPI GetHeaderCtrl();
	virtual void WINAPI SetHeaderCtrl(LPCTSTR lpszHeader);
};

#define HEADER_CHECKBOX_NORMAL			1
#define HEADER_CHECKBOX_CHECKED			2
#define HEADER_CHECKBOX_CHECKEDPART		3

class duHeaderCtrl : public duPlugin
{
public:
	virtual BOOL WINAPI InsertItem(int nIndex, LPCTSTR lpszText, BOOL bPercent, int nWidthOrPercent, LPCTSTR lpszIcon);
	virtual int WINAPI GetItemCount();
	virtual int WINAPI GetTotalWidth();
	virtual int WINAPI GetOffsetX();
	virtual void WINAPI SetOffsetX(int nOffsetX);
	virtual UINT WINAPI GetCheckBoxState();
	virtual void WINAPI SetCheckBoxState(UINT uState);
	virtual int WINAPI GetItemWidth(int nIndex);
	virtual void WINAPI SetItemWidth(int nIndex, int nWidth);
	virtual LPCTSTR WINAPI GetItemText(int nIndex);
	virtual void WINAPI SetItemText(int nIndex, LPCTSTR lpszText);
	virtual LPCTSTR WINAPI GetItemIcon(int nIndex);
	virtual void WINAPI SetItemIcon(int nIndex, LPCTSTR lpszIcon);
	
	virtual int WINAPI GetSepWidth();
	virtual void WINAPI SetSepWidth(int nSepWidth);
	virtual LPCTSTR WINAPI GetSepImage();
	virtual void WINAPI SetSepImage(LPCTSTR lpszImage);
	virtual LPCTSTR WINAPI GetListCtrl();
	virtual void WINAPI SetListCtrl(LPCTSTR lpszCtrl);
	virtual int WINAPI GetBorderWidth();
	virtual void WINAPI SetBorderWidth(int nWidth);
	virtual LPCTSTR WINAPI GetItemStyle();
	virtual void WINAPI SetItemStyle(LPCTSTR lpszStyle);
	// icon
	virtual int WINAPI GetIconX();
	virtual void WINAPI SetIconX(int nIconX);
	virtual int WINAPI GetIconY();
	virtual void WINAPI SetIconY(int nIconY);
	virtual int WINAPI GetIconWidth();
	virtual void WINAPI SetIconWidth(int nIconWidth);
	virtual int WINAPI GetIconHeight();
	virtual void WINAPI SetIconHeight(int nIconHeight);
	// sort
	virtual LPCTSTR WINAPI GetSortStyle();
	virtual void WINAPI SetSortStyle(LPCTSTR lpszStyle);
	virtual int WINAPI GetSortX();
	virtual void WINAPI SetSortX(int nSortX);
	virtual int WINAPI GetSortY();
	virtual void WINAPI SetSortY(int nSortY);
	virtual int WINAPI GetSortWidth();
	virtual void WINAPI SetSortWidth(int nSortWidth);
	virtual int WINAPI GetSortHeight();
	virtual void WINAPI SetSortHeight(int nSortHeight);
	// checkbox
	virtual LPCTSTR WINAPI GetCheckBoxImage();
	virtual void WINAPI SetCheckBoxImage(LPCTSTR lpszImage);
	virtual BOOL WINAPI IsShowCheckBox();
	virtual void WINAPI SetShowCheckBox(BOOL fShow);
	virtual int WINAPI GetCheckBoxX();
	virtual void WINAPI SetCheckBoxX(int nX);
	virtual int WINAPI GetCheckBoxY();
	virtual void WINAPI SetCheckBoxY(int nY);
	virtual int WINAPI GetCheckBoxWidth();
	virtual void WINAPI SetCheckBoxWidth(int nWidth);
	virtual int WINAPI GetCheckBoxHeight();
	virtual void WINAPI SetCheckBoxHeight(int nHeight);
};

class duMledit : public duPlugin
{
public:
	virtual void WINAPI SetText(LPCTSTR lpszText);
	virtual LPCTSTR WINAPI GetText();
	virtual void WINAPI SetSel(UINT start, UINT end, BOOL after_wrap);
	virtual LRESULT WINAPI GetSel(PUINT start, PUINT end);
	virtual COLORREF WINAPI GetMlEditTextColor();
	virtual void WINAPI SetMlEditTextColor(COLORREF clrText);
	virtual COLORREF WINAPI GetSelectColor();
	virtual void WINAPI SetSelectColor(COLORREF clrSelect);
};
class duFlash : public duHwndObj
{
public:
	virtual void WINAPI Resize(LPRECT lpRect);
	virtual LPCTSTR WINAPI GetURL();
	virtual void WINAPI SetURL(LPCTSTR lpszURL);
	virtual IUnknown *WINAPI GetControl();
	virtual IUnknown *WINAPI GetContainer();
	virtual BOOL WINAPI Play(LPCTSTR lpszMovie);
	virtual BOOL WINAPI Stop();
	virtual UINT WINAPI GetPlayState();
	virtual void WINAPI Pause();
	virtual LPCTSTR WINAPI GetMovie();
	virtual BOOL WINAPI IsAllowFullScreen();
	virtual void WINAPI SetAllowFullScreen(BOOL fAllowFullScreen);
};
	
	class duGridLayout : public duPlugin
{
public:
	virtual BOOL WINAPI IsGridLayout() ;
	virtual void WINAPI SetGridLayout(BOOL fGrid) ;
	virtual int WINAPI GetStartX() ;
	virtual void WINAPI SetStartX(int nStartX) ;
	virtual int WINAPI GetStartY() ;
	virtual void WINAPI SetStartY(int nStartY) ;
	virtual int WINAPI GetXSpace() ;
	virtual void WINAPI SetXSpace(int nXSpace) ;
	virtual int WINAPI GetYSpace() ;
	virtual void WINAPI SetYSpace(int nYSpace);
	virtual int WINAPI GetMaxCount() ;
	virtual int WINAPI GetItemWidth() ;
	virtual void WINAPI SetItemWidth(int nItemWidth);
	virtual int WINAPI GetItemHeight();
	virtual void WINAPI SetItemHeight(int nItemHeight) ;
	virtual void WINAPI AdjustGrid();
};

/*class duRemoteCtrl : public duPlugin
{
public:
	virtual LPCTSTR WINAPI GetHorzScroll();
	virtual void WINAPI SetHorzScrollBar(LPCTSTR lpszScroll);

	virtual LPCTSTR WINAPI GetVertScroll();
	virtual void WINAPI SetVertScrollBar(LPCTSTR lpszScroll);

	virtual LPCTSTR WINAPI GetHwndObj();
	virtual void WINAPI SetHwndObj(LPCTSTR lpszHwndObj);

	virtual int WINAPI GetViewWidth();
	virtual int WINAPI GetViewHeight();
	virtual void WINAPI SetViewSize(int nWidth, int nHeight);
};*/

class duXmlStatic : public duPlugin
{
public:
	virtual void WINAPI SetText(LPCTSTR lpszText);
	virtual BOOL WINAPI OnSetCursor();
	virtual void WINAPI Resize(LPRECT lpRect);
	virtual int WINAPI CalcXmlTextCache();
	//virtual void WINAPI GetLineText(int nIndex,LPTSTR &pReturnStr);
	virtual BOOL WINAPI SetLimitLineCount(int nIndex);
	virtual int WINAPI GetLimitLineCount();
};
extern "C"
{
	DULIB_API duWindowManager *WINAPI LoadStyleA(LPCWSTR lpszXml);
	DULIB_API duWindowManager *WINAPI LoadStyleW(LPCWSTR lpszXml);
	DULIB_API duWindowManager *WINAPI LoadStyleZipA(LPCWSTR lpszZip);
	DULIB_API duWindowManager *WINAPI LoadStyleZipW(LPCWSTR lpszZip);
	DULIB_API duWindowManager *WINAPI LoadStyleZipMemory(BYTE *pData, int nSize);
	DULIB_API BOOL WINAPI ReleaseStyle(duWindowManager *pWinManager);
	DULIB_API BOOL WINAPI WindowManager_Attach(duWindowManager *pWinManager, HWND hWnd, LPCWSTR lpWindowName);
	DULIB_API BOOL WINAPI MatchString(LPCTSTR lpszPat, LPCTSTR lpszStr);
	DULIB_API BOOL WINAPI Plugin_Redraw(duPlugin *pPlugin, BOOL fNotify);
	DULIB_API BOOL WINAPI Plugin_IsVisible(duPlugin *pPlugin);
	DULIB_API void WINAPI Plugin_SetVisible(duPlugin *pPlugin, BOOL fVisible);
	DULIB_API BOOL WINAPI Plugin_IsValid(duPlugin *pPlugin);
	DULIB_API duPlugin *WINAPI Plugin_Clone(duPlugin *pTemplate, duPlugin *pParent, duPlugin *pPrevious, UINT nSuffix);
	DULIB_API BOOL WINAPI Plugin_Delete(duPlugin *pPlugin);
	DULIB_API BOOL WINAPI Plugin_GetVisibleRect(duPlugin *pPlugin, LPRECT lpRect);
	void WINAPI Plugin_GetRect(duPlugin *pPlugin, LPRECT lpRect);
	DULIB_API void WINAPI Plugin_Resize(duPlugin *pPlugin, LPRECT lpRect);
	DULIB_API void WINAPI DrawByStyle(duPlugin *pPlugin, LPCTSTR lpszStyle, HDC hDC, LPRECT lpDstRect, UINT uState, LPCTSTR lpszText, int nAlpha);
	DULIB_API duPlugin *WINAPI GetPluginByName(HWND hWnd, LPCTSTR lpszName);
	DULIB_API duPlugin *WINAPI GetFocusPlugin(HWND hWnd);
	DULIB_API void WINAPI SetFocusPlugin(HWND hWnd, duPlugin *pPlugin);
	DULIB_API BOOL WINAPI Plugin_TrackPopupMenu(HWND hWndOwner, duWindowManager *pWinManager, LPCTSTR lpszWinName, LPCTSTR lpszMenuName, int x, int y, UINT uFlags);
	DULIB_API void WINAPI Plugin_EndMenu();
	UINT64 WINAPI Plugin_GetParam64(duPlugin *pPlugin);
	void WINAPI Plugin_SetParam64(duPlugin *pPlugin, UINT64 nlParam);
	void WINAPI Plugin_SetTabOrder(duPlugin *pPlugin, int nTabOrder);
	int WINAPI Plugin_GetTabOrder(duPlugin *pPlugin);
	BOOL WINAPI Plugin_SetDisable(duPlugin *pPlugin, BOOL fDisable);
	
	
};

#endif //#ifndef __DIRECTUI_LIB__
