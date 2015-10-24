	/*
 * Copyright (C) 2004 by Objective Systems, Inc.
 *
 * This software is furnished under an open source license and may be 
 * used and copied only in accordance with the terms of this license. 
 * The text of the license may generally be found in the root 
 * directory of this installation in the LICENSE.txt file.  It 
 * can also be viewed online at the following URL:
 *
 *   http://www.obj-sys.com/open/license.html
 *
 * Any redistributions of this file including modified versions must 
 * maintain this copyright notice.
 *
 *****************************************************************************/
//followed is added for adaptation to easyg7231.h
#ifndef _cplusplus
#define bool unsigned char
#define false 0
#define true !false
#endif
//above is added for adaptation to easyg7231.h

#include "oortp.h"
#include "g711.h"
/*Added by Karl on 2004-11-17 below*/
#include "va_g729a.h"
#include "..\ootypes.h"
/*Added by Karl on 2004-11-17 above*/
/*Added by Karl on 2005-01-12 below*/
#include "EasyG7231.h"
#include "EasyG728.h"
#include "g72x.h"
/*Added by Karl on 2005-01-12 above*/
#ifdef _WIN32
#include "ooWave.h"
#include <time.h>
#else
#include "oomedialx.h"
#endif

//#pragma comment(lib,"./src/H323/ooLib/va_g729a.lib")


/*Added by Karl on 2004-11-16 below*/
#define T_H245AudioCapability_nonStandard 1
#define T_H245AudioCapability_g711Alaw64k 2
#define T_H245AudioCapability_g711Alaw56k 3
#define T_H245AudioCapability_g711Ulaw64k 4
#define T_H245AudioCapability_g711Ulaw56k 5
/*Modified by Karl on 2005-01-12 below*/
#define T_H245AudioCapability_g721_40k  6
#define T_H245AudioCapability_g721_32k  7
#define T_H245AudioCapability_g721_24k  8
//#define T_H245AudioCapability_g722_64k  6
//#define T_H245AudioCapability_g722_56k  7
//#define T_H245AudioCapability_g722_48k  8
/*Modified by Karl on 2005-01-12 above*/
#define T_H245AudioCapability_g7231     9
#define T_H245AudioCapability_g728      10
#define T_H245AudioCapability_g729      11
#define T_H245AudioCapability_g729AnnexA 12
#define T_H245AudioCapability_is11172AudioCapability 13
#define T_H245AudioCapability_is13818AudioCapability 14
#define T_H245AudioCapability_g729wAnnexB 15
#define T_H245AudioCapability_g729AnnexAwAnnexB 16
#define T_H245AudioCapability_g7231AnnexCCapability 17
#define T_H245AudioCapability_gsmFullRate 18
#define T_H245AudioCapability_gsmHalfRate 19
#define T_H245AudioCapability_gsmEnhancedFullRate 20
#define T_H245AudioCapability_genericAudioCapability 21
#define T_H245AudioCapability_g729Extensions 22
#define T_H245AudioCapability_vbd       23
#define T_H245AudioCapability_audioTelephonyEvent 24
#define T_H245AudioCapability_audioTone 25
#define T_H245AudioCapability_extElem1  26
/*Added by Karl on 2004-11-16 above*/
extern int	gnOutBuffCounter;

/* Initialize the media plug-in */
int ooInitializePlugin()
{
   /* Open the log file for write */
   fpLog = NULL;
   fpLog = fopen("media.log", "w");
   if(fpLog == NULL)
   {
      printf("\nERROR:Failed to open media.log log file");
      return -1;
   }
   
#ifdef _WIN32 
   OOLOG2(1, "Initializing sockets api");
   ooSocketsInit();
#else
   ooOpenAudioDevice();
#endif
   return 0;
}

/* Create a transmit RTP channel. This creates a UDP socket for transmit 
   and initializes the seqNo, timeStamp and ssrc for transmit session
*/
int oomCreateTransmitRTPChannel(int* channelId, char * destip, int port)
{
   int ret;
   OOLOG4(1, "StartOf:CreateTransmitRTPChannel:Destination %s:%d", destip, 
          port);
#ifdef _WIN32
   InitializeCriticalSection(&gReadMutex);
#endif
   if(destip == 0)
   {
      OOLOG2(1, "ERROR: NULL ip address");
      return -1;
   }
   if(port == 0)
   {
      OOLOG2(1, "ERROR: port can not be zero");
      return -1;
   }
   memset(&gXmitChannel, 0, sizeof(struct OORTPChannel));
   strcpy(gXmitChannel.ip, destip);
   gXmitChannel.port = port;

   /* Create transmit socket */
   ret = ooSocketCreateUDP (&(gXmitChannel.sock));
   if(ret != 0)
   {
      OOLOG2(1, "ERROR: Creation of rtp socket failed");
      return -1;
   }
   
#ifdef _WIN32
   /* Generate a random seqNo to start with */
   /* 65536 is max rtp seqNo after which it is reset*/
   srand((unsigned)time( NULL ) );
   gXmitChannel.seqNo = (unsigned short)((unsigned long)(rand() % 65536)); 
   /* Assign a random value to synchronization source */
   gXmitChannel.ssrc = (unsigned long)rand();
   /* generate a random timestamp. This will be incremented monotonically*/
   gXmitChannel.timestamp = (unsigned long) rand();
#else
   srandom(time(0));
   gXmitChannel.seqNo = (unsigned short)((unsigned long)(random() % 65536)); 
   /* Assign a random value to synchronization source */
   gXmitChannel.ssrc = (unsigned long)random();
   /* generate a random timestamp. This will be incremented monotonically*/
   gXmitChannel.timestamp = (unsigned long) random();
#endif   
   
   gXmitThrdHdl = 0;
   gXmitChannel.status = OO_CHAN_OPEN;
   OOLOG2(1, "EndOf:CreateTransmitRTPChannel");
   return 0;
}

/* Close the transmit RTP channel*/
int oomCloseTransmitRTPChannel(int channelId)
{
   int i=0, ret=0;
   OOLOG2(1, "StartOf:CloseTransmitRTPChannel");
   /* First stop the transmit thread if running */
   if(gXmitThrdHdl != 0)
   {
      gXmitFileLoop = 0;
      gXmitMicLoop = 0;
      i = 0;
      while(gXmitThrdHdl != 0)
      {
        // ooSleep(1000);
		  Sleep(1000);
         if(i++ == 3)
         {
            OOLOG2(1, "ERROR: Transmit thread not exiting...");
            exit(0);
         }
      }
   }
   /* Now close the socket */
   if(gXmitChannel.status == OO_CHAN_OPEN)
   {
#ifdef _WIN32
      DeleteCriticalSection(&gReadMutex);
#endif
      ret = ooSocketClose(gXmitChannel.sock);
      if(ret != 0) 
      {
         OOLOG2(1, "Warning: Failed to close the xmit RTP socket");
         return -1;
      }
      gXmitChannel.status = OO_CHAN_CLOSE;
   }
   OOLOG2(1, "EndOf:CloseTransmitRTPChannel");
   return 0;
}

/* Create Receive RTP channel. Basically, creates a socket for 
   receiving RTP packets. The socket is bound to ip and port which
   will be communicated to the remote endpoint via H.245 signalling
*/

int oomCreateReceiveRTPChannel(int* channelId, char * localip, int localport)
{
   int ret;
   OOIPADDR ipAddr;
   OOLOG4(1, "StartOf:CreateReceiveRTPChannel: local %s:%d", localip, 
          localport);
#ifdef _WIN32
   InitializeCriticalSection(&gPlayMutex);
#endif
   memset(&gRecvChannel, 0, sizeof(struct OORTPChannel));
   strcpy(gRecvChannel.ip, localip);
   gRecvChannel.port = localport;
   
   /* Create receive socket */
   ret = ooSocketCreateUDP (&(gRecvChannel.sock));
   if(ret != 0)
   {
      OOLOG2(1, "ERROR: Creation of rtp socket failed");
      return -1;
   }
   ret = ooSocketStrToAddr (localip, &ipAddr);
   if(ret != 0)
   {
      OOLOG2(1, "ERROR: IP address conversion failed");
      return -1;
   }
   ret = ooSocketBind (gRecvChannel.sock, ipAddr, localport); 
   if(ret != 0)
   {
      OOLOG2(1, "ERROR: Socket bind failed");
      return -1;
   }
   /* Initailze seqNo, ssrc and timestamp */
   gRecvChannel.seqNo = 0; 
   /* Assign a random value to synchronization source */
   gRecvChannel.ssrc = 0;
   /* generate a random timestamp. This will be incremented monotonically*/
   gRecvChannel.timestamp = 0;
   gRecvChannel.status = OO_CHAN_OPEN;
   OOLOG2(1, "EndOf:CreateReceiveRTPChannel:");
   return 0;
}

