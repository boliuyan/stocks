#include "stdafx.h"
#include "ReadFileMgr.h"
#include "StockData.h"
#include "FileCfg.h"
#include "ResolvFile.h"
#include "OutPutMgr.h"
#include "LuaCfgMgr.h"
#include "MA.h"
CReadFileMgr::CReadFileMgr()
	:m_threadNum(0)
{

}


CReadFileMgr::~CReadFileMgr()
{

}

void CReadFileMgr::init()
{
	m_threadNum = CLuaCfgMgr::getInstance().getThread();
	m_idexNum = 0;
}

void CReadFileMgr::destroy()
{
}

CReadFileMgr & CReadFileMgr::getInstance()
{
	static CReadFileMgr m;
	return m;
	// TODO: 在此处插入 return 语句
}

void CReadFileMgr::RunReadFile()
{
	for (int i = 0; i < m_threadNum; i++) {
		
		m_vecThread.push_back(std::thread(&CReadFileMgr::ResolvData,this));
		//m_vecThread.push_back(std::thread(&CReadFileMgr::ResolvData,this,lua_newthread(CLuaCfgMgr::getInstance().getLuaData())));
	}
	for (auto& thread : m_vecThread) {
		thread.join();
	}
	//int size = CFileCfg::getInstance().getFileSize();
	//CStockData c;
	//c.Init();
	//for (int i = 0; i < size; i++) {		
	//	printf("进度:%.2lf%% \r 当前:%d ", i * 100.0 /  size, i);
	//	c.LoadFileByName(CFileCfg::getInstance().getFileNameByIdex(i));
	//	//CResolvFile::run(c)
	//	ResolvFile(&c, CFileCfg::getInstance().getFileNameByIdex(i));
	//	c.Clear();
	//}
	//c.Destroy();
	//COutPutMgr::getInstance().WriteInToFile();
}

void CReadFileMgr::ResolvData()//lua_State*L
{
	while (1) {
		int size = CFileCfg::getInstance().getFileSize();
		std::string strName = "";
		m_mutex.lock();
		if (m_idexNum >= size) {
			m_mutex.unlock();
			return;
		}
		printf("进度:%.2lf%% \r 当前:%d ", m_idexNum * 100.0 / size, m_idexNum);
		strName =CFileCfg::getInstance().getFileNameByIdex(m_idexNum);
		m_idexNum = m_idexNum + 1;
		m_mutex.unlock();
		
		CStockData c;
		c.Init();
		c.LoadFileByName(strName);
		////处理

		//ResolvFile(&c, strName,L);
		ResolvFile(&c, strName);
		c.Destroy();
		Sleep(100);
	}
}
void CReadFileMgr::SendStr(std::string m)
{
	m_mutex.lock();
	COutPutMgr::getInstance().setAddStr(m);
	m_mutex.unlock();

}
void CReadFileMgr::ResolvFile(CStockData *p, std::string strName) {
	int size = p->getSize();
	CMA* MA5 = CMA::Create();
	MA5->setPeriod(5);
	CMA* MA10 = CMA::Create();
	MA10->setPeriod(10);
	CMA* MA20 = CMA::Create();
	MA20->setPeriod(20);
	CMA* MA60 = CMA::Create();
	MA60->setPeriod(60);
	
	for (int i = 0; i < size; i++) {
		MA5->upData(p->getData(i).strClosePrice);
		MA10->upData(p->getData(i).strClosePrice);
		MA20->upData(p->getData(i).strClosePrice);
		MA60->upData(p->getData(i).strClosePrice);
	}

	if (size <= 72)
		return;
	//bool nice60 = false;
	for (int i = size-72; i < size; i++) {
		if (!Compare(MA60->getData(i - 1), MA60->getData(i))) {
			MA5->destroy();
			MA10->destroy();
			MA20->destroy();
			MA60->destroy();
			return;
		}
		if (Compare(MA5->getData(i), MA10->getData(i))) {
			if (Compare(MA10->getData(i), MA20->getData(i))) {
			
				if (Compare(atof(p->getData(i).strClosePrice.c_str()), MA60->getData(i))) {
					MA5->destroy();
					MA10->destroy();
					MA20->destroy();
					MA60->destroy();
					if(p->getData(i).strDate == p->getData(size).strDate)
						COutPutMgr::getInstance().setAddStr(p->getData(i).strDate + " " + p->getData(i).strTime +" "+strName + "\r\n");
					return;
				}
			}
		}
	}
	MA5->destroy();
	MA10->destroy();
	MA20->destroy();
	MA60->destroy();
}
//void CReadFileMgr::ResolvFile(CStockData *p,std::string strName, lua_State*L)
//{
//	try {
//		luabind::call_function<void>(L, "CalculationByLua", p, strName);
//
//	}
//	catch (luabind::error& e) {
//		//printf("%s", e.what());
//		printf("%s", e.what());
//		printf("AI throw error: err_msg[%s]", lua_tostring(L, -1));
//	}
//}



//char str[128];
//sprintf(str, "日期 %s 时间 %s 股票 %s MA5 %f MA20 %f \r\n"
//	, p->getData(i).strDate.c_str()
//	, p->getData(i).strTime.c_str()
//	, strName.c_str()
//	, MA5->getData(i)
//	, MA10->getData(i));
//COutPutMgr::getInstance().setAddStr(str);
//return;
//if (Compare(MA20->getData(i), atof(p->getData(i).strOpenPrice.c_str()))) {
//	if (Compare(MA5->getData(i), MA20->getData(i))) {
//		if (!Compare(MA5->getData(i), atof(p->getData(i).strClosePrice.c_str()))) {
//			char str[128];
//			sprintf(str, "日期 %s 时间 %s 股票 %s MA5 %f MA20 %f \r\n"
//				, p->getData(i).strDate.c_str()
//				, p->getData(i).strTime.c_str()
//				, strName.c_str()
//				, MA5->getData(i)
//				, MA20->getData(i));
//			COutPutMgr::getInstance().setAddStr(str);
//			return;
//		}
//	}
//}