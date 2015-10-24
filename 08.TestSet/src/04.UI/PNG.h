
#pragma once
#include <list>


#pragma pack(push)  // 保存对齐状态 
#pragma pack(1)     // 设定为1字节对齐

// PNG文件格式中的数据块
// 数据块符号 数据块名称      多数据块 可选否 位置限制
// IHDR      文件头数据块           否     否 第一块
// cHRM      基色和白色点数据块     否     是 在PLTE和IDAT之前
// gAMA      图像γ数据块           否     是 在PLTE和IDAT之前
// sBIT      样本有效位数据块       否     是 在PLTE和IDAT之前
// PLTE      调色板数据块           否     是 在IDAT之前
// bKGD      背景颜色数据块         否     是 在PLTE之后IDAT之前
// hIST      图像直方图数据块       否     是 在PLTE之后IDAT之前
// tRNS      图像透明数据块         否     是 在PLTE之后IDAT之前
// oFFs      (专用公共数据块)       否     是 在IDAT之前
// pHYs      物理像素尺寸数据块     否     是 在IDAT之前
// sCAL      (专用公共数据块)       否     是 在IDAT之前
// IDAT      图像数据块             是     否 与其他IDAT连续
// tIME      图像最后修改时间数据块 否     是 无限制
// tEXt      文本信息数据块         是     是 无限制
// zTXt      压缩文本数据块         是     是 无限制
// fRAc      (专用公共数据块)       是     是 无限制
// gIFg      (专用公共数据块)       是     是 无限制
// gIFt      (专用公共数据块)       是     是 无限制
// gIFx      (专用公共数据块)       是     是 无限制
// IEND      图像结束数据           否     否 最后一个数据块



typedef struct tagPngSig
{
    __int64 signature;  // "89 50 4e 47 0d 0a 1a 0a "

}PngSig, *PPngSig;

// 数据块头
// Length(长度) 4字节 指定数据块中数据域的长度
// Chunk Type Code(数据块类型码) 4字节 数据块类型码由ASCII字母(A-Z和a-z)组成 
// Chunk Data(数据块数据) 可变长度 存储按照Chunk Type Code指定的数据 
// CRC(循环冗余检测) 4字节 存储用来检测是否有错误的循环冗余码,对Chunk Type Code域和Chunk Data域中的数据进行计算得到的
typedef struct tagChunkDataHeader
{
    unsigned long length;
    char type[4];

}ChunkDataHeader, *PChunkDataHeader;

// 文件头数据块
// Width	            4 bytes 图像宽度，以像素为单位
// Height	            4 bytes 图像高度，以像素为单位
// Bit depth            1 byte  图像深度：
//                              0：索引彩色图像：1，2，4或8
//                              1：灰度图像：1，2，4，8或16
//                              2：真彩色图像：8或16
// ColorType            1 byte  颜色类型：
//                              0：灰度图像, 1通道
//                              2：真彩色图像，3通道
//                              3：索引彩色图像，1通道
//                              4：带α通道数据的灰度图像，2通道
//                              6：带α通道数据的真彩色图像，4通道
// Compression method   1 byte  压缩方法(LZ77派生算法)
// Filter method        1 byte  滤波器方法
// Interlace method     1 byte  隔行扫描方法：
//                              0：非隔行扫描
//                              1： Adam7(由Adam M. Costello开发的7遍隔行扫描方法)

typedef struct tagIHDR
{
    unsigned long width;
    unsigned long heigth;
    unsigned char bitDepth;
    unsigned char colorType;
    unsigned char compression;
    unsigned char filter;
    unsigned char interlace;

}IHDR, *PIHDR;


// Pixels per unit, X axis 4 bytes (PNG unsigned integer) 每米像素数
// Pixels per unit, Y axis 4 bytes (PNG unsigned integer) 
// Unit specifier 1 byte 
//  The following values are defined for the unit specifier: 指定单位
//  0 unit is unknown 
//  1 unit is the metre 米

typedef struct tagpHYs
{
    unsigned long x;
    unsigned long y;
    unsigned char specifier;

}pHYs, *PpHYs;

// Profile name 1-79 bytes (character string) 
//  Null separator 1 byte (null character) 
//  Compression method 1 byte  0表示deflate压缩
//  Compressed profile n bytes 

typedef struct tagiCCP
{
    char name[80]; // 是一个以'\0'结尾的字符串,不定长
    unsigned char compression;
    char *text;

}iCCP, *PiCCP;


// White point x 4 bytes 
// White point y 4 bytes 
// Red x 4 bytes 
// Red y 4 bytes 
// Green x 4 bytes 
// Green y 4 bytes 
// Blue x 4 bytes 
// Blue y 4 bytes 

typedef struct tagcHRM
{
    unsigned long whiteX;
    unsigned long whiteY;
    unsigned long redX;
    unsigned long redY;
    unsigned long greenX;
    unsigned long greenY;
    unsigned long blueX;
    unsigned long blueY;

}cHRM, *PcHRM;

