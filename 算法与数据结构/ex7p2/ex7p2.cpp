// ex7p2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"BinaryTree.cpp"

int main()
{
    BinaryTree<int> binaryTree;
    BinaryTreeNode<int>* nodes[10];//结点{ 0,1,2,3,4,5,6,7,8,9 } 奇了怪了，直接初始化赋值会析构出问题

    for (int i = 0; i < 10; i++)//New 方法出来就没问题了
    {
        *(nodes + i) = new BinaryTreeNode<int>(i);
    }

    //手动建立结点
    binaryTree.root =   nodes[0];
    nodes[0]->left =    nodes[1];
    nodes[0]->right =    nodes[2];
    nodes[1]->left =     nodes[3];
    nodes[1]->right =    nodes[4];
    nodes[2]->left =     nodes[5];
    nodes[3]->left =     nodes[6];
    nodes[3]->right =    nodes[7];
    nodes[4]->right =    nodes[8];
    nodes[6]->left =     nodes[9];

    binaryTree.ShowPreOrder();          //四种方式遍历
    binaryTree.ShowInOrder();
    binaryTree.ShowPostOrder();
    binaryTree.ShowLevelOrder();

    binaryTree.Dispose();               //回收
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
