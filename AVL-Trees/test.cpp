#include <list>
#include "catch.hpp"
#include "BinaryST.h"

TEST_CASE("Insert")
{
	CBinaryST tree;
	tree.Insert(10);
	tree.Insert(5);
	tree.Insert(34);
	tree.Insert(2);
	tree.Insert(9);
	tree.Insert(20);
	tree.Insert(3);

	REQUIRE(tree.GetRootNode()->m_iVal == 10);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 5);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 34);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->m_iVal == 2);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_iVal == 9);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->m_iVal == 20);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1)->m_iVal == 3);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(1) == nullptr);

	SECTION("Check Balance Factors")
	{
		REQUIRE(tree.GetRootNode()->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetBalanceFactor() == 1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
	}
}

TEST_CASE("Search")
{
	CBinaryST tree;
	tree.Insert(10);
	tree.Insert(5);
	tree.Insert(34);
	tree.Insert(2);
	tree.Insert(9);
	tree.Insert(20);
	tree.Insert(3);

	SECTION("Searching for existing values")
	{
		REQUIRE(tree.Search(10) == true);
		REQUIRE(tree.Search(5) == true);
		REQUIRE(tree.Search(9) == true);
		REQUIRE(tree.Search(34) == true);
		REQUIRE(tree.Search(20) == true);
		REQUIRE(tree.Search(2) == true);
		REQUIRE(tree.Search(3) == true);
	}

	SECTION("Searching for non-existant values")
	{
		REQUIRE(tree.Search(1) == false);
		REQUIRE(tree.Search(0) == false);
		REQUIRE(tree.Search(-0) == false);
		REQUIRE(tree.Search(-1) == false);
	}
}

TEST_CASE("Delete")
{
	CBinaryST tree;
	tree.Insert(10);
	tree.Insert(5);
	tree.Insert(34);
	tree.Insert(2);
	tree.Insert(9);
	tree.Insert(20);

	SECTION("Test deleting leaf node")
	{
		bool bResult = tree.Delete(20);
		REQUIRE(bResult == true);
		REQUIRE(tree.GetRootNode()->m_iVal == 10);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 5);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 34);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->m_iVal == 2);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_iVal == 9);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1) == nullptr);

		SECTION("Check Balance Factors")
		{
			REQUIRE(tree.GetRootNode()->GetBalanceFactor() == -1);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
		}
	}

	SECTION("Test deleting non-leaf node with no right branch")
	{
		bool bResult = tree.Delete(34);
		REQUIRE(bResult == true);
		REQUIRE(tree.GetRootNode()->m_iVal == 10);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 5);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 20);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->m_iVal == 2);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_iVal == 9);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1) == nullptr);

		SECTION("Check Balance Factors")
		{
			REQUIRE(tree.GetRootNode()->GetBalanceFactor() == -1);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
		}
	}

	SECTION("Test deleting root node of tree with nodes below")
	{
		bool bResult = tree.Delete(10);
		REQUIRE(bResult == true);
		REQUIRE(tree.GetRootNode()->m_iVal == 20);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 5);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 34);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->m_iVal == 2);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_iVal == 9);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1) == nullptr);

		SECTION("Check Balance Factors")
		{
			REQUIRE(tree.GetRootNode()->GetBalanceFactor() == -1);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
		}
	}

	SECTION("Test deleting non existing value")
	{
		bool bResult = tree.Delete(100);
		REQUIRE(bResult == false);
		REQUIRE(tree.GetRootNode()->m_iVal == 10);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 5);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 34);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->m_iVal == 2);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_iVal == 9);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->m_iVal == 20);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0) == nullptr);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1) == nullptr);

		SECTION("Check Balance Factors")
		{
			REQUIRE(tree.GetRootNode()->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == -1);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
			REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetBalanceFactor() == 0);
		}

	}

	SECTION("Test deleting root node of tree with nothing below it")
	{
		CBinaryST tree2;
		tree2.Insert(11);
		bool bResult = tree2.Delete(11);
		REQUIRE(bResult == true);
		REQUIRE(tree2.GetRootNode() == nullptr);
	}
}

TEST_CASE("Rotate root right")
{
	CBinaryST tree;
	tree.Insert(10);
	tree.Insert(5);
	tree.Insert(34);
	tree.Insert(2);
	tree.Insert(9);
	tree.Insert(20);
	tree.Insert(3);

	bool bResult = tree.Rotate(nullptr, 0, 0);
	REQUIRE(bResult == true);
	REQUIRE(tree.GetRootNode()->m_iVal == 5);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 2);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 10);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_iVal == 3);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->m_iVal == 9);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->m_iVal == 34);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->GetChildNode(0)->m_iVal == 20);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->GetChildNode(1) == nullptr);

	SECTION("Check Balance Factors")
	{
		REQUIRE(tree.GetRootNode()->GetBalanceFactor() == 1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == 1);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == 1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->GetChildNode(0)->GetBalanceFactor() == 0);
	}
}

