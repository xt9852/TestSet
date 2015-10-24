#pragma once
#include <windows.h>

/**
 *\fn         (*PROCESS_DATA_FUNC)(void *param, char *data, int len)
 *\brief      用户的回调函数。
 *\param[in]  param      用户自己设置的参数。
 *\param[in]  data       管道输出的数据。
 *\param[in]  len        管道输出的数据长度。
 *\return     无
 */
typedef void (*PROCESS_DATA_FUNC)(void *param, char *data, int len);


/**
 *\class  RunProcess
 *\brief  调用一个程序,可以是exe也可是bat脚本
 *\date   2012-07-03
 *\author 张海涛
 *\par    Revision History:
 *\n      0.1     2007-07-03   张海涛   创建此类
 */
class RunProcess
{
public:
	RunProcess();
	~RunProcess();

private:
	PROCESS_DATA_FUNC	procFunc_;	// 用户的回调函数
	void				*param_;	// 用户自定义的参数

	HANDLE				process_;	// 进程句柄
	HANDLE				thread_;	// 主线程句柄

public:
	/**
	 *\fn         setParam(void *param)
	 *\brief      设置用户参数,当调用回调时再传给用户。
	 *\param[in]  param     用户参数。
	 *\return     无
	 */
	void setParam(void *param) { param_ = param; }

	/**
	 *\fn         setProcFunc(PROCESS_DATA_FUNC procFunc)
	 *\brief      设置用户回调函数指针。
	 *\param[in]  procFunc  回调函数指针。
	 *\return     无
	 */
	void setProcFunc(PROCESS_DATA_FUNC procFunc) { procFunc_ = procFunc; }

	/**
	 *\fn         close()
	 *\brief      关闭此程序。
	 *\return     无
	 */
	void Close();

	/**
	 *\fn         Run(const char *name, const char *path, const char *param, bool show, 
	 *\n			  HANDLE write, HANDLE read)
	 *\brief      创建进程。
	 *\param[in]  name      进程名。
	 *\param[in]  path      进程所在的路径。
	 *\param[in]  param     参数。
	 *\param[in]  inRead    被调程序的输入管道的读端。
	 *\param[in]  outRead   被调程序的输出管道的读端。
	 *\param[in]  outWrite  被调程序的输出管道的写端。
	 *\return     是否成功
	 */
	bool Run(const char *name, 
		const char *path, 
		const char *param, 
		bool show, 
		HANDLE inRead,
		HANDLE outRead,
		HANDLE outWrite);	
	
	/**
	 *\fn         CreateAnonymousPipe(HANDLE &write, HANDLE &read)
	 *\brief      创建匿名管道。
	 *\param[in]  write     输出管道。
	 *\param[in]  read      输入管道。
	 *\return     是否成功
	 */
	bool CreateAnonymousPipe(HANDLE &write, HANDLE &read);

	/**
	 *\fn         ReadAllPipe(HANDLE outRead, unsigned char *buffer, int size)
	 *\brief      创建管道。
	 *\param[in]  outRead   被调程序的输出管道的读端。
	 *\param[in]  outWrite  被调程序的输出管道的写端。
	 *\param[out] buffer    数据缓冲区。
	 *\param[out] size      数据缓冲区长。
	 *\return     读取的数据长度
	 */
	int ReadAllPipe(HANDLE outRead, HANDLE outWrite, unsigned char *buffer, int size);

	/**
	 *\fn         ProcPipeData(HANDLE write, HANDLE read, HANDLE process)
	 *\brief      读取管道。
	 *\param[in]  outRead   被调程序的输出管道的读端。
	 *\param[in]  outWrite  被调程序的输出管道的写端。
	 *\param[out] buffer    数据缓冲区。
	 *\param[out] size      数据缓冲区长。
	 *\return     读取的数据长度
	 */
	void ProcPipeData(HANDLE outRead, HANDLE outWrite, HANDLE process);
};