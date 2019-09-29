#include "stdafx.h"
#include "StockData.h"
#include "LuaCfgMgr.h"

CStockData::CStockData()
{
}


CStockData::~CStockData()
{
}

void CStockData::Init()
{
	
	m_iTimeMode = CLuaCfgMgr::getInstance().getTimeMode();
	mOldData = new CStockInfo();
	mTempData = new CStockInfo();
	Clear();

//	LoadFile(strPath);
	
	
}

void CStockData::Clear()
{
	std::vector<CStockInfo>().swap(m_vecStockData);
	m_strBuf.clear();
	m_strBuf.str("");
	ClearData(mOldData);
	ClearData(mTempData);
	
}

void CStockData::Destroy()
{
	Clear();
	m_iTimeMode = 0;
	delete mOldData;
	delete mTempData;
}

CStockInfo CStockData::getData(int idex)
{
	return m_vecStockData.at(idex);
}

void CStockData::LoadFileByName(std::string strName)
{
	std::string strPath = CLuaCfgMgr::getInstance().getFilePath();
	strPath = strPath + strName;
	LoadFile(strPath);
}

void CStockData::LoadFile(std::string strName)
{
	ReadBuff(strName);
	ReadTitle();
	while (1) {
		if (ReadNewData()) {
			ClearData(mOldData);
			ClearData(mTempData);
			return;
		}
			
		SumOldData();
		if (ReadByTimeMode(mTempData->strTime)) {
			CStockInfo c;
			c.strClosePrice = mOldData->strClosePrice;
			c.strDate = mOldData->strDate;
			c.strHighPrice = mOldData->strHighPrice;
			c.strLowPrice = mOldData->strLowPrice;
			c.strOpenPrice = mOldData->strOpenPrice;
			c.strTime = mOldData->strTime;
			c.strTurnover = mOldData->strTurnover;
			c.strValue = mOldData->strValue;

			m_vecStockData.push_back(c);
			
			ClearData(mOldData);
			
		}
			
	}
}

void CStockData::ReadBuff(std::string strName)
{
	std::ifstream fin(strName, std::ios::in);
	m_strBuf.clear();
	m_strBuf.str("");
	m_strBuf << fin.rdbuf();
	fin.close();
}

bool CStockData::ReadByTimeMode(std::string time)
{
	std::string str(time, 2);
	int t = atoi(str.c_str());
	float mode = t%m_iTimeMode;
	return mode == 0;
}

bool CStockData::ReadNewData()
{
	std::string str;
	m_strBuf >> str;
	if (str.find("通达信") != -1)
		return true;
	mTempData->strDate = str;
	m_strBuf >> mTempData->strTime;
	m_strBuf >> mTempData->strOpenPrice;
	m_strBuf >> mTempData->strHighPrice;
	m_strBuf >> mTempData->strLowPrice;
	m_strBuf >> mTempData->strClosePrice;
	m_strBuf >> mTempData->strValue;
	m_strBuf >> mTempData->strTurnover;

	return false;
}

void CStockData::SumOldData()
{
	if (mOldData->strDate == ""){
		mOldData->strClosePrice = mTempData->strClosePrice;
		mOldData->strDate = mTempData->strDate;
		mOldData->strHighPrice = mTempData->strHighPrice;
		mOldData->strLowPrice = mTempData->strLowPrice;
		mOldData->strOpenPrice = mTempData->strOpenPrice;
		mOldData->strTime = mTempData->strTime;
		mOldData->strTurnover = mTempData->strTurnover;
		mOldData->strValue = mTempData->strValue;
		return;
	}
	mOldData->strClosePrice = mTempData->strClosePrice;
	if (!Compare(atof(mOldData->strHighPrice.c_str()), atof(mTempData->strHighPrice.c_str())))
		mOldData->strHighPrice = mTempData->strHighPrice;

	if (Compare(atof(mOldData->strLowPrice.c_str()), atof(mTempData->strLowPrice.c_str())))
		mOldData->strLowPrice = mTempData->strLowPrice;
	
	double val = boost::lexical_cast<double>(mOldData->strTurnover) + boost::lexical_cast<double>(mTempData->strTurnover);
	mOldData->strTurnover = boost::lexical_cast<std::string>(val);
	int val2 = boost::lexical_cast<int>(mOldData->strValue) + boost::lexical_cast<int>(mTempData->strValue);
	mOldData->strValue = boost::lexical_cast<std::string>(val2);
	return;
}

void CStockData::ReadTitle()
{
	std::string str;
	while (1)
	{
		str = "";
		m_strBuf >> str;
		if (str.find("成交额") != -1)
			return;
	}
}

void CStockData::ClearData(CStockInfo * p)
{
	p->strClosePrice = "";
	p->strDate = "";
	p->strHighPrice = "";
	p->strLowPrice = "";
	p->strOpenPrice = "";
	p->strTime = "";
	p->strTurnover = "";
	p->strValue = "";
}
