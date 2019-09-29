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
	//��ʱ��ĳ� vector ���� list���� ����ַ��� Ȼ���ַ��� ��vector��
private:
	std::string strPrint;
	std::string strOutFilePath;
	std::string strfileName;
	std::list<std::string> strWait;
};

