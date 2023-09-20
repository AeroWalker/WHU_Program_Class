#include <stdlib.h>
#include"..\dsa\Student.hpp"
#include <iostream>
using namespace std;

template <typename T> //模板类
void myswap(T& a, T& b) //交换，利用引用
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

int main()
{
	//初始化
	dsaUtils::Student a(1, "zhang", 18, 100);
	dsaUtils::Student b(2, "wang", 19, 60);
	cout << "交换前:" << endl << a << endl << b << endl;

	//交换
	swap<dsaUtils::Student>(a, b);
	cout << "交换后:" << endl << a << endl << b << endl;
}