#include "../dsa/CStu.hpp"
#include <iostream>
using namespace std;
using namespace dsaUtils;

int main()
{
	//初始化Cstu类
	CStu stuArr[5] = {
	{10020, "张三", 17, 65},
	{10085, "李四", 18.9, 75},
	{10078, "王五", 19.2, 85},
	{10096, "周六", 19.5, 55},
	{10053, "谢七", 12.2, 99} };

	//使用cout << 重载输出
	cout << "Cstu重载 <<" << endl;
	for (CStu u : stuArr)
	{
		cout << u << endl;
	}

	//使用.str()输出
	cout << endl << "Cstu.str" << endl;
	for (CStu u : stuArr)
	{
		cout << u.str(true) << endl;
	}

	return 0;
}