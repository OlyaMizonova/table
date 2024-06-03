#pragma once
#include"THashTable.h"
template<class Key, class Value>
class TArrayHash :public THashTable<Key, Value> {
protected:
	TRecord<Key, Value>* pRecs;
	int MaxSize, step, currPos, Free;
	TRecord<Key, Value> Empty, Del;
public:
	TArrayHash(int max_ss = 100, int steP = 3) {
		MaxSize = max_ss;
		step = steP;
		pRecs = new TRecord<Key, Value>[MaxSize];
		Empty.key = -1;
		Del.key = -2;
		for (int i = 0; i < MaxSize; i++)
		{
			pRecs[i] = Empty;
		}
	}
	void reset() override {
		for (currPos = 0; currPos < MaxSize; currPos++) {
			if ((!(pRecs[currPos] == Empty)) && (!(pRecs[currPos] == Del))) {
				break;
			}
		}
	}
	bool isEnd() override {
		return currPos == MaxSize;
	}
	void goNext() override {
		currPos++;
		for (; currPos < MaxSize; currPos++) {
			if (!(pRecs[currPos] == Empty) && !(pRecs[currPos] == Del)) {
				break;
			}
		}
	}
	bool find(Key key) override {
		Free = -1;
		currPos = HashFunc(key) % MaxSize;
		for (int t = 0; t < MaxSize; ++t) {
			efficiency++;
			if (pRecs[currPos].key == key) { return true; }
			if (pRecs[currPos] == Empty) { return false; }
			if (pRecs[currPos] == Del && Free == -1) { Free = currPos; }
			currPos = (currPos + step) % MaxSize;
		}
		return false;
	}
	bool isFull() override { return DataCount == MaxSize; }
	bool insert(const TRecord<Key,Value>& rec) override {
		if (isFull()) { throw - 1; }
		bool isFind = find(rec.key);
		if (isFind) { throw - 1; }
		else {
			efficiency++;
			if (Free != -1) { currPos = Free; }
			pRecs[currPos] = rec;
			DataCount++;
			return 1;
		}
	}
	void Delete (Key key) override {
		bool isFind = find(key);
		if (!isFind) { return; }
			pRecs[currPos] = Del;
		efficiency++;
		DataCount--;
	}
	Key getKey() override {
		return pRecs[currPos].key;
	}
	Value getValue()override {
		return pRecs[currPos].value;
	}
};