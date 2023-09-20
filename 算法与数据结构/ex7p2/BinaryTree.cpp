#include <stdio.h>
#include<queue>
#include <iostream>
#include <list>

using namespace std;

template <typename T>
class BinaryTreeNode				//二叉树节点
{
public:
	T data;							//数据，左右
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;

	BinaryTreeNode()				//二叉树节点两种初始化方式
	{
		data = data();
		left = nullptr;
		right = nullptr;
	}
	BinaryTreeNode(T SetData)		
	{
		data = SetData;
		left = nullptr;
		right = nullptr;
	}

	~BinaryTreeNode()				//析构
	{
		//cout << "??" << endl;
	//	delete &data;
	}

};

template<typename T>
class ListFlags				//定义分隔符
{
public:
	char NullSubtreeFlag = '^';
	char LeftDelimitFlag = '(';
	char RightDelimitFlag = ')';
	char MiddleDelimitFlag = ',';

	bool IsNodeData(T data)
	{
		if (data != NullSubtreeFlag)
			if (data != LeftDelimitFlag)
				if (data != RightDelimitFlag)
					if (data != MiddleDelimitFlag)
						return true;
		return false;
	}

	

	bool IsNullNode(T data)
	{
		if(data == NullSubtreeFlag)
		{
			return true;
		}
		return false;
	}

	

};
//
template<>
class ListFlags<string>			//定义分隔符
{
public:
	string NullSubtreeFlag = "^";
	string LeftDelimitFlag = "(";
	string RightDelimitFlag = ")";
	string MiddleDelimitFlag = ",";
	/*char NullSubtreeFlag = '^';
	char LeftDelimitFlag = '(';
	char RightDelimitFlag = ')';
	char MiddleDelimitFlag = ',';*/

	bool IsNodeData(string data)
	{
		if (data != NullSubtreeFlag)
			if (data != LeftDelimitFlag)
				if (data != RightDelimitFlag)
					if (data != MiddleDelimitFlag)
						return true;
		return false;
	}

	bool IsNullNode(string data)
	{
		if (data == NullSubtreeFlag)
		{
			return true;
		}
		return false;
	}
};

using namespace std;
template <typename T>
class BinaryTree					//二叉树类
{
	
public:
	BinaryTreeNode<T>* root;		//根

	BinaryTree()					//初始化
	{
		root = nullptr;
	}


	void Dispose()					//递归清除（从root）
	{
		if (root != nullptr)
		{
			Dispose(root->left);
			Dispose(root->right);
			delete root;
		}
		root = nullptr;
	}

	void Dispose(BinaryTreeNode<T>* p)//递归清除（从p）
	{
		if (p != nullptr)
		{
			Dispose(p->left);
			Dispose(p->right);
			delete p;
		}
	}

	void ShowPreOrder()				//从头开始 先根 遍历（root 和 任意一个）
	{
		BinaryTreeNode<T>* p = root;
		if (p != nullptr)
		{
			cout << p->data << " ";
			ShowPreOrder(p->left);
			ShowPreOrder(p->right);
		}
		cout << endl;
	}

	void ShowPreOrder(BinaryTreeNode<T>* p)
	{
		if (p != nullptr)
		{
			cout << p->data << " ";
			ShowPreOrder(p->left);
			ShowPreOrder(p->right);
		}
	}

	void ShowInOrder()			//从头开始 中根 遍历（root 和 任意一个）
	{
		BinaryTreeNode<T>* p = root;
		if (p != nullptr)
		{
			ShowInOrder(p->left);
			cout << p->data << " ";
			ShowInOrder(p->right);
		}
		cout << endl;
	}

	void ShowInOrder(BinaryTreeNode<T>* p)
	{
		if (p != nullptr)
		{
			ShowInOrder(p->left);
			cout << p->data << " ";
			ShowInOrder(p->right);
		}
	}

	void ShowPostOrder()		//从头开始 后根 遍历（root 和 任意一个）
	{
		BinaryTreeNode<T>* p = root;
		if (p != nullptr)
		{
			ShowPostOrder(p->left);
			ShowPostOrder(p->right);
			cout << p->data << " ";
		}
		cout << endl;
	}

	void ShowPostOrder(BinaryTreeNode<T>* p)
	{
		if (p != nullptr)
		{
			ShowPostOrder(p->left);
			ShowPostOrder(p->right);
			cout << p->data << " ";
		}
	}

