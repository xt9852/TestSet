#include "StdAfx.h"
#include "RmUtil.h"
#include "RmParser.h"

RmParser::RmParser(CString filename) : Parser(filename)
{
	index	= NULL;
	pTimeSlotLenTable	= NULL;
	sdp		= "";
}

RmParser::~RmParser(void)
{
	if (index) 	delete[] index;

	if (pTimeSlotLenTable) delete pTimeSlotLenTable;
}


BOOL		RmParser::Initial(){

	mediaFile = new RmReader();			//读取Rm文件的 工具类
	bSuccess  = mediaFile->Initial(filename);

	if (!bSuccess) return FALSE;

	CFile pFile;
	CString strFile;	
	strFile.Format("%s.meta",filename);
	
	if (!pFile.Open(strFile, CFile::modeRead))
	{

		//不存在
		if (!MakeHead()) return FALSE;

		if (!MakeIndex()) return FALSE;

		if (!MakeSDP()) return FALSE;

		Save();
	}
	else
	{
		//存在
		Load(&pFile);
	}

	return TRUE;
}


CString		RmParser::GetSDP()
{	
	return sdp;
}


DWORD		RmParser::GetDuration(){
	return duration;
}

DWORD		RmParser::GetSecondNum() 
{
	return numOfIndex;
}

BOOL		RmParser::MakeSDP(){	

	sdp.AppendFormat( "v=0\r\n" );
	sdp.AppendFormat( "o=- 1131587664 1131587664 IN IP4 127.0.0.1\r\n" );
	sdp.AppendFormat( "s=%s\r\n", title );
	sdp.AppendFormat( "i=%s %s\r\n",comment, copyright );
	sdp.AppendFormat( "t=0 0\r\n" );
	sdp.AppendFormat( "a=SdpplinVersion:1610641657\r\n" );	
	sdp.AppendFormat( "a=Flags:integer;%d\r\n",flags );
	sdp.AppendFormat( "a=IsRealDataType:integer;1\r\n" );	
	sdp.AppendFormat( "a=StreamCount:integer;%d\r\n", streamCount-1 );
	sdp.AppendFormat( "a=range:npt=0-0\r\n" );	
	sdp.AppendFormat( "m=audio 0 RTP/AVP 101\r\n" );	
	sdp.AppendFormat( "b=AS:%ld\r\n", avgAudioBitRate /1000 );
	sdp.AppendFormat( "a=control:streamid=%d\r\n", audioTrackID );

	int a = numOfIndex;
	int b = int (audioDuration * 1.0 / 1000);
	int c = a > b ? b : a;

	sdp.AppendFormat( "a=range:npt=%.6f-%.6f\r\n", 
		audioStartTime*1.0/1000, c * 1.0);
	sdp.AppendFormat( "a=length:npt=%.6f\r\n", c * 1.0);
	
	sdp.AppendFormat( "a=rtpmap:101 x-pn-realaudio/1000\r\n" );
	sdp.AppendFormat( "a=mimetype:string;\"%s\"\r\n", audioMimeType );
	sdp.AppendFormat( "a=AvgBitRate:integer;%ld\r\n", avgAudioBitRate );
	sdp.AppendFormat( "a=EndOneRuleEndAll:integer;1\r\n" );
	sdp.AppendFormat( "a=AvgPacketSize:integer;%ld\r\n",avgAudioPacketSize );
	sdp.AppendFormat( "a=Preroll:integer;%ld\r\n", audioPreroll );
	sdp.AppendFormat( "a=MaxPacketSize:integer;%ld\r\n", maxAudioPacketSize);
	sdp.AppendFormat( "a=MaxBitRate:integer;%ld\r\n", maxAudioBitRate );
	sdp.AppendFormat( "a=RMFF 1.0 Flags:buffer;\"AAIAAgAA\"\r\n" );
	sdp.AppendFormat( "a=OpaqueData:buffer;\"%s\"\r\n", audioOpaque);

	sdp.AppendFormat( "a=StreamName:string;\"%s\"\r\n", audioTrackName);
	sdp.AppendFormat( "a=intrinsicDurationType:string;\"intrinsicDurationContinuous\"\r\n" );	
	sdp.AppendFormat( "m=video 0 RTP/AVP 101\r\n" );
	sdp.AppendFormat( "b=AS:%ld\r\n",avgBitRate/1000 );
	sdp.AppendFormat( "a=control:streamid=%d\r\n", videoTrackID);

	a = numOfIndex;
	b = int(videoDuration * 1.0 / 1000);
	c = a > b ? b : a;

	sdp.AppendFormat( "a=range:npt=%.6f-%.6f\r\n", 
		videoStartTime*1.0/1000, c * 1.0);
	sdp.AppendFormat( "a=length:npt=%.6f\r\n", c *1.0 );

	sdp.AppendFormat( "a=rtpmap:101 x-pn-realvideo/1000\r\n" );

	sdp.AppendFormat( "a=mimetype:string;\"%s\"\r\n", videoMimeType );
	sdp.AppendFormat( "a=AvgBitRate:integer;%ld\r\n", avgVideoBitRate );

	sdp.AppendFormat( "a=PreDataAfterSeek:integer;1\r\n" );
	sdp.AppendFormat( "a=EndOneRuleEndAll:integer;1\r\n" );

	sdp.AppendFormat( "a=AvgPacketSize:integer;%ld\r\n",avgVideoPacketSize );

	sdp.AppendFormat( "a=PrerollAfterSeek:integer;1\r\n" );

	sdp.AppendFormat( "a=Preroll:integer;%ld\r\n", videoPreroll );
	sdp.AppendFormat( "a=MaxPacketSize:integer;%ld\r\n", maxVideoPacketSize );
	sdp.AppendFormat( "a=MaxBitRate:integer;%ld\r\n", maxVideoBitRate );

	sdp.AppendFormat( "a=RMFF 1.0 Flags:buffer;\"AAMAAgAAAAI=\"\r\n" );
	sdp.AppendFormat( "a=OpaqueData:buffer;\"%s\"\r\n",videoOpaque );

	sdp.AppendFormat( "a=StreamName:string;\"%s\"\r\n", videoTrackName);

	sdp.AppendFormat( "a=intrinsicDurationType:string;\"intrinsicDurationContinuous\"\r\n" );

	return TRUE;
}

