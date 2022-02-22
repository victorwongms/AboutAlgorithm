//###############################################################
//Summary:
//          BubbleSort �� 
//FileName:
//          BubbleSort.hpp
//Date:
//          2022/2/17
//Author:
//          VictorWong
//###############################################################
#ifndef __BUBBLESORT_H__
#define __BUBBLESORT_H__

template<class T>
void bubbleSort(T arr[], const int n)
{
	if (arr == nullptr || n < 2)
		return;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
		}
	}
}

template <class T>
void bubbleSortOptimized(T arr[], const int n)
{
	if (arr == nullptr || n < 2)
		return;
	int aux{ n }; // ��¼����ɨ�赽���յ�λ��
	int newn{ n }; // ��¼ʣ����Ҫ������յ�λ��
	do 
	{
		aux = 0;
		for (int i = 1; i < newn; i++)
			if (arr[i - 1] > arr[i])
			{
				swap(arr[i - 1], arr[i]);
				aux = i;
			}
		newn = aux;
	} while (aux > 0);
}

#endif //__BUBBLESORT_H__