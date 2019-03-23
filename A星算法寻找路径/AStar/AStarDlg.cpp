
// AStarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AStar.h"
#include "AStarDlg.h"
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


// CAStarDlg 对话框



CAStarDlg::CAStarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAStarDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAStarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAStarDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_NCLBUTTONDOWN()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CAStarDlg 消息处理程序

BOOL CAStarDlg::OnInitDialog()
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
	SetWindowPos(NULL, 300, 300, 1018, 790, WS_EX_TOPMOST);
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			this_map[i][j] = '0';
		}
	}
	//设置障碍物
	this_map[8][1] = '1';
	this_map[8][2] = '1';
	this_map[8][3] = '1';
	this_map[9][3] = '1';
	this_map[10][3] = '1';
	this_map[10][2] = '1';
	this_map[10][1] = '1';

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAStarDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAStarDlg::OnPaint()
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
		CClientDC dc(this);

		for (int i = 0; i < 1500; i += 50)
		{
			dc.MoveTo(POINT{ i, 0 });
			dc.LineTo(POINT{ i, 1000 });
		}
		for (int j = 0; j < 1000; j += 50)
		{
			dc.MoveTo(POINT{ 0, j });
			dc.LineTo(POINT{ 1500, j });
		}


		//画障碍物
		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 15; ++j)
			{
				if (this_map[i][j] == '1')
				{
					POINT p = GetXY(POINT{ i, j });
					CRect rt(p.x - 25, p.y - 25, p.x + 25, p.y + 25);
					dc.FillSolidRect(&rt, RGB(96, 96, 96));
				}
			}
		}

		//坐标字
		CFont font;
		font.CreateFont(13,                                    //   字体的高度   
			0,                                          //   字体的宽度  
			0,                                          //  nEscapement 
			0,                                          //  nOrientation   
			FW_NORMAL,                                  //   nWeight   
			FALSE,                                      //   bItalic   
			FALSE,                                      //   bUnderline   
			0,                                                   //   cStrikeOut   
			ANSI_CHARSET,                             //   nCharSet   
			OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
			CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
			DEFAULT_QUALITY,                       //   nQuality   
			DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
			_T("宋体"));
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 0, 0));

		for (int i = 0; i < 1500; i += 50)
		{
			for (int j = 0; j < 1000; j += 50)
			{
				char buff[128] = { 0 };
				POINT windp = POINT{ i + 6, j + 25 };
				sprintf(buff, "(%d,\r\n%d)", i / 50, j / 50);
				dc.TextOut(windp.x, windp.y, CString(buff));
			}
		}


		//画路径
		CPen green_pen(PS_SOLID, 5, RGB(0, 255, 0));
		dc.SelectObject(green_pen);
		std::vector<POINT>::iterator pre_it = this_cur_path.begin();
		for (std::vector<POINT>::iterator it = this_cur_path.begin(); it != this_cur_path.end(); ++it)
		{
			if (it != this_cur_path.begin())
			{

				dc.MoveTo(GetXY(*pre_it));
				dc.LineTo(GetXY(*it));
				pre_it = it;
			}
		}

		//画起点、终点
		if (!this_cur_path.empty())
		{
			POINT p1 = GetXY(this_cur_path[0]);
			CRect rt1(p1.x - 10, p1.y - 10, p1.x + 10, p1.y + 10);
			dc.FillSolidRect(&rt1, RGB(0, 0, 255));

			POINT p2 = GetXY(this_cur_path[this_cur_path.size() - 1]);
			CRect rt2(p2.x - 10, p2.y - 10, p2.x + 10, p2.y + 10);
			dc.FillSolidRect(&rt2, RGB(255, 20, 147));
		}
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CAStarDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnNcLButtonDown(nHitTest, point);
//}


void CAStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	GetPath(POINT{ 0, 0 }, POINT{ 9, 8 });
	CDialogEx::OnLButtonDown(nFlags, point);
	CAStarDlg::OnPaint();
}


POINT CAStarDlg::GetXY(POINT titlep)
{
	return POINT{ (titlep.x + 0.5) * 50, (titlep.y + 0.5) * 50 };
}

void CAStarDlg::GetPath(POINT titleOr, POINT titleEn)
{
	ClearPath();
	double allcost = abs(titleEn.x - titleOr.x) + abs(titleEn.y - titleOr.y) + abs(titleOr.x - titleOr.x) + abs(titleOr.y - titleOr.y);
	SeekPath(titleOr, POINT{ titleOr.x - 1, titleOr.y }, titleEn, allcost);
}

void CAStarDlg::ClearPath()
{
	this_for_path.clear();
	this_cur_path.clear();
}

