//#include"gtest.h"
//#include"TBalTreeTable.h"
//TEST(TBalTreeTable, can_create_sort_table)
//{
//	using MyClass = TBalTreeTable<int, int>;
//	ASSERT_NO_THROW(MyClass ts;);
//}
//
//TEST(TBalTreeTable, can_insert_record) {
//	TBalTreeTable<int, int> ts;
//	for (int i = 0; i < 100; i++) {
//		TRecord<int, int>rec(i, i);
//		ASSERT_NO_THROW(ts.insert(rec));
//	}
//}
//
//TEST(TBalTreeTable, cant_insert_existind_record) {
//	TBalTreeTable<int, int> ts;
//	for (int i = 0; i < 80; i++) {
//		TRecord<int, int>rec(i, i);
//		ASSERT_NO_THROW(ts.insert(rec));
//	}
//	TRecord<int, int>rec(1, 1);
//	ASSERT_ANY_THROW(ts.insert(rec));
//}
//
//TEST(TBalTreeTable, can_delete_record) {
//	TBalTreeTable<int, int> ts;
//	for (int i = 0; i < 4; i++) {
//		TRecord<int, int>rec(i, i);
//		ASSERT_NO_THROW(ts.insert(rec));
//	}
//	int t = 0;
//	int k = ts.getDataCount();
//	for (int i = 0; i < k; i++) {
//		ASSERT_NO_THROW(ts.Delete(t));
//		t++;
//	}
//	/*EXPECT_EQ(ts.isEmpty(), 1);
//	EXPECT_EQ(ts.getDataCount(), 0);*/
//}
//
////TEST(TBalTreeTable, can_find_record) {
////	TBalTreeTable<int, int> ts;
////	for (int i = 0; i < 100; i++) {
////		TRecord<int, int>rec(i, i);
////		ASSERT_NO_THROW(ts.insert(rec));
////	}
////	ASSERT_NO_THROW(ts.find(0));
////	EXPECT_EQ(ts.find(0), 1);
////	EXPECT_EQ(ts.find(100), 0);
////}