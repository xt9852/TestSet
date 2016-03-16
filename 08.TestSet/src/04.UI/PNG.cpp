
#include "StdAfx.h"
#include "PNG.h"
#include "Zip/zlib.h"

#pragma comment(lib, "vfw32.lib")


/**
 *\fn         CPNG()
 *\brief      缺省构造函数。
 */
CPNG::CPNG()
    :fileData_(NULL),
    fileLen_(0),
    data_(NULL),
    dataLen_(0),
    iher_(NULL),
    phys_(NULL),
    chrm_(NULL),
    gama_(NULL),
    srgb_(NULL),
    sbit_(NULL),
    time_(NULL),
    channelNum_(0),
    width_(0),
    height_(0)
{
}

/**
 *\fn         ~CPNG()
 *\brief      析构函数。
 */
CPNG::~CPNG()
{
    if (NULL != fileData_) delete fileData_;
    if (NULL != data_) delete data_;
}

/**
 *\fn         Load(const char *filname)
 *\brief      加载图片。
 *\param[in]  filname  图片文件名。
 *\return     是否成功
 */
bool CPNG::Load(const char *filname)
{
    if (NULL == filname) return false;

    FILE *file = NULL;

    fopen_s(&file, filname, "rb");

    if (NULL == file) return false;

    fseek(file, 0, SEEK_END);

    fileLen_ = ftell(file);

    if (NULL != fileData_) delete fileData_;

    fileData_ = new unsigned char[fileLen_];

    fseek(file, 0, SEEK_SET);

    fread(fileData_, fileLen_, 1, file);

    fclose(file);

    if (NULL != data_)
    {
        delete data_;
        data_ = NULL;
    }

    return ProcFile();
}

/**
 *\fn         Load(HMODULE m_hRes, int id)
 *\brief      加载图片。
 *\param[in]  m_hRes  如果为空从exe加载，否则从dll加载。
 *\param[in]  id      图片ID。
 *\return     是否成功
 */
bool CPNG::Load(HMODULE module, int id)
{
    HRSRC   res     = FindResource(module, MAKEINTRESOURCE(id), "PNG");
    HGLOBAL resData = LoadResource(module, (HRSRC)res);
    fileLen_        = SizeofResource(module, (HRSRC)res);

    if (NULL == resData)
    {
        return NULL;
    }

    fileData_ = new unsigned char[fileLen_];

    ::LockResource(resData);                // 锁定资源
    memcpy(fileData_, resData, fileLen_);   // 载入内存
    ::FreeResource(resData);                // 释放资源

    return ProcFile();
}

/**
 *\fn         ProcFile()
 *\brief      处理图片文件。
 *\return     是否成功
 */
bool CPNG::ProcFile()
{
    if (!ProcSig((const char*)fileData_)) return false;

    for (int i = sizeof(PngSig); i < fileLen_; )
    {
        PChunkDataHeader cdh = (PChunkDataHeader)(fileData_ + i);

        char name[10] = "";
        strncpy_s(name, cdh->type, 4);
        unsigned long len = getData(cdh->length);
        ATLTRACE("name:%s len:%d\n", name, len);

        if (0 == strncmp(cdh->type, "IHDR", 4))
        {
            ProcIHDR((const char*)(cdh + 1));
        }
        else if (0 == strncmp(cdh->type, "IDAT", 4))
        {
            ProcDATA((const char*)(cdh + 1), len);
        }
        else if (0 == strncmp(cdh->type, "IEND", 4))
        {
        }
        else if (0 == strncmp(cdh->type, "pHYs", 4))
        {
            phys_ = (PpHYs)(cdh + 1);
        }
        else if (0 == strncmp(cdh->type, "iCCP", 4))
        {
            ProcICCP((const char*)(cdh + 1), len);
        }
        else if (0 == strncmp(cdh->type, "cHRM", 4))
        {
            chrm_ = (PcHRM)(cdh + 1);
        }
        else if (0 == strncmp(cdh->type, "gAMA", 4))
        {
            gama_ = (PgAMA)(cdh + 1);
        }
        else if (0 == strncmp(cdh->type, "sRGB", 4))
        {
            srgb_ = (PsRGB)(cdh + 1);
        }
        else if (0 == strncmp(cdh->type, "sBIT", 4))
        {
            sbit_ = (PsBIT)(cdh + 1);
        }
        else if (0 == strncmp(cdh->type, "tIME", 4))
        {
            time_ = (PtIME)(cdh + 1);
        }
        else if (0 == strncmp(cdh->type, "tEXt", 4))
        {
            ProcTEXT((const char*)(cdh + 1), len);
        }

        i += 4 + 4 + len + 4;
    }

    UncompressDATA();

    return true;
}

