#include<iostream>

#include "MaxBinaryHeap.hpp"
#include "MaxIndexBinaryHeap.hpp"

int main(char* argc, char** argv)
{
	//MaxBinaryHeap<int> mp(100);
	//std::srand(time(NULL));
	//for (size_t i = 0; i < 30; i++)
		//mp.insetItem(std::rand() % 100);
		//mp.insetItem(i);
	//mp.insetItem(99);
	//mp.printHeap();
	//cout << mp.extractMax() << endl;

	int sam1[30], num = 30;
	for (size_t i = 0; i < 30; i++)
		sam1[i] = i;
	//MaxBinaryHeap<int> mp(sam1, num);
	//mp.insetItem(99);
	//mp.printHeap();

	MaxIndexBinaryHeap<int> mp(sam1, num);
	//MaxIndexBinaryHeap<int> mp(30);
	//for (size_t i = 0; i < 30; i++)
	//	mp.insetItem(i, i);
	mp.change(0, 99);
	mp.printHeap();

	return 0;
}