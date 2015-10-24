
#include "stdafx.h"
#include "HttpPost.h"
#include <afxinet.h> // CHttpConnection


/**
 *\fn         CHttpPost()
 *\brief      缺省构造函数。
 */
CHttpPost::CHttpPost()
	:response_(NULL),
	responseLen_(0)
{
}

/**
 *\fn         CHttpPost(const char *ip, unsigned short port, const char *path)
 *\brief      构造函数。
 *\param[in]  ip   IP地址。
 *\param[in]  port 端口地址。
 *\param[in]  path 路径。
 */
CHttpPost::CHttpPost(const char *ip, unsigned short port, const char *path)
	:response_(NULL),
	responseLen_(0)
{
	ip_ = ip;
	port_ = port;
	path_ = path;
}

/**
 *\fn         ~CHttpPost()
 *\brief      析构函数。
 */
CHttpPost::~CHttpPost()
{
}

/**
 *\fn         SendPostRequest(void *data, int len, const char *filename)
 *\brief      发送数据。
 *\param[in]  data     数据。
 *\param[in]  len      数据长。
 *\param[in]  filename 文件名。
 *\return     是否成功
 */
bool CHttpPost::SendPostRequest(void *data, int len, const char *filename)
{
	try
	{
		//1. Instantiate CInternetSession
		CInternetSession httpSession("CHttpPost Client", 
			1,
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL,
			NULL,
			INTERNET_FLAG_DONT_CACHE);

		//2. Get CHttpConnection (Server URL and Port required)
		CHttpConnection* pHttpConnection = httpSession.GetHttpConnection(ip_.c_str(),
			INTERNET_FLAG_NO_AUTO_REDIRECT,
			(INTERNET_PORT)port_, 
			NULL, 
			NULL);

		//3. Open HTTP Request (pass method type [get/post/..] and URL path (except server name))
		CHttpFile* pHttpFile = pHttpConnection->OpenRequest("POST",
			path_.c_str(),
			NULL, 
			1, 
			NULL, 
			NULL,
			INTERNET_FLAG_KEEP_CONNECTION |	INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD);

		//4. Add HTTP Request Headers
		char headers[MAX_PATH] = "";
		sprintf(headers, "Content-Type: text/xml; charset=utf-8\nContent-Length:%d", len);
		pHttpFile->AddRequestHeaders(headers);
		
		if (NULL != filename)
		{
			sprintf(headers, "Content-Disposition: form-data; name=\"%s\"", filename);
			pHttpFile->AddRequestHeaders(headers);
		}

		//5. Send the request
		pHttpFile->SendRequest(NULL, 0, data, len);

		//6. Check the return HTTP Status Code
		DWORD status = HTTP_STATUS_OK;
		pHttpFile->QueryInfoStatusCode(status);

		if (HTTP_STATUS_OK == status)
		{			
			pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, responseLen_);

			if (responseLen_ != 0)
			{
				if (NULL != response_)
				{
					delete response_;
				}
				
				response_ = new char[responseLen_];
				
				//7. Read the response text
				for (int i = 0; i < responseLen_; )
				{
					int read = pHttpFile->Read(&response_[i], responseLen_);

					i += read;
				}
			}
		}
		
		status_ = status;

		//8. Close the stream/connection
		if(pHttpFile)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}

		if(pHttpConnection)
		{
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		return true;

	}
	catch(CInternetException* exp)
	{
		TCHAR lpszErrorMsg[MAX_PATH+2];
		exp->GetErrorMessage(lpszErrorMsg, MAX_PATH);
		return false;
	}
}