#pragma once
class CStockData;
class CResolvFile
{
public:
	CResolvFile();
	~CResolvFile();
public:
	static CResolvFile& getInstance();

	void run(CStockData p);

};

