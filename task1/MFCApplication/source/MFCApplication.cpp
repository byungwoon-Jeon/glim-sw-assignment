// MFCApplication.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplicationApp

BEGIN_MESSAGE_MAP(CMFCApplicationApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CMFCApplicationApp 생성

CMFCApplicationApp::CMFCApplicationApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

// 유일한 CMFCApplicationApp 개체입니다.

CMFCApplicationApp theApp;

// CMFCApplicationApp 초기화

BOOL CMFCApplicationApp::InitInstance()
{
	CWinApp::InitInstance();
	CMFCApplicationDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// [확인] 버튼 클릭 시 처리 코드
	}
	else if (nResponse == IDCANCEL)
	{
		// [취소] 버튼 클릭 시 처리 코드
	}

	// 대화 상자가 닫혔으므로 응용 프로그램을 종료합니다.
	return FALSE;
}