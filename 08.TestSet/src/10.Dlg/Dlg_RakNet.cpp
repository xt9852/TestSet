
#include "stdafx.h"
#include "TestSet.h"
#include "Dlg_RakNet.h"
#include ".\dlg_raknet.h"
/*
#include "RakNet\MessageIdentifiers.h"
#include "RakNet\RakNetworkFactory.h"
#include "RakNet\RakPeerInterface.h"
#include "RakNet\RakNetStatistics.h"
#include "RakNet\RakNetTypes.h"
#include "assert.h"

// We copy this from Multiplayer.cpp to keep things all in one file for this example
unsigned char GetPacketIdentifier(Packet *p);
*/

// CDlg_DB ¶Ô»°¿ò

IMPLEMENT_DYNAMIC(CDlg_RakNet, CDialog)
CDlg_RakNet::CDlg_RakNet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_RakNet::IDD, pParent)
{
}

CDlg_RakNet::~CDlg_RakNet()
{
}

void CDlg_RakNet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlg_RakNet, CDialog)
	ON_BN_CLICKED(IDC_RAKNET_BTN_RUN, OnBnClickedRaknetBtnRun)
END_MESSAGE_MAP()


BOOL CDlg_RakNet::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

/*
// Copied from Multiplayer.cpp
// If the first byte is ID_TIMESTAMP, then we want the 5th byte
// Otherwise we want the 1st byte
unsigned char GetPacketIdentifier(Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		assert(p->length > sizeof(unsigned char) + sizeof(unsigned long));
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	}
	else
		return (unsigned char) p->data[0];
}
*/
void CDlg_RakNet::OnBnClickedRaknetBtnRun()
{
/*
	RakNetStatistics *rss;

	RakPeerInterface *client=RakNetworkFactory::GetRakPeerInterface();
	//client->InitializeSecurity(0,0,0,0);
	client->AllowConnectionResponseIPMigration(false);

	Packet* p;
	unsigned char packetIdentifier;
	SystemAddress clientID=UNASSIGNED_SYSTEM_ADDRESS;
	char ip[30] = "127.0.0.1", serverPort[30] = "10000", clientPort[30] = "20000";

	// Connecting the client is very simple.  0 means we don't care about
	// a connectionValidationInteger, and false for low priority threads
	SocketDescriptor socketDescriptor(atoi(clientPort),0);
	client->Startup(1,30,&socketDescriptor, 1);
	client->SetOccasionalPing(true);
	bool b = client->Connect(ip, atoi(serverPort), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"));	

	if (b)
		TRACE("Attempting connection");
	else
	{
		TRACE("Bad connection attempt.  Terminating.");
		exit(1);
	}

	char message[2048];

	while (1)
	{
		Sleep(30);

		if (strcmp(message, "stat")==0)
		{
			rss=client->GetStatistics(client->GetSystemAddressFromIndex(0));
			StatisticsToString(rss, message, 2);
			printf("%s", message);
			printf("Ping=%i\n", client->GetAveragePing(client->GetSystemAddressFromIndex(0)));			

			continue;
		}

		if (strcmp(message, "ping")==0)
		{
			if (client->GetSystemAddressFromIndex(0)!=UNASSIGNED_SYSTEM_ADDRESS)
				client->Ping(client->GetSystemAddressFromIndex(0));

			continue;
		}

		// message is the data to send
		// strlen(message)+1 is to send the null terminator
		// HIGH_PRIORITY doesn't actually matter here because we don't use any other priority
		// RELIABLE_ORDERED means make sure the message arrives in the right order
		client->Send(message, (int) strlen(message)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);

		p = client->Receive();

		if (p==0)
			continue;

		// We got a packet, get the identifier with our handy function
		packetIdentifier = GetPacketIdentifier(p);

		// Check if this is a network message packet
		switch (packetIdentifier)
		{
			case ID_DISCONNECTION_NOTIFICATION:
				 // Connection lost normally
				TRACE("ID_DISCONNECTION_NOTIFICATION\n");
				break;
			case ID_ALREADY_CONNECTED:
				// Connection lost normally
				TRACE("ID_ALREADY_CONNECTED\n");
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				TRACE("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
				break;
			case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				TRACE("ID_REMOTE_CONNECTION_LOST\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
				TRACE("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
				break;
			case ID_CONNECTION_BANNED: // Banned from this server
				TRACE("We are banned from this server.\n");
				break;			
			case ID_CONNECTION_ATTEMPT_FAILED:
				TRACE("Connection attempt failed\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				 // Sorry, the server is full.  I don't do anything here but
				// A real app should tell the user
				TRACE("ID_NO_FREE_INCOMING_CONNECTIONS\n");
				break;
			case ID_MODIFIED_PACKET:
				// Cheater!
				TRACE("ID_MODIFIED_PACKET\n");
				break;
			case ID_INVALID_PASSWORD:
				TRACE("ID_INVALID_PASSWORD\n");
				break;
			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				TRACE("ID_CONNECTION_LOST\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				// This tells the client they have connected
				TRACE("ID_CONNECTION_REQUEST_ACCEPTED\n");
				break;
			default:
					// It's a client, so just show the message
					TRACE("%s\n", p->data);
				break;
		}

		// We're done with the packet
		client->DeallocatePacket(p);
	}

	client->Shutdown(300);
	RakNetworkFactory::DestroyRakPeerInterface(client);
*/
}
