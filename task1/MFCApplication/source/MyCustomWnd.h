// MyCustomWnd.h: ����� ���� ������ ��� ����

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

    // �߰��� ��� �Լ� ����
    void ResetPoints();             // �ʱ�ȭ ���
    void MovePointsRandomly();      // ���� �̵� ���
    void SetLineThickness(int thickness); // �� �β� ����
    void UpdateCoordinateDisplay();

protected:
    DECLARE_MESSAGE_MAP()

    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
    std::vector<CPoint> m_points; // Ŭ���� ��ġ ����
    bool m_isDragging = false;    // �巡�� ������ ����
    int m_dragIndex = -1;         // �巡�� ���� ���� �ε���

    int m_lineThickness = 1; // �߰�: �� �β� ��� ����

    void DrawCircle(HDC hdc, const CPoint& point, int radius, COLORREF color);
    void DrawCircumcircle(HDC hdc);
};