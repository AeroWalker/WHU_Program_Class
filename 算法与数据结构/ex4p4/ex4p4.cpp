#include <iostream>
#include "../dsa/SingleLinkedList.hpp"
#include "../dsa/CStu.hpp"

using namespace dsaUtils;
int main()
{
	CStu cstu[3] = {		//初始化
		{100,"张三",18,20},
		{101,"李四",19,25},
		{102,"王五",20,60}
	};
	SLinkedList<CStu> cs(cstu,3);
	cout << cs << endl;

	cs.push_back(CStu(102, "金六", 20, 60));	//补充和插入
	cs.insert(0,CStu(199, "沈一", 99, 90));
	cs.show();

	cs.removeAt(1);	//移除
	cs.show();


	cs.reverse();	//反序
	cs.show();

	cout << "长度" << cs.count() << endl;
}