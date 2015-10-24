#include "StdAfx.h"
#include ".\shape.h"

CShape::CShape(void)
{
	m_pDC = NULL;
	m_bRun = false;
	m_bThread = false;

	SetData();
}

CShape::~CShape(void)
{
}

void CShape::SetData(void)
{
	// 点的位置(齐次矩阵)x,y,z
	m_nPt[0][0] = -100; m_nPt[0][1] = -100; m_nPt[0][2] = -100; m_nPt[0][3] = 1;
	m_nPt[1][0] =  100; m_nPt[1][1] = -100; m_nPt[1][2] = -100; m_nPt[1][3] = 1;
	m_nPt[2][0] =  100; m_nPt[2][1] = -100; m_nPt[2][2] =  100; m_nPt[2][3] = 1;
	m_nPt[3][0] = -100; m_nPt[3][1] = -100; m_nPt[3][2] =  100; m_nPt[3][3] = 1;
	m_nPt[4][0] = -100; m_nPt[4][1] =  100; m_nPt[4][2] = -100; m_nPt[4][3] = 1;
	m_nPt[5][0] =  100; m_nPt[5][1] =  100; m_nPt[5][2] = -100; m_nPt[5][3] = 1;
	m_nPt[6][0] =  100; m_nPt[6][1] =  100; m_nPt[6][2] =  100; m_nPt[6][3] = 1;
	m_nPt[7][0] = -100; m_nPt[7][1] =  100; m_nPt[7][2] =  100; m_nPt[7][3] = 1;

	m_nPt[8][0] =    0; m_nPt[8][1] =    0; m_nPt[8][2]  =   0; m_nPt[8][3] = 1;	// 中中点

	m_nPt[9][0] =  200; m_nPt[9][1] =    0; m_nPt[9][2]  =   0; m_nPt[9][3] = 1;	// 三轴
	m_nPt[10][0] =   0; m_nPt[10][1] = 200; m_nPt[10][2] =   0; m_nPt[10][3] = 1;
	m_nPt[11][0] =   0; m_nPt[11][1] =   0; m_nPt[11][2] = 200; m_nPt[11][3] = 1;

#pragma warning(disable : 4244)
	m_nPt[12][0] = 50*cos( 18*PI/180); m_nPt[12][1] = 50*sin( 18*PI/180); m_nPt[12][2] = 0; m_nPt[12][3] = 1;	// 大五角星
	m_nPt[13][0] = 50*cos( 90*PI/180); m_nPt[13][1] = 50*sin( 90*PI/180); m_nPt[13][2] = 0; m_nPt[13][3] = 1;
	m_nPt[14][0] = 50*cos(162*PI/180); m_nPt[14][1] = 50*sin(162*PI/180); m_nPt[14][2] = 0; m_nPt[14][3] = 1;
	m_nPt[15][0] = 50*cos(234*PI/180); m_nPt[15][1] = 50*sin(234*PI/180); m_nPt[15][2] = 0; m_nPt[15][3] = 1;
	m_nPt[16][0] = 50*cos(305*PI/180); m_nPt[16][1] = 50*sin(305*PI/180); m_nPt[16][2] = 0; m_nPt[16][3] = 1;

	m_nPt[17][0] = 20*cos( 54*PI/180); m_nPt[17][1] = 20*sin( 54*PI/180); m_nPt[17][2] = 0; m_nPt[17][3] = 1;	// 小五角星
	m_nPt[18][0] = 20*cos(126*PI/180); m_nPt[18][1] = 20*sin(126*PI/180); m_nPt[18][2] = 0; m_nPt[18][3] = 1;
	m_nPt[19][0] = 20*cos(198*PI/180); m_nPt[19][1] = 20*sin(198*PI/180); m_nPt[19][2] = 0; m_nPt[19][3] = 1;
	m_nPt[20][0] = 20*cos(278*PI/180); m_nPt[20][1] = 20*sin(278*PI/180); m_nPt[20][2] = 0; m_nPt[20][3] = 1;
	m_nPt[21][0] = 20*cos(342*PI/180); m_nPt[21][1] = 20*sin(342*PI/180); m_nPt[21][2] = 0; m_nPt[21][3] = 1;
#pragma warning(default : 4244)

	m_nPt[22][0] = 0; m_nPt[22][1] = 0; m_nPt[22][2] =  10; m_nPt[22][3] = 1;
	m_nPt[23][0] = 0; m_nPt[23][1] = 0; m_nPt[23][2] = -10; m_nPt[23][3] = 1;

	// 线的两个点的号和线的色
	m_nLine[0][0] = 0;  m_nLine[0][1] = 1;  m_nLine[0][2] = RGB(255, 0, 0);
	m_nLine[1][0] = 1;  m_nLine[1][1] = 2;  m_nLine[1][2] = RGB(255, 0, 0);
	m_nLine[2][0] = 2;  m_nLine[2][1] = 3;  m_nLine[2][2] = RGB(255, 0, 0);
	m_nLine[3][0] = 3;  m_nLine[3][1] = 0;  m_nLine[3][2] = RGB(255, 0, 0);
	m_nLine[4][0] = 4;  m_nLine[4][1] = 5;  m_nLine[4][2] = RGB(255, 0, 0);
	m_nLine[5][0] = 5;  m_nLine[5][1] = 6;  m_nLine[5][2] = RGB(255, 0, 0);
	m_nLine[6][0] = 6;  m_nLine[6][1] = 7;  m_nLine[6][2] = RGB(255, 0, 0);
	m_nLine[7][0] = 7;  m_nLine[7][1] = 4;  m_nLine[7][2] = RGB(255, 0, 0);
	m_nLine[8][0] = 0;  m_nLine[8][1] = 4;  m_nLine[8][2] = RGB(255, 0, 0);
	m_nLine[9][0] = 1;  m_nLine[9][1] = 5;  m_nLine[9][2] = RGB(255, 0, 0);
	m_nLine[10][0] = 2; m_nLine[10][1] = 6; m_nLine[10][2] = RGB(255, 0, 0);
	m_nLine[11][0] = 3; m_nLine[11][1] = 7; m_nLine[11][2] = RGB(255, 0, 0);

	m_nLine[12][0] = 0; m_nLine[12][1] = 6; m_nLine[12][2] = RGB(255, 255, 0);	// 体对角线
	m_nLine[13][0] = 1; m_nLine[13][1] = 7; m_nLine[13][2] = RGB(0, 255, 255);
	m_nLine[14][0] = 2; m_nLine[14][1] = 4; m_nLine[14][2] = RGB(255, 0, 255);
	m_nLine[15][0] = 3; m_nLine[15][1] = 5; m_nLine[15][2] = RGB(128, 0, 128);

	m_nLine[16][0] = 4; m_nLine[16][1] = 6; m_nLine[16][2] = RGB(128, 128, 0);	// 面对角线
	m_nLine[17][0] = 5; m_nLine[17][1] = 7; m_nLine[17][2] = RGB(0, 128, 128);

	m_nLine[18][0] = 8; m_nLine[18][1] = 9;  m_nLine[18][2] = RGB(255, 0, 0);	// x 轴
	m_nLine[19][0] = 8; m_nLine[19][1] = 10; m_nLine[19][2] = RGB(0, 255, 0);	// y 轴
	m_nLine[20][0] = 8; m_nLine[20][1] = 11; m_nLine[20][2] = RGB(0, 0, 255);	// z 轴

	m_nLine[21][0] = 17; m_nLine[21][1] = 22; m_nLine[21][2] = RGB(255, 0, 0);	// 小五角星到中心点
	m_nLine[22][0] = 18; m_nLine[22][1] = 22; m_nLine[22][2] = RGB(255, 0, 0);
	m_nLine[23][0] = 19; m_nLine[23][1] = 22; m_nLine[23][2] = RGB(255, 0, 0);
	m_nLine[24][0] = 20; m_nLine[24][1] = 22; m_nLine[24][2] = RGB(255, 0, 0);
	m_nLine[25][0] = 21; m_nLine[25][1] = 22; m_nLine[25][2] = RGB(255, 0, 0);

	m_nLine[26][0] = 12; m_nLine[26][1] = 22; m_nLine[26][2] = RGB(255, 0, 0);	// 大五角星脊
	m_nLine[27][0] = 13; m_nLine[27][1] = 22; m_nLine[27][2] = RGB(255, 0, 0);
	m_nLine[28][0] = 14; m_nLine[28][1] = 22; m_nLine[28][2] = RGB(255, 0, 0);
	m_nLine[29][0] = 15; m_nLine[29][1] = 22; m_nLine[29][2] = RGB(255, 0, 0);
	m_nLine[30][0] = 16; m_nLine[30][1] = 22; m_nLine[30][2] = RGB(255, 0, 0);

	m_nLine[31][0] = 12; m_nLine[31][1] = 23; m_nLine[31][2] = RGB(255, 0, 0);	// 大五角星脊
	m_nLine[32][0] = 13; m_nLine[32][1] = 23; m_nLine[32][2] = RGB(255, 0, 0);
	m_nLine[33][0] = 14; m_nLine[33][1] = 23; m_nLine[33][2] = RGB(255, 0, 0);
	m_nLine[34][0] = 15; m_nLine[34][1] = 23; m_nLine[34][2] = RGB(255, 0, 0);
	m_nLine[35][0] = 16; m_nLine[35][1] = 23; m_nLine[35][2] = RGB(255, 0, 0);

	m_nLine[36][0] = 12; m_nLine[36][1] = 17; m_nLine[36][2] = RGB(255, 0, 0);	// 大角到小角
	m_nLine[37][0] = 13; m_nLine[37][1] = 18; m_nLine[37][2] = RGB(255, 0, 0);
	m_nLine[38][0] = 14; m_nLine[38][1] = 19; m_nLine[38][2] = RGB(255, 0, 0);
	m_nLine[39][0] = 15; m_nLine[39][1] = 20; m_nLine[39][2] = RGB(255, 0, 0);
	m_nLine[40][0] = 16; m_nLine[40][1] = 21; m_nLine[40][2] = RGB(255, 0, 0);

	m_nLine[41][0] = 12; m_nLine[41][1] = 21; m_nLine[41][2] = RGB(255, 0, 0);	// 大角到小角
	m_nLine[42][0] = 13; m_nLine[42][1] = 17; m_nLine[42][2] = RGB(255, 0, 0);
	m_nLine[43][0] = 14; m_nLine[43][1] = 18; m_nLine[43][2] = RGB(255, 0, 0);
	m_nLine[44][0] = 15; m_nLine[44][1] = 19; m_nLine[44][2] = RGB(255, 0, 0);
	m_nLine[45][0] = 16; m_nLine[45][1] = 20; m_nLine[45][2] = RGB(255, 0, 0);

	m_nLine[46][0] = 17; m_nLine[46][1] = 23; m_nLine[46][2] = RGB(255, 0, 0);	// 小五角星到中心点
	m_nLine[47][0] = 18; m_nLine[47][1] = 23; m_nLine[47][2] = RGB(255, 0, 0);
	m_nLine[48][0] = 19; m_nLine[48][1] = 23; m_nLine[48][2] = RGB(255, 0, 0);
	m_nLine[49][0] = 20; m_nLine[49][1] = 23; m_nLine[49][2] = RGB(255, 0, 0);
	m_nLine[50][0] = 21; m_nLine[50][1] = 23; m_nLine[50][2] = RGB(255, 0, 0);

    // 线数
    m_nLineCount = 51;
}

