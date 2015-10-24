#pragma once
#include <math.h>

#pragma pack(push)	// 保存对齐状态 
#pragma pack(1)		// 设定为1字节对齐

typedef struct _tagColorTable
{
	BYTE byR;
	BYTE byG;
	BYTE byB;

}COLORTABLE,*PCOLORTABLE;

typedef struct _tagGraphicControlExtension	// 需要89a版本
{
	BYTE byFlag1;							// 0x21,扩展块
	BYTE byFlag2;							// 0xF9,图形控制扩展块
	BYTE byBlockSize;						// 块大小,不包括块终结器
	struct flag{
		BYTE t:1;							// 是否应用透明色标志
		BYTE i:1;							// 用户输入标志
		BYTE s:3;							// 0不处理,1图形从当前位置移去,2回复到背景色,3回复到以前状态
		BYTE o:3;							// 保留
	}Flag;
	WORD wDelayTime;						// 延迟时间,单位1/100秒
	BYTE byTransparentColorIndex;			// 透明色索引值
	BYTE byBlockTerminator;					// 块终结器,固定值0

}GRAPHICCONTROLEX,*PGRAPHICCONTROLEX;

typedef struct _tagCommentExtension			// 需要89a版本
{
	BYTE byFlag1;							// 0x21,扩展块
	BYTE byFlag2;							// 0xFE,注释扩展块
	BYTE byTextLen;							// 注释长
	CHAR szText[256];						// 注释块(n个7bit ASCII字符字,英文)
	BYTE byBlockTerm;						// 块终结器,固定值0
}COMMENTEX,*PCOMMENTEX;

typedef struct _tagPlainTextExtension		// 需要89a版本
{
	BYTE byFlag1;							// 0x21,扩展块
	BYTE byFlag2;							// 0x01,图形文本扩展块
	BYTE byBlockSize;						// 0x0c,块大小
	BYTE byOffsetX;							// 文本框离逻辑屏幕的左边界距离
	BYTE byOffsetY;							// 文本框离逻辑屏幕的上边界距离
	BYTE byWidth;							// 文本框高度
	BYTE byHeight;							// 文本框高度
	BYTE byCelWidth;						// 字符单元格宽度
	BYTE byCelHeight;						// 字符单元格高度
	BYTE byTestColor;						// 字符在全局颜色列表中的索引
	BYTE byBackColor;						// 字符背景在全局颜色列表中的索引
	CHAR szText[256];						// 字符串(n个)
	BYTE byBlockTerm;						// 块终结器,固定值0

}PLAINTEXTEX,*PPLAINTEXTEX;

typedef struct _tagApplicationExtension		// 需要89a版本
{
	BYTE byFlag1;							// 0x21,扩展块
	BYTE byFlag2;							// 0xFF,应用扩展块
	BYTE byBlockSize;						// 0x0b,块大小
	BYTE byIdentifier[8];					// 应用程序自身的标识(8个连续ASCII字符)
	BYTE byCode[3];							// 应用程序定义的特殊标识码(3个连续ASCII字符)
	BYTE byDataLen;							// 数据长
	BYTE byData[256];						// 应用程序自定义数据块,一个或多个数据块组成
	BYTE byBlockTerm;						// 块终结器,固定值0

}APPEX,*PAPPEX;

typedef struct _tagHeader
{
	BYTE bySignature[3];					// "GIF"
	BYTE byVersion[3];						// "87a" 或 "89a"

}GIFHEADER, *PGIFHEADER;

typedef struct _tagScrDesc					// 逻辑屏幕描述块
{
	WORD wWidth;							// 总的宽度
	WORD wHeight;							// 总的高度
	struct globalflag
	{
		BYTE PalBits : 3;					// 全局颜色列表大小，PalBits+1确定颜色列表的索引数（2的PalBits+1次方）
		BYTE SortFlag : 1;					// 表明全局调色板中的RGB颜色值是否按照使用率进行从高到底的次序排序的
		BYTE ColorRes : 3;					// 颜色深度，ColorRes+1确定图象的颜色深度
		BYTE GlobalPal : 1;					// 全局颜色列表标志，当置位时表示有全局颜色列表，pixel值有意义
	}GlobalFlag;
	BYTE byBackground;						// 背景颜色索引
	BYTE byAspect;							// 像素宽高比

}GIFSCRDESC, *PGIFSCRDESC;

typedef struct _tagDataSubBlock
{
	BYTE			byDataLen;
	BYTE			pbyData[256];
	_tagDataSubBlock *pNext;

}DATASUBBLOCK, *PDATASUBBLOCK;

