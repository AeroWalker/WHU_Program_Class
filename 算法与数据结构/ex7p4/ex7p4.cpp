#include"../ex7p2/BinaryTree.cpp"
#include <iostream>
#include <list>

int main()
{

	ListFlags<char> LF;
	string Input = "1(2(4(8,^),5(^,9)),3(6(1,1),7(^,1(1,^))))";
	vector<char> mylist;
	for (int i = 0; i < Input.size(); i++)
	{
		
		mylist.push_back(Input[i]);

	}
		
	
	BinaryTree<char> binaryTree = BinaryTree<char>::ByOneList(mylist,&LF);

	binaryTree.ShowPreOrder();          //四种方式遍历
	binaryTree.ShowInOrder();
	binaryTree.ShowPostOrder();
	binaryTree.ShowLevelOrder();

	cout << "支持多字符版本" << endl;
	BinaryTree<string> binaryTree2 = BinaryTree<string>::ByOneStringList("123(22(43(81,^),522(^,93)),34(36(1,1),77(^,15(18,^))))");

	binaryTree2.ShowPreOrder();          //四种方式遍历
	binaryTree2.ShowInOrder();
	binaryTree2.ShowPostOrder();
	binaryTree2.ShowLevelOrder();
	return 0;

}