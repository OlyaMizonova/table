#pragma once
#include"TArrayTable.h"
#include"TTable.h"

template<class TKey, class TValue>
class  TScanTable :public TArrayTable<TKey, TValue> {
public:
	using TArrayTable::TArrayTable;
	bool find(TKey key)override {
		DataCount;
		for (int i = 0; i < DataCount; i++)
		{
			efficiency++;
			if (pRecs[i].key == key)
			{
				currPos = i;
				return true;
			}
		}
		currPos = DataCount;
		return false;
	}

	bool isFull()override {
		return DataCount == tabSize; }
	bool insert(const TRecord<TKey,TValue>& rec)override {
		if (isFull() || find(rec.key)) 
		{
			throw  -1; 
		}
		pRecs[DataCount] = rec;
		efficiency++;
		DataCount++;
		return true;
	}
	void Delete(TKey key)override {
		if (!find(key)) { throw - 1; }
		pRecs[currPos] = pRecs[DataCount - 1];
		DataCount--;
		efficiency++;
	}

	void reset() override {
		currPos = 0;
	}
	void goNext()override {
		currPos++;
	}
	bool isEnd() override {
		return currPos == DataCount;
	};

	TKey getKey()override {
		return pRecs[currPos].key;
	};
	TValue getValue()override {
		return pRecs[currPos].value;
	}
	TRecord<TKey, TValue>& getRec() {
		return pRecs[currPos];
	}

	bool isEmpty() {
		for (int i = 0; i < tabSize; i++) {
			if (pRecs[i].valid) { return false; }
			efficiency++;
		}
		return true;
	}
};
