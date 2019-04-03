#pragma once
#include <vector>
#include <stdarg.h>

using namespace std;

template<class T>
class Array
{
public:
	Array(int n, ...);
	~Array();

private:
	vector<vector<T> > m_arrays;
};


template<class T>
Array<T>::Array(int n,...)
{
	va_list   arg_ptr;   //定义可变参数指针 
    va_start(arg_ptr,n);   // i为最后一个固定参数
    T j=va_arg(arg_ptr,T);   //返回第一个可变参数，类型为int
    T c=va_arg(arg_ptr,T);   //返回第二个可变参数，类型为char
    va_end(arg_ptr);        //  清空参数指针
}

template<class T>
Array<T>::	~Array()
{

}