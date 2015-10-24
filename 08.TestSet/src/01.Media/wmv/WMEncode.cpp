// WMEncode.cpp : 实现文件
//

#include "stdafx.h"
#include "WMEncode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//-------------------------------------------------------------------------

unsigned CWMEncode::ChannelDataThread(LPVOID lpVoid)
{
	CWMEncode *pthis = (CWMEncode*)lpVoid;

	WMENC_ENCODER_STATE enumCurState = WMENC_ENCODER_STOPPED;
	WMENC_ENCODER_STATE enumPrvState = WMENC_ENCODER_STOPPED;

	while(1)
	{
		Sleep(1);
		enumPrvState = enumCurState;
		enumCurState = pthis->m_EventSink.State();
		if (pthis->m_EventSink.SrcState() == WMENC_SOURCE_STOP)
			enumCurState = WMENC_ENCODER_STOPPED;

		if (enumCurState != enumPrvState)
		{
			switch (enumCurState)
			{
			case WMENC_ENCODER_STARTING:
				// TODO: Handle encoder starting state.
				//	AfxMessageBox(_T("WMENC_ENCODER_STARTING"));
				break;

			case WMENC_ENCODER_RUNNING:

				// TODO: Handle encoder running state.
				//	AfxMessageBox(_T("WMENC_ENCODER_RUNNING"));
				break;

			case WMENC_ENCODER_PAUSING:
				// TODO: Handle encoder pausing state.
				break;

			case WMENC_ENCODER_PAUSED:
				// TODO: Handle encoder paused state.
				break;

			case WMENC_ENCODER_STOPPING:
				// TODO: Handle encoder stopping state.
				break;

			case WMENC_ENCODER_STOPPED:
				// TODO: Handle encoder stopped state.
				// Goto EXIT;
				AfxMessageBox(_T("WMENC_ENCODER_STOPPED"));
				break;
			case WMENC_ENCODER_END_PREPROCESS:
				// TODO: Handle encoder end preprocess state.
				break;
			}
		}
		Sleep(1);
	}
	return 0;
}


CWMEncode::CWMEncode()
	:m_pcbbAudioDev(NULL),
	m_pcbbVideoDev(NULL),
	m_pcbbProfile(NULL),
	m_hPreViewWnd(NULL),
	m_hPostViewWnd(NULL)
{
}

CWMEncode::~CWMEncode()
{
}

