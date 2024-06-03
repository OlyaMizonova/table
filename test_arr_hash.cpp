#include"gtest.h"
#include"TArrayHash.h"
TEST(TArrayHash, can_create_array_hash_table)
{
	using MyClass = TArrayHash<int, int>;
	ASSERT_NO_THROW(MyClass ts(););
}

TEST(TArrayHash, can_create_copied_array_hash_table)
{
	using MyClass = TArrayHash<int, int>;
	MyClass ts(100);
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	ASSERT_NO_THROW(MyClass ts1(ts););
}

TEST(TArrayHash, can_assign_array_hash_table)
{
	using MyClass = TArrayHash<int, int>;
	MyClass ts(100);
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	MyClass ts1;
	ASSERT_NO_THROW(ts1 = ts;);
}


TEST(TArrayHash, can_insert_record) {
	TArrayHash<int, int> ts(100);
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
}

TEST(TArrayHash, cant_insert_existind_record) {
	TArrayHash<int, int> ts(100);
	for (int i = 0; i < 80; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	TRecord<int, int>rec(1, 1);
	ASSERT_ANY_THROW(ts.insert(rec));
}

TEST(TArrayHash, can_delete_record) {
	TArrayHash<int, int> ts(200);
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

TEST(TArrayHash, can_find_record) {
	TArrayHash<int, int> ts(100);
	for (int i = 0; i < 100; i++) {
		TRecord<int, int>rec(i, i);
		ASSERT_NO_THROW(ts.insert(rec));
	}
	ASSERT_NO_THROW(ts.find(0));
	EXPECT_EQ(ts.find(0), 1);
	EXPECT_EQ(ts.find(100), 0);
}