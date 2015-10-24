
#include "stdafx.h"
#include "SoundCtrl.h"


CSoundCtrl::CSoundCtrl()
{
}
CSoundCtrl::~CSoundCtrl()
{
    amdUninitialize();
}

BOOL CSoundCtrl::Init(UINT nCtrl, UINT nType)
{
    if (this->amdInitialize())
    {
        return this->amdGetMeterControl(nCtrl, nType);		 
    }

    return FALSE;
}

BOOL CSoundCtrl::amdInitialize()
{
    // get the number of mixer devices present in the system
    m_nNumMixers = ::mixerGetNumDevs();

    m_hMixer = NULL;
    ::ZeroMemory(&m_mxcaps, sizeof(MIXERCAPS));

    // open the first mixer
    // A "mapper" for audio mixer devices does not currently exist.
    if (m_nNumMixers != 0)
    {
        if (::mixerOpen(&m_hMixer, 0, 0, NULL, MIXER_OBJECTF_MIXER) != MMSYSERR_NOERROR)
            return FALSE;

        if (::mixerGetDevCaps((UINT_PTR)m_hMixer, &m_mxcaps, sizeof(MIXERCAPS)) != MMSYSERR_NOERROR)
            return FALSE;
    }

    return TRUE;
}

BOOL CSoundCtrl::amdUninitialize()
{
    BOOL bSucc = TRUE;

    if (m_hMixer != NULL)
    {
        bSucc = ::mixerClose(m_hMixer) == MMSYSERR_NOERROR;
        m_hMixer = NULL;
    }

    return bSucc;
}

BOOL CSoundCtrl::amdGetMeterControl(UINT nCtrl, UINT nType)
{
    m_strWaveLineName.Empty();
    m_strMeterControlName.Empty();

    if (m_hMixer == NULL)
        return FALSE;

    // get dwLineID
    MIXERLINE mxl;
    mxl.cbStruct = sizeof(MIXERLINE);
    mxl.dwComponentType = (WAVE == nCtrl) ? MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT: MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
    if (::mixerGetLineInfo((HMIXEROBJ)m_hMixer,   &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE)
        != MMSYSERR_NOERROR)
        return FALSE;

    // get dwControlID
    MIXERCONTROL mxc;
    MIXERLINECONTROLS mxlc;
    mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
    mxlc.dwLineID = mxl.dwLineID;
    mxlc.dwControlType = (VOLUME == nType) ? MIXERCONTROL_CONTROLTYPE_VOLUME: MIXERCONTROL_CONTROLTYPE_MUTE;
    mxlc.cControls = 1;
    mxlc.cbmxctrl = sizeof(MIXERCONTROL);
    mxlc.pamxctrl = &mxc;
    if (::mixerGetLineControls((HMIXEROBJ)m_hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE)
        != MMSYSERR_NOERROR)
        return FALSE;

    // record dwControlID
    m_strWaveLineName = mxl.szName;
    m_strMeterControlName = mxc.szName;
    m_lMinimum = mxc.Bounds.lMinimum;
    m_lMaximum = mxc.Bounds.lMaximum;
    m_dwMeterControlID = mxc.dwControlID;

    return TRUE;
}

BOOL CSoundCtrl::amdGetMeterValue(LONG &lVal) const
{
    if (m_hMixer == NULL ||	m_strWaveLineName.IsEmpty() || m_strMeterControlName.IsEmpty())
        return FALSE;

    MIXERCONTROLDETAILS_SIGNED mxcdMeter = {0};
    MIXERCONTROLDETAILS mxcd = {0};
    mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
    mxcd.dwControlID = m_dwMeterControlID;
    mxcd.cChannels = 1;
    mxcd.cMultipleItems = 0;
    mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_SIGNED);
    mxcd.paDetails = &mxcdMeter;
    if (::mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE)
        != MMSYSERR_NOERROR)
        return FALSE;

    lVal = mxcdMeter.lValue;

    return TRUE;
}

BOOL CSoundCtrl::amdSetMeterValue(LONG lVal) const
{
    if (m_hMixer == NULL ||	m_strWaveLineName.IsEmpty() || m_strMeterControlName.IsEmpty())
        return FALSE;

    MIXERCONTROLDETAILS_SIGNED mxcdMeter;
    mxcdMeter.lValue = lVal;
    MIXERCONTROLDETAILS mxcd;
    mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
    mxcd.dwControlID = m_dwMeterControlID;
    mxcd.cChannels = 1;
    mxcd.cMultipleItems = 0;
    mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_SIGNED);
    mxcd.paDetails = &mxcdMeter;

    if (::mixerSetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE)
        != MMSYSERR_NOERROR)
        return FALSE;

    return TRUE;
}