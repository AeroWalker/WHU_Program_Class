#include <iostream>
#include <algorithm>
#include "../dsa/dsaUtils.h"
#pragma comment (lib,"../x64/Debug/dsa.lib")
#include "../ex3p3/Robot.cpp"

using namespace std;
using namespace dsaUtils;

int main()
{
	Robot r[] = {				//初始化
		{10001,"王一",150},
		{10002,"李二",100},
		{10003,"菜三",99},
		{10004,"刘四",19},
		{10005,"坤五",97},
		{10006,"赵六",59},
		{10007,"郭七",59},
		{10008,"沈八",120},
		{10009,"国九",140},
	};

	cout << "ID排序" << endl;
 	sort(r, r + 9, Robot::CompareItem(0)); // 用id
	ArrTool2<Robot>::show_arr(r, 9);

	cout << "Name排序" << endl;
	sort(r, r + 9, Robot::CompareItem(1)); // 用Name
	ArrTool2<Robot>::show_arr(r, 9);

	cout << "IQ排序" << endl;
	sort(r, r + 9, Robot::CompareItem(2)); // 用IQ
	ArrTool2<Robot>::show_arr(r, 9);

	cout << "<>排序" << endl;
	sort(r, r + 9, Robot::CompareItem(3)); // 用默认大于小于
	ArrTool2<Robot>::show_arr(r, 9);
	return 0;
}