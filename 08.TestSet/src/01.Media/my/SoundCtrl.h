
#pragma once
#include <mmsystem.h>

enum{
    WAVE,
    SPEAKER,
    VOLUME,
    MUTE
};

class CSoundCtrl
{
public:
    CSoundCtrl();
    ~CSoundCtrl();

private:
    UINT m_nNumMixers;
    HMIXER m_hMixer;
    MIXERCAPS m_mxcaps;

    CString m_strWaveLineName;
    CString m_strMeterControlName;
    LONG m_lMinimum;
    LONG m_lMaximum;
    DWORD m_dwMeterControlID;

    BOOL amdUninitialize();
    BOOL amdInitialize();

public:
    BOOL Init(UINT nCtrl = SPEAKER, UINT nType = VOLUME);	
    BOOL amdGetMeterControl(UINT nCtrl, UINT nType);
    BOOL amdGetMeterValue(LONG &lVal) const;
    BOOL amdSetMeterValue(LONG lVal) const;
};
