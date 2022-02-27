#include "BinarySearch.hpp"
#include "BinarySearchTree.hpp"

int main(char* argc, char** argv[])
{
	//int tem[] = { 1,1,3,3,5,5,5,9,9 };
	//int count = sizeof(tem) / sizeof(int);
	//cout << floor(tem, count, 2) << endl;
	//cout << ceil(tem, count, 2) << endl;

	BinarySerchTree<string, int> bst = BinarySerchTree<string, int>();
	bst.insert("a", 10);
	bst.insert("c", 11);
	bst.insert("b", 12);
	bst.insert("d", 13);
	//if (bst.search("a"))
	//	cout << *bst.search("a") << endl;
	//bst.remove("c");
	//cout << bst.maximum() << bst.minimum() << bst.size() << endl;

	bst.levelTraverse();
	return 0;
}