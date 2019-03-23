#include "stdafx.h"
#include "Counter.h"


CCounter::CCounter(int lengh, ...)
{
	m_size = lengh;
	va_list arg;
	va_start(arg, lengh);
	for (int i = 1; i <= m_size; ++i)
	{
		char b = va_arg(arg, char);
		m_vx.push_back(b);
	}

	va_end(arg);
}

CCounter::~CCounter()
{
}

double CCounter::Calculate(string s, ...)
{
	string stc = s;
	
	va_list arg;
	va_start(arg, s);
	std::vector<CString> vec;
	double itr;
	for (int i = 0; i < m_size;++i)
	{
		char new_buff[256] = { 0 };
		itr = va_arg(arg, double);
		if (itr >= 0.0)
		{
			sprintf(new_buff, "%lf", itr);
		}
		else
		{
			sprintf(new_buff, "(0%lf)", itr);
		}
		string old_otr=" ";
		old_otr[0]= m_vx[i];
		//replace_all(stc, otr, str);
		replace_all(stc, old_otr, new_buff);
		memset(new_buff, 0, 256);
	}
	
	va_end(arg);
	return calculateinfix(stc);
}

string & CCounter::toPosfix(string &s, string &format)
{
	//中缀表达式转后缀表达式，并且可以计算小数
	stack<char> sta;
	string numbers{ "0123456789." };
	string signl{ "+-" };
	string signh{ "*/" };
	string numbe;//判断某数是否为多位数
	bool flag = false;
	for (const char &ch : s)
	{
		if (ch == ' ') continue;
		//判断这是几位数
		if (numbers.find(ch) != string::npos)
		{
			flag = true;
			numbe.push_back(ch);
			continue;
		}
		else if (flag)
		{
			flag = false;
			format.insert(format.end(), numbe.begin(), numbe.end());
			numbe.clear();
			format.push_back(' ');
		}
		//判断ch什么符号
		if (ch == '(') sta.push(ch);
		else if (signl.find(ch) != string::npos)
		{//如果进栈的是“+-”运算符
			while (!sta.empty() && sta.top() != '(')
			{
				format.push_back(sta.top());
				format.push_back(' ');
				sta.pop();
			}
			sta.push(ch);
		}
		else if (signh.find(ch) != string::npos)
		{
			while (!sta.empty() && sta.top() != '('&&signh.find(sta.top()) != string::npos)
			{
				format.push_back(sta.top());
				format.push_back(' ');
				sta.pop();
			}
			sta.push(ch);
		}
		else if (ch == ')')
		{
			//ch==')'
			while (!sta.empty() && sta.top() != '(')
			{
				format.push_back(sta.top());
				format.push_back(' ');
				sta.pop();
			}
			sta.pop();
		}
	}
	if (!numbe.empty())
	{
		format.insert(format.end(), numbe.begin(), numbe.end());
		numbe.clear();
		format.push_back(' ');
	}
	while (!sta.empty())
	{
		format.push_back(sta.top());
		format.push_back(' ');
		sta.pop();
	}
	return format;
}

double CCounter::calculatePosfix(string &s)
{
	stack<double> sta;
	double sum = 0;
	string numbers{ "0123456789." };
	string sign{ "+-*/" };
	string numbe;
	double num1, num2;
	for (const char &ch : s)
	{
		if (ch == ' '&&!numbe.empty())
		{
			double digit = stod(numbe);
			sta.push(digit);
			numbe.clear();
		}
		if (numbers.find(ch) != string::npos)
			numbe.push_back(ch);
		else if (sign.find(ch) != string::npos)
		{
			num2 = sta.top(), sta.pop();
			num1 = sta.top(), sta.pop();
			double ans = 0;
			switch (ch)
			{
			case '+':
				ans += num1 + num2;
				break;
			case '-':
				ans += num1 - num2;
				break;
			case '*':
				ans += num1*num2;
				break;
			case '/':
				ans += num1 / num2;
				break;
			}
			sta.push(ans);
		}
	}
	while (!sta.empty())
	{
		sum += sta.top();
		sta.pop();
	}
	return sum;
}

double CCounter::calculateinfix(string &s)
{
	string format;
	toPosfix(s, format);
	return calculatePosfix(format);
}

string& CCounter::replace_all(string& str, const string& old_value, const string& new_value)
{
	
		for (string::size_type pos(0); pos != string::npos; pos += new_value.length())   {
			if ((pos = str.find(old_value, pos)) != string::npos)
				str.replace(pos, old_value.length(), new_value);
			else   break;
		}
		return   str;
	
}
