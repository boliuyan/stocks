#pragma once
#include "Common.h"
class CFileCfg
{
public:
	CFileCfg();
	~CFileCfg();
public:
	static CFileCfg& getInstance();
	
	void Init();
	void Destroy();
	
	//��Ʊ�ļ���·��
	void setFilePath(std::string strPath);
	std::string getFilePath() { return strStockFilePath; }
	std::string getFileNameByIdex(int idx) { return m_vecStockNameList.at(idx); }
	int getFileSize() { return m_vecStockNameList.size(); }
	void readFileList();

private:
	std::string strStockFilePath;
	bool bReadByLua;
	std::vector<std::string> m_vecStockNameList;
};

