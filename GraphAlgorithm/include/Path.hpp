/**
* @file     Path.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-28
*/
#ifndef __PATH_H__
#define __PATH_H__

#include<stack>
#include<vector>

using std::stack;
using std::vector;

template <class Graph> // 寻路算法
class Path
{
private:
	Graph& G;
	int s; // 起始遍历节点
	bool* visited; // 记录节点是否已经被遍历过
	int* from; // 该节点遍历自哪一个节点

	void dfs(int v);
public:
	Path(Graph& graph, int s);
	~Path();

	bool hasPath(int w); // 从起始节点到w是否有路径
	void path(int w, vector<int>& vec); // 记录从s到w的路径特征
	void showPath(int w); // 显示从s到w的路径
};

template <class Graph>
void Path<Graph>::showPath(int w)
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
void Path<Graph>::path(int w, vector<int>& vec)
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
bool Path<Graph>::hasPath(int w)
{
	assert(w >= 0 && w < G.V());
	return visited[w];
}

template <class Graph>
void Path<Graph>::dfs(int v)
{
	visited[v] = true;

	typename Graph::adjIterator adj(G, v);
	for (int i = adj.begin(); !adj.end(); i = adj.next())
		if (!visited[i])
		{
			from[i] = v; // i节点是从v节点遍历到的
			dfs(i);
		}
}

template <class Graph>
Path<Graph>::Path(Graph& graph, int s):
	G(graph)
{
	assert(s >= 0 && s < G.V());
	visited = new bool[G.V()]();
	from = new int[G.V()];
	this->s = s;
	for (size_t i = 0; i < G.V(); i++)
		from[i] = -1;


	dfs(s);
}

template <class Graph>
Path<Graph>::~Path()
{
	delete[] visited;
	delete[] from;
}

#endif //__PATH_H__