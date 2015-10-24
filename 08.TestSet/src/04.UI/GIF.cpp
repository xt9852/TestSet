#include "StdAfx.h"
#include "gif.h"


/**
 *\fn         CGIF()
 *\brief      缺省构造函数。
 */
CGIF::CGIF()
{
	memset(&gif_, 0, sizeof(GIF));
}

/**
 *\fn         ~CGIF()
 *\brief      析构函数。
 */
CGIF::~CGIF()
{
	Unload();
}

/**
 *\fn         Load(const char *filename)
 *\brief      加载文件。
 *\param[in]  filename  文件名。
 *\return     是否成功
 */
bool CGIF::Load(const char *filename)
{
	if (NULL == filename) return false;

	Unload();

	FILE *file = fopen(filename, "rb");

	if (NULL == file) return false;

	fseek(file, 0, SEEK_END);

	int fileSize = ftell(file);

	fseek(file, 0, SEEK_SET);

	unsigned char *data = new unsigned char[fileSize];

	fread(data, fileSize, 1, file);

	fclose(file);

	return ProcData(data);
}

/**
 *\fn         ProcData(unsigned char *data)
 *\brief      处理GIF文件。
 *\param[in]  data  文件数据。
 *\return     是否成功
 */
bool CGIF::ProcData(unsigned char *data)
{
	int headLen = sizeof(GIFHEADER);
	int scrDesLen = sizeof(GIFSCRDESC);

	memcpy(&gif_.Head, data, headLen);
	data += headLen;

	memcpy(&gif_.ScrDesc, data, scrDesLen);
	data += scrDesLen;

	if (gif_.ScrDesc.GlobalFlag.GlobalPal)
	{
		gif_.nColorNum = (UINT)pow(2.0, gif_.ScrDesc.GlobalFlag.PalBits + 1);
		int nColorTableLen = sizeof(COLORTABLE) * gif_.nColorNum;
		memcpy(gif_.GlobalColorTable, data, nColorTableLen);
		data += nColorTableLen;
	}

	bool exit = false;
	while(!exit)
	{
		switch (*data)
		{
		case 0x21:	// 扩展块
			{
				switch (*(data+1))
				{
				case 0x01:	// 图形文本扩展
					{
						PLAINTEXTEX plainex = {0};
						plainex.byFlag1     = *data++;
						plainex.byFlag2     = *data++;
						plainex.byBlockSize = *data++;
						plainex.byOffsetX   = *data++;
						plainex.byOffsetY   = *data++;
						plainex.byWidth     = *data++;
						plainex.byHeight    = *data++;
						plainex.byCelWidth  = *data++;
						plainex.byCelHeight = *data++;
						plainex.byTestColor = *data++;
						plainex.byBackColor = *data++;
						strcpy(plainex.szText, (LPSTR)data);
						data += strlen(plainex.szText);
						plainex.byBlockTerm = *data++;
						ATLTRACE("GIF LAINTEXTEX %s\n", plainex.szText);
						break;
					}
				case 0xF9:	// 图像控制扩展
					{
						PGIFFRAME pFrame = new GIFFRAME;
						memset(pFrame, 0, sizeof(GIFFRAME));
						memcpy(&pFrame->gce, data, sizeof(GRAPHICCONTROLEX));
						data += sizeof(GRAPHICCONTROLEX);

						pFrame->byFrameId = gif_.nGifFrameNum++;
						if (gif_.pGifFrame == NULL)
						{
							gif_.pGifFrame = pFrame;
						}
						else
						{
							PGIFFRAME pEndFrame = gif_.pGifFrame;
							while(pEndFrame->pNext != NULL) pEndFrame = pEndFrame->pNext;
							pEndFrame->pNext = pFrame;
						}

						break;
					}
				case 0xFE:	// 注释扩展
					{
						COMMENTEX commentex = {0};
						commentex.byFlag1 = *data++;
						commentex.byFlag2 = *data++;
						commentex.byTextLen = *data++;
						memcpy(commentex.szText, data, commentex.byTextLen);
						data += commentex.byTextLen;
						commentex.byBlockTerm = *data++;
						ATLTRACE("GIF COMMENTEX: %s\n", commentex.szText);
						break;
					}
				case 0xFF:	// 应用扩展
					{
						APPEX appex = {0};
						appex.byFlag1 = *data++;
						appex.byFlag2 = *data++;
						appex.byBlockSize = *data++;
						memcpy(appex.byIdentifier, data, 8);
						data += 8;
						memcpy(appex.byCode, data, 3);
						data += 3;
						appex.byDataLen = *data++;
						memcpy(appex.byData, data, appex.byDataLen);
						data += appex.byDataLen;
						appex.byBlockTerm = *data++;
					break;
					}
				default:
					{
						exit = true;
						ATLTRACE("EX ERROR\n");
						break;
					}
				}

			break;
			}
		case 0x2c:	// 图像
			{
				if (NULL == gif_.pGifFrame)
				{
					gif_.pGifFrame = new GIFFRAME;
					memset(gif_.pGifFrame, 0, sizeof(GIFFRAME));
					gif_.pGifFrame->byFrameId = gif_.nGifFrameNum++;
				}
				
				PGIFFRAME pFrame = gif_.pGifFrame;
				while(pFrame->pNext != NULL) pFrame = pFrame->pNext;

				pFrame->gi.byFlag = *data++;
				pFrame->gi.wLeft = *(WORD*)data;
				data += 2;
				pFrame->gi.wTop = *(WORD*)data;
				data += 2;
				pFrame->gi.wWidth = *(WORD*)data;
				data += 2;
				pFrame->gi.wHeight = *(WORD*)data;
				data += 2;
				memcpy(&(pFrame->gi.LocalFlag), data, 1);
				data++;

				if (pFrame->gi.LocalFlag.LocalPal)
				{
					pFrame->gi.nColorNum = (UINT)pow(2.0, pFrame->gi.LocalFlag.PalBits + 1);
					int nColorTableLen = sizeof(COLORTABLE) * pFrame->gi.nColorNum;
					memcpy(pFrame->gi.LocolColorTable, data, nColorTableLen);
					data += nColorTableLen;
				}

				pFrame->gi.byLZWcode = *data++;

				while(*data != 0)
				{
					PDATASUBBLOCK pData = new DATASUBBLOCK;
					memset(pData, 0, sizeof(DATASUBBLOCK));
					pData->byDataLen = *data++;
					memcpy(pData->pbyData, data, pData->byDataLen);
					data += pData->byDataLen;

					if (pFrame->gi.pData == NULL)
					{
						pFrame->gi.pData = pData;
					}
					else
					{
						PDATASUBBLOCK pTemp = pFrame->gi.pData;
						while(pTemp->pNext != NULL) pTemp = pTemp->pNext;
						pTemp->pNext = pData;
					}

					pData = pData->pNext;
					pFrame->gi.nDataBlcokNum++;
				}
				data++;

			break;
			}
		case 0x3B:	// 文件结束
			{
				exit = true;
				break;
			}
		default:
			{
				exit = true;
				break;
			}
		}
	}

	// BMP头
	gif_.BmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	gif_.BmpInfo.bmiHeader.biWidth = gif_.ScrDesc.wWidth;
	gif_.BmpInfo.bmiHeader.biHeight = gif_.ScrDesc.wHeight;
	gif_.BmpInfo.bmiHeader.biPlanes = 1;
	gif_.BmpInfo.bmiHeader.biBitCount = 24;
	gif_.BmpInfo.bmiHeader.biCompression = BI_RGB;
	gif_.BmpInfo.bmiHeader.biSizeImage = 0;
	gif_.BmpInfo.bmiHeader.biXPelsPerMeter = 0;
	gif_.BmpInfo.bmiHeader.biYPelsPerMeter = 0;
	gif_.BmpInfo.bmiHeader.biClrUsed = 0;
	gif_.BmpInfo.bmiHeader.biClrImportant = 0;

	PGIFFRAME pFrame = gif_.pGifFrame;
	PGIFFRAME pLastFrame = NULL;

	while (NULL != pFrame)
	{
		pFrame->pBmpData = GetFrameBmpData(pFrame, pLastFrame);
		pLastFrame = pFrame;
		pFrame = pFrame->pNext;
	}
	
	DWORD dwPos1 = 0;
	DWORD dwPos2 = 0;
	WORD wWidth = gif_.ScrDesc.wWidth;
	WORD wHeight = gif_.ScrDesc.wHeight;
	WORD wLineInter = (wWidth%4 != 0) ? (4-(wWidth*3)%4) : 0;
	WORD wLineDataLen = wWidth * 3 + wLineInter;
	PBYTE pLine = new BYTE[wLineDataLen];
	pFrame = gif_.pGifFrame;

	while (NULL != pFrame)
	{
		PBYTE pPixData = pFrame->pBmpData;
		for (WORD i = 0; i < wHeight / 2; i++)
		{
			dwPos1 = i * wLineDataLen;
			dwPos2 = (wHeight - i - 1) * wLineDataLen;
			memcpy((void*)pLine, (void*)&(pPixData[dwPos1]), wLineDataLen);
			memcpy((void*)&(pPixData[dwPos1]), (void*)&(pPixData[dwPos2]), wLineDataLen);
			memcpy((void*)&(pPixData[dwPos2]), (void*)pLine, wLineDataLen);
		}

		pLastFrame = pFrame;
		pFrame = pFrame->pNext;
	}

	delete[] pLine;
	return true;
}

