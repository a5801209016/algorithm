
// TankDlg.h : 头文件
//

#pragma once
#include "SelfTank.h"

// CTankDlg 对话框
class CTankDlg : public CDialogEx
{
// 构造
public:
	CTankDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_Tank_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void GetPath(POINT titleOr, POINT titleEn);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLayoutBar();
	afx_msg void OnSeekPath();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	DECLARE_MESSAGE_MAP()
	
	
protected:
	//根据窗口客户区设置窗口
	void SetClientRect(CRect clientrt);

	POINT GetXY(POINT titlep);
	POINT GetTitle(POINT xy);
	
	void ClearPath();
	void InitPoints();
	bool SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost);

	//ID为位图的ID号，locate为位图的左上角坐标，si为位图的尺寸
	void ShowBitmap(UINT ID, CDC* dc, POINT locate, SIZE si);

	//在CDC中贴png图片
	void ShowImage(LPCTSTR filepath, CDC* dc, POINT locate, SIZE si, UINT rgb);

	//获取一个缓存的CDC
	void GetMemCDC(CWnd* wnd, CDC* memdc);

	//将内存中的图拷贝到屏幕上进行显示
	void CopyShows(CWnd* wnd, CDC* memdc);

	//清除this_map为'2'的点
	void ClearMap();

	//去掉路径中的环（比如：this_cur_path如果为{[0,0]},[1,0],[1,1],[2,1],[2,0],[3,0]}，那么{[1,0],[1,1],[2,1],[2,0]}就是一个环，要去掉）
	void ClearLoop();

	//设置窗口背景
	void SetBkColor(CDC* dc, COLORREF color);

	//与路径相关的成员变量
private:
	//对应界面显示的大小
	static const int this_map_x = 13;//改这里就行
	static const int this_map_y = 13;//改这里就行
	char this_map[this_map_x][this_map_y];

	//每个格子的像素大小
	int this_grid_width = 32;//改这里就行
	int this_grid_height = 32;//改这里就行

	//与坦克相关的
private:
	//坦克的尺寸大小(像素)
	SIZE tank_size = SIZE{ 26, 26 };

	//坦克的位置坐标(瓦块)
	POINT tank_location_tit = POINT{ 0, 0 };

	//坦克的位置坐标(窗口)
	POINTF tank_location_dlg =POINTF{ tank_location_tit.x*this_grid_width + tank_size.cx/2, tank_location_tit.y *this_grid_height+tank_size.cy/2 };
	
	//坦克
	SelfTank this_self_tank;
	//与控件相关的成员变量
private:
	CMenu this_menu;
	int this_cur_menu=0;

	//与路径相关的
private:
	POINT this_point1;//起点
	POINT this_point2;//终点
	std::vector<POINT> this_for_path;
	std::vector<POINT> this_cur_path;

public:
	
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};