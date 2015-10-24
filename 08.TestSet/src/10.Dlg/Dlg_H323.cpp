// H323Dlg.cpp : implementation file
//
#include "stdafx.h"
#include "Dlg_H323.h"
#include "H323\CallAdvSetupDlg.h"
#include "H323\H323MsgHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "H323\Base\ooh245.h"
#include "H323\Base\ooRas.h"
#include "H323\Base\ooPorts.h"

struct ooAppContext *myContext = NULL;
static ASN1OBJID gRasProtocolID = {
   6, { 0, 0, 8, 2250, 0, 2 }
};

static ASN1OBJID gProtocolID = {
   6, { 0, 0, 8, 2250, 0, 4 }
};


/////////////////////////////////////////////////////////////////////////////
// CH323Dlg dialog

CDlg_H323::CDlg_H323(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_H323::IDD, pParent)
{
	//{{AFX_DATA_INIT(CH323Dlg)
	m_strCalled = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAIN_ICON_MAINFRAME);
	m_bAutoAnswer = FALSE;
	m_bDoNotBother = FALSE;
	m_pCallingDlg = NULL;
	m_pInCallDlg = NULL;

	//tony add 2004/11/24
	m_bViaGK = FALSE;
	m_bName = FALSE;
	m_bNumber = FALSE;
	m_bRegistered = FALSE;
	m_bViaGW = FALSE;
	m_strGatekeeper = "";
	m_strName = "";
	m_strNumber = "";
	m_strGateway = "";
}

CDlg_H323::~CDlg_H323()
{
	if(m_pCallingDlg)
		delete m_pCallingDlg;
	if(m_pInCallDlg)
		delete m_pInCallDlg;
}

void CDlg_H323::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CH323Dlg)
	DDX_Control(pDX, IDC_H323_PARTIES, m_cParties);
	DDX_CBString(pDX, IDC_H323_CALLED_ADDR, m_strCalled);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_H323, CDialog)
	//{{AFX_MSG_MAP(CH323Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_H323_MAKECALL, OnMakecall)
	ON_BN_CLICKED(IDC_H323_HANGUP, OnHangup)	
	ON_BN_CLICKED(IDC_H323_SET, OnCallAdvanceSetup)
	ON_BN_CLICKED(IDC_H323_DONOT_BOTHER, OnDonotBother)
	ON_BN_CLICKED(IDC_H323_AUTO_ANSWER, OnAutoAnswer)
	
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_INCOMINGCALL,OnIncomingCall)
	ON_MESSAGE(WM_USER_RECVRCF,OnRecvRCF)
	ON_MESSAGE(WM_USER_RECVACF,OnRecvACF)
	ON_MESSAGE(WM_USER_RECVCONNECT,OnRecvConnect)
	ON_MESSAGE(WM_USER_SENDCONNECT,OnSendConnect)
	ON_MESSAGE(WM_USER_RECVReleaseComplete,OnRecvReleaseComplete)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CH323Dlg message handlers

