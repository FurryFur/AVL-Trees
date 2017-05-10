#pragma once

#include <array>

class CBSTNode
{
public:
	CBSTNode();
	CBSTNode(int _iVal);
	~CBSTNode();

	int m_iVal;
	std::array<int, 2> m_arriSubTreeHeights;

	CBSTNode*& GetChildNode(int _iChildIdx);
	const CBSTNode* const & GetChildNode(int _iChildIdx) const;
	void SetChildNode(int _iChildIdx, CBSTNode* _pNode);
	bool IsLeaf() const;

	bool Delete(int _iChildIdx);

	int GetBalanceFactor() const;

private:
	std::array<CBSTNode*, 2> m_arrpChildNodes;
};

