#include <vector>

#include"../dsa/dsaUtils.h"
#include "../dsa/CStu.hpp"
#include <iostream>
#pragma comment (lib,"../x64/Debug/dsa.lib")

using namespace std;
using namespace dsaUtils;

int main()
{
	//初始化一个线性表
	CStu S[] = {
	{10020, "张三", 17, 65},
	{10085, "李四", 18.9, 75},
	{10078, "王五", 19.2, 85},
	{10096, "周六", 19.5, 55},
	{10053, "谢七", 12.2, 99} };
	vector<CStu> vS(S, S + 5);


	//分别向开头，和“周六”插入
	vS.insert(vS.begin(), CStu(10086,"蔡徐坤",2.5,100));
	vS.insert(find_if(vS.begin(),vS.end(), [](CStu a) {return a._name == "周六"; }), CStu(10010, "小黑子", 25, 66));

	//循环输出
	for (auto i : vS)
	{
		cout << i << endl;
	}

	/*
	相对于任务二，任务三利用template初始化了vector<CStu>：实验二线性表元素为int，这里为CStu
	相同：
		结构相同，均为线性表，支持线性表的操作
	不同：
		元素不同：int和CStu，导致内存占用不同
		操作不同：前者支持默认int加减乘除操作，sort等，后者需要自己写
	*/
	return 0;
}