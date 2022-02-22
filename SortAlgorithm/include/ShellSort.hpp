//###############################################################
//Summary:
//          ShellSort �� 
//FileName:
//          ShellSort.hpp
//Date:
//          2022/2/17
//Author:
//          VictorWong
//###############################################################
#ifndef __SHELLSORT_H__
#define __SHELLSORT_H__

template <class T>
void shellSort(T arr[], const int n)
{
	int step{ 0 }; // ����ֵ
	int ins{ 0 }; // ��¼��������ÿ��������ѯ��Ԫ����ֵ, ���������������в�������ļ�¼
	for (step = n - 1; step > 0; step /= 2) // ��ʼ����ȡ��󲽳�ֵ��ÿ��ѯ�������룬������ֵΪ1ʱ�������
	{
		for (int i = step; i < n; i += step) // �������������
		{
			ins = arr[i];
			int j;
			for (j = i; j > 0 && arr[j - step] > ins; j -= step)
				if (arr[j - step] > arr[j])
					arr[j] = arr[j - step];
			arr[j] = ins;
		}
	}
}

#endif //__SHELLSORT_H__