#include "stdafx.h"
#include "Common.h"
#include "ResolvFile.h"
#include "StockData.h"
#include "OutPutMgr.h"
CResolvFile::CResolvFile()
{
}


CResolvFile::~CResolvFile()
{
}



CResolvFile & CResolvFile::getInstance()
{
	// TODO: 在此处插入 return 语句
	static CResolvFile m;
	return m;
}

void CResolvFile::run(CStockData p)
{
	
	
}
