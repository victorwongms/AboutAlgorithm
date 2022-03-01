/**
* @file     SparseGraph.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-27
*/
#ifndef __SPARSEGRAPH_H__
#define __SPARSEGRAPH_H__

#include <iostream>
#include <cassert>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class SparseGraph // �ڽӱ���ͼ������
{
public:
	SparseGraph(int N, bool directed);
	~SparseGraph();
	int V();
	int E();
	bool hasEdge(int v, int w);
	void addEdge(int v, int w);
	void show();

	class adjIterator // �������������ڽӱ�˽������
	{
	private:
		SparseGraph& G;
		int v, index;
	public:
		adjIterator(SparseGraph& graph, int v); // �ڵ�v
		int begin(); // ��ڵ�v���ڵĵ�һ���ڵ�
		int next(); // ��ڵ�v���ڵ���һ���ڵ�
		bool end(); // �Ƿ��Ѿ��������ڽڵ�
	};
private:
	int n, m;
	bool directed;
	vector<vector<int>> g;
};

SparseGraph::adjIterator::adjIterator(SparseGraph& graph, int v) :
	G(graph)
{
	this->v = v;
	this->index = 0;
}

int SparseGraph::adjIterator::begin()
{
	index = 0;
	if (G.g[v].size())
		return G.g[v][index];
	return -1;
}

int SparseGraph::adjIterator::next()
{
	index++;
	if (index < G.g[v].size())
		return G.g[v][index];
	return -1;
}

bool SparseGraph::adjIterator::end()
{
	return index >= G.g[v].size();
}

SparseGraph::SparseGraph(int N, bool directed) :
	n(N),
	directed(directed),
	m(0)
{
	for (size_t i = 0; i < N; i++)
		g.emplace_back(vector<int>());
}

int SparseGraph::V()
{
	return n;
}

int SparseGraph::E()
{
	return m;
}

bool SparseGraph::hasEdge(int v, int w) // �Ƿ���v��w�ı�
{
	assert(v >= 0 && v < n);
	assert(w >= 0 && w < n);
	for (size_t i = 0; i < m; i++)
		if (g[v][i] == w)
			return true;
	return false;
}

void SparseGraph::addEdge(int v, int w)
{
	assert(v >= 0 && v < n);
	assert(w >= 0 && w < n);

	g[v].emplace_back(w);
	if (v != w && !directed) // �������Ի���
		g[w].emplace_back(v);
	m++;
}

SparseGraph::~SparseGraph()
{

}

void SparseGraph::show()
{
	for (size_t i = 0; i < n; i++)
	{
		cout << i << ": ";
		for (size_t j = 0; j < g[i].size(); j++)
		{
			cout << g[i][j] << ", ";
		}
		cout << endl;
	}
}

#endif //__SPARSEGRAPH_H__