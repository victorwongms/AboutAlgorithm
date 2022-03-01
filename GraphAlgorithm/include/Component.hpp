/**
* @file     Component.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-28
*/
#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

template <class Graph>
class Component // ͼ��������ȱ�������ͼ��Ԫ�ص���ͨ����(��ͨ�ļ�����)
{
private:
	Graph& G;
	bool* visited; // ��ǽڵ��Ƿ��б�����,����
	int cCount; // ��ͨ������¼ֵ
	int* id; // ��¼��ͬ��ͨ�����ڵ��IDֵ

	void dfs(int v);
public:
	Component(Graph& graph);
	~Component();
	int count();
	bool isConnected(int v, int w);
};

template <class Graph>
bool Component<Graph>::isConnected(int v, int w)
{
	assert(v >= 0 && v < G.V());
	assert(w >= 0 && w < G.V());
	return id[v] == id[w];
}

template <class Graph>
void Component<Graph>::dfs(int v)
{
	visited[v] = true;
	id[v] = cCount; // ��һ����ͨ�����еĽڵ�id����Ϊ��ͬ
	typename Graph::adjIterator adj(G, v); // ������������
	for (int i = adj.begin(); !adj.end(); i = adj.next()) // ʹ�õݹ�������ȱ���ͼ
		if (!visited[i])
			dfs(i);
}

template <class Graph>
int Component<Graph>::count()
{
	return cCount;
}

template <class Graph>
Component<Graph>::~Component()
{
	delete[] visited;
	delete[] id;
}

template <class Graph>
Component<Graph>::Component(Graph& graph) :
	G(graph)
{
	visited = new bool[G.V()]();
	id = new int[G.V()];
	for (size_t i = 0; i < G.V(); i++) // Ĭ��idΪ-1
		id[i] = -1;
	cCount = 0;
	for (size_t i = 0; i < G.V(); i++)
	{
		if (!visited[i])
		{
			dfs(i); // ������ȱ���
			cCount++;
		}
	}
}

#endif //__COMPONENT_H__