BOOL CDlg_H323::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(ooInitialize(&myContext,"H323.log",&HandleCommand) != OO_OK)
	{
		AfxMessageBox("\nH323Ep\tError in stack initialization");
		return FALSE;
	}
	// Setup TCP port range
	if(ooSetTCPPorts(myContext, 3020, 3060)!= OO_OK)
	  OOTRACEWARN2(myContext, "Warn: Error in setting TCP port range -"
							  " using default");
	// Setup UDP port range
	if(ooSetUDPPorts(myContext, 3080, 4020) != OO_OK)
	  OOTRACEWARN2(myContext, "Warn: Error in setting UDP port range -"
							  " using default");
	// Setup RTP port range
	if(ooSetRTPPorts(myContext, 4040, 4080) != OO_OK)
	  OOTRACEWARN2(myContext, "Warn: Error in setting RTP port range -"
							  " using default");

	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.pszText = "名称";
	col.cx = 200;
	m_cParties.InsertColumn(0,&col);
	m_Imgs.Create(16,16,ILC_COLOR4,1,2);
	CBitmap bmp;
	bmp.LoadBitmap(IDR_MAIN_ICON_MAINFRAME);
	m_Imgs.Add(&bmp,RGB(0,0,0));
	m_cParties.SetImageList(&m_Imgs,LVSIL_SMALL);

	Loadini();

	if(m_bViaGK)
	{
		myContext->callByGK = TRUE;	
		RegistrationRequest();
	}

	//Listen for incoming call
	Listen();
	
	//create monitoring thread to monitor 
	m_hMonitorThread = CreateThread(0,0,&CH323MsgHandler::MsgMonitorProc,this,/*CREATE_SUSPENDED*/0,0);
	if(!m_hMonitorThread)
	{
		AfxMessageBox("H323消息监控线程创建失败");
		return FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlg_H323::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlg_H323::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CDlg_H323::Listen()
{
	int ret;
	char localip[40];
	struct ooConnectionEP connectionEP;
	ooGetLocalIPAddress(localip); /* Get local ip address to listen on */
	strcpy(connectionEP.ipaddress, localip);
	connectionEP.port = 1720;
	ret=ooCreateH2250Channel(myContext, &CH323MsgHandler::OnReceivedH2250Msg,
								connectionEP, OORECEIVER);
	return ASN_OK;
}

void CDlg_H323::OnMakecall() 
{
	UpdateData(TRUE);
	m_nDestStrType = WhatTypeIsDestStr(m_strCalled);

	//added by tony below [2005.1.17]
	while(myContext->h225Channel != 0)
		Sleep(100);
	//added by tony above [2005.1.17]

	if(m_bViaGK)	//若使用网守呼叫，则首先判断该终端是否已经成功注册
	{
		AdmissionRequest();
		m_bAsCaller = TRUE;
	}
	else		//直接呼叫
	{
		if(m_nDestStrType != 0)
		{
			AfxMessageBox("输入的被叫信息不正确，请正确输入对方的IP地址");
			return;
		}

		PopupCallingDlg();
		CallSetup();	//发送呼叫建立消息
	}
}

void CDlg_H323::CallSetup()
{
	struct ooConnectionEP connectionEP;
	H225Setup_UUIE setup;
	H225TransportAddress_ipAddress destCallSignalIpAddress;
	int addr_part1, addr_part2, addr_part3, addr_part4;
	char hexip[20];
	H225TransportAddress_ipAddress srcCallSignalIpAddress;
	char localip[40];
	int i =0, ret;
	H225H323_UserInformation userInfo;
	H225AliasAddress *alias;
	OOCTXT *pctxt;
	char destip[20];

	if(m_bViaGK)	//通过网守呼叫
	{
		strcpy(destip,myContext->remoteIP);
		strcpy(connectionEP.ipaddress,myContext->remoteIP);
		connectionEP.port = 1720;
	}
	else			//直接呼叫
	{
		if(m_nDestStrType != 0)
		{
			AfxMessageBox("无效的呼叫地址，请重新输入");
			return;
		}
		UpdateData(TRUE);
		strcpy(destip,LPCTSTR(m_strCalled));
		strcpy(connectionEP.ipaddress,LPCTSTR(m_strCalled));
		connectionEP.port = 1720;
	}

	/* This function will create a local socket and make a connect request
	  to the destination IP at port 1720 */
	ret = ooCreateH2250Channel(myContext, &CH323MsgHandler::OnReceivedH2250Msg, 
						  connectionEP, OOTRANSMITTER);

	if(ret !=OO_OK)
	{
		CloseCallingDlg();
		AfxMessageBox("您呼叫的用户无法接受呼叫");
		return;
	}

	/*Create outgoing Q931 message. An outgoing Q931 setup message will be 
	 created for the context.
	*/ 
	ret = ooCreateQ931Message(myContext, Q931SetupMsg);
	if(ret != OO_OK)
	{
	    OOTRACEERR2(myContext, "ERROR: Creating Q931 setup message...");
		CloseCallingDlg();
		return;
	}

	/*Populate the setup UUIE to be passed into the outgoing setup message*/   
	memset (&setup, 0, sizeof(setup));
	setup.protocolIdentifier = gProtocolID;
	setup.sourceInfo.m.vendorPresent=TRUE;
	/* Populate the vendor information */
	setup.sourceInfo.vendor.vendor.t35CountryCode = 9;
	setup.sourceInfo.vendor.vendor.t35Extension = 0;
	setup.sourceInfo.vendor.vendor.manufacturerCode=61;
	setup.sourceInfo.vendor.productId.numocts = ASN1MIN(strlen("GiantVoip"), 
							   sizeof(setup.sourceInfo.vendor.productId.data));
	strncpy((char*)setup.sourceInfo.vendor.productId.data, "GiantVoip", 
		   setup.sourceInfo.vendor.productId.numocts);

  
	setup.sourceInfo.vendor.versionId.numocts = ASN1MIN(strlen("Version 1.0"), 
							   sizeof(setup.sourceInfo.vendor.versionId.data));
	strncpy((char*)setup.sourceInfo.vendor.versionId.data, "Version 1.0", 
		   setup.sourceInfo.vendor.versionId.numocts);

	setup.sourceInfo.vendor.m.productIdPresent=TRUE;
	setup.sourceInfo.vendor.m.versionIdPresent=TRUE;
	setup.sourceInfo.mc = FALSE;
	setup.sourceInfo.m.terminalPresent = TRUE;
	setup.sourceInfo.terminal.m.nonStandardDataPresent = FALSE;
	setup.sourceInfo.undefinedNode = FALSE;
	setup.activeMC=FALSE;

	pctxt = myContext->outgoing->pctxt;
	if(m_bViaGK)
	{
		//destination address(alias)
	   dListInit(&(setup.destinationAddress));
	   if(m_nDestStrType == 1)	//号码
	   {
		   alias = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
		   memset(alias,0,sizeof(H225AliasAddress));
		   alias->t = T_H225AliasAddress_dialedDigits;
		   alias->u.dialedDigits = LPCTSTR(m_strCalled);
		   dListAppend(pctxt,&(setup.destinationAddress),alias);
	   }
	   else/* if(m_nDestStrType == 2)*/	//账号
	   {
		   alias = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
		   memset(alias,0,sizeof(H225AliasAddress));
		   alias->t = T_H225AliasAddress_h323_ID;
		   Asn116BitCharString *str = &(alias->u.h323_ID);
		   int nCount = m_strCalled.GetLength();
		   str->nchars = nCount;
		   str->data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,sizeof(ASN116BITCHAR) * nCount);
		   memset(str->data,0,sizeof(ASN116BITCHAR) * nCount);
		   for(int i = 0; i < nCount; i++)	//这里需要进一步转换成16进制吗？
			   str->data[i] = (ASN116BITCHAR)m_strCalled.GetAt(i);
		   dListAppend(pctxt,&(setup.destinationAddress),alias);
	   }
	   setup.m.destinationAddressPresent = TRUE;

	   //source address (alias)
	   dListInit(&(setup.sourceAddress));
	   if(m_bNumber)	//号码
	   {
		   alias = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
		   memset(alias,0,sizeof(H225AliasAddress));
		   alias->t = T_H225AliasAddress_dialedDigits;
		   alias->u.dialedDigits = LPCTSTR(m_strNumber);
		   dListAppend(pctxt,&(setup.sourceAddress),alias);
	   }
	   if(m_bName)	//账号
	   {
		   alias = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
		   memset(alias,0,sizeof(H225AliasAddress));
		   alias->t = T_H225AliasAddress_h323_ID;
		   Asn116BitCharString *str = &(alias->u.h323_ID);
		   int nCount = m_strName.GetLength();
		   str->nchars = nCount;
		   str->data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,sizeof(ASN116BITCHAR) * nCount);
		   memset(str->data,0,sizeof(ASN116BITCHAR) * nCount);
		   for(int i = 0; i < nCount; i++)	//这里需要进一步转换成16进制吗？
			   str->data[i] = (ASN116BITCHAR)m_strName.GetAt(i);
		   dListAppend(pctxt,&(setup.sourceAddress),alias);
	   }
	   setup.m.sourceAddressPresent = TRUE;
	}
	else
	{
		/* Populate the destination Call Signal Address */
		setup.destCallSignalAddress.t=T_H225TransportAddress_ipAddress;

		sscanf(destip, "%d.%d.%d.%d", &addr_part1, &addr_part2, &addr_part3, 
									 &addr_part4);
		sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, addr_part3, 
									 addr_part4);
		sscanf(hexip, "%x %x %x %x", &destCallSignalIpAddress.ip.data[0], 
									&destCallSignalIpAddress.ip.data[1],
									&destCallSignalIpAddress.ip.data[2], 
									&destCallSignalIpAddress.ip.data[3]);

		destCallSignalIpAddress.ip.numocts=4;
		destCallSignalIpAddress.port=1720;
		setup.destCallSignalAddress.u.ipAddress = &destCallSignalIpAddress;
		setup.m.destCallSignalAddressPresent=TRUE;

		/* Populate the source Call Signal Address */
		setup.sourceCallSignalAddress.t=T_H225TransportAddress_ipAddress;
		ooGetLocalIPAddress(localip);
		sscanf(localip, "%d.%d.%d.%d", &addr_part1, &addr_part2, &addr_part3,
									  &addr_part4);
		sprintf(hexip, "%x %x %x %x", addr_part1, addr_part2, addr_part3, 
									 addr_part4);
		sscanf(hexip, "%x %x %x %x", &srcCallSignalIpAddress.ip.data[0], 
									&srcCallSignalIpAddress.ip.data[1],
									&srcCallSignalIpAddress.ip.data[2], 
									&srcCallSignalIpAddress.ip.data[3]);

		srcCallSignalIpAddress.ip.numocts=4;
		srcCallSignalIpAddress.port=ooGetH225ChannelPort(myContext);
		setup.sourceCallSignalAddress.u.ipAddress = &srcCallSignalIpAddress;
		setup.m.sourceCallSignalAddressPresent=TRUE;	
	}

	/* No fast start */
	setup.m.fastStartPresent = FALSE;
 
	//modified by tony below 2004.12.13
	/*setup.conferenceID.numocts = 16;
	for (i = 0; i < 16; i++)
	  setup.conferenceID.data[i] = i + 1;*/
	if(myContext->conferenceId.numocts != 16 )
	{
		ooGenerateGUID(myContext->conferenceId.data);
		myContext->conferenceId.numocts = 16;
	}
	setup.conferenceID.numocts = myContext->conferenceId.numocts;
	memcpy(setup.conferenceID.data,myContext->conferenceId.data,myContext->conferenceId.numocts);
	//modified by tony above 2004.12.13

	setup.conferenceGoal.t = T_H225Setup_UUIE_conferenceGoal_create;
	/* H.225 point to point call */
	setup.callType.t = T_H225CallType_pointToPoint;

	/* Populate optional fields */
	setup.m.callIdentifierPresent = TRUE;
	setup.m.mediaWaitForConnectPresent = TRUE;
	setup.m.canOverlapSendPresent = TRUE;

	//modified by tony below 2004.12.13
	/* Dummy call identifier. Need to add a function in stack to generate
	  unique call id */
	/*setup.callIdentifier.guid.numocts = 16;
	for (i = 0; i < 16; i++)
	   setup.callIdentifier.guid.data[i] = i + 1;*/
	if(myContext->callIdentifier.guid.numocts != 16)
	{
		ooGenerateGUID(myContext->callIdentifier.guid.data);
		myContext->callIdentifier.guid.numocts = 16;
	}
	setup.callIdentifier.guid.numocts = myContext->callIdentifier.guid.numocts;
	memcpy(setup.callIdentifier.guid.data,myContext->callIdentifier.guid.data,myContext->callIdentifier.guid.numocts);

	/*Since currently call ID is generated outside stack, application needs to store 
	it in the context field for stack to use.*/
	//memcpy(myContext->callIdentifier.guid.data, setup.callIdentifier.guid.data,16);
	//myContext->callIdentifier.guid.numocts = setup.callIdentifier.guid.numocts;
	//modified by tony above 2004.12.13
	setup.mediaWaitForConnect = FALSE;
	setup.canOverlapSend = FALSE;
	
	/* Populate the userInfo structure with the setup UUIE */ 
	memset (&userInfo, 0, sizeof(userInfo));
	userInfo.h323_uu_pdu.h323_message_body.t = 
		 T_H225H323_UU_PDU_h323_message_body_setup;
	userInfo.h323_uu_pdu.h323_message_body.u.setup = &setup;

	/* Add userinfo to the outgoing q931 setup message */   
	if(ooAddUserUserIE(myContext, &userInfo) != OO_OK)
	{
	  OOTRACEERR2(myContext, "Error: Failed to add UUIE to Q931 message");
	  return;
	}
	else
	{
	  /* This queues the outgoing message into the outgoing message queue.
		 The message will be sent whenever the corresponing channel is ready
		 for send, in other words corresponing socket is available for write.
	  */
 	  OOTRACEINFO2(myContext, "Sending H.225 setup message");
	  ooSendH225Msg(myContext);
	  SetTimer(2006,30000,NULL);	//启动10秒钟定时器，若在此期间无法收到Connect消息则退出
	}
}

