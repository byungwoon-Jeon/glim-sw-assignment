// MyCustomWnd.h: 사용자 정의 윈도우 헤더 파일

#pragma once
#include <vector>
#include <afxwin.h>

class MyCustomWnd : public CWnd
{
public:
    MyCustomWnd();
    virtual ~MyCustomWnd();

    BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
        const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);

    // 추가된 멤버 함수 선언
    void ResetPoints();             // 초기화 기능
    void MovePointsRandomly();      // 랜덤 이동 기능
    void SetLineThickness(int thickness); // 선 두께 설정
    void UpdateCoordinateDisplay();

protected:
    DECLARE_MESSAGE_MAP()

    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
    std::vector<CPoint> m_points; // 클릭한 위치 저장
    bool m_isDragging = false;    // 드래그 중인지 여부
    int m_dragIndex = -1;         // 드래그 중인 원의 인덱스

    int m_lineThickness = 1; // 추가: 선 두께 멤버 변수

    void DrawCircle(HDC hdc, const CPoint& point, int radius, COLORREF color);
    void DrawCircumcircle(HDC hdc);
};