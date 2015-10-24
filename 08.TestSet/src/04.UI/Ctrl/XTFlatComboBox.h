
#pragma once

 
class CXTFlatComboBox : public CXTUI
{ 
public:     
    CXTFlatComboBox();
    virtual ~CXTFlatComboBox();
 
protected: 
 
    // enum used to determine the state the combo box should be 
    enum STATE { NORMAL = 1, RAISED = 2, PRESSED = 3 }; 
 
    int      m_cxHThumb;     // Size of the drop arrow for the combo box. 
    BOOL     m_bLBtnDown;    // TRUE if left mouse button is pressed 
    BOOL     m_bPainted;     // used during paint operations 
    BOOL     m_bHasFocus;    // TRUE if control has focus 
    BOOL     m_bAutoComp;    // Used by Autocompleting. 
    BOOL     m_bFlatLook;    // TRUE if the control is flat. 
	BOOL     m_bDisableAC;   // TRUE when auto complete is disabled internally. 
    COLORREF m_clr3DHilight; // System color for ::GetSysColor(COLOR_3DHILIGHT). 
	COLORREF m_clr3DShadow;  // System color for ::GetSysColor(COLOR_3DSHADOW). 
	COLORREF m_clr3DFace;    // System color for ::GetSysColor(COLOR_3DFACE). 
 
public: 
 
    // -> Input:   bDisable - TRUE to disable flat appearance. 
    // -> Remarks: This member function will disable the flat look for the combo box. 
    void DisableFlatLook(BOOL bDisable); 
 
    // -> Input:   bEnable - TRUE to enable auto completion; otherwise FALSE. 
    // -> Remarks: This member function enables or disables auto completion. 
    virtual void EnableAutoCompletion(BOOL bEnable=TRUE); 
 
    // -> Returns: TRUE if the mouse is over the combo box; otherwise FALSE. 
    // -> Remarks: This member function determines if the mouse is within the controls rect. 
    virtual BOOL PointInRect(); 
 
protected: 
 
    // -> Input:   pDC            - Points to the current device context. 
	//             eState         - Current state of the combo box, either NORMAL, RAISED, or PRESSED. 
    //             clrTopLeft     - RGB color value for top left 3D borders. 
    //             clrBottomRight - RGB color value for bottom right 3D borders. 
    //              
    // -> Remarks: This member function is called by the combo box whenever a paint  
    //             operation should occur. 
    virtual void DrawCombo(CDC* pDC, STATE eState, COLORREF clrTopLeft, COLORREF clrBottomRight); 
 
	// -> Input:   pDC - Points to the current device context. 
	// -> Remarks: This member function is called by the control to for flicker 
	//             free drawing. 
	void OnNoFlickerPaint(CDC* pDC); 
 
    //{{AFX_VIRTUAL(CXTFlatComboBox) 
    public: 
    virtual BOOL PreTranslateMessage(MSG* pMsg); 
    //}}AFX_VIRTUAL 
 
    //{{AFX_MSG(CXTFlatComboBox) 
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point); 
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
    afx_msg void OnTimer(UINT nIDEvent); 
    afx_msg void OnPaint(); 
    afx_msg void OnSetFocus(); 
    afx_msg void OnKillFocus(); 
	afx_msg void OnSysColorChange(); 
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); 
	afx_msg void OnEditUpdate(); 
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); 

}; 
 