void CDlg_H323::RegistrationRequest()
{
	int ret;
	H225RegistrationRequest *regRequest;
	OOCTXT *pctxt;
	H225TransportAddress *CallSignalAddress,*RasAddress;
	H225TransportAddress_ipAddress *IpAddr1,*IpAddr2;
	int addr_seg1,addr_seg2,addr_seg3,addr_seg4;
	char hexIp[20];
	H225AliasAddress *alias1,*alias2;
	int bindPort;

	ret = ooSocketCreateUDP(&myContext->RASChannel);
	if(ret != ASN_OK)
	{
	  OOTRACEERR2(myContext, "ERROR: Creating RAS channel failed...");
	  return;
	}
	
	bindPort = ooBindPort(myContext,OOUDP,myContext->RASChannel);
	if(bindPort == OO_FAILED)
	{
	  OOTRACEERR2(myContext, "ERROR: Bind port failed...");
	  return;
	}

	myContext->RASCallback = &CH323MsgHandler::OnReceivedRasMsg;
	strncpy(myContext->GkIp,LPCTSTR(m_strGatekeeper),20);
	myContext->RasChanPort = 1719;

	//build and send RAS registration message
   ret = ooCreateRasMessage(myContext,T_H225RasMessage_registrationRequest);
   if(ret == OO_FAILED)
   {
      OOTRACEERR2(myContext,"Error:Failed to create Ras message");
      return;
   }

   myContext->outgoingRas->msgType = OORegistrationRequest;
   regRequest = myContext->outgoingRas->RasMsg.u.registrationRequest;
   pctxt = myContext->outgoingRas->pctxt;
   regRequest->requestSeqNum = (myContext->seqNumber++) % 65536;
   regRequest->protocolIdentifier = gRasProtocolID;
   regRequest->discoveryComplete = FALSE;

   CallSignalAddress = (H225TransportAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress));
   memset(CallSignalAddress,0,sizeof(H225TransportAddress));
   CallSignalAddress->t = T_H225TransportAddress_ipAddress;
   IpAddr1 = (H225TransportAddress_ipAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress_ipAddress));
   memset(IpAddr1,0,sizeof(H225TransportAddress_ipAddress));
   ooGetLocalIPAddress(myContext->localIP);
   sscanf(myContext->localIP,"%d.%d.%d.%d",&addr_seg1,&addr_seg2,&addr_seg3,&addr_seg4);
   sprintf(hexIp,"%x %x %x %x",addr_seg1,addr_seg2,addr_seg3,addr_seg4);
   sscanf(hexIp,"%x %x %x %x",&IpAddr1->ip.data[0],&IpAddr1->ip.data[1],
	   &IpAddr1->ip.data[2],&IpAddr1->ip.data[3]);
   IpAddr1->ip.numocts = 4;
   IpAddr1->port = 1720;
   CallSignalAddress->u.ipAddress = IpAddr1;
   dListInit(&(regRequest->callSignalAddress));
   dListAppend(pctxt,&(regRequest->callSignalAddress),CallSignalAddress);
	
   RasAddress = (H225TransportAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress));
   memset(RasAddress,0,sizeof(H225TransportAddress));
   RasAddress->t = T_H225TransportAddress_ipAddress;
   IpAddr2 = (H225TransportAddress_ipAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress_ipAddress));
   memset(IpAddr2,0,sizeof(H225TransportAddress_ipAddress));
   sscanf(/*myContext->GkIp*/myContext->localIP,"%d.%d.%d.%d",&addr_seg1,&addr_seg2,&addr_seg3,&addr_seg4);
   sprintf(hexIp,"%x %x %x %x",addr_seg1,addr_seg2,addr_seg3,addr_seg4);
   sscanf(hexIp,"%x %x %x %x",&IpAddr2->ip.data[0],&IpAddr2->ip.data[1],
	   &IpAddr2->ip.data[2],&IpAddr2->ip.data[3]);
   IpAddr2->ip.numocts = 4;
   IpAddr2->port = bindPort;
   RasAddress->u.ipAddress = IpAddr2;
   dListInit(&(regRequest->rasAddress));
   dListAppend(pctxt,&(regRequest->rasAddress),RasAddress);	

   //terminal type
   regRequest->terminalType.mc = FALSE;
   regRequest->terminalType.undefinedNode = FALSE;
   regRequest->terminalType.terminal.m.nonStandardDataPresent = FALSE;
   regRequest->terminalType.m.terminalPresent = TRUE;
   
   //terminal alias
	if(m_bName || m_bNumber)
	{
		regRequest->m.terminalAliasPresent = 1;
		dListInit(&(regRequest->terminalAlias));
	}
	else
		regRequest->m.terminalAliasPresent = 0;
	
   if(m_bName)
   {
	   alias1 = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
	   memset(alias1,0,sizeof(H225AliasAddress));
	   alias1->t = T_H225AliasAddress_h323_ID;
	   Asn116BitCharString *str = &(alias1->u.h323_ID);
	   int nCount = m_strName.GetLength();
	   str->nchars = nCount;
	   str->data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,sizeof(ASN116BITCHAR) * nCount);
	   memset(str->data,0,sizeof(ASN116BITCHAR) * nCount);
	   for(int i = 0; i < nCount; i++)	//这里需要进一步转换成16进制吗？
		   str->data[i] = (ASN116BITCHAR)m_strName.GetAt(i);
	   dListAppend(pctxt,&(regRequest->terminalAlias),alias1);
   }
   if(m_bNumber)
   {
	   alias2 = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
	   memset(alias2,0,sizeof(H225AliasAddress));
	   alias2->t = T_H225AliasAddress_dialedDigits;
	   alias2->u.dialedDigits = LPCTSTR(m_strNumber);
	   dListAppend(pctxt,&(regRequest->terminalAlias),alias2);
   }

    //endpoint Vendor
	regRequest->endpointVendor.vendor.t35CountryCode = 9;
	regRequest->endpointVendor.vendor.t35Extension = 0;
	regRequest->endpointVendor.vendor.manufacturerCode= 61;
	regRequest->endpointVendor.productId.numocts = ASN1MIN(strlen("GiantVoip"), 
							   sizeof(regRequest->endpointVendor.productId.data));
	strncpy((char*)regRequest->endpointVendor.productId.data, "GiantVoip", 
		   regRequest->endpointVendor.productId.numocts);


	regRequest->endpointVendor.versionId.numocts = ASN1MIN(strlen("Version 1.0"), 
							   sizeof(regRequest->endpointVendor.versionId.data));
	strncpy((char*)regRequest->endpointVendor.versionId.data, "Version 1.0", 
		   regRequest->endpointVendor.versionId.numocts);

	regRequest->endpointVendor.m.productIdPresent=TRUE;
	regRequest->endpointVendor.m.versionIdPresent=TRUE;

	regRequest->keepAlive = FALSE;
	regRequest->willSupplyUUIEs = FALSE;
	regRequest->maintainConnection = FALSE;

    ooSendRasMsg(myContext);
    OOTRACEINFO2(myContext, "Sending registration request message");
}

