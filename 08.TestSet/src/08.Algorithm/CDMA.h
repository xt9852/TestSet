
#pragma once



class CDMA
{
public:
	CDMA();
	~CDMA();

protected:
    static const int walshLen_ = 8;

    static char walshMatrix_[walshLen_][walshLen_];
    static char walshInverseMatrix_[walshLen_][walshLen_];

public:
    int encode(unsigned int key, unsigned char *data, unsigned int len, unsigned char *buff, unsigned int buffLen);

    int decode(unsigned int key, unsigned char *data, unsigned int len, unsigned char *buff, unsigned int buffLen);
};