TEST_CASE("Trigger: Rotate Root Left with Insert")
{
	CBinaryST tree;
	tree.Insert(5);
	tree.Insert(2);
	tree.Insert(10);
	tree.Insert(9);
	tree.Insert(34);
	tree.Insert(20);

	REQUIRE(tree.GetRootNode()->m_iVal == 10);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 5);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 34);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->m_iVal == 2);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_iVal == 9);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->m_iVal == 20);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(1) == nullptr);

	SECTION("Check Balance Factors")
	{
		REQUIRE(tree.GetRootNode()->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetBalanceFactor() == 0);
	}
}

TEST_CASE("Trigger: Rotate Root Right with Insert")
{

	CBinaryST tree;
	tree.Insert(5);
	tree.Insert(2);
	tree.Insert(10);
	tree.Insert(1);
	tree.Insert(3);
	tree.Insert(0);

	REQUIRE(tree.GetRootNode()->m_iVal == 2);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 1);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 5);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->m_iVal == 0);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->m_iVal == 3);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->m_iVal == 10);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->GetChildNode(1) == nullptr);

	SECTION("Check Balance Factors")
	{
		REQUIRE(tree.GetRootNode()->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1)->GetBalanceFactor() == 0);
	}
}

TEST_CASE("Rotate non-root left")
{
	CBinaryST tree;
	tree.Insert(10);
	tree.GetRootNode()->SetChildNode(0, new CBSTNode(2));
	tree.GetRootNode()->SetChildNode(1, new CBSTNode(34));
	tree.GetRootNode()->GetChildNode(0)->SetChildNode(1, new CBSTNode(5));
	tree.GetRootNode()->GetChildNode(1)->SetChildNode(0, new CBSTNode(20));
	tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->SetChildNode(0, new CBSTNode(3));
	tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->SetChildNode(1, new CBSTNode(9));

	tree.GetRootNode()->m_arriSubTreeHeights = { 3, 2 };
	tree.GetRootNode()->GetChildNode(0)->m_arriSubTreeHeights = { 0, 2 };
	tree.GetRootNode()->GetChildNode(1)->m_arriSubTreeHeights = { 1, 0 };
	tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_arriSubTreeHeights = { 1, 1 };
	tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->m_arriSubTreeHeights = { 0, 0 };
	tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0)->m_arriSubTreeHeights = { 0, 0 };
	tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1)->m_arriSubTreeHeights = { 0, 0 };

	bool bResult = tree.Rotate(tree.GetRootNode(), 0, 1);
	REQUIRE(bResult == true);
	REQUIRE(tree.GetRootNode()->m_iVal == 10);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->m_iVal == 5);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->m_iVal == 34);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->m_iVal == 2);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->m_iVal == 9);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->m_iVal == 20);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1)->m_iVal == 3);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetChildNode(1) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(0) == nullptr);
	REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetChildNode(1) == nullptr);

	SECTION("Check Balance Factors")
	{
		REQUIRE(tree.GetRootNode()->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetBalanceFactor() == -1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetBalanceFactor() == 1);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(1)->GetChildNode(0)->GetBalanceFactor() == 0);
		REQUIRE(tree.GetRootNode()->GetChildNode(0)->GetChildNode(0)->GetChildNode(1)->GetBalanceFactor() == 0);
	}
}

TEST_CASE("Test Pre-Oder Processing (depth first)")
{
	CBinaryST tree;
	tree.Insert(10);
	tree.Insert(5);
	tree.Insert(34);
	tree.Insert(2);
	tree.Insert(9);
	tree.Insert(20);
	tree.Insert(3);

	std::list<int> listResult;
	auto testFn = [&listResult](int _iVal) {
		listResult.push_back(_iVal);
	};

	tree.PreOrderOp(testFn);

	std::list<int> listExpected = { 10, 5, 2, 3, 9, 34, 20 };
	REQUIRE(listResult == listExpected);
}

TEST_CASE("Test Post-Oder Processing (depth first)")
{
	CBinaryST tree;
	tree.Insert(10);
	tree.Insert(5);
	tree.Insert(34);
	tree.Insert(2);
	tree.Insert(9);
	tree.Insert(20);
	tree.Insert(3);

	std::list<int> listResult;
	auto testFn = [&listResult](int _iVal) {
		listResult.push_back(_iVal);
	};

	tree.PostOrderOp(testFn);

	std::list<int> listExpected = { 3, 2, 9, 5, 20, 34, 10 };
	REQUIRE(listResult == listExpected);
}

TEST_CASE("Test In-Oder Processing (depth first)")
{
	CBinaryST tree;
	tree.Insert(10);
	tree.Insert(5);
	tree.Insert(34);
	tree.Insert(2);
	tree.Insert(9);
	tree.Insert(20);
	tree.Insert(3);

	std::list<int> listResult;
	auto testFn = [&listResult](int _iVal) {
		listResult.push_back(_iVal);
	};

	tree.InOrderOp(testFn);

	std::list<int> listExpected = { 2, 3, 5, 9, 10, 20, 34 };
	REQUIRE(listResult == listExpected);
}