bool CWMEncode::Init(CComboBox *pcbbAudioDev,
					 CComboBox *pcbbVideoDev,
					 CComboBox *pcbbProfile,
					 HWND hPreViewWnd,
					 HWND hPostViewWnd)
{
	m_pcbbAudioDev = pcbbAudioDev;
	m_pcbbVideoDev = pcbbVideoDev;
	m_pcbbProfile = pcbbProfile;
	m_hPreViewWnd = hPreViewWnd;	
	m_hPostViewWnd = hPostViewWnd;

	if (m_pcbbAudioDev && m_pcbbVideoDev && m_pcbbProfile)
		return true;
	else
		return false;
}
void CWMEncode::GetParam(void)
{
	HRESULT hr = S_OK;	
	IWMEncoder* pEncoder = NULL;
	IWMEncoder2* pEncoder2 = NULL;
	IWMEncProfileCollection* pProColl = NULL;
	IWMEncProfile* pPro;
	long lProfileCount = 0;

	try
	{
		// Initialize the COM library and retrieve a pointer
		// to an IWMEncoder interface.
		hr = CoInitialize(NULL);

		if (SUCCEEDED(hr))
		{
			hr = CoCreateInstance(CLSID_WMEncoder,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_IWMEncoder,
				(void**) &pEncoder);
		}

		// Retrieve a pointer to an IWMEncProfileCollection interface.
		if (SUCCEEDED(hr))
		{
			hr = pEncoder->get_ProfileCollection(&pProColl);
		}

		// Loop through the profile collection and retrieve a specific profile.
		CString strName;
		CComBSTR bstrName(L"");

		if (SUCCEEDED(hr))
		{
			hr = pProColl->get_Count(&lProfileCount);
		}

		for (long i = 0; i < lProfileCount; i++)
		{
			if (SUCCEEDED(hr))
			{
				hr = pProColl->Item(i, &pPro);
			}
			if (SUCCEEDED(hr))
			{
				hr = pPro->get_Name(&bstrName);
			}

			if (NULL != m_pcbbProfile)
				m_pcbbProfile->InsertString(i, (CString)bstrName);
			TRACE(strName + _T("\n"));
		}

		if (NULL != pEncoder)
			pEncoder->Release();

		if (NULL != pProColl)
			pProColl->Release();

		//--------------------------------------------------------------------

		hr = CoCreateInstance(CLSID_WMEncoder,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWMEncoder2,
			(void**) &pEncoder2);

		IWMEncSourcePluginInfoManager* pSrcPlugMgr = NULL;
		IWMEncPluginInfo* pPlugInfo = NULL;

		if (SUCCEEDED(hr))
		{
			hr = pEncoder2->get_SourcePluginInfoManager(&pSrcPlugMgr);
		}

		CComBSTR sDeviceName;
		CComBSTR sScheme;
		CComBSTR sResrcName;
		CString strDeviceName;
		VARIANT_BOOL bResources;
		long lDeviceCount = 0;
		long lResrcCount = 0;

		// Loop through all the audio and video devices on the system.
		if (SUCCEEDED(hr))
		{
			hr = pSrcPlugMgr->get_Count(&lDeviceCount);
		}

		for (long i = 0; i < lDeviceCount; i++)
		{
			// Set the IWMEncPluginInfo object to the current plug-in.
			if (SUCCEEDED(hr))
			{
				hr = pSrcPlugMgr->Item(i, &pPlugInfo);
			}		

			if (SUCCEEDED(hr))
			{
				hr = pPlugInfo->get_Name(&sDeviceName);

				strDeviceName = (CString)sDeviceName;
				TRACE((CString)strDeviceName + _T("\n"));
			}		

			// Find the plug-ins that support resources.
			if (SUCCEEDED(hr))
			{
				hr = pPlugInfo->get_SchemeType(&sScheme);
			}

			if (_wcsicmp(sScheme, CComBSTR(L"DEVICE"))==0)
			{
				// Find the devices.
				if (SUCCEEDED(hr))
				{
					hr = pPlugInfo->get_Resources(&bResources);
				}
				if (bResources == VARIANT_TRUE)
				{
					// Loop through the resources in the current plug-in.
					if (SUCCEEDED(hr))
					{
						hr = pPlugInfo->get_Count(&lResrcCount);
					}
					for (long j = 0; j < lResrcCount; j++)
					{
						// Display the name of the plug-in.
						if (SUCCEEDED(hr))
						{
							hr = pPlugInfo->Item(j, &sResrcName);
						}

						if (strDeviceName.Find(_T("音频"), 0) >= 0)
						{
							if (NULL != m_pcbbAudioDev)
								m_pcbbAudioDev->InsertString(j, (CString)sResrcName);
						}
						else if (strDeviceName.Find(_T("视频"), 0) >= 0)
						{
							if (NULL != m_pcbbVideoDev)
								m_pcbbVideoDev->InsertString(j, (CString)sResrcName);
						}

						TRACE((CString)sResrcName + _T("\n"));
					}
				}
			}

			if (NULL != pPlugInfo)
				pPlugInfo->Release();

		}// end for

		if (NULL != pEncoder2)
			pEncoder2->Release();

		if (NULL != pSrcPlugMgr)
			pSrcPlugMgr->Release();

		if (NULL != m_pcbbAudioDev)
			m_pcbbAudioDev->AddString(_T("从文件输入"));

		if (NULL != m_pcbbVideoDev)
		{
			m_pcbbVideoDev->AddString(_T("从文件输入"));
			m_pcbbVideoDev->AddString(_T("屏幕"));
		}
	}
	catch (...)
	{
		TRACE(_T("GetParam Error\n"));
	}
}

