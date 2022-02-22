#ifndef __LINEARLIST__
#define __LINEARLIST__
#include <iostream>
#include <string>
#include <cstring>
#include <exception>

using std::cout;
using std::endl;

template <class T>
class LinearList
{
public:
    LinearList(const int n);
    LinearList();
    ~LinearList();

    void initList(const int n);
    void initList(T a[], const int n);
    inline int getLength() noexcept;
    void printList();
    inline T* getPtr() noexcept;
    void insertList(const int i, T a);
    void insertList(const int i, T a[], const int n);
    void del(const int i);
    void delList(const int start, const int end);
    void alterList(const int i, T a);
    void alterList(const int i, T a[], const int n);
    inline T get(const int i);
    void clearList();
    int locate(T a);
private:
    T* con_ptr {nullptr};
    int length {0};
    int maxSize {0};
    bool inited();
};

#endif // !__LINEARLIST__