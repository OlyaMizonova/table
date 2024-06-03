#pragma once
#include"TTreeTable.h"
#define H_OK 0
#define H_INC 1
#define H_DEC -1
template<class Key, class Value>
class TBalTreeTable:public TTreeTable <Key, Value> {
protected:
	int InsBalTree(TTreeNode<Key, Value>*& pNode, TRecord<Key, Value>rec); //int - is the high changed
	int LeftBalance(TTreeNode<Key, Value>*& pNode);
	int RightBalance(TTreeNode<Key, Value>*& pNode);
public:

	bool insert(const TRecord<Key,Value>& rec)override {
		bool res = TTreeTable<Key,Value>::find(rec.key);
		if (res == true) {
			throw - 1;
		}
		InsBalTree(pRoot, rec);
		return 1;
	}
	int DeleteRec(TTreeNode<Key, Value>*& pNode, Key key){
		int res;
		if (pNode == nullptr) return H_OK;
		efficiency++;
		if (pNode->rec.key > key)
		{
			res = DeleteRec(pNode->pLeft, key);
			if (res != H_OK)
			{
				res = RightBalance(pNode);
			}
		}
		else if (pNode->rec.key < key)
		{
			res = DeleteRec(pNode->pRight, key);
			if (res != H_OK)
			{
				res = LeftBalance(pNode);
			}
		}
		else
		{
			DataCount--;
			if (pNode->pLeft == nullptr && pNode->pRight == nullptr)
			{
				delete pNode;
				pNode = nullptr;
				res = H_DEC;
			}
			else if (pNode->pRight == nullptr && pNode->pLeft != nullptr)
			{
				pNode->rec = pNode->pLeft->rec;
				delete pNode->pLeft;
				pNode->pLeft = nullptr;
				pNode->bal = balOK;
				res = H_DEC;
			}
			else if (pNode->pRight != nullptr && pNode->pLeft == nullptr)
			{
				pNode->rec = pNode->pRight->rec;
				delete pNode->pRight;
				pNode->pRight = nullptr;
				pNode->bal = balOK;
				res = H_DEC;
			}
			else
			{
				TTreeNode<Key, Value>* l, * r;
				l = pNode->pLeft;
				r = pNode->pRight;
				TTreeNode<Key, Value>* min = FindMin(r);
				//TTreeNode* tmp = min;
				int min_key = min->rec.key;
				pNode->rec = min->rec;
				res = RemoveMin(r);

				delete min;
				//delete tmp;
				pNode->pLeft = l;
				pNode->pRight = r;

				if (res != H_OK)
				{
					res = LeftBalance(pNode);
				}

			}
		}
		return res;
	}
	void Delete(Key key)override {
		if (!find(key)) {
			throw - 1;
		}
		DeleteRec(pRoot, key);
	}
	TTreeNode<Key, Value>* FindMin(TTreeNode<Key, Value>* pNode){
		if (pNode == nullptr) {
			return nullptr;
		}
		while (pNode->pLeft != nullptr) {
			pNode = pNode->pLeft;
		}
		return pNode;
	}
	int RemoveMin(TTreeNode<Key, Value>*& pNode);
};

template<class Key, class Value>
int TBalTreeTable<Key, Value>::InsBalTree(TTreeNode<Key, Value>*& pNode, TRecord<Key, Value>rec) {
	int res = H_OK;
	if (pNode == nullptr) {
		pNode = new TTreeNode<Key, Value>(rec);
		res = H_INC;
		DataCount++;
	}
	else if (pNode->rec.key>rec.key) {
		int tmp = InsBalTree(pNode->pLeft, rec);
		if (tmp == H_INC) {
			res = LeftBalance(pNode);
		}
	}
	else if(pNode->rec.key<rec.key) { 
		int tmp = InsBalTree(pNode->pRight, rec);
		if (tmp == H_INC) {
			res = RightBalance(pNode);
		}
	}
	return res;
}

