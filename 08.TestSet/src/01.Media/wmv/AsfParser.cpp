
#include "StdAfx.h"
#include "asfparser.h"
#include "rm\RmUtil.h"

//////////////////////////////////////////////////////////////////////////////
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) \
   if (x != NULL)       \
   {                    \
      x->Release();     \
      x = NULL;         \
   }
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE(x) \
   if (x != NULL)            \
   {                         \
      delete[] x;            \
      x = NULL;              \
   }
#endif
//////////////////////////////////////////////////////////////////////////////


AsfParser::AsfParser(CString filename) : Parser ( filename )
{
	index = NULL;
}

AsfParser::~AsfParser(void)
{

	if(index != NULL) {
		delete[] index;
	}
}

BOOL  AsfParser::Initial()
{
	CFile pFile;
	CString strFile;
	
	strFile.Format("%s.meta",filename);
	
	if( ! pFile.Open( strFile, CFile::modeRead))
	{
		//不存在
		if( !reader.Initial( filename ) ) return FALSE;
		
		if( !GetMetaData() ) return FALSE;

		if( !MakeIndex() ) return FALSE;

		if( !MakeSDP() ) return FALSE;

		Save();
	}
	else
	{
		//存在
		Load( &pFile );
	}

	return TRUE;
}


CString		AsfParser::GetSDP(){
    return sdp;

}

DWORD		AsfParser::GetDuration(){
    return duration;
}

DWORD		AsfParser::GetSecondNum() 
{
    return numOfIndex;
}

BOOL		AsfParser::MakeIndex()
{
	//生成索引，以一秒为单位， 索引项为当前时刻对应
	//的数据包的序号。
	DWORD sec = duration/1000;
	DWORD size = duration/1000 + 16;

	if(index ==NULL) {

		index = new INDEX[ size];	//待定
	}
	DWORD  packetSize = reader.pHeadObj->PacketSize;
	DWORD packetCounts = reader.pHeadObj->PacketCounts;

	DWORD time = -1;
	DWORD newTime = 0;
	AsfPacket  *packet = NULL;
	DWORD blockCounts = packetCounts / 1024;
	DWORD leftCounts = packetCounts % 1024;
	BYTE  *buf = new BYTE[ 1024* packetSize];
	CFile &fp = reader.fp;	// XT+20110323 CFile fp = reader.fp 将会出 error C2248: 'CObject::CObject'
	for(DWORD i =0; i< blockCounts; i++) {
		DWORD nRead = fp.Read( buf, 1024 * packetSize );
		if( nRead != 1024*packetSize ) 
		{
			printf("error :nRead=%d,1024 * packetSize =%d\n",nRead,1024 * packetSize);
		}
		if ( nRead == 1024 * packetSize )
		{
			for( int j = 0; j< 1024; j++ ) {
				packet = AsfPacket::CreatePacket( buf+j*packetSize,packetSize);
				if( packet == NULL ) continue;
				
				newTime = packet->Time/1000;
				if(newTime != time ) {
					if( newTime > time+10 ) continue; //if timestamp too larger than the former packet 
														//consider it a  fault one
					
					index[newTime] = i*1024 + j;
					
					if (newTime != time+1)			//if the gap between two packet is larger than one 
					{
						for (DWORD k = time +1; k<newTime; k++)
						{
							index[k] = index[time] +
								(k-time)*(index[newTime]-index[time])/(newTime-time);
						}


					}
					time = newTime;
				}
			}
		}
	}
	
	DWORD len = fp.Read( buf, leftCounts * packetSize );
	//add by xianjian at 4.10 for testing 
	DWORD dwFileOffset = (DWORD)fp.Seek(0, CFile::current);
	DWORD dwFileSize   = (DWORD)fp.GetLength();


	//end
	if( len != leftCounts*packetSize ) {
		return FALSE ;
	}

	for(DWORD i = 0; i< leftCounts; i++) {
		packet = AsfPacket::CreatePacket (buf+i*packetSize,packetSize);
		if( packet == NULL) continue;
		newTime = packet->Time/1000;
		
		if( newTime != time ) {
			if( newTime > time+10 ) continue; //if timestamp too larger than the former packet 
														//consider it a  fault one
					
			index[ newTime ] = blockCounts*1024 +i;
			if (newTime != time + 1)			//if the gap between two packet is larger than one 
			{
				for (DWORD k = time + 1; k < newTime; k++)
				{
					index[k] = index[time] + (k-time)*(index[newTime]-index[time])/(newTime-time);
				}


			}
					
			time = newTime;

		}
	}
	index[time +1] = packetCounts-1; 
	numOfIndex = time+1;	// time or sec with the change policy  of making index 

	//add by xianjian at 4.3  check index
	for (DWORD i = 0; i<numOfIndex; i++)
	{
		ASSERT(index[i]>=0&&index[i]<=packetCounts-1);
		ASSERT(index[i+1] >= index[i]);
		
	}
	ASSERT(index[numOfIndex] == packetCounts - 1);
	//end of add

	pTimeSlotLenTable = new DWORD[numOfIndex];
	for (UINT i = 0; i < numOfIndex; i++)
	{
        pTimeSlotLenTable[i] = (index[i+1]-index[i])*(packetSize + sizeof(DATAPACKET_HEADER) + RtpPacket::RTP_HEAD_LEN + 4);
	}

#ifdef DEBUG
	for (UINT i = 0; i < numOfIndex+1; i++)
	{
		printf("%d %d\n",i, index[i] );
	}
#endif

	return TRUE;
}



