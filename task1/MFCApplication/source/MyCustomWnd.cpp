// MyCustomWnd.cpp: 사용자 정의 윈도우 구현 파일

#include "pch.h"
#include "MyCustomWnd.h"
#include <cmath>
#include "resource.h"

MyCustomWnd::MyCustomWnd() {}
MyCustomWnd::~MyCustomWnd() {}

BEGIN_MESSAGE_MAP(MyCustomWnd, CWnd)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BOOL MyCustomWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
    const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    RECT newRect = { rect.left, rect.top, rect.left + 500, rect.top + 500 };
    return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, newRect, pParentWnd, nID, pContext);
}

void MyCustomWnd::OnPaint()
{
    PAINTSTRUCT ps;
    HDC hdc = ::BeginPaint(m_hWnd, &ps);

    // 배경을 흰색으로 초기화
    ::FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    // 점에 색상 추가 (1번: 빨강, 2번: 파랑, 3번: 초록)
    COLORREF colors[3] = { RGB(255, 0, 0), RGB(0, 0, 255), RGB(0, 255, 0) };

    for (size_t i = 0; i < m_points.size(); ++i)
    {
        DrawCircle(hdc, m_points[i], 10, colors[i]);
    }

    if (m_points.size() == 3)
    {
        DrawCircumcircle(hdc); // 세 점을 지나는 정원 그리기
    }

    ::EndPaint(m_hWnd, &ps);
}

void MyCustomWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_points.size() < 3)
    {
        m_points.push_back(point);
        Invalidate();
        UpdateCoordinateDisplay(); // 좌표 자동 갱신
    }
    else
    {
        for (size_t i = 0; i < m_points.size(); ++i)
        {
            CRect rect(m_points[i].x - 10, m_points[i].y - 10, m_points[i].x + 10, m_points[i].y + 10);
            if (rect.PtInRect(point))
            {
                m_isDragging = true;
                m_dragIndex = static_cast<int>(i);
                break;
            }
        }
    }
    CWnd::OnLButtonDown(nFlags, point);
}

void MyCustomWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_isDragging && (nFlags & MK_LBUTTON))
    {
        m_points[m_dragIndex] = point;
        Invalidate();
        UpdateCoordinateDisplay(); // 좌표 자동 갱신
    }
    CWnd::OnMouseMove(nFlags, point);
}

void MyCustomWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_isDragging = false;
    m_dragIndex = -1;
    CWnd::OnLButtonUp(nFlags, point);
}

void MyCustomWnd::DrawCircle(HDC hdc, const CPoint& point, int radius, COLORREF color)
{
    HBRUSH hBrush = ::CreateSolidBrush(color);
    HGDIOBJ hOldBrush = ::SelectObject(hdc, hBrush);

    HPEN hPen = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 검정 테두리
    HGDIOBJ hOldPen = ::SelectObject(hdc, hPen);

    ::Ellipse(hdc, point.x - radius, point.y - radius, point.x + radius, point.y + radius);

    ::SelectObject(hdc, hOldBrush);
    ::DeleteObject(hBrush);

    ::SelectObject(hdc, hOldPen);
    ::DeleteObject(hPen);
}

void MyCustomWnd::DrawCircumcircle(HDC hdc)
{
    if (m_points.size() < 3) return;

    const CPoint& A = m_points[0];
    const CPoint& B = m_points[1];
    const CPoint& C = m_points[2];

    int D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    if (D == 0) return; // 세 점이 일직선일 때

    int Ux = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
        (B.x * B.x + B.y * B.y) * (C.y - A.y) +
        (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;

    int Uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
        (B.x * B.x + B.y * B.y) * (A.x - C.x) +
        (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;

    int r = static_cast<int>(sqrt((Ux - A.x) * (Ux - A.x) + (Uy - A.y) * (Uy - A.y)));

    HPEN hPen = ::CreatePen(PS_SOLID, m_lineThickness, RGB(0, 0, 0));
    HGDIOBJ hOldPen = ::SelectObject(hdc, hPen);

    ::Ellipse(hdc, Ux - r, Uy - r, Ux + r, Uy + r);

    ::SelectObject(hdc, hOldPen);
    ::DeleteObject(hPen);
}

void MyCustomWnd::ResetPoints()
{
    m_points.clear(); // 모든 점 초기화
    Invalidate();
    UpdateCoordinateDisplay(); // 좌표 초기화
}

void MyCustomWnd::MovePointsRandomly()
{
    CRect rect;
    GetClientRect(&rect);

    int margin = 10; // 점이 화면 밖으로 나가지 않도록 여유 공간 설정

    for (auto& point : m_points)
    {
        point.x = margin + rand() % (rect.Width() - 2 * margin);
        point.y = margin + rand() % (rect.Height() - 2 * margin);
    }

    UpdateCoordinateDisplay(); // 좌표 표시 업데이트
    Invalidate(); // 화면 갱신
}


void MyCustomWnd::SetLineThickness(int thickness)
{
    m_lineThickness = thickness; // 선 두께 설정
    Invalidate(); // 화면 갱신
}

void MyCustomWnd::UpdateCoordinateDisplay()
{
    CWnd* pParent = GetParent(); // 부모 다이얼로그 참조
    if (!pParent) return;

    CString strCoord;
    const TCHAR* colorNames[3] = { _T("빨강 점"), _T("파랑 점"), _T("초록 점") };

    for (size_t i = 0; i < m_points.size(); ++i)
    {
        // 색상 이름을 사용해 좌표 표시
        strCoord.Format(_T("%s: X: %d, Y: %d"), colorNames[i], m_points[i].x, m_points[i].y);
        switch (i)
        {
        case 0: pParent->GetDlgItem(IDC_STATIC_COORD1)->SetWindowText(strCoord); break;
        case 1: pParent->GetDlgItem(IDC_STATIC_COORD2)->SetWindowText(strCoord); break;
        case 2: pParent->GetDlgItem(IDC_STATIC_COORD3)->SetWindowText(strCoord); break;
        }
    }

    // 빈 좌표 표시 초기화
    for (size_t i = m_points.size(); i < 3; ++i)
    {
        switch (i)
        {
        case 0: pParent->GetDlgItem(IDC_STATIC_COORD1)->SetWindowText(colorNames[0]); break;
        case 1: pParent->GetDlgItem(IDC_STATIC_COORD2)->SetWindowText(colorNames[1]); break;
        case 2: pParent->GetDlgItem(IDC_STATIC_COORD3)->SetWindowText(colorNames[2]); break;
        }
    }
}