//绕y轴旋转f度
void CShape::rotation_y(int f)
{
	int i,j,n,nTempPt[4];
	double dbTemp;

	if (f < 0) f += 360;
	if (f > 360) f %= 360;

	m_dRot[0][0] = cos((double)f * PI / 180.0);
	m_dRot[0][1] = 0;
	m_dRot[0][2] = -1*sin((double)f * PI / 180.0f);
	m_dRot[0][3] = 0;

	m_dRot[1][0] = 0;
	m_dRot[1][1] = 1;
	m_dRot[1][2] = 0;
	m_dRot[1][3] = 0;

	m_dRot[2][0] = sin((double)f * PI / 180.0f);
	m_dRot[2][1] = 0;
	m_dRot[2][2] = cos((double)f * PI / 180.0f);
	m_dRot[2][3] = 0;

	m_dRot[3][0] = 0;
	m_dRot[3][1] = 0;
	m_dRot[3][2] = 0;
	m_dRot[3][3] = 1;

	for (n = 0; n < m_nLineCount; n++)
	{
		for (i = 0; i < 4; i++)
		{
			dbTemp = 0;
			for (j = 0; j < 4; j++)
				dbTemp += (double)m_nPt[n][j] * m_dRot[j][i];

			nTempPt[i] = (int)dbTemp;
			
		}
		for (i = 0; i < 4; i++)
			m_nPt[n][i] = nTempPt[i];
	}
}

