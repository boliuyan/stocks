#pragma once
#include "Common.h"

struct CStockInfo
{
	//����	    ����	    ���	    ���	    ����	    �ɽ���	    �ɽ���
	std::string strDate;//����
	std::string strTime;
	std::string strOpenPrice; //����
	std::string strHighPrice; //���
	std::string strLowPrice; //���
	std::string strClosePrice; //����
	std::string strValue; //�ɽ���
	std::string strTurnover; //�ɽ���
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

