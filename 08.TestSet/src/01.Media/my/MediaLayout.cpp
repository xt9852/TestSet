
#include "StdAfx.h"
#include "MediaLayout.h"


/**
 *\fn         MeidaLayout()
 *\brief      缺省构造函数。
 */
MeidaLayout::MeidaLayout()
    :pre_(NULL),
    next_(NULL)
{
}

/**
 *\fn         ~MeidaLayout()
 *\brief      析构函数。
 */
MeidaLayout::~MeidaLayout()
{
}

/**
 *\fn         int send(void *data)
 *\brief      发送数据。
 *\param[in]  data           数据包。
 *\return     是否成功,0成功,其它失败。
 */
int MeidaLayout::send(void *data)
{
    if (NULL == next_ || NULL == data) return -1;

    return next_->send(data);
}

/**
 *\fn         int recv(void *data)
 *\brief      接收数据。
 *\param[in]  data           数据包。
 *\return     是否成功,0成功,其它失败。
 */
int MeidaLayout::recv(void *data)
{
    if (NULL == pre_ || NULL == data) return -1;

    return pre_->recv(data);
}
