#include <iostream>
#include "../dsa/SequencedList.hpp"

using namespace std;
using namespace dsaUtils;

int main()
{
	//初始化
	SequencedList<int> a(2);

	//测试添加
	a.push_back(123);
	a.push_back(456);
	cout << a << "是否空满" << a.full() << a.empty() << endl;

	//测试插入
	a.push_back(789);
	a.insert(2, 888);

	//测试index和contains和删除
	cout << "888的有么" << a.contains(888) << endl;
	cout << "888的位置" << a.index(888) << endl;
	a.remove(888);

	//测试输出
	cout << a << endl;
	cout << a.str() << endl;
	cout << "开头为" << a[0];
	a[0] = 999;
	cout << "开头为" << a[0];
}