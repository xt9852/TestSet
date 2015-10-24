
#pragma once
#include "Sink.h"


class CWebInvoke
{
public:
    CWebInvoke();           // 动态创建所使用的受保护的构造函数
    virtual ~CWebInvoke();

protected:	
    CSink	m_sink;			// 接收器对象
    CEvent	m_evComplete;
    LONG	m_lErrorCode;

    void SetProxy(LPCSTR pszProxy);
    void UnenableProxy(void);

public:	
    DWORD OpenUrl(LPCSTR strUrl, LPSTR strProxy, DWORD dwTime);
};
