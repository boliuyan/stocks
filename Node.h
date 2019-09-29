#pragma once
#include "Common.h"
class CNode
{
public:
	CNode();
	~CNode();
public:
	virtual void init();
	virtual void destroy();
	static CNode* Create();
	virtual void AddChild(CNode *child, int Tag);
	virtual CNode* GetChildByTag(int tag);
	virtual void SetParent(CNode *p);
	virtual CNode* GetParent();
	virtual void RemoveChildByTag(int Tag);
	virtual int GetChildNum() { return m_vecChild.size(); }
	virtual void SetTag(int Tag);
	virtual int GetTag();
	virtual void Cleaup();
	virtual void DeleteSelf();
	void UpData();
	void run();
	virtual void RemoveAllChild();
	virtual void SetIsOpen(bool b) { bIsOpen = b; }
	virtual bool GetIsOpen() { return bIsOpen; }
private:
	std::vector<CNode*> m_vecChild;
	int m_iTag;
	CNode *m_Parent;
	bool bIsOpen;
};

