#include "stdafx.h"
#include "LuaRegMgr.h"
#include "LuaCfgMgr.h"
#include "Node.h"
#include "MA.h"
#include "OutPutMgr.h"
#include "StockData.h"
CLuaRegMgr::CLuaRegMgr()
{
}


CLuaRegMgr::~CLuaRegMgr()
{
}

CLuaRegMgr & CLuaRegMgr::getInstance()
{
	static CLuaRegMgr reg;
	return reg;
	// TODO: 在此处插入 return 语句
}

scope CLuaRegMgr::RegisterSig()
{
	return class_<CNode>("CNode")
		.scope[def("Create", &CNode::Create)]
		.def("AddChild", &CNode::AddChild)
		.def("destroy", &CNode::destroy)
		.def("GetParent", &CNode::GetParent)
		.def("RemoveChildByTag", &CNode::RemoveChildByTag)
		.def("UpData", &CNode::UpData)
		.def("SetTag", &CNode::SetTag)
		.def("GetChildByTag", &CNode::GetChildByTag)
		.def("RemoveAllChild", &CNode::RemoveAllChild)

		, class_<CMA, CNode>("CMA")
		.scope[def("Create", &CMA::Create)]
		//.def("Create", &CMA::Create)
		.def("setPeriod", &CMA::setPeriod)
		.def("getData", &CMA::getData)
		.def("destroy", &CMA::destroy)
		;

}

scope CLuaRegMgr::RegisterAPI()
{
	return  class_<CStockInfo>("CStockInfo")
		.def_readonly("strDate", &CStockInfo::strDate)
		.def_readonly("strTime", &CStockInfo::strTime)
		.def_readonly("strOpenPrice", &CStockInfo::strOpenPrice)
		.def_readonly("strHighPrice", &CStockInfo::strHighPrice)
		.def_readonly("strLowPrice", &CStockInfo::strLowPrice)
		.def_readonly("strClosePrice", &CStockInfo::strClosePrice)
		.def_readonly("strValue", &CStockInfo::strValue)
		.def_readonly("strTurnover", &CStockInfo::strTurnover)
		, class_<CStockData>("CStockData")
		.def("getData", &CStockData::getData)
		.def("getSize", &CStockData::getSize)
		, class_<COutPutMgr>("COutPutMgr")
		.scope[def("getInstance", &COutPutMgr::getInstance)]
		.def("setAddStr", &COutPutMgr::setAddStr)
		;
	
}

void CLuaRegMgr::RegisterForLua()
{
	module(CLuaCfgMgr::getInstance().getLuaData())
		[
			RegisterSig()
			, RegisterAPI()


		];
}
