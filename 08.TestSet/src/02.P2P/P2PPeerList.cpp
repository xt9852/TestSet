
#include "StdAfx.h"
#include "P2PPeerList.h"
#include "P2PProtocol.h"


namespace XT_P2P
{
	/**
	 *\fn         P2PPeerList()
	 *\brief      缺省构造函数。
	 */
	P2PPeerList::P2PPeerList()
        :fileListSize_(0),
        peerCount_(0)
	{
        fileListMd5_[0] = _T('\0');

        size_ = M(1);
        buff_ = new TCHAR[size_];
	}

	/**
	 *\fn         ~P2PPeerList()
	 *\brief      析构函数。
	 */
	P2PPeerList::~P2PPeerList()
	{
        if (NULL != buff_) delete[] buff_;
	}

    int P2PPeerList::GetData(UINT ip, USHORT port, P2P_PEER_LIST &list)
    {
        peerCount_ = list.size() + 1;

        int dataLen = sizeof(P2P_ADDR) * peerCount_;

        if (dataLen > size_)
        {
            delete[] buff_;

            size_ = dataLen;
            buff_ = new TCHAR[size_];
        }

        P2P_ADDR *addList = (P2P_ADDR*)buff_;
        addList->wanIp_ = ip;
        addList->lanIp_ = ip;
        addList->wanPort_ = port;
        addList->lanPort_ = port;

        P2P_PEER_LIST::const_iterator iter = list.begin();
        for (int i = 1; iter != list.end(); ++iter, ++i)
        {
            P2PPeer *peer = *iter;

            addList[i] = *peer->getAddr();
        }

        return 0;
    }
}