/*
从rm文件中创建索引
如果文件中有错误的帧,索引会自动跳过,并且有的索引项为零,
表示相应的时间段中不用发送数据
*/

BOOL		RmParser::MakeIndex(){

	//RmReader* mediaFile = new RmReader();				//读取Rm文件的 工具类
	//BOOL bSuccess = mediaFile->Initial( filename );	//初始化Rm读取类
	if (bSuccess){

		DWORD time = /* */duration/1000 ;				//取得rm文件的持续时间
		index = new INDEX[time+1+10];					//加10是为了避免后面构建索引的时候出界，导致Index的内存释放出问题
		memset(index, 0, sizeof(INDEX)*(time+1+10));	//索引清零

		DWORD timestamp=0;
		rmff_frame_t * frame=NULL;						//rm文件帧
		index[0].offset = mediaFile->Tell();
		int index_n = 0;								//索引偏移指针

		DWORD nDataLen = 0;								//Slot所需的每个索引对应的数据长度 

		while( (frame = mediaFile->ReadNextFrame() ) !=NULL ) //依次读取rm帧
		{
			int i		= frame->timecode/1000;
			nDataLen   += frame->size; 	
			
#pragma warning(disable : 4018)
			if(i <= time)								//如果是正确的索引
#pragma warning(default : 4018)
			{
				if( i > index_n)						//如果时间戳超过1秒
				{					
					index[index_n].length_of_data = nDataLen;

					index_n = i ;
					index[index_n].offset = mediaFile->Tell();
									
					nDataLen =0;
				}

				index[index_n].num_of_packets++;
			}

			mediaFile->ReleaseFrame( frame );
		}

		delete mediaFile;

		numOfIndex = index_n+1;

		pTimeSlotLenTable	= new DWORD[numOfIndex];

		for(int i=0; i < numOfIndex; i++)
		{
			//pTimeSlotLenTable[i] = index[i].length_of_data + index[i].num_of_packets * ( RDT_HEAD_LEN + 4 + sizeof(DATAPACKET_HEADER) );			
		}
		return TRUE;
	}
	else
	{
		delete mediaFile;
		return FALSE;
	}
}


