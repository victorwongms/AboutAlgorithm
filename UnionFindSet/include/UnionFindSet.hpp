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
	int* parent; // ָ�򸸽ڵ㣬��ָ������ͨ�ĸ��ڵ�Ԫ��, �������Ԫ���ڼ����е�����
	int* rank; // rank[i]������i����ӦԪ��Ϊ�������Ĳ��������ڼ�¼����·��ѹ���Ż�
public:
	UnionFindSet(int n);
	~UnionFindSet();
	int find(int p); // ����Ԫ��p����Ӧ�ĸ��ڵ�Ԫ�ص�����
	bool isConnected(int p, int q); // ��������Ԫ���Ƿ���ͨ���Ƿ���ڽ���
	void unionElements(int p, int q); // ��p, q����Ԫ���ཻ����ɲ���
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
		//	p = parent[p]; // ������·��ѹ������Ѱ�Ҹ��ڵ�
		parent[p] = parent[parent[p]]; // ·��ѹ����������һ���ڵ㲢����·��ѹ��
		p = parent[p];
	}

	// �ݹ�Ѱ��
	//if (p != parent[p])
	//	parent[p] = find(parent[p]); // ·��ѹ���ݹ齫ÿ���ڵ��ָ����ڵ�
	// return parent[p];
	return p;
}

bool UnionFindSet::isConnected(int p, int q)
{
	return find(p) == find(q);
}

void UnionFindSet::unionElements(int p, int q)
{
	int pRoot = find(p); // Ѱ������Ԫ�صĸ��ڵ�λ��
	int qRoot = find(q);

	if (pRoot == qRoot)
		return;
	if (rank[pRoot] > rank[qRoot]) // ��������Ԫ�طֱ����ڵ����Ĳ�����������κϲ�����Ԫ�أ����������ٵ��������϶��Ԫ���Ϻϲ�
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
		parent[i] = i; // Ĭ��ָ���Լ�
		rank[i] = 1; // Ĭ����ֻ��һ��
	}
}

#endif //__UNIONFINDSET_H__