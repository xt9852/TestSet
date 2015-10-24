// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../resource.h"
#include "UI/dulib.h"

class duWindowManager;

class CMainFrame : 
	public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

    CMainFrame();
    ~CMainFrame();

     /**
     *\fn         void GetCurrentPath()
     *\brief      得到程序的当前路径。
     *\return     无。
     */
    void GetCurrentPath();

    /**
     *\fn         int LoadSkin()
     *\brief      加载DirectUI皮肤。
     *\return     是否成功,0成功，其它失败
     */
    int LoadSkin();

    /**
     *\fn         duWindowManager* getWindowManager()
     *\brief      得到DirectUI窗体管理。
     *\return     DirectUI窗体管理
     */
    duWindowManager* getWindowManager() { return wndManager_; }

protected:
    duWindowManager *wndManager_;           // DirectUI窗体管理
    TCHAR           currentPath_[MAX_PATH]; // 当前路径

public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_DIRECTUI_NOTIFY, OnDirectUINotify)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnDirectUINotify(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnMinClick(duPlugin * /*pPlugin*/, WPARAM /*wParam*/, LPARAM /*lParam*/);
    LRESULT OnCloseClick(duPlugin * /*pPlugin*/, WPARAM /*wParam*/, LPARAM /*lParam*/);
};
