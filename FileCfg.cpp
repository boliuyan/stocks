#include "stdafx.h"
#include "FileCfg.h"
#include "LuaCfgMgr.h"


CFileCfg::CFileCfg()
:strStockFilePath("")
{
}


CFileCfg::~CFileCfg()
{
}

CFileCfg & CFileCfg::getInstance()
{
	static CFileCfg m;
	return m;
	// TODO: 在此处插入 return 语句
}

void CFileCfg::Init()
{	
	setFilePath(CLuaCfgMgr::getInstance().getFilePath());
}

void CFileCfg::Destroy()
{
}

void CFileCfg::setFilePath(std::string strPath)
{
	strStockFilePath = strPath;
}

void CFileCfg::readFileList()
{
	if (bReadByLua)
	{
		//LoadFromLua();
		return;
	}

	std::string strPath;
	strPath = strStockFilePath + "*.*";
	std::wstring wstr = boost::locale::conv::to_utf<wchar_t>(strPath, "gbk");
	//std::wstring path = wstr ;

	WIN32_FIND_DATA fdFileData;
	HANDLE  hFind = FindFirstFile(wstr.c_str(), &fdFileData);
	std::string file = "..";
	while (FindNextFile(hFind, &fdFileData))
	{
		file = boost::locale::conv::from_utf(fdFileData.cFileName, "GBK");
		if (file != "..")
		{
			m_vecStockNameList.push_back(file);
		}
	}
	//hFind = NULL;
	FindClose(hFind);
}
