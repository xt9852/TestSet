#pragma once


class CScaleBmp
{
public:
	CScaleBmp(void);
	~CScaleBmp(void);

private:
    BITMAPFILEHEADER m_BmpFileHeader;
    BITMAPINFOHEADER m_BmpInfoHeader;
    char             *m_pszData;

protected:
	void GetPixelValue(char* pszData, int nWidthLen, int i, int j, int &r, int &g, int &b);
    void SetPixelValue(char* pszData, int nWidthLen, int i, int j, int r, int g, int b);

public:
	bool Load(const char *pszFileName);
	bool SaveBmp(const char *pszFileName, float fScaleX, float fScaleY);
};
