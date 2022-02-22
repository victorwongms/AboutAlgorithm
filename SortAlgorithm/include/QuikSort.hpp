//###############################################################
//Summary:
//          QuickSort 类 
//FileName:
//          QuikSort.hpp
//Date:
//          2022/2/19
//Author:
//          VictorWong
//###############################################################
#ifndef __QUIKSORT_H__
#define __QUIKSORT_H__
#include <algorithm>
#include <ctime>
#include "InsertSort.hpp"

using std::swap;
using std::srand;

template <class T>
int partition(T arr[], const int L, const int R) // 以数组首个元素作为标识，将其放置在正确的顺序位置后返回其索引
{
	T aux = arr[L]; // 以首个元素为标识
	int pos = L;
	for (int i = L + 1; i < R; i++) // 经过分区处理，使[L,pos)区域全小于aux，[pos + 1, R) 全大于(或等于)aux,最后将aux放置在正确的顺序位置上
		if (arr[i] < aux)
			swap(arr[i], arr[++pos]); // pos 前移，并把arr[i]放置在pos + 1
	swap(arr[L], arr[pos]); // 将标识元素放置在正确的排序位置上
	return pos;
}

template <class T>
int partition2Ways(T arr[], const int L, const int R)
{
	swap(arr[L], arr[std::rand() % (R - L) + L]);  // 处理乱序程度低的数组造成排序算法退化
	T aux = arr[L];
	int lt = L + 1, gt = R - 1; // lt是小于aux的边界位置，不能与L重合，gt是大于aux的边界位置
	while (true)
	{
		while (lt < R && arr[lt] < aux) // 设定边界判定条件和边界移动条件
			lt++;
		while (gt > L && arr[gt] > aux)  //避开标识值位置
			gt--;
		if (lt > gt) // 退出条件
			break;
		if (arr[lt] != arr[gt])
			swap(arr[lt], arr[gt]); // 如果两个值相等则不必再交换提高效率
		lt++, gt--;  // 边界继续移动
	}
	swap(aux, arr[gt]); // 将标识值放置到正确的位置处
	return gt;
}

template <class T>
int partitionOptimized(T arr[], const int L, const int R)
{
	swap(arr[L], arr[std::rand() % (R - L) + L]); // 将随机索引位置处元素与首元素交换再排序，避免因乱序程度低的数组样本造成算法退化
	T aux = arr[L];
	int pos = L;
	for (int i = L + 1; i < R; i++)
		if (arr[i] < aux)
			swap(arr[i], arr[++pos]);
	swap(aux, arr[pos]);
	return pos;
}

template <class T>
void __quickSort(T arr[], const int L, const int R) // 对[L,R)进行快排
{
	if (L >= R - 1)
		return;
	int pos = partition(arr, L, R); // 返回经过一次快排后元素的正确索引
	__quickSort(arr, L, pos); // 以此元素为界，将数组分治为两个子数组继续递归
	__quickSort(arr, pos + 1, R);
}

template <class T>
void __quickSortOptimized(T arr[], const int L, const int R)
{
	if (R - L < 16)
	{
		__sortByInsert(arr, L, R); // 子数列左右边界距离较小时换用插入排序进行替换
		return;
	}
	srand(time(NULL));
	int pos = partitionOptimized(arr, L, R);
	__quickSortOptimized(arr, L, pos);
	__quickSortOptimized(arr, pos + 1, R);
}

template <class T>
void quickSort(T arr[], const int n)
{
	__quickSort(arr, 0, n);
}

template <class T>
void quickSortOptimized(T arr[], const int n)
{
	__quickSortOptimized(arr, 0, n);
}

template <class T>
void __quickSort2Ways(T arr[], const int L, const int R)  // 区域为[L,R)
{
	if (R - L < 16)
	{
		__sortByInsert(arr, L, R);
		return;
	}
	srand(time(NULL));
	int pos = partition2Ways(arr, L, R);
	__quickSort2Ways(arr, L, pos);
	__quickSort2Ways(arr, pos + 1, R);
}

template <class T>
void __quickSort3Ways(T arr[], const int L, const int R)
{
	if (R - L < 16)
	{
		__sortByInsert(arr, L, R);
		return;
	}

	swap(arr[L], arr[std::rand() % (R - L) + L]);
	T aux = arr[L];
	int lt = L; // 经过三路分治达到[L, lt]均小于aux, [lt+2,gt-1]均等于aux, [gt,R)均大于aux
	int gt = R;
	int pos = L + 1;
	while (pos < gt)
	{
		if (arr[pos] < aux)
		{
			swap(arr[pos], arr[lt + 1]);
			pos++;
			lt++;
		}
		else if (arr[pos] > aux)
		{
			swap(arr[pos], arr[gt - 1]);
			gt--;
		}
		else
			pos++;
	}
	swap(aux, arr[lt]);  // 与lt所在元素交换，不要与gt-1处交换，防止出现不稳定

	__quickSort3Ways(arr, L, lt); // 注意界限
	__quickSort3Ways(arr, gt, R); // 注意界限
}

template <class T>
void quickSort2Ways(T arr[], const int n) // 从小于标识值和大于标识值两个方向进行分治达到2路快排效果
{
	__quickSort2Ways(arr, 0, n);
}

template <class T>
void quickSort3Ways(T arr[], const int n) // 从小于标示值，等于标示值和大于标识值三个方向进行分治达到3路快排效果
{
	srand(time(NULL));
	__quickSort3Ways(arr, 0, n);
}
#endif //__QUIKSORT_H__