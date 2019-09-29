#pragma once
#include "Node.h"
class CMA:public CNode
{
public:
	CMA();
	~CMA();
public:
	static CMA* Create();
	void setPeriod(int period);
	float getData(int idx) {
		return m_vecMa.at(idx);
	}
	void upData(std::string Price);
	void upData(float Price);
	int getSize() { return m_vecMa.size(); }
	void destroy();
private:
	std::vector<float> m_vecMa;
	std::list<float> m_listTmp;
	int m_iPeriod;
};

