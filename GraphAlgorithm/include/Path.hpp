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

template <class Graph> // Ѱ·�㷨
class Path
{
private:
	Graph& G;
	int s; // ��ʼ�����ڵ�
	bool* visited; // ��¼�ڵ��Ƿ��Ѿ���������
	int* from; // �ýڵ��������һ���ڵ�

	void dfs(int v);
public:
	Path(Graph& graph, int s);
	~Path();

	bool hasPath(int w); // ����ʼ�ڵ㵽w�Ƿ���·��
	void path(int w, vector<int>& vec); // ��¼��s��w��·������
	void showPath(int w); // ��ʾ��s��w��·��
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
			from[i] = v; // i�ڵ��Ǵ�v�ڵ��������
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