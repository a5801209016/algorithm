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
//第一个参数：3个参数,后面随便定义
CCouter c(3,'x','y','z');

//第一个参数：输入表达式，11代表x，12代表y，13代表z
//输出为11*11+12*12+13*13
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