template<class Key, class Value>
int TBalTreeTable<Key, Value>::LeftBalance(TTreeNode<Key, Value>*& pNode) {//при балансировке сам узел может изменяться, поэтому ссылка на указатель
	efficiency++;
	int res = H_OK;
	switch (pNode->bal)
	{
	case balRight:pNode->bal = balOK;
		res = H_OK;
		break;

	case balOK:
		pNode->bal = balLeft;
		res = H_INC; break;
	case balLeft:
		TTreeNode<Key,Value>* p1; TTreeNode<Key, Value>* p2;
		p1 = pNode->pLeft;

		if (pNode->bal == balLeft)
		{
			pNode->pLeft = p1->pRight;
			p1->pRight = pNode;
			pNode->bal = balOK;
			pNode = p1;
			pNode->bal = balOK;
		}
		else
		{
			p2 = p1->pRight;
			p1->pRight = p2->pLeft;
			pNode->pLeft = p2->pRight;
			p2->pLeft = p1;
			p2->pRight = pNode;

			if (p2->bal == balRight)
			{
				p1->bal = balLeft;
				pNode->bal = balOK;
			}
			else
			{
				p1->bal = balOK;
				pNode->bal = balRight;
			}
			pNode = p2;
			pNode->bal = balOK;
		}
		res = H_OK;
	}
	return res;
	//int res = H_OK;
	//switch (pNode->bal) {
	//case balRight: 
	//	pNode->bal = balOK; 
	//	res = H_OK; 
	//	break;
	//case balOK:
	//	pNode->bal = balLeft;
	//	res = H_INC;
	//	break;
	//case balLeft: //нужно проверить балансировку у левого потомка, чтобы понять, какой это случай
	//	TTreeNode<Key, Value>* p1, * p2;
	//	p1 = pNode->pLeft;
	//	if (p1->bal == balLeft) {
	//		pNode->pLeft = p1->pRight;
	//		p1->pRight = pNode;
	//		pNode->bal = balOK;
	//		pNode = p1;
	//		pNode->bal = balOK;
	//	}
	//	else {
	//		p2 = p1->pRight;
	//		p1->pRight = p2->pLeft; //ошибка доступа, р2 - 0
	//		pNode->pLeft = p2->pRight;
	//		p2->pLeft = p1;
	//		p2->pRight = pNode;
	//		if (p2->bal == balRight) {
	//			p1->bal = balLeft;
	//			pNode->bal = balOK;
	//		}
	//		else {
	//			p1->bal = balOK;
	//			pNode->bal = balRight;
	//		}
	//		pNode = p2;
	//		pNode->bal = balOK;
	//	}
	//	res = H_OK;
	//	break;
	//}
	//return res;
	/*efficiency++; int res = H_OK;
	switch (pNode->bal)
	{
	case balRight:
		pNode->bal = balOK; res = H_OK; break;
	case balOK:
		pNode->bal = balLeft; res = H_INC; break;
	case balLeft:
		TTreeNode<Key, Value>* p1, * p2;
		p1 = pNode->pLeft;
		if (p1->bal == balLeft)
		{
			pNode->pLeft = p1->pRight;
			p1->pRight = pNode;
			pNode->bal = balOK;
			pNode = p1;
			pNode->bal = balOK;
		}
		else
		{
			p2 = p1->pRight;
			p1->pRight = p2->pLeft;
			pNode->pLeft = p2->pRight;
			p2->pLeft = p1;
			p2->pRight = pNode;
			if (p2->bal = balRight)
			{
				p1->bal = balLeft;
				pNode->bal = balOK;

			}
			else {
				p1->bal = balOK;
				pNode->bal = balRight;
			}
			pNode = p2; pNode->bal = balOK;
			res = H_OK;
		}
		break;


	default:
		break;
	}
	return res;*/
}

