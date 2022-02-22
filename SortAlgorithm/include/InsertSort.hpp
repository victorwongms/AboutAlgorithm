//###############################################################
//Summary:
//          InsertSort �� 
//FileName:
//          InsertSort.hpp
//Date:
//          2022/2/17
//Author:
//          VictorWong
//###############################################################
#ifndef __INSERTSORT_H__
#define __INSERTSORT_H__

template <class T>
void insertSort(T arr[], const int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
			swap(arr[j], arr[j - 1]);
	}
}

template <class T>
void insertSortOptimized(T arr[], const int n)
{
	for (int i = 1; i < n; i++)
	{
		T aux = arr[i];
		int j; // ��¼��ǰԪ������Ӧ����λ��
		for (j = i; j > 0 && arr[j - 1] > aux; j--)
			arr[j] = arr[j - 1];
		arr[j] = aux;
	}
}

template <class T>
void __sortByInsert(T arr[], const int L, const int R) //��[L,R)�����������в�������
{
	T aux;
	for (int i = L + 1; i < R; i++)
	{
		aux = arr[i];
		int j;
		for (j = i; j > L && arr[j - 1] > aux; j--)
				arr[j] = arr[j - 1];
		arr[j] = aux;
	}
}


#endif //__INSERTSORT_H__