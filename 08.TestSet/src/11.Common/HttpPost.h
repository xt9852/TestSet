#pragma once


/**
 *\class  CHttpPost
 *\brief  该类主要用于HTTP的POST数据
 *\date   2012-06-25
 *\author 张海涛
 *\par    Revision History:
 */
class CHttpPost
{
public:
	/**
	 *\fn         CHttpPost()
	 *\brief      缺省构造函数。
     */
	CHttpPost();

	/**
	 *\fn         CHttpPost(const char *ip, unsigned short port, const char *path)
	 *\brief      构造函数。
	 *\param[in]  ip   IP地址。
	 *\param[in]  port 端口地址。
	 *\param[in]  path 路径。
     */
	CHttpPost(const char *ip, unsigned short port, const char *path);

	/**
	 *\fn         ~CHttpPost()
	 *\brief      析构函数。
     */
	~CHttpPost();

private:
	std::string ip_;

	unsigned short port_;

	std::string path_;

	int status_;

	char *response_;

	DWORD responseLen_;


public:
	/**
	 *\fn         setAddr(const char *ip, unsigned short port, const char *path)
	 *\brief      设置地址参数。
	 *\param[in]  ip   IP地址。
	 *\param[in]  port 端口地址。
	 *\param[in]  path 路径。
	 */
	void setAddr(const char *ip, unsigned short port, const char *path) { ip_ = ip; port_ = port; path_ = path; }

	/**
	 *\fn         SendPostRequest(void *data, int len, const char *filename)
	 *\brief      发送数据。
	 *\param[in]  data     数据。
	 *\param[in]  len      数据长。
	 *\param[in]  filename 文件名。
	 *\return     是否成功
	 */
	bool SendPostRequest(void *data, int len, const char *filename);

	/**
	 *\fn         getResponse()
	 *\brief      得到应答数据。
	 *\return     应答数据
	 */
	void* getResponse() { return response_; }

	/**
	 *\fn         getResponseLen()
	 *\brief      得到应答数据长度。
	 *\return     应答数据长度
	 */
	int getResponseLen() { return responseLen_; }

	/**
	 *\fn         getStatusCode()
	 *\brief      得到状态码。
	 *\return     状态码
	 */
	int  getStatusCode() { return status_; }
};
