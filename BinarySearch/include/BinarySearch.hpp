/**
* @file     BinarySearch.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-24
*/
#ifndef __BINARYSEARCH_H__
#define __BINARYSEARCH_H__

#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

// ���ֲ��ң�floorָ��Ԫ�ص�һ�γ���λ�ã�ceilָ��Ԫ�������ֵ�λ��
// ������Ԫ��target����������ʱ����Ҫfloorָ���targetС�����һ��Ԫ�أ�ceilָ���target��ĵ�һ��Ԫ��

// ������������в��ң������Ԫ���ظ����ڶ�����򷵻ظ�Ԫ�ص���С����ֵ
// ������Ҳ�����Ԫ��target�򷵻رȸ�Ԫ��С�����һ��Ԫ������, ��Ԫ�ش�С���ڶ�����򷵻��������ֵ
template <class T>
int floor(T arr[], const int n, T target)  // Ѱ����߽磬��Ҫʹ��R���ж�̬Ѱ�ң���R�պ�Խ��target����ʱѭ����ֹ
{
	assert(n > 0);
	if (arr[0] > target || arr[n - 1] < target) // �����ڸ�Ԫ�أ�-1
		return -1;
	int L = -1, R = n - 1; // Lȡֵ-1����arr[0] == targetʱ����󲻻�ǰ�Ƶ���������λ
	while (L < R)
	{
		int mid = L + (R - L + 1 >> 1); // �����Ǵ�R��ʼ��̬�ұ߽磬�������ȡ��, ָ��ǰ�ƣ�������ѭ��

		if (arr[mid] >= target)
			R = mid - 1; // ������ͬ��Ԫ��ָ�����ʹL��R������������ѭ��
		else
			// arr[mid] < target
			L = mid;
	}

	assert(L == R); // �˳�ѭ����L==R��ָ����ƹ�����Ҫǰ���ж�
	if (L + 1 < n && arr[L + 1] == target) // ��ǰλ�øպ�Խ��target��ֵλ�ã������ʼL=0���������ƶ�һ�Σ���L=-1
		return L + 1;
	else
		return L;
}

// �������������в��ң�������ҵ������Ԫ���򷵻ظ�Ԫ�ص���С����ֵ
// ���û���ҵ���Ԫ����ָ����һ���ȸ�Ԫ�ش��Ԫ�أ�����ж��������Ԫ�أ�ָ����СԪ������
template <class T>
int ceil(T arr[], const int n, T target) // Ѱ���б߽磬��Ҫʹ��L���ж�̬Ѱ�ң���L�պ�Խ��target��ֵλ��ʱ�ж�ѭ��
{
	assert(n > 0);
	if (arr[0] > target || arr[n - 1] < target)
		return 0;
	int L = 0, R = n; // ͬ��Rȡn�� ��arr[n-1]==targetʱ����󲻻�ǰ�Ƶ���������λ
	while (L < R)
	{
		int mid = L + (R - L >> 1); // ��������LѰ�ұ߽磬����ȡ�����ɣ�ָ����Ʊ�����ѭ��
		if (arr[mid] <= target)
			L = mid + 1; // ������ͬ��Ԫ��ָ��ǰ�ƣ�������R�����˳�ѭ����������ѭ��
		else
			// arr[mid] > target
			R = mid;
	}
	assert(L == R);
	if (R - 1 >= 0 && arr[R - 1] == target)
		return R -1; // ��ǰλ�øպ�Խ��target��ֵλ�ã������ʼR=n-1���������ƶ�һ�Σ���R=N
	else
		return R;
}

#endif //__BINARYSEARCH_H__