//绕x轴旋转f度
void CShape::rotation_x(int f)
{
	int i,j,n,nTempPt[4];
	double dbTemp;

	if(f < 0) f += 360;
	if(f > 360) f %=360;

	m_dRot[0][0] = 1;
	m_dRot[0][1] = 0;
	m_dRot[0][2] = 0;
	m_dRot[0][3] = 0;
	
	m_dRot[1][0] = 0;
	m_dRot[1][1] = cos(f * PI / 180.0);
	m_dRot[1][2] = sin(f * PI / 180.0);
	m_dRot[1][3] = 0;
	
	m_dRot[2][0] = 0;
	m_dRot[2][1] = -1*sin(f * PI / 180.0);
	m_dRot[2][2] = cos(f * PI / 180.0);
	m_dRot[2][3] = 0;
	
	m_dRot[3][0] = 0;
	m_dRot[3][1] = 0;
	m_dRot[3][2] = 0;
	m_dRot[3][3] = 1;

	for (n = 0; n < m_nLineCount; n++)
	{
		for (i = 0; i < 4; i++)
		{
			dbTemp = 0;
			for (j = 0; j < 4; j++)
				dbTemp += (double)m_nPt[n][j] * m_dRot[j][i];

			nTempPt[i] = (int)dbTemp;
			
		}
		for (i = 0; i < 4; i++)
			m_nPt[n][i] = nTempPt[i];
	}
}