/**
 *\fn         ProcSig(const char *data)
 *\brief      处理PNG文件头。
 *\param[in]  data  PNG文件头。
 *\return     是否成功
 */
bool CPNG::ProcSig(const char *data)
{
    PPngSig sig = (PPngSig)data;
    return (sig->signature == 0x0a1a0a0d474e5089);
}

/**
 *\fn         ProcIHDR(const char *data)
 *\brief      处理PNG文件IHDR节。
 *\param[in]  data     PNG文件IHDR节。
 *\param[in]  dataLen  PNG文件IHDR节数据长。
 *\return     是否成功
 */
bool CPNG::ProcIHDR(const char *data)
{
    if (NULL == data) return false;

    iher_ = (PIHDR)data;
    width_ = getData(iher_->width);
    height_ = getData(iher_->heigth);

    switch (iher_->colorType)
    {
    case 0: channelNum_ = 1; break;
    case 2: channelNum_ = 3; break;
    case 3: channelNum_ = 1; break;
    case 4: channelNum_ = 2; break;
    case 6: channelNum_ = 4; break;
    }

    return true;
}

/**
 *\fn         ProcICCP(const char *data, int dataLen)
 *\brief      处理PNG文件ICCP节。
 *\param[in]  data     PNG文件ICCP节。
 *\param[in]  dataLen  PNG文件ICCP节数据长。
 *\return     是否成功
 */
bool CPNG::ProcICCP(const char *data, int dataLen)
{
    strcpy_s(iccp_.name, data);
    int nameLen = strlen(iccp_.name);

    iccp_.compression = data[nameLen+1];

    if (0 == iccp_.compression) // 压缩的
    {
        int comprLen = dataLen - nameLen - 1 - 1;
        char *comprData = new char[comprLen];
        memcpy(comprData, data + nameLen + 1 + 1, comprLen);

        z_stream zstream = {0};
        int ret = inflateInit(&zstream);

        int outLen = comprLen * 100;
        iccp_.text = new char[outLen];
        memset(iccp_.text, 0, outLen);

        zstream.next_in  = (BYTE*)comprData;
        zstream.avail_in = comprLen;
        zstream.next_out = (BYTE*)iccp_.text; // 使用完后新分配了一块空间
        zstream.avail_out = outLen;

        ret = inflate(&zstream, Z_NO_FLUSH);

        delete comprData;

        ATLTRACE("iCCP: name:%s text:%s len:%d\n", iccp_.name, iccp_.text, outLen-zstream.avail_out);
    }

    return true;
}

/**
 *\fn         ProcTEXT(const char *data, int dataLen)
 *\brief      处理PNG文件TEXT节。
 *\param[in]  data     PNG文件TEXT节。
 *\param[in]  dataLen  PNG文件TEXT节数据长。
 *\return     是否成功
 */
bool CPNG::ProcTEXT(const char *data, int dataLen)
{
    strcpy_s(text_.keyword, data);
    int keyLen = strlen(text_.keyword);
    int textLen = dataLen - keyLen - 1;
    strncpy_s(text_.text, data + keyLen + 1, textLen);
    text_.text[textLen] = '\0';

    ATLTRACE("tEXt: keyword:%s text:%s\n", text_.keyword, text_.text);

    return true;
}

/**
 *\fn         ProcDATA()
 *\brief      处理PNG文件DATA节。
 *\return     是否成功
 */
