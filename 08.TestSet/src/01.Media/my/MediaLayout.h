
#pragma once

typedef struct _tagFRAMEINFO
{
    BYTE type;      // 1音频,2视频
    WORD sleep;     // 等待时间
    int  len;       // 帧数据长,后跟数据
    void *data;     // 数据

} FRAMEINFO, *PFRAMEINFO;

/**
 *\class  MeidaLayout
 *\brief  该类主要是层基础类
 *\date   2012-12-26
 *\author 张海涛
 *\par    Revision History:
 */
class MeidaLayout
{
public:
    /**
     *\fn         P2PLayoutBase()
     *\brief      缺省构造函数。
     */
    MeidaLayout();

    /**
     *\fn         ~P2PLayoutBase()
     *\brief      析构函数。
     */
    ~MeidaLayout();

protected:
    MeidaLayout *pre_;  // 上一个节点
    MeidaLayout *next_; // 下一个节点

public:
    /**
     *\fn         int send(void *data)
     *\brief      发送数据。
     *\param[in]  data           数据包。
     *\return     是否成功,0成功,其它失败。
     */
    virtual int send(void *data);

    /**
     *\fn         int recv(void *data)
     *\brief      接收数据。
     *\param[in]  data           数据包。
     *\return     是否成功,0成功,其它失败。
     */
    virtual int recv(void *data);

    /**
     *\fn         void setPre(MeidaLayout *layout)
     *\brief      设置上一层节点。
     *\param[in]  layout        层节点。
     *\return     无。
     */
    void setPre(MeidaLayout *layout) { pre_ = layout; }

    /**
     *\fn         void setNext(MeidaLayout *layout)
     *\brief      设置下一层节点。
     *\param[in]  layout        层节点。
     *\return     无。
     */
    void setNext(MeidaLayout *layout) { next_ = layout; }

    /**
     *\fn         MeidaLayout* getPre()
     *\brief      得到上一层节点。
     *\param[in]  无。
     *\return     上一层节点指针。
     */
    MeidaLayout* getPre() { return pre_; }

    /**
     *\fn         MeidaLayout* getNext()
     *\brief      得到下一层节点。
     *\param[in]  无。
     *\return     下一层节点指针。
     */
    MeidaLayout* getNext() { return next_; }

};

