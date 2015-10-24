// OptimizationTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RunProcess.h"
#include <tlhelp32.h> // CreateToolhelp32Snapshot


RunProcess::RunProcess()
	:param_(NULL),
	procFunc_(NULL),
	process_(NULL),
	thread_(NULL)
{
}

RunProcess::~RunProcess()
{
    Close();
}

/**
 *\fn         Close()
 *\brief      关闭此程序。
 *\return     无
 */
void RunProcess::Close()
{
	TerminateProcess(process_, 0);
	CloseHandle(process_);
	CloseHandle(thread_);

	process_ = NULL;
	thread_ = NULL;
}

/**
 *\fn         CreateAnonymousPipe(HANDLE &write, HANDLE &read)
 *\brief      创建匿名管道。
 *\param[in]  write  输出管道。
 *\param[in]  read  输入管道。
 *\return     是否成功
 */
bool RunProcess::CreateAnonymousPipe(HANDLE &write, HANDLE &read)
{
	SECURITY_ATTRIBUTES sa; 
	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL; 
	sa.bInheritHandle = TRUE;

	return (TRUE == CreatePipe(&read, &write, &sa, 0));
}

/**
 *\fn         ReadAllPipe(HANDLE outRead, HANDLE outWrite, unsigned char *buffer, int size)
 *\brief      创建管道。
 *\param[in]  outRead   被调程序的输出管道的读端。
 *\param[in]  outWrite  被调程序的输出管道的写端。
 *\param[out] buffer    数据缓冲区。
 *\param[out] size      数据缓冲区长。
 *\return     读取的数据长度
 */
int RunProcess::ReadAllPipe(HANDLE outRead, HANDLE outWrite, unsigned char *buffer, int size)
{
	CloseHandle(outWrite); // 如果不关键写管道则会阻塞在ReadFile

	int count = 0;
	DWORD num = 0;

	while (ReadFile(outRead, (void*)buffer, size, &num, NULL))
	{
		count += num;
		printf("%s\n", buffer);
	}

	CloseHandle(outRead);

	return count;
}

/**
 *\fn         ProcPipeData(HANDLE outRead, HANDLE outWrite, HANDLE process)
 *\brief      读取管道。
 *\param[in]  outRead   被调程序的输出管道的读端。
 *\param[in]  outWrite  被调程序的输出管道的写端。
 *\param[out] buffer 数据缓冲区。
 *\param[out] size   数据缓冲区长。
 *\return     读取的数据长度
 */
void RunProcess::ProcPipeData(HANDLE outRead, HANDLE outWrite, HANDLE process)
{
	DWORD num = 0;
	int dataLen = 1024*1024;
	char *data = new char[dataLen];

	for (int i = 0; true; i++)
	{
		int ret = WaitForSingleObject(process, 100);

		if (ret == WAIT_OBJECT_0)
		{
			CloseHandle(outWrite); // 如果不关键写管道则会阻塞在ReadFile
		}

		//ATLTRACE("ReadFile %d ", ret);

		if (PeekNamedPipe(outRead, (void*)data, dataLen, &num, NULL, NULL) && (num != 0))
		{
			ReadFile(outRead, (void*)data, dataLen, &num, NULL);
		}

		//ATLTRACE("over\n");

		if (num != 0)
		{
			data[num] = '\0';
			procFunc_(param_, data, num);
		}

		if (ret == WAIT_OBJECT_0)
		{
			CloseHandle(outRead);
			break;
		}
	}

	delete data;
}

/**
 *\fn         Run(const char *name, const char *path, const char *param, bool show, 
 *\n			  HANDLE write, HANDLE read)
 *\brief      创建进程。
 *\param[in]  name      进程名。
 *\param[in]  path      进程所在的路径。
 *\param[in]  param     参数。
 *\param[in]  show      是否显示界面。
 *\param[in]  inRead    被调程序的输入管道的读端。
 *\param[in]  outRead   被调程序的输出管道的读端。
 *\param[in]  outWrite  被调程序的输出管道的写端。
 *\return     是否成功
 */
bool RunProcess::Run(const char *name,
	const char *path,
	const char *param,
	bool show,
	HANDLE inRead,
	HANDLE outRead,
	HANDLE outWrite)
{
	if ((name == NULL) || (path == NULL) || (param == NULL)){
		return false;
	}

	char cmd[MAX_PATH] = "";
	char temp[10] = "";
	const char *cmdPath = path;
	
	if (0 == strcmp(path, ""))
	{
		cmdPath = NULL;
	}
	else if (path[strlen(path)-1] != '\\')
	{
		strcpy(temp, "\\");
	}

	sprintf(cmd, "%s%s%s %s", path, temp, name, param);

	DWORD exitCode = 0;
	STARTUPINFOA si = {0};
	PROCESS_INFORMATION pi = {0};
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = show ? SW_SHOW : SW_HIDE;

	if (outWrite != NULL || inRead != NULL)
	{
		si.dwFlags    = si.dwFlags | STARTF_USESTDHANDLES;
		si.hStdInput  = inRead;
		si.hStdError  = outWrite;
		si.hStdOutput = outWrite;
	}

	BOOL retValue = CreateProcessA(NULL, (LPSTR)cmd, NULL, NULL, TRUE, CREATE_NEW_PROCESS_GROUP, NULL, cmdPath, &si, &pi);

	process_ = pi.hProcess;
	thread_ = pi.hThread;

	if (outRead != NULL)
	{
		ProcPipeData(outRead, outWrite, pi.hProcess);
	}
	else
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		GetExitCodeProcess(pi.hProcess, &exitCode);
	}

	return retValue?true:false;
}