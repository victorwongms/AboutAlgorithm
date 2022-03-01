/**
* @file     DenseGraph.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-27
*/
#ifndef __DENSEGRAPH_H__
#define __DENSEGRAPH_H__

#include <iostream>
#include <vector>
#include <cassert>

using std::vector;
using std::cout;
using std::endl;

class DenseGraph  // ����ͼ��ʹ���ڽӾ����¼����
{
public:
	DenseGraph(int n, bool directed);
	~DenseGraph();
	void addEdge(int v, int w); // ��(v, w)λ�ô���ӱ�
	int V(); // ͼ�Ľڵ���
	int E(); // ͼ�ı���
	bool hasEdge(int v, int w);
	void show();

	class adjIterator
	{
	private:
		int v, index;
		DenseGraph& D;
	public:
		adjIterator(DenseGraph& graph, int v);
		int begin();
		int next();
		bool end();
	};
private:
	int n; // ͼ�Ľڵ���
	int m; // ͼ�ı���
	bool directed; // ͼ�Ƿ�����
	vector<vector<bool>> g; // �ڽӾ���
};

DenseGraph::adjIterator::adjIterator(DenseGraph& graph, int v) :
	D(graph),
	index(0)
{
	this->v = v;
}

int DenseGraph::adjIterator::begin()
{
	index = 0;
	for (; index < D.V(); index++)
		if (D.g[v][index])
			return index;
	return -1;
}

int DenseGraph::adjIterator::next()
{
	index++;
	for (; index < D.V(); index++)
		if (D.g[v][index])
			return index;
	return -1;
}

bool DenseGraph::adjIterator::end()
{
	return index >= D.V();
}

DenseGraph::DenseGraph(int N, bool directed) :
	n(N),
	m(0),
	directed(directed)
{
	/*for (size_t i = 0; i < N; i++)
		g.emplace_back(vector<bool>(N, false));*/
	g = vector<vector<bool>>(n, vector<bool>(n, false));
}

int DenseGraph::V()
{
	return n;
}

int DenseGraph::E()
{
	return m;
}

void DenseGraph::addEdge(int v, int w)
{
	assert(v >= 0 && v < n);
	assert(w >= 0 && w < n);
	if (hasEdge(v, w))
		return;
	g[v][w] = true;
	if (!directed)
		g[w][v] = true;
	m++;
}

bool DenseGraph::hasEdge(int v, int w)
{
	assert(v >= 0 && v < n);
	assert(w >= 0 && w < n);
	return g[v][w];
}

DenseGraph::~DenseGraph()
{

}

void DenseGraph::show()
{
	for (size_t i = 0; i < n; i++)
	{
		cout << i << ": ";
		for (size_t j = 0; j < n; j++)
		{
			cout << g[i][j] << ", ";
		}
		cout << endl;
	}
}

#endif //__DENSEGRAPH_H__