/**
 *\fn         Unload()
 *\brief      清空数据。
 */
void CGIF::Unload()
{
	gif_.nGifFrameNum = 0;

	while (gif_.pGifFrame != NULL)
	{
		PGIFFRAME pFrame = gif_.pGifFrame;
		PGIFFRAME pNextFrame = gif_.pGifFrame->pNext;
		while (pFrame->gi.pData != NULL)
		{
			PDATASUBBLOCK pNextData = pFrame->gi.pData->pNext;
			delete pFrame->gi.pData;

			pFrame->gi.pData = pNextData;
		}

		if (NULL != pFrame->pBmpData) delete[] pFrame->pBmpData;
		delete pFrame;
		gif_.pGifFrame = pNextFrame;
	}
	memset(&gif_, 0, sizeof(GIF));
}

/**
 *\fn         getDelayTime()
 *\brief      得到间隔时间。
 *\return     间隔时间
 */
int CGIF::getDelayTime(int frameId)
{
	PGIFFRAME pFrame = gif_.pGifFrame;
	for (int i = 0; (i < frameId) && (NULL != pFrame); i++)	pFrame = pFrame->pNext;

	return pFrame->gce.wDelayTime;
}

/**
 *\fn         GetFrameBmpData(PGIFFRAME frame, PGIFFRAME lastFrame)
 *\brief      得到位图数据。
 *\param[in]  frame      帧数据。
 *\param[in]  lastFrame  上一帧数据。
 *\return     是否成功
 */
