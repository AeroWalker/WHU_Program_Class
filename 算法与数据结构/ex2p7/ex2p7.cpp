#include <queue>
#include <iostream>
using namespace std;

//队列解决约瑟夫环，all为人数，jump为数数值，返回最终剩余的那个
int JosephusProblem(int all, int jump)
{
	//创建一个队列，并向其中添加编号
	queue<int> q;
	for (int i = 1; i <= all; i++)
	{
		q.push(i);
	}

	//循环筛选出，直到剩余最后一个
	while (q.size() > 1)
	{
		//略过前面的人：报数为1到jump-1，把这些人放到队尾
		for (int j = 1; j < jump; j++)
		{
			q.push(q.front());
			q.pop();
		}

		//报数jump的，弹出他
		cout << "Pop out:" << q.front() << endl;
		q.pop();
	}

	//剩下最后一人输出
	cout << "Winner:" << q.front() << endl;
	return q.front();
}

//数组+flag解决
int JosephusProblem2(int all, int jump)
{
	//记录数组和总体计数
	vector<bool> q(all,true);
	int count = all;
	int pointer = -1;

	//循环到没人
	while (count > 0)
	{
		for (int i = 0; i < jump;) //报数中，到jump-1
		{
			pointer++;
			pointer %= all;
			if (q[pointer] == true)
			{
				i++;
			}
		}
		cout << "Pop out:" << pointer + 1  << endl; //报数=下表+1
		q[pointer] = false;	//标记推出，减少一人
		count--;
	}

	return 0;
}


//百度百科的代码，用于检测结果
int WinnerCheck(int all, int jump)
{
	int f = 0;
	for (int i = 1; i <= all; i++) f = (f + jump) % i;
	return f + 1 ;
}


int main()
{
	//自己的代码输出
	JosephusProblem(30,9); //queue实现
	JosephusProblem2(30,9); //vector+flag实现
	//百度的代码
	cout << "Winner:" << WinnerCheck(30, 9) << endl;
}