void CDlg_H323::UnregistrationRequest()
{
	H225UnregistrationRequest *UnregRequest;
	OOCTXT *pctxt;
	H225TransportAddress *CallSignalAddress;
	H225TransportAddress_ipAddress *IpAddr1;
	int addr_seg1,addr_seg2,addr_seg3,addr_seg4;
	char hexIp[20];
	H225AliasAddress *alias1,*alias2;
	int ret;
	int iCharNum;

	ret = ooCreateRasMessage(myContext,T_H225RasMessage_unregistrationRequest);
	if(ret == OO_FAILED)
	{
		OOTRACEERR2(myContext,"Error:Failed to create Ras message");
		return;
	}
	myContext->outgoingRas->msgType = OOUnregistrationRequest;
	UnregRequest = myContext->outgoingRas->RasMsg.u.unregistrationRequest;
	pctxt = myContext->outgoingRas->pctxt;
	
	//requestSeqNum
	UnregRequest->requestSeqNum = (myContext->seqNumber++) % 65536;

	//CallSignalAddress
	CallSignalAddress = (H225TransportAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress));
	memset(CallSignalAddress,0,sizeof(H225TransportAddress));
	CallSignalAddress->t = T_H225TransportAddress_ipAddress;
	IpAddr1 = (H225TransportAddress_ipAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress_ipAddress));
	memset(IpAddr1,0,sizeof(H225TransportAddress_ipAddress));
	sscanf(myContext->localIP,"%d.%d.%d.%d",&addr_seg1,&addr_seg2,&addr_seg3,&addr_seg4);
	sprintf(hexIp,"%x %x %x %x",addr_seg1,addr_seg2,addr_seg3,addr_seg4);
	sscanf(hexIp,"%x %x %x %x",&IpAddr1->ip.data[0],&IpAddr1->ip.data[1],
	   &IpAddr1->ip.data[2],&IpAddr1->ip.data[3]);
	IpAddr1->ip.numocts = 4;
	IpAddr1->port = 1720;
	CallSignalAddress->u.ipAddress = IpAddr1;
	dListInit(&(UnregRequest->callSignalAddress));
	dListAppend(pctxt,&(UnregRequest->callSignalAddress),CallSignalAddress);	

	//endpointAlias
	if(m_bName || m_bNumber)
	{
		UnregRequest->m.endpointAliasPresent = 1;
		dListInit(&(UnregRequest->endpointAlias));
	}
	else
		UnregRequest->m.endpointAliasPresent = 0;
	
	if(m_bName)
	{
	   alias1 = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
	   memset(alias1,0,sizeof(H225AliasAddress));
	   alias1->t = T_H225AliasAddress_h323_ID;
	   Asn116BitCharString *str = &(alias1->u.h323_ID);
	   int nCount = m_strName.GetLength();
	   str->nchars = nCount;
	   str->data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,sizeof(ASN116BITCHAR) * nCount);
	   memset(str->data,0,sizeof(ASN116BITCHAR) * nCount);
	   for(int i = 0; i < nCount; i++)
		   str->data[i] = (ASN116BITCHAR)m_strName.GetAt(i);
	   dListAppend(pctxt,&(UnregRequest->endpointAlias),alias1);
	}
	if(m_bNumber)
	{
	   alias2 = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
	   memset(alias2,0,sizeof(H225AliasAddress));
	   alias2->t = T_H225AliasAddress_dialedDigits;
	   alias2->u.dialedDigits = LPCTSTR(m_strNumber);
	   dListAppend(pctxt,&(UnregRequest->endpointAlias),alias2);
	}	

	//endpointIdentifier
	UnregRequest->m.endpointIdentifierPresent = TRUE;
	iCharNum = UnregRequest->endpointIdentifier.nchars = myContext->epIdentifier.nchars;
	UnregRequest->endpointIdentifier.data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,iCharNum * sizeof(ASN116BITCHAR));
	memcpy(UnregRequest->endpointIdentifier.data,myContext->epIdentifier.data,iCharNum * sizeof(ASN116BITCHAR));

	ooSendRasMsg(myContext);
	OOTRACEINFO2(myContext, "Sending registration request message");	
}

