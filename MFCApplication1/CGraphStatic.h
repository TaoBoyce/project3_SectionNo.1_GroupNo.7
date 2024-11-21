#pragma once
#include <vector>

class CGraphStatic : public CStatic
{
public:
	void SetData(const std::vector<int>& data);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;

private:
	std::vector<int> m_data;
};
