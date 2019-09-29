#pragma once
#include "Common.h"
class COutPutMgr
{
public:
	COutPutMgr();
	~COutPutMgr();
public:
	static COutPutMgr& getInstance();
	void Init(std::string path);
	void setAddStr(std::string c);
	void Destroy();
	void WriteInToFile(std::string strName);
	void WriteInToFile();
	std::string getTime();
	//有时间改成 vector 或者 list这种 添加字符串 然后字符串 从vector读
private:
	std::string strPrint;
	std::string strOutFilePath;
	std::string strfileName;
	std::list<std::string> strWait;
};

