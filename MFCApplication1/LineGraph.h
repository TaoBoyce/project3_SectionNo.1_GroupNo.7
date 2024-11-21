#pragma once

#include <vector>
#include <afxwin.h>

class CLineGraph : public CStatic
{
public:
	void SetData(const std::vector<int>& data);

protected:
	std::vector<int> m_data;

	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};
