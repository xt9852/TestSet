
#pragma once

#include <math.h>

#define CENTER_POINT_X	600
#define CENTER_POINT_Y	500
#define MAX_POINT_COUNT 100
#define MAX_LINE_COUNT	1000
#define PI				3.141592653589793

class CShape
{
public:
	CShape(void);
	~CShape(void);

	int		m_nPt[MAX_POINT_COUNT][4];		// 点坐标,齐次距阵
	double	m_dRot[4][4];
	UINT	m_nLine[MAX_LINE_COUNT][3];		// 线两端的点号和线的颜色	
	int		m_nLineCount;
	int		m_nScreenHeight;
	bool	m_bThread;
	bool	m_bRun;

	CDC*	m_pDC;
	CPen	m_Pen;

	void SetData(void);
	void clear(void);
	void show_xy_face(void);
	void move(int x,int y,int z);
	void rotation_x(int f);
	void rotation_y(int f);
	void line(int x1, int y1, int x2, int y2, COLORREF col);
	void Do(void);
	void SetScreenHeight(int nHeight);
	void SetDC(CDC *pDC);

};
