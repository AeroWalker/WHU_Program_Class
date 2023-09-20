#include "LoopSLinked.cpp"
#include <iostream>
#define N 30
#define M 3

using namespace std;
int main()
{
	int* arr = new int[N];
	for (int i = 0; i < N; i++)		//直接用数组初始化循环链表
	{
		arr[i] = i + 1;
	}
	LoopSingleLinkedList<int> a = LoopSingleLinkedList<int>(arr, N);



	int countSum = N;	//分别标记还有多少人，报数多少，报到了哪位
	int countJump = 0;
	int* temp = nullptr;
	while (N > 0)				//到没人为止
	{
		countJump = 0;
		while (countJump < M)		//循环到报对应数的
		{
			temp = a.irt();
			if (*temp != -1) countJump++;
		}
		cout << *temp << " ";		//输出，标记为-1
		*temp = -1;
	}

}