void CDlg_H323::AdmissionRequest()
{
	H225AdmissionRequest *admRequest;
	OOCTXT *pctxt;
	H225TransportAddress_ipAddress *IpAddr;
	int addr_seg1,addr_seg2,addr_seg3,addr_seg4;
	char hexIp[20];
	H225AliasAddress *alias,*Alias1,*Alias2;
	int ret;
	int nCharNum;

	//build and send RAS registration message
	ret = ooCreateRasMessage(myContext,T_H225RasMessage_admissionRequest);
	if(ret == OO_FAILED)
	{
	  OOTRACEERR2(myContext,"Error:Failed to create Ras message");
	  return;
	}
	myContext->outgoingRas->msgType = OOAdmissionRequest;

	pctxt = myContext->outgoingRas->pctxt;
	admRequest = myContext->outgoingRas->RasMsg.u.admissionRequest;
	admRequest->requestSeqNum = (myContext->seqNumber++) % 65536;
	admRequest->callType.t = T_H225CallType_pointToPoint;
	
	//endpoint identifier
	nCharNum = admRequest->endpointIdentifier.nchars = myContext->epIdentifier.nchars;
	admRequest->endpointIdentifier.data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,nCharNum * sizeof(ASN116BITCHAR));
	memcpy(admRequest->endpointIdentifier.data,myContext->epIdentifier.data,nCharNum * sizeof(ASN116BITCHAR));

	//followed is destinationInfo or destCallSignalAddress
	if(m_bAsCaller)	//作为主叫方
	{
		//dest info
		admRequest->m.destinationInfoPresent = 1;
		dListInit(&(admRequest->destinationInfo));
		alias = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
		memset(alias,0,sizeof(H225AliasAddress));
		if(m_nDestStrType == 1)	//目标字串是号码
		{
			alias->t = T_H225AliasAddress_dialedDigits;
			alias->u.dialedDigits = LPCTSTR(m_strCalled);
		}
		else	//目标字串是账户名称
		{
			alias->t = T_H225AliasAddress_h323_ID;
			int nCount = m_strCalled.GetLength();
			alias->u.h323_ID.nchars = nCount;
			alias->u.h323_ID.data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,sizeof(ASN116BITCHAR) * nCount);
			memset(alias->u.h323_ID.data,0,sizeof(ASN116BITCHAR) * nCount);
			for(int i = 0; i < nCount; i++)	//这里需要进一步转换成16进制吗？
			   alias->u.h323_ID.data[i] = (ASN116BITCHAR)m_strCalled.GetAt(i);
		}
	    dListAppend(pctxt,&(admRequest->destinationInfo),alias);
		
		//srcInfo
		dListInit(&(admRequest->srcInfo));
		if(m_bNumber)
		{
			Alias1 = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
			memset(Alias1,0,sizeof(H225AliasAddress));
			Alias1->t = T_H225AliasAddress_dialedDigits;
			Alias1->u.dialedDigits = LPCTSTR(m_strNumber);
			dListAppend(pctxt,&(admRequest->srcInfo),Alias1);
		}
		if(m_bName)
		{
			Alias2 = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
			memset(Alias2,0,sizeof(H225AliasAddress));
			Alias2->t = T_H225AliasAddress_h323_ID;
			int nCount = m_strName.GetLength();
			Alias2->u.h323_ID.data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,sizeof(ASN116BITCHAR) * nCount);
			for(int i = 0; i < nCount; i++)
				Alias2->u.h323_ID.data[i] = (ASN116BITCHAR)m_strName.GetAt(i);
			Alias2->u.h323_ID.nchars = nCount;
			dListAppend(pctxt,&(admRequest->srcInfo),Alias2);
		}

		//call reference
		myContext->callReference = ooGenerateCallReference();

		//conference ID
		ooGenerateGUID(myContext->conferenceId.data);
		myContext->conferenceId.numocts = 16;

		//callIdentifier
		ooGenerateGUID(myContext->callIdentifier.guid.data);
		myContext->callIdentifier.guid.numocts = 16;
	}
	else	//作为被叫方
	{
		//destination alias
		admRequest->m.destinationInfoPresent = 1;
		dListInit(&(admRequest->destinationInfo));
		if(m_bNumber)
		{
			Alias1 = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
			memset(Alias1,0,sizeof(H225AliasAddress));
			Alias1->t = T_H225AliasAddress_dialedDigits;
			Alias1->u.dialedDigits = LPCTSTR(m_strNumber);
			dListAppend(pctxt,&(admRequest->destinationInfo),Alias1);
		}
		if(m_bName)
		{
			Alias2 = (H225AliasAddress*)ASN1MALLOC(pctxt,sizeof(H225AliasAddress));
			memset(Alias2,0,sizeof(H225AliasAddress));
			Alias2->t = T_H225AliasAddress_h323_ID;
			int nCount = m_strName.GetLength();
			Alias2->u.h323_ID.data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,sizeof(ASN116BITCHAR) * nCount);
			for(int i = 0; i < nCount; i++)
				Alias2->u.h323_ID.data[i] = (ASN116BITCHAR)m_strName.GetAt(i);
			Alias2->u.h323_ID.nchars = nCount;
			dListAppend(pctxt,&(admRequest->destinationInfo),Alias2);
		}

		//destination signaling address
		admRequest->m.destCallSignalAddressPresent = 1;
		admRequest->destCallSignalAddress.t = T_H225TransportAddress_ipAddress;
		IpAddr = (H225TransportAddress_ipAddress*)ASN1MALLOC(pctxt,sizeof(H225TransportAddress_ipAddress));
		memset(IpAddr,0,sizeof(H225TransportAddress_ipAddress));
		sscanf(myContext->localIP,"%d.%d.%d.%d",&addr_seg1,&addr_seg2,&addr_seg3,&addr_seg4);
		sprintf(hexIp,"%x %x %x %x",addr_seg1,addr_seg2,addr_seg3,addr_seg4);
		sscanf(hexIp,"%x %x %x %x",&IpAddr->ip.data[0],&IpAddr->ip.data[1], &IpAddr->ip.data[2],
			&IpAddr->ip.data[3]);
		IpAddr->ip.numocts = 4;
		IpAddr->port = 1720;
		admRequest->destCallSignalAddress.u.ipAddress = IpAddr;
	}

	admRequest->callReferenceValue = myContext->callReference;

	admRequest->bandWidth = 1;
	myContext->callReference = ooGenerateCallReference();
	admRequest->callReferenceValue = myContext->callReference;
	
	admRequest->conferenceID.numocts = myContext->conferenceId.numocts;
	memcpy(admRequest->conferenceID.data,myContext->conferenceId.data,myContext->conferenceId.numocts);

	admRequest->activeMC = FALSE;
	admRequest->answerCall = FALSE;
	admRequest->canMapAlias = FALSE;
	admRequest->m.canMapAliasPresent = TRUE;

	admRequest->m.callIdentifierPresent = TRUE;
	admRequest->callIdentifier.guid.numocts = myContext->callIdentifier.guid.numocts;
	memcpy(admRequest->callIdentifier.guid.data,myContext->callIdentifier.guid.data,
		myContext->callIdentifier.guid.numocts);

	admRequest->willSupplyUUIEs = FALSE;
	admRequest->m.willSupplyUUIEsPresent = TRUE;

	ooSendRasMsg(myContext);
	OOTRACEINFO2(myContext, "Sending admission request message");
}

