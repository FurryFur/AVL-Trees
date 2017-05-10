#include <assert.h>
#include <utility>
#include <math.h>

#include "BinaryST.h"

CBinaryST::CBinaryST() :
	m_pNodeRoot(nullptr)
{
}


CBinaryST::~CBinaryST()
{
	DeleteTree(m_pNodeRoot);
}

void CBinaryST::Insert(int _iVal)
{
	// Special case when root is null
	if (m_pNodeRoot == nullptr)
	{
		CBSTNode* pNewNode = new CBSTNode();
		pNewNode->m_iVal = _iVal;
		m_pNodeRoot = pNewNode;
		return;
	}

	// Traverse the tree to find the position for the new node
	std::stack<std::pair<CBSTNode*, int>> stackPathToRoot;
	CBSTNode* pCurNode = m_pNodeRoot;
	while (true)
	{
		// Don't insert duplicates
		if (_iVal == pCurNode->m_iVal)
			return;

		// Get child link to traverse
		int iChildIdx = (_iVal < pCurNode->m_iVal) ? 0 : 1;

		// Taverse / Insert
		CBSTNode* childNode = pCurNode->GetChildNode(iChildIdx);
		stackPathToRoot.push(std::make_pair(pCurNode, iChildIdx));
		if (childNode != nullptr)
		{
			// Continue traversing
			pCurNode = childNode;
		}
		else
		{
			// Insert new node on the link
			CBSTNode* pNewNode = new CBSTNode();
			pNewNode->m_iVal = _iVal;
			pCurNode->SetChildNode(iChildIdx, pNewNode);
			ReBalanceTree(stackPathToRoot);
			break;
		}
	}
}

void CBinaryST::Delete(CBSTNode* _pNodeToDelete, std::stack<std::pair<CBSTNode*, int>> _stackPathToRoot)
{
	// Check we have a node to delete
	if (_pNodeToDelete == nullptr)
		return;

	CBSTNode* pParentNode = nullptr;
	int iNodeToDeleteIdx = 0;
	if (!_stackPathToRoot.empty())
	{
		pParentNode = _stackPathToRoot.top().first;
		iNodeToDeleteIdx = _stackPathToRoot.top().second;
	}

	int iChildIdx = 0;

	// For leaf nodes just delete them
	if (_pNodeToDelete->IsLeaf())
	{
		if (!_stackPathToRoot.empty())
		{
			// Delete from parent
			pParentNode->Delete(iNodeToDeleteIdx);
		}
		else
		{
			// Handle root node case
			delete m_pNodeRoot;
			m_pNodeRoot = nullptr;
		}
	}
	// For nodes that only have one child, replace the node with that child
	else if (_pNodeToDelete->GetChildNode(iChildIdx) == nullptr || _pNodeToDelete->GetChildNode(++iChildIdx) == nullptr)
	{
		// Use the other node to replace the deleted one
		CBSTNode* pReplacementNode = _pNodeToDelete->GetChildNode((iChildIdx + 1) % 2);
		*_pNodeToDelete = *pReplacementNode;
		delete pReplacementNode;
	}
	// Otherwise, find a node to replace the current node and update the links
	else
	{
		// Traverse one right, then to the leftmost node
		int iReplacementIdx = 1; // First traverse right
		CBSTNode* pReplacementParent = nullptr;
		CBSTNode* pReplacementNode = _pNodeToDelete;
		CBSTNode* pNextLeftChild;
		while (pNextLeftChild = pReplacementNode->GetChildNode(iReplacementIdx))
		{
			pReplacementParent = pReplacementNode;
			_stackPathToRoot.push(std::make_pair(pReplacementParent, iReplacementIdx));
			pReplacementNode = pNextLeftChild;

			// Swap to traversing left after first iteration
			iReplacementIdx = 0;
		}

		// Update contained value of the node to replace with the value from the replacement node
		_pNodeToDelete->m_iVal = pReplacementNode->m_iVal;

		// If the right child of the replacement node exists, move it up the tree
		CBSTNode* pRightChildOfReplacement = pReplacementNode->GetChildNode(1);
		if (pRightChildOfReplacement)
		{
			*pReplacementNode = *pRightChildOfReplacement;
			delete pRightChildOfReplacement;
		}
		// Otherwise delete the replacment node from its parent
		else
		{
			pReplacementParent->Delete(iReplacementIdx);
		}
	}

	ReBalanceTree(_stackPathToRoot);
}


