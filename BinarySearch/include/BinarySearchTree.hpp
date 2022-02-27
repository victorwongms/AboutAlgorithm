/**
* @file     BinarySearchTree.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-25
*/
#ifndef __BINARYSEARCHTREE_H__
#define __BINARYSEARCHTREE_H__

#include <iostream>
#include <string>
#include <cassert>
#include <queue>

using std::cout;
using std::endl;
using std::string;
using std::queue;

// 二叉搜索树的结构特征为，左侧子节点元素值必须小于父节点值，右侧子节点元素值必须大于父节点值。二叉搜索树不一定需要为最大完整树。
// 二叉搜索树的最左侧子节点为最小元素，最右侧子节点为最大元素
// 二叉搜索树遍历有四种方式，前序、中序、后序遍历（深度优先），层序遍历（广度优先）。其中经过中序遍历后，会得到有序序列;删除节点需要后序遍历到再删除
//   递归，前序遍历						中序遍历					后序遍历
//		do something;				inTraverse(node->left);		postTraverse(node->left);
//		preTraverse(node->left);		do something;				postTraverse(node->right);
//		preTraverse(node->right);		inTraverse(node->right);		do something;
// 层序遍历需要借助队列处理
// 二叉搜索树的遍历，插入，删除的算法复杂度均为O（logn）

template <class Key, class Value>
class BinarySerchTree
{
private:
	int count;

	typedef struct Node  // 二叉搜索树的节点
	{
		Key key;
		Value value;
		Node* left;
		Node* right;

		Node(Key key, Value value)
		{
			this->key = key;
			this->value = value;
			this->left = nullptr;
			this->right = nullptr;
		}

		Node(Node* node) // 拷贝构造函数
		{
			key = node->key;
			value = node->value;
			left = node->left;
			right = node->right;
		}
	}node_t;
	node_t* root; // 根节点指针

	node_t* insert(node_t* node, Key key, Value value) // 往node节点插入
	{
		if (!node) // 当前节点空，则创建新的节点
		{
			count++;
			return new node_t(key, value);
		}

		if (node->key == key) // 要插入的位置正好是当前节点，则更新value即可
			node->value = value;
		else if (node->key > key) // 键值比父节点小，向左侧子节点插入
			node->left = insert(node->left, key, value);
		else
			node->right = insert(node->right, key, value);
		return node;
	}

	node_t* minimum(node_t* node)
	{
		if ((!node->left)) // 没有子节点
			return node;
		return minimum(node->left);
	}

	node_t* maximum(node_t* node)
	{
		if (!node->right) // 没有子节点
			return node;
		return maximum(node->right);
	}

	node_t* removeMin(node_t* node)
	{
		if (!node->left)
		{
			node_t* right = node->right; // 无论是否有右节点需要保存下来，如果有则将右节点添加到父节点即可
			delete node;
			count--;
			return right;
		}
		node->left = removeMin(node->left);
		return node;
	}

	node_t* removeMax(node_t* node)
	{
		if (!node->right)
		{
			node_t* left = node->left;
			delete node;
			count--;
			return left;
		}
		node->right = removeMax(node->right);
	}

	node_t* remove(node_t* node, Key key)
	{
		if (!node)
			return nullptr;
		// 如果当前节点同时拥有左右子节点，则删除当前节点后，当前节点的后继者应是以右子节点为根节点的最小值节点，后继者的左节点为当前元素的左节点，右节点为当前元素的右节点
		// 后继者其实也可以左子节点为根节点的最大值节点
		if (node->key == key)
		{
			if (!node->left) // 左子节点不存在
			{
				node_t* right = node->right;
				delete node;
				count--;
				return right;
			}
			if (!node->right)
			{
				node_t* left = node->left;
				delete node;
				count--;
				return left;
			}

			node_t* successor = new node_t(minimum(node->right)); // 找到以右子节点为根节点的最小值节点为后继者,并复制下来
			count++; // 抵消后面删除的替换元素
			successor->right = removeMin(node->right); // 删除该替换元素
			successor->left = node->left; // 将当前节点与后继者替换
			delete node;
			count--;
			return successor;
		}
		else if (node->key > key)
			node->left = remove(node->left, key);
		else
			node->right = remove(node->right, key);
		return node;
	}

