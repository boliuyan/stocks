#include "stdafx.h"
#include "MA.h"


CMA::CMA()
{
}


CMA::~CMA()
{
}

CMA * CMA::Create()
{
	return new CMA();
}

void CMA::setPeriod(int period)
{	
	m_iPeriod = period;
}

void CMA::upData(std::string Price)
{
	upData(atof(Price.c_str()));
}

void CMA::upData(float Price)
{
	if (m_iPeriod <= 0)
		return;
	m_listTmp.push_back(Price);
	int size = m_listTmp.size();
	if (size < m_iPeriod)
	{
		m_vecMa.push_back(Price);
		return;
	}
	float tmp = 0;
	std::list<float>::iterator it;
	for (it = m_listTmp.begin(); it != m_listTmp.end(); ++it)
	{
		tmp = tmp + (float)(*it);
	}
	m_listTmp.pop_front();
	tmp = tmp / m_iPeriod;
	m_vecMa.push_back(tmp);
}

void CMA::destroy()
{
	m_iPeriod = 0;

	std::list<float>().swap(m_listTmp);
	//m_listTmp.clear();

	std::vector<float>().swap(m_vecMa);
	//m_vecMa.clear();
}
