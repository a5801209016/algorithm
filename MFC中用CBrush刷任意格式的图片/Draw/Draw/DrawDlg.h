
// DrawDlg.h : 头文件
//

#pragma once


// CDrawDlg 对话框
class CDrawDlg : public CDialogEx
{
// 构造
public:
	CDrawDlg(CWnd* pParent = NULL);	// 标准构造函数

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
	//刷bmp的图片
	void ShowBitmap(UINT ID, CDC* dc, POINT locate, SIZE si);

	//刷png的图片,rgb为忽略的颜色
	void ShowImage(LPCTSTR filepath, CDC* dc, POINT locate, SIZE si, UINT rgb);
};
