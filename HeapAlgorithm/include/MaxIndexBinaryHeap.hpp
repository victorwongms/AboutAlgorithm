/**
* @file     MaxIndexBinaryHeap.hpp
* @brief
* @details
* @author   VictorWong
* @date     2022-2-22
*/
#ifndef __MAXINDEXBINARYHEAP_H__
#define __MAXINDEXBINARYHEAP_H__

#include <memory>
#include <cassert>
#include <string>
#include <ctime>

using std::cout;
using std::endl;
using std::string;

template <class Item>
class MaxIndexBinaryHeap  // 最大索引二叉堆,从索引为0开始存储数据，而非1
{
private:
	int count;
	int capcity;
	std::unique_ptr<Item[]> ptr;
	std::unique_ptr<int[]> indexes; // 用于储存二叉堆中元素在数组中的索引
	std::unique_ptr<int[]> reverse; // 用于反向查找，储存二叉堆元素所对应的indexes中的索引值 reverse[indexes[i]] = i, indexes[reverse[i]] = i

	void putNumberInLine(int num, string& line, int index_cur_level, int cur_tree_width, bool isLeft);
	void putBranchInLine(string& line, int index_cur_level, int cur_tree_width);
	bool full(int i = 0);
	void expandHeap(); // 储存堆的数组内存满后自动扩容
	void shiftUp(int i); // 将堆底的元素上升至二叉树的合适节点位置
	void shiftDown(int i); // 将堆顶的元素下降至二叉树的合适节点位置
	bool contain(int i); // 数组中是否包含索引为i的元素
public:
	MaxIndexBinaryHeap(const int cap);
	MaxIndexBinaryHeap(Item arr[], const int n); // 传入数组直接转化为堆数据结构
	~MaxIndexBinaryHeap();
	int size();
	bool empty();
	void printHeap(); // 以树状打印整个堆结构
	void insetItem(int i, Item n); // 在索引为i处插入元素
	Item getItem(int i); // 获取索引为i处的元素
	Item extractMax();
	int extrackMaxIndex(); // 获取二叉堆堆顶元素的索引
	Item getMax(); // 获取最大二叉堆顶元素
	int getMaxIndex(); // 获取最大二叉堆顶元素的索引
	void change(int i, Item n); // 将二叉堆中索引为i处元素修改为Item n
};

template <class Item>
void MaxIndexBinaryHeap<Item>::change(int i, Item n)
{
	assert(contain(i));
	i++;
	ptr[i] = n;
	shiftUp(reverse[i]);
	shiftDown(reverse[i]);
}

template <class Item>
int MaxIndexBinaryHeap<Item>::getMaxIndex()
{
	assert(count > 0);
	return indexes[1] - 1;
}

template <class Item>
Item MaxIndexBinaryHeap<Item>::getMax()
{
	assert(count > 0);
	return ptr[indexes[1]];
}

template <class Item>
int MaxIndexBinaryHeap<Item>::extrackMaxIndex()
{
	assert(count > 0);
	int ret = indexes[1] - 1;
	std::swap(indexs[1], indexes[count]);
	reverse[indexes[count]] = 0; // 删除置换后的堆顶元素
	count--;
	if (count)
	{
		reverse[indexes[1]] = 1;
		shiftDown(1);
	}
	return ret;
}

template <class Item>
bool MaxIndexBinaryHeap<Item>::contain(int i)
{
	assert(i + 1 >= 1 && i + 1 <= capcity);
	return reverse[i + 1] != 0; // 通过判断reverse中是否为0判断是否存在该元素
}

template <class Item>
MaxIndexBinaryHeap<Item>::MaxIndexBinaryHeap(Item arr[], const int n) :
	ptr(new Item[n + 1]),
	indexes(new int[n + 1]),
	reverse(new int[n + 1]()),
	capcity(n),
	count(n)
{
	std::copy(arr, arr + n, ptr.get() + 1); // 首先拷贝数据, 注意将第一个元素空余出来，从索引1起作为堆顶元素

	for (size_t i = 1; i <= count; i++)
	{
		indexes[i] = i;
		reverse[i] = i;
	}
	for (size_t i = n / 2; i >= 1; i--) // 从最后一个有子节点的节点i / 2，起开始进行反向下降，将大元素上升至堆顶(Heapify)
		shiftDown(i);
}

