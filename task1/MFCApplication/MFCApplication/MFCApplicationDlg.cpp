// MFCApplicationDlg.cpp: 구현 파일

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"
#include "MyCustomWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplicationDlg 대화 상자

CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_RESET, &CMFCApplicationDlg::OnBnClickedButtonReset)
    ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CMFCApplicationDlg::OnBnClickedButtonRandom)
    ON_EN_CHANGE(IDC_EDIT_THICKNESS, &CMFCApplicationDlg::OnEnChangeEditThickness)
END_MESSAGE_MAP()

// [초기화] 버튼 클릭 이벤트
void CMFCApplicationDlg::OnBnClickedButtonReset()
{
    CWnd* pCustomWnd = GetDlgItem(1234);
    if (pCustomWnd)
    {
        ((MyCustomWnd*)pCustomWnd)->ResetPoints();
    }

    // 좌표 표시 초기화
    GetDlgItem(IDC_STATIC_COORD1)->SetWindowText(_T(""));
    GetDlgItem(IDC_STATIC_COORD2)->SetWindowText(_T(""));
    GetDlgItem(IDC_STATIC_COORD3)->SetWindowText(_T(""));

    // 랜덤 이동 버튼 다시 활성화
    GetDlgItem(IDC_BUTTON_RANDOM)->EnableWindow(TRUE);
}
// [랜덤 이동] 버튼 클릭 이벤트
void CMFCApplicationDlg::OnBnClickedButtonRandom()
{
    CWnd* pCustomWnd = GetDlgItem(1234);
    if (pCustomWnd)
    {
        MyCustomWnd* pMyCustomWnd = (MyCustomWnd*)pCustomWnd;

        // 점의 개수가 3개가 아닌 경우 경고 메시지 출력
        if (pMyCustomWnd->GetPointCount() < 3)
        {
            AfxMessageBox(_T("랜덤 이동을 하려면 세 개의 점이 필요합니다!"));
            return;
        }

        // 이미 랜덤 이동 중이라면 중복 실행 방지
        if (pMyCustomWnd->IsMovingRandomly())
        {
            AfxMessageBox(_T("이미 랜덤 이동이 진행 중입니다!"));
            return;
        }

        pMyCustomWnd->StartRandomMoveThread();

        // 랜덤 이동 버튼 비활성화
        GetDlgItem(IDC_BUTTON_RANDOM)->EnableWindow(FALSE);
    }
}

// 선 두께 입력 이벤트
void CMFCApplicationDlg::OnEnChangeEditThickness()
{
    CString strThickness;
    GetDlgItem(IDC_EDIT_THICKNESS)->GetWindowText(strThickness);

    int thickness = _ttoi(strThickness);
    if (thickness > 0)
    {
        m_lineThickness = thickness;
        CWnd* pCustomWnd = GetDlgItem(1234);
        if (pCustomWnd)
        {
            ((MyCustomWnd*)pCustomWnd)->SetLineThickness(m_lineThickness);
        }
    }
}

// CMFCApplicationDlg 메시지 처리기

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 사용자 정의 윈도우 생성
	CRect rect(50, 50, 300, 300); // 다이얼로그 내 위치와 크기 설정
	m_customWnd.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, rect, this, 1234);

    // 버튼 크기 및 글꼴 설정
    CButton* pButtonReset = (CButton*)GetDlgItem(IDC_BUTTON_RESET);
    CButton* pButtonRandom = (CButton*)GetDlgItem(IDC_BUTTON_RANDOM);
    CWnd* pEditThickness = GetDlgItem(IDC_EDIT_THICKNESS);
    CWnd* pCoord1 = GetDlgItem(IDC_STATIC_COORD1);
    CWnd* pCoord2 = GetDlgItem(IDC_STATIC_COORD2);
    CWnd* pCoord3 = GetDlgItem(IDC_STATIC_COORD3);
    CWnd* pLabelThickness = GetDlgItem(IDC_STATIC_THICKNESS_LABEL);

    // 버튼 크기 및 위치 조정
    if (pButtonReset)
        pButtonReset->MoveWindow(600, 50, 100, 40);
    if (pButtonRandom)
        pButtonRandom->MoveWindow(710, 50, 100, 40);

    // 폰트 설정
    CFont* pFont = new CFont();
    pFont->CreatePointFont(120, _T("Segoe UI")); // 12pt 글꼴 설정

    // 버튼에 폰트 적용
    if (pButtonReset)
        pButtonReset->SetFont(pFont);
    if (pButtonRandom)
        pButtonRandom->SetFont(pFont);

    // 선 두께 입력창 및 텍스트 라벨 설정
    if (pLabelThickness)
    {
        pLabelThickness->MoveWindow(600, 100, 80, 30);
        pLabelThickness->SetFont(pFont);
    }

    if (pEditThickness)
    {
        pEditThickness->MoveWindow(700, 100, 100, 30);
        pEditThickness->SetFont(pFont);
    }

    // 좌표 표시 위치 및 폰트 설정
    if (pCoord1)
    {
        pCoord1->MoveWindow(600, 140, 200, 30);
        pCoord1->SetFont(pFont);
    }

    if (pCoord2)
    {
        pCoord2->MoveWindow(600, 180, 200, 30);
        pCoord2->SetFont(pFont);
    }

    if (pCoord3)
    {
        pCoord3->MoveWindow(600, 220, 200, 30);
        pCoord3->SetFont(pFont);
    }

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}