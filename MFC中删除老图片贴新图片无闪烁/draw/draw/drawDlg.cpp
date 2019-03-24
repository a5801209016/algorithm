
// drawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "draw.h"
#include "drawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdrawDlg 对话框



CdrawDlg::CdrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdrawDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CdrawDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CdrawDlg 消息处理程序

BOOL CdrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	this_point = POINT{100,100};
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//开始绘制
		CDC* dc = new CDC;
		GetMemCDC(this, dc);

		//画图(你就不需要考虑是否要清空背景图片，每次this_point更改，画出一条新的直线)
		dc->MoveTo(POINT{ 0, 0 });
		dc->LineTo(this_point);

		//将内存中的图拷贝到屏幕上进行显示
		CopyShows(this, dc);
		CDialogEx::OnPaint();
	}
}

//************************************
// Method:    GetCDC
// FullName:  CAStarDlg::GetCDC
// Access:    protected 
// Returns:   CDC
// Qualifier:获取一个缓存的CDC
//************************************
void CdrawDlg::GetMemCDC(CWnd* wnd, CDC* memdc)
{
	CClientDC dc(wnd);
	CBitmap MemBitmap;//定义一个位图对象

	//随后建立与屏幕显示兼容的内存显示设备
	memdc->CreateCompatibleDC(NULL);
	//这时还不能绘图，因为没有地方画 ^_^
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	CRect rcWnd;
	GetClientRect(rcWnd);
	MemBitmap.CreateCompatibleBitmap(this->GetDC(), rcWnd.Width(), rcWnd.Height());

	//将位图选入到内存显示设备中
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap *pOldBit = memdc->SelectObject(&MemBitmap);

	//先用背景色将位图清除干净，这里我用的是白色作为背景
	//你也可以用自己应该用的颜色
	memdc->FillSolidRect(0, 0, rcWnd.Width(), rcWnd.Height(), RGB(255, 255, 255));

	return;
}

//************************************
// Method:    CopyShows
// FullName:  CAStarDlg::CopyShows
// Access:    protected 
// Returns:   void
// Qualifier:将缓存memdc显示到wnd上
// Parameter: CWnd * wnd
// Parameter: CDC memdc
//************************************
void CdrawDlg::CopyShows(CWnd* wnd, CDC* memdc)
{
	CClientDC dc(wnd);
	CRect rcWnd;
	wnd->GetWindowRect(&rcWnd);
	dc.BitBlt(0, 0, rcWnd.Width(), rcWnd.Height(), memdc, 0, 0, SRCCOPY);
	//绘图完成后的清理
	memdc->GetCurrentBitmap()->DeleteObject();
	memdc->DeleteDC();
	delete memdc;
	memdc = NULL;
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CdrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdrawDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	this_point = point;
	SendMessage(WM_PAINT);
	CDialogEx::OnLButtonDown(nFlags, point);
}
