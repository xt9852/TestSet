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

#include "stdafx.h"
#include "./BufferedFileIO.h"
#include "./IOException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace Kademlia;

void CBufferedFileIO::ReadArray(LPVOID lpResult, uint32 uByteCount)
{
	if( Read(lpResult, uByteCount) != uByteCount )
		throw new CIOException(ERR_END_OF_FILE);
}

void CBufferedFileIO::WriteArray(LPCVOID lpVal, uint32 uByteCount)
{
	Write(lpVal, uByteCount);
}

UINT CBufferedFileIO::GetAvailable() const
{
	return (UINT)(GetLength() - GetPosition());
}






///////////////////////////////////////////////////////////////////////////////
// CSafeMemFile

UINT CSafeMemFile::Read(void* lpBuf, UINT nCount)
{
	if (m_nPosition + nCount > m_nFileSize)
		AfxThrowFileException(CFileException::endOfFile, 0, CMemFile::GetFileName());
	return CMemFile::Read(lpBuf, nCount);
}

void CSafeMemFile::Write(const void* lpBuf, UINT nCount)
{
	CMemFile::Write(lpBuf, nCount);
}

ULONGLONG CSafeMemFile::Seek(LONGLONG lOff, UINT nFrom)
{
	return CMemFile::Seek(lOff, nFrom);
}

uint8 CSafeMemFile::ReadUInt8()
{
	if (m_nPosition + sizeof(uint8) > m_nFileSize)
		AfxThrowFileException(CFileException::endOfFile, 0, CMemFile::GetFileName());
	return *(m_lpBuffer + m_nPosition++);
}

uint16 CSafeMemFile::ReadUInt16()
{
	if (m_nPosition + sizeof(uint16) > m_nFileSize)
		AfxThrowFileException(CFileException::endOfFile, 0, CMemFile::GetFileName());
	uint16 nResult = *((uint16*)(m_lpBuffer + m_nPosition));
	m_nPosition += sizeof(uint16);
	return nResult;
}

uint32 CSafeMemFile::ReadUInt32()
{
	if (m_nPosition + sizeof(uint32) > m_nFileSize)
		AfxThrowFileException(CFileException::endOfFile, 0, CMemFile::GetFileName());
	uint32 nResult = *((uint32*)(m_lpBuffer + m_nPosition));
	m_nPosition += sizeof(uint32);
	return nResult;
}

uint64 CSafeMemFile::ReadUInt64()
{
	if (m_nPosition + sizeof(uint64) > m_nFileSize)
		AfxThrowFileException(CFileException::endOfFile, 0, CMemFile::GetFileName());
	uint64 nResult = *((uint64*)(m_lpBuffer + m_nPosition));
	m_nPosition += sizeof(uint64);
	return nResult;
}

void CSafeMemFile::ReadUInt128(Kademlia::CUInt128* pVal)
{
	if (m_nPosition + sizeof(uint32)*4 > m_nFileSize)
		AfxThrowFileException(CFileException::endOfFile, 0, CMemFile::GetFileName());
	uint32* pUInt32Val = (uint32*)pVal->GetDataPtr();
	const uint32* pUInt32 = (uint32*)(m_lpBuffer + m_nPosition);
	pUInt32Val[0] = pUInt32[0];
	pUInt32Val[1] = pUInt32[1];
	pUInt32Val[2] = pUInt32[2];
	pUInt32Val[3] = pUInt32[3];
	m_nPosition += sizeof(uint32)*4;
}

void CSafeMemFile::ReadHash16(uchar* pVal)
{
	if (m_nPosition + sizeof(uint32)*4 > m_nFileSize)
		AfxThrowFileException(CFileException::endOfFile, 0, CMemFile::GetFileName());
	const uint32* pUInt32 = (uint32*)(m_lpBuffer + m_nPosition);
	((uint32*)pVal)[0] = pUInt32[0];
	((uint32*)pVal)[1] = pUInt32[1];
	((uint32*)pVal)[2] = pUInt32[2];
	((uint32*)pVal)[3] = pUInt32[3];
	m_nPosition += sizeof(uint32)*4;
}

