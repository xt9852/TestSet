#include "StdAfx.h"
#include "Srv_HTTP.h"
#include "Common\StrConver.h"


namespace XT_IOCP
{

	/**
	 *\fn         CSrv_HTTP()
	 *\brief      缺省构造函数。
	 */
	CSrv_HTTP::CSrv_HTTP(void)
		:postData_(NULL),
		postDataLen_(0),
		client_(NULL)
	{
		CleanHead();

		// Init MIME Types
		mimeTypes_["doc"]	= "application/msword";
		mimeTypes_["bin"]	= "application/octet-stream";
		mimeTypes_["dll"]	= "application/octet-stream";
		mimeTypes_["exe"]	= "application/octet-stream";
		mimeTypes_["pdf"]	= "application/pdf";
		mimeTypes_["p7c"]	= "application/pkcs7-mime";
		mimeTypes_["ai"]	= "application/postscript";
		mimeTypes_["eps"]	= "application/postscript";
		mimeTypes_["ps"]	= "application/postscript";
		mimeTypes_["rtf"]	= "application/rtf";
		mimeTypes_["fdf"]	= "application/vnd.fdf";
		mimeTypes_["arj"]	= "application/x-arj";
		mimeTypes_["gz"]	= "application/x-gzip";
		mimeTypes_["class"]	= "application/x-java-class";
		mimeTypes_["js"]	= "application/x-javascript";
		mimeTypes_["lzh"]	= "application/x-lzh";
		mimeTypes_["lnk"]	= "application/x-ms-shortcut";
		mimeTypes_["tar"]	= "application/x-tar";
		mimeTypes_["hlp"]	= "application/x-winhelp";
		mimeTypes_["cert"]	= "application/x-x509-ca-cert";
		mimeTypes_["zip"]	= "application/zip";
		mimeTypes_["rar"]	= "application/rar";
		mimeTypes_["cab"]	= "application/x-compressed";
		mimeTypes_["arj"]	= "application/x-compressed";
		mimeTypes_["aif"]	= "audio/aiff";
		mimeTypes_["aifc"]	= "audio/aiff";
		mimeTypes_["aiff"]	= "audio/aiff";
		mimeTypes_["au"]	= "audio/basic";
		mimeTypes_["snd"]	= "audio/basic";
		mimeTypes_["mid"]	= "audio/midi";
		mimeTypes_["rmi"]	= "audio/midi";
		mimeTypes_["mp3"]	= "audio/mpeg";
		mimeTypes_["vox"]	= "audio/voxware";
		mimeTypes_["wav"]	= "audio/wav";
		mimeTypes_["ra"]	= "audio/x-pn-realaudio";
		mimeTypes_["ram"]	= "audio/x-pn-realaudio";
		mimeTypes_["bmp"]	= "image/bmp";
		mimeTypes_["gif"]	= "image/gif";
		mimeTypes_["jpeg"]	= "image/jpeg";
		mimeTypes_["jpg"]	= "image/jpeg";
		mimeTypes_["tif"]	= "image/tiff";
		mimeTypes_["tiff"]	= "image/tiff";
		mimeTypes_["xbm"]	= "image/xbm";
		mimeTypes_["wrl"]	= "model/vrml";
		mimeTypes_["htm"]	= "text/html";
		mimeTypes_["html"]	= "text/html";
		mimeTypes_["c"]		= "text/plain";
		mimeTypes_["cpp"]	= "text/plain";
		mimeTypes_["def"]	= "text/plain";
		mimeTypes_["h"]		= "text/plain";
		mimeTypes_["txt"]	= "text/plain";
		mimeTypes_["rtx"]	= "text/richtext";
		mimeTypes_["rtf"]	= "text/richtext";
		mimeTypes_["java"]	= "text/x-java-source";
		mimeTypes_["css"]	= "text/css";
		mimeTypes_["mpeg"]	= "video/mpeg";
		mimeTypes_["mpg"]	= "video/mpeg";
		mimeTypes_["mpe"]	= "video/mpeg";
		mimeTypes_["avi"]	= "video/msvideo";
		mimeTypes_["mov"]	= "video/quicktime";
		mimeTypes_["qt"]	= "video/quicktime";
		mimeTypes_["shtml"]	= "wwwserver/html-ssi";
		mimeTypes_["asa"]	= "wwwserver/isapi";
		mimeTypes_["asp"]	= "wwwserver/isapi";
		mimeTypes_["cfm"]	= "wwwserver/isapi";
		mimeTypes_["dbm"]	= "wwwserver/isapi";
		mimeTypes_["isa"]	= "wwwserver/isapi";
		mimeTypes_["plx"]	= "wwwserver/isapi";
		mimeTypes_["url"]	= "wwwserver/isapi";
		mimeTypes_["cgi"]	= "wwwserver/isapi";
		mimeTypes_["php"]	= "wwwserver/isapi";
		mimeTypes_["wcgi"]	= "wwwserver/isapi";

		defaultHtmlFile_ = "/htm/Demo.htm";

		html404_ = "<HTML><HEAD><TITLE>404 Resource not found</TITLE></HEAD><BODY>404 Resource not found</BODY></HTML>";
	
#ifdef _DEBUG
        buffPool_.name_ = _T("http_buffPool_");
        inputQueue_.name_ = _T("http_inputQueue_");
        outputQueue_.name_ = _T("http_outputQueue_");
#endif // _DEBUG        
    }