bool CBinaryST::Delete(int _iVal)
{
	bool bResult = false;

	std::stack<std::pair<CBSTNode*, int>> stackPathToRoot;
	CBSTNode* pParentNode = nullptr;
	CBSTNode* pCurNode = m_pNodeRoot;
	int iCurNodeIdx = 0;
	while (pCurNode != nullptr && bResult == false)
	{
		// Check if current node should be deleted
		if (pCurNode->m_iVal == _iVal)
		{
			bResult = true;
			Delete(pCurNode, stackPathToRoot);
		}
		// Otherwise continue searching the tree
		else
		{
			// Get traversal direction
			iCurNodeIdx = (_iVal <= pCurNode->m_iVal) ? 0 : 1;

			// Traverse
			pParentNode = pCurNode;
			pCurNode = pCurNode->GetChildNode(iCurNodeIdx);
			stackPathToRoot.push(std::make_pair(pParentNode, iCurNodeIdx));
		}
	}

	return bResult;
}

bool CBinaryST::ReBalanceTree(std::stack<std::pair<CBSTNode*, int>> _stackPathToRoot)
{
	bool bReBalanced = false;

	while (!_stackPathToRoot.empty() && !bReBalanced)
	{
		// Traverse up the tree
		CBSTNode* pCurNode = _stackPathToRoot.top().first;
		int iChildIdx = _stackPathToRoot.top().second;
		CBSTNode* pChildNode = pCurNode->GetChildNode(iChildIdx);
		_stackPathToRoot.pop();

		// Update height of relevant subtree
		if (pChildNode)
		{
			pCurNode->m_arriSubTreeHeights[iChildIdx] = std::max(
				pChildNode->m_arriSubTreeHeights[0] + 1,
				pChildNode->m_arriSubTreeHeights[1] + 1
			);
		}
		else
		{
			pCurNode->m_arriSubTreeHeights[iChildIdx] = 0;
		}

		// Check if we need to rotate the tree
		int iBalanceFactor = pCurNode->GetBalanceFactor();
		if (std::abs(iBalanceFactor) > 1)
		{
			bReBalanced = true;

			int iPivotIdx = (iBalanceFactor + 2) / 4;
			int iInternalIdx = (iPivotIdx + 1) % 2;
			CBSTNode* pNodePivot = pCurNode->GetChildNode(iPivotIdx);

			// Check if we need a double rotation
			int iInternalHeight = pNodePivot->m_arriSubTreeHeights[iInternalIdx];
			int iExternalHeight = pNodePivot->m_arriSubTreeHeights[iPivotIdx];
			if (iInternalHeight > iExternalHeight)
			{
				Rotate(pCurNode, iPivotIdx, iInternalIdx);
			}

			// Rotate the tree
			if (!_stackPathToRoot.empty())
			{
				CBSTNode* pParentNode = _stackPathToRoot.top().first;
				int iCurNodeIdx = _stackPathToRoot.top().second;
				Rotate(pParentNode, iCurNodeIdx, iPivotIdx);
			}
			else
				Rotate(nullptr, 0, iPivotIdx);
		}
	}

	return bReBalanced;
}

bool CBinaryST::Search(int _iVal)
{
	CBSTNode* pCurNode = m_pNodeRoot;
	while (pCurNode != nullptr)
	{
		// Check if current node contains the value we are looking for
		if (_iVal == pCurNode->m_iVal)
		{
			return true;
		}

		// Get child link to traverse
		int iChildIdx = (_iVal <= pCurNode->m_iVal) ? 0 : 1;

		// Traverse
		pCurNode = pCurNode->GetChildNode(iChildIdx);
	}

	return false;
}

