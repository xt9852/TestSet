#ifndef		__RMLIB_H
#define		__RMLIB_H

#pragma  once 

#pragma warning( disable : 4018 )

#include "librmff.h"

class RmLib {
private:
	rmff_file_t * file;

	WORD	videoTrackID;
	WORD	audioTrackID;

	rmff_track_t *	audioTrack;
	rmff_track_t *	videoTrack;
	rmff_mdpr_t  *	audioProps;
	rmff_mdpr_t  *  videoProps;
	rmff_prop_t  *	props;
	rmff_cont_t  *	cont;

public:
	RmLib();
	~RmLib();
	BOOL	Initial(CString);
	
	BOOL	Open( CString );
	BOOL	Close( );
	BOOL	Seek( DWORD , int =SEEK_SET);
	DWORD	Tell( );

	rmff_frame_t *	ReadNextFrame();

	BOOL			ReleaseFrame( rmff_frame_t * );


	
	WORD	GetStreamCount();
	WORD	GetAudioTrackID();
	WORD	GetVideoTrackID();
	WORD	GetFlags();
	DWORD	GetAvgBitRate( WORD = FILE_ID );
	DWORD	GetMaxBitRate( WORD = FILE_ID );
	DWORD	GetAvgPacketSize( WORD = FILE_ID );
	DWORD	GetMaxPacketSize( WORD = FILE_ID );
	
	DWORD	GetDuration( WORD = FILE_ID );
	DWORD	GetPreroll( WORD = FILE_ID );

	DWORD	GetStartTime( WORD  );
	char *	GetTrackName( WORD  );
	char *  GetMimeType( WORD  );

	char *	GetTitle();
	char *	GetComment( void );
	char *	GetCopyRight();


	unsigned char *	GetAudioTypeSpec();
	DWORD	GetAudioTypeLen();


	unsigned char *	GetVideoTypeSpec();
	DWORD	GetVideoTypeLen();



	enum  TRACK_ID { AUDIO_TRACK_ID, VIDEO_TRACK_ID, FILE_ID };
	rmff_track_t * GetAudioTrack();
	rmff_track_t * GetVideoTrack();


private:
	BOOL			ReadHeaders();
//public:

	//add by xianjian at 2.28
	//读取当前文件指针后第一个关键帧
	//返回关键帧的指针,如果没有符合条件的关键帧,返回NULL;
	rmff_frame_t*			ReadNextKeyFrame();


};








#endif    //__RMLIB_H
