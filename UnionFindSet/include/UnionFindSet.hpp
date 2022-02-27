/**
* @file     UnionFindSet.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-27
*/
#ifndef __UNIONFINDSET_H__
#define __UNIONFINDSET_H__

#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

class UnionFindSet
{
private:
	int count;
	int* parent; // 指向父节点，意指与其联通的父节点元素, 储存的是元素在集合中的索引
	int* rank; // rank[i]，是以i所对应元素为根的树的层数，用于记录进行路径压缩优化
public:
	UnionFindSet(int n);
	~UnionFindSet();
	int find(int p); // 查找元素p所对应的根节点元素的索引
	bool isConnected(int p, int q); // 查找两个元素是否连通，是否存在交集
	void unionElements(int p, int q); // 将p, q两个元素相交，组成并集
	void printParent();
};

UnionFindSet::~UnionFindSet()
{
	delete[] parent;
	delete[] rank;
}

int UnionFindSet::find(int p)
{
	assert(p >= 0 && p < count);
	while (p != parent[p])
	{
		//	p = parent[p]; // 不进行路径压缩，仅寻找根节点
		parent[p] = parent[parent[p]]; // 路径压缩，向上跳一个节点并进行路径压缩
		p = parent[p];
	}

	// 递归寻找
	//if (p != parent[p])
	//	parent[p] = find(parent[p]); // 路径压缩递归将每个节点均指向根节点
	// return parent[p];
	return p;
}

bool UnionFindSet::isConnected(int p, int q)
{
	return find(p) == find(q);
}

void UnionFindSet::unionElements(int p, int q)
{
	int pRoot = find(p); // 寻找两个元素的根节点位置
	int qRoot = find(q);

	if (pRoot == qRoot)
		return;
	if (rank[pRoot] > rank[qRoot]) // 根据两个元素分别所在的树的层数来决定如何合并两个元素，将层数较少的往层数较多的元素上合并
		parent[qRoot] = pRoot;
	else if (rank[pRoot] < rank[qRoot])
		parent[pRoot] = qRoot;
	else
	{
		parent[pRoot] = qRoot;
		rank[qRoot]++;
	}
}

void UnionFindSet::printParent()
{
	for (size_t i = 0; i < count; i++)
		cout << parent[i] << endl;
}

UnionFindSet::UnionFindSet(int n) :
	count(n)
{
	parent = new int[count];
	rank = new int[count];
	for (size_t i = 0; i < count; i++)
	{
		parent[i] = i; // 默认指向自己
		rank[i] = 1; // 默认树只有一层
	}
}

#endif //__UNIONFINDSET_H__