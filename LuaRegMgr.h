#pragma once
#include "Common.h"

using namespace luabind;
class CLuaRegMgr
{
public:
	CLuaRegMgr();
	~CLuaRegMgr();
public:
	static CLuaRegMgr& getInstance();
	void GetLuaFileTable(std::string fun);
	scope RegisterSig();
	scope RegisterAPI();
	void RegisterForLua();
};