// 伽玛校正就是对图像的伽玛曲线进行编辑，以对图像进行非线性色调编辑的方法，
// 检出图像信号中的深色部分和浅色部分，并使两者比例增大，从而提高图像对比度效果。
// 但是不幸的一件事是各个平台的gamma修正值是不一样的。window上Gamma系数为2.2，
// Mac上Gamma为1.8。Gamma修正意味着对于每一个R/G/B，它们必须被转换到R’=Rgamma，
// G’=Ggamma，B’=Bgamma，然后再传递到操作系统。

// Image gamma 4 bytes 
typedef struct taggAMA
{
    unsigned long gamma;

}gAMA, *PgAMA;


// Rendering intent 1 byte 
// 
// The following values are defined for rendering intent:
// 
// 0 Perceptual for images preferring good adaptation to the output device gamut at the expense of colorimetric accuracy, such as photographs. 
// 1 Relative colorimetric for images requiring colour appearance matching (relative to the output device white point), such as logos. 
// 2 Saturation for images preferring preservation of saturation at the expense of hue and lightness, such as charts and graphs. 
// 3 Absolute colorimetric for images requiring preservation of absolute colorimetry, such as previews of images destined for a different output device (proofs). 

typedef struct tagsRGB
{
    unsigned char rendering;

}sRGB, *PsRGB;


// 当IHDR的Colour type

// Colour type 0 
//  significant greyscale bits 1 byte 
// Colour types 2 and 3 
//  significant red bits 1 byte 
//  significant green bits 1 byte 
//  significant blue bits 1 byte 
// Colour type 4 
//  significant greyscale bits 1 byte 
//  significant alpha bits 1 byte 
// Colour type 6 
//  significant red bits 1 byte 
//  significant green bits 1 byte 
//  significant blue bits 1 byte 
//  significant alpha bits 1 byte 

typedef struct tagsBIT
{

}sBIT, *PsBIT;


// Colour types 0 and 4 
//  Greyscale 2 bytes 
// Colour types 2 and 6 
//  Red 2 bytes 
//  Green 2 bytes 
//  Blue 2 bytes 
// Colour type 3 
//  Palette index 1 byte 

typedef struct tagbKGD
{

}bKGD, *PbKGD;


typedef struct tagoFFs
{

}oFFs, *PoFFs;

// Year 2 bytes (complete; for example, 1995, not 95) 
//  Month 1 byte (1-12) 
//  Day 1 byte (1-31) 
//  Hour 1 byte (0-23) 
//  Minute 1 byte (0-59) 
//  Second 1 byte (0-60) (to allow for leap seconds) 
typedef struct tagtIME
{
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;

}tIME, *PtIME;

// Keyword 1-79 bytes (character string) 
//  Null separator 1 byte (null character) 
//  Text string 0 or more bytes (character string) 
typedef struct tagtEXt
{
    char keyword[80];
    char text[MAX_PATH]; // 数据长 = 本节总数据长 - keyword长 -1

}tEXt, *PtEXt;

// Keyword 1-79 bytes (character string) 
//  Null separator 1 byte (null character) 
//  Compression method 1 byte 是否压缩
//  Compressed text datastream n bytes 
typedef struct tagzTXt
{
    char keyword[80];
    unsigned char compression;
    char compressed[MAX_PATH];

}zTXt, *PzTXt;

// Keyword 1-79 bytes (character string) 
//  Null separator 1 byte (null character) 
//  Compression flag 1 byte 
//  Compression method 1 byte 
//  Language tag 0 or more bytes (character string) 
//  Null separator 1 byte (null character) 
//  Translated keyword 0 or more bytes 
//  Null separator 1 byte (null character) 
//  Text 0 or more bytes 
typedef struct tagiTXt
{
    char keyword[80];
    unsigned char compression;
    unsigned char compressed;
    char language[80];
    char translated[80];
    char text[80];

}iTXt, *PiTXt;


//pCAL sTER vpAg 

#pragma pack(pop)   // 恢复对齐状态


typedef std::list<void*> LIST_VOID; // 内部存,ChunkDataHeader指针


/**
 *\class  CPNG
 *\brief  该类主要用于显示PNG图片
 *\date   2012-06-25
 *\author 张海涛
 *\par    Revision History:
 */
class CPNG
{
public:
    /**
     *\fn         CPNG()
     *\brief      缺省构造函数。
     */
    CPNG();

    /**
     *\fn         ~CPNG()
     *\brief      析构函数。
     */
    ~CPNG();

private:
    unsigned char   *fileData_; // PNG文件数据
    int             fileLen_;   // PNG文件数据长

    unsigned char   *data_;     // BMP文件数据
    int             dataLen_;   // BMP文件数据长

    PIHDR           iher_;      // 头节
    PpHYs           phys_;      // 物理节
    iCCP            iccp_;      // 嵌入信息
    PcHRM           chrm_;      // 白点信息
    PgAMA           gama_;      // gama校正
    PsRGB           srgb_;      // RGB信息
    PsBIT           sbit_;      // BIT信息
    PtIME           time_;      // 时间
    tEXt            text_;      // 文本信息

