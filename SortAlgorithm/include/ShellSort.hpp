//###############################################################
//Summary:
//          ShellSort 类 
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
	int step{ 0 }; // 步长值
	int ins{ 0 }; // 记录子数组中每次排序轮询的元素数值, 用于字数组排序中插入排序的记录
	for (step = n - 1; step > 0; step /= 2) // 初始步长取最大步长值，每轮询步长减半，至步长值为1时完成排序
	{
		for (int i = step; i < n; i += step) // 子数组插入排序
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