LPBYTE CGIF::GetFrameBmpData(PGIFFRAME frame, PGIFFRAME lastFrame)
{
	if (NULL == frame) return NULL;

	LPBYTE pPixIndex = DecodeImageData(frame);	// 解压缩,得到颜色索引

	WORD wImageWidth = frame->gi.wWidth;
	WORD wImageHeight = frame->gi.wHeight;
	WORD wGifWidth = gif_.ScrDesc.wWidth;
	WORD wGifHeight = gif_.ScrDesc.wHeight;
	BYTE byTranColorIndex = frame->gce.byTransparentColorIndex;

	int nLineInter = (wGifWidth % 4 != 0) ? 4 - (wGifWidth * 3) % 4 : 0;
	int nLineDataLen = wGifWidth * 3 + nLineInter;
	int nBmpDataLen = wGifHeight * nLineDataLen;
	int nPixNum = wImageWidth * wImageHeight;
	int nPos = 0;
	
	BYTE* pPixData = new BYTE[nBmpDataLen];
	ATLASSERT(NULL != pPixData);

	if (!frame->gi.LocalFlag.Interlace)	// 非交插
	{
		bool bUseTranColor = frame->gce.Flag.t;

// 		// 填前面的空白,应当只有不是第一帧才有
// 		if ((pFrame->gi.wTop > 0 || pFrame->gi.wLeft > 0) && (NULL != pLastFrame))
// 		{
// 			nPos = nLineDataLen * pFrame->gi.wTop  + pFrame->gi.wLeft * 3;
// 			for (int i = 0; i < nPos; i++)
// 				pPixData[i] = pLastFrame->pBmpData[i];
// 		}
// 
// 		// 图像数据
// 		for (int i = 0; i < nPixNum; i++)
// 		{
// 			if (pPixIndex[i] == byTranColorIndex)
// 			{
// 				if (NULL != pLastFrame)
// 				{
// 					pPixData[nPos] = pLastFrame->pBmpData[nPos++];
// 					pPixData[nPos] = pLastFrame->pBmpData[nPos++];
// 					pPixData[nPos] = pLastFrame->pBmpData[nPos++];
// 				}
// 			}
// 			else
// 			{
// 				pPixData[nPos++] = gif_.GlobalColorTable[ pPixIndex[i] ].byB;
// 				pPixData[nPos++] = gif_.GlobalColorTable[ pPixIndex[i] ].byG;
// 				pPixData[nPos++] = gif_.GlobalColorTable[ pPixIndex[i] ].byR;
// 			}
// 
// 			if (((i+1) % wImageWidth == 0) && (i != 0))		// 图像一行开始
// 			{
// 				int nInter = (wGifWidth - wImageWidth) * 3;	// 行间空白
// 
// 				if (NULL != pLastFrame)
// 				{
// 					for (int j = 0; j < nInter; j++)
// 						pPixData[nPos + j] = pLastFrame->pBmpData[nPos + j];
// 				}
// 
// 				nPos += nInter;
// 				nPos += nLineInter;	// BMP要求一行4个字节对齐
// 			}
// 		}
// 
// 		// 后面空白,应当只有不是第一帧才有
// 		if (nPos < nBmpDataLen && NULL != pLastFrame)
// 		{
// 			for (int i = 0; i < nBmpDataLen - nPos - 1; i++)
// 				pPixData[nPos + i] = pLastFrame->pBmpData[nPos + i];
// 		}

		// 填前面的空白,应当只有不是第一帧才有
		if ((frame->gi.wTop > 0) || (frame->gi.wLeft > 0))
		{
			nPos = nLineDataLen * frame->gi.wTop  + frame->gi.wLeft * 3;

			if (bUseTranColor && (NULL != lastFrame))	// 应用透明色
			{
				memcpy(pPixData, lastFrame->pBmpData, nPos);
			}
			else
			{
				memset(pPixData, 255, nPos);
			}
		}

		// 图像数据
		for (int i = 0; i < nPixNum; i++)
		{
			if (bUseTranColor && (pPixIndex[i] == byTranColorIndex) && (NULL != lastFrame))
			{
				pPixData[nPos] = lastFrame->pBmpData[nPos++];
				pPixData[nPos] = lastFrame->pBmpData[nPos++];
				pPixData[nPos] = lastFrame->pBmpData[nPos++];
			}
			else
			{
				pPixData[nPos++] = gif_.GlobalColorTable[ pPixIndex[i] ].byB;
				pPixData[nPos++] = gif_.GlobalColorTable[ pPixIndex[i] ].byG;
				pPixData[nPos++] = gif_.GlobalColorTable[ pPixIndex[i] ].byR;
			}

			if (((i+1) % wImageWidth == 0) && (i != 0))		// 图像一行开始
			{
				int nInter = (wGifWidth - wImageWidth) * 3;	// 行间空白

				if (bUseTranColor && (NULL != lastFrame))
					memcpy(&pPixData[nPos], &(lastFrame->pBmpData[nPos]), nInter);
				else
					memset(&pPixData[nPos], 255, nInter);

				nPos += nInter + nLineInter;	// BMP要求一行4个字节对齐
			}
		}

		// 后面空白,应当只有不是第一帧才有
		if (nPos < nBmpDataLen)
		{
			if (bUseTranColor && (NULL != lastFrame))	// 应用透明色
				memcpy(&pPixData[nPos], &(lastFrame->pBmpData[nPos]), nBmpDataLen - nPos - 1);
			else
				memset(&pPixData[nPos], 255, nBmpDataLen - nPos - 1);
		}
	}
	else
	{
		delete[] pPixIndex;
		delete[] pPixData;		
		return NULL;

// 		int pass = 0;//当前通道
// 		while (pass < 4)
// 		{
// 			// 总共有4个通道
// 			if (pass == 1)
// 			{
// 				p = tempPointer;
// 				p += (2 * width * 4);
// 			}
// 			else if (pass == 2)
// 			{
// 				p = tempPointer;
// 				p += (1 * width * 4);
// 			}
// 			else if (pass == 3)
// 			{
// 				p = tempPointer;
// 				p += (4 * width * 4);
// 			}
// 			int i = 0;
// 			for (i = 0; i < pixel.Length; )
// 			{
// 				Color c = Color.FromArgb(colorTable[pixel[i++]]);
// 				*p++ = c.B;
// 				*p++ = c.G;
// 				*p++ = c.R;
// 				*p++ = c.A;
// 				if (i % (iw) == 0)
// 				{
// 					p += (width - iw) * 4;
// 					p += width * 8 * 4;
// 					if (ih % 4 == 0)
// 					{
// 						pass++;
// 						break;
// 					}
// 				}
// 			}
// 		}
	}

	delete[] pPixIndex;
	return pPixData;
}

