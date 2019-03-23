
// AStarDlg.h : 头文件
//

#pragma once


// CAStarDlg 对话框
class CAStarDlg : public CDialogEx
{
// 构造
public:
	CAStarDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ASTAR_DIALOG };

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
	DECLARE_MESSAGE_MAP()
	
	
protected:
	POINT GetXY(POINT titlep);
	POINT GetTitle(POINT xy);
	
	void ClearPath();
	bool SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost);

//与路径相关的成员变量
private:
	char this_map[20][15];
	std::vector<POINT> this_for_path;
	std::vector<POINT> this_cur_path;

//与控件相关的成员变量
private:
	CMenu this_menu;
	int this_cur_menu=0;

private:
	POINT this_point1;//起点
	POINT this_point2;//终点
	
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
