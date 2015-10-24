#pragma once
#include "Network\Srv.h"
#include "Base\MD5.h"
#include <map>
#include <list>
#include <string>


namespace XT_IOCP
{

#define SERVERNAME		"MyWebServer/0.1"


	typedef std::map<std::string, void*>		MAP_STR_VOID;
	typedef std::map<std::string, std::string>	MAP_STR_STR;
	typedef std::list<std::string>				LIST_STR;

	/**
	 *\class  CSrv_HTTP
	 *\brief  该类主要是HTTP服务
	 *\date   2012-07-03
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2007-07-03   张海涛   创建此类
	 */
	class CSrv_HTTP : public CSrv
	{
	public:
		/**
		 *\fn         CSrv_HTTP()
		 *\brief      缺省构造函数。
	     */
		CSrv_HTTP();

		/**
		 *\fn         ~CSrv_HTTP()
		 *\brief      析构函数。
	     */
		~CSrv_HTTP();

	private:
		std::string		defaultHtmlFile_;	// 默认的文件
		std::string		html404_;			// 没有找到文件
		std::string		root_;				// 根路径
		std::string		reqFile_;			// 请求的文件

		std::string		boundary_;			// POST标记
		std::string		boundaryEnd_;		// POST标记
		std::string		postFile_;			// POST的文件名
		char			*postData_;			// POST文件数据
		int				postDataLen_;		// POST文件大小
		
		PCLIENT			client_;			// 客户端
		MAP_STR_VOID    htmlFiles_;			// 加载的文件
		MAP_STR_STR		mimeTypes_;			// 类型
		MAP_STR_STR		headers_;			// 请求头

    protected:
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

		/**
		 *\fn         ParseRequstHead(const char *data, int len)
		 *\brief      解析请求头
		 *\param[in]  data		数据。
		 *\param[in]  len		数据长。
		 *\return     命令类型
		 */
		std::string ParseRequstHead(const char *data, int len);

		/**
		 *\fn         ProcessGET(PCLIENT client, const char *data, int len);
		 *\brief      处理GET请求
		 *\param[in]  client	客户端对象。
		 *\param[in]  data		数据。
		 *\param[in]  len		数据长。
		 *\return     命令类型
		 */
		void ProcessGET(PCLIENT client, const char *data, int len);
		
		/**
		 *\fn         ProcessPOST(PCLIENT client, const char *data, int len);
		 *\brief      处理POST请求
		 *\param[in]  client	客户端对象。
		 *\param[in]  data		数据。
		 *\param[in]  len		数据长。
		 *\return     命令类型
		 */
		std::string ProcessPOST(PCLIENT client, const char *data, int len);

		/**
		 *\fn         SendResponseData(PCLIENT client, const char *head, int headLen, 
		 *\n                           const char *data, int dataLen, char *pack)
		 *\brief      发送应答数据
		 *\param[in]  client	客户端对象。
		 *\param[in]  head		头节部数据。
		 *\param[in]  headLen	头节部数据长。
		 *\param[in]  data		内容数据。
		 *\param[in]  dataLen	内容数据长。
		 *\param[in]  pack		数据包。
		 */
		void CSrv_HTTP::SendResponseData(PCLIENT client, const char *head, int headLen, 
			const char *data, int dataLen, char *pack);

		/**
		 *\fn         GetResponseHead(const char *statusCode, const char *reqFile, int dataLen)
		 *\brief      得到应答头
		 *\param[in]  statusCode	状态码。
		 *\param[in]  reqFile		请求的文件名。
		 *\param[in]  dataLen		数据长。
		 *\return	  得到应答头部数据
		 */
		std::string GetResponseHead(const char *statusCode, const char *reqFile, int dataLen);

		/**
		 *\fn         GetHeadContent(const char *data, std::string &head, std::string &content)
		 *\brief      得到头部信息内容。
		 *\param[in]  data		头部文本。
		 *\param[out] head		头节点名称。
		 *\param[out] content	头节点内容。
		 */
		void GetHeadContent(const char *data, std::string &head, std::string &content);

		/**
		 *\fn         CleanHead()
		 *\brief      清空数据。
		 */
		void CleanHead();

		/**
		 *\fn         LoadFile(const char *root)
		 *\brief      开始http服务。
		 *\param[in]  root	根目录。
		 */
		void LoadFile(const char *root);

		/**
		 *\fn         GetFiles(const char *root, const char *path, LIST_STR &files)
		 *\brief      查找文件，包含子目录。
		 *\param[in]  root	根目录。
		 *\param[in]  path	相对目录。
		 *\param[out] files	文件。
		 */
		bool GetFiles(const char *root, const char *path, LIST_STR &files);

	public:
		/**
		 *\fn         Start(const char *ip, const int port, const char *root)
		 *\brief      开始http服务。
		 *\param[in]  ip	ip地址。
		 *\param[in]  port	端口。
		 *\param[in]  root	根目录。
		 */
		int Start(const char *ip, const int port, const char *root);

		/**
		 *\fn         Post()
		 *\brief      Post数据。
		 */
		void Post();

        /**
		 *\fn         getFileList()
		 *\brief      得到已经加载的文件。
         *\return     已经加载的文件
		 */
        MAP_STR_VOID* getFileList() { return &htmlFiles_; }
	};

}