bool CAStarDlg::SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost)
{
	//1、判断titleOr是否与titleEn相等（如果相等返回这个点）
	this_for_path.push_back(titleOr);

	if (titleOr.x == titleEn.x&&titleOr.y == titleEn.y)
	{
		//this_cur_path.push_back(titleOr);
		return true;
	}
	//2、获取titleOr的上、下、左、右，等八个点放到vec_points
	std::vector<POINT> vec_points;
	/*vec_points.push_back(POINT{ titleOr.x - 1, titleOr.y - 1 });
	vec_points.push_back(POINT{ titleOr.x - 1, titleOr.y - 0 });
	vec_points.push_back(POINT{ titleOr.x + 1, titleOr.y - 0 });
	vec_points.push_back(POINT{ titleOr.x - 0, titleOr.y - 1 });
	vec_points.push_back(POINT{ titleOr.x - 0, titleOr.y + 1 });
	vec_points.push_back(POINT{ titleOr.x + 1, titleOr.y + 1 });
	vec_points.push_back(POINT{ titleOr.x - 1, titleOr.y + 1 });
	vec_points.push_back(POINT{ titleOr.x + 1, titleOr.y - 1 });*/

	//四个点的
	vec_points.push_back(POINT{ titleOr.x - 1, titleOr.y - 0 });
	vec_points.push_back(POINT{ titleOr.x + 1, titleOr.y - 0 });
	vec_points.push_back(POINT{ titleOr.x - 0, titleOr.y - 1 });
	vec_points.push_back(POINT{ titleOr.x - 0, titleOr.y + 1 });


	//3、遍历vec_points，踢出非法点
	for (std::vector<POINT>::iterator it = vec_points.begin(); it != vec_points.end();)
	{
		POINT pit{ (*it).x, (*it).y };


		//属于this_path的点
		//std::vector<POINT>::iterator iterp = std::find(this_path.begin(), this_path.end(), pit);
		//如果在this_path找到，那么踢出
		bool b = false;
		for (std::vector<POINT>::iterator it = this_for_path.begin(); it != this_for_path.end(); ++it)
		{
			if (pit.x == (*it).x&&pit.y == (*it).y)
			{
				b = true;
			}
		}

		//超出范围的点
		if (pit.x < 0 || pit.y < 0 || pit.x>19 || pit.y>14)
		{
			it = vec_points.erase(it);
		}
		else if (b)
		{
			it = vec_points.erase(it);
		}
		//障碍物踢出
		else if (this_map[pit.x][pit.y] == '1')
		{
			it = vec_points.erase(it);
		}
		else if (this_map[pit.x][pit.y] == '2')
		{
			it = vec_points.erase(it);
		}
		else
		{
			++it;
		}
	}

	//如果是死胡同
	if (vec_points.empty())
	{
		this_for_path.pop_back();
		return false;
	}

	//4、计算剩下合法点，到目标点的步数，最短的点假设为A点,排序从短到长

	for (int i = 0; i < vec_points.size() - 1; i++)
	{
		for (int j = 0; j < vec_points.size() - 1 - i; j++)
		{
			double cost1 = abs(titleEn.x - vec_points[j].x) + abs(titleEn.y - vec_points[j].y) + abs(titleOr.x - vec_points[j].x) + abs(titleOr.y - vec_points[j].y);//pow(pow(titleEn.x - vec_points[j].x, 2) + pow(titleEn.y - vec_points[j].y, 2), 0.5);
			double cost2 = abs(titleEn.x - vec_points[j + 1].x) + abs(titleEn.y - vec_points[j + 1].y) + abs(titleOr.x - vec_points[j + 1].x) + abs(titleOr.y - vec_points[j + 1].y);//pow(pow(titleEn.x - vec_points[j + 1].x, 2) + pow(titleEn.y - vec_points[j + 1].y, 2), 0.5);
			if (cost1 > cost2)
			{
				POINT tmp{ vec_points[j + 1].x, vec_points[j + 1].y };
				vec_points[j + 1].x = vec_points[j].x;
				vec_points[j + 1].y = vec_points[j].y;
				vec_points[j].x = tmp.x;
				vec_points[j].y = tmp.y;
			}
			else if (cost1 == cost2)
			{
				//看转角哪个大
				POINT e1{ vec_points[j].x - titleOr.x, vec_points[j].y - titleOr.y };
				POINT e2{ vec_points[j + 1].x - titleOr.x, vec_points[j + 1].y - titleOr.y };
				POINT eb{ titleOr.x - titlePr.x, titleOr.y - titlePr.y };
				float θ1 = acos(e1.x *eb.x + e1.y * eb.y);
				float θ2 = acos(e2.x *eb.x + e2.y * eb.y);
				if (θ1>θ2)
				{
					POINT tmp{ vec_points[j + 1].x, vec_points[j + 1].y };
					vec_points[j + 1].x = vec_points[j].x;
					vec_points[j + 1].y = vec_points[j].y;
					vec_points[j].x = tmp.x;
					vec_points[j].y = tmp.y;
				}
			}
			else//dis1<dis2
			{
				//不做处理
			}
		}
	}

	POINT pa;
	if (!vec_points.empty())
	{
		pa.x = vec_points[0].x,
			pa.y = vec_points[0].y;
	}


	//5、对A重复第1步到第5步
	bool  bfind = SeekPath(pa, titleOr, titleEn, allcost);

	//6、把A点放入this_path

	if (bfind)
	{
		this_cur_path.push_back(pa);
	}
	else
	{
		this_map[pa.x][pa.y] = '2';
		bool  rfind = SeekPath(pa, titleOr, titleEn, allcost);
		if (!rfind)
		{
			return false;
		}
	}
	
	return true;
}