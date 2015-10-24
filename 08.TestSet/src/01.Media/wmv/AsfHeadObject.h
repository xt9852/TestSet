/*
AsfHeadObj 类不修改原数据，不管理内存的分配和释放。
*/

#pragma once

typedef unsigned __int64 QWORD;

const GUID HEAD_OBJECT_ID={
    0x75B22630,0x668E,0x11CF,{0xa6,0xd9,0x00,0xAA,0x00,0x62,0xCE,0x6C}
};
const GUID EX_HEAD_OBJECT_ID={
    0x5FBF03B5,0xA92E,0x11CF,{0x8E,0xE3,0x00,0xC0,0x0C,0x20,0x53,0x65}
};
//5FBF03B5-A92E-11CF-8EE3-00C00C205365
const GUID DATA_OBJECT_ID={
    0x75B22636,0x668E,0x11CF,{0xa6,0xd9,0x00,0xAA,0x00,0x62,0xCE,0x6C}
};
const GUID FILE_PROPERTY_ID={
    0x8CABDCA1, 0xA947, 0x11CF, {0x8E,0xE4, 0x00,0xC0,0x0C,0x20,0x53,0x65}
};
//8CABDCA1-A947-11CF-8EE4-00C00C205365
const GUID STREAM_PROPERTY_ID={
    0xB7DC0791, 0xA9B7, 0x11CF, {0x8E,0xE6, 0x00,0xC0,0x0C,0x20,0x53,0x65}
};
//B7DC0791-A9B7-11CF-8EE6-00C00C205365
const GUID EX_STREAM_PROPERTY_ID={
    0x14E6A5CB, 0xC672, 0x4332, {0x83,0x99, 0xA9,0x69,0x52,0x06,0x5B,0x5A}
};
//14E6A5CB-C672-4332-8399-A96952065B5A
const GUID CONTENT_DESCRIPTION_ID={
    0x75B22633, 0x668E, 0x11CF, {0xA6,0xD9, 0x00,0xAA,0x00,0x62,0xCE,0x6C}
};
//75B22633-668E-11CF-A6D9-00AA0062CE6C
const GUID ASF_AUDIO_MEDIA={
    0xF8699E40, 0x5B4D, 0x11CF,{ 0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B}
};
//F8699E40-5B4D-11CF-A8FD-00805F5C442B
const GUID ASF_VIDEO_MEDIA={
    0xBC19EFC0, 0x5B4D, 0x11CF, {0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B}
};

#pragma pack( push ,1)	

typedef struct _object 
{
    GUID ObjectID;
    QWORD ObjectSize;
}  OBJECT;

typedef struct _headObject
{
    GUID			Object_ID										;   
    QWORD			Object_Size						      ;   
    DWORD	Number_of_Header_Objects	  ; 
    BYTE	Reserved1	                  ; 
    BYTE	Reserved2	                  ; 


} HEAD_OBJECT;

typedef struct _dataObject
{
    GUID	ObjectID;
    QWORD	ObjectSize;
    GUID	FileID;
    QWORD	TotalDataPackets;
    WORD	Reserved;
}  DATA_OBJECT;

typedef struct _fileObject
{
    GUID			Object_ID;   
    QWORD			Object_Size						      ;   
    GUID			File_ID 							      ;   
    QWORD			File_Size							      ;   
    QWORD			Creation_Date					      ;   
    QWORD			Data_Packets_Count		      ;   
    QWORD			Play_Duration					      ;   
    QWORD			Send_Duration					      ;   
    QWORD			Preroll								      ;   
    DWORD			Flags									      ;   

    DWORD		Minimum_Data_Packet_Size	  	; 
    DWORD		Maximum_Data_Packet_Size	  	; 
    DWORD		Maximum_Bitrate						    ; 


}FILE_OBJECT;

