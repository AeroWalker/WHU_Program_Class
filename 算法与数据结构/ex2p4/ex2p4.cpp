#include <queue>
#include <iostream>

using namespace std;

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main()
{
    // 定义并初始化队列对象
    queue<int> q ( { 1, 5, 8, 7, 4, 6 });

    //向队列中追加一个对象
    q.push(7);

    // 定义栈对象
    stack<int> s;

    // 将队列中的元素依次压入栈中
    cout << "从队列取出顺序（压入stack顺序）" << endl;
    while (!q.empty()) {
        s.push(q.front());
        cout << q.front() << " ";
        q.pop();
    }

    // 将栈中的元素依次弹出并输出
    cout << endl << "弹出stack顺序" << endl;
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }

    return 0;
}