CBSTNode*& CBinaryST::GetRootNode()
{
	return m_pNodeRoot;
}

bool CBinaryST::Rotate(CBSTNode* _pNodeTreeParent, int _iRotRootIdx, int _iPivotIdx)
{
	CBSTNode* pNodeRotRoot;
	if (_pNodeTreeParent == nullptr)
	{
		pNodeRotRoot = m_pNodeRoot;
	}
	else
	{
		pNodeRotRoot = _pNodeTreeParent->GetChildNode(_iRotRootIdx);
	}

	assert(0 <= _iPivotIdx && _iPivotIdx <= 1);

	CBSTNode* pNodePivot = pNodeRotRoot->GetChildNode(_iPivotIdx);
	if (pNodeRotRoot == nullptr || pNodePivot == nullptr)
		return false;

	int iInternalIdx = (_iPivotIdx + 1) % 2;
	CBSTNode* pNodeInternal = pNodePivot->GetChildNode(iInternalIdx);

	// Rewire old root nodes pivot pointer to pivots internal tree root
	pNodeRotRoot->SetChildNode(_iPivotIdx, pNodeInternal);

	// Rewire pivots internal tree pointer to old root
	pNodePivot->SetChildNode(iInternalIdx, pNodeRotRoot);

	// Update tree heights for pivot and old root node
	if (pNodeInternal)
	{
		pNodeRotRoot->m_arriSubTreeHeights[_iPivotIdx] = std::max(
			pNodeInternal->m_arriSubTreeHeights[0] + 1,
			pNodeInternal->m_arriSubTreeHeights[1] + 1
		);
	}
	else
	{
		pNodeRotRoot->m_arriSubTreeHeights[_iPivotIdx] = 0;
	}
	pNodePivot->m_arriSubTreeHeights[iInternalIdx] = std::max(
		pNodeRotRoot->m_arriSubTreeHeights[0] + 1,
		pNodeRotRoot->m_arriSubTreeHeights[1] + 1
	);

	// Rewire tree parent's root pointer to pivot
	if (_pNodeTreeParent)
		_pNodeTreeParent->SetChildNode(_iRotRootIdx, pNodePivot);
	else
		m_pNodeRoot = pNodePivot;

	return true;
}

void CBinaryST::DeleteTree(CBSTNode* _pCurNode)
{
	if (_pCurNode != nullptr)
	{
		DeleteTree(_pCurNode->GetChildNode(0));
		DeleteTree(_pCurNode->GetChildNode(1));
		delete _pCurNode;
	}
}



void CBinaryST::PreOrderOp(std::function<void(int)> _fn)
{
	PreOrderOp(_fn, m_pNodeRoot);
}

void CBinaryST::PreOrderOp(std::function<void(int)> _fn, CBSTNode * _pCurNode)
{
	if (_pCurNode != nullptr)
	{
		_fn(_pCurNode->m_iVal);
		PreOrderOp(_fn, _pCurNode->GetChildNode(0));
		PreOrderOp(_fn, _pCurNode->GetChildNode(1));
	}
}

void CBinaryST::PostOrderOp(std::function<void(int)> _fn)
{
	PostOrderOp(_fn, m_pNodeRoot);
}

void CBinaryST::PostOrderOp(std::function<void(int)> _fn, CBSTNode * _pCurNode)
{
	if (_pCurNode != nullptr)
	{
		PostOrderOp(_fn, _pCurNode->GetChildNode(0));
		PostOrderOp(_fn, _pCurNode->GetChildNode(1));
		_fn(_pCurNode->m_iVal);
	}
}

void CBinaryST::InOrderOp(std::function<void(int)> _fn)
{
	InOrderOp(_fn, m_pNodeRoot);
}

void CBinaryST::InOrderOp(std::function<void(int)> _fn, CBSTNode * _pCurNode)
{
	if (_pCurNode != nullptr)
	{
		InOrderOp(_fn, _pCurNode->GetChildNode(0));
		_fn(_pCurNode->m_iVal);
		InOrderOp(_fn, _pCurNode->GetChildNode(1));
	}
}