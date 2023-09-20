#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <vector>
#include <iostream>

#include "../dsa/dsaUtils.h"
#pragma comment (lib,"../x64/Debug/dsa.lib")

using namespace std;




//将vector arr填入n个随机数，范围从min到max
void rand_arr(vector<int>& arr, int n, int min = -99, int max = 99)
{
	//初始化随机种子
	srand(time(NULL));

	//生成随机
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % (max - min + 1) + min;
	}
}



int main()
{
	vector<int> v(20);

	dsaUtils::ArrTools::rand_vec(v); // 使用dsa.lib排序
	//rand_arr(v, 20);				//使用上方排序

	cout << "排序前：" << endl;
	for (auto i : v)
	{
		cout << i << "  ";
	}

	cout << endl << "顺序排序：" << endl;
	sort(v.begin(), v.end(), [](int a, int b) {return a > b; });
	for (auto i : v)
	{
		cout << i << "  ";
	}

	cout << endl << "绝对值排序：" << endl;
	sort(v.begin(), v.end(), [](int a, int b) {return abs(a) > abs(b); });
	for (auto i : v)
	{
		cout << i << "  ";
	}


	return 0;
}