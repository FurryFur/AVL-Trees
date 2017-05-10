#include "BSTNode.h"

CBSTNode::CBSTNode() :
	CBSTNode(0)
{
}

CBSTNode::CBSTNode(int _iVal) :
	m_arrpChildNodes{ nullptr, nullptr },
	m_arriSubTreeHeights{ 0, 0 },
	m_iVal(_iVal)
{
}

CBSTNode::~CBSTNode()
{
}

CBSTNode*& CBSTNode::GetChildNode(int _iChildIdx)
{
	// Non-const version
	return const_cast<CBSTNode*&>(static_cast<const CBSTNode*>(this)->GetChildNode(_iChildIdx));
}

const CBSTNode * const & CBSTNode::GetChildNode(int _iChildIdx) const
{
	// Do bounds checked index operation
	return m_arrpChildNodes.at(_iChildIdx);
}

void CBSTNode::SetChildNode(int _iChildIdx, CBSTNode * _pNode)
{
	// Do bounds checked set operation
	m_arrpChildNodes.at(_iChildIdx) = _pNode;
}

bool CBSTNode::IsLeaf() const
{
	if (m_arrpChildNodes[0] == nullptr && m_arrpChildNodes[1] == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CBSTNode::Delete(int _iChildIdx)
{
	CBSTNode*& pChildNode = GetChildNode(_iChildIdx);
	if (pChildNode)
	{
		delete pChildNode;
		pChildNode = nullptr;
		return true;
	}
	else
	{
		return false;
	}
}

int CBSTNode::GetBalanceFactor() const
{
	// Right - Left tree height
	return m_arriSubTreeHeights.at(1) - m_arriSubTreeHeights.at(0);
}
