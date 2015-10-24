
#pragma once
#include "Network/Srv.h"
//#include "AV/AVProcess.h"

class CDlg_AV;

namespace XT_IOCP
{

	class CSrv_AV : public CSrv
	{
	public:
		CSrv_AV(void);
		~CSrv_AV(void);

	private:
		CDlg_AV   *m_pDlg;
		//CAVProcess m_AVProcess;
		DWORD      m_dwAVChannId;

		enum {AUDIO = 1, VIDEO, VIDEO_BIG};

		void ProcessPack(void *client, void *buf, int len, int ip, short port);

	public:
		int  Init(CDlg_AV *pDlg);
		int  Start(void);
		void Stop(void);

		void StartTest(void);
		void StopTest(void);
	};

}