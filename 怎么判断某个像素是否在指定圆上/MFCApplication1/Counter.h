#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <stdarg.h>
using std::string;
using std::stack;
using std::cout;
using std::cin;
using std::endl;
/*
//��һ��������3������,������㶨��
CCouter c(3,'x','y','z');

//��һ��������������ʽ��11����x��12����y��13����z
//���Ϊ11*11+12*12+13*13
Calculate("x*x+y*y+z*z",11,12,13);
*/
class CCounter
{
public:
	CCounter(int lengh, ...);
	~CCounter();
	double Calculate(string s,...);
protected:
	string &toPosfix(string &s, string &format);
	double calculatePosfix(string &s);
	double calculateinfix(string &s);
	string&   replace_all(string&   str, const  string&  old_value, const  string&  new_value);
protected:
	int m_size;
	std::vector<char> m_vx;
};

