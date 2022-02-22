//###############################################################
//Summary:
//          MergeSort �� 
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
	for (int i = L; i < R; i++) // ��[L,R)�������ֵ����aux�����ռ��¼
		aux[i - L] = arr[i];

	int i = L, j = mid;
	for (int k = L; k < R; k++) // �������鲢������ݴ�aux�ռ�����������
	{
		if (i > mid - 1) // ��벿���Ѿ��������
		{
			arr[k] = aux[j - L]; j++;
		}
		else if (j > R - 1) // �Ұ벿���Ѿ��������
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
void __mergeSort(T arr[], const int L, const int R) // ��[L,R)����������������
{
	if (L >= R - 1)
		return;
	int mid = L + R >> 1;
	__mergeSort(arr, L, mid); // ������������������
	__mergeSort(arr, mid, R); // �Ұ����������������
	__merge(arr, L, mid, R); // ���ź��������������鲢����
}

template <class T>
void __mergeSortOptimized(T arr[], const int L, const int R)
{
	if (R - L < 16) // ���ڱ߽��С�������˵����������̶��ѵͣ����Կ���ʹ�ò������򷨼ӿ�����
	{
		__sortByInsert(arr, L, R);
		return;
	}
	int mid = L + R >> 1;
	__mergeSortOptimized(arr, L, mid);
	__mergeSortOptimized(arr, mid, R);
	if (arr[mid - 1] > arr[mid]) // �����Ѿ���������������鲻�ù鲢���������̶ȵ͵������Ż�
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
	// �����ұ߽��С��������в����������Ч��
	for (size_t i = 0; i < n; i += 16)
		__sortByInsert(arr, i, min<int>(i + 16, n));

	for (int size = 16; size < n; size *= 2) // �ӵײ���ʼ���Ϲ鲢���鲢�������鳤�ȳɱ�����, �Ѿ������������ĳ���16��ʼ�����鲢����
		for (int i = 0; i + size - 1 < n - 1; i += 2 * size) // i + size - 1 ȷ�������������벿��������
			// ��[i,i+size)��[i+size,i+2*size)���й鲢
			// ��arr[i + size -1] <= arr[i + size] ʱ�����Ұ��������Ѿ�����ȷ˳�򴦣�����Ҫ������
			if (arr[i + size - 1] > arr[i + size])
				__merge(arr, i, i + size, min<int>(i + 2 * size, n)); // ȷ��i + 2*size ����Խ��
}
#endif //__MERGESORT_H__