	/**
	 *\fn         ~CSrv_HTTP()
	 *\brief      析构函数。
	 */
	CSrv_HTTP::~CSrv_HTTP(void)
	{
		MAP_STR_VOID::iterator iter = htmlFiles_.begin();

		for (; iter != htmlFiles_.end(); ++iter)
		{
			if (iter->second != NULL)
			{
				delete[] (char*)iter->second;
			}
		}
	}

	/**
	 *\fn         CleanHead()
	 *\brief      清空数据。
	 */
	void CSrv_HTTP::CleanHead()
	{
		// 应答给客户端:状态码为206,Content-Range: bytes 5275648-15143085/15143086,从5275648到15143085,文件全长15143086

		headers_["Accept"] = "";				// 客户端可识别的内容类型列表,按优先级排序
		headers_["Accept-Language"] = "";		// 客户端乐于接受的自然语言列表,如:zh,cn
		headers_["Accept-Encoding"] = "";		// 客户端可以理解的编码机制,如:gzip,deflate compress
		headers_["Accept-Charset"] = "";		// 客户端可以处理的字符集,按优先级排序
		headers_["Cache-Control"] = "";			// 缓存:no-cache
		headers_["Connection"] = "";			// 连接操作:keep-alive,close
		headers_["Content-Disposition"] = "";	// 数据描述,POST时,Content-Disposition: form-data; name="test.txt"
		headers_["Content-Length"] = "";		// 数据长
		headers_["Content-Type"] = "";			// 数据编码类型
		headers_["Cookie"] = "";				// COOKIE
		headers_["Date"] = "";					// 发送时间
		headers_["Host"] = "";					// 主机地址
		headers_["Keep-Alive"] = "";			// 后跟保持连接的时间
		headers_["Pragma"] = "";				// 缓存数据no-cache
		headers_["Range"] = "";					// http断点续传,的开始点,例 Range: bytes=5275648-
		headers_["Referer"] = "";				// 从哪个网址转来
		headers_["UA-CPU"] = "";				// 客户端CPU架构
		headers_["User-Agent"] = "";			// 客户端标识

		reqFile_.clear();
		boundary_.clear();
		boundaryEnd_.clear();

		postFile_.clear();
	}

