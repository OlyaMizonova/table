#pragma once
#include"THashTable.h"
#include<list>
template<class Key, class Value>
class TListHash :public THashTable<Key, Value> { 
protected:
	std::list <TRecord<Key, Value>>* pList;
	int maxSize, CurrList;
	using MyClass = TRecord<Key, Value>;
	//std::list<TRecord<Key, Value>>::iterator pCurr;
	typename std::list<MyClass>::iterator pCurr;
	//std::_List_iterator<std::_List_val<std::_List_simple_types<_Ty>>> pCurr ;
public:
	TListHash(int maxs = 100) {
		CurrList = 0;
		maxSize = maxs;
		pList = new std::list <TRecord<Key, Value>>[maxs];
		//int pCr = (*pList).begin();
	}
	~TListHash() {
		delete[] pList;
	}

	bool find(Key key) override{
		CurrList = HashFunc(key) % maxSize;
	for (pCurr = pList[CurrList].begin(); 
		pCurr != pList[CurrList].end(); 
		pCurr++) {
		efficiency++;
		if (pCurr->key == key) {
			return true;// а каррент уже на нужном месте
		}
	}
	return false;
	}
	bool insert(const TRecord<Key, Value>& rec) override{
		bool res = find(rec.key);
		if (res) { throw - 1; }
		pList[CurrList].push_front(rec);
		DataCount++;
		return 1;
	}
	void Delete(Key key) override{
		bool res = find(key);
		if (!res) { throw - 1; }
		pList[CurrList].erase(pCurr);
		DataCount--;
	}

	void reset() override{
		CurrList = 0;
		pCurr = pList[CurrList].begin();
		while (pCurr == pList[CurrList].end()) {
			CurrList++;
			if (CurrList != maxSize - 1) {
				pCurr = pList[CurrList].begin();
			}
			else {
				break;
			}
		}
	}
	void goNext() override{
		pCurr++;
		while (pCurr == pList[CurrList].end()) {
			CurrList++;
			if (CurrList != maxSize) {
			    pCurr = pList[CurrList].begin();
			}
			else {
				break;
			}
		}
	}
	bool isEnd() override{
		return CurrList == maxSize;
	}

	Key getKey() override{
		return pCurr->key;
	}
	Value getValue() override {
		return pCurr->value;
	}
	bool isFull()override {
		return DataCount == maxSize; }
};
// преобразовать "std::_List_iterator<std::_List_val<std::_List_simple_types<_Ty>>>" в "int"
