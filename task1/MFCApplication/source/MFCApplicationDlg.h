// MFCApplicationDlg.h: 정리된 헤더 파일
#include "MyCustomWnd.h" // 사용자 정의 윈도우 헤더 포함
#pragma once

// CMFCApplicationDlg 대화 상자
class CMFCApplicationDlg : public CDialogEx
{
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonRandom();
	afx_msg void OnEnChangeEditThickness();

private:
	int m_lineThickness = 1; // 선 두께 기본값 (1px)

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	MyCustomWnd m_customWnd; // 사용자 정의 윈도우 멤버 변수 추가

	// 메시지 맵
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticThicknessLabel();
};
