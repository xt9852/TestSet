
#include "stdafx.h"
#include "Srv.h"
//#include <ws2ipdef.h>
#include <process.h>


/*
线程    状态    退出码

工作    正常    300
工作    强闭    301
工作    异常    302
*/

namespace XT_IOCP
{

	/**
	 *\fn         CSrv()
	 *\brief      默认构造函数。
	 */
	CSrv::CSrv(void)
		:thread_(NULL),
		running_(false),
		cmdType_(0)
	{
	}

	/**
	 *\fn         ~CSrv()
	 *\brief      析构函数。
	 */
	CSrv::~CSrv(void)
	{
		Stop();
	}

	/**
	 *\fn         Start(int cmdType, int buffSize)
	 *\brief      开始运行服务。
	 *\param[in]  cmdType  命令类型。
	 *\param[in]  buffSize 缓冲区大小。
	 *\return     是否成功(0成功，其它失败)
	 */
	int CSrv::Start(int cmdType, int buffSize)
	{
        if (running_) return -1;

        running_ = true;
		unsigned int threadID = 0;
		thread_ = (HANDLE)_beginthreadex(NULL, 0, ProcessPackThread, this, 0, &threadID);

        if (NULL == thread_) return -2;

		buffPool_.setSize(buffSize);
		inputQueue_.Start();
		outputQueue_.Start();

        int ret = iocp_.Init(cmdType, &inputQueue_, &outputQueue_, &buffPool_);
		
        if (0 != ret)
        {
            running_ = false;
        }

        return ret;
	}

	/**
	 *\fn         Stop()
	 *\brief      停止运行服务。
	 */
	void CSrv::Stop()
	{
		running_ = false;

		iocp_.Stop();

		StopThread(thread_);
	}

	/**
	 *\fn         Stop(HANDLE thread)
	 *\brief      停止线程。
	 *\param[in]  thread  线程句柄。
	 */
	void CSrv::StopThread(HANDLE thread)
	{
        if (NULL == thread) return;

        int i = 10;
        for (; i > 0; i--)
        {
            int code = 0;
            if (!GetExitCodeThread(thread, (LPDWORD)&code) || 
                (code !=STILL_ACTIVE))
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
        thread_ = NULL;
    }

	/**
	 *\fn         ProcessPackThread(LPVOID pParam)
	 *\brief      处理线程。
	 *\param[in]  param  线程参数。
	 *\return     是否成功(0成功，其它失败)
	 */
	unsigned CSrv::ProcessPackThread(LPVOID param)
	{
		if (NULL == param) return -1;

		CSrv *pthis = reinterpret_cast<CSrv*>(param);

		return pthis->ProcessPackThreadPoc();
	}

	/**
	 *\fn         ProcessPackThreadPoc()
	 *\brief      实现处理函数。
	 *\return     是否成功(0成功，其它失败)
	 */
	int CSrv::ProcessPackThreadPoc()
	{
		//PQueueNode node = NULL;
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
				//if (inputQueue_.Get(&node))
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
			TRACE(_T("CSrv::ProcessPackThread error:%d\n"), ::GetLastError());
			return 302;
		}
	}

	// 协议处理函数(虚函数)
	// pInfo [IN] 数据列表节点
	void CSrv::ProcessPack(void *client, void *buf, int len, int ip, short port)
	{
		PPACK pack = (PPACK)buf;

		switch (pack->protoId)
		{
		case CLIENT_CLOSE_SOCKET:   // SOCKET断开连接,pack->dataLen为SOCKET值
			{
				TRACE("CLIENT_CLOSE_SOCKET SOCKET:%d\n", pack->dataLen);
				buffPool_.Free(buf);
				break;
			}
		default:
			{
				TRACE("Pack protoId %x\n", pack->protoId);
				buffPool_.Free(buf);
			}
		}
	}
}