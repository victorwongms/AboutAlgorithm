/**
* @file     ShortestPath.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-3-1
*/
#ifndef __SHORTESTPATH_H__
#define __SHORTESTPATH_H__

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::queue;
using std::vector;

template <class Graph>
class ShortestPath
{
private:
	Graph& G;
	int s; // 开始节点
	bool* visited; // 记录节点是否被访问过（是否加入遍历队列）
	int* from; // 从哪个节点起始开始遍历到当前节点
	int* ord; // 距离起始节点的距离
	queue<int> q; // 存放正确遍历的节点

	void bfs(int s); // 从s开始广度优先遍历
public:
	ShortestPath(Graph& graph, int s);
	~ShortestPath();
	bool hasPath(int w);
	void path(int w, vector<int>& vec);
	void showPahth(int w);
	int length(int w);
};

template <class Graph>
void ShortestPath<Graph>::bfs(int s) // 无向图最短路径，广度优先遍历
{
	q.push(s);
	visited[s] = true;
	ord[s] = 0;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next())
		{
			if (!visited[i])
			{
				q.push(i);
				visited[i] = true;
				from[i] = v; // 是从v遍历到i的
				ord[i] = ord[v] + 1; // 距离s起始点的距离是v到起点距离+1
			}
		}
	}
}

template <class Graph>
int ShortestPath<Graph>::length(int w)
{
	assert(w >= 0 && w<G>V());
	return ord[w];
}

template <class Graph>
void ShortestPath<Graph>::showPahth(int w)
{
	vector<int> vec;
	path(w, vec);
	cout << endl;
	cout << s << "->" << w << ": " << endl;
	for (size_t i = 0; i < vec.size(); i++)
		cout << vec[i] << ", ";
	cout << endl;
}

template <class Graph>
void ShortestPath<Graph>::path(int w, vector<int>& vec)
{
	// 从终点倒向寻找到起点，从from中可以得知来向
	stack<int> s; // 临时储存来向节点
	int p = w;
	while (p != -1)
	{
		s.push(p);
		p = from[p]; // 倒向寻找起始节点
	}

	vec.clear();
	while (!s.empty())
	{
		vec.emplace_back(s.top()); // 取出栈顶
		s.pop();
	}
}

template <class Graph>
bool ShortestPath<Graph>::hasPath(int w)
{
	assert(w >= 0 && w < G.V());
	return visited[w];
}

template <class Graph>
ShortestPath<Graph>::~ShortestPath()
{
	delete[] visited;
	delete[] from;
	delete[] ord;
}

template <class Graph>
ShortestPath<Graph>::ShortestPath(Graph& graph, int s) :
	G(graph)
{
	assert(s >= 0 && s < G.V());
	this->s = s;
	visited = new bool[G.V()]();
	from = new int[G.V()];
	ord = new int[G.V()];
	for (size_t i = 0; i < G.V(); i++)
	{
		from[i] = -1;
		ord[i] = -1;
	}

	bfs(s);
}

#endif //__SHORTESTPATH_H__