//移动
void CShape::move(int x,int y,int z)
{
	int i,j,n,nTempPt[4];
	double dbTemp;

	m_dRot[0][0] = 1;
	m_dRot[0][1] = 0;
	m_dRot[0][2] = 0;
	m_dRot[0][3] = 0;
				  
	m_dRot[1][0] = 0;
	m_dRot[1][1] = 1;
	m_dRot[1][2] = 0;
	m_dRot[1][3] = 0;
				  
	m_dRot[2][0] = 0;
	m_dRot[2][1] = 0;
	m_dRot[2][2] = 1;
	m_dRot[2][3] = 0;
				  
	m_dRot[3][0] = x;
	m_dRot[3][1] = y;
	m_dRot[3][2] = z;
	m_dRot[3][3] = 1;

	for (n = 0; n < m_nLineCount; n++)
	{
		for (i = 0; i < 4; i++)
		{
			dbTemp = 0;
			for (j = 0; j < 4; j++)
				dbTemp += (double)m_nPt[n][j] * m_dRot[j][i];

			nTempPt[i] = (int)dbTemp;			
		}
		for (i = 0; i < 4; i++)
			m_nPt[n][i] = nTempPt[i];
	}
}

#pragma warning(disable : 4311)

void CShape::show_xy_face(void)
{

    if ((NULL != m_pDC) && (0xfeeefeee != (int)m_pDC))
    {
        m_pDC->TextOut(CENTER_POINT_X+m_nPt[ 9][0], m_nScreenHeight-CENTER_POINT_Y-m_nPt[ 9][1], _T("X"));
        m_pDC->TextOut(CENTER_POINT_X+m_nPt[10][0], m_nScreenHeight-CENTER_POINT_Y-m_nPt[10][1], _T("Y"));
        m_pDC->TextOut(CENTER_POINT_X+m_nPt[11][0], m_nScreenHeight-CENTER_POINT_Y-m_nPt[11][1], _T("Z"));
        
        for (int i = 0; i< m_nLineCount; i++)
        {
            line(m_nPt[m_nLine[i][0]][0], m_nScreenHeight - m_nPt[m_nLine[i][0]][1],
                m_nPt[m_nLine[i][1]][0], m_nScreenHeight - m_nPt[m_nLine[i][1]][1],
                m_nLine[i][2]);
        }
    }
}