/**
 *\fn         DecodeImageData(PGIFFRAME frame)
 *\brief      LZW压缩算法的解码数据。
 *\param[in]  pFrame  帧数据。
 *\return     是否成功
 */
LPBYTE CGIF::DecodeImageData(PGIFFRAME frame)
{
	if (NULL == frame) return NULL;

	int MaxStackSize = 4096;
	int NullCode = -1;
	int pixelCount = frame->gi.wWidth * frame->gi.wHeight;// 获取原图像的像素数，公式为 像素数 = 图像长度*图像高度
	LPBYTE pixels = new byte[pixelCount];
	int dataSize = gif_.pGifFrame->gi.byLZWcode;			// 图像编码流的第一个字节(byte)存放的是数据位大小，在gif通常为1,4,8
	int codeSize = dataSize + 1;			// 编码位大小，根据lzw算法的要求，编码位的大小 = 数据位大小+1 ，针对gif，有如下对应关系 1->3 4->5 ->9,而最大的codeSize为12
	int clearFlag = 1 << dataSize;			// 在lzw算法有两个特殊标记，clearFlag为其中的清除标记，此后的编码将重头再来，这样做可以防止编码位无限增大
	int endFlag = clearFlag + 1;			// lzw算法两个特殊标记之一，endFlag为结束标记，表示一次编码的结束  endFlag=clearFlag+1
	int available = endFlag + 1;			// 初始的可用编码大小，因为0-(clear-1)为元数据，所以均可用，不必研究，此处从能形成压缩的编码开始算起

	int code = NullCode;					// 用于存储当前的编码值
	int old_code = NullCode;				// 用于存储上一次的编码值
	int code_mask = (1 << codeSize) - 1;	// 表示编码的最大值，如果codeSize=5,则code_mask=31
	int bits = 0;							// 在编码流中数据的保存形式为byte，而实际编码过程中是找实际编码位来存储的，比如当codeSize=5的时候，那么实际上5bit的数据就应该可以表示一个编码，这样取出来的1个字节就富余了3个bit，这3个bit用于和第二个字节的后两个bit进行组合，再次形成编码值，如此类推

	int prefix[4096] = {0};					// 用于保存前缀的集合
	int suffix[4096] = {0};					// 用于保存后缀
	int pixelStatck[4096 + 1] = {0};		// 用于临时保存数据流

	int top = 0;
	int count = 0;							// 在下面的循环中，每次会获取一定量的编码的字节数组，而处理这些数组的时候需要1个个字节来处理，count就是表示还要处理的字节数目
	int bi = 0;								// count表示还剩多少字节需要处理，而bi则表示本次已经处理的个数
	int i = 0;								// i代表当前处理得到像素数

	int data = 0;							// 表示当前处理的数据的值
	int first = 0;							// 一个字符串重的第一个字节
	int inCode = NullCode;					// 在lzw中，如果认识了一个编码所代表的数据entry，则将编码作为下一次的prefix，此处inCode代表传递给下一次作为前缀的编码值

	// 先生成元数据的前缀集合和后缀集合，元数据的前缀均为0，而后缀与元数据相等，同时编码也与元数据相等
	for (code = 0; code < clearFlag; code++)
	{
		// 前缀初始为0
		prefix[code] = 0;
		// 后缀=元数据=编码
		suffix[code] = (byte)code;
	}

	int nBlockNum = 0;
	LPBYTE buffer = NULL;

	while (i < pixelCount)		// 最大像素数已经确定为pixelCount = width * width
	{
		if (top == 0)
		{
			if (bits < codeSize)// 如果当前的要处理的bit数小于编码位大小，则需要加载数据
			{
				if (count == 0)	// 如果count为0，表示要从编码流中读一个数据段来进行分析
				{
					if (NULL != frame)
					{
						PDATASUBBLOCK pData = frame->gi.pData;

						for(int i = 0; i < nBlockNum && NULL != pData->pNext; i++)	// 找到想要的数据块
						{
							pData = pData->pNext;
						}

						if (pData != NULL)
						{
							buffer = pData->pbyData;
							count = pData->byDataLen;
							nBlockNum++;
						}
					}

					if (count == 0)
					{
						// 再次想读取数据段，却没有读到数据，此时就表明已经处理完了
						break;
					}
					// 重新读取一个数据段后，应该将已经处理的个数置0
					bi = 0;
				}
				// 获取本次要处理的数据的值
				data += buffer[bi] << bits;	// 此处为何要移位呢，比如第一次处理了1个字节为176，第一次只要处理5bit就够了，剩下3bit留给下个字节进行组合。也就是第二个字节的后两位+第一个字节的前三位组成第二次输出值
				bits += 8;					// 本次又处理了一个字节，所以需要+8
				bi++;						// 将处理下一个字节
				count--;					// 已经处理过的字节数+1
				continue;
			}
			// 如果已经有足够的bit数可供处理，下面就是处理过程
			// 获取编码
			code = data & code_mask;	// 获取data数据的编码位大小bit的数据
			data >>= codeSize;			// 将编码数据截取后，原来的数据就剩下几个bit了，此时将这些bit右移，为下次作准备
			bits -= codeSize;			// 同时需要将当前数据的bit数减去编码位长，因为已经得到了处理。

			// 下面根据获取的code值来进行处理
			if (code > available || code == endFlag)
			{
				//当编码值大于最大编码值或者为结束标记的时候，停止处理
				break;
			}
			if (code == clearFlag)
			{
				// 如果当前是清除标记，则重新初始化变量，好重新再来
				codeSize = dataSize + 1;
				// 重新初始化最大编码值
				code_mask = (1 << codeSize) - 1;
				// 初始化下一步应该处理得编码值
				available = clearFlag + 2;
				// 将保存到old_code中的值清除，以便重头再来
				old_code = NullCode;
				continue;
			}
			// 下面是code属于能压缩的编码范围内的的处理过程
			if (old_code == NullCode)
			{
				// 如果当前编码值为空,表示是第一次获取编码
				pixelStatck[top++] = suffix[code];//获取到1个数据流的数据
				// 本次编码处理完成，将编码值保存到old_code中
				old_code = code;
				// 第一个字符为当前编码
				first = code;
				continue;
			}
			inCode = code;
			if (code == available)
			{
				// 如果当前编码和本次应该生成的编码相同
				pixelStatck[top++] = (byte)first;//那么下一个数据字节就等于当前处理字符串的第一个字节
				code = old_code; //回溯到上一个编码
			}
			while (code > clearFlag)
			{
				// 如果当前编码大于清除标记，表示编码值是能压缩数据的
				pixelStatck[top++] = suffix[code];
				code = prefix[code];//回溯到上一个编码
			}
			first = suffix[code];
			if (available > MaxStackSize)
			{
				// 当编码最大值大于gif所允许的编码（4096）最大值的时候停止处理
				break;
			}
			// 获取下一个数据
			pixelStatck[top++] = suffix[code];
			// 设置当前应该编码位置的前缀
			prefix[available] = old_code;
			// 设置当前应该编码位置的后缀
			suffix[available] = first;
			// 下次应该得到的编码值
			available++;
			if (available == code_mask + 1 && available < MaxStackSize)
			{
				// 增加编码位数
				codeSize++;
				// 重设最大编码值
				code_mask = (1 << codeSize) - 1;
			}
			// 还原old_code
			old_code = inCode;
		}
		// 回溯到上一个处理位置
		top--;
		// 获取元数据
		pixels[i++] = (byte)pixelStatck[top];
	}

	return pixels;
}

