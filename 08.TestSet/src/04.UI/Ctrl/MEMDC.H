#ifndef _MEMDC_H_
#define _MEMDC_H_

class CMemeryDC : public CDC 
{
private:
    CBitmap    m_bitmap;        // Offscreen bitmap
    CBitmap*   m_oldBitmap;		// bitmap originally found in CMemDC
    CDC*       m_pDC;           // Saves CDC passed in constructor
    CRect      m_rect;          // Rectangle of drawing area.
    BOOL       m_bMemDC;        // TRUE if CDC really is a Memory DC.
	bool	   m_bFlushed;

public:
	CMemeryDC(CDC* pDC, LPCRECT pRect = NULL)
		: CDC()
	{
		ASSERT(pDC != NULL);

		// Some initialization
		m_pDC = pDC;
		m_oldBitmap = NULL;
		m_bMemDC = !pDC->IsPrinting();
		m_bFlushed = false;

		// Get the rectangle to draw
		if (pRect == NULL)
			pDC->GetClipBox(&m_rect);
		else
			m_rect = *pRect;

		if (m_bMemDC)
		{
			// Create a Memory DC
			CreateCompatibleDC(pDC);
			//pDC->LPtoDP(&m_rect);	// what is this needed for= -- we can't use that for RTL DCs!

			VERIFY( m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height()) );
			m_oldBitmap = SelectObject(&m_bitmap);

			SetMapMode(pDC->GetMapMode());
			SetWindowExt(pDC->GetWindowExt());
			SetViewportExt(pDC->GetViewportExt());
            //pDC->DPtoLP(&m_rect);	// what is this needed for? -- we can't use that for RTL DCs!
			SetWindowOrg(m_rect.left, m_rect.top);
		}
		else
		{
			m_bPrinting = pDC->m_bPrinting;
			m_hDC		 = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}

		// Fill background
		FillSolidRect(m_rect, pDC->GetBkColor());
	}
    
    ~CMemeryDC()      
    {
		Flush();
    }

	void Flush()
	{
		if (!m_bFlushed)
		{
			m_bFlushed = true;
			if (m_bMemDC)
			{
				// Copy the offscreen bitmap onto the screen.
				m_pDC->BitBlt(m_rect.left, m_rect.top, 
							  m_rect.Width(), m_rect.Height(), this, 
							  m_rect.left, m_rect.top, SRCCOPY);            
				
				//Swap back the original bitmap.
				SelectObject(m_oldBitmap);
			}
			else
				m_hDC = m_hAttribDC = NULL;
		}
	}

    // Allow usage as a pointer    
    CMemeryDC* operator->() 
    {
        return this;
    }       
 
    // Allow usage as a pointer    
    operator CMemeryDC*() 
    {
        return this;
    }
};

#endif