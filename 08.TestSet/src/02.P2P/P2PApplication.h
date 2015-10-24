
#pragma once
#include "P2PEnginer.h"
#include "03.Network/IOCP/BuffPool.h"
#include "03.Network/IOCP/PackQueue.h"

namespace XT_P2P
{
	/**
	 *\class  P2PApplication
	 *\brief  该类主要是P2P的上层应用类
	 *\date   2013-04-15
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2013-04-15   张海涛   创建此类,使用P2P。
	 */
	class P2PApplication
	{
	public:
		/**
		 *\fn         P2PApplication()
		 *\brief      默认构造函数。
		 */
		P2PApplication();

		/**
		 *\fn         ~P2PApplication()
		 *\brief      析构函数。
		 */
		~P2PApplication();

	protected:
		HANDLE		        thread_;	    // 背景线程
		bool 		        running_;	    // 是否正在运行

		P2PEnginer          enginer_;	    // P2P引擎
        XT_IOCP::BuffPool   buffPool_;      // 缓冲池
		XT_IOCP::PackQueue	inputQueue_;	// 输入列队

	public:
		/**
	     *\fn         Start(LPCTSTR rootPath, LPCTSTR ip, LPCTSTR port)
	     *\brief      开始运行服务。
	     *\param[in]  rootPath  文件根路径。
         *\param[in]  ip        IP地址。
         *\param[in]  port      端口地址。
	     *\return     是否成功(0成功，其它失败)
	     */
	    int Start(LPCTSTR rootPath, LPCTSTR ip, LPCTSTR port);

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
		 *\brief      工作线程处理函数。
		 *\return     是否成功(0成功，其它失败)
		 */
		int ProcessPackThreadProc();

		/**
		 *\fn         ProcessPackThread(LPVOID pParam)
		 *\brief      工作线程。
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
