
#include "stdafx.h"
#include "CDMA.h"

char CDMA::walshInverseMatrix_[walshLen_][walshLen_] = {0};
char CDMA::walshMatrix_[walshLen_][walshLen_] = 
{
    1,  1,  1,  1,  1,  1,  1,  1, 
    1,  1,  1,  1, -1, -1, -1, -1, 
    1,  1, -1, -1, -1, -1,  1,  1, 
    1,  1, -1, -1,  1,  1, -1, -1, 
    1, -1, -1,  1,  1, -1, -1,  1, 
    1, -1, -1,  1, -1,  1,  1, -1, 
    1, -1,  1, -1, -1,  1, -1,  1, 
    1, -1,  1, -1,  1, -1,  1, -1
};


CDMA::CDMA()
{
    for (int i = 0; i < walshLen_; i++)
    {
        for (int j = 0; j < walshLen_; j++)
        {
            walshInverseMatrix_[i][j] = -walshMatrix_[i][j];
        }
    }
}

CDMA::~CDMA()
{
}

bool getBit(unsigned char num, int pos)
{
    if (pos < 0 || pos > 7) return false;

    switch(pos)
    {
    case 0: return ((num & 0x01) > 0);
    case 1: return ((num & 0x02) > 0);
    case 2: return ((num & 0x04) > 0);
    case 3: return ((num & 0x08) > 0);
    case 4: return ((num & 0x10) > 0);
    case 5: return ((num & 0x20) > 0);
    case 6: return ((num & 0x40) > 0);
    case 7: return ((num & 0x80) > 0);
    }

    return false;
}

void setBit(unsigned char &num, int pos)
{
    if (pos < 0 || pos > 7) return;
    
    switch(pos)
    {
    case 0: num |= 0x01; break;
    case 1: num |= 0x02; break;
    case 2: num |= 0x04; break;
    case 3: num |= 0x08; break;
    case 4: num |= 0x10; break;
    case 5: num |= 0x20; break;
    case 6: num |= 0x40; break;
    case 7: num |= 0x80; break;
    }
}


int CDMA::encode(unsigned int key, unsigned char *data, unsigned int len, unsigned char *buff, unsigned int buffLen)
{
    if (NULL == data || NULL == buff || buffLen < (len * walshLen_ * 8) || key >= walshLen_) return -1;

    int pos = 0;

    for (int i = 0; i < len; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            memcpy(&buff[pos], 
                getBit(data[i], j)?walshMatrix_[key]:walshInverseMatrix_[key], 
                walshLen_);

            pos += walshLen_;
        }
    }

    return pos;
}

int CDMA::decode(unsigned int key, unsigned char *data, unsigned int len, unsigned char *buff, unsigned int buffLen)
{
    if (NULL == data || NULL == buff || buffLen < (len / walshLen_ / 8) || key >= walshLen_) return -1;

    int pos = 0;
    int temp = 0;

    for (int i = 0; i < len; i+=walshLen_*8)
    {
        pos = i / 8 / walshLen_;

        buff[pos] = 0;

        for (int j = 0; j < 8; j++)
        {
            temp = 0;

            for (int k = 0; k < walshLen_; k++)
            {
                temp += (char)data[i+j*8+k] * walshMatrix_[key][k];
            }

            if (temp == walshLen_)
            {
                setBit(buff[pos], 7-j);
            }
        }
    }

    return pos+1;
}