typedef struct _streamProperty
{
    GUID			Object_ID										;   
    QWORD			Object_Size						      ;   
    GUID	  Stream_Type						       ; 
    GUID	  Error_Correction_Type	       ; 
    QWORD	  Time_Offset						       ; 
    DWORD	  Type_Specific_Data_Length			;
    DWORD	  Error_Correction_Data_Length	;
    WORD	  Flags					               ; 
    /*Stream_Number		7 (LSB)      ; 
    Reserved		8                  
    EncryptedContent Flag		1      */     
    DWORD	  Reserved;			 
    //BYTE	  Type_Specific_Data[0]	        ;
    //BYTE	  Error_Correction_Data[0]	        ;
} STREAM_PROPERTY;
typedef struct _contentDescription
{
    GUID 			Object_ID         	  ;  
    QWORD          Object_Size            ;  
    WORD           Title_Length           ;  
    WORD           Author_Length          ;  
    WORD           Copyright_Length       ;  
    WORD           Description_Length     ;  
    WORD           Rating_Length          ;  
    //WCHAR		   Title[0]                  ;  
    /*WCHAR*          Author                 ;  
    WCHAR*          Copyright              ;  
    WCHAR*          Description            ;  
    WCHAR*          Rating                 ;  */
} CONTENT_DESCRIPTION;
typedef struct _exHeadObject
{
    GUID 		   Object_ID         		  ;  
    QWORD          Object_Size            ;  
    GUID          Reserved_Field_1                ;  
    WORD           Reserved_Field_2                ;  
    DWORD          Header_Extension_Data_Size      ;  
} EX_HEAD_OBJECT;

typedef struct _exStreamProperty
{
    GUID 					Object_ID         		  ;  
    QWORD          Object_Size            ;  

    QWORD     Start_Time;
    QWORD    	End_Time                       				;         
    DWORD     Data_Bitrate                          ;         
    DWORD     Buffer_Size                           ;         
    DWORD     Initial_Buffer_Fullness               ;         
    DWORD     Alternate_Data_Bitrate                ;         
    DWORD     Alternate_Buffer_Size                 ;         
    DWORD     Alternate_Initial_Buffer_Fullness     ;         
    DWORD     Maximum_Object_Size                   ;         
    DWORD     Flags                                 ;         
    /*Reliable Flag                1 (LSB)         ;  
    Seekable Flag                1               ;  
    No Cleanpoints Flag          1               ;  
    Resend Live Cleanpoints Flag 1          			; 
    Reserved Flags               28              ;  */
    WORD      Stream_Number                         ;         
    WORD      Stream_Language_ID_Index              ;         
    QWORD     Average_Time_Per_Frame                ;         
    WORD      Stream_Name_Count                     ;         
    WORD      Payload_Extension_System_Count        ;         
    /*See below Stream Names                          ;         
    See below Payload Extension Systems             ;         
    See below Stream Properties Object              ;  */       
} EX_STREAM_PROPERTY;

#pragma pack(pop )
class AsfHeadObject
{

public:
    AsfHeadObject(const BYTE * buf, WORD  len);
    virtual ~AsfHeadObject(void);
    BOOL	Initial();

    WCHAR*		    Title                  ;  
    WCHAR*          Author                 ;  
    WCHAR*          Copyright              ;  
    WCHAR*          Description            ;  
    WCHAR*          Rating                 ; 

    WORD	AudioNum;
    WORD	VideoNum;
    DWORD	AudioBitrate;
    DWORD	VideoBitrate;

    DWORD	Start_Time;
    DWORD	End_Time;
    DWORD	Duration;
    DWORD   Bitrate;
    DWORD	PacketSize;
    DWORD	PacketCounts;
private:
    const BYTE* Buf;
    WORD		Len;

    HEAD_OBJECT * pHead;
    FILE_OBJECT * pFile;
    STREAM_PROPERTY* pAudioStream;
    STREAM_PROPERTY* pVideoStream;
    CONTENT_DESCRIPTION* pContent;

    EX_HEAD_OBJECT * pExHead;
    EX_STREAM_PROPERTY* pExAudioStream;
    EX_STREAM_PROPERTY* pExVideoStream;


public:
    static void  Test();
};
