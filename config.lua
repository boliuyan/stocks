
Config = {
FilePath = "F:/outof6/",
OutPutPath = "F:/output/",
ReadListByLua = false,
ReadTimeMode = 5,
thread = 8,
}

require "..\\script\\luaNode"
require "..\\script\\FileNameTable"
require "..\\script\\luaBIAS_MACD"
require "..\\script\\luaBIAS"
require "..\\script\\test"

function CalculationByLua(pCStockData,sName)
	 funStockTest(pCStockData,sName)
end
--改多线程 字符串输出 锁 字符串接受数据 缓存