/*------------------------------------------------------------------------------*\
[模块名称]
CG729

[文件名称]
G729.h

[相关文件]
G729.cpp

[目的] 
方便音频解压缩 

[描述]
封装 g.729 api

[依赖性]
G729a.lib

\*------------------------------------------------------------------------------*/

#ifndef _G729_H_
#define _G729_H_

//#define SIZE_AUDIO_FRAME 960
//#define SIZE_AUDIO_PACKED 60
#define SIZE_AUDIO_FRAME 15840
#define SIZE_AUDIO_PACKED 990

class CG729
{
public:
    virtual  ~CG729();
    CG729();

    BOOL Encode(char *pin,int len,char* pout,int* lenr);
    BOOL Decode(char *pin,int len,char* pout,int* lenr);
};


#endif