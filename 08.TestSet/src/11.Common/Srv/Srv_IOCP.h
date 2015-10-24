#pragma once
#include "Network/Srv.h"
#include "ZipFile/CZip.h"


namespace XT_IOCP
{

	/**
	 *\class  CSrv_IOCP
	 *\brief  该类主要是IOCP服务
	 *\date   2012-07-03
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2007-07-03   张海涛   创建此类
	 */
	class CSrv_IOCP : public CSrv
	{
	public:
		/**
		 *\fn         CSrv_HTTP()
		 *\brief      缺省构造函数。
		 */
		CSrv_IOCP(void);

		/**
		 *\fn         ~CSrv_IOCP()
		 *\brief      析构函数。
		 */
		~CSrv_IOCP(void);

		int  num_;		// 处理的包数

		CZip zipFile_;	// ZIP压缩文件

        PCLIENT	client_;// 客户端对像
		
		/**
		 *\fn         getNum()
		 *\brief      处理的包数
		 *\return	  处理的包数
		 */
		int  getNum() { return num_; }
		
		/**
		 *\fn         Start(const char *ip, unsigned short port)
		 *\brief      添加监听
		 *\param[in]  ip		本机IP。
		 *\param[in]  port		本机端口。
		 *\return     是否成功(0成功,其它失败)
		 */
		int  Start(const char *ip, unsigned short port);

		/**
		 *\fn         Test(const char *ip, unsigned short port)
		 *\brief      连接
		 *\param[in]  ip		对方IP。
		 *\param[in]  port		对方端口。
		 */
		void Test(const char *ip, unsigned short port);

		/**
		 *\fn         ProcessPack(void *client, void *buf, int len, int ip, short port)
		 *\brief      处理数据包
		 *\param[in]  client	客户端对象。
		 *\param[in]  buf		数据。
		 *\param[in]  len		数据长。
		 *\param[in]  ip		对方IP(UDP)。
		 *\param[in]  port		对方端口(UDP)。
		 */
		void ProcessPack(void *client, void *buf, int len, int ip, short port);
	};
}