#include"gtest.h"
#include"TTreeTable.h"
TEST(TTreeTable, can_create_sort_table)
{
	using MyClass = TTreeTable<int, int>;
	ASSERT_NO_THROW(MyClass ts;);
}

TEST(TTreeTable, can_insert_record) {
	TTreeTable<int, int> ts;
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
}

TEST(TTreeTable, cant_insert_existind_record) {
	TTreeTable<int, int> ts;
	for (int i = 0; i < 80; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	TRecord<int, int>rec(1, 1);
	ASSERT_ANY_THROW(ts.insert(rec));
}

TEST(TTreeTable, can_delete_record) {
	TTreeTable<int, int> ts;
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	int t = 0;
	int k = ts.getDataCount();
	for (int i = 0; i < k; i++) {
		ASSERT_NO_THROW(ts.Delete(t));
		t++;
	}
	EXPECT_EQ(ts.isEmpty(), 1);
	EXPECT_EQ(ts.getDataCount(), 0);
}

TEST(TTreeTable, can_find_record) {
	TTreeTable<int, int> ts;
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	ASSERT_NO_THROW(ts.find(0));
	EXPECT_EQ(ts.find(0), 1);
	EXPECT_EQ(ts.find(100), 0);
}