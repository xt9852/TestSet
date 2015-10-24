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

#include "./DataIO.h"
#include "../StringConversion.h"

namespace Kademlia
{
	class CBufferedFileIO : public CStdioFile, public CDataIO
	{
		public:
			virtual void ReadArray(LPVOID lpResult, uint32 uByteCount);
			virtual void WriteArray(LPCVOID lpVal, uint32 uByteCount);
			virtual UINT GetAvailable() const;
	};


	///////////////////////////////////////////////////////////////////////////////
	// CSafeMemFile

	class CSafeMemFile : public CMemFile//, public CBufferedFileIO
	{
	public:
		CSafeMemFile(UINT nGrowBytes = 512)
			: CMemFile(nGrowBytes) {}

			CSafeMemFile::CSafeMemFile(const BYTE* lpBuffer, UINT nBufferSize)
				: CMemFile(const_cast<BYTE*>(lpBuffer), nBufferSize, 0) {}

				const BYTE* GetBuffer() const { return CMemFile::m_lpBuffer; }

				UINT Read(void* lpBuf, UINT nCount);
				void Write(const void* lpBuf, UINT nCount);
				ULONGLONG Seek(LONGLONG lOff, UINT nFrom);
				ULONGLONG GetPosition() const;
				ULONGLONG GetLength() const;

				uint8 ReadUInt8();
				uint16 ReadUInt16();
				uint32 ReadUInt32();
				uint64 ReadUInt64();
				void ReadUInt128(Kademlia::CUInt128 *pVal);
				void ReadHash16(uchar* pVal);

				void WriteUInt8(uint8 nVal);
				void WriteUInt16(uint16 nVal);
				void WriteUInt32(uint32 nVal);
				void WriteUInt64(uint64 nVal);
				void WriteUInt128(const Kademlia::CUInt128 *pVal);
				void WriteHash16(const uchar* pVal);

				CStringW ReadStringUTF8();
	};
}

/*
virtual 
virtual 
virtual 
virtual 
virtual 

virtual 
virtual 
virtual 
virtual 
virtual 
virtual 

virtual 
virtual 
virtual 
virtual 
virtual 
virtual 
*/














