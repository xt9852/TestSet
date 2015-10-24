#pragma once

class CXTDC;

class CXTUI
{
public:
	CXTUI();
	~CXTUI();

public:
	CXTDC *xtDC_;
	
	HDC	dc_;		// 窗体DC
	HDC	compDC_;	// 兼容图像DC
	HDC	imageDC_;	// 背景图像DC

	int x_;			// X坐标
	int y_;			// Y坐标
	int cx_;		// 宽
	int cy_;		// 高
	int sx_;		// 原图X坐标
	int sy_;		// 原图Y坐标
};
