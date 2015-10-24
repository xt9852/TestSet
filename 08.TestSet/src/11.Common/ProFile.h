
#pragma once
#include "ComputerInfo.h"
#include <list>
#include <string>

typedef std::list<std::string> STRING_LIST;

class CProFile
{
public:
    CProFile();
    ~CProFile();

protected:
    std::string  path_;
    CImageList   imageList_;
    ComputerInfo computerInfo_;

public:
    void Init(STRING_LIST &list);

    const char* getIp(int id) { return computerInfo_.getIpStr(id); }

    const char* getPath() { return path_.c_str(); }

    CImageList* getImageList() { return &imageList_; }
};