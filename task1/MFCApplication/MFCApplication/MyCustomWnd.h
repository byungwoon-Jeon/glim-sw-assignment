// MyCustomWnd.h: 사용자 정의 윈도우 헤더 파일

#pragma once
#include <vector>
#include <afxwin.h>
#include <thread>
#include <atomic>

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
    void StartRandomMoveThread();
    bool IsMovingRandomly() const { return m_isMovingRandomly; }
    size_t GetPointCount() const { return m_points.size(); }

protected:
    DECLARE_MESSAGE_MAP()

    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);


private:
    std::vector<CPoint> m_points;
    bool m_isDragging = false;
    int m_dragIndex = -1;
    int m_lineThickness = 1;

    void DrawCircle(HDC hdc, const CPoint& point, int radius, COLORREF color);
    void DrawCircumcircle(HDC hdc);

    // 스레드 관련 멤버 변수
    std::atomic<bool> m_isMovingRandomly{ false };
    std::thread m_randomMoveThread;

    void RandomMoveWorker(); // 스레드 함수
};