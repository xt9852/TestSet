#include "StdAfx.h"
#include "srv_iocp.h"


namespace XT_IOCP
{

//#define USE_TCP

	/**
	 *\fn         CSrv_HTTP()
	 *\brief      缺省构造函数。
	 */
	CSrv_IOCP::CSrv_IOCP(void)
		:num_(0),
        client_(NULL)
	{
	}

	/**
	 *\fn         ~CSrv_IOCP()
	 *\brief      析构函数。
	 */
	CSrv_IOCP::~CSrv_IOCP(void)
	{
	}

	/**
	 *\fn         Start(const char *ip, unsigned short port)
	 *\brief      添加监听
	 *\param[in]  ip		本机IP。
	 *\param[in]  port		本机端口。
	 *\return     是否成功(0成功,其它失败)
	 */
	int CSrv_IOCP::Start(const char *ip, unsigned short port)
	{
		CSrv::Start(CMD_TYPE_MYSELF, 4000);

#ifdef USE_TCP
        return iocp_.AddTcpListen(ip, port, &client_);
#else
        return iocp_.AddUdpListen(ip, port, &client_);
#endif
	}

	/**
	 *\fn         Test(const char *ip, unsigned short port)
	 *\brief      连接
	 *\param[in]  ip		对方IP。
	 *\param[in]  port		对方端口。
	 */
	void CSrv_IOCP::Test(const char *ip, unsigned short port)
	{
		PCLIENT client = NULL;

#ifdef USE_TCP
        if (0 == iocp_.ConnectTo(ip, port, &client))
#endif
        {
			PPACK pack = (PPACK)buffPool_.Get(1);
			if (NULL != pack)
			{
				pack->clear();
				pack->protoId = 123;
				pack->dataLen = buffPool_.getSize()-sizeof(PACK)+1;

				LOG(INFO) << "datalen:" << pack->dataLen 
					<< "packsize:" << sizeof(PACK) 
					<< "buffsize:" << buffPool_.getSize();

				for (int i = 0; i < pack->dataLen - 1; i++)
				{
					pack->data[i] = '1';
				}

				pack->data[pack->dataLen - 1] = '2'; // 最后一个数据

				int len = 0;
				char *data = NULL;

				if (zipFile_.Compress((char*)pack->data, pack->dataLen, &data, (UINT&)len))
				{
					pack->dataLen = len;
				}

                memcpy(pack->data, data, len);

#ifdef USE_TCP
                outputQueue_.Add(client, pack, pack->getPackLen());
#else
                outputQueue_.Add(client_, pack, pack->getPackLen(), inet_addr(ip), htons(port));
#endif
            }
		}
	}

	/**
	 *\fn         ProcessPack(void *client, void *buf, int len, int ip, short port)
	 *\brief      处理数据包
	 *\param[in]  client	客户端对象。
	 *\param[in]  buf		数据。
	 *\param[in]  len		数据长。
	 *\param[in]  ip		对方IP(UDP)。
	 *\param[in]  port		对方端口(UDP)。
	 */
	void CSrv_IOCP::ProcessPack(void *client, void *buf, int len, int ip, short port)
	{
		PPACK pack = (PPACK)buf;

		switch (pack->protoId)
		{
		case 123:
			{
				++num_;

				char data[1024*10] = "";
				int len = sizeof(data);

// 				if (!zipFile_.UnCompress((char*)pack->data, pack->dataLen, data, (UINT&)len))
// 				{
// 					TRACE(_T("UnCompress not ok\n"));
// 				}

#ifdef USE_TCP
				outputQueue_.Add(client, pack, pack->getPackLen());
#else
				outputQueue_.Add(client, pack, pack->getPackLen(), ip, port);
#endif
				break;
			}
		case CLIENT_CLOSE_SOCKET:
		default:
			{
				TRACE("CSrv_IOCP::ProcessPack default\n");
				buffPool_.Free(pack);
				break;
			}
		}
	}
}