#pragma once
#include "Common\KeyList.h"
#include "Network\BuffPool.h"

class CAVList : public CKeyList
{
public:
	CAVList(void);
	~CAVList(void);

private:
	DWORD		m_dwAudioId;	// 音频ID
	DWORD		m_dwVideoId;	// 视频ID
	WORD		m_wLimitNum;	// 节点数量
	CBuffPool	*m_pBuffPool;

public:
	bool Init(CBuffPool* pBuffPool, WORD wLimitNum);
	bool AddLimitNode(DWORD dwKey, LPBYTE pbyData);
	virtual void DelAll(void);

	int EnumAll(void);
};
