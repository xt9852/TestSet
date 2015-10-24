
#pragma once

#include "./opcodes.h"
#include "../../Common/Zip/zlib.h"

typedef unsigned char		uchar;
typedef unsigned char		uint8;
typedef	  signed char		sint8;

typedef unsigned short		uint16;
typedef	  signed short		sint16;

typedef unsigned int		uint32;
typedef	  signed int		sint32;

typedef unsigned __int64	uint64;
typedef   signed __int64	sint64;

/*-----------------------------------------------------------------------------------> xt
#ifdef _DEBUG
#include "Debug_FileSize.h"
#define USE_DEBUG_EMFILESIZE
typedef CEMFileSize			EMFileSize;
#else
typedef unsigned __int64	EMFileSize;
#endif
*/


#define	MP_COPYSELECTED			10326
#define	MP_CUT					10335
#define	MP_PASTE				10336
#define MPG_ALTENTER			10330
#define MPG_DELETE				10325
#define MPG_F2					10331

/////////////////////////////////////////////////////////////////


//#include "otherfunctions.h"

// md4clr -- replacement for memset(hash,0,16)
__inline void md4clr(const void* hash) {
	((uint32*)hash)[0] = ((uint32*)hash)[1] = ((uint32*)hash)[2] = ((uint32*)hash)[3] = 0;
}

// md4cpy -- replacement for memcpy(dst,src,16)
__inline void md4cpy(void* dst, const void* src) {
	((uint32*)dst)[0] = ((uint32*)src)[0];
	((uint32*)dst)[1] = ((uint32*)src)[1];
	((uint32*)dst)[2] = ((uint32*)src)[2];
	((uint32*)dst)[3] = ((uint32*)src)[3];
}

__inline bool strmd4(const CStringW& rstr, uchar* hash)
{
	memset(hash, 0, 16);
	if (rstr.GetLength() != 16*2)
		return false;
	for (int i = 0; i < 16; i++)
	{
		char byte[3];
		byte[0] = (char)rstr[i*2+0];
		byte[1] = (char)rstr[i*2+1];
		byte[2] = '\0';

		UINT b;
		if (sscanf(byte, "%x", &b) != 1)
			return false;
		hash[i] = (char)b;
	}
	return true;
}

#define MAX_CFEXP_ERRORMSG	(MAX_PATH + 256)

__inline void AddDebugLogLine(bool b, LPCTSTR pszLine, ...)
{
	TRACE(_T("-------%s\n"), pszLine);
}

__inline void DebugRecv(char *pszInfo, uint32 uIP, uint16 uPort)
{
	BYTE *pbyIp = (BYTE *)&uIP;
	CStringA strIp;
	strIp.Format("%d.%d.%d.%d", pbyIp[3], pbyIp[2], pbyIp[1], pbyIp[0]);

	TRACE("Recv %s %s:%d\n", pszInfo, strIp, uPort);
}

__inline void DebugSend(char *pszInfo, uint32 uIP, uint16 uPort)
{ 
	BYTE *pbyIp = (BYTE *)&uIP;

	CStringA strIp;
	strIp.Format("%d.%d.%d.%d", pbyIp[3], pbyIp[2], pbyIp[1], pbyIp[0]);

	TRACE("Send %s %s:%d\n", pszInfo, strIp, uPort);
}

__inline void DebugSendF(char *pszInfo, uint32 uIP, uint16 uPort, LPCSTR pszMsg, ...)
{
	BYTE *pbyIp = (BYTE *)&uIP;

	va_list args;
	va_start(args, pszMsg);

	CStringA strIp;
	strIp.Format("Send %s %d.%d.%d.%d:%d  ", pszInfo, pbyIp[3], pbyIp[2], pbyIp[1], pbyIp[0], uPort);
	strIp.AppendFormat(pszMsg, (uint16)*args);
	strIp.AppendFormat("\n");

	va_end(args);

	TRACE(strIp);
}


/////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Header_Struct{
	uint8	eDonkeyID;
	uint32	packetlength;
	uint8	command;
};
#pragma pack()

#pragma pack(1)
struct UDP_Header_Struct{
	uint8	eDonkeyID;
	uint8	command;
};
#pragma pack()


class Packet
{
public:
	Packet(uint8 protocol = OP_EDONKEYPROT)
	{
		m_bSplitted = false;
		m_bLastSplitted = false;
		m_bFromPF = false;
		size = 0;
		pBuffer = 0;
		completebuffer = 0;
		tempbuffer = 0;
		opcode = 0x00;
		prot = protocol;
		m_bPacked = false;
	}

