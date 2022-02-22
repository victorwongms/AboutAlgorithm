/*
 * @Author: Victor Wong
 * @Date: 2022-02-15 16:31:27
 * @LastEditors: Victor Wong
 * @LastEditTime: 2022-02-16 21:47:48
 * @Description: file content
 */
#include <iostream>

using std::swap;

template <class T>
void selectionSort(T arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}
		swap(arr[i], arr[minIndex]);
	}
}

// int main(int argc, char const *argv[])
// {
//     // int test[] = {3, 56, -10, -10, 0, 222, 1234, -896, 0};
//     char test[] = {'a', 'F', 'O', 'q', 'T'};
//     int len = sizeof(test)/sizeof(test[0]);
//     selectionSort<char>(test, len);
//     sortEfficiencyTest::printArr<char>(test, len);
//     return 0;
// }
