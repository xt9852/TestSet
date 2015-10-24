
#include "StdAfx.h"
#include "PrePack.h"
#include "BuffPool.h"
#include "PackQueue.h"



namespace XT_IOCP
{

	/**
	 *\fn         PrePack()
	 *\brief      缺省构造函数。
	 */
	PrePack::PrePack(void)
		:cmdType_(CMD_TYPE_MYSELF),
		inQueue_(NULL),
		buffPool_(NULL),
		oneBuffSize_(0),
		dataLen_(0),
		buffSize_(0),
		buff_(NULL)
	{
		InitializeCriticalSection(&csUsed_);
	}

	/**
	*\fn         ~PrePack()
	*\brief      析构函数。
	*/
	PrePack::~PrePack(void)
	{
		if (NULL != buff_)
		{
			delete[] buff_;
			buff_ = NULL;
		}
		DeleteCriticalSection(&csUsed_);
	}

	/**
	 *\fn         Init(int cmdType, PackQueue *inQueue, BuffPool *buffPool)
	 *\brief      初使化预处理包。
	 *\param[in]  cmdType  命令类型。
	 *\param[in]  inQueue  数据包输入队列。
	 *\param[in]  buffPool 内存池。
	 *\return     是否成功
	 */
	bool PrePack::Init(int cmdType, PackQueue *inQueue, BuffPool *buffPool)
	{
		if (NULL == inQueue || NULL == buffPool) return false;

		cmdType_ = cmdType;
		inQueue_ = inQueue;
		buffPool_ = buffPool;

		oneBuffSize_ = 10;//buffPool->getSize();
		buffSize_ = oneBuffSize_ * 4;
		buff_ = new char[buffSize_];

		return true;
	}

	/**
	*\fn         Add(PCLIENT client, long len, void *buffer)
	*\brief      添加一个数据包。
	*\param[in]  client  客户端对象。
	*\param[in]  len     数据长。
	*\param[in]  buffer  数据包。
	*\return     是否成功
	*/
	bool PrePack::Add(PCLIENT client, long len, PVOID buffer)
	{
		EnterCriticalSection(&csUsed_);

		switch(cmdType_)
		{
		case CMD_TYPE_MYSELF:
			{
				long newDataLen = 0;

				PPACK pack = (PPACK)buffer;
				long packLen = pack->getPackLen();
				if (packLen == len && pack->flag == packFlag)	// 是一个完整的包
				{
					inQueue_->Add(client, buffer, len);
				}
				else
				{
					newDataLen = dataLen_ + len;			// 加入当前数据后的数据长

					if (newDataLen > buffSize_)				// 合并数据后长度大于缓冲区
					{
						long newBuffNum = (newDataLen / oneBuffSize_) + 1;
						buffSize_ = newBuffNum * oneBuffSize_;
						char *newBuff = new char[buffSize_];// 重新分配内存
						if (NULL == newBuff)
						{
							//g_ProFile.m_pLog->println(LOG_ERROR, _T("CPreparePack::Add new buff error, thread exit !"));
							//delete[] buff_;
							return false;
						}

						//g_ProFile.m_pLog->println(LOG_INFO, _T("CPreparePack::Add new memory %d bytes socket= %d"), m_dwBuffSize, pClient);

						memcpy(newBuff, buff_, dataLen_);	// 将原数据拷贝到新的缓冲区中
						delete[] buff_;
						buff_ = newBuff;
					}

					memcpy(buff_ + dataLen_, buffer, len);	// 将当前数据加入到缓冲区尾部
					dataLen_ += len;

					buffPool_->Free(buffer);				// 回收缓冲区

					while ((NULL != buff_) && (dataLen_ > 0))
					{
						PPACK newPack = (PPACK)buff_;
						if (packFlag != newPack->flag)		// 如果不是包头
						{
							char *pos = buff_;
							long *flag = (long*)buff_;

							for (long i = 0; i < (dataLen_ - 3); i++)
							{
								if (packFlag == *flag)		// 查找包头标记
								{
									dataLen_ -= i;
									memcpy(buff_, pos, dataLen_);
								}
								else
								{
									pos++;
									flag = (long*)pos;
								}
							}

							break;
						}
						else if ((newDataLen = newPack->getPackLen()) <= dataLen_)
						{
							// 是一个完整的消息包
							PPACK newPack = (PPACK)buffPool_->Get(1);
							if (NULL == newPack)
							{
								break;
							}

							memcpy(newPack, buff_, newDataLen);
							inQueue_->Add(client, newPack, newDataLen);

							dataLen_ -= newDataLen;
							memcpy(buff_, buff_ + newDataLen, dataLen_);
						}
						else
						{
							break;
						}
					}
				}

				break;
			}		
		case CMD_TYPE_HTTP:
			{
				inQueue_->Add(client, buffer, len);
				break;
			}
		case CMD_TYPE_MMS:
			{
				unsigned char *buf = (unsigned char *)buffer;
				ULONGLONG flag = 0;

				memcpy(&flag, buffer, 8);

				if (0xb00bface4a000001 == flag || 0xb00bface00000001 == flag)	//0xb00bface00000001
					inQueue_->Add(client, buffer, len);
				else
					//g_ProFile.m_pLog->println(LOG_ERROR, _T("CPreprocPack::Add Error MMS"));
				break;
			}
		default:
			TRACE(_T("CPreprocPack::Add CmdType Error\n"));
			break;
		}

		LeaveCriticalSection(&csUsed_);
		return true;
	}

}