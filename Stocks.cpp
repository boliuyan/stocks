// Stocks.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LuaCfgMgr.h"
#include "FileCfg.h"
#include "StockData.h"
#include "OutPutMgr.h"
#include "ReadFileMgr.h"
#include "LuaRegMgr.h"
int main()
{
	CLuaCfgMgr::getInstance().InitLua();
	CLuaCfgMgr::getInstance().LoadLuaCfg();
	//CLuaCfgMgr::getInstance().DestroyLua();
	CLuaRegMgr::getInstance().RegisterForLua();
	CFileCfg::getInstance().Init();
	CFileCfg::getInstance().readFileList();
	COutPutMgr::getInstance().Init(CLuaCfgMgr::getInstance().getOutPutPath());
	CReadFileMgr::getInstance().init();
	CReadFileMgr::getInstance().RunReadFile();

	COutPutMgr::getInstance().WriteInToFile();

	//CStockData c;
	//c.Init(CFileCfg::getInstance().getFileNameByIdex(1));
	system("pause");
    return 0;
}