BOOL        RmParser::MakeHead()
{
   // RmReader* mediaFile = new RmReader();
   // BOOL bSuccess = mediaFile->Initial(filename);
    if (bSuccess)
    {

        streamCount = mediaFile->GetStreamCount();
        audioTrackID = mediaFile->GetAudioTrackID();
        videoTrackID = mediaFile->GetVideoTrackID();
        flags = mediaFile->GetFlags();

        avgBitRate = mediaFile->GetAvgBitRate(  );
        maxBitRate = mediaFile->GetMaxBitRate(  );
        avgPacketSize = mediaFile->GetAvgPacketSize(  );
        maxPacketSize = mediaFile->GetMaxPacketSize(  );
        duration = mediaFile->GetDuration();
        preroll = mediaFile->GetPreroll();

        avgAudioBitRate = mediaFile->GetAvgBitRate( RmReader::AUDIO_TRACK_ID );
        maxAudioBitRate = mediaFile->GetMaxBitRate( RmReader::AUDIO_TRACK_ID );
        avgAudioPacketSize = mediaFile->GetAvgPacketSize( RmReader::AUDIO_TRACK_ID );
        maxAudioPacketSize = mediaFile->GetMaxPacketSize( RmReader::AUDIO_TRACK_ID );
        audioDuration = mediaFile->GetDuration( RmReader::AUDIO_TRACK_ID );
        audioPreroll = mediaFile->GetPreroll( RmReader::AUDIO_TRACK_ID );

        avgVideoBitRate = mediaFile->GetAvgBitRate( RmReader::VIDEO_TRACK_ID );
        maxVideoBitRate = mediaFile->GetMaxBitRate( RmReader::VIDEO_TRACK_ID );
        avgVideoPacketSize = mediaFile->GetAvgPacketSize( RmReader::VIDEO_TRACK_ID );
        maxVideoPacketSize = mediaFile->GetMaxPacketSize( RmReader::VIDEO_TRACK_ID );
        videoDuration = mediaFile->GetDuration( RmReader::VIDEO_TRACK_ID );
        videoPreroll = mediaFile->GetPreroll( RmReader::VIDEO_TRACK_ID );	

        audioStartTime = mediaFile->GetStartTime( RmReader::AUDIO_TRACK_ID );
        audioTrackName = mediaFile->GetTrackName( RmReader::AUDIO_TRACK_ID );
        audioMimeType = mediaFile->GetMimeType( RmReader::AUDIO_TRACK_ID );

        videoStartTime = mediaFile->GetStartTime( RmReader::VIDEO_TRACK_ID );
        videoTrackName = mediaFile->GetTrackName( RmReader::VIDEO_TRACK_ID );
        videoMimeType = mediaFile->GetMimeType( RmReader::VIDEO_TRACK_ID );


		//add by xianjian at 3.3 for wuhu.rm
		if( !duration ) 
		{
			duration = (audioDuration > videoDuration) ?  audioDuration : videoDuration;
		}

        title = mediaFile->GetTitle();
        copyright = mediaFile->GetComment();
        comment = mediaFile->GetCopyRight();

        BYTE * inBuf = NULL;
        DWORD	len = 0;
        BYTE * outBuf = NULL;
        DWORD re = 0;


        inBuf = mediaFile->GetAudioTypeSpec();
        len = mediaFile->GetAudioTypeLen();
        outBuf = ( BYTE *)audioOpaque.GetBuffer( len*4/3 + 4  );
        re = BinTo64( inBuf, len, ( char *)outBuf );
        audioOpaque.ReleaseBuffer( re );

        inBuf = mediaFile->GetVideoTypeSpec();
        len = mediaFile->GetVideoTypeLen();
        outBuf = ( BYTE *)videoOpaque.GetBuffer( len*4/3 + 4  );
        re = BinTo64( inBuf, len, ( char *)outBuf );
        videoOpaque.ReleaseBuffer( re );

        //delete mediaFile;
        return TRUE;
    }

    delete mediaFile;
    return FALSE;
}


//
//	从文件中Load信息
//
BOOL RmParser::Load(CFile *pFile)
{
	try
	{
		CArchive ar(pFile, CArchive::load);
		Serialize(ar);
		ar.Close();
	}
	catch (CException* pException)
	{
		pException->Delete();
	}

	return TRUE;
}

//
//	保存信息到文件
//
BOOL RmParser::Save()
{
	CString strFile;
	CFile pFile;

	strFile.Format(_T("%s.meta"),  filename);

	if (!pFile.Open(strFile, CFile::modeWrite|CFile::modeCreate)) return FALSE;

	CArchive ar(&pFile, CArchive::store);
	Serialize(ar);
	ar.Close();

	return TRUE;
}


