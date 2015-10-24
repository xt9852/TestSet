
#include "stdafx.h"
#include "G729.h"

extern "C" void va_g729a_init_encoder();
extern "C" void va_g729a_init_decoder();
extern "C" void va_g729a_encoder(short *speech, unsigned char *bitstream);
extern "C" void va_g729a_decoder(unsigned char *bitstream, short *synth_short, int bfi);
#define  L_FRAME_COMPRESSED 10
#define  L_FRAME            80

//#pragma comment(lib, "../lib/G729/G729a.lib")

CG729::CG729()
{
    //va_g729a_init_encoder();
    //va_g729a_init_decoder();
}

CG729::~CG729()
{
}

BOOL CG729::Encode(char *pin,int len,char* pout,int* lenr)
{
    BOOL bRet=FALSE;
    if (!pin||len!=SIZE_AUDIO_FRAME||!pout) goto RET;

    for (int i = 0; i < SIZE_AUDIO_PACKED/10; i++)
    {
        //va_g729a_encoder((short*)(pin+i*160),(BYTE*)(pout+i*10));
    }

    if (lenr) *lenr=SIZE_AUDIO_PACKED;

    bRet=TRUE;
RET:
    return bRet;
}

BOOL CG729::Decode(char *pin,int len,char* pout,int* lenr)
{
    BOOL bRet=FALSE;
    if (!pin||len!=SIZE_AUDIO_PACKED||!pout) goto RET;

    for (int i = 0; i < SIZE_AUDIO_PACKED/10; i++)
    {
        //va_g729a_decoder((BYTE*)(pin+i*10),(short*)(pout+i*160), 0);
    }


    if (lenr) *lenr=SIZE_AUDIO_FRAME;
    
    bRet=TRUE;
RET:
    return bRet;
}