#include "stdafx.h"
#include "Node.h"


CNode::CNode()
{
}


CNode::~CNode()
{
}

void CNode::init()
{
}

void CNode::destroy()
{
	this->m_Parent = nullptr;
}

CNode * CNode::Create()
{
	CNode *node = new CNode();
	return node;
}

void CNode::AddChild(CNode *node, int Tag)
{
	for (const auto &child : m_vecChild)
	{
		if (child->GetTag() == Tag)
			return;
	}
	node->SetTag(Tag);
	node->SetParent(this);
	m_vecChild.push_back(node);
}

CNode* CNode::GetChildByTag(int Tag)
{
	for (const auto &child : m_vecChild)
	{
		if (child->GetTag() == Tag)
			return child;
	}
	return nullptr;
}

void CNode::SetParent(CNode *p)
{
	m_Parent = p;
}

CNode* CNode::GetParent()
{
	return m_Parent;
}

void CNode::RemoveChildByTag(int Tag)
{
	if (m_vecChild.empty())
		return;
	std::vector<CNode*>::iterator it;
	for (std::vector<CNode*>::iterator iter = m_vecChild.begin(); iter != m_vecChild.end(); )
	{
		if (dynamic_cast<CNode*>(*iter)->GetTag() == Tag)
		{
			dynamic_cast<CNode*>(*iter)->Cleaup();
			dynamic_cast<CNode*>(*iter)->destroy();
			it = iter;
			m_vecChild.erase(it);
			return;
		}
		else
			iter++;
	}


}

void CNode::SetTag(int tag)
{
	m_iTag = tag;
}

int CNode::GetTag()
{
	return m_iTag;
}

void CNode::Cleaup()
{
	if (m_vecChild.empty())
		return;

	//for (int i = 0; i < m_vecChild.size(); ++i)
	//{
	//	m_vecChild[i]->Cleaup(); //子节点全部清理
	//	m_vecChild[i]->destroy();
	//	delete m_vecChild[i];
	//}
	for (const auto &child : m_vecChild)
	{
		child->Cleaup(); //子节点全部清理
		child->destroy(); //销毁自有
		child->DeleteSelf();
	}
	std::vector<CNode*>().swap(m_vecChild);
	//m_vecChild.clear();
	return;
}

void CNode::DeleteSelf()
{
	delete this;
}

void CNode::UpData()
{
}

void CNode::run()
{
}

void CNode::RemoveAllChild()
{
	this->Cleaup();
}