template<class Key, class Value>
int TBalTreeTable<Key, Value>::RightBalance(TTreeNode<Key, Value>*& pNode) { 
	efficiency++;
	/*int res = H_OK;
	switch (pNode->bal)
	{
	case balLeft:
		pNode->bal = balOK;
		res = H_OK;
		break;
	case balOK:
		pNode->bal = balRight;
		res = H_INC;
		break;
	case balRight:
		TTreeNode<Key, Value>* p1, * p2;
		p1 = pNode->pRight;
		if (p1->bal == balRight)
		{
			pNode->pRight = p1->pLeft;
			p1->pLeft = pNode;
			pNode->bal = balOK;
			pNode = p1;
			pNode->bal = balOK;
		}
		else
		{
			p2 = p1->pLeft;
			p1->pLeft = p2->pRight;
			pNode->pRight = p2->pLeft;
			p2->pRight = p1;
			p2->pLeft = pNode;
			if (p2->bal == balLeft)
			{
				p1->bal = balRight;
				pNode->bal = balOK;
			}
			else
			{
				p1->bal = balOK;
				pNode->bal = balLeft;
			}
			pNode = p2;
			pNode->bal = balOK;
			res = H_OK;
		}
		break;
	default:
		break;
	}*/
	int res = H_OK;
	switch (pNode->bal)
	{
	case balLeft:pNode->bal = balOK;
		res = H_OK;
		break;

	case balOK:pNode->bal = balRight;
		res = H_INC; break;
	case balRight:
		TTreeNode<Key, Value>* p1, * p2;
		p1 = pNode->pRight;
		if (pNode->bal == balRight)
		{
			pNode->pRight = p1->pLeft;
			p1->pLeft = pNode;
			pNode->bal = balOK;
			pNode = p1;
			pNode->bal = balOK;
		}
		else
		{
			p2 = p1->pLeft;
			p1->pLeft = p2->pRight;
			pNode->pRight = p2->pLeft;
			p2->pRight = p1;
			p2->pLeft = pNode;

			if (p2->bal == balRight)
			{
				p1->bal = balLeft;
				pNode->bal = balOK;
			}
			else
			{
				p1->bal = balOK;
				pNode->bal = balRight;
			}
			pNode = p2;
			pNode->bal = balOK;
		}
		res = H_OK;
	}
	return res;
	//efficiency++;
	//int res = H_OK;
	//switch (pNode->bal) {
	//case balLeft:
	//	pNode->bal = balOK;
	//	res = H_OK;
	//	break;
	//case balOK:
	//	pNode->bal = balRight;
	//	res = H_INC;
	//	break;
	//case balRight: //нужно проверить балансировку у левого потомка, чтобы понять, какой это случай
	//	TTreeNode<Key, Value>* p1, * p2;
	//	p1 = pNode->pRight;
	//	if (p1->bal == balLeft) {
	//		pNode->pRight = p1->pLeft;
	//		p1->pLeft = pNode;
	//		pNode->bal = balOK;
	//		pNode = p1;
	//		pNode->bal = balOK;
	//	}
	//	else {
	//		p2 = p1->pLeft;
	//		p1->pLeft = p2->pRight;
	//		pNode->pRight = p2->pLeft;
	//		p2->pRight = p1;
	//		p2->pLeft = pNode;
	//		if (p2->bal == balLeft) {
	//			p1->bal = balRight;
	//			pNode->bal = balOK;
	//		}
	//		else {
	//			p1->bal = balOK;
	//			pNode->bal = balLeft;
	//		}
	//		pNode = p2;
	//		pNode->bal = balOK;
	//	}
	//	break;
	//}
	//return res;
}

