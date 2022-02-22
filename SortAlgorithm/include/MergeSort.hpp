//###############################################################
//Summary:
//          MergeSort 类 
//FileName:
//          MergeSort.hpp
//Date:
//          2022/2/18
//Author:
//          VictorWong
//###############################################################
#ifndef __MERGESORT_H__
#define __MERGESORT_H__
#include <algorithm>
#include "InsertSort.hpp"

using std::min;

template <class T>
void __merge(T arr[], const int L, const int mid, const int R)
{
	T* aux = new T[R - L];
	for (int i = L; i < R; i++) // 将[L,R)区间的数值放入aux辅助空间记录
		aux[i - L] = arr[i];

	int i = L, j = mid;
	for (int k = L; k < R; k++) // 将经过归并后的数据从aux空间填入数组中
	{
		if (i > mid - 1) // 左半部分已经填入完成
		{
			arr[k] = aux[j - L]; j++;
		}
		else if (j > R - 1) // 右半部分已经填入完成
		{
			arr[k] = aux[i - L]; i++;
		}
		else if (aux[i - L] < aux[j - L])
		{
			arr[k] = aux[i - L]; i++;
		}
		else
		{
			arr[k] = aux[j - L]; j++;
		}
	}
	delete[] aux;
}

template <class T>
void __mergeSort(T arr[], const int L, const int R) // 对[L,R)区间的数组进行排序
{
	if (L >= R - 1)
		return;
	int mid = L + R >> 1;
	__mergeSort(arr, L, mid); // 左半区间数组进行排序
	__mergeSort(arr, mid, R); // 右半区间数组进行排序
	__merge(arr, L, mid, R); // 将排好序的两组子数组归并起来
}

template <class T>
void __mergeSortOptimized(T arr[], const int L, const int R)
{
	if (R - L < 16) // 对于边界较小的情况，说明数组无序程度已低，可以考虑使用插入排序法加快排序
	{
		__sortByInsert(arr, L, R);
		return;
	}
	int mid = L + R >> 1;
	__mergeSortOptimized(arr, L, mid);
	__mergeSortOptimized(arr, mid, R);
	if (arr[mid - 1] > arr[mid]) // 对于已经有序的两个子数组不用归并，针对无序程度低的数组优化
		__merge(arr, L, mid, R);
}

template <class T>
void mergeSort(T arr[], const int n)
{
	__mergeSort(arr, 0, n);
}

template <class T>
void mergeSortOptimized(T arr[], const int n)
{
	__mergeSortOptimized(arr, 0, n);
}

template <class T>
void mergeSortB2U(T arr[], const int n)
{
	// 对左右边界较小的数组进行插入排序提高效率
	for (size_t i = 0; i < n; i += 16)
		__sortByInsert(arr, i, min<int>(i + 16, n));

	for (int size = 16; size < n; size *= 2) // 从底部开始向上归并，归并的子数组长度成倍增长, 已经过插入排序后的长度16开始继续归并排序
		for (int i = 0; i + size - 1 < n - 1; i += 2 * size) // i + size - 1 确保存在左右两半部分子数组
			// 将[i,i+size)和[i+size,i+2*size)进行归并
			// 对arr[i + size -1] <= arr[i + size] 时表明右半子数组已经在正确顺序处，不需要再排序
			if (arr[i + size - 1] > arr[i + size])
				__merge(arr, i, i + size, min<int>(i + 2 * size, n)); // 确保i + 2*size 不会越界
}
#endif //__MERGESORT_H__