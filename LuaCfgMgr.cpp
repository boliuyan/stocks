#include "stdafx.h"
#include "LuaCfgMgr.h"

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#ifdef _DEBUG
#pragma comment(lib,"..\\Debug\\luabind.lib")
#else
#pragma comment(lib,"..\\release\\luabind.lib")
#endif

CLuaCfgMgr::CLuaCfgMgr()
{
}


CLuaCfgMgr::~CLuaCfgMgr()
{
}

CLuaCfgMgr & CLuaCfgMgr::getInstance()
{
	static CLuaCfgMgr m;
	return m;
	// TODO: 在此处插入 return 语句
}

void CLuaCfgMgr::InitLua()
{
	m_LuaState = luaL_newstate();
	luaL_openlibs(m_LuaState);
	luabind::open(m_LuaState);

	LuaCfg m;
	m_cfg = m;
	return;
}

void CLuaCfgMgr::LoadLuaCfg()
{
	if (luaL_dofile(m_LuaState, LUA_CONFIG_PATH))
	{
		printf("%s", lua_tostring(m_LuaState, -1));
		return;
	}

	luabind::object global = luabind::globals(m_LuaState);
	luabind::object configTable = global["Config"];

	m_cfg.strFilePath =luabind::object_cast<std::string>(configTable["FilePath"]);
	m_cfg.strOutPutPath = luabind::object_cast<std::string>(configTable["OutPutPath"]);
	m_cfg.nReadTimeMode = luabind::object_cast<int>(configTable["ReadTimeMode"]);
	m_cfg.bReadListByLua = luabind::object_cast<bool>(configTable["ReadListByLua"]);
	m_cfg.nThread = luabind::object_cast<int>(configTable["thread"]);
}

void CLuaCfgMgr::setIsReadByLua(bool IsReadByLua)
{
	m_cfg.bReadListByLua = IsReadByLua;
}

bool CLuaCfgMgr::getIsReadByLua()
{
	return m_cfg.bReadListByLua;
}

std::string CLuaCfgMgr::getFilePath()
{
	return m_cfg.strFilePath;
}

std::string CLuaCfgMgr::getOutPutPath()
{
	return m_cfg.strOutPutPath;
}

int CLuaCfgMgr::getTimeMode()
{
	return m_cfg.nReadTimeMode;
}

void CLuaCfgMgr::DestroyLua()
{
	lua_close(m_LuaState);
	return;
}

int CLuaCfgMgr::getThread()
{
	return m_cfg.nThread;
}
