#pragma once

template <class T>
class CProxy_IShowImageEvents : public IConnectionPointImpl<T, &__uuidof(_IShowImageEvents), CComDynamicUnkArray>
{
	//警告此类将由向导重新生成。
public:

	HRESULT Fire_OpenFile(BSTR bstrFileName)
	{
		HRESULT hr = S_OK;
		T * pThis = static_cast<T *>(this);
		int nConnections = m_vec.GetSize();

		for (int iConnection = 0; iConnection < nConnections; iConnection++)
		{
			pThis->Lock();
			CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
			pThis->Unlock();

			IDispatch * pConnection = static_cast<IDispatch *>(punkConnection.p);

			if (pConnection)
			{
				CComVariant varResult;
				CComVariant avarParams[1];
				avarParams[0].vt = VT_BSTR;
				avarParams[0].bstrVal = bstrFileName;
				DISPPARAMS params = { avarParams, NULL, 1, 0 };

				hr = pConnection->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, &varResult, NULL, NULL);
			}
		}
		return E_NOTIMPL;
	}
};
