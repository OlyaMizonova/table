#pragma once
#include"TScanTable.h"
#include"TTable.h"
enum typeSort { select, merge, quick };

template<class TKey, class TValue>
class TSortTable : public TScanTable<TKey, TValue> {
protected:
    TRecord<TKey, TValue>* pBuf;
    typeSort sT;
public:
    TSortTable(int sz = 10) :TScanTable<TKey, TValue>(sz) {
        pBuf = new TRecord<TKey, TValue>[tabSize];
        sT = quick;
    }
    TSortTable(const TScanTable& ts) {
        DataCount = ts.DataCount;
        tabSize = ts.tabSize;
        pRecs = new TRecord<TKey, TValue>[tabSize];
        for (int i = 0; i < DataCount; i++) {
            pRecs[i] = ts.pRecs[i];
        }
        if (sT == select) { sortSelect(); }
        else if (sT == merge) { sortMerge(); }
        else if (sT == quick) { sortQuick(); }
    }
    bool isFull()override {
        return DataCount == tabSize;
    }
    void setSortType(typeSort t) { sT = t; }
    bool find(TKey key) override;
    bool insert(const TRecord<TKey, TValue>& rec)override;
    void Delete(TKey key) {
        if (!find(key))
        {
            throw - 1;
        }
        for (int i = currPos; i < DataCount - 1; i++)
        {
            pRecs[i] = pRecs[i + 1];
            efficiency++;
        }
        DataCount--;
    }
    void sortSelect() {
        sortSel(DataCount);
    }
    void sortSel(int n);
    void swap(TRecord<TKey, TValue>* rec1, TRecord<TKey, TValue>* rec2);


    void sortMerge() {
        mergeS(0, DataCount - 1);
    }
    void mergeS(int l, int r);
    void merge(int left, int mid, int right);

    void sortQuick() { QSort(0, DataCount - 1); };
    void QSort(int l, int r);


};

template< class TKey, class TValue>
void TSortTable <TKey, TValue>::QSort(int l, int r) {
    int m = (l + r) / 2;
    TKey key = pRecs[m].key;
    int i = l, j = r;
    while (i < j) {
        while (pRecs[i].key < key) { ++i; efficiency++;
        }
        while (pRecs[j].key < key) { --j; efficiency++;
        }
        if (i <= j) {
            std::swap(pRecs[i], pRecs[j]);
            ++i; --j;
        }
    }
    //now j<i
    if (l < j) { QSort(l, j); }
    if (i < r) { QSort(i, r); }
}

template<class TKey, class TValue>
bool TSortTable<TKey, TValue> ::find(TKey key) {
    int l = 0, r = DataCount - 1;
    while (l <= r) {
        efficiency++;
        int m = (l + r) / 2;
        if (key == pRecs[m].key) {
            currPos = m;
            return true;
        }
        if (pRecs[m].key > key) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    currPos = l;
    return false;
}

template<class TKey, class TValue>
bool TSortTable <TKey, TValue>::insert(const TRecord<TKey, TValue>& rec) {
    bool res = find(rec.key);
    if (!res) {
        if (isFull())
        {
            throw - 1;
        }
        for (int i = DataCount - 1; i >= currPos; i--)
        {
            pRecs[i + 1] = pRecs[i];
            efficiency++;
        }
        pRecs[currPos] = rec;
        efficiency++;
        DataCount++;
        return 1;
    }
    else {
        throw - 1;
    }
}

template<class TKey, class TValue>
void TSortTable <TKey, TValue>::merge(int left, int mid, int right) {
    int n = right - left + 1;
    pBuff = new TRecord<TKey, TValue>[n];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        efficiency++;
        if (pRecs[i].key < pRecs[j].key) {
            pBuff[k] = pRecs[i];
            i++;
        }
        else {
            pBuff[k] = pRecs[j];
            j++;
        }
        k++;
    }
    if (i > mid) {
        while (j <= right) {
            efficiency++;
            pBuff[k] = pRecs[j];
            j++;
            k++;
        }
    }
    else {
        while (i <= mid) {
            efficiency++;
            pBuff[k] = pRecs[i];
            i++;
            k++;
        }
    }
    k = 0;
    for (int q = left; q < right + 1; q++) {
        efficiency++;
        pRecs[q] = pBuff[k];
        k++;
    }
    delete[]pBuff;
}

template<class TKey, class TValue>
void TSortTable <TKey, TValue>::mergeS(int left, int right) {
    if (left == right) {
        return;
    }
    int mid = (left + right) / 2;
    mergeS(left, mid);
    mergeS(mid + 1, right);
    merge(left, mid, right);
}

template<class TKey, class TValue>
void TSortTable <TKey, TValue>::swap(TRecord<TKey, TValue>* rec1, TRecord<TKey, TValue>* rec2){
    TRecord<TKey, TValue>tmp = *rec1;
    *rec1 = *rec2;
    *rec2 = tmp;
}

template<class TKey, class TValue>
void TSortTable <TKey, TValue>::sortSel(int n) {
    for (int i = 0; i < n; i++) {
        int pos = i;
        Key min_a = pRecs[i];
        for (int j = i; j < n; j++) {
            efficiency++;
            if (pRecs[j] < min_a) {
                pos = j;
                min_a = a[j];
            }
        }
        swap(&pRecs[i], &pRecs[pos]);
    }
}

