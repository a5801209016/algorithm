
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "MAP.h"
#include "AXES.h"
#include "DATA.h"
#include "Counter.h"

#include <iostream>
#include <fstream>

struct COLOR
{
	COLOR(int x, int y, int z)
	{
		r = x;
		g = y;
		b = z;
	}

	int r;
	int g;
	int b;
}; 

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMFCApplication1Dlg()
	{
		writefile.close();
		delete m_map;
		m_map = NULL;
	}
// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	MAP* m_map;
	AXES m_x;
	AXES m_y;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	//把中点坐标转换为窗口坐标
static
	DOT GetXY(DOT d2)
	{
		DOT d(d2.X() + 500, 300 - d2.Y());
		return d;
	}
	void DrawPath();

	//画一条线

	void DrawLine(DOT d1, DOT d2, COLOR c);

	//设置窗体背景颜色
	void SetBkColor(COLOR c);

	bool HaseDOT(std::vector<DOT> vec, DOT d);

	void FindPath(DOT orginal);

	//在以center为中心，长度为2r的正方形内寻找符合要求的节点
	std::list<DOT> FindNodes(DOT center, int r);

protected:
	static UINT ThreadFunc1(LPVOID lpParam);
	static UINT ThreadFunc2(LPVOID lpParam);

protected:
	static std::vector<DOT> m_path;
	static DOT duff[2];
	static CMutex test_mutex;
	static DATA this_data;
	static std::ofstream writefile;
	static CCounter this_counter;
};
