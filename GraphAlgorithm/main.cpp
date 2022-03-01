#include "DenseGraph.hpp"
#include "SparseGraph.hpp"
#include "ReadGraph.hpp"
#include "Component.hpp"
#include "Path.hpp"
#include "ShortestPath.hpp"

#include <ctime>

using std::srand;
using std::rand;

int main(int argc, char** argv)
{
	//srand(time(nullptr));
	//int N = 10;
	//int M = 100;
	//SparseGraph sg(N, false);
	//DenseGraph dg(N, false);

	//for (size_t i = 0; i < M; i++)
	//{
	//	int v = rand() % N;
	//	int w = rand() % N;
	//	//sg.addEdge(v, w);
	//	dg.addEdge(v, w);
	//}

	//for (size_t i = 0; i < N; i++)
	//{
	//	cout << i << ": ";
	//	//SparseGraph::adjIterator adj(sg, i);
	//	DenseGraph::adjIterator adj(dg, i);
	//	for (int w = adj.begin(); !adj.end(); w = adj.next())
	//		cout << w << ", ";
	//	cout << endl;
	//}

	//ReadGraph<DenseGraph> fg(dg, "test.txt");
	//ReadGraph<SparseGraph> fg(sg, "test.txt");
	//sg.show();
	//Path<SparseGraph> findPath(sg, 0);
	//findPath.showPath(6);
	//ShortestPath<SparseGraph> sp(sg, 0);
	////sp.showPahth(6);
	return 0;
}