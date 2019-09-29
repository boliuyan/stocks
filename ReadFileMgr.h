#pragma once
#include "Common.h"
class CStockData;
class CReadFileMgr
{
public:
	CReadFileMgr();
	~CReadFileMgr();
	static CReadFileMgr& getInstance();
	void init();
	void destroy();
	void RunReadFile();
	void ResolvData();
	void SendStr(std::string m);
	//void ResolvData(lua_State*L);
	void ResolvFile(CStockData *p,std::string strName);
	void ResolvFile(CStockData *p, std::string strName, lua_State*L);
private:
	std::vector<std::thread> m_vecThread;
	int m_threadNum;
	int m_idexNum;
	std::mutex m_mutex;
	std::condition_variable cond;
};