	Packet(char* header) // only used for receiving packets
	{
		m_bSplitted = false;
		m_bPacked = false;
		m_bLastSplitted = false;
		m_bFromPF = false;
		tempbuffer = 0;
		pBuffer = 0;
		completebuffer = 0;
		Header_Struct* head = (Header_Struct*) header;
		size = head->packetlength-1;
		opcode = head->command;
		prot = head->eDonkeyID;
	}

	Packet(CMemFile* datafile, uint8 protocol = OP_EDONKEYPROT, uint8 ucOpcode = 0x00)
	{
		m_bSplitted = false;
		m_bPacked = false;
		m_bLastSplitted = false;
		m_bFromPF = false;
		size = (UINT)datafile->GetLength();
		completebuffer = new char[(UINT)datafile->GetLength() + 10];
		pBuffer = completebuffer+6;
		BYTE* tmp = datafile->Detach();
		memcpy(pBuffer,tmp,size);
		free(tmp);
		tempbuffer = 0;
		opcode = ucOpcode;
		prot = protocol;
	}
	

	Packet(const CStringA& str, uint8 ucProtocol, uint8 ucOpcode)
	{
		m_bSplitted = false;
		m_bPacked = false;
		m_bLastSplitted = false;
		m_bFromPF = false;
		size = str.GetLength();
		completebuffer = new char[size+10];
		pBuffer = completebuffer+6;
		memcpy(pBuffer,(LPCSTR)str,size);
		tempbuffer = 0;
		opcode = ucOpcode;
		prot = ucProtocol;
	}


	Packet(uint8 in_opcode, uint32 in_size, uint8 protocol = OP_EDONKEYPROT, bool bFromPartFile = true)
	{
		m_bFromPF = bFromPartFile;
		m_bSplitted = false;
		m_bPacked = false;
		m_bLastSplitted = false;
		tempbuffer = 0;
		if (in_size){
			completebuffer = new char[in_size+10];
			pBuffer = completebuffer+6;
			memset(completebuffer,0,in_size+10);
		}
		else{
			pBuffer = 0;
			completebuffer = 0;
		}
		opcode = in_opcode;
		size = in_size;
		prot = protocol;
	}	

	Packet(char* pPacketPart,uint32 nSize,bool bLast,bool bFromPartFile = true) // only used for splitted packets!
	{
		m_bFromPF = bFromPartFile;
		m_bSplitted = true;
		m_bPacked = false;
		m_bLastSplitted = bLast;
		tempbuffer = 0;
		pBuffer = 0;
		completebuffer = pPacketPart;
		size = nSize-6;
		opcode = 0x00;
		prot = 0x00;
	}

	virtual ~Packet(){
		if (completebuffer)
			delete[] completebuffer;
		else
			delete[] pBuffer;
		delete[] tempbuffer;
	}

	virtual char* GetHeader()
	{
		ASSERT ( !m_bSplitted );
		Header_Struct* header = (Header_Struct*) head;
		header->command = opcode;
		header->eDonkeyID =  prot;
		header->packetlength = size+1;
		return head;
	}

	virtual char* GetUDPHeader()
	{
		ASSERT ( !m_bSplitted );
		UDP_Header_Struct* header = (UDP_Header_Struct*) head;
		header->command = opcode;
		header->eDonkeyID =  prot;
		return head;
	}

	virtual char* GetPacket()
	{
		if (completebuffer){
			if (!m_bSplitted)
				memcpy(completebuffer,GetHeader(),6);
			char* result = completebuffer;
			completebuffer = 0;
			pBuffer = 0;
			return result;
		}
		else{
			delete[] tempbuffer;
			tempbuffer = NULL; // 'new' may throw an exception
			tempbuffer = new char[size+10];
			memcpy(tempbuffer,GetHeader(),6);
			memcpy(tempbuffer+6,pBuffer,size);
			char* result = tempbuffer;
			tempbuffer = 0;
			return result;
		}
	}

	virtual char* DetachPacket()
	{
		if (completebuffer){
			if (!m_bSplitted)
				memcpy(completebuffer,GetHeader(),6);
			char* result = completebuffer;
			completebuffer = 0;
			pBuffer = 0;
			return result;
		}
		else{
			delete[] tempbuffer;
			tempbuffer = NULL; // 'new' may throw an exception
			tempbuffer = new char[size+10];
			memcpy(tempbuffer,GetHeader(),6);
			memcpy(tempbuffer+6,pBuffer,size);
			char* result = tempbuffer;
			tempbuffer = 0;
			return result;
		}
	}

