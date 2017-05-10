#pragma once

#include <stack>

#include "BSTNode.h"

class CBinaryST
{
public:
	CBinaryST();
	~CBinaryST();

	void Insert(int _iVal);
	bool Delete(int _iVal);
	bool Search(int _iVal);
	CBSTNode*& GetRootNode();

	bool Rotate(CBSTNode* _pNodeRoot, int _iPivotIdx, CBSTNode* _pNodeRootParent, int _iRootIdx);

private:
	CBSTNode* m_pNodeRoot;

	void Delete(CBSTNode* _pNodeToDelete, std::stack<std::pair<CBSTNode*, int>> _stackPathToRoot);
	bool ReBalanceTree(std::stack<std::pair<CBSTNode*, int>> _stackPathToRoot);
};

