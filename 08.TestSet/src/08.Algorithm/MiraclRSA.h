#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    #include "miracl/miracl.h"

#ifdef __cplusplus
}
#endif


class MiraclRSA
{
public:
    MiraclRSA(void);
    ~MiraclRSA(void);

protected:
    big _p;
    big _q;
    big _n;
    big _pn;
    big _d;
    big _e;
    miracl *_mip;

public:
    int GetPublicKey(int num, char *key, int &keyBufLen);

    int GetPrivateKey(int numP, int numQ, char *key, int &keyBufLen, bool save);

    int Encode(char *data, int dataLen, char *buff, int &buffLen);

    int Decode(char *data, int dataLen, char *buff, int &buffLen);
};

