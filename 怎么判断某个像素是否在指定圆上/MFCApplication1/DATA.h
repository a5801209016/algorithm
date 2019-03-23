#pragma once
class DATA
{
public:
	DATA(CClientDC* d, CListBox* pl);
	DATA();
public:
	CClientDC* dc;
	CListBox* plist;
};