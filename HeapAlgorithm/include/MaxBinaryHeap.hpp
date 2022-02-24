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
	void expandHeap(); // ����ѵ������ڴ������Զ�����
	void shiftUp(int i); // ���ѵ׵�Ԫ���������������ĺ��ʽڵ�λ��
	void shiftDown(int i); // ���Ѷ���Ԫ���½����������ĺ��ʽڵ�λ��
public:
	MaxBinaryHeap(const int cap);
	MaxBinaryHeap(Item arr[], const int n); // ��������ֱ��ת��Ϊ�����ݽṹ
	~MaxBinaryHeap();
	int size();
	bool empty();
	void printHeap(); // ����״��ӡ�����ѽṹ
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
	std::copy(arr, arr + n, ptr.get() + 1); // ���ȿ�������, ע�⽫��һ��Ԫ�ؿ��������������1����Ϊ�Ѷ�Ԫ��
	for (size_t i = n / 2; i >= 1; i--) // �����һ�����ӽڵ�Ľڵ�i / 2����ʼ���з����½�������Ԫ���������Ѷ�(Heapify)
		shiftDown(i);
}

template <class Item>
void MaxBinaryHeap<Item>::shiftDown(int i)
{
	Item aux = ptr[i];  // ʹ����ʱֵ�������Ҫ�½���Ԫ�أ���ֵ���滻swap�����㷨Ч��
	int j;
	while (2 * i <= count) // ȷ��iλ�ÿ϶����ӽڵ㣨������ڵ㣩
	{
		j = 2 * i; // j������¼��Ҫ��i�ڵ��û�λ�õ��ӽڵ�����
		if (j + 1 <= count && ptr[j + 1] >= ptr[j]) // �����ӽڵ����ҽڵ�����ӽڵ����ֻ�ñȽ�i�ڵ�����ӽڵ�
			j++;
		//if (ptr[j] <= ptr[i]) // �ӽڵ�ȸ��ڵ�С������Ҫ�ټ������µ���
		//	break;
		//std::swap(ptr[j], ptr[i]); // �����ȸ��ڵ����ӽڵ���ֵ
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

	std::swap(ptr[1], ptr[count]); // ���Ƚ��Ѷ��ڵ���ѵ����һ��Ԫ�ؽ���
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
	//while (i > 1 && ptr[i / 2] < ptr[i]) // �������ڵ㣬�ӽڵ���ڸ��ڵ�Ķ���Ҫ�������û�
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
void MaxBinaryHeap<Item>::insetItem(Item n)  // �������ڵ�i�������ӽڵ�����2*i�����ӽڵ�����2*i + 1
{
	if (full()) // ������������������������Զ�����expandSize��С
		expandHeap();
	ptr[count + 1] = n; // ��Ԫ�����ȷ��������Ľڵ�
	count++;
	shiftUp(count); // ��Ԫ����������ȷ�Ľڵ㴦
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
	// ���ǵ�testPrintֻ�ܴ�ӡ100��Ԫ�����ڵĶѵ���״��Ϣ
	if (size() >= 100) {
		cout << "This print function can only work for less than 100 int";
		return;
	}

	// ���ǵ�testPrintֻ�ܴ���������Ϣ
	if (typeid(Item) != typeid(int)) {
		cout << "This print function can only work for int item";
		return;
	}

	cout << "The max heap size is: " << size() << endl;
	cout << "Data in the max heap: ";
	for (int i = 1; i <= size(); i++) {
		// ���ǵ�testPrintҪ����е�����������[0, 100)�ķ�Χ��
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