/* Close the receive RTP channel. Stops any receive thread running on the
   channel and then closes the socket.
*/
int oomCloseReceiveRTPChannel(int channelId)
{
   int i, ret=0;
   OOLOG2(1, "StartOf:CloseReceiveRTPChannel");
   /* Stop the receive thread, if running */
   if(gRecvThrdHdl != 0)
   {
      gRecvPlayLoop = 0;
      i = 0;
      while(gRecvThrdHdl != 0)
      {
        // ooSleep(1000);
		  Sleep(1000);
         if(i++ == 3)
         {
            OOLOG2(1, "ERROR: Receive thread not exiting...");
            exit(0);
         }
      }
   }
   /* Close the socket */
   if(gRecvChannel.status == OO_CHAN_OPEN)
   {
#ifdef _WIN32
      DeleteCriticalSection(&gPlayMutex);
#endif
      ret = ooSocketClose(gRecvChannel.sock);
      if(ret != 0)
      {
         OOLOG2(1, "Warning: Failed to close the receive RTP socket");
         return -1;
      }
      gRecvChannel.status = OO_CHAN_CLOSE;
   }
   OOLOG2(1, "EndOf:CloseReceiveRTPChannel");
   return 0;
}

/* Start transmitting wave file. Note that a transmit RTP channel
   has to be created before using this function.
*/
int oomStartTransmitWaveFile(int channelId, char * filename)
{
   int ret =0;
   OOLOG2(1, "StartOf:StartTransmitWaveFile");
   if(gXmitChannel.status != OO_CHAN_OPEN)
   {
      OOLOG2(1,"ERROR:Transmit RTP channel is not open");
      return -1;
   }
   /* Open the wave file for read */
   ret = ooOpenWaveFileForRead(filename);
   if( ret < 0)
   {
      OOLOG3(1, "ERROR: Failed to open the %s wave file for read", filename);
      return -1;
   }

   /* Create a thread which will read from the wave file and transmit data
      as rtp packets. 
   */
#ifdef _WIN32
   gXmitThrdHdl = CreateThread(0, 0, 
                    (LPTHREAD_START_ROUTINE)ooTransmitFileThreadFunc, 0, 0, 0);
#else
   pthread_create(&gXmitThrdHdl, NULL, ooTransmitFileThreadFuncLnx, 0);
#endif

   OOLOG2(1, "EndOf:StartTransmitWaveFile");
   return 0;
}
/* Stop the wave file transmission. Basically stops the transmit thread
*/
int oomStopTransmitWaveFile(int channelId)
{
   OOLOG2(1, "StartOf:StopTransmitWaveFile");
   gXmitFileLoop = 0;
   OOLOG2(1, "EndOf:StopTransmitWaveFile");
   return 0;
}

/* Start capturing data from microphone and transmitting as RTP packets.
*/   
/*Modified by Karl on 2004-11-17 below*/
int oomStartTransmitMic(int channelId,struct ooAppContext *context)
/*Modified by Karl on 2004-11-17 above*/
{
   int ret =0;
   int type;
   OOLOG2(1, "StartOf:StartTransmitMic");
#ifdef _WIN32
  // ret = ooOpenMic(); /* Open the Mic device for read */
  /* if( ret < 0)
   {
      OOLOG2(1, "ERROR: Failed to open the Mic device");
      return -1;
   }*/
   /* Start thread which will read data from Mic, and transmit it as RTP 
      packets.
   */   
      /*Modified by Karl on 2004-11-16 below */

   type = context->endCapability->transmitAudioCapability->t;
   if(type == T_H245AudioCapability_g729AnnexA){
	   gXmitThrdHdl = CreateThread(0, 0, 
                    (LPTHREAD_START_ROUTINE)ooG729ATransmitMicThreadFunc, 0, 0, 0);	   
   }
   if(type == T_H245AudioCapability_g711Ulaw64k){
	   gXmitThrdHdl = CreateThread(0, 0, 
                    (LPTHREAD_START_ROUTINE)ooG711TransmitMicThreadFunc, 0, 0, 0);
   }
   /*Added by Karl on 2004-11-26 below */
   if(type == T_H245AudioCapability_g721_32k){
	   gXmitThrdHdl = CreateThread(0, 0, 
                    (LPTHREAD_START_ROUTINE)ooG721TransmitMicThreadFunc, 0, 0, 0);
   }
   /*Modified by Karl on 2004-11-16 above */
   /*Added by Karl on 2005-01-13 below */
   if(type == T_H245AudioCapability_g728){
	   gXmitThrdHdl = CreateThread(0, 0, 
                    (LPTHREAD_START_ROUTINE)ooG728TransmitMicThreadFunc, 0, 0, 0);
   }
   if(type == T_H245AudioCapability_g7231){
	   gXmitThrdHdl = CreateThread(0, 0, 
                    (LPTHREAD_START_ROUTINE)ooG7231TransmitMicThreadFunc, 0, 0, 0);
   }
   /*Added by Karl on 2005-01-13 above */
   
#else
   pthread_create(&gXmitThrdHdl, NULL, ooTransmitMicThreadFuncLnx, 0);
#endif
   OOLOG2(1, "EndOf:StartTransmitMic");


   return 0;
}

/* Stop the transmit Mic thread */
int oomStopTransmitMic(int channelId)
{
   OOLOG2(1, "StartOf:StopTransmitMic");
   gXmitMicLoop = 0;
   OOLOG2(1, "EndOf:StopTransmitMic");
   return 0;
}

/* Start receiving audio on Receive RTP channel and playing it on
   speakers. 
*/
/*Modified by karl on 2004-11-17 below */
int oomStartReceiveAudioAndPlayback(int channelId,struct ooAppContext* context)
/*Modified by karl on 2004-11-17 above */
{
   int ret = 0;
#ifdef _WIN32
   WAVEFORMATEX waveFormat;
   
   /* Wave format of the audio to be played.*/
   waveFormat.wFormatTag = WAVE_FORMAT_PCM;
   waveFormat.nChannels = 1;
   waveFormat.nSamplesPerSec = 8000;
   waveFormat.nAvgBytesPerSec = 16000;
   waveFormat.nBlockAlign = 2;
   waveFormat.wBitsPerSample = 16;
   waveFormat.cbSize = 0;
#endif

   OOLOG2(1, "StartOf:StartReceiveAudioAndPlayback");
#ifdef _WIN32
   /*Open the speaker device */
   ret = ooOpenSpeaker(&ghWaveOut, waveFormat);
   if(ret != 0)
   {
      OOLOG2(1, "ERROR: Failed to open the Wave-out device");
      return -1;
   }

   /*Create  a thread which will receive rtp packets and playback the audio
     on the speaker device.
   */
   /* Modified by Karl on 2004-11-16 below*/
   if(context->endCapability->receiveAudioCapability->t == T_H245AudioCapability_g729AnnexA){
	   gRecvThrdHdl = CreateThread(0, 0, 
                  (LPTHREAD_START_ROUTINE)ooG729AReceiveSpeakerThreadFunc, 0, 0, 0);
   }
   if(context->endCapability->receiveAudioCapability->t == T_H245AudioCapability_g711Ulaw64k){
	   gRecvThrdHdl = CreateThread(0, 0, 
                  (LPTHREAD_START_ROUTINE)ooG711ReceiveSpeakerThreadFunc, 0, 0, 0);
   }
   if(context->endCapability->receiveAudioCapability->t == T_H245AudioCapability_g721_32k){
	   gRecvThrdHdl = CreateThread(0, 0, 
                  (LPTHREAD_START_ROUTINE)ooG721ReceiveSpeakerThreadFunc, 0, 0, 0);	   
   }
   /* Modified by Karl on 2004-11-16 above*/
   /* Modified by Karl on 2005-01-13 below*/
   if(context->endCapability->receiveAudioCapability->t == T_H245AudioCapability_g728){
	   gRecvThrdHdl = CreateThread(0, 0, 
                  (LPTHREAD_START_ROUTINE)ooG728ReceiveSpeakerThreadFunc, 0, 0, 0);	   
   }
   if(context->endCapability->receiveAudioCapability->t == T_H245AudioCapability_g7231){
	   gRecvThrdHdl = CreateThread(0, 0, 
                  (LPTHREAD_START_ROUTINE)ooG7231ReceiveSpeakerThreadFunc, 0, 0, 0);	   
   }
   /* Modified by Karl on 2005-01-13 above*/
#else
   pthread_create(&gRecvThrdHdl, NULL, ooReceiveSpeakerThreadFuncLnx, 0);
#endif
   OOLOG2(1, "EndOf:StartReceiveAudioAndPlayback");
   return 0;
}