//template<class Key, class Value>
//int TBalTreeTable<Key, Value>::DeleteRec(TTreeNode<Key, Value>*& pNode, Key key) {
//	int res;
//	if (pNode == nullptr) return H_OK;
//	efficiency++;
//	if (pNode->rec.key > key)
//	{
//		res = DeleteRec(pNode->pLeft, key);
//		if (res != H_OK)
//		{
//			res = RightBalance(pNode);
//		}
//	}
//	else if (pNode->rec.key < key)
//	{
//		res = DeleteRec(pNode->pRight, key);
//		if (res != H_OK)
//		{
//			res = LeftBalance(pNode);
//		}
//	}
//	else
//	{
//		DataCount--;
//		if (pNode->pLeft == nullptr && pNode->pRight == nullptr)
//		{
//			delete pNode;
//			pNode = nullptr;
//			res = H_DEC;
//		}
//		else if (pNode->pRight == nullptr && pNode->pLeft != nullptr)
//		{
//			pNode->rec = pNode->pLeft->rec;
//			delete pNode->pLeft;
//			pNode->pLeft = nullptr;
//			pNode->bal = balOK;
//			res = H_DEC;
//		}
//		else if (pNode->pRight != nullptr && pNode->pLeft == nullptr)
//		{
//			pNode->rec = pNode->pRight->rec;
//			delete pNode->pRight;
//			pNode->pRight = nullptr;
//			pNode->bal = balOK;
//			res = H_DEC;
//		}
//		else
//		{
//			TTreeNode<Key, Value>* l, * r;
//			l = pNode->pLeft;
//			r = pNode->pRight;
//			TTreeNode<Key, Value>* min = FindMin(r);
//			//TTreeNode* tmp = min;
//			int min_key = min->rec.key;
//			pNode->rec = min->rec;
//			res = RemoveMin(r);
//
//			delete min;
//			//delete tmp;
//			pNode->pLeft = l;
//			pNode->pRight = r;
//
//			if (res != H_OK)
//			{
//				res = LeftBalance(pNode);
//			}
//
//		}
//	}
//	return res;
//	//int res = H_OK;
//	//efficiency++;
//	///* if(pNode==nullptr) return N_OK; //- если не писать иф не файнд*/
//	//if (pNode->rec.key > key) {
//	//	res = DeleteRec(pNode->pLeft, key);
//	//	if (res != H_OK) { //удалили слева, слева высота уменьшилась - нужно запустить балансировку справа
//	//		res = RightBalance(pNode);
//	//	}
//	//}
//	//else if (pNode->rec.key < key) {
//	//	res = DeleteRec(pNode->pRight, key);
//	//	if (res != H_OK) { //удалили справа, справа высота уменьшилась - нужно запустить балансировку слева
//	//		res = LeftBalance(pNode);
//	//	}
//	//}
//	//else {
//	//	DataCount--;
//	//	if (pNode->pLeft == nullptr || pNode->pRight == nullptr) { //нет потомков
//	//		delete pNode;
//	//		pNode = nullptr;
//	//		res = H_DEC;
//	//	}
//	//	else if (pNode->pLeft == nullptr && pNode->pRight != nullptr) { // один потомок справа
//	//		pNode->rec = pNode->pRight->rec;
//	//		delete pNode->pRight;
//	//		pNode->pRight = nullptr;
//	//		pNode->bal = balOK;
//	//		res = H_DEC;
//	//	}
//	//	else if (pNode->pLeft != nullptr && pNode->pRight == nullptr) { // один потомок слева
//	//		pNode->rec = pNode->pLeft->rec;
//	//		delete pNode->pLeft;
//	//		pNode->pLeft = nullptr;
//	//		pNode->bal = balOK; 
//	//		res = H_DEC;
//	//	}
//	//	else { //оба потомка
//	//		TTreeNode<Key, Value> * r;
//	//		r = pNode->pRight;
//	//		TTreeNode<Key, Value>* minim = FindMin(r);//ищем минимальное справа
//	//		res = RemoveMin(r); //рекурсивная функция, которая исключает из поддерева минимальную вершину (не удаляет!)
//	//							// и выполняет перебалансировку (может изменить r)
//	//		pNode->rec = minim->rec;//записали значение в наш узел
//	//		delete minim;//удалили саму отвязанную вершину
//	//		pNode->pRight = r;//привязали правую ветку
//	//		if (res != H_OK) {
//	//			res = LeftBalance(pNode);
//	//		}
//	//	}
//	//}
//	//return res;
//}
//findmin сами
template<class Key, class Value>
int TBalTreeTable<Key, Value>::RemoveMin(TTreeNode<Key, Value>*& pNode) {
	/* int res = H_OK;
	efficiency++;
	if (pNode->pLeft == nullptr) {
		pNode = pNode->pRight;//неважно есть или нет изначально правый потомок, если нет, то нулптр и все ок,
							//если нет, то не потеряли потомка
		res = H_DEC;
	}
	else {
		res = RemoveMin(pNode->pLeft);
		if (res != H_OK) {
			res = RightBalance(pNode);
		}
	}
	return res;*/
	int res = H_OK;
		if (!pNode) {
			return res; 
		}

		TTreeNode<Key,Value>* rightNode = pNode->pRight;
		if (!pNode->pLeft)
		{
			pNode = rightNode;
			res = H_DEC;
		}
		else
		{
			res = RemoveMin(pNode->pLeft);
			if (res != H_OK)
			{
				res = RightBalance(pNode);
			}
		}
		return res;
}
/* 

int LeftBalanse(TTreeNode*& pNode)
{
eff++;
int res = H_OK;
switch (pNode->bal)
{
case balRight:pNode->bal = balOK;
res = H_OK;
break;

case balOK:
	pNode->bal = balLeft;
	res = H_INC; break;
case balLeft:TTreeNode* p1;TTreeNode* p2;
	p1 = pNode->pLeft;

	if (p1->bal == balLeft)
	{
	pNode->pLeft = p1->pRight;
	p1->pRight = pNode;
	pNode->bal = balOK;
	pNode = p1;
	pNode->bal = balOK;
	}
else
{
p2 = p1->pRight;
p1->pRight = p2->pLeft;
pNode->pLeft = p2->pRight;
p2->pLeft = p1;
p2->pRight = pNode;

if (p2->bal == balRight)
{
p1->bal = balLeft;
pNode->bal = balOK;
}
else
{
p1->bal = balOK;
pNode->bal = balRight;
}
pNode = p2;
pNode->bal = balOK;
}
res = H_OK;
}
return res;
}
int RightBalanse(TTreeNode*& pNode)
{
eff++;
int res = H_OK;
switch (pNode->bal)
{
case balLeft:pNode->bal = balOK;
res = H_OK;
break;

case balOK:pNode->bal = balRight;
res = H_INC; break;
case balRight:TTreeNode* p1, * p2;
p1 = pNode->pRight;
if (p1->bal == balRight)
{
pNode->pRight = p1->pLeft;
p1->pLeft = pNode;
pNode->bal = balOK;
pNode = p1;
pNode->bal = balOK;
}
else
{
p2 = p1->pLeft;
p1->pLeft = p2->pRight;
pNode->pRight = p2->pLeft;
p2->pRight = p1;
p2->pLeft = pNode;

if (p2->bal == balRight)
{
p1->bal = balLeft;
pNode->bal = balOK;
}
else
{
p1->bal = balOK;
pNode->bal = balRight;
}
pNode = p2;
pNode->bal = balOK;
}
res = H_OK;
}
return res;
}

int DeleteRec(TTreeNode*& pNode, TKey key)
{
int res = H_OK; eff++;
if (pNode == NULL) return H_OK;
if (pNode->rec.key > key)
{
res = DeleteRec(pNode->pLeft, key);
if (res != H_OK)
res = RightBalanse(pNode);
}
else if (pNode->rec.key < key)
{
res = DeleteRec(pNode->pRight, key);
if (res != H_OK) res = LeftBalanse(pNode);
}
else
{
DataCount--;
if (pNode->pRight == NULL && pNode->pLeft == NULL)
{
delete pNode;
pNode = NULL;
res = H_DEC;
}
else if (pNode->pRight == NULL)
{
pNode->rec = pNode->pLeft->rec;
delete pNode->pLeft;
pNode->pLeft = NULL;
pNode->bal = balOK;
res = H_DEC;
}
else if (pNode->pLeft == NULL)
{
pNode->rec = pNode->pRight->rec;
delete pNode->pRight;
pNode->pRight = NULL;
pNode->bal = balOK;
res = H_DEC;
}
else
{
TTreeNode* l, * r;
l = pNode->pLeft; r = pNode->pRight;
TTreeNode* min = FindMin(r);
res = RemoveMin(r);
pNode->rec = min->rec;
delete min;
pNode->pLeft = l; pNode->pRight = r;
if (res != H_OK) res = LeftBalanse(pNode);

}
}
return res;
}
TTreeNode* FindMin(TTreeNode* r)
{
eff++;
if (pRoot == NULL) return NULL;
TTreeNode* curr = pRoot->pRight;
while (curr->pLeft != NULL) curr = curr->pLeft;
return curr;
}
int RemoveMin(TTreeNode*& pNode)
{
eff++;
int res = H_OK;
if (pNode->pLeft == NULL)
{
pNode = pNode->pRight;
res = H_DEC;
}
else
{
res = RemoveMin(pNode->pLeft);
if (res != H_OK)
res = RightBalanse(pNode);
}
return res;
}

}
*/