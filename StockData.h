#pragma once
#include "Common.h"

struct CStockInfo
{
	//日期	    开盘	    最高	    最低	    收盘	    成交量	    成交额
	std::string strDate;//日期
	std::string strTime;
	std::string strOpenPrice; //开盘
	std::string strHighPrice; //最高
	std::string strLowPrice; //最低
	std::string strClosePrice; //收盘
	std::string strValue; //成交量
	std::string strTurnover; //成交额
};
class CStockData
{
public:
	CStockData();
	~CStockData();

	void Init();
	void Clear();
	void Destroy();
	CStockInfo getData(int idex);
	int getSize() { return m_vecStockData.size(); }
	void LoadFileByName(std::string strName);
private:
	void LoadFile(std::string strName);
	void ReadBuff(std::string strName);
	bool ReadByTimeMode(std::string time);
	bool ReadNewData();
	void SumOldData();
	void ReadTitle();
	void ClearData(CStockInfo* p);
private:
	std::vector<CStockInfo> m_vecStockData;
	std::stringstream m_strBuf;
	int m_iTimeMode;
	CStockInfo *mTempData;
	CStockInfo *mOldData;
};

