#include"../ex7p2/BinaryTree.cpp"
#include <iostream>
#include <list>

int main()
{
	list<int> mylist;
	for (int i = 0; i < 15; i++)
	{
		mylist.push_back(i);
	}
	BinaryTree<int> binaryTree = BinaryTree<int>::ByOneList(mylist);

	binaryTree.ShowPreOrder();          //四种方式遍历
	binaryTree.ShowInOrder();
	binaryTree.ShowPostOrder();
	binaryTree.ShowLevelOrder();

	return 0;

}