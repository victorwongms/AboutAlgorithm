/**
* @file     ReadGraph.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-28
*/
#ifndef __READGRAPH_H__
#define __READGRAPH_H__

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;

template <class Graph>
class ReadGraph
{
private:

public:
	ReadGraph(Graph& graph, const string& filename);
};

template <class Graph>
ReadGraph<Graph>::ReadGraph(Graph& graph, const string& filename)
{
	ifstream ifs(filename);
	string line;
	int V, E;
	assert(ifs.is_open());
	assert(std::getline(ifs, line));
	stringstream ss(line);
	ss >> V >> E; // 记录图的文件第一行表示节点和边
	for (size_t i = 0; i < E; i++)
	{
		if (!std::getline(ifs, line))
			break;
		stringstream ss(line);
		int a, b;
		ss >> a >> b;
		assert(a >= 0 && a < V);
		assert(b >= 0 && b < V);
		graph.addEdge(a, b);
	}

}

#endif //__READGRAPH_H__