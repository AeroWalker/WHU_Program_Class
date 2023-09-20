#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <vector>
#include "../dsa/dsaUtils.h"
#pragma comment (lib,"../x64/Debug/dsa.lib")

; using namespace std;

#define N 30

void rand_arr(vector<int>& arr, int size = -1, int min = -99, int max = 99)
{
	//初始化随机种子
	srand(time(NULL));


	if (size == -1) size = arr.size();

	//生成随机
	vector<int>::iterator i = arr.begin();
	for (vector<int>::iterator i = arr.begin(); i < arr.begin() + size; i++)
	{
		*i = rand() % (max - min + 1) + min;
	}
}

int main()
{
	//初始化数组，并处理异常
	vector<int>* p;
	try {
		p = new vector<int>(N);
	}
	catch (exception e)
	{
		throw e;
		cout << "New arr failed" << endl;
		exit(1);
	}


	//向p内填充随机数
	dsaUtils::ArrTools::rand_vec(*p);
	//rand_arr(*p);

	cout << "数组为：" << endl;
	for (auto i : *p)
	{
		cout << i << "  ";
	}

	//使用find，寻找50
	vector<int>::iterator p_50 = find(p->begin(), p->end(), 50);
	if (p_50 != p->end())
	{	//找到
		cout << endl << "50存在" << endl;
	}
	else
	{	//没找到
		cout << endl << "50不存在" << endl;
	}

	//使用find，寻找50
	auto p_40_90 = find_if(p->begin(), p->end(), [](int i) {return (i > 40 && i < 90); });
	if (p_40_90 != p->end())
	{	//找到
		cout << "40-90的数存在,为" << *p_40_90 << endl;
	}
	else
	{	//没找到
		cout << "40-90的数不存在" << endl;
	}

	delete p;
}

