#include "stdafx.h"
#include "OutPutMgr.h"


COutPutMgr::COutPutMgr()
{
}


COutPutMgr::~COutPutMgr()
{
}

COutPutMgr & COutPutMgr::getInstance()
{
	static COutPutMgr m;
	return m;
	// TODO: 在此处插入 return 语句
}

std::string COutPutMgr::getTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y_%m_%d_%H_%M_%S", localtime(&timep));
	return tmp;
}
void COutPutMgr::Init(std::string path)
{
	strPrint = "";
	strOutFilePath = path;
	strfileName = getTime();
}

void COutPutMgr::setAddStr(std::string c)
{
	strPrint = strPrint + c;
}

void COutPutMgr::Destroy()
{
	strOutFilePath.clear();
	strPrint.clear();
	strfileName.clear();
}

void COutPutMgr::WriteInToFile(std::string strName)
{
	strName = strOutFilePath + strName;
	FILE* fp = fopen(strName.c_str(), "ab+");
	fwrite(strPrint.c_str(), strPrint.size(), 1, fp);
	fclose(fp);
}

void COutPutMgr::WriteInToFile()
{
	WriteInToFile(strfileName);
}
