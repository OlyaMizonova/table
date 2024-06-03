#pragma once
#include"TTable.h"
#include<stack>
/* 
ациклический связный граф
бинарное дерево
		root
	/			\
	0			1
/		\	/		\
1		2   3		4
дерево поиска, каждой вершине приписано значение,
сравниваем их, все ключи слева меньше вершины, справа все больше вершины
пример
		  50
	/			\
	25		   100
/		\	/		\
1		28  70		400
сбалансированное дерево

идеально сбалансированное дерево количество вершин 
справа и слева для каждого узла отличается не более чем на 1

другая балансировка (avl)
высота не должна различаться больше чем на 1
*/
enum typeBal{balLeft, balRight, balOK};
template<class Key, class Value>
struct TTreeNode{
	TRecord<Key, Value> rec;
	TTreeNode<Key, Value> *pLeft, *pRight;
	typeBal bal; //bal ok, bal left, bal right
	TTreeNode(TRecord<Key,Value> rrecc) {
		pRight = pLeft = nullptr;
		rec = rrecc;
		bal = balOK;//ok
	}
};

template<class Key, class Value>
class TTreeTable :public TTable<Key, Value> {
protected:
	TTreeNode<Key, Value> *pRoot, *pCurrent, *pPrevious;
	std::stack<TTreeNode<Key, Value>*> st;
	int CurrPos, lvl;
public:
	/* full как в линейном списке*/
	TTreeTable() {
		CurrPos = -1;
		pRoot = nullptr;
		pCurrent = nullptr;
		pPrevious = nullptr;
		lvl = 0;
	}
	~TTreeTable() {
		deleteTreeTab(pRoot);
	}
	bool find(Key key)override {
		/*pCurrent = pRoot;
		pPrevious = nullptr;
		while (pCurrent!=nullptr) {
			efficiency++;
			if (pCurrent->rec.key == key) {
				return true;
			}
			else {
				pPrevious = pCurrent;
				if (pCurrent->rec.key > key) {
					pCurrent = pCurrent->pLeft;
				}
				if (pCurrent->rec.key < key) {
					pCurrent = pCurrent->pRight;
				}
			}
		}
		if (pCurrent != nullptr) {
			return true;
		}
		else {
			pCurrent = pPrevious;
			return false;
		}*/
		if (pCurrent != nullptr)
		{
			if (pCurrent->rec.key == key)
			{
				return true;
			}
		}
		pCurrent = pRoot; pPrevious = nullptr;
		while (pCurrent != nullptr)
		{
			efficiency++;
			if (pCurrent->rec.key == key) break;
			else {
				pPrevious = pCurrent;
				if (pCurrent->rec.key > key)
				{
					pCurrent = pCurrent->pLeft;
				}
				else {
					pCurrent = pCurrent->pRight;
				}
			}
		}
		if (pCurrent != nullptr) {
			return true;
		}
		else {
			pCurrent = pPrevious;
			return false;
		}
	}
	bool insert(const TRecord<Key,Value>& rec)override {
		/*if (pRoot == nullptr) {
			pCurrent->rec = pRoot->rec = rec;
			pPrevious = nullptr;
		}
		bool res = find(rec.key);
		if (res == true) {
			throw - 1;
		}
		else {
			DataCount++;
			TTreeNode<Key, Value>* pNew = new TTreeNode<Key,Value>(rec);
			if (pCurrent->rec.key > rec.key) {
				pCurrent->pLeft = pNew;
			}
			if (pCurrent->rec.key < rec.key) {
				pCurrent->pRight = pNew;
			}
		}
		return 1;*/
		if (find(rec.key))
		{
			throw -1;
		}
		else
		{
			TTreeNode<Key, Value>* newNode = new TTreeNode<Key, Value>(rec);
			if (pRoot == nullptr)
			{
				pRoot = newNode;

			}
			else
			{
				if (pCurrent->rec.key > rec.key)
				{
					pCurrent->pLeft = newNode;

				}
				else
				{
					pCurrent->pRight = newNode;
				}
			}
			DataCount++;
			return true;
		}
	}
	void deleteTreeTab(TTreeNode<Key, Value>* pNode) {
		if (pNode != nullptr) {
			deleteTreeTab(pNode->pLeft);
			deleteTreeTab(pNode->pRight);
			delete pNode;
		}
	}
	void Delete(Key key)override {
		if (!find(key)) throw - 1;
		TTreeNode<Key, Value>* pDel = pCurrent;
		if (pCurrent->pRight == nullptr)
		{
			if (pPrevious == nullptr)  pRoot = pRoot->pLeft;
			else
			{
				if (pCurrent->rec.key > pPrevious->rec.key)
				{
					pPrevious->pRight = pCurrent->pLeft;
				}
				else
				{
					pPrevious->pLeft = pCurrent->pLeft;
				}
			}

		}
		else if (pCurrent->pLeft == nullptr)
		{
			if (pPrevious == nullptr)  pRoot = pRoot->pRight;
			else
			{
				if (pCurrent->rec.key > pPrevious->rec.key)
				{
					pPrevious->pRight = pCurrent->pRight;
				}
				else
				{
					pPrevious->pLeft = pCurrent->pRight;
				}
			}

		}
		else
		{
			TTreeNode<Key, Value>* tmp = pCurrent->pLeft;
			pPrevious = pCurrent;
			while (tmp->pRight != nullptr)
			{
				efficiency++;
				pPrevious = tmp;
				tmp = tmp->pRight;
			}
			pCurrent->rec = tmp->rec;
			if (pPrevious != pCurrent)
			{
				pPrevious->pRight = tmp->pLeft;
			}
			else
			{
				pPrevious->pLeft = tmp->pLeft;
			}
			pDel = tmp;
		}
		efficiency++;
		delete pDel;
		DataCount--;
		//return true;
		/*TTreeNode<Key, Value>* pDel = pCurrent;
		bool res = find(key);
		if (res == false) { throw - 1; }
		else {
			if (pCurrent->pRight == nullptr) {
				pDel = pCurrent;
				if (pPrevious == nullptr) {
					pRoot = pCurrent->pLeft;
				}
				if (pPrevious->rec.key > pCurrent->rec.key) {
					pPrevious->pLeft = pCurrent->pLeft;
				}
				else {
					pPrevious->pRight = pCurrent->pRight;
				}
			}
			else if (pCurrent->pLeft == nullptr) {
				pDel = pCurrent;
				if (pPrevious == nullptr) {
					pRoot = pCurrent->pRight;
				}
				if (pPrevious->rec.key > pCurrent->rec.key) {
					pPrevious->pLeft = pCurrent->pLeft;
				}
				else {
					pPrevious->pRight = pCurrent->pRight;
				}
			}
		}
	delete pDel;*/
	}
	bool isEnd()override {
		return CurrPos>=DataCount;
	}
	void reset() override{
		TTreeNode<Key, Value>* pNode = pCurrent = pRoot;
		while (!st.empty()) { st.pop(); }
		CurrPos = 0;
		while (pNode != nullptr) {
			st.push(pNode);
			pNode = pNode->pLeft;
		}
		//return isEnd();
	}
	void goNext() override{
		if ((!isEnd()) && (pCurrent != nullptr)) {
			TTreeNode<Key, Value>* pNode = pCurrent = pCurrent->pRight;
			st.pop();
			while (pNode != nullptr) {
				st.push(pNode);
				pCurrent = pNode;
				pNode = pNode->pLeft;
			}
			if ((pCurrent == nullptr) && !st.empty()) {
				pCurrent = st.top();
			}
			CurrPos++;
		}
		//return isEnd();
	}
	Key getKey()override { return pCurrent->rec.key; }
	Value getValue()override { return pCurrent->rec.value; }
	bool isFull() override { return false; };
	void PrintTable(std::ostream& os, TTreeNode<Key,Value>* pNode)
	{
		if (pNode != nullptr)
		{
			for (int i = 0; i < lvl; i++)
			{
				os << " ";
			}
			os << pNode->rec.key << std::endl;
			lvl++;
			PrintTable(os, pNode->pRight);
			PrintTable(os, pNode->pLeft);
			lvl--;

		}
	}
	void output(std::ostream& os) {
		PrintTable(os, pRoot);
	}
};