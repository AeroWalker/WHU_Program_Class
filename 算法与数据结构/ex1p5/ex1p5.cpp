#include<vector>
#include"stu.cpp"
#include <string>
#include <iostream>

#include "../dsa/dsaUtils.h"
#pragma comment (lib,"../x64/Debug/dsa.lib")
#include "../dsa/Student.hpp"

using namespace dsaUtils;

using namespace std;

int main()
{
	//初始化vector<int>
	vector<int> v;
	v.push_back(123);
	v.push_back(456);
	v.push_back(789);

	//分别向第二个插入123，和第一个大于400的元素插入888
	v.insert(v.begin() + 1, 124);
	v.insert(find_if(v.begin(), v.end(), [](int a) {return a > 400; }), 888);
	ArrTools::show_vec(v);


	//初始化学生数组
	student s[] = { 
		{1001, "张三", 17, 65},
		{1002, "李四", 18.9, 75},
		{1004, "王五", 19.2, 85}, 
		{1005, "周六", 19.5, 55},
		{1008, "谢七", 12.2, 99} };
	vector<student> vs(s,s+5);
	vs.push_back(student(999, "super张三", 18.88, 100));

	for (auto i : vs)
	{
		cout << i << endl;
	}



	cout << endl  << "下面使用lib输出" << endl;

	//使用大Student初始化（dsa.lib里）
	Student S[] = {
		{10020, "张三", 17, 65},
		{10085, "李四", 18.9, 75},
		{10078, "王五", 19.2, 85},
		{10096, "周六", 19.5, 55},
		{10053, "谢七", 12.2, 99} };
	vector<Student> vS(S, S + 5);
	vS.push_back(Student(999, "super张三", 18.88, 100));

	for (auto i : vS)
	{
		cout << i << endl;
	}

	cout << "前两个人学号比较结果" << (vS[1] < vS[2]) << endl;
	return 0;
}

