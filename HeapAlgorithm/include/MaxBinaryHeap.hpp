/**
* @file     MaxBinaryHeap.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-21
*/
#ifndef __MAXBINARYHEAP_H__
#define __MAXBINARYHEAP_H__

#include <memory>
#include <cassert>
#include <string>
#include <ctime>

using std::cout;
using std::endl;
using std::string;

template <class Item>
class MaxBinaryHeap
{
private:
	int count;
	int capcity;
	std::unique_ptr<Item[]> ptr;

	void putNumberInLine(int num, string& line, int index_cur_level, int cur_tree_width, bool isLeft);
	void putBranchInLine(string& line, int index_cur_level, int cur_tree_width);
	bool full();
	void expandHeap(); // 储存堆的数组内存满后自动扩容
	void shiftUp(int i); // 将堆底的元素上升至二叉树的合适节点位置
	void shiftDown(int i); // 将堆顶的元素下降至二叉树的合适节点位置
public:
	MaxBinaryHeap(const int cap);
	MaxBinaryHeap(Item arr[], const int n); // 传入数组直接转化为堆数据结构
	~MaxBinaryHeap();
	int size();
	bool empty();
	void printHeap(); // 以树状打印整个堆结构
	void insetItem(Item n);
	Item get(int i);
	Item extractMax();
};

template <class Item>
MaxBinaryHeap<Item>::MaxBinaryHeap(Item arr[], const int n) :
	ptr(new Item[n + 1]),
	capcity(n),
	count(n)
{
	std::copy(arr, arr + n, ptr.get() + 1); // 首先拷贝数据, 注意将第一个元素空余出来，从索引1起作为堆顶元素
	for (size_t i = n / 2; i >= 1; i--) // 从最后一个有子节点的节点i / 2，起开始进行反向下降，将大元素上升至堆顶(Heapify)
		shiftDown(i);
}

template <class Item>
void MaxBinaryHeap<Item>::shiftDown(int i)
{
	Item aux = ptr[i];  // 使用临时值储存该需要下降的元素，赋值法替换swap提升算法效率
	int j;
	while (2 * i <= count) // 确保i位置肯定有子节点（即有左节点）
	{
		j = 2 * i; // j用来记录需要与i节点置换位置的子节点索引
		if (j + 1 <= count && ptr[j + 1] >= ptr[j]) // 有右子节点且右节点比左子节点大，则只用比较i节点和右子节点
			j++;
		//if (ptr[j] <= ptr[i]) // 子节点比父节点小，不需要再继续向下调换
		//	break;
		//std::swap(ptr[j], ptr[i]); // 交换比父节点大的子节点数值
		if (ptr[j] <= aux)
			break;
		ptr[i] = ptr[j];
		i = j;
	}
	ptr[i] = aux;
}

template <class Item>
Item MaxBinaryHeap<Item>::extractMax()
{
	assert(count > 0);
	Item ret = ptr[1];

	std::swap(ptr[1], ptr[count]); // 首先将堆顶节点与堆底最后一个元素交换
	count--;
	shiftDown(1);
	return ret;
}

template <class Item>
Item MaxBinaryHeap<Item>::get(int i)
{
	return ptr[i];
}

template <class Item>
void MaxBinaryHeap<Item>::shiftUp(int i)
{
	Item aux = ptr[i];
	//while (i > 1 && ptr[i / 2] < ptr[i]) // 跳过顶节点，子节点大于父节点的都需要上升并置换
	while (i > 1 && ptr[i / 2] < aux)
	{
		//std::swap(ptr[i], ptr[i / 2]);
		ptr[i] = ptr[i / 2];
		i /= 2;
	}
	ptr[i] = aux;
}

template <class Item>
void MaxBinaryHeap<Item>::expandHeap()
{
	std::unique_ptr<Item[]> aux(new Item[capcity * 2 + 1]);
	std::copy(ptr.get(), ptr.get() + capcity * 2 + 1, aux.get());
	ptr.swap(aux);
	aux.reset();
	capcity *= 2;
}

