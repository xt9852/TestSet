/********************************************************************
	created:	2005/01/14
	filename: 	H323MsgHandler.h
	author:		Tony Tan
	
	purpose:	object used to handle all of H323 messages include 
				Ras,Q931,H245 message etc.
*********************************************************************/


#if !defined(AFX_H323MSGHANDLER_H__39E3B135_BDCB_41FD_82CA_0CA7562A1404__INCLUDED_)
#define AFX_H323MSGHANDLER_H__39E3B135_BDCB_41FD_82CA_0CA7562A1404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "H323\Base\ootypes.h"
#include "H323\Base\ooRas.h"
#include "H323\Base\ooh245.h"
#include "DLG\DLG_H323.h"

class CH323MsgHandler  
{
public:
	CH323MsgHandler();
	virtual ~CH323MsgHandler();

	static HANDLE hRespondEvent;
	static BOOL bAcceptCall;
	static DWORD WINAPI MsgMonitorProc(LPVOID lpParameter);
	static int OnReceivedRasMsg(void *msg);
	static int OnReceivedH2250Msg(void *msg);
	static int OnReceivedH245Msg(void *msg);

private:
	//ras message
	static int OnRecvRasRRQ(RasMessage *msg);
	static int OnRecvRasRCF(RasMessage *msg);
	static int OnRecvRasRRJ(RasMessage *msg);
	static int OnRecvRasURQ(RasMessage *msg);
	static int OnRecvRasUCF(RasMessage *msg);
	static int OnRecvRasURJ(RasMessage *msg);
	static int OnRecvRasARQ(RasMessage *msg);
	static int OnRecvRasACF(RasMessage *msg);
	static int OnRecvRasARJ(RasMessage *msg);
	static int OnRecvRasDRQ(RasMessage *msg);
	static int OnRecvRasDCF(RasMessage *msg);
	static int OnRecvRasDRJ(RasMessage *msg);
	//..待续

	//q931 message
	static int OnRecvQ931SetupMsg(Q931Message *msg);
	static int OnRecvQ931CallProceedingMsg(Q931Message *msg);
	static int OnRecvQ931AlertingMsg(Q931Message* msg);
	static int OnRecvQ931ConnectMsg(Q931Message *msg);
	static int OnRecvQ931InformationMsg(Q931Message *msg);
	static int OnRecvQ931ReleaseCompleteMsg(Q931Message *msg);
	static int OnRecvQ931FacilityMsg(Q931Message *msg);
	static int OnRecvQ931ProgressMsg(Q931Message *msg);
	static int OnRecvQ931StatusMsg(Q931Message *msg);
	static int OnRecvQ931StatusEnquiryMsg(Q931Message *msg);
	static int OnRecvQ931SetupAckMsg(Q931Message *msg);
	static int OnRecvQ931NotifyMsg(Q931Message *msg);
	static int OnReceivedSignalConnect(Q931Message *q931Msg);

	//
	static int OnReceivedTerminalCapabilitySet(void * pmsg);
	/*本函数协商接收音频能力*/
    static int OnNegotiateCapability(H245TerminalCapabilitySet* termCap);
private:
	static struct ooAppContext *context;
	static CDlg_H323 *MainWnd;
};

#endif // !defined(AFX_H323MSGHANDLER_H__39E3B135_BDCB_41FD_82CA_0CA7562A1404__INCLUDED_)
