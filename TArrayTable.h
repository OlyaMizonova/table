#pragma once
#include"TTable.h"

template<class TKey, class TValue>
class  TArrayTable :public TTable<TKey, TValue> {
protected:
	int tabSize;
	int currPos;
	TRecord<TKey, TValue>* pRecs;
public:
	TArrayTable(int sz = 10) {
		tabSize = sz;
		currPos = 0;
		pRecs = new TRecord<TKey, TValue>[sz];
		//DataCount;
	}
	~TArrayTable()override {
		delete[]pRecs;
	}
	TArrayTable(TArrayTable<TKey, TValue>&tb){
		tabSize = tb.tabSize;
		DataCount = tb.DataCount;
		currPos = tb.currPos;
		efficiency = tb.efficiency;
		pRecs = new TRecord<TKey, TValue>[tabSize];
		for (int i = 0; i < DataCount; i++) {
			pRecs[i] = tb.pRecs[i];
		}
	}
	bool operator==(const TArrayTable<TKey, TValue>& tb) {
		if (DataCount != tb.DataCount || 
			tabSize!=tb.tabSize) {
			return false;
		}
		for (int i = 0; i < DataCount; i++) {
			if ((pRecs[i].valid == 1 && tb.pRecs[i].valid == 1) && (!(pRecs[i] == tb.pRecs[i]))) {
				return false;
			}
		}
		return true;
	}
	TArrayTable<TKey, TValue>& operator=(TArrayTable<TKey, TValue>& tb) {
		if (tb == *this) { return *this; }
		delete[]pRecs;
		tabSize = tb.tabSize;
		DataCount = tb.DataCount;
		currPos = tb.currPos;
		efficiency = tb.efficiency;
		pRecs = new TRecord<TKey, TValue>[DataCount];
		for (int i = 0; i < DataCount; i++) {
			pRecs[i] = tb.pRecs[i];
		}
		return *this;
	}
	int getTabSize()const { return tabSize; }
	virtual TKey getKey() { return pRecs[currPos].key; }
};