	/**
	 *\fn         Start(const char *ip, const int port, const char *root)
	 *\brief      开始http服务。
	 *\param[in]  ip	ip地址。
	 *\param[in]  port	端口。
	 *\param[in]  root	根目录。
	 */
	int CSrv_HTTP::Start(const char *ip, const int port, const char *root)
	{
		root_ = root;

        LOG(INFO) << "HTTP服务开始加载数据";

		LoadFile(root);

        LOG(INFO) << "HTTP服务加载数据完成";

        google::FlushLogFiles(0);

		CSrv::Start(CMD_TYPE_HTTP, 1024*20);
		
		PCLIENT client = NULL;

		return iocp_.AddTcpListen(ip, port, &client);
	}

	/**
	 *\fn         LoadFile(const char *root)
	 *\brief      开始http服务。
	 *\param[in]  root	根目录。
	 */
	void CSrv_HTTP::LoadFile(const char *root)
	{
		LIST_STR files;

		if (this->GetFiles(root, "", files))
		{
			FILE *file = NULL;
			std::string path;

			LIST_STR::iterator iter = files.begin();

			for (; iter != files.end(); ++iter)
			{
				path = root_ + iter->c_str();

				if (file = fopen(path.c_str(), "rb"))
				{
					fseek(file, 0, SEEK_END);

					unsigned int fileLen = ftell(file);

					char *fileData = new char[fileLen+4];

					memcpy(fileData, &fileLen, sizeof(fileLen));	// 记录文件长度

					fseek(file, 0, SEEK_SET);

					fread(&fileData[4], fileLen, 1, file);	// 文件内容

					fclose(file);

					htmlFiles_[iter->c_str()] = fileData;

                    TRACE("Load file: %s\n", iter->c_str());
				}
			}
		}
	}

	/**
	 *\fn         GetFiles(const char *root, const char *path, LIST_STR &files)
	 *\brief      查找文件，包含子目录。
	 *\param[in]  root	根目录。
	 *\param[in]  path	相对目录。
	 *\param[out] files	文件。
	 */
	bool CSrv_HTTP::GetFiles(const char *root, const char *path, LIST_STR &files)
	{
		bool ret = true;
		bool finished = false;    

		std::string name;

		WIN32_FIND_DATA fileData = {0};

		char fullPath[MAX_PATH] = "";
		strcpy(fullPath, root);
		strcat(fullPath, path);

		//int ret1 = chdir(fullPath);    // 设置当前目录
		SetCurrentDirectory(fullPath);

		HANDLE search = FindFirstFile("*.*", &fileData);
		if (search == INVALID_HANDLE_VALUE)
		{
			ret = false;
		}

		while (!finished && ret) 
		{
			if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)// 是文件
			{
				char file[MAX_PATH] = "";
				strcpy(file, path);
				strcat(file, "/");
				strcat(file, fileData.cFileName);
				files.push_back(file);
			}
			else// 是目录
			{
				if ((strcmp(fileData.cFileName, ".") != 0) && (strcmp(fileData.cFileName, "..") != 0))
				{
					char shortPath[MAX_PATH] = "";	// 相对路径
					strcpy(shortPath, path);
					strcat(shortPath, "/");
					strcat(shortPath, fileData.cFileName);
					GetFiles(root, shortPath, files);  // 递归调用
				}
			}

			if (!FindNextFile(search, &fileData))
			{
				if (GetLastError() == ERROR_NO_MORE_FILES)
				{
					finished = true;
				}
				else
				{
					ret = false;
				}
			}
		}

		FindClose(search);

