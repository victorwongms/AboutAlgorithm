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

// �����������Ľṹ����Ϊ������ӽڵ�Ԫ��ֵ����С�ڸ��ڵ�ֵ���Ҳ��ӽڵ�Ԫ��ֵ������ڸ��ڵ�ֵ��������������һ����ҪΪ�����������
// ������������������ӽڵ�Ϊ��СԪ�أ����Ҳ��ӽڵ�Ϊ���Ԫ��
// �������������������ַ�ʽ��ǰ�����򡢺��������������ȣ������������������ȣ������о�����������󣬻�õ���������;ɾ���ڵ���Ҫ�����������ɾ��
//   �ݹ飬ǰ�����						�������					�������
//		do something;				inTraverse(node->left);		postTraverse(node->left);
//		preTraverse(node->left);		do something;				postTraverse(node->right);
//		preTraverse(node->right);		inTraverse(node->right);		do something;
// ���������Ҫ�������д���
// �����������ı��������룬ɾ�����㷨���ӶȾ�ΪO��logn��

template <class Key, class Value>
class BinarySerchTree
{
private:
	int count;

	typedef struct Node  // �����������Ľڵ�
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

		Node(Node* node) // �������캯��
		{
			key = node->key;
			value = node->value;
			left = node->left;
			right = node->right;
		}
	}node_t;
	node_t* root; // ���ڵ�ָ��

	node_t* insert(node_t* node, Key key, Value value) // ��node�ڵ����
	{
		if (!node) // ��ǰ�ڵ�գ��򴴽��µĽڵ�
		{
			count++;
			return new node_t(key, value);
		}

		if (node->key == key) // Ҫ�����λ�������ǵ�ǰ�ڵ㣬�����value����
			node->value = value;
		else if (node->key > key) // ��ֵ�ȸ��ڵ�С��������ӽڵ����
			node->left = insert(node->left, key, value);
		else
			node->right = insert(node->right, key, value);
		return node;
	}

	node_t* minimum(node_t* node)
	{
		if ((!node->left)) // û���ӽڵ�
			return node;
		return minimum(node->left);
	}

	node_t* maximum(node_t* node)
	{
		if (!node->right) // û���ӽڵ�
			return node;
		return maximum(node->right);
	}

	node_t* removeMin(node_t* node)
	{
		if (!node->left)
		{
			node_t* right = node->right; // �����Ƿ����ҽڵ���Ҫ������������������ҽڵ���ӵ����ڵ㼴��
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
		// �����ǰ�ڵ�ͬʱӵ�������ӽڵ㣬��ɾ����ǰ�ڵ�󣬵�ǰ�ڵ�ĺ����Ӧ�������ӽڵ�Ϊ���ڵ����Сֵ�ڵ㣬����ߵ���ڵ�Ϊ��ǰԪ�ص���ڵ㣬�ҽڵ�Ϊ��ǰԪ�ص��ҽڵ�
		// �������ʵҲ�������ӽڵ�Ϊ���ڵ�����ֵ�ڵ�
		if (node->key == key)
		{
			if (!node->left) // ���ӽڵ㲻����
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

			node_t* successor = new node_t(minimum(node->right)); // �ҵ������ӽڵ�Ϊ���ڵ����Сֵ�ڵ�Ϊ�����,����������
			count++; // ��������ɾ�����滻Ԫ��
			successor->right = removeMin(node->right); // ɾ�����滻Ԫ��
			successor->left = node->left; // ����ǰ�ڵ��������滻
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
	Value* search(Key key); // ���ؼ�ֵ����Ӧ��ֵ
	Key minimum(); // ������С�ڵ�ļ�ֵ
	Key maximum();
	void removeMin(); // ɾ����С�ڵ�
	void removeMax(); // ɾ�����ڵ�
	void remove(Key key); // ɾ����ֵ���ڽڵ�

	void preTraverse(); // ǰ�����
	void inTraverse(); // �������
	void postTraverse(); // �������
	void levelTraverse(); // �������
};

template <class Key, class Value>
void BinarySerchTree<Key, Value>::levelTraverse(node_t* node)
{
	if (!node)
		return;
	queue<node_t*> auxQ; // ��ʱ��������
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
		root = removeMin(root); // ɾ����rootΪ������СԪ�ؽڵ�
}

template <class Key, class Value>
Value* BinarySerchTree<Key, Value>::search(node_t* node, Key key)
{
	if (!node) // û�иýڵ�
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
	else if (node->key > key) // ���ڵ��ֵ����Ҫ�����ӽڵ����
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