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
	int s; // ��ʼ�ڵ�
	bool* visited; // ��¼�ڵ��Ƿ񱻷��ʹ����Ƿ����������У�
	int* from; // ���ĸ��ڵ���ʼ��ʼ��������ǰ�ڵ�
	int* ord; // ������ʼ�ڵ�ľ���
	queue<int> q; // �����ȷ�����Ľڵ�

	void bfs(int s); // ��s��ʼ������ȱ���
public:
	ShortestPath(Graph& graph, int s);
	~ShortestPath();
	bool hasPath(int w);
	void path(int w, vector<int>& vec);
	void showPahth(int w);
	int length(int w);
};

template <class Graph>
void ShortestPath<Graph>::bfs(int s) // ����ͼ���·����������ȱ���
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
				from[i] = v; // �Ǵ�v������i��
				ord[i] = ord[v] + 1; // ����s��ʼ��ľ�����v��������+1
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
	// ���յ㵹��Ѱ�ҵ���㣬��from�п��Ե�֪����
	stack<int> s; // ��ʱ��������ڵ�
	int p = w;
	while (p != -1)
	{
		s.push(p);
		p = from[p]; // ����Ѱ����ʼ�ڵ�
	}

	vec.clear();
	while (!s.empty())
	{
		vec.emplace_back(s.top()); // ȡ��ջ��
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