void CShape::clear(void)
{
    if ((NULL != m_pDC) && (0xfeeefeee != (int)m_pDC))
    {
        COLORREF clOld = m_pDC->SetTextColor(RGB(136,217,147));

        m_pDC->TextOut(CENTER_POINT_X+m_nPt[ 9][0], m_nScreenHeight-CENTER_POINT_Y-m_nPt[ 9][1], _T("X"));
        m_pDC->TextOut(CENTER_POINT_X+m_nPt[10][0], m_nScreenHeight-CENTER_POINT_Y-m_nPt[10][1], _T("Y"));
        m_pDC->TextOut(CENTER_POINT_X+m_nPt[11][0], m_nScreenHeight-CENTER_POINT_Y-m_nPt[11][1], _T("Z"));

        m_pDC->SetTextColor(clOld);

        for (int i = 0; i < m_nLineCount; i++)
        {
            line(m_nPt[m_nLine[i][0]][0], m_nScreenHeight - m_nPt[m_nLine[i][0]][1],
                m_nPt[m_nLine[i][1]][0], m_nScreenHeight - m_nPt[m_nLine[i][1]][1],
                RGB(136,217,147));
        }
    }
}

#pragma warning(default : 4311)

void CShape::line(int x1, int y1, int x2, int y2, COLORREF col)
{
	x1 += CENTER_POINT_X;
	y1 -= CENTER_POINT_Y;
	x2 += CENTER_POINT_X;
	y2 -= CENTER_POINT_Y;

	if (NULL == m_pDC) return;

	m_Pen.CreatePen(BS_SOLID, 1, col);
	CPen *pOldPen = (CPen*)m_pDC->SelectObject(&m_Pen);
	
	m_pDC->MoveTo(x1, y1);
	m_pDC->LineTo(x2, y2);

	m_pDC->SelectObject(pOldPen);
	m_Pen.DeleteObject();
}

void CShape::SetDC(CDC *pDC)
{
	m_pDC = pDC;

	m_pDC->SetBkMode(TRANSPARENT);
}

void CShape::SetScreenHeight(int nHeight)
{
	m_nScreenHeight = nHeight;
}

void CShape::Do(void)
{
	m_bRun = true;
	m_bThread = true;

	for (int i = 0; ; i++)//i < 360*3
	{
		rotation_y(i);
		rotation_x(i);

		show_xy_face();

		::Sleep(30);

		if (!m_bRun)
		{
			break;
		}
		
		clear();

		SetData();
	}

	m_bRun = false;
	m_bThread = false;
}