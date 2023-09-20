#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "../dsa/dsaUtils.h"
#pragma comment (lib,"../x64/Debug/dsa.lib")

using namespace std;
using namespace dsaUtils;

int main()
{
	//按照大小排序
	int arr[20];//初始化
	ArrTools::rand_arr(arr, 20,-99,99);

	//排序并输出
	sort(arr, arr + 19, [](int a, int b) {return a > b; });
	ArrTools::show_arr(arr, 20);

	//重新随机，按照绝对值排序
	srand(time(0));
	ArrTools::rand_arr(arr, 20, -99, 99);
	sort(arr, arr + 19, [](int a, int b) {return abs(a) > abs(b); });
	ArrTools::show_arr(arr, 20);
	return 0;
}