/* Stops the receive and playback audio thread. */
int oomStopReceiveAudioAndPlayback(int channelId)
{
   OOLOG2(1, "StartOf:StopReceiveAudioAndPlayback");
   gRecvPlayLoop = 0;
   OOLOG2(1, "EndOf:StopReceiveAudioAndPlayback");
   return 0;
}

#ifdef _WIN32
/*Added by Karl on 2004-11-17 below */
/* Thread function to receive G729A RTP data and play it onto the
   speaker device.
*/
int ooG729AReceiveSpeakerThreadFunc()
{
   int ret = 0, i;
   char * pcSndBuf;
   short * psSndBuf;
   unsigned char psTempBuf[1024];
   struct timeval timeout;
   fd_set readfds;
   unsigned char	serial[10];
   short			synth[80];
   int				bfi;
   unsigned char buffer[1024]; 
   OOLOG2(1, "StartOf:G729AnnexA ReceiveSpeakerThread");
   //va_g729a_init_decoder();//Initialize the G729A decoder
   gRecvPlayLoop = 1; /* start recv loop */
   while(1)
   {
      if(!gRecvPlayLoop)
      {
         OOLOG2(1, "Exiting from RecvPlay loop ");
         break;
      }
      FD_ZERO(&readfds);
      FD_SET(gRecvChannel.sock, &readfds);
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      /* Check whether there is data for read */
      ret = ooSocketSelect(gRecvChannel.sock+1, &readfds, 0, 
                           0, &timeout);

      if(FD_ISSET(gRecvChannel.sock, &readfds))
      {
         pcSndBuf = (char*) malloc(1024);
         if(pcSndBuf == 0)
         {
            OOLOG2(1, "ERROR: Memalloc for playback buffer failed");
         }
         else{
            ret = ooSocketRecvFrom (gRecvChannel.sock, buffer, 
                                    1024, 0, 0);
                        
            /* We have a RTP packet in buffer. Assume that data always begins 
               from 12th octet, since standard RTP header length is 12.
               Convert G711 data to 16 bit PCM.
            */
            
            psSndBuf = (short*)pcSndBuf;
			for (i=0;i<1024;i++)
			{
               psTempBuf[i] = buffer[i];
			}
			
			/*--------------------------------------------------------------*
     		* Call the G729 decoder.                                            *
	    	*--------------------------------------------------------------*/
			//第一段10byte
			for(i=0;i<10;i++)
			{
				serial[i]=psTempBuf[i+12];
			}
            bfi = 0;
		    //va_g729a_decoder(serial, synth, bfi);
            for( i =0; i < 80; i++)
            {               
				psSndBuf[i] = synth[i];              
               
            }
			//第二段10byte
			for(i=0;i<10;i++)
			{
				serial[i]=psTempBuf[i+22];
			}
            bfi = 0;
		    //va_g729a_decoder(serial, synth, bfi);
            for( i =0; i < 80; i++)
            {               
				psSndBuf[i+80] = synth[i];              
               
            }
			//第三段10byte
			for(i=0;i<10;i++)
			{
				serial[i]=psTempBuf[i+32];
			}
            bfi = 0;
		    //va_g729a_decoder(serial, synth, bfi);
            for( i =0; i < 80; i++)
            {               
				psSndBuf[i+160] = synth[i];              
               
            }
			/*for( i =12; i < ret; i++)
            {                
               psSndBuf[i-12] = (short)ulaw2linear((unsigned char)(buffer[i]));              
               
            }*/
            /* Play the data buffer onto the speaker device*/            
            //ooPlayWaveBuffer(ghWaveOut, (char*)psSndBuf, (i-12)*sizeof(short));
			ooPlayWaveBuffer(ghWaveOut, (char*)psSndBuf, (240)*sizeof(short));
            pcSndBuf =0;
         }
      }
   }
   /*Close speaker*/
   if(ooCloseSpeaker(ghWaveOut) != 0)
      OOLOG2(1, "ERROR:Closing Speaker device");
   gRecvThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G729AnnexA ReceiveSpeakerThread");
   return 0;
}
/*Added by Karl on 2004-11-17 above */

/*Modified by Karl on 2004-11-17 below */
/* Thread function to receive G711 uLaw RTP data and play it onto the
   speaker device.
*/
int ooG711ReceiveSpeakerThreadFunc()
/*Modified by Karl on 2004-11-17 above */
{
   int ret = 0, i;
   char * pcSndBuf;
   short * psSndBuf;
   struct timeval timeout;
   fd_set readfds;
   /*unsigned*/ char buffer[1024]; 
   OOLOG2(1, "StartOf:G711 uLaw ReceiveSpeakerThread");
   gRecvPlayLoop = 1; /* start recv loop */
   while(1)
   {
      if(!gRecvPlayLoop)
      {
         OOLOG2(1, "Exiting from RecvPlay loop ");
         break;
      }
      FD_ZERO(&readfds);
      FD_SET(gRecvChannel.sock, &readfds);
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      /* Check whether there is data for read */
      ret = ooSocketSelect(gRecvChannel.sock+1, &readfds, 0, 
                           0, &timeout);

      if(FD_ISSET(gRecvChannel.sock, &readfds))
      {
         pcSndBuf = (char*) malloc(1024);
         if(pcSndBuf == 0)
         {
            OOLOG2(1, "ERROR: Memalloc for playback buffer failed");
         }
         else{
            ret = ooSocketRecvFrom (gRecvChannel.sock, buffer, 
                                    1024, 0, 0);
                        
            /* We have a RTP packet in buffer. Assume that data always begins 
               from 12th octet, since standard RTP header length is 12.
               Convert G711 data to 16 bit PCM.
            */
            
            psSndBuf = (short*)pcSndBuf;
            for( i =12; i < ret; i++)
            {                
               psSndBuf[i-12] = (short)ulaw2linear((unsigned char)(buffer[i]));
               /*c = (short)ulaw2linear((unsigned char)(buffer[i]));
               pcSndBuf[j++]= (unsigned char) ((c>>8) & 0xff);
               pcSndBuf[j++] = (unsigned char) (c & 0xff);*/
            }
            /* Play the data buffer onto the speaker device*/
            /*ooPlayWaveBuffer(ghWaveOut, (char*)pcSndBuf, j);*/
            ooPlayWaveBuffer(ghWaveOut, (char*)psSndBuf, (i-12)*sizeof(short));
            pcSndBuf =0;
         }
      }
   }
   /*Close speaker*/
   if(ooCloseSpeaker(ghWaveOut) != 0)
      OOLOG2(1, "ERROR:Closing Speaker device");
   gRecvThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G711 uLaw ReceiveSpeakerThread");
   return 0;
}



