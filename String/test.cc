
#include "String2.h"

//void test()
//{
//	String2 s1("hello world");
//	String2 s2("change world");
//
//	String2 s3(s1);
//	cout<<s1.GetStr()<<endl;
//	cout<<s3.GetStr()<<endl;
//}
//
void test1()
{
	String2 str1 = "hello world";
	String2 str2 = str1;

	printf ("Sharing the memory:\n");
	printf ("/tstr1's address: %x\n", str1.GetStr() );
	printf ("/tstr2's address: %x\n", str2.GetStr() );

	str1[1]='q';
	str2[1]='w';

	printf ("After Copy-On-Write:\n");
	printf ("/tstr1's address: %x\n", str1.GetStr() );
	printf ("/tstr2's address: %x\n", str2.GetStr() );
	cout<<str1.GetLength()<<endl;
}
//void test2()
//{
//	String s1;
//}
//int main()
//{
//	test1();
//}