		return ret;
	}

	/**
	 *\fn         GetHeadContent(const char *data, std::string &head, std::string &content)
	 *\brief      得到头部信息内容。
	 *\param[in]  data		头部文本。
	 *\param[out] head		头节点名称。
	 *\param[out] content	头节点内容。
	 */
	void CSrv_HTTP::GetHeadContent(const char *data, std::string &head, std::string &content)
	{
		std::string dataStr(data);

		int index = dataStr.find(":");

		if (index != -1)
		{
			char name[MAX_PATH] = "";
			strncpy(name, data, index);

			head = name;
			content = &data[index + 1];

			return;
		}

		// 可能是GET或POST
		index = dataStr.find(" ");

		if (index != -1)
		{
			char name[MAX_PATH] = "";
			strncpy(name, data, index);

			head = name;
			content = &data[index + 1];

			index = content.find(" ");
			if (index != -1)
			{
				content.erase(index, content.length());
			}

			index = content.find(" ");
			if (index != -1)
			{
				content.erase(index, content.length());
			}
		}
		else    // POST的标记,例:-----------------------------7db1f467094c
		{
			head = data;
		}
	}

	/**
	 *\fn         SendResponseData(PCLIENT client, const char *head, int headLen, const char *data, int dataLen, char *pack)
	 *\brief      发送应答数据
	 *\param[in]  client	客户端对象。
	 *\param[in]  head		头节部数据。
	 *\param[in]  headLen	头节部数据长。
	 *\param[in]  data		内容数据。
	 *\param[in]  dataLen	内容数据长。
	 *\param[in]  pack		数据包。
	 */
	void CSrv_HTTP::SendResponseData(PCLIENT client, const char *head, int headLen, 
		const char *data, int dataLen, char *pack)
	{
		if (headLen + dataLen < buffPool_.getSize())	// 一个数据包可发送
		{
			memcpy(pack, head, headLen);
			memcpy(&pack[headLen], data, dataLen);

			iocp_.SendData(client, pack, headLen + dataLen, 0, 0);
		}
		else	// 得多个包发送
		{
			// 第一个包,是满的
			memcpy(pack, head, headLen);
			memcpy(&pack[headLen], data, buffPool_.getSize() - headLen);

			iocp_.SendData(client, pack, buffPool_.getSize(), 0, 0);

			int remain = dataLen - (buffPool_.getSize() - headLen);	// 剩余数据长

			for (int pos = buffPool_.getSize() - headLen; remain > 0; pos += buffPool_.getSize())
			{
                Sleep(50); // 完成端口多线程发送数据，有时会乱序，所以延时

				void *buf = buffPool_.Get(1);

				int len = (remain >= buffPool_.getSize()) ? buffPool_.getSize() : remain;	// 最后一个包长

				memcpy(buf, &data[pos], len);

				iocp_.SendData(client, buf, len);

				remain -= len;

				TRACE(_T("client:%d pos:%d len:%d remain:%d\n"), client, pos, len, remain);
			}
		}
	}

	/**
	 *\fn         GetResponseHead(const char *statusCode, const char *reqFile, int dataLen)
	 *\brief      得到应答头
	 *\param[in]  statusCode	状态码。
	 *\param[in]  reqFile		请求的文件名。
	 *\param[in]  dataLen		数据长。
	 *\return	  得到应答头部数据
	 */
	std::string CSrv_HTTP::GetResponseHead(const char *statusCode, const char *reqFile, int dataLen)
	{
		// 得到扩展名
		const char *ext = strrchr(reqFile, '.');

		MAP_STR_STR::iterator iter = mimeTypes_.find(ext + 1);

		std::string contentType = (iter != mimeTypes_.end()) ? iter->second : "text/html";

		char head[MAX_PATH] = "";

		sprintf(head, "HTTP/1.1 %s\r\nServer: %s\r\nDate: %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n",
			statusCode,
			CTime::GetCurrentTime().FormatGmt(_T("%a, %d %b %Y %H:%M:%S GMT")),
			SERVERNAME,
			contentType.c_str(),
			dataLen);

		return head;
	}

	/**
	 *\fn         ParseRequstHead(const char *data, int len)
	 *\brief      解析请求头
	 *\param[in]  data		数据。
	 *\param[in]  len		数据长。
	 *\return     命令类型
	 */
	std::string CSrv_HTTP::ParseRequstHead(const char *data, int len)
	{
		if ((strncmp("GET", data, 3) == 0) || 
			(strncmp("POST", data, 4) == 0) || 
			(strncmp("----", data, 4) == 0))
		{
			(char)data[len] = '\0';
			char *sub = (char*)strstr(data, "\r\n\r\n");	// 没有\r\n\r\n,则是POST来的数据
			int index = (NULL == sub)?-1:(sub-data);

			postData_ = (char*)&data[index + 4];
			postDataLen_ = len - index - 4;
		}
		else    // 只有数据没有头结构
		{
			postData_ = (char*)data;
			postDataLen_ = len;
			return "POST";
		}

		VECTOR_STR headerNodes;
		CStrConver::TokenizeData(data, "\r\n", headerNodes);

		std::string cmd;
		std::string header;
		std::string content;

		for (unsigned int i = 0; i < headerNodes.size(); i++)
		{
			GetHeadContent(headerNodes[i].c_str(), header, content);

			if (header == "GET")                         // GET
			{
				CleanHead();

				int index = content.find("?");
				if (-1 != index)
				{
					content = content.substr(0, index);
				}

				reqFile_ = content;
				cmd = header;
			}
			else if (header == "POST")                   // POST
			{
				CleanHead();
				reqFile_ = content;
				cmd = header;
			}
			else if (header == "Content-Disposition")    // 数据描述,POST时,Content-Disposition: form-data; name="test.txt"
			{
				int begin = content.find("name=\"");
				int end = content.find("\"", begin + 6);

				if ((-1 != begin) && (-1 != end))
				{
					postFile_ = content.substr(begin + 6, end - begin - 6);
					cmd = "POST";
				}
			}
			else   
			{
				MAP_STR_STR::iterator iter = headers_.find(header);

				if (iter != headers_.end())
				{
					headers_[header] = content;
				}

				TRACE(_T("Head:%s Value:%s\n"), header.c_str(), content.c_str());
			}
		}

		return cmd;
	}

	/**
	 *\fn         ProcessGET(PCLIENT client, const char *data, int len);
	 *\brief      处理GET请求
	 *\param[in]  client	客户端对象。
	 *\param[in]  data		数据。
	 *\param[in]  len		数据长。
	 *\return     命令类型
	 */
	void CSrv_HTTP::ProcessGET(PCLIENT client, const char *data, int len)
	{
		if ("/" == reqFile_)
		{
			reqFile_ = defaultHtmlFile_;
		}
// 		else
// 		{
// 			CStrConver::StringReplace(reqFile_, "/", "\\");
// 		}

		MAP_STR_VOID::iterator iter = htmlFiles_.find(reqFile_);

		if (iter != htmlFiles_.end())
		{
			char *fileData = (char*)iter->second;

			unsigned int fileLen = 0;

			memcpy(&fileLen, fileData, 4);

			fileData += 4;

			std::string responseHead = GetResponseHead("200 OK", reqFile_.c_str(), fileLen);
			SendResponseData(client, responseHead.c_str(), responseHead.length(), fileData, fileLen, (char*)data);
		}
		else
		{
			std::string responseHead = GetResponseHead("200 OK", reqFile_.c_str(), html404_.length());
			SendResponseData(client, responseHead.c_str(), responseHead.length(), html404_.c_str(), html404_.length(), (char*)data);
		}
	}

	/**
	 *\fn         ProcessPOST(PCLIENT client, const char *data, int len);
	 *\brief      处理POST请求
	 *\param[in]  client	客户端对象。
	 *\param[in]  data		数据。
	 *\param[in]  len		数据长。
	 *\return     命令类型
	 */
	std::string CSrv_HTTP::ProcessPOST(PCLIENT client, const char *data, int len)
	{
		std::string cmd;

		std::string contentType = headers_["Content-Type"];

		if ("" != contentType)
		{
			int index = contentType.find("boundary=");
			if (-1 != index)
			{
				boundary_ = "--" + contentType.substr(index+9);
				boundaryEnd_ = "\r\n" + boundary_ + "--\r\n";
			}
		}

		if ((0 != postDataLen_) && (NULL != postData_))
		{
			char *end = postData_ + postDataLen_ - boundaryEnd_.length();

			if (0 == strncmp(end, boundaryEnd_.c_str(), boundaryEnd_.length()))
			{
				cmd = "GET";
				postDataLen_ -= boundaryEnd_.length();
			}

			//-----------------------------------------------

			std::string filePath = root_ + "\\" + postFile_;
			bool open = false;
			UINT bModeCmd = 0;

			FILE *file = fopen(filePath.c_str(), "ab");

			if (NULL != file)
			{
				fseek(file, 0, SEEK_END);
				fwrite(postData_, postDataLen_, 1, file);
				fclose(file);
			}
		}

		return cmd;
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
	void CSrv_HTTP::ProcessPack(void *client, void *buf, int len, int ip, short port)
	{
		PPACK pack = (PPACK)buf;

		if ((packFlag == pack->flag) && (CLIENT_CLOSE_SOCKET == pack->protoId))
		{
			buffPool_.Free(pack);
			return;
		}

		std::string cmd = ParseRequstHead((char*)buf, len);

		if ("POST" == cmd)
		{
			cmd = ProcessPOST((PCLIENT)client, (char*)buf, len);
		}

		if ("GET" == cmd)
		{
			ProcessGET((PCLIENT)client, (char*)buf, len);
		}

		if (headers_["Connection"] == "close") // Keep-Alive
		{
			::Sleep(500);
			iocp_.CloseClient((PCLIENT)client, NULL);
		}

		return;
	}

	/**
	 *\fn         Post()
	 *\brief      Post数据。
	 */
	void CSrv_HTTP::Post(void)
	{
		if (0 == iocp_.ConnectTo(g_ProFile.getIp(0), 8080, &client_))
		{
			CString strLen;
			CString strPost1;
			CString strPost2;        
			CString strData("这里的测试的要上传的数据");

			strPost1.AppendFormat("POST /post.aspx HTTP/1.1\r\n");
			strPost1.AppendFormat("Accept: */*\r\n");
			strPost1.AppendFormat("Referer: http://%s:8080/post.aspx\r\n", g_ProFile.getIp(0));
			strPost1.AppendFormat("Accept-Language: zh-cn\r\n");
			strPost1.AppendFormat("Content-Type: multipart/form-data; boundary=---------------------------7d8186a20320\r\n");   // 比下面的少两个--
			strPost1.AppendFormat("UA-CPU: x86\r\n");
			strPost1.AppendFormat("Accept-Encoding: gzip, deflate\r\n");
			strPost1.AppendFormat("User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Maxthon; .NET CLR 1.1.4322; InfoPath.1)\r\n");
			strPost1.AppendFormat("Host: 127.0.0.1:86\r\n");
			strPost1.AppendFormat("Content-Length: ****\r\n");
			strPost1.AppendFormat("Connection: Keep-Alive\r\n");//close");//
			strPost1.AppendFormat("Cache-Control: no-cache\r\n");
			strPost1.AppendFormat("\r\n");

			strPost2.AppendFormat("-----------------------------7d8186a20320\r\n");
			strPost2.AppendFormat("Content-Disposition: form-data; name=\"\\test.txt\"\r\n");
			strPost2.AppendFormat("\r\n");
			strPost2.AppendFormat("%s\r\n", strData);
			strPost2.AppendFormat("-----------------------------7d8186a20320--\r\n");

			strLen.Format("%d", strData.GetLength());

			strPost1.Replace("****", strLen);

			BYTE* pbyBuf = (BYTE*)buffPool_.Get(1);
			memcpy(pbyBuf, (LPCSTR)strPost1, strPost1.GetLength());
			outputQueue_.Add(client_, pbyBuf, strPost1.GetLength());

			pbyBuf = (BYTE*)buffPool_.Get(1);
			memcpy(pbyBuf, (LPCSTR)strPost2, strPost2.GetLength());
			outputQueue_.Add(client_, pbyBuf, strPost2.GetLength());
		}
	}
}