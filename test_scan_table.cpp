#include"gtest.h"
#include"TScanTable.h"
TEST(TScanTable, can_create_scan_table)
{
	using MyClass = TScanTable<int, int>;
	ASSERT_NO_THROW(MyClass ts(););
}

TEST(TScanTable, can_create_copied_scan_table)
{
	using MyClass = TScanTable<int, int>;
	MyClass ts(100);
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	ASSERT_NO_THROW(MyClass ts1(ts););
}

TEST(TScanTable, can_assign_scan_table)
{
	using MyClass = TScanTable<int, int>;
	MyClass ts(100);
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	MyClass ts1;
	ASSERT_NO_THROW(ts1 = ts;);
}


TEST(TScanTable, can_insert_record) {
	TScanTable<int, int> ts(100);
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
}

TEST(TScanTable, cant_insert_existind_record) {
	TScanTable<int, int> ts(100);
	for (int i = 0; i < 80; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	TRecord<int, int>rec(1, 1);
	ASSERT_ANY_THROW(ts.insert(rec));
}

TEST(TScanTable, can_delete_record) {
	TScanTable<int, int> ts(11);
	for (int i = 0; i < 3; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	int t = 0, dc= ts.getDataCount();
	EXPECT_EQ(ts.getDataCount(), 3);
	for (int i = 0; i < dc; i++) {
		ASSERT_NO_THROW(ts.Delete(t));
		t++;
	}
	EXPECT_EQ(ts.getDataCount(), 0);
	//EXPECT_EQ(ts.isEmpty(), 1);
}

TEST(TScanTable, cant_delete_from_empty_or_not_existing) {
	TScanTable<int, int> ts(11);
	ASSERT_ANY_THROW(ts.Delete(5));
	for (int i = 0; i < 11; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	ASSERT_ANY_THROW(ts.Delete(12));
}

TEST(TScanTable, can_find_record) {
	TScanTable<int, int> ts(100);
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	ASSERT_NO_THROW(ts.find(0));
	EXPECT_EQ(ts.find(0), 1);
	EXPECT_EQ(ts.find(100), 0);
}