template <class Item>
void MaxIndexBinaryHeap<Item>::shiftDown(int i)
{
	Item aux = ptr[indexes[i]];  // 使用临时值储存该需要下降的元素，赋值法替换swap提升算法效率
	int auxIndex = i;
	int j;
	while (2 * i <= count) // 确保i位置肯定有子节点（即有左节点）
	{
		j = 2 * i; // j用来记录需要与i节点置换位置的子节点索引
		if (j + 1 <= count && ptr[indexes[j + 1]] >= ptr[indexes[j]]) // 有右子节点且右节点比左子节点大，则只用比较i节点和右子节点
			j++;
		//if (ptr[j] <= ptr[i]) // 子节点比父节点小，不需要再继续向下调换
		//	break;
		//std::swap(ptr[j], ptr[i]); // 交换比父节点大的子节点数值
		if (ptr[indexes[j]] <= aux)
			break;
		reverse[indexes[i]] = j;
		indexes[i] = indexes[j];
		i = j;
	}
	//ptr[indexes[i]] = aux;
	indexes[i] = indexes[auxIndex];
	reverse[indexes[i]] = auxIndex;
}

template <class Item>
Item MaxIndexBinaryHeap<Item>::extractMax()
{
	assert(count > 0);
	Item ret = ptr[indexes[1]];

	std::swap(indexes[1], indexes[count]); // 首先将堆顶节点与堆底最后一个元素交换
	reverse[indexes[count]] = 0;
	count--;
	if (count)
	{
		reverse[indexes[1]] = 1;
		shiftDown(1);
	}
	return ret;
}

template <class Item>
Item MaxIndexBinaryHeap<Item>::getItem(int i)
{
	assert(contain(i));
	return ptr[indexes[i + 1]];
}

template <class Item>
void MaxIndexBinaryHeap<Item>::shiftUp(int i)
{
	Item aux = ptr[indexes[i]];
	//while (i > 1 && ptr[i / 2] < ptr[i]) // 跳过顶节点，子节点大于父节点的都需要上升并置换
	while (i > 1 && ptr[indexes[i / 2]] < aux)
	{
		//std::swap(ptr[i], ptr[i / 2]);
		indexes[i] = indexes[i / 2];
		reverse[indexes[i]] = i;
		reverse[indexes[i / 2]] = i / 2;
		i /= 2;
	}
	ptr[indexes[i]] = aux;
}

template <class Item>
void MaxIndexBinaryHeap<Item>::expandHeap()
{
	std::unique_ptr<Item[]> aux(new Item[capcity * 2 + 1]);
	std::copy(ptr.get(), ptr.get() + capcity * 2 + 1, aux.get());
	ptr.swap(aux);
	aux.reset();
	capcity *= 2;
}

template <class Item>
bool MaxIndexBinaryHeap<Item>::full(int i)
{
	return count + 1 > capcity;
}

template <class Item>
void MaxIndexBinaryHeap<Item>::insetItem(int i, Item n)  // 二叉树节点i，其左子节点索引2*i，右子节点索引2*i + 1
{
	if (full()) // 二叉树数组如果容量已满，自动扩容expandSize大小
		expandHeap();
	assert(!contain(i)); // 确保索引i对应位置没有元素
	i += 1; 
	ptr[i] = n;
	indexes[count + 1] = i; // 将元素索引设置为最后一个位置
	reverse[i] = count + 1;
	//ptr[count + 1] = n; // 将元素首先放置在最后的节点
	count++;
	shiftUp(count); // 将元素上升至正确的节点处
}

template <class Item>
void MaxIndexBinaryHeap<Item>::putBranchInLine(string& line, int index_cur_level, int cur_tree_width)
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
void MaxIndexBinaryHeap<Item>::putNumberInLine(int num, string& line, int index_cur_level, int cur_tree_width, bool isLeft)
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
void MaxIndexBinaryHeap<Item>::printHeap()
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
bool MaxIndexBinaryHeap<Item>::empty()
{
	return !count;
}

template <class Item>
int MaxIndexBinaryHeap<Item>::size()
{
	return count;
}

template <class Item>
MaxIndexBinaryHeap<Item>::~MaxIndexBinaryHeap()
{
	ptr.release();
	indexes.release();
	reverse.release();
	ptr.reset();
	indexes.reset();
	reverse.reset();
}

template<class Item>
inline MaxIndexBinaryHeap<Item>::MaxIndexBinaryHeap(const int cap) :
	ptr(new Item[cap + 1]),
	indexes(new int[cap + 1]),
	reverse(new int[cap + 1]())  // reverse中初始化元素均为0，代表元素不存在
{
	capcity = cap;
	count = 0;
};

#endif //__MAXINDEXBINARYHEAP_H__