/* Read the wave file and transmit wave file data
   as rtp packets on RTP transmit channel.
*/
static int ooTransmitFileThreadFunc()
{
   int DataTxed=0;
   long audioDataSize;
   int ret = 0;
   char databuf[480];
   short *tempBuf;
   unsigned char sendBuf[252]; /* additional 12 bytes for RTP header */
   int marker = 1; /* Only first packet has marker bit set */
   int i;
   OOLOG2(1, "StartOf:TransmitFileThread");
   
   gXmitFileLoop = 1;
   while(1)
   {
      if(!gXmitFileLoop)
         break;
      /* Number of bytes read is returned and stored in audioDataSize */

      audioDataSize = ooReadWaveFileData(databuf, 480);

      if(audioDataSize>0) /* If any data is read */
      {
         DataTxed += audioDataSize;
         /* RTP version = 2, padding = 0, extension = 0, CSRC = 0 */
         sendBuf[0] = 0x80; 
         sendBuf[1] = 0x00; /* RTP Payload type PCM ulaw Need to use #define */
         if(marker)
         {
            sendBuf[1] |= 0x80; /* Set marker bit for first packet */
            marker = 0;
         }
         /*packet sequence number*/
         *((short *)(sendBuf + 2)) = ooHTONS((short)gXmitChannel.seqNo);
         /*packet timestamp*/
         *((long  *)(sendBuf + 4)) = ooHTONL((long)gXmitChannel.timestamp);
         /*packet ssrc*/
         *((long  *)(sendBuf + 8)) = ooHTONL((long)gXmitChannel.ssrc);
         
         if(gXmitChannel.seqNo == 65535)
            gXmitChannel.seqNo = 0; /* Seq num wrap around */
         else
            gXmitChannel.seqNo += 1;

         /* Next timestamp is current timestamp + play duration of the 
            current buffer.
         */
         gXmitChannel.timestamp += 480;
         tempBuf = (short*) databuf;
         /* Copy PCM audio data into sendBuf as ulaw audio data*/
         for(i=0; i<(audioDataSize/2); i++)
         {
            sendBuf[12+i] = (unsigned char) linear2ulaw((int)*(tempBuf+i));
         }
         /* transmit rtp packet */
         ret = ooSocketSendTo(gXmitChannel.sock, sendBuf, 
                     (audioDataSize/2+12), gXmitChannel.ip, gXmitChannel.port);
         if(ret<0)
         {
            OOLOG2(1, "ERROR: Failed to transmit rtp packet");
            return -1;
         }
         Sleep(2);/* Just slows down the transmit rate a bit */
      }
      else{
         if(DataTxed == gWaveFile.dataSize)
         {
            printf("File transmission over\n");
            gXmitFileLoop = 0;
         }
         else{
            OOLOG2(1, "ERROR: Data read failure");
            gXmitFileLoop = 0;
         }
      }
   }
   /* Close the wave file */
   ret = ooCloseWaveFile();
   if(ret < 0)
   {
      OOLOG2(1, "ERROR: Failed to close the open wave file");
      return -1;
   }
   gXmitThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:TransmitFileThread");
   return 0;
}