/**
 *\fn         Draw(HDC dc, int x, int y, int frameId)
 *\brief      将图片画到DC上。
 *\param[in]  dc        要载入图片的DC。
 *\param[in]  x         图片x坐标。
 *\param[in]  y         图片y坐标。
 *\param[in]  frameId   图片帧ID。
 *\return     是否成功
 */
bool CGIF::Draw(HDC dc, int x, int y, int frameId)
{
	if (NULL == gif_.pGifFrame) return false;

	PGIFFRAME pFrame = gif_.pGifFrame;
	for (int i = 0; (i < frameId) && (NULL != pFrame); i++)	pFrame = pFrame->pNext;

	::StretchDIBits(dc, x, y, gif_.BmpInfo.bmiHeader.biWidth, gif_.BmpInfo.bmiHeader.biHeight, 
		0, 0, gif_.BmpInfo.bmiHeader.biWidth, gif_.BmpInfo.bmiHeader.biHeight, 
		pFrame->pBmpData, &gif_.BmpInfo, DIB_RGB_COLORS, SRCCOPY);

	return true;
}

/**
 *\fn         SaveBmp(const char *filname, int frameId)
 *\brief      将图片存成BITMAP格式。
 *\param[in]  filname  图片文件名。
 *\param[in]  frameId   图片帧ID。
 *\return     是否成功
 */