void CDlg_H323::DisengageRequest()
{
	int iCharNum;
	int ret;

	H225DisengageRequest *DisengageRequest;
	OOCTXT *pctxt;

	//build and send RAS disengageRequest message
	ret = ooCreateRasMessage(myContext,T_H225RasMessage_disengageRequest);
	if(ret == OO_FAILED)
	{
	  OOTRACEERR2(myContext,"Error:Failed to create Ras message");
	  return;
	}
	myContext->outgoingRas->msgType = OODisengageRequest;
	pctxt = myContext->outgoingRas->pctxt;
	DisengageRequest = myContext->outgoingRas->RasMsg.u.disengageRequest;
	DisengageRequest->requestSeqNum = (myContext->seqNumber++) % 65536;
	
	//endpointIdentifier
	iCharNum = DisengageRequest->endpointIdentifier.nchars = myContext->epIdentifier.nchars;
	DisengageRequest->endpointIdentifier.data = (ASN116BITCHAR*)ASN1MALLOC(pctxt,iCharNum * sizeof(ASN116BITCHAR));
	memcpy(DisengageRequest->endpointIdentifier.data,myContext->epIdentifier.data,iCharNum * sizeof(ASN116BITCHAR));

	//ConferenceID
	DisengageRequest->conferenceID.numocts = myContext->conferenceId.numocts;
	memcpy(DisengageRequest->conferenceID.data,myContext->conferenceId.data,myContext->conferenceId.numocts);
	
	//CallReferenceValue
	DisengageRequest->callReferenceValue = myContext->callReference;
	DisengageRequest->disengageReason.t = T_H225DisengageReason_normalDrop;

	//CallIdentifier
	DisengageRequest->m.callIdentifierPresent = TRUE;
	DisengageRequest->callIdentifier.guid.numocts = myContext->callIdentifier.guid.numocts;
	memcpy(DisengageRequest->callIdentifier.guid.data,myContext->callIdentifier.guid.data,
		myContext->callIdentifier.guid.numocts);

	ooSendRasMsg(myContext);
	OOTRACEINFO2(myContext, "Sending disengage request message");
}

void CDlg_H323::PopupCallingDlg()
{
	if(!m_pCallingDlg)
		m_pCallingDlg = new CCallingDlg;
	if(m_pCallingDlg->GetSafeHwnd() == NULL)
		m_pCallingDlg->Create(IDD_DLG_H323_CALLING,this);
	m_pCallingDlg->ShowWindow(SW_SHOW);
	UpdateData(TRUE);
	m_pCallingDlg->ShowTip(LPCTSTR(m_strCalled));
}

void CDlg_H323::CloseCallingDlg()
{
	if(m_pCallingDlg && m_pCallingDlg->GetSafeHwnd())
		m_pCallingDlg->PostMessage(WM_CLOSE);
}

BOOL CDlg_H323::IsAutoAnswer()
{
	return m_bAutoAnswer;
}

BOOL CDlg_H323::DoNotBother()
{
	return m_bDoNotBother;
}

void CDlg_H323::OnHangup()
{
	// TODO: Add your control notification handler code here
	ooSendEndSessionCommand(myContext);
	GetDlgItem(IDC_H323_HANGUP)->EnableWindow(FALSE);
}

int HandleCommand()
{
	return -1;
}

void CDlg_H323::SaveAdvSetup()
{
	LPCTSTR strFile = ".\\H323.ini";
	TCHAR strOpt[10];
	LPCTSTR strApp = "网守设置";

	if(m_bViaGK)
		_tcscpy(strOpt,"TRUE");
	else
		_tcscpy(strOpt,"FALSE");
	
	WritePrivateProfileString(strApp,"用网守呼叫",strOpt,strFile);
	if(m_bViaGK)
		WritePrivateProfileString(strApp,"网守",LPCTSTR(m_strGatekeeper),strFile);

	if(m_bName)
		_tcscpy(strOpt,"TRUE");
	else
		_tcscpy(strOpt,"FALSE");

	WritePrivateProfileString(strApp,"用账户名登录",strOpt,strFile);
	if(m_bName)
		WritePrivateProfileString(strApp,"账户名",LPCTSTR(m_strName),strFile);

	if(m_bNumber)
		_tcscpy(strOpt,"TRUE");
	else
		_tcscpy(strOpt,"FALSE");

	WritePrivateProfileString(strApp,"用电话号码登录",strOpt,strFile);
	if(m_bNumber)
		WritePrivateProfileString(strApp,"电话号码",LPCTSTR(m_strNumber),strFile);

	if(m_bViaGW)
		_tcscpy(strOpt,"TRUE");
	else
		_tcscpy(strOpt,"FALSE");

	WritePrivateProfileString("网关设置","使用网关呼叫",strOpt,strFile);
	if(m_bViaGW)
		WritePrivateProfileString("网关设置","网关",LPCTSTR(m_strGateway),strFile);

}

void CDlg_H323::SaveIpAddr()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_H323_CALLED_ADDR);
	if(!pCombo)
		return;
	LPCTSTR strFile = ".\\H323.ini";
	TCHAR strApp[20];
	TCHAR strKey[20];
	TCHAR strValue[20];
	int nCount = pCombo->GetCount();
	CString strIpAddr;

	_tcscpy(strApp, "历史被叫地址");
	_tcscpy(strKey,"数目");
	_stprintf(strValue,"%d",nCount);
	WritePrivateProfileString(strApp,strKey,strValue,strFile);
	for(int i = 0; i < nCount; i++)
	{
		_stprintf(strKey,"地址%d",(i+1));
		pCombo->GetLBText(i,strIpAddr);
		WritePrivateProfileString(strApp,strKey,LPCTSTR(strIpAddr),strFile);
	}
}