BOOL AsfParser::GetMetaData () 
{
	PacketSize = reader.pHeadObj->PacketSize;  

	audioNumber = reader.pHeadObj->AudioNum;   
	videoNumber = reader.pHeadObj->VideoNum; 
	               
	audioBitrate = reader.pHeadObj->AudioBitrate;  
	videoBitrate = reader.pHeadObj->VideoBitrate;  
	Bitrate = reader.pHeadObj->Bitrate;    

	Title = reader.pHeadObj->Title;         
	Author = reader.pHeadObj->Author;        
	Copyright = reader.pHeadObj->Copyright;   

	Start_Time = reader.pHeadObj->Start_Time;
	End_Time = reader.pHeadObj->End_Time;
	duration = reader.pHeadObj->End_Time - reader.pHeadObj->Start_Time;

    return TRUE;

}


BOOL		AsfParser::MakeSDP()
{
	sdp = "";
	sdp.AppendFormat("v=0\r\n");
	sdp.AppendFormat("o=- 200512050814190250 200512050814190250 IN IP4 127.0.0.1\r\n");
	sdp.AppendFormat("s=%s\r\n",Title);
	sdp.AppendFormat("c=IN IP4 0.0.0.0\r\n");
	sdp.AppendFormat("b=AS:%d\r\n",Bitrate/1000+1);
	sdp.AppendFormat("a=maxps:%d\r\n",PacketSize);
	sdp.AppendFormat("t=0 0\r\n");

	CString onlyname;
	int i = filename.ReverseFind('\\');
	if(i!= -1 )
	{
		onlyname = filename.Right(filename.GetLength() - i-1);
	} else 
	{
		onlyname = filename;
	}

	sdp.AppendFormat("a=control:rtsp://127.0.0.1:5555/%s/\r\n",onlyname);
	sdp.AppendFormat("a=etag:{9657E110-1964-26D2-DBD8-7729E8237D58}\r\n");
	sdp.AppendFormat("a=range:npt=%.3f-%.3f\r\n",Start_Time*1.0/1000, End_Time*1.0/1000 );

	sdp.AppendFormat("a=recvonly\r\n");
	sdp.AppendFormat("a=pgmpu:data:application/x-wms-contentdesc,%s\r\n",GetPgmpu());
	sdp.AppendFormat("a=pgmpu:data:application/vnd.ms.wms-hdr.asfv1;base64,%s\r\n",GetPgmpu2());
	sdp.AppendFormat("m=audio 0 RTP/AVP 96\r\n");
	sdp.AppendFormat("b=X-AV:%d\r\n",audioBitrate/1000 + 1);

	sdp.AppendFormat("b=RS:0\r\n");
	sdp.AppendFormat("b=RR:0\r\n");
	sdp.AppendFormat("a=rtpmap:96 x-asf-pf/1000\r\n");
	sdp.AppendFormat("a=control:audio\r\n");
	sdp.AppendFormat("a=stream:%d\r\n",audioNumber);
	
	sdp.AppendFormat("m=application 0 RTP/AVP 96\r\n");
	sdp.AppendFormat("b=RS:0\r\n");
	sdp.AppendFormat("b=RR:0\r\n");
	sdp.AppendFormat("a=rtpmap:96 x-wms-rtx/1000\r\n");
	sdp.AppendFormat("a=control:rtx\r\n");
	sdp.AppendFormat("a=stream:65536\r\n");
	
	sdp.AppendFormat("m=video 0 RTP/AVP 96\r\n");
	sdp.AppendFormat("b=X-AV:%d\r\n",videoBitrate/1000+1);

	sdp.AppendFormat("b=RS:0\r\n");
	sdp.AppendFormat("b=RR:0\r\n");
	sdp.AppendFormat("a=rtpmap:96 x-asf-pf/1000\r\n");
	sdp.AppendFormat("a=control:video\r\n");
	sdp.AppendFormat("a=stream:%d\r\n",videoNumber);

	return TRUE;

}

