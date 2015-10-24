#pragma once


//--------------------------------------------------------------------------------
// 可能出现错误，只要点击继承就可以，最好用unicode编码方式
// 将此代码移到其它VS2003工程下没有问题

#include <windows.h>
#include <atlbase.h>
#include <comdef.h>
extern CComModule _Module;
#include <atlcom.h>

enum WMENC_DEVICECONTROL_STATE;

#include "WMEncSDK9\wmencode.h"
#include "WMEncSDK9\wmdevctl.h"
#include "WMEncSDK9\wmencvu.h"
#include "WMEncSDK9\WMSEncid.h"

#define EVENT_ID        100
#define LIB_VERMAJOR    1
#define LIB_VERMINOR    0

class CCallBack : public IDispEventImpl< EVENT_ID, 
	CCallBack,
	&DIID__IWMEncoderEvents,
	&LIBID_WMEncoderLib,
	LIB_VERMAJOR, 
	LIB_VERMINOR >
{
private:
	WMENC_ENCODER_STATE m_enumState;
	WMENC_SOURCE_STATE  m_enumSrcState;

public:
	// Define the event sink map which determines the events
	// that the application receives.
	BEGIN_SINK_MAP( CCallBack )
		SINK_ENTRY_EX( EVENT_ID, 
		DIID__IWMEncoderEvents,
		DISPID_ENCODEREVENT_STATECHANGE,
		OnStateChange )
		SINK_ENTRY_EX( EVENT_ID,
		DIID__IWMEncoderEvents,
		DISPID_ENCODEREVENT_SRCSTATECHANGE,
		OnSourceStateChange )
	END_SINK_MAP()

	// Implement the event handler for the OnStateChange event.
	STDMETHOD( OnStateChange )( WMENC_ENCODER_STATE enumState )
	{
		m_enumState = enumState;
		return S_OK;
	}

	// Implement the event handler for the OnSourceStateChange event.
	STDMETHOD( OnSourceStateChange )( WMENC_SOURCE_STATE enumState,
		WMENC_SOURCE_TYPE enumType,
		short iIndex,
		BSTR bstrSourceGroup )
	{
		m_enumSrcState = enumState;
		return S_OK;
	}

	// Override the base class virtual function to provide information
	// on the implemented event handlers.
	HRESULT GetFuncInfoFromId( const IID& iid, DISPID dispidMember,
		LCID lcid, _ATL_FUNC_INFO& info )
	{
		if( InlineIsEqualGUID( iid, DIID__IWMEncoderEvents ) )
		{
			info.cc = CC_STDCALL;
			info.vtReturn = VT_ERROR;
			switch( dispidMember )
			{
				// Descibe the parameters of the
				// OnStateChange event handler.
			case DISPID_ENCODEREVENT_STATECHANGE:
				info.nParams = 1;
				info.pVarTypes[0] = VT_I4;
				return S_OK;

				// Describe the parameters of the
				// OnSourceStateChange event handler.
			case DISPID_ENCODEREVENT_SRCSTATECHANGE:
				info.nParams = 4;
				info.pVarTypes[0] = VT_I4;
				info.pVarTypes[1] = VT_I4;
				info.pVarTypes[2] = VT_I2;
				info.pVarTypes[3] = VT_BSTR;
				return S_OK;

			default:
				return E_FAIL;
			}
		}
		return E_FAIL;
	}

	// Link the events to the encoder instance.
	HRESULT CCallBack::Init( IWMEncoder* pEncoder )
	{
		if( pEncoder == NULL )
			return E_FAIL;

		HRESULT hr = DispEventAdvise( pEncoder );
		if( FAILED( hr ) ) 
		{
			// TODO: Handle failure condition.
		}
		return hr;
	}

	// Detach the event sink from the encoder instance.
	HRESULT CCallBack::Shutdown( IWMEncoder* pEncoder )
	{
		if( pEncoder == NULL )
			return E_FAIL;

		HRESULT hr = DispEventUnadvise( pEncoder );
		if( FAILED( hr ) ) 
		{
			// TODO: Handle failure condition.
		}
		return hr;
	}

	// Private member variable access functions.
	WMENC_ENCODER_STATE State() { return m_enumState; }
	WMENC_SOURCE_STATE SrcState() { return m_enumSrcState; }

	CCallBack() { _asm nop }
};

//--------------------------------------------------------------------------------

class CWMEncode
{
public:
	CWMEncode();           // 动态创建所使用的受保护的构造函数
	virtual ~CWMEncode();

private:
	CComboBox			*m_pcbbAudioDev;
	CComboBox			*m_pcbbVideoDev;
	CComboBox			*m_pcbbProfile;
	HWND				m_hPreViewWnd;
	HWND				m_hPostViewWnd;

	CCallBack			m_EventSink;

public:
	bool Init(			CComboBox *pcbbAudioDev,
						CComboBox	*pcbbVideoDev,
						CComboBox *pcbbProfile,
						HWND hPreViewWnd,
						HWND hPostViewWnd
						);

	void GetParam(void);

	void StartCaption(	const CString &strVideoDevName,
						const CString &strAudioDevName,
						int nProfileId,
						int nPort = 0,
						const CString &strVideoFile = _T(""),
						const CString &strAudioFile = _T(""),
						const CString &strOutFileName = _T("")
						);

	void SaveProfile(const CString &strFileName);

	void Test(void);

	static unsigned __stdcall ChannelDataThread(LPVOID lpVoid);
};
