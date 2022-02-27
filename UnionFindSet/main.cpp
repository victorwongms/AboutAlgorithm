#include "UnionFindSet.hpp"

#include <ctime>

using std::srand;
using std::rand;

int main(int argc, char** argv)
{
	const int num = 10;
	srand(time(nullptr));
	UnionFindSet ufs(num);
	int* sam = new int[num];
	for (size_t i = 0; i < num; i++)
		sam[i] = i;
	for (size_t i = 0; i < num; i++)
	{
		int m = rand() % num;
		int n = rand() % num;
		ufs.unionElements(m, n);
	}
	ufs.printParent();
	delete[] sam;
	return 0;
}