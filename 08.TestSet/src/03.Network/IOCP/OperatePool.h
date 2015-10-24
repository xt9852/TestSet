
#pragma once
#include "Pool.h"
#include <ws2def.h>	// WSABUF


namespace XT_IOCP
{

	/**
	 *\enum   OperateType
	 *\brief  操作类型
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	enum OperateType 
	{
		OP_ACCEPT,	    // 接收连接
		OP_READ,	    // 读
		OP_WRITE,	    // 写
        OP_WRITE_FINISH,// 写过完成
        OP_IDLE		    // 空闲
	};

// 	typedef struct _WSABUF {
// 		ULONG len;     /* the length of the buffer */
// 		__field_bcount(len) CHAR FAR *buf; /* the pointer to the buffer */
// 	} WSABUF, FAR * LPWSABUF;

	/**
	 *\struct tagOverLappedPlus
	 *\brief  扩展重叠结构，代表IOCP的动作
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	typedef struct tagOverLappedPlus
	{
		OVERLAPPED	overlapped;	// 重叠结构
		OperateType	type;		// 操作类型
		WSABUF      buf;		// 缓冲区
		SOCKADDR_IN remoteAddr; // 对方地址(UDP)
        int         addrSize;   // 地址结构大小
        int			sock;		// TCP客户端(TCP客户端连接监听端口时,监听端口执行IOAccept操作,内部记录的就是分配给这个客户端的SOCKET)
		bool		sent;		// 发送完成
		bool		udp;		// UDP数据包

        tagOverLappedPlus::tagOverLappedPlus()
        {
            memset(this, 0, sizeof(tagOverLappedPlus));
            addrSize = sizeof(remoteAddr);
            remoteAddr.sin_family = AF_INET;
        }

        void tagOverLappedPlus::setIp(int ip)
        {
            remoteAddr.sin_addr.S_un.S_addr = ip;
        }

        void tagOverLappedPlus::setPort(int port)
        {
            remoteAddr.sin_port = port;
        }

        int tagOverLappedPlus::getIp()
        {
            return remoteAddr.sin_addr.S_un.S_addr;
        }

        USHORT tagOverLappedPlus::getPort()
        {
            return remoteAddr.sin_port;
        }

	}OPERATE,*POPERATE;

	/**
	 *\class  PackQueue
	 *\brief  重叠结构的扩展，每一个代表一种操作，
	 *\	      不与socket一一对应，只有投递某种操作时才用到
	 *\date   2012-07-17
	 *\author 张海涛
	 *\par    Revision History:
	 */
	class OperatePool : public Pool
	{
	public:
		/**
		 *\fn         OperatePool()
		 *\brief      缺省构造函数。
	     */
		OperatePool();

		/**
		 *\fn         ~OperatePool()
		 *\brief      析构函数。
	     */
		~OperatePool();

	private:
		/**
		 *\fn         NewItem()
		 *\brief      new一个单元,纯虚函数。
		 *\return     单元指针。
		 */
		virtual void* NewItem();

		/**
		 *\fn         DeleteItem()
		 *\brief      删除一个单元,纯虚函数。
		 *\param[in]  data 数据指针。
		 *\return     单元指针。
		 */
		virtual void DeleteItem(void *data);

	public:
		/**
		 *\fn         Get()
		 *\brief      从池中取得一个操作对象。
		 *\return     操作对象指针。
		 */
		POPERATE Get();
	};

}