//void CH323Dlg::LoadIpAddr()
void CDlg_H323::Loadini()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_H323_CALLED_ADDR);
	if(!pCombo)
		return;

	int nCount;
	LPCTSTR strFile = ".\\H323.ini";
	TCHAR strApp[20];
	TCHAR strCount[10];
	TCHAR strIp[20];
	TCHAR strKey[10];
	TCHAR strOpt[10];

	_tcscpy(strApp,"历史被叫地址");
	GetPrivateProfileString(strApp,"数目",NULL,strCount,10,strFile);
	nCount = atoi(strCount);
	for(int i = 0; i < nCount; i++)
	{
		_stprintf(strKey,"地址%d",(i+1));
		GetPrivateProfileString(strApp,strKey,NULL,strIp,20,strFile);
		pCombo->AddString(strIp);
	}

	_tcscpy(strApp,"网守设置");
	GetPrivateProfileString(strApp,"用网守呼叫","FALSE",strOpt,10,strFile);
	if(_tcscmp(strOpt,"TRUE") == 0)
		m_bViaGK = TRUE;
	else
		m_bViaGK = FALSE;

	if(m_bViaGK)
	{
		GetPrivateProfileString(strApp,"网守","172.17.1.34",m_strGatekeeper.GetBuffer(20),20,strFile);
		m_strGatekeeper.ReleaseBuffer();
	}

	GetPrivateProfileString(strApp,"用账户名登录","FALSE",strOpt,10,strFile);
	if(_tcscmp(strOpt,"TRUE") == 0)
		m_bName = TRUE;
	else
		m_bName = FALSE;

	if(m_bName)
	{
		GetPrivateProfileString(strApp,"账户名","tony",m_strName.GetBuffer(50),50,strFile);
		m_strName.ReleaseBuffer();
	}

	GetPrivateProfileString(strApp,"用电话号码登录","FALSE",strOpt,10,strFile);
	if(_tcscmp(strOpt,"TRUE") == 0)
		m_bNumber = TRUE;
	else
		m_bNumber = FALSE;

	if(m_bNumber)
	{
		GetPrivateProfileString(strApp,"电话号码","7788",m_strNumber.GetBuffer(50),50,strFile);
		m_strNumber.ReleaseBuffer();
	}

	GetPrivateProfileString("网关设置","使用网关呼叫","FALSE",strOpt,10,strFile);
	if(_tcscmp(strOpt,"TRUE") == 0)
		m_bViaGW = TRUE;
	else
		m_bViaGW = FALSE;

	if(m_bViaGW)
	{
		GetPrivateProfileString("网关设置","网关","172.17.0.50",m_strGateway.GetBuffer(50),50,strFile);
		m_strGateway.ReleaseBuffer();
	}
}

void CDlg_H323::OnClose()
{	
	ShowWindow(SW_HIDE);
	if(myContext->h245Channel && myContext->h225Channel)
	{
		OnHangup();	
		WaitForSingleObject(CH323MsgHandler::hRespondEvent,INFINITE);
		ResetEvent(CH323MsgHandler::hRespondEvent);
	}

	if(m_bViaGK)
	{
		//wait for unregistration confirm
		if(m_bRegistered)
		{
			UnregistrationRequest();
			WaitForSingleObject(CH323MsgHandler::hRespondEvent,INFINITE);
			ResetEvent(CH323MsgHandler::hRespondEvent);
		}
	}

	TerminateThread(m_hMonitorThread,0);

	if(myContext->callByGK == TRUE)
		ooCloseRasChannel(myContext);

	SaveIpAddr();
	ooSocketsCleanup();
	ooCloseContext(myContext);
	CDialog::OnClose();
}

//tony add 2004/11/24
void CDlg_H323::OnCallAdvanceSetup() 
{
	// TODO: Add your command handler code here
	CCallAdvSetupDlg dlg;

	dlg.m_bViaGK = m_bViaGK;
	dlg.m_strGatekeeper = m_strGatekeeper;
	dlg.m_bName = m_bName;
	dlg.m_strName = m_strName;
	dlg.m_bNumber = m_bNumber;
	dlg.m_strNumber = m_strNumber;
	dlg.m_bViaGW = m_bViaGW;
	dlg.m_strGateway = m_strGateway;
	if(IDOK == dlg.DoModal())
	{
		m_bViaGK = dlg.m_bViaGK;
		m_bName = dlg.m_bName;
		m_bNumber = dlg.m_bNumber;
		m_bViaGW = dlg.m_bViaGW;
		if(m_bViaGK)
			m_strGatekeeper = dlg.m_strGatekeeper;
		if(m_bName)
			m_strName = dlg.m_strName;
		if(m_bNumber)
			m_strNumber = dlg.m_strNumber;

		if(m_bViaGW)
			m_strGateway = dlg.m_strGateway;

		SaveAdvSetup();
	}
}

int CDlg_H323::WhatTypeIsDestStr(CString strCalled)
{
	int nCount = strCalled.GetLength();
	TCHAR ch;
	BOOL bIsnotNumber = FALSE;
	for(int i = 0; i < nCount; i++)
	{
		ch = strCalled.GetAt(i);
		if((ch < '0' && ch != '*' && ch != '#') || ch > '9')
		{
			bIsnotNumber = TRUE;
			break;
		}
	}

	if(bIsnotNumber == FALSE)
		return 1;		//号码类型
	
	int nIdx;
	BOOL bIsnotIp = FALSE;
	int nDotNum = 0;
	while((nIdx = strCalled.Find('.')) != -1)
	{
		nDotNum++;
		CString strLeft = strCalled.Left(nIdx);
		nCount = strCalled.GetLength();
		strCalled = strCalled.Right(nCount - nIdx -1);
		// for(i = 0; i < strLeft.GetLength(); i++)     XT-20110328
        for(int i = 0; i < strLeft.GetLength(); i++) // XT+20110328
		{
			ch = strLeft.GetAt(i);
			if(ch < '0'  || ch > '9')
			{
				bIsnotIp = TRUE;
				break;
			}
		}
		if(bIsnotIp == TRUE)
			break;
		else if(atoi(LPCTSTR(strLeft)) > 255)
		{
			bIsnotIp = TRUE;
			break;
		}
	}

	if(bIsnotIp == FALSE && nDotNum != 3)
		bIsnotIp = TRUE;

	if(bIsnotIp == FALSE)
		return 0;	//Ip地址类型

	return 2;		//账户类型
}

// XT-20110328
//
// void CH323Dlg::OnIncomingCall(WPARAM wParam,LPARAM lParam)
// {
// 	if(!m_pInCallDlg)
// 		m_pInCallDlg = new CIncomingCallDlg;
// 	if(m_pInCallDlg->GetSafeHwnd() == NULL)
// 		m_pInCallDlg->Create(IDD_INCOMING_CALL_DLG,this);
// 	m_pInCallDlg->ShowWindow(SW_SHOW);
// 	UpdateData(TRUE);
// 	m_pInCallDlg->ShowTip(LPCTSTR(m_strCalled));
// 	m_pInCallDlg->SetTimer(2005,400,NULL);
// }
// 
// void CH323Dlg::OnRecvRCF(WPARAM wParam,LPARAM lParam)
// {
// 	m_bRegistered = TRUE;
// }
// 
// 
// void CH323Dlg::OnRecvACF(WPARAM wParam,LPARAM lParam)
// {
// 	PopupCallingDlg();	
// 	CallSetup();
// }
// 
// void CH323Dlg::OnRecvConnect(WPARAM wParam,LPARAM lParam)
// {
// 	//record the successful connect ip address
// 	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_CALLED_ADDR);
// 	if(pCombo && pCombo->FindString(-1,LPCTSTR(m_strCalled)) == CB_ERR)
// 	{
// 		pCombo->AddString(m_strCalled);
// 		SaveIpAddr();
// 	}
// 
// 	CloseCallingDlg();
// 	KillTimer(2006);
// 	CWnd *pBtn = GetDlgItem(IDC_HANGUP);
// 	if(pBtn)
// 		pBtn->EnableWindow(TRUE);
// 
// 	if(!m_bName)
// 		AddParty(myContext->localIP);
// 	else
// 		AddParty(LPCTSTR(m_strName));
// 
// 	AddParty(m_strCalled);
// }
// 
// void CH323Dlg::OnSendConnect(WPARAM wParam,LPARAM lParam)
// {
// 	GetDlgItem(IDC_HANGUP)->EnableWindow(TRUE);
// 	AddParty(myContext->remoteIP);
// 	if(!m_bName)
// 		AddParty(myContext->localIP);
// 	else
// 		AddParty(LPCTSTR(m_strName));
// }
// 
// void CH323Dlg::OnRecvReleaseComplete(WPARAM wParam,LPARAM lParam)
// {
// 	m_cParties.DeleteAllItems();
// 	GetDlgItem(IDC_HANGUP)->EnableWindow(FALSE);
// }

