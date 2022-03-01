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
class Component // 图的深度优先遍历，求图中元素的连通分量(连通的集合数)
{
private:
	Graph& G;
	bool* visited; // 标记节点是否有遍历到,数组
	int cCount; // 连通分量记录值
	int* id; // 记录相同连通分量节点的ID值

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
	id[v] = cCount; // 将一个连通集合中的节点id设置为相同
	typename Graph::adjIterator adj(G, v); // 声明是类型名
	for (int i = adj.begin(); !adj.end(); i = adj.next()) // 使用递归深度优先遍历图
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
	for (size_t i = 0; i < G.V(); i++) // 默认id为-1
		id[i] = -1;
	cCount = 0;
	for (size_t i = 0; i < G.V(); i++)
	{
		if (!visited[i])
		{
			dfs(i); // 深度优先遍历
			cCount++;
		}
	}
}

#endif //__COMPONENT_H__