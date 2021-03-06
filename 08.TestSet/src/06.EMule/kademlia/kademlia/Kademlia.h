/*
Copyright (C)2003 Barry Dunne (http://www.emule-project.net)
 
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

// Note To Mods //
/*
Please do not change anything here and release it..
There is going to be a new forum created just for the Kademlia side of the client..
If you feel there is an error or a way to improve something, please
post it in the forum first and let us look at it.. If it is a real improvement,
it will be added to the offical client.. Changing something without knowing
what all it does can cause great harm to the network if released in mass form..
Any mod that changes anything within the Kademlia side will not be allowed to advertise
there client on the eMule forum..
*/
#pragma once

#include "../routing/Maps.h"
#include "../net/KademliaUDPListener.h"
#include "../ClientUDPSocket.h"
#include "../../UI/KadContactListCtrl.h"
#include "../../UI/KadSearchListCtrl.h"
#include "../../UI/KadContactHistogramCtrl.h"
#include "./SearchManager.h"
#include "./Prefs.h"

#include "../../XTIP2Country.h"
#include "../../../Dlg/Dlg_Emule_KAD.h"

//------------------------------> xt
//class CSharedFileList;
//struct Status;

	class CClientUDPSocket;
	class CKadContactListCtrl;
	class CKadSearchListCtrl;
	class CKadContactHistogramCtrl;
	class CXTIP2Country;
	
//-----------------------------< xt


namespace Kademlia
{
    class CPrefs;
	class CKademliaUDPListener;
	class CIndexed;
	class CKademlia
	{
		public:
			CKademlia();

			static BOOL Start(CKadContactListCtrl *pListCtrl,
				CKadSearchListCtrl *pSearchListCtrl,
				CKadContactHistogramCtrl *pHistogramCtrl,
				CXTIP2Country *pIP2Country,
				LPCTSTR tszIP,
				WORD wTcpPort,
				WORD wUdpPort);
			static BOOL	Start(CPrefs *pPrefs,
				CKadContactListCtrl *pListCtrl,
				CKadSearchListCtrl *pSearchListCtrl,
				CKadContactHistogramCtrl *pHistogramCtrl,
				CXTIP2Country *pIP2Country);
			static void	Stop();
			static CPrefs *GetPrefs();
			static CRoutingZone *GetRoutingZone();
			static CKademliaUDPListener *GetUDPListener();
			static CIndexed *GetIndexed();
			static bool	IsRunning();
			static bool	IsConnected();
			static bool	IsFirewalled();
			static void	RecheckFirewalled();
			//  force find-buddy going
			static bool StartFindBuddy();
			static uint32 GetKademliaUsers();
			static uint32 GetKademliaFiles();
			static uint32 GetTotalStoreKey();
			static uint32 GetTotalStoreSrc();
			static uint32 GetTotalStoreNotes();
			static uint32 GetTotalFile();
			static bool	GetPublish();
			static uint32 GetIPAddress();
			static void	Bootstrap(uint32 uIP, uint16 uPort, bool bKad2);
			static void	Bootstrap(LPCTSTR szHost, uint16 uPort, bool bKad2);
			static void	ProcessPacket(const byte* pbyData, uint32 uLenData, uint32 uIP, uint16 uPort);
			static void	AddEvent(CRoutingZone *pZone);
			static void	RemoveEvent(CRoutingZone *pZone);
			static void	Process();
			static bool	InitUnicode(HMODULE hInst);
			static bool LostConnection();
			static bool IsReady(){return GetPublish();}
		private:
			static CKademlia *m_pInstance;
			static EventMap	m_mapEvents;
			static time_t m_tNextSearchJumpStart;
			static time_t m_tNextSelfLookup;
			static time_t m_tNextFirewallCheck;
			static time_t m_tNextFindBuddy;
			static time_t m_tStatusUpdate;
			static time_t m_tBigTimer;
			static time_t m_tBootstrap;
			static time_t m_tConsolidate;
			static time_t m_tRecvData;
			static bool	m_bRunning;
			CPrefs *m_pPrefs;
			CRoutingZone *m_pRoutingZone;
			CKademliaUDPListener *m_pUDPListener;
			CIndexed *m_pIndexed;

			//ADDED by VC-fengwen 2007/08/10 <begin> : Update whole K-Bucket
			static time_t m_tNextUpdateWholeKBucket;
			static void Process_UpdateWholeKBucket();
			static void UpdateWholeKBucket();
			//ADDED by VC-fengwen 2007/08/10 <end> : Update whole K-Bucket

			//---------------------------------------------------->
			// xt add

			CClientUDPSocket				*m_pUDPSocket;
			CKadContactListCtrl				*m_pListCtrl;
			CKadSearchListCtrl				*m_pSearchListCtrl;
			CKadContactHistogramCtrl		*m_pHistogramCtrl;
			CXTIP2Country					*m_pIP2Country;
	public:
			static CString					m_strCofigPath;
			static CClientUDPSocket			*GetUDPSocket();
			static CKadContactListCtrl		*GetListCtrl();
			static CKadSearchListCtrl		*GetSearchListCtrl();
			static CKadContactHistogramCtrl	*GetHistogramCtrl();
			static CXTIP2Country			*GetIP2Country();
			//----------------------------------------------------<
	};
}