template <class Item>
bool MaxBinaryHeap<Item>::full()
{
	return count + 1 > capcity;
}

template <class Item>
void MaxBinaryHeap<Item>::insetItem(Item n)  // 二叉树节点i，其左子节点索引2*i，右子节点索引2*i + 1
{
	if (full()) // 二叉树数组如果容量已满，自动扩容expandSize大小
		expandHeap();
	ptr[count + 1] = n; // 将元素首先放置在最后的节点
	count++;
	shiftUp(count); // 将元素上升至正确的节点处
}

template <class Item>
void MaxBinaryHeap<Item>::putBranchInLine(string& line, int index_cur_level, int cur_tree_width)
{
	int sub_tree_width = (cur_tree_width - 1) / 2;
	int sub_sub_tree_width = (sub_tree_width - 1) / 2;
	int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
	assert(offset_left + 1 < line.size());
	int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
	assert(offset_right < line.size());

	line[offset_left + 1] = '/';
	line[offset_right + 0] = '\\';
}

template <class Item>
void MaxBinaryHeap<Item>::putNumberInLine(int num, string& line, int index_cur_level, int cur_tree_width, bool isLeft)
{
	int sub_tree_width = (cur_tree_width - 1) / 2;
	int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
	assert(offset + 1 < line.size());
	if (num >= 10) {
		line[offset + 0] = '0' + num / 10;
		line[offset + 1] = '0' + num % 10;
	}
	else {
		if (isLeft)
			line[offset + 0] = '0' + num;
		else
			line[offset + 1] = '0' + num;
	}
}

template <class Item>
void MaxBinaryHeap<Item>::printHeap()
{
	// 我们的testPrint只能打印100个元素以内的堆的树状信息
	if (size() >= 100) {
		cout << "This print function can only work for less than 100 int";
		return;
	}

	// 我们的testPrint只能处理整数信息
	if (typeid(Item) != typeid(int)) {
		cout << "This print function can only work for int item";
		return;
	}

	cout << "The max heap size is: " << size() << endl;
	cout << "Data in the max heap: ";
	for (int i = 1; i <= size(); i++) {
		// 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
		assert(ptr[i] >= 0 && ptr[i] < 100);
		cout << ptr[i] << " ";
	}
	cout << endl;
	cout << endl;

	int n = size();
	int max_level = 0;
	int number_per_level = 1;
	while (n > 0) {
		max_level += 1;
		n -= number_per_level;
		number_per_level *= 2;
	}

	int max_level_number = int(pow(2, max_level - 1));
	int cur_tree_max_level_number = max_level_number;
	int index = 1;
	for (int level = 0; level < max_level; level++) {
		string line1 = string(max_level_number * 3 - 1, ' ');

		int cur_level_number = std::min(count - int(pow(2, level)) + 1, int(pow(2, level)));
		bool isLeft = true;
		for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
			putNumberInLine(ptr[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
			isLeft = !isLeft;
		}
		cout << line1 << endl;

		if (level == max_level - 1)
			break;

		string line2 = string(max_level_number * 3 - 1, ' ');
		for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
			putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
		cout << line2 << endl;

		cur_tree_max_level_number /= 2;
	}
}

template <class Item>
bool MaxBinaryHeap<Item>::empty()
{
	return !count;
}

template <class Item>
int MaxBinaryHeap<Item>::size()
{
	return count;
}

template <class Item>
MaxBinaryHeap<Item>::~MaxBinaryHeap()
{
	ptr.reset();
}

template<class Item>
inline MaxBinaryHeap<Item>::MaxBinaryHeap(const int cap) :
	ptr(new Item[cap + 1])
{
	capcity = cap;
	count = 0;
};

#endif //__MAXBINARYHEAP_H__