	bool contain(node_t* node, Key key, Value value);
	Value* search(node_t* node, Key key);
	void destroy(node_t* node);
	void preTraverse(node_t* node);
	void inTraverse(node_t* node);
	void postTraverse(node_t* node);
	void levelTraverse(node_t* node);
public:
	BinarySerchTree();
	~BinarySerchTree();
	bool empty();
	int size();
	void insert(Key key, Value value);
	bool contain(Key key, Value value);
	Value* search(Key key); // 返回键值所对应的值
	Key minimum(); // 返回最小节点的键值
	Key maximum();
	void removeMin(); // 删除最小节点
	void removeMax(); // 删除最大节点
	void remove(Key key); // 删除键值所在节点

	void preTraverse(); // 前序遍历
	void inTraverse(); // 中序遍历
	void postTraverse(); // 后序遍历
	void levelTraverse(); // 层序遍历
};

template <class Key, class Value>
void BinarySerchTree<Key, Value>::levelTraverse(node_t* node)
{
	if (!node)
		return;
	queue<node_t*> auxQ; // 临时辅助队列
	auxQ.push(root);
	while (!auxQ.empty())
	{
		node_t* get = auxQ.front();
		auxQ.pop();

		// TODO: do something
		cout << get->key << endl;

		if (get->left)
			auxQ.push(get->left);
		if (get->right)
			auxQ.push(get->right);
	}
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::postTraverse(node_t* node)
{
	if (node)
	{
		postTraverse(node->left);
		postTraverse(node->right);
		// TODO: do something
	}
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::inTraverse(node_t* node)
{
	if (node)
	{
		inTraverse(node->left);
		// TODO: do something
		inTraverse(node->right);
	}
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::preTraverse(node_t* node)
{
	if (node)
	{
		// TODO: do something
		preTraverse(node->left);
		preTraverse(node->right);
	}
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::levelTraverse()
{
	if (root)
		levelTraverse(root);
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::postTraverse()
{
	if (root)
		postTraverse(root);
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::inTraverse()
{
	if (root)
		inTraverse(root);
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::preTraverse()
{
	if (root)
		preTraverse(root);
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::remove(Key key)
{
	if (root)
		root = remove(root, key);
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::removeMax()
{
	if (root)
		root = removeMax(root);
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::removeMin()
{
	if (root)
		root = removeMin(root); // 删除以root为根的最小元素节点
}

template <class Key, class Value>
Value* BinarySerchTree<Key, Value>::search(node_t* node, Key key)
{
	if (!node) // 没有该节点
		return nullptr;
	if (node->key == key)
		return &node->value;
	else if (node->key > key)
		search(node->left, key);
	else
		search(node->right, key);
}

template <class Key, class Value>
Value* BinarySerchTree<Key, Value>::search(Key key)
{
	return search(root, key);
}

template <class Key, class Value>
Key BinarySerchTree<Key, Value>::maximum()
{
	assert(root);
	node_t* maxNode = maximum(root);
	return maxNode->key;
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::destroy(node_t* node)
{
	destroy(node->left);
	destroy(node->right);

	delete node;
	count--;
}

template <class Key, class Value>
Key BinarySerchTree<Key, Value>::minimum()
{
	assert(root);
	node_t* minNode = minimum(root);
	return minNode->key;
}

template <class Key, class Value>
bool BinarySerchTree<Key, Value>::contain(node_t* node, Key key, Value value)
{
	if (!node)
		return false;
	if (node->key == key)
		return true;
	else if (node->key > key) // 父节点键值大，需要向左子节点查找
		return contain(node->left, key, value);
	else
		return contain(node->right, key, value);
}

template <class Key, class Value>
bool BinarySerchTree<Key, Value>::contain(Key key, Value value)
{
	return contain(root, key, value);
}

template <class Key, class Value>
void BinarySerchTree<Key, Value>::insert(Key key, Value value)
{
	root = insert(root, key, value);
}

template <class Key, class Value>
bool BinarySerchTree<Key, Value>::empty()
{
	return !root;
}

template<class Key, class Value>
int BinarySerchTree<Key, Value>::size()
{
	return count;
}

template <class Key, class Value>
BinarySerchTree<Key, Value>::~BinarySerchTree()
{

}

template <class Key, class Value>
BinarySerchTree<Key, Value>::BinarySerchTree() :
	count(0),
	root(nullptr)
{

};

#endif //__BINARYSEARCHTREE_H__