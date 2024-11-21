#include "pch.h"
#include "LineGraph.h"

BEGIN_MESSAGE_MAP(CLineGraph, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CLineGraph::SetData(const std::vector<int>& data)
{
	m_data = data;
	TRACE(_T("Data set with %d points\n"), static_cast<int>(m_data.size()));
	Invalidate(); // Request redraw
}


void CLineGraph::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	if (rect.IsRectEmpty())
	{
		AfxMessageBox(_T("The graph area is invalid."));
		return;
	}

	TRACE(_T("OnPaint called. Rect: (%d, %d, %d, %d)\n"), rect.left, rect.top, rect.right, rect.bottom);
	if (rect.IsRectEmpty())
		return;

	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.MoveTo(rect.left, rect.bottom);
	dc.LineTo(rect.right, rect.bottom);
	dc.LineTo(rect.right, rect.top);

	if (!m_data.empty())
	{
		int maxDataValue = *std::max_element(m_data.begin(), m_data.end());
		int step = rect.Width() / static_cast<int>(m_data.size());
		for (size_t i = 1; i < m_data.size(); ++i)
		{
			int x1 = rect.left + (i - 1) * step;
			int y1 = rect.bottom - (m_data[i - 1] * rect.Height() / maxDataValue);
			int x2 = rect.left + i * step;
			int y2 = rect.bottom - (m_data[i] * rect.Height() / maxDataValue);

			dc.MoveTo(x1, y1);
			dc.LineTo(x2, y2);
		}
	}
}
