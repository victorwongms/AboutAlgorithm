//###############################################################
//Summary:
//          QuickSort �� 
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
int partition(T arr[], const int L, const int R) // �������׸�Ԫ����Ϊ��ʶ�������������ȷ��˳��λ�ú󷵻�������
{
	T aux = arr[L]; // ���׸�Ԫ��Ϊ��ʶ
	int pos = L;
	for (int i = L + 1; i < R; i++) // ������������ʹ[L,pos)����ȫС��aux��[pos + 1, R) ȫ����(�����)aux,���aux��������ȷ��˳��λ����
		if (arr[i] < aux)
			swap(arr[i], arr[++pos]); // pos ǰ�ƣ�����arr[i]������pos + 1
	swap(arr[L], arr[pos]); // ����ʶԪ�ط�������ȷ������λ����
	return pos;
}

template <class T>
int partition2Ways(T arr[], const int L, const int R)
{
	swap(arr[L], arr[std::rand() % (R - L) + L]);  // ��������̶ȵ͵�������������㷨�˻�
	T aux = arr[L];
	int lt = L + 1, gt = R - 1; // lt��С��aux�ı߽�λ�ã�������L�غϣ�gt�Ǵ���aux�ı߽�λ��
	while (true)
	{
		while (lt < R && arr[lt] < aux) // �趨�߽��ж������ͱ߽��ƶ�����
			lt++;
		while (gt > L && arr[gt] > aux)  //�ܿ���ʶֵλ��
			gt--;
		if (lt > gt) // �˳�����
			break;
		if (arr[lt] != arr[gt])
			swap(arr[lt], arr[gt]); // �������ֵ����򲻱��ٽ������Ч��
		lt++, gt--;  // �߽�����ƶ�
	}
	swap(aux, arr[gt]); // ����ʶֵ���õ���ȷ��λ�ô�
	return gt;
}

template <class T>
int partitionOptimized(T arr[], const int L, const int R)
{
	swap(arr[L], arr[std::rand() % (R - L) + L]); // ���������λ�ô�Ԫ������Ԫ�ؽ��������򣬱���������̶ȵ͵�������������㷨�˻�
	T aux = arr[L];
	int pos = L;
	for (int i = L + 1; i < R; i++)
		if (arr[i] < aux)
			swap(arr[i], arr[++pos]);
	swap(aux, arr[pos]);
	return pos;
}

template <class T>
void __quickSort(T arr[], const int L, const int R) // ��[L,R)���п���
{
	if (L >= R - 1)
		return;
	int pos = partition(arr, L, R); // ���ؾ���һ�ο��ź�Ԫ�ص���ȷ����
	__quickSort(arr, L, pos); // �Դ�Ԫ��Ϊ�磬���������Ϊ��������������ݹ�
	__quickSort(arr, pos + 1, R);
}

template <class T>
void __quickSortOptimized(T arr[], const int L, const int R)
{
	if (R - L < 16)
	{
		__sortByInsert(arr, L, R); // ���������ұ߽�����Сʱ���ò�����������滻
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
void __quickSort2Ways(T arr[], const int L, const int R)  // ����Ϊ[L,R)
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
	int lt = L; // ������·���δﵽ[L, lt]��С��aux, [lt+2,gt-1]������aux, [gt,R)������aux
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
	swap(aux, arr[lt]);  // ��lt����Ԫ�ؽ�������Ҫ��gt-1����������ֹ���ֲ��ȶ�

	__quickSort3Ways(arr, L, lt); // ע�����
	__quickSort3Ways(arr, gt, R); // ע�����
}

template <class T>
void quickSort2Ways(T arr[], const int n) // ��С�ڱ�ʶֵ�ʹ��ڱ�ʶֵ����������з��δﵽ2·����Ч��
{
	__quickSort2Ways(arr, 0, n);
}

template <class T>
void quickSort3Ways(T arr[], const int n) // ��С�ڱ�ʾֵ�����ڱ�ʾֵ�ʹ��ڱ�ʶֵ����������з��δﵽ3·����Ч��
{
	srand(time(NULL));
	__quickSort3Ways(arr, 0, n);
}
#endif //__QUIKSORT_H__