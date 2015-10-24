
#include "stdafx.h"
#include "P2PApplication.h"


namespace XT_P2P
{

	/**
	 *\fn         P2PApplication()
	 *\brief      默认构造函数。
	 */
	P2PApplication::P2PApplication()
		:thread_(NULL),
		running_(false)
	{
	}

	/**
	 *\fn         ~P2PApplication()
	 *\brief      析构函数。
	 */
	P2PApplication::~P2PApplication()
	{
		Stop();
	}

	/**
	 *\fn         Start(LPCTSTR rootPath, LPCTSTR ip, LPCTSTR port)
	 *\brief      开始运行服务。
	 *\param[in]  rootPath  文件根路径。
     *\param[in]  ip        IP地址。
	 *\return     是否成功(0成功，其它失败)
	 */
	int P2PApplication::Start(LPCTSTR rootPath, LPCTSTR ip, LPCTSTR port)
	{
        if (running_ || NULL == rootPath || NULL == ip || NULL == port) return -1;

        running_ = true;

		unsigned int threadID = 0;
		thread_ = (HANDLE)_beginthreadex(NULL, 0, ProcessPackThread, this, 0, &threadID);

        if (NULL == thread_) return -2;

#ifdef _DEBUG
        buffPool_.name_ = _T("P2PEnginerBuffPool");
#endif // _DEBUG
        
        buffPool_.setSize(1300);
		inputQueue_.Start();

        int ret = enginer_.init(&buffPool_, &inputQueue_, rootPath);

        if (0 != ret) goto end;

        ret = enginer_.addListen(ip, _ttoi(port));

        if (0 != ret) goto end;

        return ret;

end:
        running_ = false;
        return ret;
	}

	/**
	 *\fn         Stop()
	 *\brief      停止运行服务。
	 */
	void P2PApplication::Stop()
	{
        if (!running_) return;

		running_ = false;

		inputQueue_.Stop();

        enginer_.stop();

		StopThread(thread_);

        thread_ = NULL;
	}

	/**
	 *\fn         Stop(HANDLE thread)
	 *\brief      停止线程。
	 *\param[in]  thread  线程句柄。
	 */
	void P2PApplication::StopThread(HANDLE thread)
	{
        if (NULL == thread) return;

        int i = 10;
        for (; i > 0; i--)
        {
            int code = 0;
            if (!GetExitCodeThread(thread, (LPDWORD)&code) || (code != STILL_ACTIVE))
            {
                break;
            }

            Sleep(50);
        }

        if (i == 0)
        {
            TRACE("WARNING: Terminating Thread. %d\n", thread);
            TerminateThread(thread, 301);
        }

        CloseHandle(thread);
    }

	/**
	 *\fn         ProcessPackThread(LPVOID pParam)
	 *\brief      处理线程。
	 *\param[in]  param  线程参数。
	 *\return     是否成功(0成功，其它失败)
	 */
	unsigned P2PApplication::ProcessPackThread(LPVOID param)
	{
		if (NULL == param) return -1;

		P2PApplication *pthis = reinterpret_cast<P2PApplication*>(param);

		return pthis->ProcessPackThreadProc();
	}

	/**
	 *\fn         ProcessPackThreadPoc()
	 *\brief      实现处理函数。
	 *\return     是否成功(0成功，其它失败)
	 */
	int P2PApplication::ProcessPackThreadProc()
	{
		short times = 0;
		short waitTime = 1;		
		void *client = NULL;
		void *buf = NULL;
		int   len = 0;
		int   ip = 0;
		short port = 0;

		try
		{
			while (running_)
			{
				if (inputQueue_.Get(&client, &buf, len, ip, port))
				{
					ProcessPack(client, buf, len, ip, port);  // 缓冲于其处理(数据包，队列节点)
					waitTime = 0;
				}
				else
				{
					::Sleep(waitTime); // 如果不加它CPU将100%
					if (++times > 10000)
					{
						times = 0;
						waitTime = 1;
					}
				}
			}

			return 300;
		}
		catch (...)
		{
			TRACE(_T("P2PApplication::ProcessPackThread error:%d\n"), ::GetLastError());
			return 302;
		}
	}

	// 协议处理函数(虚函数)
	// pInfo [IN] 数据列表节点
	void P2PApplication::ProcessPack(void *client, void *buf, int len, int ip, short port)
	{
	}
}