    int             channelNum_;// 通过数
    int             width_;     // 图片宽
    int             height_;    // 图片高

    /**
     *\fn         ProcFile()
     *\brief      处理图片文件。
     *\return     是否成功
     */
    bool ProcFile();

    /**
     *\fn         ProcSig(const char *data)
     *\brief      处理PNG文件头。
     *\param[in]  data  PNG文件头。
     *\return     是否成功
     */
    bool ProcSig(const char *data);

    /**
     *\fn         ProcIHDR(const char *data)
     *\brief      处理PNG文件IHDR节。
     *\param[in]  data     PNG文件IHDR节。
     *\return     是否成功
     */
    bool ProcIHDR(const char *data);

    /**
     *\fn         ProcICCP(const char *data, int dataLen)
     *\brief      处理PNG文件ICCP节。
     *\param[in]  data     PNG文件ICCP节。
     *\param[in]  dataLen  PNG文件ICCP节数据长。
     *\return     是否成功
     */
    bool ProcICCP(const char *data, int dataLen);

    /**
     *\fn         ProcTEXT(const char *data, int dataLen)
     *\brief      处理PNG文件TEXT节。
     *\param[in]  data     PNG文件TEXT节。
     *\param[in]  dataLen  PNG文件TEXT节数据长。
     *\return     是否成功
     */
    bool ProcTEXT(const char *data, int dataLen);

    /**
     *\fn         ProcDATA(const char *data, int dataLen)
     *\brief      处理PNG文件DATA节。
     *\param[in]  data     PNG文件DATA节。
     *\param[in]  dataLen  PNG文件DATA节数据长。
     *\return     是否成功
     */
    bool ProcDATA(const char *data, int dataLen);

    /**
     *\fn         UncompressDATA()
     *\brief      解压数据。
     *\return     是否成功
     */
    bool UncompressDATA();

    /**
     *\fn         ProcFilter(unsigned char *row, const unsigned char *lastRow, int rowLen, int filterType)
     *\brief      处理一行图像数据。
     *\param[in]  row        本行数据。
     *\param[in]  lastRow    上一行数据。
     *\param[in]  rowLen     本行数据长。
     *\param[in]  filterType 过滤器类型。
     *\return     是否成功
     */
    void ProcFilter(unsigned char *row, const unsigned char *lastRow, int rowLen, int filterType);

    /**
     *\fn         ToBitmap(const unsigned char *image)
     *\brief      将图像转成BITMAP图像。
     *\param[in]  image       本行数据。
     *\return     是否成功
     */
    void ToBitmap(const unsigned char *image);

    /**
     *\fn         getData(unsigned long data)
     *\brief      将大头顺序改变小头顺序。
     *\param[in]  data  数据。
     *\return     小头数据
     */
    unsigned long getData(unsigned long data)
    {
        unsigned long n1 = (data & 0xFF000000) >> 24;
        unsigned long n2 = (data & 0x00FF0000) >> 8;
        unsigned long n3 = (data & 0x0000FF00) << 8;
        unsigned long n4 = (data & 0x000000FF) << 24;

        return n1 | n2 | n3 | n4;
    }

public:
    /**
     *\fn         Load(HMODULE module, int id)
     *\brief      加载图片。
     *\param[in]  molule  如果为空从exe加载，否则从dll加载。
     *\param[in]  id      图片ID。
     *\return     是否成功
     */
    bool Load(HMODULE module, int id);

    /**
     *\fn         Load(const char *filname)
     *\brief      加载图片。
     *\param[in]  filname  图片文件名。
     *\return     是否成功
     */
    bool Load(const char *filname);

    /**
     *\fn         Draw(HDC dc, int x, int y)
     *\brief      将图片画到DC上。
     *\param[in]  dc  要载入图片的DC。
     *\param[in]  x   图片x坐标。
     *\param[in]  y   图片y坐标。
     *\return     是否成功
     */
    bool Draw(HDC dc, int x, int y);

    /**
     *\fn         SaveBmp(const char *filname)
     *\brief      将图片存成BITMAP格式。
     *\param[in]  filname  图片文件名。
     *\return     是否成功
     */
    bool SaveBmp(const char *filname);

    /**
     *\fn         getWidth()
     *\brief      得到图片宽。
     *\return     图片宽
     */
    int getWidth() { return width_; }

    /**
     *\fn         getHeight()
     *\brief      得到图片高。
     *\return     图片高
     */
    int getHeight() { return height_; }

    /**
     *\fn         getData()
     *\brief      得到图片数据。
     *\return     图片数据
     */
    unsigned char * getData() { return data_; }

    /**
     *\fn         getBmpInfo()
     *\brief      得到位图结构数据。
     *\return     位图结构数据
     */
    BITMAPINFOHEADER* getBmpInfo() { return (BITMAPINFOHEADER*)&data_[sizeof(BITMAPFILEHEADER)]; }
};