//
//	
//
void RmParser::Serialize(CArchive& ar)
{
	if ( ar.IsStoring() )
	{
		ar << numOfIndex;

		ar << streamCount;
		ar << audioTrackID;
		ar << videoTrackID;
		ar << flags;

		ar << avgBitRate;
		ar << avgAudioBitRate;
		ar << avgVideoBitRate;

		ar << maxBitRate;
		ar << maxAudioBitRate;
		ar << maxVideoBitRate;
		ar << avgPacketSize;
		ar << avgAudioPacketSize;
		ar << avgVideoPacketSize;
		ar << maxPacketSize;
		ar << maxAudioPacketSize;
		ar << maxVideoPacketSize;

		ar << duration;
		ar << audioDuration;
		ar << videoDuration;
		ar << preroll;
		ar << audioPreroll;
		ar << videoPreroll;

		ar << audioStartTime;
		ar << videoStartTime;
		ar << audioMimeType;
		ar << videoMimeType;
		ar << audioTrackName;
		ar << videoTrackName;

		ar << title;
		ar << copyright;
		ar << comment;

		ar << audioOpaque;
		ar << videoOpaque;

		ar << sdp;

		ar.Write(index,numOfIndex*sizeof(INDEX));

	}
	else
	{
		ar >> numOfIndex;

		ar >> streamCount;
		ar >> audioTrackID;
		ar >> videoTrackID;
		ar >> flags;

		ar >> avgBitRate;
		ar >> avgAudioBitRate;
		ar >> avgVideoBitRate;

		ar >> maxBitRate;
		ar >> maxAudioBitRate;
		ar >> maxVideoBitRate;
		ar >> avgPacketSize;
		ar >> avgAudioPacketSize;
		ar >> avgVideoPacketSize;
		ar >> maxPacketSize;
		ar >> maxAudioPacketSize;
		ar >> maxVideoPacketSize;

		ar >> duration;
		ar >> audioDuration;
		ar >> videoDuration;
		ar >> preroll;
		ar >> audioPreroll;
		ar >> videoPreroll;

		ar >> audioStartTime;
		ar >> videoStartTime;
		ar >> audioMimeType;
		ar >> videoMimeType;
		ar >> audioTrackName;
		ar >> videoTrackName;

		ar >> title;
		ar >> copyright;
		ar >> comment;

		ar >> audioOpaque;
		ar >> videoOpaque;

		ar >> sdp;

		index = new INDEX[numOfIndex];

		ar.Read(index,numOfIndex*sizeof(INDEX));

		pTimeSlotLenTable	= new DWORD[numOfIndex];

//		for(int i=0; i < numOfIndex; i++)
//			pTimeSlotLenTable[i] = index[i].length_of_data + index[i].num_of_packets * ( RDT_HEAD_LEN + 4 + sizeof(DATAPACKET_HEADER));

	}
}

DWORD RmParser::GetOffset( WORD second ) {
	return  index[ second ].offset;
}

WORD RmParser::GetPacketCounts( WORD second ){
	return  index[second].num_of_packets; 
}

DWORD *RmParser::GetLengthTable()
{
	return pTimeSlotLenTable;
}

BOOL RmParser::SeekIndex(WORD second)
{
	return mediaFile->Seek(index[second].offset);
}

// pBuf [out] data
// return datalen, 0 error
DWORD RmParser::GetNextFrame(UCHAR *pBuf)
{
	if (NULL == pBuf) return 0;

	static WORD wStreamSeq[2] = {0,0};

	rmff_frame_t *frame = NULL;
	frame = mediaFile->ReadNextFrame();

	if( NULL == frame) return FALSE;
	else
	{
		if (frame->size < 6 * 1024 - 10)
		{
			BYTE m = frame->id<<1;
			m |= 0x40;

			DWORD dwDataLen = frame->size + 14;
			
			pBuf[0] = '$';
#pragma warning(disable : 4244)
			pBuf[1] = frame->id;
#pragma warning(default : 4244)
			*(WORD*)(pBuf+2) = htons(frame->size + 10);			
			pBuf[4] = m;
			*(WORD*)(pBuf+5) = htons(wStreamSeq[frame->id]++);
			pBuf[7] = frame->flags ? 0xc0 : 0xc1;
			*(UINT*)(pBuf+8) = htonl(frame->timecode);
			pBuf[12] = 0;
			pBuf[13] = 0;
			
			memcpy(pBuf + 14, frame->data, frame->size);
			mediaFile->ReleaseFrame(frame);

/*			CFile file;
			if (file.Open("rtsp.txt", CFile::modeReadWrite))
			{
				file.SeekToEnd();
				CString msg;
				msg.Format("->P,D,datalength=%-6d ", dwDataLen);
				for (int i = 0; i < 20; i++)
					msg.AppendFormat(",%2x", pBuf[i]);
				msg.AppendFormat("\r\n");
				file.Write((VOID*)(LPCSTR)msg, msg.GetLength());
				file.Close();
			}
*/
			return dwDataLen;
		}

		return 0;
	}
}


