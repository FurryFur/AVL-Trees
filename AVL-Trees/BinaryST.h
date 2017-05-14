#pragma once

#include <stack>
#include <functional>

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

	void PreOrderOp(std::function<void(int)> _fn);
	void PreOrderOp(std::function<void(int)> _fn, CBSTNode* _pCurNode);
	void PostOrderOp(std::function<void(int)> _fn);
	void PostOrderOp(std::function<void(int)> _fn, CBSTNode* _pCurNode);
	void InOrderOp(std::function<void(int)> _fn);
	void InOrderOp(std::function<void(int)> _fn, CBSTNode* _pCurNode);

private:
	CBSTNode* m_pNodeRoot;

	bool Rotate(CBSTNode* _pNodeTreeParent, int _iRotRootIdx, int _iPivotIdx);
	void Delete(CBSTNode* _pNodeToDelete, std::stack<std::pair<CBSTNode*, int>> _stackPathToRoot);
	bool ReBalanceTree(std::stack<std::pair<CBSTNode*, int>> _stackPathToRoot);

	void DeleteTree(CBSTNode* _pCurNode);
};

