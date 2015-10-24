#include "StdAfx.h"
#include "ScaleBmp.h"

#pragma warning (disable : 4244)


CScaleBmp::CScaleBmp(void)
:m_pszData(NULL)
{
	memset(&m_BmpFileHeader, 0, sizeof(m_BmpFileHeader));
    memset(&m_BmpInfoHeader, 0, sizeof(m_BmpInfoHeader));
}

CScaleBmp::~CScaleBmp(void)
{
}

//************************************
// Method:    GetPixelValue
// FullName:  GetPixelValue
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char* pszData [IN]  数据源
// Parameter: int nWidthLen [IN]  一行的总宽度
// Parameter: int i         [IN]  列号
// Parameter: int j         [IN]  行号
// Parameter: int & r       [OUT] 像素值
// Parameter: int & g       [OUT] 像素值
// Parameter: int & b       [OUT] 像素值
//************************************
void CScaleBmp::GetPixelValue(char* pszData, int nWidthLen, int i, int j, int &r, int &g, int &b)
{
    int nIndex = i*nWidthLen + j*3;

    r = pszData[nIndex+0];
    g = pszData[nIndex+1];
    b = pszData[nIndex+2];
}

//************************************
// Method:    SetPixelValue
// FullName:  SetPixelValue
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char* pszData [IN]  数据源
// Parameter: int nWidthLen [IN]  一行的总宽度
// Parameter: int i         [IN]  列号
// Parameter: int j         [IN]  行号
// Parameter: int & r       [OUT] 像素值
// Parameter: int & g       [OUT] 像素值
// Parameter: int & b       [OUT] 像素值
//************************************
void CScaleBmp::SetPixelValue(char* pszData, int nWidthLen, int i, int j, int r, int g, int b)
{
    int nIndex = i*nWidthLen + j*3;

    pszData[nIndex+0] = r;
    pszData[nIndex+1] = g;
    pszData[nIndex+2] = b;
}

//************************************
// Method:    Load
// FullName:  CScaleBmp::Load
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const char * pszFileName
// 打开文件
//************************************
bool CScaleBmp::Load(const char *pszFileName)
{
    if (NULL == pszFileName) return false;

    FILE *pFile = fopen(pszFileName, "rb");

    if (NULL != pFile)
    {
        fread(&m_BmpFileHeader, sizeof(m_BmpFileHeader), 1, pFile);
        fread(&m_BmpInfoHeader, sizeof(m_BmpInfoHeader), 1, pFile);

        if (NULL != m_pszData)
        {
            delete m_pszData;
            m_pszData = NULL;
        }

        int nLineDataLen = (m_BmpInfoHeader.biWidth * 3 + 3) / 4 * 4;
        int nDataSize = nLineDataLen * m_BmpInfoHeader.biHeight;

        m_pszData = new char[nDataSize];

        fread(m_pszData, nDataSize, 1, pFile);
        fclose(pFile);
        return true;
    }
    else
    {
        return false;
    }
}

//************************************
// Method:    SaveBmp
// FullName:  CScaleBmp::SaveBmp
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const char * pszFileName  [IN] 文件名
// Parameter: float fScaleX             [IN] X方向放大比例
// Parameter: float fScaleY             [IN] Y方向放大比例
//************************************
bool CScaleBmp::SaveBmp(const char *pszFileName, float fScaleX, float fScaleY)
{
	if (NULL == pszFileName) return false;

    //----------------------------------------------------------
    // 双线性内插法
    // f(i+u, j+v) = (1-u)(1-v)f(i,j) + (1-u)vf(i,j+1) + u(1-v)f(i+1,j) + uvf(i+1,j+1)
    //----------------------------------------------------------

    int nSrcWidth = m_BmpInfoHeader.biWidth;
    int nSrcHeight = m_BmpInfoHeader.biHeight;
    float fDestWidth = nSrcWidth * fScaleX;
    float fDestHeight = nSrcHeight * fScaleY;
    float fUScale = nSrcWidth / fDestWidth;      // 横向放大比例
    float fVScale = nSrcHeight / fDestHeight;    // 纵向放大比例

    int nSrcLineDataLen = (m_BmpInfoHeader.biWidth * 3 + 3) / 4 * 4; // 原图像一行数据长度
    int nDestLineDataLen = ((int)fDestWidth * 3 + 3) / 4 * 4;             // 目标图像一行数据长度
    int nDataLen = nDestLineDataLen * fDestHeight * 3;

    char *pszDet = new char[nDataLen];
    memset(pszDet, 0, nDataLen);

    int i = 0;
    int j = 0;
    float u = 0.0;
    float v = 0.0;
    float t = 0.0;
    int r[5] = {0};
    int g[5] = {0};
    int b[5] = {0};

    for (int h = 0; h < fDestHeight; h++)
    {
        for (int w = 0; w < fDestWidth; w++)
        {
            t = h * fVScale;
            i = t;      // 取整数部分
            u = t - i;  // 取小数部分

            t = w * fUScale;
            j = t;
            v = t - j;

            GetPixelValue(m_pszData, nSrcLineDataLen, i,   j,   r[0], g[0], b[0]);
            GetPixelValue(m_pszData, nSrcLineDataLen, i,   j+1, r[1], g[1], b[1]);
            GetPixelValue(m_pszData, nSrcLineDataLen, i+1, j,   r[2], g[2], b[2]);
            GetPixelValue(m_pszData, nSrcLineDataLen, i+1, j+1, r[3], g[3], b[3]);

            r[4] = (1-u)*(1-v)*r[0] + (1-u)*v*r[1] + u*(1-v)*r[2] + u*v*r[3];
            g[4] = (1-u)*(1-v)*g[0] + (1-u)*v*g[1] + u*(1-v)*g[2] + u*v*g[3];
            b[4] = (1-u)*(1-v)*b[0] + (1-u)*v*b[1] + u*(1-v)*b[2] + u*v*b[3];

            SetPixelValue(pszDet, nDestLineDataLen, h, w, r[4], g[4], b[4]);
        }
    }


    //----------------------------------------------------------

    FILE *pFile = fopen(pszFileName, "wb");

    if (NULL == pFile)
    {
        return false;
    }

    BITMAPFILEHEADER BmpFileHaader = {0};
    BmpFileHaader.bfType = 0x4D42;	// "BM"
    BmpFileHaader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    BmpFileHaader.bfSize = BmpFileHaader.bfOffBits + fDestWidth*fDestHeight*3;

    BITMAPINFOHEADER BmpInfo = {0};
    BmpInfo.biSize = sizeof(BITMAPINFOHEADER);
    BmpInfo.biPlanes = 1;
    BmpInfo.biBitCount = 24;   // 24位BMP
    BmpInfo.biWidth = fDestWidth;
    BmpInfo.biHeight = fDestHeight;

    fwrite(&BmpFileHaader, sizeof(BITMAPFILEHEADER), 1, pFile);
    fwrite(&BmpInfo, sizeof(BITMAPINFOHEADER), 1, pFile);
    fwrite(pszDet, nDestLineDataLen*fDestHeight, 1, pFile);
    fclose(pFile);

	return true;
}

#pragma warning (default : 4244)