bool CPNG::ProcDATA(const char *data, int dataLen)
{
    if (NULL == data_)
    {
        data_ = new unsigned char[(width_*4+1)*height_];
    }

    memcpy(&data_[dataLen_], data, dataLen);
    dataLen_ += dataLen;

    return true;
}

/**
 *\fn         UncompressDATA()
 *\brief      解压数据。
 *\return     是否成功
 */
bool CPNG::UncompressDATA()
{
    int rowLen = width_ * channelNum_;
    int imageLen = (rowLen + 1) * height_;
    unsigned char *image = new unsigned char[imageLen];

    z_stream zstream = {0};
    int ret = inflateInit(&zstream);
    zstream.next_in  = data_;
    zstream.avail_in = dataLen_;
    zstream.avail_out = imageLen;
    zstream.next_out = image; // 使用完后新分配了一块空间

    ret = inflate(&zstream, Z_NO_FLUSH);

    if (ret == Z_STREAM_END)
    {
        unsigned char *lastRow = NULL;
        unsigned char *row = NULL;

        for (int i = 0; i < height_; i++)
        {
            row = &image[i * (rowLen+1)];

            ProcFilter(&row[1], lastRow, rowLen, row[0]);

            lastRow = &row[1];

            ATLTRACE("row:%d filter:%d\n", i, row[0]);
        }

        ToBitmap(image);

        delete image;
        delete fileData_;
        fileData_ = NULL;
        fileLen_ = 0;

        return true;
    }

    return false;
}

/**
 *\fn         ProcFilter(unsigned char *row, const unsigned char *lastRow, int rowLen, int filterType)
 *\brief      处理图像数据。
 *\param[in]  row        本行数据。
 *\param[in]  lastRow    上一行数据。
 *\param[in]  rowLen     本行数据长。
 *\param[in]  filterType 过滤器类型。
 *\return     是否成功
 */
void CPNG::ProcFilter(unsigned char *row, const unsigned char *lastRow, int rowLen, int filterType)
{
    switch(filterType)
    {
    case 1:
        {
            unsigned char *lp = row;
            unsigned char *rp = &row[channelNum_];

            for (int i = channelNum_; i < rowLen; i++)
            {
                int a = *rp;
                int b = *lp;

                *rp = (a + b) & 0xFF;

                rp++;
                lp++;
            }

            break;
        }
    case 2:
        {
            const unsigned char *pp = lastRow;
            unsigned char *rp = row;

            for (int i = 0; i < rowLen; i++)
            {
                int a = *rp;
                int b = *pp;

                *rp = (a + b) & 0xFF;

                rp++;
                pp++;
            }

            break;
        }
    case 3:
        {
            const unsigned char *pp = lastRow;
            unsigned char *rp = row;
            unsigned char *lp = row;

            for (int i = 0; i < channelNum_; i++)
            {
                int a = *rp;
                int b = *pp;

                *rp = (a + (b/2)) & 0xFF;

                rp++;
                pp++;
            }

            for (int i = 0; i < rowLen - channelNum_; i++)
            {
                int a = *rp;
                int b = *pp;
                int c = *lp;

                *rp = (a + (b + c)/2) & 0xFF;

                rp++;
                pp++;
                lp++;
            }

            break;
        }
    case 4:
        {
            const unsigned char *pp = lastRow;
            const unsigned char *cp = lastRow;
            unsigned char *rp = row;
            unsigned char *lp = row;

            for (int i = 0; i < channelNum_; i++)
            {
                int a = *rp;
                int b = *pp;

                *rp = (BYTE)(a + b) & 0xFF;
                rp++;
                pp++;
            }

            for (int i = 0; i < rowLen - channelNum_; i++)
            {
                int a  = *lp++;
                int b  = *pp++;
                int c  = *cp++;
                int p  = b - c;
                int pc = a - c;

                int pa = p < 0 ? -p : p;
                int pb = pc < 0 ? -pc : pc;
                pc = (p + pc) < 0 ? -(p + pc) : p + pc;

                p = (pa <= pb && pa <= pc) ? a : (pb <= pc) ? b : c; // 最小值

                int d = *rp;

                *rp = (d + p) & 0xFF;
                rp++;
            }

            break;
        }
    }
}