	void ShowLevelOrder()			//从头开始 按层次遍历
	{
		BinaryTreeNode<T>* p = root;	//根
		queue<BinaryTreeNode<T>*> q;	//缓存层

		if (p != nullptr)q.push(p);		//从root开始
		int Level_Count = 0;			//记录层数

		while (q.size() > 0)
		{
			cout << Level_Count << ":";	//输出层数

			int LevelLength = q.size();	//记录该层有多少个节点
			for (int i = 0; i < LevelLength; i++)
			{
				p = q.front();
				cout << p->data << " ";						//输出节点
				if (p->left != nullptr) q.push(p->left);	//将左右节点纳入缓冲
				if (p->right != nullptr) q.push(p->right);
				q.pop();									//弹出该节点
			}
			cout << endl;
			Level_Count++;									//多层计数
		}
	}

	static BinaryTree<T> ByOneList(list<T> mylist)				//通过list建立完全二叉树
	{
		BinaryTree<T>* BT = new BinaryTree<T>();				//用于返回的树
		if (mylist.size() > 0)
		{
			BinaryTreeNode<T>** Nodes = new BinaryTreeNode<T>*[mylist.size() + 1];	//新建所有nodes

			list<int>::iterator it = mylist.begin();			//循环初始化每一个nodes
			for (int i = 0; i < mylist.size(); i++)
			{
				Nodes[i] = new BinaryTreeNode<T>(*it);
				it++;
			}
			BT->root = Nodes[0];								//链接根
			for (int i = 0; i < mylist.size(); i++)				//循环，利用公式链接左右节点，没链接默认nullptr
			{
				int LeftIndex = 2 * (i + 1) - 1;				//2 * n
				int RightIndex = 2 * (i + 1) -1 + 1;			//2 * n + 1  ,由于数组从0开始n=i+1，计算结果回归到数组index = k - 1


				if (LeftIndex < mylist.size())					//链接节点
				{
					Nodes[i]->left = Nodes[LeftIndex];
				}
				if (RightIndex < mylist.size())
				{
					Nodes[i]->right = Nodes[RightIndex];
				}
			}
		}
		return *BT;
	}

	static BinaryTree<string> ByOneStringList(string str)				//通过list建立完全二叉树
	{
		ListFlags<string> LF;
		BinaryTree<string>* BT = new BinaryTree<string>();				//用于返回的树
		vector<string> mylist;
		for (int i = 0; i < str.length(); i++)
		{
			string tempbuf = "";
			string nowchar = str.substr(i, 1);
			if (LF.IsNodeData(str.substr(i, 1)))
			{
				while (LF.IsNodeData(str.substr(i,1)))
				{
					tempbuf = tempbuf + str[i];
					i++;
				}
				mylist.push_back(tempbuf);
				mylist.push_back(str.substr(i, 1));
			}
			else
			{
				mylist.push_back(str.substr(i, 1));
			}
			
		}
		int index = 0;
		BT->root = MakeNodesByList(mylist, &LF, index);
		return *BT;
	}

	static BinaryTree<T> ByOneList(vector<T> mylist,ListFlags<T>* LF)				//通过list建立完全二叉树
	{
		BinaryTree<T>* BT = new BinaryTree<T>();				//用于返回的树
		int index = 0;
		BT->root = MakeNodesByList(mylist, LF, index);
		return *BT;
	}

	static BinaryTreeNode<T>* MakeNodesByList(vector<T> mylist, ListFlags<T>* LF, int& index)//列表，标记字符，从index开始扫描，返回待扫描的index
	{
		BinaryTreeNode<T>* BTN = nullptr;
		if (index >= mylist.size())			
		{
			return BTN;
		}

		T NowItem = mylist[index];
		if (LF->IsNodeData(NowItem))
		{
			BTN = new BinaryTreeNode<T>(NowItem);
			index++;
			NowItem = mylist[index];
			if (NowItem == LF->LeftDelimitFlag)
			{
				index++;	//‘（’
				BTN->left = MakeNodesByList(mylist, LF, index);
				index++;	//‘，’
				BTN->right = MakeNodesByList(mylist, LF, index);
				index++;	//‘）’
			}
		}
		if (LF->IsNullNode(NowItem))
		{
			index++;	//空的就跳
		}
		return BTN;

	}

	~BinaryTree()
	{
		Dispose();
	}
};

//template<typename T>
//class ListFlags				//定义分隔符
//{
//public:
//	char NullSubtreeFlag = '^';
//	char LeftDelimitFlag = '(';
//	char RightDelimitFlag = ')';
//	char MiddleDelimitFlag = ',';
//
//	bool IsNodeData(T data)
//	{
//		switch (data)
//		{
//		case NullSubtreeFlag:
//		case LeftDelimitFlag:
//		case RightDelimitFlag:
//		case MiddleDelimitFlag:
//			return false;
//		default:
//			return true;
//		}
//	}
//
//	bool IsNullNode(T data)
//	{
//		switch (data)
//		{
//		case NullSubtreeFlag:
//			return true;
//		default:
//			return false;
//		}
//	}
//};

