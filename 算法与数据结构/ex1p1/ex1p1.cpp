#include <vector>
#include<string>
#include<iostream>

using namespace std;

int main(int argc, char* argv[])
{
	//测试的两个参数 123.1 456.2
	// 获得两个加数，将其转化为double，相加
	double sum = stod(argv[1]) + stod(argv[2]);
	cout << argv[1] << "和" << argv[2] << "为" << sum << endl;

	//初始化vector以及对应文字，使用基于范围for循环输出
	vector<string> v = { "Hello","C++","World","!" };
	for (string s : v)
	{
		cout << s << " ";
	}

	return 0;
}