#include <vector>
#include <iostream>
using namespace std;


int main()
{
	vector<int> v;
	//压栈
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);

	//插入
	v.insert(find_if(v.begin(),v.end(), [](int a) { return a > 3; }), 20); //插入第一个大于3的
	v.insert(v.begin(), 10); //插入开头
	
	for (auto i : v) //遍历输出
	{
		cout << i << " ";
	}
	/*
	相同点：
		存储有序数据；
		可随机访问，下标访问；
		末尾添加元素；
	不同点：

		数组的大小必须指定其长度，线性表可动态地增减；
		数组空间连续，线性表可连续的可分散的；
		数组插入删除需要移动其他元素，而线性表的插入和删除操作相对较快；
		线性表可以是链式存储结构，支持插入和删除的快速操作，但是随机访问的效率比数组低；
		数组可以直接进行数值运算，而线性表需要先将元素取出再进行运算。
	*/
	return 0;
}