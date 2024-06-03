#pragma once
#include"TTable.h"
template<class Key, class Value>
class THashTable :public TTable<Key, Value>{
public:	int HashFunc(Key key) { 
		return key%11+5;
	}
};


