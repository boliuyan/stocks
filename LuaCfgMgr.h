#pragma once
#include "Common.h"

using namespace luabind;


struct LuaCfg {
	std::string strFilePath;
	
	std::string strOutPutPath;

	bool bReadListByLua;

	int nReadTimeMode; 

	int nThread;
};
class CLuaCfgMgr
{
public:
	CLuaCfgMgr();
	~CLuaCfgMgr();
public:
	static CLuaCfgMgr& getInstance();
	void InitLua();
	lua_State* getLuaData() {
		return m_LuaState;
	};
	void LoadLuaCfg();
	void setIsReadByLua(bool IsReadByLua);
	bool getIsReadByLua();
	std::string getFilePath();
	std::string getOutPutPath();
	int getTimeMode();
	void DestroyLua();
	int getThread();
private:
	lua_State *	 m_LuaState;
	LuaCfg m_cfg;
};