void CSafeMemFile::WriteUInt8(uint8 nVal)
{
	if (m_nPosition + sizeof(uint8) > m_nBufferSize)
		GrowFile(m_nPosition + sizeof(uint8));
	*(m_lpBuffer + m_nPosition++) = nVal;
	if (m_nPosition > m_nFileSize)
		m_nFileSize = m_nPosition;
}

void CSafeMemFile::WriteUInt16(uint16 nVal)
{
	if (m_nPosition + sizeof(uint16) > m_nBufferSize)
		GrowFile(m_nPosition + sizeof(uint16));
	*((uint16*)(m_lpBuffer + m_nPosition)) = nVal;
	m_nPosition += sizeof(uint16);
	if (m_nPosition > m_nFileSize)
		m_nFileSize = m_nPosition;
}

void CSafeMemFile::WriteUInt32(uint32 nVal)
{
	if (m_nPosition + sizeof(uint32) > m_nBufferSize)
		GrowFile(m_nPosition + sizeof(uint32));
	*((uint32*)(m_lpBuffer + m_nPosition)) = nVal;
	m_nPosition += sizeof(uint32);
	if (m_nPosition > m_nFileSize)
		m_nFileSize = m_nPosition;
}

void CSafeMemFile::WriteUInt64(uint64 nVal)
{
	if (m_nPosition + sizeof(uint64) > m_nBufferSize)
		GrowFile(m_nPosition + sizeof(uint64));
	*((uint64*)(m_lpBuffer + m_nPosition)) = nVal;
	m_nPosition += sizeof(uint64);
	if (m_nPosition > m_nFileSize)
		m_nFileSize = m_nPosition;
}

void CSafeMemFile::WriteUInt128(const Kademlia::CUInt128* pVal)
{
	if (m_nPosition + sizeof(uint32)*4 > m_nBufferSize)
		GrowFile(m_nPosition + sizeof(uint32)*4);
	uint32* pUInt32 = (uint32*)(m_lpBuffer + m_nPosition);
	const uint32* pUInt32Val = (uint32*)pVal->GetData();
	pUInt32[0] = pUInt32Val[0];
	pUInt32[1] = pUInt32Val[1];
	pUInt32[2] = pUInt32Val[2];
	pUInt32[3] = pUInt32Val[3];
	m_nPosition += sizeof(uint32)*4;
	if (m_nPosition > m_nFileSize)
		m_nFileSize = m_nPosition;
}

void CSafeMemFile::WriteHash16(const uchar* pVal)
{
	if (m_nPosition + sizeof(uint32)*4 > m_nBufferSize)
		GrowFile(m_nPosition + sizeof(uint32)*4);
	uint32* pUInt32 = (uint32*)(m_lpBuffer + m_nPosition);
	pUInt32[0] = ((uint32*)pVal)[0];
	pUInt32[1] = ((uint32*)pVal)[1];
	pUInt32[2] = ((uint32*)pVal)[2];
	pUInt32[3] = ((uint32*)pVal)[3];
	m_nPosition += sizeof(uint32)*4;
	if (m_nPosition > m_nFileSize)
		m_nFileSize = m_nPosition;
}

ULONGLONG CSafeMemFile::GetPosition() const
{
	return CMemFile::GetPosition();
}

ULONGLONG CSafeMemFile::GetLength() const
{
	return CMemFile::GetLength();
}

CStringW CSafeMemFile::ReadStringUTF8()
{
	UINT uRawSize = ReadUInt16();
	const UINT uMaxShortRawSize = SHORT_RAW_ED2K_UTF8_STR;
	if (uRawSize <= uMaxShortRawSize)
	{
		char acRaw[uMaxShortRawSize];
		Read(acRaw, uRawSize);
		WCHAR awc[uMaxShortRawSize];
		int iChars = ByteStreamToWideChar(acRaw, uRawSize, awc, ARRSIZE(awc));
		if (iChars >= 0)
			return CStringW(awc, iChars);
		return CStringW(acRaw, uRawSize); // use local codepage
	}
	else
	{
		Array<char> acRaw(uRawSize);
		Read(acRaw, uRawSize);
		Array<WCHAR> awc(uRawSize);
		int iChars = ByteStreamToWideChar(acRaw, uRawSize, awc, uRawSize);
		if (iChars >= 0)
			return CStringW(awc, iChars);
		return CStringW(acRaw, uRawSize); // use local codepage;
	}
}


