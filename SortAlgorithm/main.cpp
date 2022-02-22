/*
 * @Author: Victor Wong
 * @Date: 2022-02-16 18:24:37
 * @LastEditors: Victor Wong
 * @LastEditTime: 2022-02-16 22:09:22
 * @Description: file content
 */
#include "SelectionSort.hpp"
#include "sortEfficiencyTest.hpp"
#include "InsertSort.hpp"
#include "BubbleSort.hpp"
#include "ShellSort.hpp"
#include "MergeSort.hpp"
#include "QuikSort.hpp"

using namespace sortEfficiencyTest;

int main(int argc, char const* argv[])
{
	int num = 20000000;
	//int* sam1 = sortEfficiencyTest::randomNearlyOrderedArr(num, 100);
	int* sam1 = sortEfficiencyTest::randomIntArrSample(num, 0, 10);
	//int* sam2 = sortEfficiencyTest::copyIntArr(sam1, num);
	int* sam3 = sortEfficiencyTest::copyIntArr(sam1, num);
	//sortEfficiencyTest::staticsSortEfficiency("SelectionSort", selectionSort, sam1, num);
	//sortEfficiencyTest::staticsSortEfficiency("InsertSort", insertSort, sam2, num);
	//sortEfficiencyTest::staticsSortEfficiency("InsertSortOptimized", insertSortOptimized, sam1, num);

	//sortEfficiencyTest::staticsSortEfficiency("BubbleSort", bubbleSort, sam2, num);
	//sortEfficiencyTest::staticsSortEfficiency("BubbleSortOptimized", bubbleSortOptimized, sam3, num);

	//sortEfficiencyTest::staticsSortEfficiency("ShellSort", shellSort, sam3, num);

	//sortEfficiencyTest::staticsSortEfficiency("MergeSort", mergeSort, sam3, num);
	//sortEfficiencyTest::staticsSortEfficiency("mergeSortOptimized", mergeSortOptimized, sam3, num);
	//sortEfficiencyTest::staticsSortEfficiency("mergeSortB2U", mergeSortB2U, sam3, num);
	//sortEfficiencyTest::staticsSortEfficiency("quickSort", quickSort, sam3, num);
	//sortEfficiencyTest::staticsSortEfficiency("quickSortOptimized", quickSortOptimized, sam3, num);
	sortEfficiencyTest::staticsSortEfficiency("quickSort2Ways", quickSort2Ways, sam3, num);
	sortEfficiencyTest::staticsSortEfficiency("quickSort3Ways", quickSort3Ways, sam3, num);

	//sortEfficiencyTest::printArr<int>(sam3, num);
	delete[]sam1;
	//delete[]sam2;
	delete[]sam3;
	return 0;
}
