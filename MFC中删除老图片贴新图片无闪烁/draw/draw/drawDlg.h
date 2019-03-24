
// drawDlg.h : 头文件
//

#pragma once


// CdrawDlg 对话框
class CdrawDlg : public CDialogEx
{
// 构造
public:
	CdrawDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	//获取一个缓存的CDC
	void GetMemCDC(CWnd* wnd, CDC* memdc);

	//将内存中的图拷贝到屏幕上进行显示
	void CopyShows(CWnd* wnd, CDC* memdc);

private:
	POINT this_point;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
