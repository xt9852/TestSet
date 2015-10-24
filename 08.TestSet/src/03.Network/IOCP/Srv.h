
#pragma once

#include "IOCP.h"
#include "PackQueue.h"
#include "BuffPool.h"
#include "PrePack.h"


namespace XT_IOCP
{
	/**
	 *\class  CSrv
	 *\brief  该类主要是完成端口服务类
	 *\date   2012-07-03
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2007-07-03   张海涛   创建此类,使用完成端口。
	 */
	class CSrv
	{
	public:
		/**
		 *\fn         CSrv()
		 *\brief      默认构造函数。
		 */
		CSrv();

		/**
		 *\fn         ~CSrv()
		 *\brief      析构函数。
		 */
		~CSrv();

	protected:
		HANDLE		thread_;		// 处理线程
		bool 		running_;	    // 是否正在运行

		IOCP        iocp_;			// 完成端口
		PackQueue	inputQueue_;	// 输入列队
		PackQueue	outputQueue_;	// 输出列队
		BuffPool    buffPool_;		// 内存池
		int			cmdType_;		// 命令类型

	public:
		/**
		 *\fn         Start(int cmdType, int buffSize)
		 *\brief      开始运行服务。
		 *\param[in]  cmdType  命令类型。
		 *\param[in]  buffSize 缓冲区大小。
		 *\return     是否成功(0成功，其它失败)
		 */
		int Start(int cmdType, int buffSize);

		/**
		 *\fn         Stop()
		 *\brief      停止运行服务。
		 */
		void Stop();

		/**
		 *\fn         Stop(HANDLE thread)
		 *\brief      停止线程。
		 *\param[in]  thread  线程句柄。
		 */
		void StopThread(HANDLE thread);

		/**
		 *\fn         ProcessPackThreadPoc()
		 *\brief      实现处理函数。
		 *\return     是否成功(0成功，其它失败)
		 */
		int ProcessPackThreadPoc();
		
		/**
		 *\fn         ProcessPackThread(LPVOID pParam)
		 *\brief      处理线程。
		 *\param[in]  param  线程参数。
		 *\return     是否成功(0成功，其它失败)
		 */
		static unsigned __stdcall ProcessPackThread(LPVOID param);		

		/**
		 *\fn         ProcessPack(void *client, void *buf, int len, int ip, short port)
		 *\brief      处理数据包。
		 *\param[in]  client  客户端。
		 *\param[in]  buf     数据。
		 *\param[in]  len     数据长。
		 *\param[in]  ip	  IP地址(UDP)。
		 *\param[in]  port    端口地址(UDP)。
		 */
		virtual void ProcessPack(void *client, void *buf, int len, int ip, short port);
	};

}
