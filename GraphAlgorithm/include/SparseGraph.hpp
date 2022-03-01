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

class SparseGraph // 邻接表储存图的特征
{
public:
	SparseGraph(int N, bool directed);
	~SparseGraph();
	int V();
	int E();
	bool hasEdge(int v, int w);
	void addEdge(int v, int w);
	void show();

	class adjIterator // 迭代器，访问邻接表私有向量
	{
	private:
		SparseGraph& G;
		int v, index;
	public:
		adjIterator(SparseGraph& graph, int v); // 节点v
		int begin(); // 与节点v相邻的第一个节点
		int next(); // 与节点v相邻的下一个节点
		bool end(); // 是否已经遍历完邻节点
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

bool SparseGraph::hasEdge(int v, int w) // 是否有v到w的边
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
	if (v != w && !directed) // 不包括自环边
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