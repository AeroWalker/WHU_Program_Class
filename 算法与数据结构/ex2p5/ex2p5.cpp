#include "../dsa/CStu.hpp"
#include <iostream>
using namespace dsaUtils;

int main()
{
	//分别初始化int数组和Cstu数组
	int iArr[5]={1,2,3,4,5};
	CStu stuArr[5] = {
	{10020, "张三", 17, 65},
	{10085, "李四", 18.9, 75},
	{10078, "王五", 19.2, 85},
	{10096, "周六", 19.5, 55},
	{10053, "谢七", 12.2, 99} };

	//分别输出int、Cstu
	cout << "int数组为" << endl;
	for (int i : iArr)
	{
		cout << i << " ";
	}

	cout << endl << "Cstu数组为" << endl;
	for (CStu u : stuArr)
	{
		cout << u << " " << endl;
	}
	
}