/*Added by Karl on 2004-11-17 below */
/* Thread function to read data from microphone and transmit it
   as G729A rtp packets.
*/
static int ooG729ATransmitMicThreadFunc()
{   
   unsigned char sendBuf[42];
   short* tempBuf;
   int marker = 1; 
   unsigned int i;
   int ret;
   short			speech[80];
   unsigned char	serial[10];
   OOLOG2(1, "StartOf:G729AnnexA TransmitMicThread");
   ret = ooOpenMic();/* Open the Mic device*/
   if(ret < 0)
   {
      OOLOG2(1, "ERROR: Opening the Mic device");
      return -1;
   }
   //Initialization of G729 encoder
   //va_g729a_init_encoder();
   /* Start data capture */
   ooStartMicDataCapture(ghWaveIn);
   gXmitMicLoop = 1;
   while(1)
   {
      if(!gXmitMicLoop)
         break;
      if(gpWaveHead != 0)
      {
         //memset(sendBuf, 0, 252);
         memset(sendBuf, 0, 42);
         memset(speech, 0, 80);
		 memset(serial, 0, 10);		 

         /* RTP version = 2, padding = 0, extension = 0, CSRC = 0 */
         sendBuf[0] = 0x80; 
         /* RTP Payload type PCM ulaw Need to use #define */
         sendBuf[1] = 0x00; 
         if(marker)
         {
            sendBuf[1] |= 0x80; /* Set marker bit for first packet */
            marker = 0;
         }
         /*packet sequence number*/
         *((short *)(sendBuf + 2)) = ooHTONS((short)gXmitChannel.seqNo);
         /*packet timestamp*/
         *((long  *)(sendBuf + 4)) = ooHTONL((long)gXmitChannel.timestamp);
         /*packet ssrc*/
         *((long  *)(sendBuf + 8)) = ooHTONL((long)gXmitChannel.ssrc);
         
         if(gXmitChannel.seqNo == 65535)
            gXmitChannel.seqNo = 0; /* Seq num wrap around */
         else
            gXmitChannel.seqNo += 1;

         /* Next timestamp is current timestamp + play duration of the 
            current buffer
         */
         gXmitChannel.timestamp += OORTPPACKETDATASIZE;
         
		 /* Copy PCM audio data into sendBuf as  audio data*/
         tempBuf = (short*)gpWaveHead->pWaveHdr->lpData;
		 
		 //压缩第一段80byte
		 for(i=0;i<80;i++)
		 {
             speech[i]=tempBuf[i];
		 }
		 //va_g729a_encoder(speech, serial);
         for(i=0; i<10; i++)
         {
            sendBuf[12+i] = serial[i];
         }
		 //压缩第二段80byte
		 for(i=0;i<80;i++)
		 {
             speech[i]=tempBuf[80+i];
		 }
		 //va_g729a_encoder(speech, serial);
         for(i=0; i<10; i=i+1)
         {
            sendBuf[22+i] = serial[i];
         }
		 //压缩第三段80byte
		 for(i=0;i<80;i++)
		 {
             speech[i]=tempBuf[160+i];
		 }
		 //va_g729a_encoder(speech, serial);
         for(i=0; i<10; i=i+1)
         {
            sendBuf[32+i] = serial[i];
         }
         /* Convert data into g711 ulaw and copy to sendBuf */
         /*tempBuf = (short*)gpWaveHead->pWaveHdr->lpData;
         for(i=0; i<(gpWaveHead->pWaveHdr->dwBytesRecorded/2); i=i+1)
         {
            sendBuf[12+i] = (unsigned char) linear2ulaw((int)*(tempBuf+i));
         }*/
         /* transmit rtp packet */
		 ret = ooSocketSendTo(gXmitChannel.sock, sendBuf, 
                              30+12, 
                              gXmitChannel.ip, gXmitChannel.port);
         //ret = ooSocketSendTo(gXmitChannel.sock, sendBuf, 
         //                     (gpWaveHead->pWaveHdr->dwBytesRecorded/2+12), 
         //                     gXmitChannel.ip, gXmitChannel.port);
         if(ret<0)
         {
            OOLOG2(1, "ERROR: Failed to transmit rtp packet");
            return -1;
         }
         /* Requeue the buffer into the Mic device for data capture. */
         if(waveInAddBuffer(ghWaveIn, gpWaveHead->pWaveHdr, 
                            sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
         {
            OOLOG2(1, "ERROR: In adding wave-in buffers");
            return -1;
         }
         EnterCriticalSection(&gReadMutex);
         gQueuedBufCount++; /* Increase the count of queued buffers by one*/
         ooRemoveHeadOfWaveBufferList();
         LeaveCriticalSection(&gReadMutex);
      }
      else
         Sleep(5); /*else sleep for 5 ms*/
   }/*End of while loop*/
   ooCloseMic(ghWaveIn);
   gXmitThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G729AnnexA TransmitMicThread");
   return 0;
}
/*Added by Karl on 2004-11-17 above */

/*Modified by Karl on 2004-11-17 below */
/* Thread function to read data from microphone and transmit it
   as G711 rtp packets.
*/
static int ooG711TransmitMicThreadFunc()
/*Modified by Karl on 2004-11-17 below */
{
   unsigned char sendBuf[252];
   short* tempBuf;
   int marker = 1; 
   unsigned int i;
   int ret;
   OOLOG2(1, "StartOf:G711 TransmitMicThread");
   ret = ooOpenMic();/* Open the Mic device*/
   if(ret < 0)
   {
      OOLOG2(1, "ERROR: Opening the Mic device");
      return -1;
   }


   /* Start data capture */
   ooStartMicDataCapture(ghWaveIn);
   gXmitMicLoop = 1;
   while(1)
   {
      if(!gXmitMicLoop)
         break;
      if(gpWaveHead != 0)
      {
         memset(sendBuf, 0, 252);
         /* RTP version = 2, padding = 0, extension = 0, CSRC = 0 */
         sendBuf[0] = 0x80; 
         /* RTP Payload type PCM ulaw Need to use #define */
         sendBuf[1] = 0x00; 
         if(marker)
         {
            sendBuf[1] |= 0x80; /* Set marker bit for first packet */
            marker = 0;
         }
         /*packet sequence number*/
         *((short *)(sendBuf + 2)) = ooHTONS((short)gXmitChannel.seqNo);
         /*packet timestamp*/
         *((long  *)(sendBuf + 4)) = ooHTONL((long)gXmitChannel.timestamp);
         /*packet ssrc*/
         *((long  *)(sendBuf + 8)) = ooHTONL((long)gXmitChannel.ssrc);
         
         if(gXmitChannel.seqNo == 65535)
            gXmitChannel.seqNo = 0; /* Seq num wrap around */
         else
            gXmitChannel.seqNo += 1;

         /* Next timestamp is current timestamp + play duration of the 
            current buffer
         */
         gXmitChannel.timestamp += OORTPPACKETDATASIZE;
               
         /* Convert data into g711 ulaw and copy to sendBuf */
         tempBuf = (short*)gpWaveHead->pWaveHdr->lpData;
         for(i=0; i<(gpWaveHead->pWaveHdr->dwBytesRecorded/2); i=i+1)
         {
            sendBuf[12+i] = (unsigned char) linear2ulaw((int)*(tempBuf+i));
         }
         /* transmit rtp packet */
         ret = ooSocketSendTo(gXmitChannel.sock, sendBuf, 
                              (gpWaveHead->pWaveHdr->dwBytesRecorded/2+12), 
                              gXmitChannel.ip, gXmitChannel.port);
         if(ret<0)
         {
            OOLOG2(1, "ERROR: Failed to transmit rtp packet");
            return -1;
         }
         /* Requeue the buffer into the Mic device for data capture. */
         if(waveInAddBuffer(ghWaveIn, gpWaveHead->pWaveHdr, 
                            sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
         {
            OOLOG2(1, "ERROR: In adding wave-in buffers");
            return -1;
         }
         EnterCriticalSection(&gReadMutex);
         gQueuedBufCount++; /* Increase the count of queued buffers by one*/
         ooRemoveHeadOfWaveBufferList();
         LeaveCriticalSection(&gReadMutex);
      }
      else
         Sleep(5); /*else sleep for 5 ms*/
   }/*End of while loop*/
   ooCloseMic(ghWaveIn);
   gXmitThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G711 TransmitMicThread");
   return 0;
}

/*Added by Karl on 2005-01-13 below */
/* Thread function to receive G728 RTP data and play it onto the
   speaker device.
*/
int ooG728ReceiveSpeakerThreadFunc()
{
   int ret = 0, i;
   char * pcSndBuf;
   short * psSndBuf;
   unsigned char psTempBuf[1024];
   struct timeval timeout;
   fd_set readfds;
   unsigned char	serial[L_G728_FRAME_COMPRESSED];
   short			synth[L_G728_FRAME];
   //CODER_HANDLE hDecoder;

   unsigned char buffer[1024]; 
   OOLOG2(1, "StartOf:G728 ReceiveSpeakerThread");
   //hDecoder = G728_init_decoder(  );//Initialize the G728 decoder
   gRecvPlayLoop = 1; /* start recv loop */
   while(1)
   {
      if(!gRecvPlayLoop)
      {
         OOLOG2(1, "Exiting from RecvPlay loop ");
         break;
      }
      FD_ZERO(&readfds);
      FD_SET(gRecvChannel.sock, &readfds);
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      /* Check whether there is data for read */
      ret = ooSocketSelect(gRecvChannel.sock+1, &readfds, 0, 
                           0, &timeout);

      if(FD_ISSET(gRecvChannel.sock, &readfds))
      {
         pcSndBuf = (char*) malloc(1024);
         if(pcSndBuf == 0)
         {
            OOLOG2(1, "ERROR: Memalloc for playback buffer failed");
         }
         else{
            ret = ooSocketRecvFrom (gRecvChannel.sock, buffer, 
                                    1024, 0, 0);
                        
            /* We have a RTP packet in buffer. Assume that data always begins 
               from 12th octet, since standard RTP header length is 12.
               Convert G728 data to 16 bit PCM.
            */
            
            psSndBuf = (short*)pcSndBuf;
			for (i=0;i<1024;i++)
			{
               psTempBuf[i] = buffer[i];
			}
			
			/*--------------------------------------------------------------*
     		* Call the G728 decoder.                                            *
	    	*--------------------------------------------------------------*/
			//第一段20byte
			for(i=0;i<20;i++)
			{
				serial[i]=psTempBuf[i+12];
			}
            //G728_decoder(hDecoder, serial, synth );
            for( i =0; i < 80; i++)
            {               
				psSndBuf[i] = synth[i];              
               
            }
			//第二段20byte
			for(i=0;i<20;i++)
			{
				serial[i]=psTempBuf[i+32];
			}
            //G728_decoder(hDecoder, serial, synth );
            for( i =0; i < 80; i++)
            {               
				psSndBuf[i+80] = synth[i]; 
               
            }
			//第三段20byte
			for(i=0;i<20;i++)
			{
				serial[i]=psTempBuf[i+52];
			}
            //G728_decoder(hDecoder, serial, synth );
            for( i =0; i < 80; i++)
            {               
				psSndBuf[i+160] = synth[i];              
               
            }
            /* Play the data buffer onto the speaker device*/
			ooPlayWaveBuffer(ghWaveOut, (char*)psSndBuf, (240)*sizeof(short));
            pcSndBuf =0;
         }
      }
   }
   /*Close speaker*/
   //G728_release_decoder( hDecoder );
   if(ooCloseSpeaker(ghWaveOut) != 0)
      OOLOG2(1, "ERROR:Closing Speaker device");
   gRecvThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G728 ReceiveSpeakerThread");
   return 0;
}

/* Thread function to read data from microphone and transmit it
   as G728 rtp packets.
*/
static int ooG728TransmitMicThreadFunc()
{   
   unsigned char sendBuf[72];
   short* tempBuf;
   int marker = 1; 
   unsigned int i;
   int ret;
   short			speech[L_G728_FRAME];
   unsigned char	serial[L_G728_FRAME_COMPRESSED];
   //CODER_HANDLE hEncoder;
   OOLOG2(1, "StartOf:G728 TransmitMicThread");
   ret = ooOpenMic();/* Open the Mic device*/
   if(ret < 0)
   {
      OOLOG2(1, "ERROR: Opening the Mic device");
      return -1;
   }
   //Initialization of G728 encoder
   //hEncoder = G728_init_encoder( );
   /* Start data capture */
   ooStartMicDataCapture(ghWaveIn);
   gXmitMicLoop = 1;
   while(1)
   {
      if(!gXmitMicLoop)
         break;
      if(gpWaveHead != 0)
      {         
         memset(sendBuf, 0, 72);
         memset(speech, 0, 80);
		 memset(serial, 0, 20);		 

         /* RTP version = 2, padding = 0, extension = 0, CSRC = 0 */
         sendBuf[0] = 0x80; 
         /* RTP Payload type PCM ulaw Need to use #define */
         sendBuf[1] = 0x00; 
         if(marker)
         {
            sendBuf[1] |= 0x80; /* Set marker bit for first packet */
            marker = 0;
         }
         /*packet sequence number*/
         *((short *)(sendBuf + 2)) = ooHTONS((short)gXmitChannel.seqNo);
         /*packet timestamp*/
         *((long  *)(sendBuf + 4)) = ooHTONL((long)gXmitChannel.timestamp);
         /*packet ssrc*/
         *((long  *)(sendBuf + 8)) = ooHTONL((long)gXmitChannel.ssrc);
         
         if(gXmitChannel.seqNo == 65535)
            gXmitChannel.seqNo = 0; /* Seq num wrap around */
         else
            gXmitChannel.seqNo += 1;

         /* Next timestamp is current timestamp + play duration of the 
            current buffer
         */
         gXmitChannel.timestamp += OORTPPACKETDATASIZE;
         
		 /* Copy PCM audio data into sendBuf as  audio data*/
         tempBuf = (short*)gpWaveHead->pWaveHdr->lpData;
		 /* Convert data into g728 and copy to sendBuf */
		 //压缩第一段80byte
		 for(i=0;i<80;i++)
		 {
             speech[i]=tempBuf[i];
		 }
		 //G728_encoder(hEncoder, speech, serial);
         for(i=0; i<20; i++)
         {
            sendBuf[12+i] = serial[i];
         }
		 //压缩第二段80byte
		 for(i=0;i<80;i++)
		 {
             speech[i]=tempBuf[80+i];
		 }
		 //G728_encoder(hEncoder, speech, serial);
         for(i=0; i<20; i=i+1)
         {
            sendBuf[32+i] = serial[i];
         }
		 //压缩第三段80byte
		 for(i=0;i<80;i++)
		 {
             speech[i]=tempBuf[160+i];
		 }
		 //G728_encoder(hEncoder, speech, serial);
         for(i=0; i<20; i=i+1)
         {
            sendBuf[52+i] = serial[i];
         }         
         
         /* transmit rtp packet */
		 ret = ooSocketSendTo(gXmitChannel.sock, sendBuf, 
                              60+12, 
                              gXmitChannel.ip, gXmitChannel.port);
         if(ret<0)
         {
            OOLOG2(1, "ERROR: Failed to transmit rtp packet");
            return -1;
         }
         /* Requeue the buffer into the Mic device for data capture. */
         if(waveInAddBuffer(ghWaveIn, gpWaveHead->pWaveHdr, 
                            sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
         {
            OOLOG2(1, "ERROR: In adding wave-in buffers");
            return -1;
         }
         EnterCriticalSection(&gReadMutex);
         gQueuedBufCount++; /* Increase the count of queued buffers by one*/
         ooRemoveHeadOfWaveBufferList();
         LeaveCriticalSection(&gReadMutex);
      }
      else
         Sleep(5); /*else sleep for 5 ms*/
   }/*End of while loop*/
   //G728_release_encoder( hEncoder );
   ooCloseMic(ghWaveIn);
   gXmitThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G728 TransmitMicThread");
   return 0;
}




/* Thread function to receive G7231 RTP data and play it onto the
   speaker device.
*/
int ooG7231ReceiveSpeakerThreadFunc()
{
   int ret = 0, i;
   char * pcSndBuf;
   short * psSndBuf;
   unsigned char psTempBuf[1024];
   struct timeval timeout;
   fd_set readfds;
   unsigned char	serial[L_G7231_FRAME_COMPRESSED_53];
   short			synth[L_G7231_FRAME];
   //CODER_HANDLE hDecoder;

   unsigned char buffer[1024]; 
   OOLOG2(1, "StartOf:G7231 ReceiveSpeakerThread");
   //hDecoder = EasyG7231_init_decoder( false );//Initialize the G7231 decoder
   gRecvPlayLoop = 1; /* start recv loop */
   while(1)
   {
      if(!gRecvPlayLoop)
      {
         OOLOG2(1, "Exiting from RecvPlay loop ");
         break;
      }
      FD_ZERO(&readfds);
      FD_SET(gRecvChannel.sock, &readfds);
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      /* Check whether there is data for read */
      ret = ooSocketSelect(gRecvChannel.sock+1, &readfds, 0, 
                           0, &timeout);

      if(FD_ISSET(gRecvChannel.sock, &readfds))
      {
         pcSndBuf = (char*) malloc(1024);
         if(pcSndBuf == 0)
         {
            OOLOG2(1, "ERROR: Memalloc for playback buffer failed");
         }
         else{
            ret = ooSocketRecvFrom (gRecvChannel.sock, buffer, 
                                    1024, 0, 0);
                        
            /* We have a RTP packet in buffer. Assume that data always begins 
               from 12th octet, since standard RTP header length is 12.
               Convert G7231 data to 16 bit PCM.
            */
            
            psSndBuf = (short*)pcSndBuf;
			for (i=0;i<1024;i++)
			{
               psTempBuf[i] = buffer[i];
			}
			
			/*--------------------------------------------------------------*
     		* Call the G7231 decoder.                                       *
	    	*--------------------------------------------------------------*/			
			for(i=0;i<L_G7231_FRAME_COMPRESSED_53;i++)
			{
				serial[i]=psTempBuf[i+12];
			}
            //EasyG7231_decoder(hDecoder, serial, synth );
            for( i =0; i < L_G7231_FRAME; i++)
            {               
				psSndBuf[i] = synth[i];              
               
            }			
            /* Play the data buffer onto the speaker device*/
			ooPlayWaveBuffer(ghWaveOut, (char*)psSndBuf, (240)*sizeof(short));
            pcSndBuf =0;
         }
      }
   }
   /*Close speaker*/
   //EasyG7231_release_decoder( hDecoder );
   if(ooCloseSpeaker(ghWaveOut) != 0)
      OOLOG2(1, "ERROR:Closing Speaker device");
   gRecvThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G7231 ReceiveSpeakerThread");
   return 0;
}

/* Thread function to read data from microphone and transmit it
   as G7231 rtp packets.
*/
static int ooG7231TransmitMicThreadFunc()
{   
   unsigned char sendBuf[32];
   short* tempBuf;
   int marker = 1; 
   unsigned int i;
   int ret;
   short			speech[L_G7231_FRAME];
   unsigned char	serial[L_G7231_FRAME_COMPRESSED_53];
//   CODER_HANDLE hEncoder;
   OOLOG2(1, "StartOf:G7231 TransmitMicThread");
   ret = ooOpenMic();/* Open the Mic device*/
   if(ret < 0)
   {
      OOLOG2(1, "ERROR: Opening the Mic device");
      return -1;
   }
   //Initialization of G7231 encoder
//   hEncoder = EasyG7231_init_encoder( false );
   /* Start data capture */
   ooStartMicDataCapture(ghWaveIn);
   gXmitMicLoop = 1;
   while(1)
   {
      if(!gXmitMicLoop)
         break;
      if(gpWaveHead != 0)
      {         
         memset(sendBuf, 0, 32);
         memset(speech, 0, 240);
		 memset(serial, 0, 20);		 

         /* RTP version = 2, padding = 0, extension = 0, CSRC = 0 */
         sendBuf[0] = 0x80; 
         /* RTP Payload type PCM ulaw Need to use #define */
         sendBuf[1] = 0x00; 
         if(marker)
         {
            sendBuf[1] |= 0x80; /* Set marker bit for first packet */
            marker = 0;
         }
         /*packet sequence number*/
         *((short *)(sendBuf + 2)) = ooHTONS((short)gXmitChannel.seqNo);
         /*packet timestamp*/
         *((long  *)(sendBuf + 4)) = ooHTONL((long)gXmitChannel.timestamp);
         /*packet ssrc*/
         *((long  *)(sendBuf + 8)) = ooHTONL((long)gXmitChannel.ssrc);
         
         if(gXmitChannel.seqNo == 65535)
            gXmitChannel.seqNo = 0; /* Seq num wrap around */
         else
            gXmitChannel.seqNo += 1;

         /* Next timestamp is current timestamp + play duration of the 
            current buffer
         */
         gXmitChannel.timestamp += OORTPPACKETDATASIZE;
         
		 /* Copy PCM audio data into sendBuf as  audio data*/
         tempBuf = (short*)gpWaveHead->pWaveHdr->lpData;
		 /* Convert data into g7231 and copy to sendBuf */		 
		 for(i=0;i<240;i++)
		 {
             speech[i]=tempBuf[i];
		 }
//		 EasyG7231_encoder(hEncoder, speech, serial);
         for(i=0; i<20; i++)
         {
            sendBuf[12+i] = serial[i];
         }		 
         
         /* transmit rtp packet */
		 ret = ooSocketSendTo(gXmitChannel.sock, sendBuf, 
                              20+12, 
                              gXmitChannel.ip, gXmitChannel.port);
         if(ret<0)
         {
            OOLOG2(1, "ERROR: Failed to transmit rtp packet");
            return -1;
         }
         /* Requeue the buffer into the Mic device for data capture. */
         if(waveInAddBuffer(ghWaveIn, gpWaveHead->pWaveHdr, 
                            sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
         {
            OOLOG2(1, "ERROR: In adding wave-in buffers");
            return -1;
         }
         EnterCriticalSection(&gReadMutex);
         gQueuedBufCount++; /* Increase the count of queued buffers by one*/
         ooRemoveHeadOfWaveBufferList();
         LeaveCriticalSection(&gReadMutex);
      }
      else
         Sleep(5); /*else sleep for 5 ms*/
   }/*End of while loop*/
//   EasyG7231_release_encoder( hEncoder );
   ooCloseMic(ghWaveIn);
   gXmitThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G7231 TransmitMicThread");
   return 0;
}
/*Added by Karl on 2005-01-13 above */


/*Added by Karl on 2004-11-24 below */
/* Thread function to receive G721 RTP data and play it onto the
   speaker device.
*/
int ooG721ReceiveSpeakerThreadFunc()
{
   int ret = 0, i;   
   struct timeval timeout;
   fd_set readfds;
   unsigned char buffer[1024]; 
   short * psSndBuf;
   
   /*G721*/
   struct g72x_state	state;
   short		 sample;
   int	dec_bits;
   int resid = 0;
   int nBit = 4;//G721=4
   int out_size;
   int iCount;
   //short sample_short;
   
   int idataSamples = 0;
   unsigned char pDataTrack[240];
   unsigned char in_byte;
   unsigned char in_byte1;
   unsigned char in_byte2;   
   
   out_size = sizeof (char);
   dec_bits = 4;
   g72x_init_state(&state);
   /*G721*/

   OOLOG2(1, "StartOf:G721 ReceiveSpeakerThread");   
   gRecvPlayLoop = 1; /* start recv loop */
   memset(pDataTrack,0,240);
   while(1)
   {
      if(!gRecvPlayLoop)
      {
         OOLOG2(1, "Exiting from RecvPlay loop ");
         break;
      }
      FD_ZERO(&readfds);
      FD_SET(gRecvChannel.sock, &readfds);
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      /* Check whether there is data for read */
      ret = ooSocketSelect(gRecvChannel.sock+1, &readfds, 0, 
                           0, &timeout);

      if(FD_ISSET(gRecvChannel.sock, &readfds))
      {
         psSndBuf = (short *) malloc(1024);
         if(psSndBuf == 0)
         {
            OOLOG2(1, "ERROR: Memalloc for playback buffer failed");
         }
         else{
            ret = ooSocketRecvFrom (gRecvChannel.sock, buffer, 
                                    1024, 0, 0);
                        
            /* We have a RTP packet in buffer. Assume that data always begins 
               from 12th octet, since standard RTP header length is 12.
               Convert G721 data to 16 bit PCM.
            */
			/*Decode data by g721 */
			for (i = 0; i < 120; i++) {				
				in_byte1 = buffer[i+12];
				in_byte2 = buffer[i+12];
				in_byte1 = in_byte1 >> 4;
				in_byte2 = in_byte2 << 4;
				in_byte2 = in_byte2 >> 4;
                in_byte = in_byte1;				
				iCount = 2 * i;				
				sample = g721_decoder(in_byte1, AUDIO_ENCODING_LINEAR, &state);
				psSndBuf[iCount] = sample;						
				iCount++;					
				sample = g721_decoder(in_byte2, AUDIO_ENCODING_LINEAR, &state);
				psSndBuf[iCount] = sample;						
			}	
			
            /* Play the data buffer onto the speaker device*/            
			ooPlayWaveBuffer(ghWaveOut, (unsigned char*)psSndBuf, (240)*sizeof(short));
			psSndBuf = 0;
         }
      }
   }
   /*Close speaker*/
   if(ooCloseSpeaker(ghWaveOut) != 0)
      OOLOG2(1, "ERROR:Closing Speaker device");
   gRecvThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G721 ReceiveSpeakerThread");
   return 0;
}
/*Added by Karl on 2004-11-24 above */

/*Added by Karl on 2004-11-23 below */
/* Thread function to read data from microphone and transmit it
   as G721 rtp packets.
*/
static int ooG721TransmitMicThreadFunc()
{
   unsigned char sendBuf[132];   
   short* tempBuf;
   int marker = 1; 
   int i;   
   int ret;
   /*G721*/
   struct g72x_state	state;
   int code;
   int resid = 0;
   int nBit = 4;//G721=4
   short sample_short;   
   int idataSamples = 0;
   BYTE *pDataTrack;
   g72x_init_state(&state);
   /*G721*/

   OOLOG2(1, "StartOf:G721 TransmitMicThread");
   ret = ooOpenMic();/* Open the Mic device*/
   if(ret < 0)
   {
      OOLOG2(1, "ERROR: Opening the Mic device");
      return -1;
   }   
   /* Start data capture */
   ooStartMicDataCapture(ghWaveIn);
   gXmitMicLoop = 1;
   while(1)
   {
      if(!gXmitMicLoop)
         break;
      if(gpWaveHead != 0)
      {         
         memset(sendBuf, 0, 132);        		 

         /* RTP version = 2, padding = 0, extension = 0, CSRC = 0 */
         sendBuf[0] = 0x80; 
         /* RTP Payload type PCM ulaw Need to use #define */
         sendBuf[1] = 0x00; 
         if(marker)
         {
            sendBuf[1] |= 0x80; /* Set marker bit for first packet */
            marker = 0;
         }
         /*packet sequence number*/
         *((short *)(sendBuf + 2)) = ooHTONS((short)gXmitChannel.seqNo);
         /*packet timestamp*/
         *((long  *)(sendBuf + 4)) = ooHTONL((long)gXmitChannel.timestamp);
         /*packet ssrc*/
         *((long  *)(sendBuf + 8)) = ooHTONL((long)gXmitChannel.ssrc);
         
         if(gXmitChannel.seqNo == 65535)
            gXmitChannel.seqNo = 0; /* Seq num wrap around */
         else
            gXmitChannel.seqNo += 1;

         /* Next timestamp is current timestamp + play duration of the 
            current buffer
         */
         gXmitChannel.timestamp += OORTPPACKETDATASIZE;
         
		 /* Copy PCM audio data into sendBuf as  audio data*/
         tempBuf = (short*)gpWaveHead->pWaveHdr->lpData;

		 idataSamples = gpWaveHead->pWaveHdr->dwBytesRecorded/2;
		 
		 
		 //Encode data 
		 gnOutBuffCounter = 0;	//Reset output buffer counter at first
     	 pDataTrack = (unsigned char*) malloc(1024);
		 for (i = 0; i < idataSamples; i++) {
	 		sample_short = tempBuf[i];//pSrcBuff[i];
	  		code = g721_encoder(sample_short, AUDIO_ENCODING_LINEAR, &state);
			resid = pack_output(code, nBit, pDataTrack);
		 }
		 //Write zero codes until all residual codes are written out */
		 while (resid) {
	 	 	resid = pack_output(0, nBit, pDataTrack);
		 }

		 for(i = 0; i < idataSamples/2; i++){
             sendBuf[12+i] = pDataTrack[i];
		 }
         /* transmit rtp packet */
		 /*because G721 is 32kbps,the length is dataSample*(32/64)+12*/
		 ret = ooSocketSendTo(gXmitChannel.sock, sendBuf, 
                              idataSamples/2+12, 
                              gXmitChannel.ip, gXmitChannel.port);         
         if(ret<0)
         {
            OOLOG2(1, "ERROR: Failed to transmit rtp packet");
            return -1;
         }
         /* Requeue the buffer into the Mic device for data capture. */
         if(waveInAddBuffer(ghWaveIn, gpWaveHead->pWaveHdr, 
                            sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
         {
            OOLOG2(1, "ERROR: In adding wave-in buffers");
            return -1;
         }
         EnterCriticalSection(&gReadMutex);
         gQueuedBufCount++; /* Increase the count of queued buffers by one*/
         ooRemoveHeadOfWaveBufferList();
         LeaveCriticalSection(&gReadMutex);
      }
      else
         Sleep(5); /*else sleep for 5 ms*/
   }/*End of while loop*/
   ooCloseMic(ghWaveIn);
   gXmitThrdHdl = 0;
   ExitThread(0);
   OOLOG2(1, "EndOf:G721 TransmitMicThread");
   return 0;
}
/*Added by Karl on 2004-11-23 above */

#endif
#ifndef _WIN32
/* Thread function to read data from microphone and transmit it
   as rtp packets.
*/
static int ooTransmitMicThreadFuncLnx()
{
   unsigned char sendBuf[252];
   short buffer[OORTPPACKETDATASIZE];
   int marker = 1; 
   int i;
   int bytesRead, ret;
   OOLOG2(1, "StartOf:TransmitMicThread");
   
   gXmitMicLoop = 1;
   while(1)
   {
      if(!gXmitMicLoop)
         break;
      memset(sendBuf, 0, 252);
      /* RTP version = 2, padding = 0, extension = 0, CSRC = 0 */
      sendBuf[0] = 0x80; 
      /* RTP Payload type PCM ulaw Need to use #define */
      sendBuf[1] = 0x00; 
      if(marker)
      {
         sendBuf[1] |= 0x80; /* Set marker bit for first packet */
         marker = 0;
      }
      /*packet sequence number*/
      *((short *)(sendBuf + 2)) = ooHTONS((short)gXmitChannel.seqNo);
      /*packet timestamp*/
      *((long  *)(sendBuf + 4)) = ooHTONL((long)gXmitChannel.timestamp);
      /*packet ssrc*/
      *((long  *)(sendBuf + 8)) = ooHTONL((long)gXmitChannel.ssrc);
         
      if(gXmitChannel.seqNo == 65535)
         gXmitChannel.seqNo = 0; /* Seq num wrap around */
      else
         gXmitChannel.seqNo += 1;

      /* Next timestamp is current timestamp + play duration of the 
         current buffer
      */
      gXmitChannel.timestamp += OORTPPACKETDATASIZE;
               
      /* Convert data into g711 ulaw and copy to sendBuf */
	  bytesRead = ooGetMicAudioBuffer((unsigned char*)buffer, 
                                          OORTPPACKETDATASIZE*sizeof(short));
      for(i=0; i<(bytesRead/sizeof(short)); i++)
         sendBuf[12+i] = (unsigned char) linear2ulaw((short)buffer[i]);
 
 
      /* transmit rtp packet */
      ret = ooSocketSendTo(gXmitChannel.sock, sendBuf,
                           (bytesRead/sizeof(short)+12), 
                           gXmitChannel.ip, gXmitChannel.port);
      if(ret<0)
      {
         OOLOG2(1, "ERROR: Failed to transmit rtp packet");
         return -1;
      }
      ooSleep(5); /*sleep for 5 ms*/
   }/*End of while loop*/
   
   gXmitThrdHdl = 0;
   pthread_exit(0);
   OOLOG2(1, "EndOf:TransmitMicThread");
   return 0;
}

/* Thread function to receive RTP data and play it onto the
   speaker device.
*/

static int ooReceiveSpeakerThreadFuncLnx()
{
   int ret = 0, i, j;
   char * pcSndBuf;
   struct timeval timeout;
   short c;
   fd_set readfds;
   char buffer[1024]; 
   OOLOG2(1, "StartOf:ReceiveSpeakerThread");
   gRecvPlayLoop = 1; /* start recv loop */
   while(1)
   {
      if(!gRecvPlayLoop)
      {
         OOLOG2(1, "Exiting from RecvPlay loop ");
         break;
      }
      FD_ZERO(&readfds);
      FD_SET(gRecvChannel.sock, &readfds);
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      /* Check whether there is data for read */
      ret = ooSocketSelect(gRecvChannel.sock+1, &readfds, 0, 
                           0, &timeout);

      if(FD_ISSET(gRecvChannel.sock, &readfds))
      {
         pcSndBuf = (char*) malloc(1024);
         if(pcSndBuf == 0)
         {
            OOLOG2(1, "ERROR: Memalloc for playback buffer failed");
         }
         else{
            ret = ooSocketRecvFrom (gRecvChannel.sock, buffer, 
                                    1024, 0, 0);
                        
            /* We have a RTP packet in buffer. Assume that data always begins 
               from 12th octet, since standard RTP header length is 12.
               Convert G711 data to 16 bit PCM.
            */
            j = 0;
            for( i =12; i < ret; i++)
            {                           
               c = (short)ulaw2linear((unsigned char)(buffer[i]));
               pcSndBuf[j++]= (unsigned char) ((c>>8) & 0xff);
               pcSndBuf[j++] = (unsigned char) (c & 0xff);
            }
            /* Play the data buffer onto the speaker device*/
            ooPlayAudioBuffer(pcSndBuf, j);
            pcSndBuf =0;
         }
      }
   }
   
   gRecvThrdHdl = 0;
   pthread_exit(0);   
   OOLOG2(1, "EndOf:ReceiveSpeakerThread");
   return 0;
}


/* Read the wave file and transmit wave file data
   as rtp packets on RTP transmit channel.
*/
static int ooTransmitFileThreadFuncLnx()
{
   int DataTxed=0;
   long audioDataSize;
   int ret = 0;
   char databuf[480];
   short *tempBuf;
   unsigned char sendBuf[252]; /* additional 12 bytes for RTP header */
   int marker = 1; /* Only first packet has marker bit set */
   int i;
   OOLOG2(1, "StartOf:TransmitFileThread");
   
   gXmitFileLoop = 1;
   while(1)
   {
      if(!gXmitFileLoop)
         break;
      /* Number of bytes read is returned and stored in audioDataSize */

      audioDataSize = ooReadWaveFileData(databuf, 480);

      if(audioDataSize>0) /* If any data is read */
      {
         DataTxed += audioDataSize;
         /* RTP version = 2, padding = 0, extension = 0, CSRC = 0 */
         sendBuf[0] = 0x80; 
         sendBuf[1] = 0x00; /* RTP Payload type PCM ulaw Need to use #define */
         if(marker)
         {
            sendBuf[1] |= 0x80; /* Set marker bit for first packet */
            marker = 0;
         }
         /*packet sequence number*/
         *((short *)(sendBuf + 2)) = ooHTONS((short)gXmitChannel.seqNo);
         /*packet timestamp*/
         *((long  *)(sendBuf + 4)) = ooHTONL((long)gXmitChannel.timestamp);
         /*packet ssrc*/
         *((long  *)(sendBuf + 8)) = ooHTONL((long)gXmitChannel.ssrc);
         
         if(gXmitChannel.seqNo == 65535)
            gXmitChannel.seqNo = 0; /* Seq num wrap around */
         else
            gXmitChannel.seqNo += 1;

         /* Next timestamp is current timestamp + play duration of the 
            current buffer.
         */
         gXmitChannel.timestamp += 480;
         tempBuf = (short*) databuf;
         /* Copy PCM audio data into sendBuf as ulaw audio data*/
         for(i=0; i<(audioDataSize/2); i++)
         {
            sendBuf[12+i] = (unsigned char) linear2ulaw((int)*(tempBuf+i));
         }
         /* transmit rtp packet */
         ret = ooSocketSendTo(gXmitChannel.sock, sendBuf, 
                     (audioDataSize/2+12), gXmitChannel.ip, gXmitChannel.port);
         if(ret<0)
         {
            OOLOG2(1, "ERROR: Failed to transmit rtp packet");
            return -1;
         }
         ooSleep(2);/* Just slows down the transmit rate a bit */
      }
      else{
         gXmitFileLoop = 0;
         OOLOG2(1, "End of file transmission");
      }
   }
   /* Close the wave file */
   ret = ooCloseWaveFile();
   if(ret < 0)
   {
      OOLOG2(1, "ERROR: Failed to close the open wave file");
      return -1;
   }
   gXmitThrdHdl = 0;
   pthread_exit(0);   
   OOLOG2(1, "EndOf:TransmitFileThread");
   return 0;
}

#endif
