
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
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


// CMFCApplication1Dlg 对话框

std::vector<DOT> CMFCApplication1Dlg::m_path;
CMutex CMFCApplication1Dlg::test_mutex;
DATA CMFCApplication1Dlg::this_data;
std::ofstream CMFCApplication1Dlg::writefile("C:\\Users\\Administrator\\Desktop\\log.txt");
DOT CMFCApplication1Dlg::duff[2];

CCounter CMFCApplication1Dlg::this_counter(2, 'x', 'y');

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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
	
	this_data.dc = new CClientDC(this);

	CWinThread* mythread1 = AfxBeginThread(
		ThreadFunc1,
		NULL,
		THREAD_PRIORITY_NORMAL,
		0,
		0,
		NULL
		);
	CWinThread* mythread2 = AfxBeginThread(
		ThreadFunc2,
		NULL,
		THREAD_PRIORITY_NORMAL,
		0,
		0,
		NULL
		);

	// TODO:  在此添加额外的初始化代码
	SetWindowPos(NULL, 100, 100, 1010, 650, SWP_NOMOVE);
	m_map = new MAP(-500, -300, 500, 300);
	m_x.SetValue(DOT(-500, 0), DOT(500,0), 50, -500);
	m_y.SetValue(DOT(0, -500), DOT(0, 500), 50, -500);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::DrawPath()
{
}

void CMFCApplication1Dlg::DrawLine(DOT d1, DOT d2, COLOR c)
{
	DOT dd1 = GetXY(d1);
	DOT dd2 = GetXY(d2);
	POINT p1, p2;
	p1.x = dd1.X();
	p1.y = dd1.Y();
	p2.x = dd2.X();
	p2.y = dd2.Y();

	CClientDC dc(this);
	CPen* newpen = new CPen(PS_SOLID, 1, RGB(c.r, c.g, c.b));
	CPen* oldpen = dc.GetCurrentPen();
	dc.SelectObject(newpen);
	dc.MoveTo(p1);
	dc.LineTo(p2);
	dc.SelectObject(oldpen);
	delete newpen;
	newpen = NULL;
}

void CMFCApplication1Dlg::SetBkColor(COLOR c)
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(c.r, c.g, c.b));
}

bool CMFCApplication1Dlg::HaseDOT(std::vector<DOT> vec, DOT d)
{
	bool result = false;
	for (std::vector<DOT>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if ((*it) == d)
		{
			return true;
		}
	}
	return false;
}

void CMFCApplication1Dlg::FindPath(DOT orginal)
{
	std::list<DOT> list_dot;
	m_path.push_back(orginal);
	for (int i = 1; i <= 8; ++i)
	{
		list_dot = FindNodes(m_path.back(), i);

		//删除已有的节点
		for (std::list<DOT>::iterator it = list_dot.begin(); it != list_dot.end(); ++it)
		{
			if (HaseDOT(m_path, *it))
			{
				it = list_dot.erase(it);
			}
		}
		if (!list_dot.empty())
		{
			break;
		}
		else
		{
			return;
		}
	}

	FindPath(*list_dot.begin());
}

std::list<DOT> CMFCApplication1Dlg::FindNodes(DOT center, int r)
{
	std::list<DOT> vec_dot;
	DOT lef_top(center.X() - r, center.Y() + r);
	DOT right_top(center.X() + r, center.Y() + r);
	DOT lef_bottom(center.X() - r, center.Y() - r);
	DOT right_bottom(center.X() + r, center.Y() - r);
	for (int i = lef_top.X(); i <= right_top.X(); ++i)
	{
		//center.Y()+r
		//std::vector<DOT>::iterator it = std::find(m_path.begin(), m_path.end(), DOT(i, center.Y() + r));
		if (m_map->Node(i, center.Y() + r))
		{
			vec_dot.push_back(DOT(i, center.Y() + r));
		}
	}
	for (int i = lef_bottom.X(); i <= right_bottom.X(); ++i)
	{
		//center.Y()-r
		//std::vector<DOT>::iterator it = std::find(m_path.begin(), m_path.end(), DOT(i, center.Y() - r));
		if (m_map->Node(i, center.Y() - r))
		{
			vec_dot.push_back(DOT(i, center.Y() - r));
		}
	}
	for (int i = lef_bottom.Y(); i <= lef_top.Y(); ++i)
	{
		//center.X()-r
		//std::vector<DOT>::iterator it = std::find(m_path.begin(), m_path.end(), DOT(center.X() - r, i));
		if (m_map->Node(center.X() - r, i))
		{
			vec_dot.push_back(DOT(center.X() - r, i));
		}
	}
	for (int i = right_bottom.Y(); i <= right_top.Y(); ++i)
	{
		//center.X()+r
		//std::vector<DOT>::iterator it = std::find(m_path.begin(), m_path.end(), DOT(center.X() + r, i));
		if (m_map->Node(center.X() + r, i))
		{
			vec_dot.push_back(DOT(center.X() + r, i));
		}
	}
	return vec_dot;
}

UINT CMFCApplication1Dlg::ThreadFunc1(LPVOID lpParam)
{
	
	return 0;
}

//************************************
// Method:    ThreadFunc2
// FullName:  CMFCApplication1Dlg::ThreadFunc2
// Access:    protected static 
// Returns:   UINT
// Qualifier:关键代码
// Parameter: LPVOID lpParam
//************************************
UINT CMFCApplication1Dlg::ThreadFunc2(LPVOID lpParam)
{
	CClientDC* dc = this_data.dc;
	CPen* newpen = new CPen(PS_SOLID, 1, RGB(255, 0, 0));
	dc->SelectObject(newpen);

	while (1)
	{	
		double x0 = 0.0;
		double y0 = 0.0;
		double r = 100.0;

		for (double i = x0 - r; i <= x0 + r; i++)
		{
			for (double j = y0 - r; j <= y0 + r; j++)
			{

				//用计算器计算结果，效果很慢
/*				bool r1 = this_counter.Calculate("x*x+y*y", i + 0.5 - x0, j + 0.5 - y0) < r*r ? 0 : 1;
				bool r2 = this_counter.Calculate("x*x+y*y", i + 0.5 - x0, j - 0.5 - y0) < r*r ? 0 : 1;
				bool r3 = this_counter.Calculate("x*x+y*y", i - 0.5 - x0, j + 0.5 - y0) < r*r ? 0 : 1;
				bool r4 = this_counter.Calculate("x*x+y*y", i - 0.5 - x0, j - 0.5 - y0) < r*r ? 0 : 1;
*/
				//用表达式计算结果，效果还好
				bool r1 = pow(i + 0.5 - x0, 2) + pow(j + 0.5 - y0, 2) < r*r ? 0 : 1;
				bool r2 = pow(i + 0.5 - x0, 2) + pow(j - 0.5 - y0, 2) <= r*r ? 0 : 1;
				bool r3 = pow(i - 0.5 - x0, 2) + pow(j + 0.5 - y0, 2) < r*r ? 0 : 1;
				bool r4 = pow(i - 0.5 - x0, 2) + pow(j - 0.5 - y0, 2) <= r*r ? 0 : 1;

				if ((r1 || r2 || r3 || r4) == 1 && (r1 && r2 && r3 && r4) == 0)
				{
					
					DOT oldp = GetXY(DOT(i, j));
					dc->SetPixel(oldp.X(), oldp.Y(), RGB(255, 0, 0));
					Sleep(1);
				
				}
			}
		}
	}
	return 0;
}
