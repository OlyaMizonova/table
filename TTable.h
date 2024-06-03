#pragma once
#include<iostream>
#include<string>
//#include<iomanip>
/* 
вектор, лист, хэш таблица, дерево
но общие методы - итерация, поиск, добавление, удаление

иерархия классов, базовый - с интерфэйсом

                        class ttable

tarraytable+       thashtable                  ttreetable
tscantable+   tarrayhash  tlisthash        tavltree   trbtree
tsosttable+

частота встречаемости слов в тексте
*/
template<class TKey, class TValue>
struct TRecord {
    TKey key;
    TValue value;
    bool valid = 0;
    TRecord(TKey keyy = -100000, TValue valuee = -100000) {
        key = keyy;
        value = valuee;
    }
    bool operator ==(const TRecord<TKey, TValue>& rec) {
        return (key == rec.key) && (value==rec.value);
    }
};
template<class TKey, class TValue>
class TTable {
public:
    TTable() { DataCount = efficiency = 0; }
    virtual ~TTable(){}
    virtual bool isFull() = 0;
    virtual bool find(TKey key) = 0;
    //where exactly?
    //if not in table ret position where it should be
    virtual bool insert(const TRecord<TKey,TValue>& rec) = 0;
    virtual void Delete(TKey key) = 0;

    virtual void reset() = 0;
    virtual void goNext() = 0;
    virtual bool isEnd() = 0;
    //get key get value - current
    virtual TKey getKey() = 0;
    virtual TValue getValue() = 0;


    int getDataCount ()const {
        return DataCount;
    }
    int getEfficiency ()const {
        return efficiency;
    }
    bool isEmpty() {
        return DataCount == 0;
    }
    void clearEfficiency(){
        efficiency = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, TTable& t) {
        for (t.reset(); !t.isEnd(); t.goNext()) {
        os << "key: "<<t.getKey() << ", value: " << t.getValue() << '\n';
        }
        return os;
    }
protected:
    int DataCount;
    int efficiency;
};
/*
typedef int TKey;
typedef string TValue;
struct TRecord {
    TKey key;
    TValue value;
};
*/
/*
2 quick - слияние и быстрая 1 медленный выбором
enum typeSort{select, merge, quick}
sorted array
typedef<class T>
class TSortTable : publicTScanTable {
protected:
TRecord* pBuf;
sortType sT;
void sortBuf(){

}
void sortSelect(){

}
void sortMerge(){
    
}
void sortQuick(){

}
void QSort(int l, int r){}
};
*/