void CWMEncode::StartCaption(const CString &strVideoDevName,
							 const CString &strAudioDevName,
							 int nProfileId,
							 int nPort/* = 0*/,
							 const CString &strVideoFile/* = _T("")*/,
							 const CString &strAudioFile/* = _T("")*/,
							 const CString &strOutFileName/* = _T("")*/)
{
	IWMEncoder* pEncoder = NULL;
	IWMEncSourceGroupCollection* pSrcGrpColl = NULL;	// 流源组集合
	IWMEncSourceGroup* pSrcGrp = NULL;					// 流源组
	IWMEncSource* pAudSrc1 = NULL;						// Audio流源
	IWMEncSource* pSrc1 = NULL;							// Video流源
	IWMEncVideoSource* pVidSrc1 = NULL;
	IWMEncProfileCollection* pProColl = NULL;
	IWMEncProfile2* pPro = NULL;
	WMENC_ENCODER_STATE enumEncoderState;
	HRESULT hr = S_OK;
	CComBSTR bstrResource(L"");	
	long lCount = 0;	
	short i = 0;

	try
	{
		hr = ::CoInitialize(NULL);	//初始化com库
		
		hr = ::CoCreateInstance(CLSID_WMEncoder,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWMEncoder,
			(void**) &pEncoder);

		if ( ! SUCCEEDED(hr))
		{
			return;
		}

		if (SUCCEEDED(hr))			// 设置连接点
		{
			hr = m_EventSink.Init(pEncoder);
		}

		// Retrieve a pointer to an IWMEncSourceGroupCollection	interface.	
		if (SUCCEEDED(hr))
		{
			hr = pEncoder->get_SourceGroupCollection(&pSrcGrpColl);
		}

		// Add a source group to the collection. named "SG_1"
		if (SUCCEEDED(hr))
		{
			hr = pSrcGrpColl->Add(CComBSTR(L"SG_1"), &pSrcGrp);
		}

		// Add a video and audio source to the source group.
		if (SUCCEEDED(hr))
		{
			hr = pSrcGrp->AddSource(WMENC_VIDEO, &pSrc1);
			hr = pSrcGrp->AddSource(WMENC_AUDIO, &pAudSrc1);
		}

		// Retrieve a pointer to an IWMEncVideoSource interface.
		if (SUCCEEDED(hr))
		{
			hr = pSrc1->QueryInterface(IID_IWMEncVideoSource, (void**)&pVidSrc1);
		}

		//-------------------------------------------------------------------
		// 音频源

		if (strAudioDevName.Find(_T("文件")) > 0)
		{
			hr = pAudSrc1->SetInput(strAudioFile.AllocSysString());
		}
		else
		{
			CComBSTR Aud(L"DEVICE://");
			Aud.Append(strAudioDevName.AllocSysString());

			hr = pAudSrc1->SetInput(Aud);		// 设置声音的输入
		}

		//-------------------------------------------------------------------
		// 视频源

		if (strVideoDevName.Find(_T("文件")) > 0)
		{
			hr = pVidSrc1->SetInput(strVideoFile.AllocSysString());
		}
		else if (strVideoDevName.Compare(_T("屏幕")) == 0)
		{
			hr = pVidSrc1->SetInput(L"ScreenCap://Screen Capture");
		}
		else
		{
			CComBSTR Vid(L"DEVICE://");
			Vid.Append(strVideoDevName.AllocSysString());

			hr = pVidSrc1->SetInput(Vid);		// 设置视频的输入
		}

		// Choose a profile from the collection.
		if (SUCCEEDED(hr))
		{
			hr = pEncoder->get_ProfileCollection(&pProColl);
		}

		if (SUCCEEDED(hr))
		{
			hr = pProColl->Item(nProfileId, (struct IWMEncProfile **)&pPro);
		}

		//CComBSTR bstrName = NULL;
		CComVariant varProfile;
		varProfile.vt = VT_DISPATCH;	
		varProfile.pdispVal = pPro;

		if (SUCCEEDED(hr))
		{
			hr = pSrcGrp->put_Profile(varProfile);
		}

		if (NULL != pProColl)
			pProColl->Release();

		if (NULL != pPro)
			pPro->Release();

		/*----------------------------------------------------------------------
		varProfile1.vt = VT_DISPATCH;
		hr = CoCreateInstance(CLSID_WMEncProfile2,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWMEncProfile2,
		(void**) &pPro2);


		if ( SUCCEEDED( hr ) )
		{
		hr = pPro2->put_ValidateMode(VARIANT_TRUE);
		}

		if ( SUCCEEDED( hr ) )
		{
		hr = pPro2->put_ContentType(16);
		}

		if ( SUCCEEDED( hr ) )
		{
		hr = pPro2->put_VBRMode(WMENC_VIDEO, 0, WMENC_PVM_NONE);
		}

		// Add audiences for 200, 400, and 600 Kbps.
		if ( SUCCEEDED( hr ) )
		{
		hr = pPro2->AddAudience(200000, &pAudnc);
		}

		long lAudCount;

		if ( SUCCEEDED( hr ) )
		{
		hr = pPro2->get_AudienceCount(&lAudCount);
		}

		for (i = 0; i < lAudCount; i++)
		{
		if ( SUCCEEDED( hr ) )
		{
		hr = pPro2->get_Audience(i, &pAudnc);
		}
		// The Windows Media 9 codec is used by default, but you can change
		// it as follows. Be sure to make this change for each audience.

		// Make the video output size match the input size by setting the height and width to 0.
		if ( SUCCEEDED( hr ) )
		{
		hr = pAudnc->put_VideoHeight(0, 230);
		}
		if ( SUCCEEDED( hr ) )
		{
		hr = pAudnc->put_VideoWidth(0, 300);
		}

		// Change the buffer size to 5 seconds. By default, the end user's default setting is used.
		}

		varProfile1.pdispVal = pPro2;

		//	hr = pSrcGrp->put_Profile(varProfile1);
		*/

		//----------------------------------------------------------------------------
		// 描述信息

		IWMEncDisplayInfo* pDispInfo = NULL;

		// Retrieve a pointer to an IWMEncDisplayInfo interface.
		hr = pEncoder->get_DisplayInfo(&pDispInfo);

		// Describe the encoded content
		CComBSTR bstrAuthor(L"Let5fly");
		CComBSTR bstrCopyright(L"Copyright 2000. All rights reserved.");
		CComBSTR bstrDescription(L"Description of the encoded content.");
		CComBSTR bstrRating(L"Content rating.");
		CComBSTR bstrTitle(L"Test the Encoder");

		if (SUCCEEDED(hr))
		{
			hr = pDispInfo->put_Author(bstrAuthor);
			hr = pDispInfo->put_Copyright(bstrCopyright);
			hr = pDispInfo->put_Description(bstrDescription);
			hr = pDispInfo->put_Rating(bstrRating);
			hr = pDispInfo->put_Title(bstrTitle);
		}

		if (NULL != pDispInfo)
			pDispInfo->Release();

		//----------------------------------------------------------------------
		// 设置属性
		/*
		IWMEncAttributes* pAttr = NULL;

		// Retrieve a pointer to an IWMEncAttributes interface.	
		hr = pEncoder->get_Attributes(&pAttr);

		// Add an attribute to the attributes collection.	
		CComBSTR bstrAttrName(L"DateCreated: ");
		CComVariant varValue;

		varValue.vt = VT_BSTR;	
		//varValue.bstrVal = _T("09/15/2008");
		varValue.bstrVal = BSTR(_T("02/15/2000"));

		hr = pAttr->Add(bstrAttrName,varValue);	
		*/
		//-----------------------------------------------------------------------------
		// 广播(拉传)

		if (nPort > 0)
		{
			IWMEncBroadcast* pBrdcast = NULL;

			// Retrieve a pointer to an IWMEncBroadcast interface.	
			hr = pEncoder->get_Broadcast(&pBrdcast);

			// Specify a port number and a protocol.	
			hr = pBrdcast->put_PortNumber(WMENC_PROTOCOL_HTTP, nPort); //设定广播端口

			//-----------------------------------------------------------------------------
			/* 推传
			if (SUCCEEDED(hr))
			{
			hr = pBrdcast->QueryInterface(IID_IWMEncPushDistribution, (void**)&pPushDist);
			}

			CComBSTR strServerName(_T("127.0.0.1"));
			CComBSTR strPubPoint(_T("Bruce"));

			if (SUCCEEDED(hr))
			{
			hr = pPushDist->put_ServerName(strServerName);
			}

			if (SUCCEEDED(hr))
			{
			hr = pPushDist->put_PublishingPoint(strPubPoint);
			}
			*/

			if (NULL != pBrdcast)
				pBrdcast->Release();
		}

		//-----------------------------------------------------------------------------
		// 输出为文件

		if (strOutFileName.GetLength() > 0)
		{
			IWMEncFile* pFile = NULL;

			// Retrieve a pointer to an IWMEncFile interface.	
			hr = pEncoder->get_File(&pFile);

			// Specify a file in which to save encoded content.	
			hr = pFile->put_LocalFileName(strOutFileName.AllocSysString());	//存储编码后的文件

			if (NULL != pFile)
				pFile->Release();
		}

		//-----------------------------------------------------------------------------
		// 显示编码前的视频

		long lCookiePreview = -1;	
		long lCookiePostview = -1;

		IWMEncDataViewCollection* pPreviewColl = NULL;
		IWMEncDataViewCollection* pPostviewColl = NULL;

		IWMEncDataView* pPreview = NULL;
		IWMEncDataView* pPostview = NULL;	

		// Retrieve a pointer to a preview object.	
		hr = CoCreateInstance(CLSID_WMEncPreview,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWMEncDataView,
			(void**)&pPreview);

		hr = CoCreateInstance(CLSID_WMEncPreview,	
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWMEncDataView,
			(void**)&pPostview);

		// Retrieve the preview collection.	
		if (SUCCEEDED(hr))
		{
			hr = pSrc1->get_PreviewCollection(&pPreviewColl);
			//hr = pSrc1->get_PostviewCollection(&pPostviewColl);
		}

		// Add the postiew object to the data view collection. If you set the
		// cookie to -1, the encoder engine automatically generates a unique	
		// cookie.

		if (SUCCEEDED(hr))
		{
			hr = pPreviewColl->Add(pPreview, &lCookiePreview);	
			//hr = pPostviewColl->Add(pPostview, &lCookiePostview);
		}

		// Continue configuring the encoder engine.	
		if (SUCCEEDED(hr))
		{
			hr = pEncoder->PrepareToEncode(VARIANT_TRUE);
		}

		if (SUCCEEDED(hr))
		{
			hr = pPreview->SetViewSetting((DWORD)lCookiePreview, sizeof(m_hPreViewWnd), (BYTE*)&m_hPreViewWnd);
			//hr = pPostview->SetViewSetting((DWORD)lCookiePostview, sizeof(m_hPostViewWnd), (BYTE*)&m_hPostViewWnd);
		}

		hr = pEncoder->Start();

		if (SUCCEEDED(hr))
		{		
			hr = pPreview->Start(lCookiePreview);
			//hr = pPostview->Start(lCookiePostview);
		}

		// Wait until the engoder engine stops before exiting the application.	
		// You can do this by using the _IWMEncoderEvents object to create an	
		// event sink.

		hr = pEncoder->get_RunState(&enumEncoderState); //得到运行状态

		UINT  nThreadId;
		HANDLE hThreadHandle;
		hThreadHandle = (HANDLE)_beginthreadex(NULL, 0, ChannelDataThread, this, 0, &nThreadId);
	}
	catch (...)
	{
		TRACE(_T("StartCaption Error\n"));
	}
}


