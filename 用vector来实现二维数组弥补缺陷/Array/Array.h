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
	va_list   arg_ptr;   //����ɱ����ָ�� 
    va_start(arg_ptr,n);   // iΪ���һ���̶�����
    T j=va_arg(arg_ptr,T);   //���ص�һ���ɱ����������Ϊint
    T c=va_arg(arg_ptr,T);   //���صڶ����ɱ����������Ϊchar
    va_end(arg_ptr);        //  ��ղ���ָ��
}

template<class T>
Array<T>::	~Array()
{

}