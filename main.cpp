#include <cstdlib>
#include<time.h>
#include<iostream>
#include<list>
#include<fstream>
#include<set>

#include "gtest.h"
#include"TSortTable.h"
#include"TArrayHash.h"
#include"TListHash.h"
#include"TTreeTable.h"
#include"TBalTreeTable.h"


//#define TESTS

#ifdef TESTS
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#endif 

#ifndef TESTS

int main()
{
	TScanTable <int, int> t1(1000);
	TSortTable <int, int> t2(1000);
	TArrayHash<int, int> t3(1000, 3);
	TListHash<int, int> t4(1000);
	TTreeTable<int, int> t5;
	TBalTreeTable<int, int>t6;
	std::set<int> s;
	/*for (int i = 0; i < 100; i++) {
		int r = i*11;
		TRecord<int, int>rec(r, i);
		t3.insert(rec);
	}
	t3.Delete(44);
	t3.Delete(88);
	t3.clearEfficiency();
	int e = t3.find(110);
	int eff = t3.getEfficiency();
	std::cout <<"res of find "<< e<<'\n'<<"eff of find "<<eff;*/
	/*TRecord<int, int>rec(10,1);
	t6.insert(rec);
	TRecord<int, int>rec1(5, 2);
	t6.insert(rec1);
	TRecord<int, int>rec2(15, 3);
	t6.insert(rec2);
	TRecord<int, int>rec3(3, 4);
	t6.insert(rec3);
	TRecord<int, int>rec4(6, 5);
	t6.insert(rec4);
	TRecord<int, int>rec5(20, 6);
	t6.insert(rec5);
	TRecord<int, int>rec6(17, 7);
	t6.insert(rec6);
	t6.output();
	TRecord<int, int>rec7(16, 8);
	t6.insert(rec7);*/
	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		int r = i;
		TRecord<int, int>rec(r, i);
		bool w = s.count(rec.key);
		while (w) {
			rec.key = rand();
			w = s.count(rec.key);
		}
		s.insert(rec.key);
		t1.insert(rec);
		t2.insert(rec);
		t3.insert(rec);
		t4.insert(rec);
		t5.insert(rec);
		t6.insert(rec);
	}
	t5.clearEfficiency();
	t6.clearEfficiency();
	t6.Delete(511);
	t5.Delete(511);
	//t1.clearEfficiency();
	//t2.clearEfficiency();
	//t3.clearEfficiency();
	//t4.clearEfficiency();
	//t5.clearEfficiency();
	//t6.clearEfficiency();
	//t1.find(10000);
	//t2.find(10000);
	//t3.find(10000);
	//t4.find(10000);
	//t5.find(10000);
	//t6.find(10000);


	std::ofstream fs, fs1;
	fs.open("D:/study/yaziki_i_metodi/git_labs/table/data.txt");
	fs1.open("D:/study/yaziki_i_metodi/git_labs/table/data1.txt");
	//fs << t4;
	t5.output(fs);
	t6.output(fs1);
	fs.close();
	fs1.close();
	//std::cout << "\n efficiency scan = "<< t1.getEfficiency();
	//std::cout << "\n efficiency sort = " << t2.getEfficiency();
	//std::cout << "\n efficiency hash array = " << t3.getEfficiency();
	//std::cout << "\n efficiency hash list = " <<t4.getEfficiency();
	std::cout << "\n efficiency tree tab = " << t5.getEfficiency();
	std::cout << "\n efficiency bal tree = " << t6.getEfficiency();
	
}
#endif // !TESTS

