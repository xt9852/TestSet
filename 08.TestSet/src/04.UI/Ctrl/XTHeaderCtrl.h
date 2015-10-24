#pragma once
#include "XTUI.h"


class CXTHeaderCtrl : public CHeaderCtrl, public CXTUI
{
public:
    CXTHeaderCtrl();
    virtual ~CXTHeaderCtrl();

private:
    CFont font_;				// ×ÖÌå
    CFont *oldFont_;

public:
    bool Initial(int x, int y, int cx, int cy, int sx, int sy, CXTDC *xtDC);
    void DrawImage(CPaintDC &dc);
    void ResetImage(int sx = -1, int sy = -1);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnDestroy();

    DECLARE_MESSAGE_MAP()
};
