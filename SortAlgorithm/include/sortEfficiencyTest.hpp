/*
 * @Author: Victor Wong
 * @Date: 2022-02-16 12:03:58
 * @LastEditors: Victor Wong
 * @LastEditTime: 2022-02-16 22:12:11
 * @Description: file content
 */
#ifndef __SORTEFFICIENCYTEST_H__
#define __SORTEFFICIENCYTEST_H__

#include <iostream>
#include <ctime>
#include <string>
#include <cassert>

using std::string;
using std::cout;
using std::endl;
using std::swap;
using std::copy;


 namespace sortEfficiencyTest
 {
     /**
      * @description: None
      * @param {int} n 生成随机数组的大小
      * @param {int} L 生成随机数组的左右边界
      * @param {int} R
      * @return {*}
      */
     int* randomIntArrSample(const int n, const int L, const int R)
     {
         int* arr = new int[n];
         srand(time(NULL));  // 根据时钟生成随机种子
         for(int i = 0; i < n; i++)
         {
             arr[i] = rand() % (R - L + 1) + L; // 取[L, R]区间的随机整数填充数组
         }
         return arr;
     }
    
     template<class T>
     void printArr(T arr[], const int n)
     {
         for (int i = 0; i < n; i++)
         {
             cout << arr[i] << " ";
         }
         cout << endl; 
     }
    
     int* randomNearlyOrderedArr(const int n, const int swapTimes)
     {
         int* arr = new int[n];
         for (int i = 0; i < n; i++)
             arr[i] = i;
         srand(time(NULL));
         for (int i = 0; i < swapTimes; i++)
         {
             int m = rand() % n;
             int o = rand() % n;
             swap(arr[m], arr[o]);
         }
         return arr;
     }
    
     int* copyIntArr(int arr[], const int n)
     {
         int* arrT = new int[n];
         std::copy(arr, arr + n, arrT);
         return arrT;
     }
    
     template<class T>
     bool isSorted(T arr[], const int n)
     {
         for (int i = 0; i < n - 1; i++)
         {
             if (arr[i] > arr[i + 1])
                 return false;
         }
         return true;
     }
    
     template<class T>
     void staticsSortEfficiency(const string& sortName, void(*sort)(T[], const int), T arr[], const int n)
     {
         clock_t start = clock();
         sort(arr, n);
         clock_t end = clock();
         cout << sortName << " : " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
         assert(isSorted(arr, n));
     }
 };

#endif // __SORTEFFICIENCYTEST_H__