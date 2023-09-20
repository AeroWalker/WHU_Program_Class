#include <stdio.h>
#include<queue>
#include <iostream>
#include <list>

using namespace std;

template <typename T>
class BinaryTreeNode				//�������ڵ�
{
public:
	T data;							//���ݣ�����
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;

	BinaryTreeNode()				//�������ڵ����ֳ�ʼ����ʽ
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

	~BinaryTreeNode()				//����
	{
		//cout << "??" << endl;
	//	delete &data;
	}

};

template<typename T>
class ListFlags				//����ָ���
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
class ListFlags<string>			//����ָ���
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
class BinaryTree					//��������
{
	
public:
	BinaryTreeNode<T>* root;		//��

	BinaryTree()					//��ʼ��
	{
		root = nullptr;
	}


	void Dispose()					//�ݹ��������root��
	{
		if (root != nullptr)
		{
			Dispose(root->left);
			Dispose(root->right);
			delete root;
		}
		root = nullptr;
	}

	void Dispose(BinaryTreeNode<T>* p)//�ݹ��������p��
	{
		if (p != nullptr)
		{
			Dispose(p->left);
			Dispose(p->right);
			delete p;
		}
	}

	void ShowPreOrder()				//��ͷ��ʼ �ȸ� ������root �� ����һ����
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

	void ShowInOrder()			//��ͷ��ʼ �и� ������root �� ����һ����
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

	void ShowPostOrder()		//��ͷ��ʼ ��� ������root �� ����һ����
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

	void ShowLevelOrder()			//��ͷ��ʼ ����α���
	{
		BinaryTreeNode<T>* p = root;	//��
		queue<BinaryTreeNode<T>*> q;	//�����

		if (p != nullptr)q.push(p);		//��root��ʼ
		int Level_Count = 0;			//��¼����

		while (q.size() > 0)
		{
			cout << Level_Count << ":";	//�������

			int LevelLength = q.size();	//��¼�ò��ж��ٸ��ڵ�
			for (int i = 0; i < LevelLength; i++)
			{
				p = q.front();
				cout << p->data << " ";						//����ڵ�
				if (p->left != nullptr) q.push(p->left);	//�����ҽڵ����뻺��
				if (p->right != nullptr) q.push(p->right);
				q.pop();									//�����ýڵ�
			}
			cout << endl;
			Level_Count++;									//������
		}
	}

	static BinaryTree<T> ByOneList(list<T> mylist)				//ͨ��list������ȫ������
	{
		BinaryTree<T>* BT = new BinaryTree<T>();				//���ڷ��ص���
		if (mylist.size() > 0)
		{
			BinaryTreeNode<T>** Nodes = new BinaryTreeNode<T>*[mylist.size() + 1];	//�½�����nodes

			list<int>::iterator it = mylist.begin();			//ѭ����ʼ��ÿһ��nodes
			for (int i = 0; i < mylist.size(); i++)
			{
				Nodes[i] = new BinaryTreeNode<T>(*it);
				it++;
			}
			BT->root = Nodes[0];								//���Ӹ�
			for (int i = 0; i < mylist.size(); i++)				//ѭ�������ù�ʽ�������ҽڵ㣬û����Ĭ��nullptr
			{
				int LeftIndex = 2 * (i + 1) - 1;				//2 * n
				int RightIndex = 2 * (i + 1) -1 + 1;			//2 * n + 1  ,���������0��ʼn=i+1���������ع鵽����index = k - 1


				if (LeftIndex < mylist.size())					//���ӽڵ�
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

	static BinaryTree<string> ByOneStringList(string str)				//ͨ��list������ȫ������
	{
		ListFlags<string> LF;
		BinaryTree<string>* BT = new BinaryTree<string>();				//���ڷ��ص���
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

	static BinaryTree<T> ByOneList(vector<T> mylist,ListFlags<T>* LF)				//ͨ��list������ȫ������
	{
		BinaryTree<T>* BT = new BinaryTree<T>();				//���ڷ��ص���
		int index = 0;
		BT->root = MakeNodesByList(mylist, LF, index);
		return *BT;
	}

	static BinaryTreeNode<T>* MakeNodesByList(vector<T> mylist, ListFlags<T>* LF, int& index)//�б�����ַ�����index��ʼɨ�裬���ش�ɨ���index
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
				index++;	//������
				BTN->left = MakeNodesByList(mylist, LF, index);
				index++;	//������
				BTN->right = MakeNodesByList(mylist, LF, index);
				index++;	//������
			}
		}
		if (LF->IsNullNode(NowItem))
		{
			index++;	//�յľ���
		}
		return BTN;

	}

	~BinaryTree()
	{
		Dispose();
	}
};

//template<typename T>
//class ListFlags				//����ָ���
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