/**
 *\fn         ToBitmap(const unsigned char *image)
 *\brief      将图像转成BITMAP图像。
 *\param[in]  image       本行数据。
 *\return     是否成功
 */
void CPNG::ToBitmap(const unsigned char *image)
{
    int bitCount = 24;
    int remain = (width_ * bitCount / 8) % 4;
    remain = remain?(4-remain):0;
    int bytes = (width_ * bitCount / 8 + remain) * height_;
    int index = 0;

    // BMP文件头
    BITMAPFILEHEADER bmpHead = {0};
    bmpHead.bfType = 0x4D42; // "BM"
    bmpHead.bfOffBits = sizeof(bmpHead) + sizeof(BITMAPINFOHEADER);
    bmpHead.bfSize = bmpHead.bfOffBits + bytes;

    // 图形格式参数
    BITMAPINFOHEADER bmpInfo = {0};
    bmpInfo.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.biWidth = width_;
    bmpInfo.biHeight = height_;
    bmpInfo.biPlanes = 1;
    bmpInfo.biBitCount = (WORD)bitCount;
    bmpInfo.biCompression = BI_RGB;
    bmpInfo.biSizeImage = 0;
    bmpInfo.biXPelsPerMeter = 0;
    bmpInfo.biYPelsPerMeter = 0;
    bmpInfo.biClrUsed = 0;
    bmpInfo.biClrImportant = 0;

    memcpy(data_, &bmpHead, sizeof(bmpHead));
    index += sizeof(bmpHead);

    memcpy(&data_[index], &bmpInfo, sizeof(bmpInfo));
    index += sizeof(bmpInfo);

    int rowLen = width_ * channelNum_;

    for (int i = height_-1; i >= 0; i--)
    {
        for (int j = 0; j < width_; j++)
        {
            int pos = i * (rowLen+1) + 1 + j * channelNum_;

            if ((4 == channelNum_) && (0 == image[pos + 3]))
            {
                data_[index++] = 255;
                data_[index++] = 255;
                data_[index++] = 255;
            }
            else
            {
                data_[index++] = image[pos + 2];
                data_[index++] = image[pos + 1];
                data_[index++] = image[pos + 0];
            }
        }

        for (int k = 0; k < remain; k++)
        {
            data_[index++] = 0;
        }
    }

    dataLen_ = index;
}

#include <Vfw.h>

/**
 *\fn         Draw(HDC dc, int x, int y)
 *\brief      将图片画到DC上。
 *\param[in]  dc  要载入图片的DC。
 *\param[in]  x   图片x坐标。
 *\param[in]  y   图片y坐标。
 *\return     是否成功
 */
bool CPNG::Draw(HDC dc, int x, int y)
{
    HDRAWDIB dib = DrawDibOpen();

    DrawDibBegin(dib, dc, -1, -1, (LPBITMAPINFOHEADER)&data_[sizeof(BITMAPFILEHEADER)], width_, height_, 0);

    DrawDibDraw(dib, dc, x, y, -1, -1, (LPBITMAPINFOHEADER)&data_[sizeof(BITMAPFILEHEADER)], 
        &data_[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)], 
        0, 0, width_, height_,DDF_SAME_DRAW);

    DrawDibEnd(dib);

    DrawDibClose(dib);

    return true;
}

/**
 *\fn         SaveBmp(const char *filname)
 *\brief      将图片存成BITMAP格式。
 *\param[in]  filname  图片文件名。
 *\return     是否成功
 */
bool CPNG::SaveBmp(const char *filname)
{
    if (NULL == filname) return false;

    FILE *file = NULL;

    fopen_s(&file, filname, "w+b");

    if (NULL == file) return false;

    fwrite(data_, dataLen_, 1, file);

    fclose(file);

    return true;
}