// void CH323Dlg::OnIncomingCall(WPARAM wParam,LPARAM lParam)
// {
// 	if(!m_pInCallDlg)
// 		m_pInCallDlg = new CIncomingCallDlg;
// 	if(m_pInCallDlg->GetSafeHwnd() == NULL)
// 		m_pInCallDlg->Create(IDD_INCOMING_CALL_DLG,this);
// 	m_pInCallDlg->ShowWindow(SW_SHOW);
// 	UpdateData(TRUE);
// 	m_pInCallDlg->ShowTip(LPCTSTR(m_strCalled));
// 	m_pInCallDlg->SetTimer(2005,400,NULL);
// }
// 
// void CH323Dlg::OnRecvRCF(WPARAM wParam,LPARAM lParam)
// {
// 	m_bRegistered = TRUE;
// }
// 
// 
// void CH323Dlg::OnRecvACF(WPARAM wParam,LPARAM lParam)
// {
// 	PopupCallingDlg();	
// 	CallSetup();
// }
// 
// void CH323Dlg::OnRecvConnect(WPARAM wParam,LPARAM lParam)
// {
// 	//record the successful connect ip address
// 	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_CALLED_ADDR);
// 	if(pCombo && pCombo->FindString(-1,LPCTSTR(m_strCalled)) == CB_ERR)
// 	{
// 		pCombo->AddString(m_strCalled);
// 		SaveIpAddr();
// 	}
// 
// 	CloseCallingDlg();
// 	KillTimer(2006);
// 	CWnd *pBtn = GetDlgItem(IDC_HANGUP);
// 	if(pBtn)
// 		pBtn->EnableWindow(TRUE);
// 
// 	if(!m_bName)
// 		AddParty(myContext->localIP);
// 	else
// 		AddParty(LPCTSTR(m_strName));
// 
// 	AddParty(m_strCalled);
// }
// 
// void CH323Dlg::OnSendConnect(WPARAM wParam,LPARAM lParam)
// {
// 	GetDlgItem(IDC_HANGUP)->EnableWindow(TRUE);
// 	AddParty(myContext->remoteIP);
// 	if(!m_bName)
// 		AddParty(myContext->localIP);
// 	else
// 		AddParty(LPCTSTR(m_strName));
// }
// 
// void CH323Dlg::OnRecvReleaseComplete(WPARAM wParam,LPARAM lParam)
// {
// 	m_cParties.DeleteAllItems();
// 	GetDlgItem(IDC_HANGUP)->EnableWindow(FALSE);
// }

// XT+20110328
LRESULT CDlg_H323::OnIncomingCall(WPARAM wParam,LPARAM lParam)
{
	if(!m_pInCallDlg)
		m_pInCallDlg = new CIncomingCallDlg;
	if(m_pInCallDlg->GetSafeHwnd() == NULL)
		m_pInCallDlg->Create(IDD_DLG_H323_INCOMING_CALL,this);
	m_pInCallDlg->ShowWindow(SW_SHOW);
	UpdateData(TRUE);
	m_pInCallDlg->ShowTip(LPCTSTR(m_strCalled));
	m_pInCallDlg->SetTimer(2005,400,NULL);
    return 0L;
}

LRESULT CDlg_H323::OnRecvRCF(WPARAM wParam,LPARAM lParam)
{
	m_bRegistered = TRUE;
    return 0;
}


LRESULT CDlg_H323::OnRecvACF(WPARAM wParam,LPARAM lParam)
{
	PopupCallingDlg();	
	CallSetup();
    return 0;
}

LRESULT CDlg_H323::OnRecvConnect(WPARAM wParam,LPARAM lParam)
{
	//record the successful connect ip address
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_H323_CALLED_ADDR);
	if(pCombo && pCombo->FindString(-1,LPCTSTR(m_strCalled)) == CB_ERR)
	{
		pCombo->AddString(m_strCalled);
		SaveIpAddr();
	}

	CloseCallingDlg();
	KillTimer(2006);
	CWnd *pBtn = GetDlgItem(IDC_H323_HANGUP);
	if(pBtn)
		pBtn->EnableWindow(TRUE);

	if(!m_bName)
		AddParty(myContext->localIP);
	else
		AddParty(LPCTSTR(m_strName));

	AddParty(m_strCalled);
    return 0;
}

LRESULT CDlg_H323::OnSendConnect(WPARAM wParam,LPARAM lParam)
{
	GetDlgItem(IDC_H323_HANGUP)->EnableWindow(TRUE);
	AddParty(myContext->remoteIP);
	if(!m_bName)
		AddParty(myContext->localIP);
	else
		AddParty(LPCTSTR(m_strName));
    return 0;
}

LRESULT CDlg_H323::OnRecvReleaseComplete(WPARAM wParam,LPARAM lParam)
{
	m_cParties.DeleteAllItems();
	GetDlgItem(IDC_H323_HANGUP)->EnableWindow(FALSE);
    return 0;
}
//-------------------------------------------------

void CDlg_H323::OnDonotBother() 
{
	m_bDoNotBother = !m_bDoNotBother;
// 	CMenu *pMenu = GetMenu();
// 	UINT uCheck;
// 	uCheck = m_bDoNotBother ? MF_CHECKED : MF_UNCHECKED;
// 	pMenu->CheckMenuItem(ID_DONOT_BOTHER,uCheck);
}

void CDlg_H323::OnAutoAnswer() 
{
	m_bAutoAnswer = !m_bAutoAnswer;
// 	CMenu *pMenu = GetMenu();
// 	UINT uCheck;
// 	uCheck = m_bAutoAnswer ? MF_CHECKED : MF_UNCHECKED;
// 	pMenu->CheckMenuItem(ID_AUTO_ANSWER,uCheck);	
}

void CDlg_H323::AddParty(LPCTSTR strName)
{
	LVITEM item;
	item.mask = LVIF_IMAGE | LVIF_TEXT;

	item.iItem = m_cParties.GetItemCount();
	item.pszText = (char*)strName;
	item.iImage = 0;
	item.iSubItem = 0;
	m_cParties.InsertItem(&item);
}

void CDlg_H323::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnTimer(nIDEvent);

	// XT-20110328 CloseCallingDlg();
	// XT-20110328 AfxMessageBox("您呼叫的用户无法接通");
	KillTimer(2006);
}