	virtual uint32 GetRealPacketSize() const	{return size+6;}
	//	bool	IsSplitted() const					{return m_bSplitted;}
	//	bool	IsLastSplitted() const				{return m_bLastSplitted;}
	bool	IsFromPF() const					{return m_bFromPF;}
	void	PackPacket()
	{
		ASSERT (!m_bSplitted);
		uLongf newsize = size+300;
		BYTE* output = new BYTE[newsize];
		UINT result = compress2(output,&newsize,(BYTE*)pBuffer,size,Z_BEST_COMPRESSION);
		if (result != Z_OK || size <= newsize){
			delete[] output;
			return;
		}
		if( prot == OP_KADEMLIAHEADER )
			prot = OP_KADEMLIAPACKEDPROT;
		else
			prot = OP_PACKEDPROT;
		memcpy(pBuffer,output,newsize);
		size = newsize;
		delete[] output;
		m_bPacked = true;
	}

	bool	UnPackPacket(UINT uMaxDecompressedSize = 50000)
	{
		ASSERT ( prot == OP_PACKEDPROT || prot == OP_KADEMLIAPACKEDPROT); 
		uint32 nNewSize = size*10+300;
		if (nNewSize > uMaxDecompressedSize){
			//ASSERT(0);
			nNewSize = uMaxDecompressedSize;
		}
		BYTE* unpack = new BYTE[nNewSize];
		uLongf unpackedsize = nNewSize;
		UINT result = uncompress(unpack,&unpackedsize,(BYTE*)pBuffer,size);
		if (result == Z_OK){
			ASSERT ( completebuffer == NULL );
			ASSERT ( pBuffer != NULL );
			size = unpackedsize;
			delete[] pBuffer;
			pBuffer = (char*)unpack;
			if( prot == OP_KADEMLIAPACKEDPROT )
				prot = OP_KADEMLIAHEADER;
			else
				prot =  OP_EMULEPROT;
			return true;
		}
		delete[] unpack;
		return false;
	}

	char*	pBuffer;
	uint32	size;
	uint8	opcode;
	uint8	prot;

protected:
	bool	m_bSplitted;
	bool	m_bLastSplitted;
	bool	m_bPacked;
	bool	m_bFromPF;
	char*	completebuffer;
	char*	tempbuffer;
	char	head[6];
};

//////////////////////////////////////////////////////////////////////////////////////


class CTempIconLoader
{
public:
	// because nearly all icons we are loading are 16x16, the default size is specified as 16 and not as 32 nor LR_DEFAULTSIZE
	CTempIconLoader(LPCTSTR pszResourceID, int cx = 16, int cy = 16, UINT uFlags = LR_DEFAULTCOLOR)
	{
		m_hIcon = LoadIcon(pszResourceID, cx, cy, uFlags);
	}

	CTempIconLoader(UINT uResourceID, int cx = 16, int cy = 16, UINT uFlags = LR_DEFAULTCOLOR)
	{
		UNREFERENCED_PARAMETER(uFlags);
		ASSERT( uFlags == 0 );
		//m_hIcon = LoadIcon(uResourceID);
	}

	~CTempIconLoader()
	{
		if (m_hIcon)
			VERIFY( DestroyIcon(m_hIcon) );
	}

	operator HICON() const
	{
		return this == NULL ? NULL : m_hIcon;
	}

	HICON LoadIcon(LPCTSTR lpszResourceName, int cx, int cy, UINT uFlags)
	{
		HICON hIcon = NULL;

		if (cx != LR_DEFAULTSIZE || cy != LR_DEFAULTSIZE || uFlags != LR_DEFAULTCOLOR)
			hIcon = (HICON)::LoadImage(AfxGetResourceHandle(), lpszResourceName, IMAGE_ICON, cx, cy, uFlags);
		if (hIcon == NULL)
		{
			//TODO: Either do not use that function or copy the returned icon. All the calling code is designed
			// in a way that the icons returned by this function are to be freed with 'DestroyIcon'. But an 
			// icon which was loaded with 'LoadIcon', is not be freed with 'DestroyIcon'.
			// Right now, we never come here...
			ASSERT(0);
			//hIcon = CWinApp::LoadIcon(lpszResourceName);
		}

		return hIcon;
	}

protected:
	HICON m_hIcon;
};


//----------------------------------------------------------------------------------< xt