void CWMEncode::SaveProfile(const CString &strFileName)
{	
	IWMEncoder2* pEncoder = NULL;
	IWMEncProfileCollection* pProColl = NULL;
	IWMEncProfile* pPro1 = NULL;
	IWMEncProfile2* pPro2 = NULL;
	IWMEncAudienceObj* pAudnc = NULL;
	CComBSTR bstrName;
	CComBSTR bstrDir;
	HRESULT hr = NULL;	
	long lCount = 0;

	// Initialize the COM library and retrieve a pointer
	// to an IWMEncoder interface.
	hr = CoInitialize(NULL);
	if ( SUCCEEDED( hr ) )
	{
		hr = CoCreateInstance(CLSID_WMEncoder,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWMEncoder2,
			(void**) &pEncoder);
	}

	// Retrieve an existing profile to modify.
	hr = pEncoder->get_ProfileCollection(&pProColl);	
	hr = pProColl->get_Count(&lCount);

	for (long i = 0; i < lCount; i++)
	{
		hr = pProColl->Item(i, &pPro1);
		hr = pPro1->get_Name(&bstrName);
		if (_wcsicmp(bstrName,CComBSTR(L"Windows Media Video 8 for Local Area Network (384 Kbps)"))==0)
		{
			break;
		}
	}

	// Create the WMEncProfile2 object.
	if ( SUCCEEDED( hr ) )
	{
		hr = CoCreateInstance(CLSID_WMEncProfile2,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWMEncProfile2,
			(void**) &pPro2);
	}

	pProColl->get_ProfileDirectory(&bstrDir);
	// Load the profile.
	hr = pPro2->LoadFromIWMProfile(pPro1);
	pPro2->put_ProfileName(CComBSTR(L"GXD Sample MBR Profile"));

	// Add support for interlace mode.
	hr = pPro2->put_InterlaceMode(0, VARIANT_TRUE); 

	// For each audience in the profile, set the height and width of the video
	// output to match the original input size, rather than the values
	// predetermined in the profile, by setting the height and width to 0.
	long lAudCount = 0; 
	hr = pPro2->get_AudienceCount(&lAudCount); 
	for (long i = 0; i < lAudCount; i++)
	{
		// Set the current audience into the IWMEncAudience object.
		hr = pPro2->get_Audience(i, &pAudnc); 
		hr = pAudnc->put_VideoHeight(0, 0); 
		hr = pAudnc->put_VideoWidth(0, 0); 
	}

	// Save changes to a new file or save over the existing profile.
	hr = pPro2->SaveToFile(strFileName.AllocSysString()); // REPLACE WITH PATH AND FILENAME

	// Release pointers.
	if (pProColl)
	{
		pProColl->Release();
		pProColl = NULL;
	}

	if (pPro1)
	{
		pPro1->Release();
		pPro1 = NULL;
	}

	if (pPro2)
	{
		pPro2->Release();
		pPro2 = NULL;
	}

	if (pAudnc)
	{
		pAudnc->Release();
		pAudnc = NULL;
	}

	if (pEncoder)
	{
		pEncoder->Release();
		pEncoder = NULL;
	}
}