typedef struct _tagImage
{
	BYTE byFlag;							// 0x2C
	WORD wLeft;								// 与整个图像左边的距离
	WORD wTop;								// 与整个图像上边的距离
	WORD wWidth;							// 小图像的宽
	WORD wHeight;							// 小图像的高
	struct localflag
	{
		BYTE PalBits : 3;					// 局部颜色列表大小，PalBits+1确定颜色列表的索引数（2的PalBits+1次方）
		BYTE Reserved : 2;					// 保留,必须初始化为0
		BYTE SortFlag : 1;					// 表明局部调色板中的RGB颜色值是否按照使用率进行从高到底的次序排序的
		BYTE Interlace : 1;					// 交织标志,置位时图象数据使用连续方式排列，否则使用顺序排列。
		BYTE LocalPal : 1;					// 局部颜色列表标志,值否时使用全局颜色列表
	}LocalFlag;

	UINT			nColorNum;				// 本地颜色表颜色数
	COLORTABLE		LocolColorTable[255];	// 颜色表
	BYTE			byLZWcode;				// 数据位大小，在gif通常为1,4,8
	UINT			nDataBlcokNum;			// 子数据块数
	PDATASUBBLOCK	pData;					// 子数据块

}GIFIMAGE, *PGIFIMAGE;

typedef struct _tagFrame
{
	GRAPHICCONTROLEX gce;					// 图像控制块
	GIFIMAGE		 gi;					// 一帧图像
	_tagFrame*		 pNext;					// 下一帧

	BYTE			 byFrameId;				// 帧ID
	BYTE*			 pBmpData;				// 转成BMP文件的数据 

}GIFFRAME, *PGIFFRAME;

typedef struct _tagGIF
{
	GIFHEADER		Head;					// 文件头块
	GIFSCRDESC		ScrDesc;				// 逻辑屏幕描述块
	UINT			nColorNum;				// 全局颜色表的颜色数
	COLORTABLE		GlobalColorTable[256];	// 全局颜色表
	UINT			nGifFrameNum;			// 帧数
	PGIFFRAME		pGifFrame;				// 帧数据

	BITMAPINFO		BmpInfo;				// BMP文件信息头

}GIF,*PGIF;

#pragma pack(pop)	// 恢复对齐状态

//-------------------------------------------------------------------------------------------------------

/**
 *\class  CGIF
 *\brief  该类主要用于显示GIF图片
 *\date   2012-06-25
 *\author 张海涛
 *\par    Revision History:
 */
class CGIF
{
public:
	/**
	 *\fn         CGIF()
	 *\brief      缺省构造函数。
	 */
	CGIF();

	/**
	 *\fn         ~CGIF()
	 *\brief      析构函数。
	 */
	~CGIF();

private:
	GIF	gif_;

protected:
	/**
	 *\fn         DecodeImageData(PGIFFRAME frame)
	 *\brief      LZW压缩算法的解码数据。
	 *\param[in]  pFrame  帧数据。
	 *\return     是否成功
	 */
	LPBYTE DecodeImageData(PGIFFRAME frame);

	/**
	 *\fn         GetFrameBmpData(PGIFFRAME frame, PGIFFRAME lastFrame)
	 *\brief      得到位图数据。
	 *\param[in]  frame      帧数据。
	 *\param[in]  lastFrame  上一帧数据。
	 *\return     是否成功
	 */
	LPBYTE GetFrameBmpData(PGIFFRAME frame, PGIFFRAME lastFrame);

	/**
	 *\fn         ProcData(unsigned char *data)
	 *\brief      处理GIF文件。
	 *\param[in]  data  文件数据。
	 *\return     是否成功
	 */
	bool ProcData(unsigned char *data);

public:
	/**
	 *\fn         Load(const char *filename)
	 *\brief      加载文件。
	 *\param[in]  filename  文件名。
	 *\return     是否成功
	 */
	bool Load(const char *filename);

	/**
	 *\fn         Unload()
	 *\brief      清空数据。
	 */
	void Unload();

	/**
	 *\fn         Draw(HDC dc, int x, int y, int frameId)
	 *\brief      将图片画到DC上。
	 *\param[in]  dc        要载入图片的DC。
	 *\param[in]  x         图片x坐标。
	 *\param[in]  y         图片y坐标。
	 *\param[in]  frameId   图片帧ID。
	 *\return     是否成功
	 */
	bool Draw(HDC dc, int x, int y, int frameId);

	/**
	 *\fn         SaveBmp(const char *filname, int frameId)
	 *\brief      将图片存成BITMAP格式。
	 *\param[in]  filname  图片文件名。
	 *\param[in]  frameId   图片帧ID。
	 *\return     是否成功
	 */
	bool SaveBmp(const char *filename, int frameId);

	/**
	 *\fn         getWidth()
	 *\brief      得到图片宽。
	 *\return     图片宽
	 */
	int getWidth() { return gif_.ScrDesc.wWidth;; }

	/**
	 *\fn         getHeight()
	 *\brief      得到图片高。
	 *\return     图片高
	 */
	int getHeight() { return gif_.ScrDesc.wHeight; }

	/**
	 *\fn         getFrameCount()
	 *\brief      得到图片帧数。
	 *\return     图片帧数
	 */
	int getFrameCount() { return gif_.nGifFrameNum; }

	/**
	 *\fn         getDelayTime()
	 *\brief      得到间隔时间。
	 *\return     间隔时间
	 */
	int getDelayTime(int frameId);	
};
