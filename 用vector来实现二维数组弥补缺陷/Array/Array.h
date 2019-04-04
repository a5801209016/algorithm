#pragma once
#include <vector>
#include <stdarg.h>

using namespace std;

//һά����
template<class T>
class Barry
{
public:
	Barry(int n);
	~Barry();
	T operator [](const int& n);
private:
	vector<T> m_barry;
};

template<class T>
Barry<T>::Barry(int n)
{
	m_barry.resize(n);
}

template<class T>
Barry<T>::	~Barry()
{

}

template<class T>
T Barry<T>::operator [](const int& n)
{
	return T;
}


//��ά����
template<class T>
class Array
{
public:
	Array(int row, int col, ...);
	~Array();
	Barry<T >& operator [](const int& n);
private:
	vector<Barry<T> > m_arrays;
};


template<class T>
Array<T>::Array(int row, int col, ...)
{
	for(int k=0;k<row;++k)
	{
		Barry<T> b_t(col);
		m_arrays.push_back(b_t);
	}


	va_list   arg_ptr;   //����ɱ����ָ�� 
    va_start(arg_ptr,col);   // iΪ���һ���̶�����
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			m_arrays[i].swap();
		}
	}
    va_end(arg_ptr);        //  ��ղ���ָ��
}

template<class T>
Array<T>::	~Array()
{

}

template<class T>
Barry<T>& Array<T>::operator [](const int& n)
{
	return m_arrays[n];
}