CString		AsfParser::GetPgmpu()
{

	CString str;
	CString buf;
	str.AppendFormat(",8,language,31,0,");
	buf = PgmpuConvert( Title );
	str.AppendFormat(",5,title,31,%d,%s",Title.GetLength(), buf);
	buf = PgmpuConvert( Author );
	str.AppendFormat(",6,author,31,%d,%s",Author.GetLength(), buf);
	buf = PgmpuConvert( Copyright );
	str.AppendFormat(",9,copyright,31,%d,%s",Copyright.GetLength(), buf);
	str.AppendFormat(",44,WMS_CONTENT_DESCRIPTION_SERVER_BRANDING_INFO,31,12,WMServer/9.0");
	str.AppendFormat(",51,WMS_CONTENT_DESCRIPTION_PLAYLIST_ENTRY_START_OFFSET,3,4,3000");
	buf.Format( "%d",duration);
	str.AppendFormat(",47,WMS_CONTENT_DESCRIPTION_PLAYLIST_ENTRY_DURATION,3,%d,%s",buf.GetLength(), buf);
	str.AppendFormat(",58,WMS_CONTENT_DESCRIPTION_COPIED_METADATA_FROM_PLAYLIST_FILE,3,1,1");
	buf = filename;
	int strIndex = buf.ReverseFind( '\\');
	buf = buf.Mid( strIndex+1 );
	str.AppendFormat("42,WMS_CONTENT_DESCRIPTION_PLAYLIST_ENTRY_URL,31,%d,%s%%0D%%0A",buf.GetLength(), buf);
	return str;
}

CString  AsfParser::PgmpuConvert( const CString str) 
{
	WORD   len = str.GetLength();
	BYTE * buf = new BYTE[ len*3];
	char a,b;
    int j=0;
	for( int i=0; i<len; i++) {
		if( str[i]> 0x7f ) {
			a = str[i]/16;
			b = str[i]%16;
			if( a>=10 ) a ='a'+a-10;
			else	  a = '0' + a;
			if( b>=10 ) b= 'a' + b -10;
			else	  b= '0'+b;
			buf[j] = '%';
			buf[j+1] = a;
			buf[j+2] = b;
			j+=3;
		} else {
			buf[j++] = str[i];
		}
	}
	ASSERT( j<= len*3+1 );
	CString reStr((const char *)buf,j);
	reStr.Replace(" ","%20");
	delete[] buf;
	return reStr;
}



CString		AsfParser::GetPgmpu2()
{
	CString str;
	BYTE * buf = NULL;
	BYTE * buf2= NULL;
	DWORD len2 = 0;
	WORD   len = (WORD)reader.packetInitOffset;
	buf = new BYTE[ len ];
	buf2 = new BYTE[ len*4/3 +4 ];

	reader.fp.SeekToBegin();
	QWORD readLen = reader.fp.Read( buf,len );
	if( readLen != len ) {
		delete []buf;
		delete []buf2;
		return str;
	} else {
		
		len2 = BinTo64( buf, len, (char*)buf2);
		str = CString( (const char*) buf2, len2);
		delete []buf;
		delete []buf2;
		return str;
	}
}

DWORD *	AsfParser::GetLengthTable()
{
    return pTimeSlotLenTable;
}


void		AsfParser::Serialize(CArchive& ar)
{
	if ( ar.IsStoring() )
	{
		ar << numOfIndex;

		//ar << streamCount;
		ar << audioNumber;
		ar << videoNumber;

		ar << Bitrate;
		ar << PacketSize;

		ar << duration;

		

		ar << Title;
		ar << Copyright;
		ar << Author;

		ar << sdp;

		ar.Write(index,(numOfIndex + 1)*sizeof(INDEX));

	}
	else
	{
		ar >> numOfIndex;

		//ar >> streamCount;
		ar >> audioNumber;
		ar >> videoNumber;

		ar >> Bitrate;
		ar >> PacketSize;

		ar >> duration;

		

		ar >> Title;
		ar >> Copyright;
		ar >> Author;

		ar >> sdp;

		
		index = new INDEX[numOfIndex + 1];

		ar.Read(index,(numOfIndex + 1)*sizeof(INDEX));

		pTimeSlotLenTable	= new DWORD[numOfIndex];

		for(DWORD i = 0; i < numOfIndex; i++)
			pTimeSlotLenTable[i] = (index[i+1]-index[i])*(PacketSize + sizeof(DATAPACKET_HEADER) + RtpPacket::RTP_HEAD_LEN + 4 );

	}
}

BOOL		AsfParser::Load(CFile *pFile)
{
	try
	{
		CArchive ar( pFile, CArchive::load );
		Serialize( ar );
		ar.Close();
	}
	catch ( CException* pException )
	{
		pException->Delete();
	}

	return TRUE;
}

BOOL		AsfParser::Save()
{
	CString strFile;
	CFile pFile;

	strFile.Format( _T("%s.meta"),  filename);

	if ( ! pFile.Open( strFile, CFile::modeWrite|CFile::modeCreate ) ) return FALSE;

	CArchive ar( &pFile, CArchive::store );
	Serialize( ar );
	ar.Close();

	return TRUE;
}