bool CGIF::SaveBmp(const char *filename, int frameId)
{
	if (NULL == filename || frameId >= (int)gif_.nGifFrameNum) return false;

	int nLineDataLen = (gif_.ScrDesc.wWidth * (gif_.BmpInfo.bmiHeader.biBitCount / 8) + 3) * 4 /4;
	PGIFFRAME pFrame = gif_.pGifFrame;

	for (int i = 0; (i < frameId) && (NULL != pFrame); i++) pFrame = pFrame->pNext;

	if ((pFrame->byFrameId != frameId) || (NULL == pFrame->pBmpData)) return false;

	int nBMPBytes = (gif_.ScrDesc.wWidth * gif_.ScrDesc.wHeight) * 24 / 8;

	BITMAPFILEHEADER bmfh = {0};
	bmfh.bfType = 0x4D42;	// "BM"
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + nBMPBytes;

	FILE *file = fopen(filename, "w+b");

	if (NULL == file) return false;

	fwrite(&bmfh, sizeof(BITMAPFILEHEADER), 1, file);
	fwrite(&(gif_.BmpInfo), sizeof(BITMAPINFOHEADER), 1, file);
	fwrite(pFrame->pBmpData, nLineDataLen * gif_.ScrDesc.wHeight, 1, file);
	
	fclose(file);

	return true;
}