void CWMEncode::Test(void)
{
	HRESULT hr;
	IWMEncoder* pEncoder;
	IWMEncSourceGroupCollection* pSrcGrpColl;
	IWMEncSourceGroup* pSrcGrp;
	IWMEncSource* pSrc;
	IWMEncSource* pSrcAud;
	IWMEncVideoSource2* pSrcVid;
	IWMEncInputCollection* pInputColl;
	int i;

	// Initialize the COM library and retrieve a pointer to an IWMEncoder interface.
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_WMEncoder,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWMEncoder,
			(void**) &pEncoder);
	}

	// Retrieve the source group collection.
	if (SUCCEEDED(hr))
	{
		hr = pEncoder->get_SourceGroupCollection(&pSrcGrpColl);
	}

	// Add a source group to the collection.
	if (SUCCEEDED(hr))
	{
		hr = pSrcGrpColl->Add(CComBSTR(L"SG_1"), &pSrcGrp);
	}
	if (SUCCEEDED(hr))
	{
		hr = pSrcGrp->AddSource(WMENC_AUDIO, &pSrcAud);
	}
	if (SUCCEEDED(hr))
	{
		hr = pSrcGrp->AddSource(WMENC_VIDEO, &pSrc);
	}

	// Retrieve an IWMEncVideoSource2 pointer.
	if (SUCCEEDED(hr))
	{
		hr = pSrc->QueryInterface(IID_IWMEncVideoSource2, (void**)&pSrcVid);
	}

	// Add a video and audio source to the source group.
	if (SUCCEEDED(hr))
	{
		hr = pSrcAud->SetInput(CComBSTR(L"Device://SoundMAX Digital Audio"));
	}
	if (SUCCEEDED(hr))
	{
		hr = pSrcVid->SetInput(CComBSTR(L"Device://TridVid Capture"));
	}


	// Configure the output and profile for the encoding session.

	// Initialize the encoding session.
	if (SUCCEEDED(hr))
	{
		hr = pEncoder->PrepareToEncode(VARIANT_TRUE);
	}

	// Enumerate the type of inputs supported by the TV-tuner capture card.
	// Find and select the Video Tuner input.
	if (SUCCEEDED(hr))
	{
		hr = pSrcVid->EnumerateInputs(&pInputColl);
	}

	long lCount; 
	if (SUCCEEDED(hr))
	{
		hr = pInputColl->get_Count(&lCount);
	}

	CComBSTR sInput; 
	for (i = 0;  i < lCount; i++)
	{
		hr = pInputColl->Item(i, &sInput);
		if (sInput == L"Video Tuner")
		{
			if (SUCCEEDED(hr))
			{
				hr = pSrcVid->put_Input(i);
			}
			break;
		}
	}

	// Specify the TV channel, pixel format, and country/region code (USA).
	if (SUCCEEDED(hr))
	{
		hr = pSrcVid->put_Channel(5);
	}
	if (SUCCEEDED(hr))
	{
		hr = pSrcVid->put_PixelFormat(WMENC_PIXELFORMAT_UYVY);
	}
	if (SUCCEEDED(hr))
	{
		hr = pSrcVid->put_Country(1);
	}

	// Specify cable reception.
	if (SUCCEEDED(hr))
	{
		hr = pSrcVid->put_TVType(0);
	}

	// Specify the NTSC TV format.
	if (SUCCEEDED(hr))
	{
		hr = pSrcVid->put_TVFormat(1);
	}

	// Start the encoding process.
	if (SUCCEEDED(hr))
	{
		hr = pEncoder->Start();
	}

	// Release pointers.
	if (pSrcGrpColl)
	{
		pSrcGrpColl->Release();
		pSrcGrpColl = NULL;
	}
	if (pSrcGrp)
	{
		pSrcGrp->Release();
		pSrcGrp = NULL;
	}
	if (pSrcAud)
	{
		pSrcAud->Release();
		pSrcAud = NULL;
	}
	if (pSrcVid)
	{
		pSrcVid->Release();
		pSrcVid = NULL;
	}
	if (pSrc)
	{
		pSrc->Release();
		pSrc = NULL;
	}
	if (pInputColl)
	{
		pInputColl->Release();
		pInputColl = NULL;
	}
	if (pEncoder)
	{
		pEncoder->Release();
		pEncoder = NULL;
	}
}
