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

// 二分查找，floor指向元素第一次出现位置，ceil指向元素最后出现的位置
// 当所找元素target不在序列中时，需要floor指向比target小的最后一个元素；ceil指向比target大的第一个元素

// 对有序数组进行查找，如果该元素重复存在多个，则返回该元素的最小索引值
// 如果查找不到该元素target则返回比该元素小的最后一个元素索引, 该元素大小存在多个，则返回最大索引值
template <class T>
int floor(T arr[], const int n, T target)  // 寻找左边界，需要使用R进行动态寻找，当R刚好越过target索引时循环终止
{
	assert(n > 0);
	if (arr[0] > target || arr[n - 1] < target) // 不存在该元素，-1
		return -1;
	int L = -1, R = n - 1; // L取值-1，当arr[0] == target时，最后不会前移导致索引错位
	while (L < R)
	{
		int mid = L + (R - L + 1 >> 1); // 由于是从R开始动态找边界，因此向上取整, 指针前移，避免死循环

		if (arr[mid] >= target)
			R = mid - 1; // 遇到相同的元素指针后移使L，R相遇，否则死循环
		else
			// arr[mid] < target
			L = mid;
	}

	assert(L == R); // 退出循环后L==R，指针后移过，需要前移判断
	if (L + 1 < n && arr[L + 1] == target) // 当前位置刚好越过target等值位置，如果初始L=0，则会错误移动一次，故L=-1
		return L + 1;
	else
		return L;
}

// 针对有序数组进行查找，如果查找到多个该元素则返回该元素的最小索引值
// 如果没有找到该元素则指向下一个比该元素大的元素，如果有多个这样的元素，指向最小元素索引
template <class T>
int ceil(T arr[], const int n, T target) // 寻找有边界，需要使用L进行动态寻找，当L刚好越过target等值位置时中断循环
{
	assert(n > 0);
	if (arr[0] > target || arr[n - 1] < target)
		return 0;
	int L = 0, R = n; // 同理R取n， 当arr[n-1]==target时，最后不会前移导致索引错位
	while (L < R)
	{
		int mid = L + (R - L >> 1); // 由于是由L寻找边界，向下取整即可，指针后移避免死循环
		if (arr[mid] <= target)
			L = mid + 1; // 遇到相同的元素指针前移，让其与R相遇退出循环，避免死循环
		else
			// arr[mid] > target
			R = mid;
	}
	assert(L == R);
	if (R - 1 >= 0 && arr[R - 1] == target)
		return R -1; // 当前位置刚好越过target等值位置，如果初始R=n-1，则会错误移动一次，故R=N
	else
		return R;
}

#endif //__BINARYSEARCH_H__