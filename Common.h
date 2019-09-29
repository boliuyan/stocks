#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__
#include <string>
#include <map>
#include <vector>
#include <list>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <luabind\luabind.hpp>
#include <boost\locale.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/lexical_cast.hpp>
#endif
#define LUA_CONFIG_PATH "./config.lua"

static bool Compare(float a, float b)
{

	int nBefore = a;
	int nLast = b;
	if (nBefore > nLast)
		return true;
	if (nBefore < nLast)
		return false;
	std::string strBefore = boost::lexical_cast<std::string>(a);
	std::string strLast = boost::lexical_cast<std::string>(b);
	int idxNum = strBefore.find(".");
	if (idxNum == -1)
		return false;
	int size = strBefore.size();
	if (size < strLast.size())
		size = strLast.size();

	for (int i = idxNum; i < size; i++) {
		if (strBefore.substr(i, 1) > strLast.substr(i, 1))
			return true;
		if (strBefore.substr(i, 1) < strLast.substr(i, 1))
			return false;
	}
	return false;
}