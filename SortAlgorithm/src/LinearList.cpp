#include "LinearList.hpp"

using std::cout;
using std::endl;

template<class T>
bool LinearList<T>::inited()
{
    return con_ptr != nullptr;
}

template<class T> 
LinearList<T>::LinearList(){}   

template<class T> 
LinearList<T>::LinearList(const int n)
{
    if (!inited())
        initList(n);
    else
        throw "Error, List has inited!";
}

template<class T> 
LinearList<T>::~LinearList()
{
    if (inited())
    {
        if (con_ptr != nullptr)
        {
            delete []con_ptr;
            con_ptr = nullptr;
        }
    }
}

template<class T> 
void LinearList<T>::initList(const int n)
{
    try
    {
        con_ptr = new T[n]();
        maxSize = n;
    }
    catch(const std::exception& e)
    {
        throw e.what();
    }    
}

template<class T> 
void LinearList<T>::initList(T a[], const int n)
{
    try
    {
        con_ptr = new T[n]();
        maxSize = n;
        memcpy(con_ptr, a, n);
        length = n;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

template<class T> 
int LinearList<T>::getLength() noexcept
{
    return length;
}

template<class T> 
T* LinearList<T>::getPtr() noexcept
{
    return con_ptr;
}

template<class T> 
T LinearList<T>::get(const int i)
{
    if (i >= maxSize)
        throw std::range_error("Error, index out of ranges");
    return con_ptr[i];
}

template<class T> 
void LinearList<T>::clearList()
{
    memset(con_ptr, '\0', maxSize);
    length = 0;
}

template<class T>
void LinearList<T>::printList()
{
    if (!inited())
        throw std::length_error("Error, LinearList is not initialized");
    for (int i = 0; i < length; i++)
    {
        cout << con_ptr[i] << endl;
    }
}

template<class T>
void LinearList<T>::insertList(const int i, T a)
{
    if (i < 0 || i >= maxSize)
        throw std::range_error("Error, index out of range");
    if (length == maxSize)
        throw std::range_error("Error, LinearList full length");
    if (i > length - 1 || i == maxSize - 1)
    {
        con_ptr[length] = a;
        length++;
        return;
    }
    for (int j=length; j>i;j--)
    { 
        con_ptr[j] = con_ptr[j - 1];
    }
    con_ptr[i] = a;
    length++;
}

template<class T>
void LinearList<T>::insertList(const int i, T a[], const int n)
{
    if (i < 0 || i >= maxSize)
        throw std::range_error("Error, index out of range");
    if (length == maxSize)
        throw std::range_error("Error, LinearList full length");
    if (n + length > maxSize)
        throw std::range_error("Error, Insurfficient memory");
    if (i >= length - 1)
    {
        for (int j=0;j<n;j++)
            con_ptr[length + j] = a[j];
        length += n;
        return;
    }
    for (int j=length + n; j>=i + n - 1; j--)
        con_ptr[j] = con_ptr[j - n];
    for (int j=0;j<n;j++)
        con_ptr[i + j] = a[j];
    length += n;
}

template<class T>
void LinearList<T>::del(const int i)
{
    if (i < 0 || i >= maxSize)
        throw std::range_error("Error, invalid index");
    if (i >= length - 1)
    {
        con_ptr[length - 1] = '\0';
        length--;
        return;
    }
    for (int j = i; j < length; j++)
        con_ptr[j] = con_ptr[j + 1];
    con_ptr[length - 1] = '\0';
    length--;
}

template<class T>
void LinearList<T>::delList(const int start, const int end)
{
    if (start > end)
        throw std::logic_error("Error, wrong index");
    if (start < 0 || start >= maxSize)
        throw std::range_error("Error, invalid index");
    if (end < 0 || end >= maxSize)
        throw std::logic_error("Error, wrong index");
    if (end > length - 1)
    {
        for (int j = start; j < 2 * length + start; j++)
            con_ptr[j] = con_ptr[j + length - start];
        for (int j = 2 * length + start - 1; j >= length - 1 ; j++)
            con_ptr[j] = '\0';
        length -= length - start;
        return;
    }
    else
    {
        for (int j = start; j <= length + start - end - 2; j++)
            con_ptr[j] = con_ptr[j + end - start + 1];
        for (int j = length + start - end - 2; j >= length - 1 ; j--)
            con_ptr[j] = '\0';
        length -= end - start + 1;
    }
}

template<class T>
void LinearList<T>::alterList(const int i, T a)
{
    if (i < 0 || i >= maxSize)
        throw std::range_error("Error, invalid index");
    if (i == length - 1)
    {
        con_ptr[length - 1] = a;
        return;
    }
    else if (i > length - 1)
    {
        con_ptr[length] = a;
        length++;
        return; 
    }
    con_ptr[i] = a;   
}

template<class T>
void LinearList<T>::alterList(const int i, T a[], const int n)
{
    if (i < 0 || i >= maxSize)
        throw std::range_error("Error, invalid index");
    if (i > length - 1 && length + n > maxSize)
        throw std::range_error("Error, Insurfficient memory");
    if (i + n > maxSize - 1)
        throw std::range_error("Error, LinearList full length");
    if (i > length - 1)
    {
        for (int j = 0; j < n; j++)
            con_ptr[j + length] = a[j];
        length += n;
        return;
    }
    for (int j = 0; j < n; j++)
        con_ptr[j + i] = a[j];
    length += n - (length - i);
}

template<class T>
int LinearList<T>::locate(T a)
{
    for (int i = 0; i < length - 1; i++)
    {
        if (con_ptr[i] == a)
            return i;
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    try
    {
        LinearList<char> a(20);
        a.insertList(0, "hello world", 11);
        a.alterList(8, "4444", 4);
        a.clearList();
        a.printList();
        cout << a.getLength() << endl;
    }
    catch(const char* e)
    {
         cout << e << endl;
    }
    return 0;
}
