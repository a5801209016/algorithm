
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
ON_COMMAND(ID_LAYOUT_BAR, &CAStarDlg::OnLayoutBar)
ON_COMMAND(ID_SEEK_PATH, &CAStarDlg::OnSeekPath)
ON_WM_RBUTTONDOWN()
ON_WM_ERASEBKGND()
ON_WM_ACTIVATE()
//ON_WM_TIMER()
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

	//与menu控件相关的代码
	this_menu.LoadMenu(IDR_MENU1);
	SetMenu(&this_menu);

	// TODO:  在此添加额外的初始化代码
	SetWindowPos(NULL, 300, 300, 1018, 810, WS_EX_TOPMOST);
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			this_map[i][j] = '0';
		}
	}
	
	//路径的起点和终点的设置
	InitPoints();

	SetTimer(1, 1, NULL);
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
		CDC* dc = new CDC;
		GetMemCDC(this, dc);

		//绘图
		for (int i = 0; i < 1500; i += 50)
		{
			dc->MoveTo(POINT{ i, 0 });
			dc->LineTo(POINT{ i, 1000 });
		}
		for (int j = 0; j < 1000; j += 50)
		{
			dc->MoveTo(POINT{ 0, j });
			dc->LineTo(POINT{ 1500, j });
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
					dc->FillSolidRect(&rt, RGB(96, 96, 96));
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
		dc->SelectObject(&font);
		dc->SetBkMode(TRANSPARENT);
		dc->SetTextColor(RGB(255, 0, 0));

		for (int i = 0; i < 1500; i += 50)
		{
			for (int j = 0; j < 1000; j += 50)
			{
				char buff[128] = { 0 };
				POINT windp = POINT{ i + 6, j + 25 };
				sprintf(buff, "(%d,\r\n%d)", i / 50, j / 50);
				dc->TextOut(windp.x, windp.y, CString(buff));
			}
		}


		//画路径
		CPen green_pen(PS_SOLID, 5, RGB(0, 255, 0));
		dc->SelectObject(green_pen);
		std::vector<POINT>::iterator pre_it = this_cur_path.begin();
		for (std::vector<POINT>::iterator it = this_cur_path.begin(); it != this_cur_path.end(); ++it)
		{
			if (it != this_cur_path.begin())
			{

				dc->MoveTo(GetXY(*pre_it));
				dc->LineTo(GetXY(*it));
				pre_it = it;
			}
		}

		//画起点、终点
		//if (!this_cur_path.empty())
		{
			//取坐标整数
			POINT tilep1 = GetTitle(this_point1);
			POINT p1 = GetXY(tilep1);
			//画小方块
			CRect rt1(p1.x - 10, p1.y - 10, p1.x + 10, p1.y + 10);
			dc->FillSolidRect(&rt1, RGB(0, 0, 255));

			//取坐标整数
			POINT tilep2 = GetTitle(this_point2);
			POINT p2 = GetXY(tilep2);
			//画小方块
			CRect rt2(p2.x - 10, p2.y - 10, p2.x + 10, p2.y + 10);
			dc->FillSolidRect(&rt2, RGB(255, 20, 147));
		}

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
void CAStarDlg::GetMemCDC(CWnd* wnd, CDC* memdc)
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
void CAStarDlg::CopyShows(CWnd* wnd, CDC* memdc)
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

//************************************
// Method:    ClearMap
// FullName:  CAStarDlg::ClearMap
// Access:    private 
// Returns:   void
// Qualifier:清除this_map为'2'的点
//************************************
void CAStarDlg::ClearMap()
{
	for (int i = 0; i < 20;++i)
	{
		for (int j = 0; j < 15;++j)
		{
			if (this_map[i][j]=='2')
			{
				this_map[i][j] = '0';
			}
		}
	}
}

//************************************
// Method:    ClearLoop
// FullName:  CAStarDlg::ClearLoop
// Access:    protected 
// Returns:   void
// Qualifier:去掉路径中的环（比如：this_cur_path如果为{[0,0]},[1,0],[1,1],[2,1],[2,0],[3,0]}，
// 那么{[1,0],[1,1],[2,1],[2,0]}就是一个环，要去掉）
//************************************
void CAStarDlg::ClearLoop()
{
	if (this_cur_path.size()>=4)
	{
		for (std::vector<POINT>::iterator i = this_cur_path.begin(); i != this_cur_path.end()-2;)
		{
			POINT p = *i;
			for (std::vector<POINT>::iterator j = i + 2; j != this_cur_path.end();)
			{
				POINT memp = *j;
				//横向判定

				if ((abs(p.x - memp.x) == 0 && abs(p.y - memp.y) == 1) ||
					(abs(p.x - memp.x) == 1 && abs(p.y - memp.y) == 0))
				{
					//删除中间节点
					j = this_cur_path.erase(i + 1, j );
					i = j-1;
					break;
				}
				++j;
			}
			++i;
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//************************************
// Method:    GetXY
// FullName:  CAStarDlg::GetXY
// Access:    protected 
// Returns:   POINT
// Qualifier:瓦块坐标变成窗口坐标
// Parameter: POINT titlep
//************************************
POINT CAStarDlg::GetXY(POINT titlep)
{
	return POINT{ (titlep.x + 0.5) * 50, (titlep.y + 0.5) * 50 };
}

POINT CAStarDlg::GetTitle(POINT xy)
{
	return POINT{ int(xy.x/50), int(xy.y/50) };
}

//************************************
// Method:    GetPath
// FullName:  CAStarDlg::GetPath
// Access:    protected 
// Returns:   void
// Qualifier:获取路径到this_cur_path
// Parameter: POINT titleOr//起点
// Parameter: POINT titleEn//终点
//************************************
void CAStarDlg::GetPath(POINT titleOr, POINT titleEn)
{
	ClearPath();
	double allcost = abs(titleEn.x - titleOr.x) + abs(titleEn.y - titleOr.y) + abs(titleOr.x - titleOr.x) + abs(titleOr.y - titleOr.y);
	bool b = SeekPath(titleOr, POINT{ titleOr.x - 1, titleOr.y }, titleEn, allcost);
	if (b)
	{
		this_cur_path.push_back(titleOr);
	}
	ClearLoop();
}

//************************************
// Method:    ClearPath
// FullName:  CAStarDlg::ClearPath
// Access:    protected 
// Returns:   void
// Qualifier:将预测路径和正确路径清理
//************************************
void CAStarDlg::ClearPath()
{
	this_for_path.clear();
	this_cur_path.clear();
}

void CAStarDlg::InitPoints()
{
	this_point1 = POINT{ INT_MAX, INT_MAX };
	this_point2 = POINT{ INT_MAX, INT_MAX };
}

//************************************
// Method:    SeekPath
// FullName:  CAStarDlg::SeekPath
// Access:    protected 
// Returns:   bool
// Qualifier:核心A星算法
// Parameter: POINT titleOr
// Parameter: POINT titlePr
// Parameter: POINT titleEn
// Parameter: int allcost
//************************************
bool CAStarDlg::SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost)
{
	//1、判断titleOr是否是障碍点
	if (titleOr.x >= 20 || titleOr.y>=15)
	{
		return false;
	}
 	if (this_map[titleOr.x][titleOr.y]=='1')
	{
		return false;
	}
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

	//POINT pa;
	//if (!vec_points.empty())
	//{
	//	pa.x = vec_points[0].x;
	//	pa.y = vec_points[0].y;
	//}


	////5、对A重复第1步到第5步
	//bool  bfind = SeekPath(pa, titleOr, titleEn, allcost);

	////6、把A点放入this_path

	//if (bfind)
	//{
	//	this_cur_path.push_back(pa);
	//}
	//else
	//{
	//	this_map[pa.x][pa.y] = '2';
	//	vec_points.erase(vec_points.begin());
	//	if (!vec_points.empty())
	//	{
	//		pa.x = vec_points[0].x;
	//		pa.y = vec_points[0].y;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//	bool  rfind = SeekPath(pa, titleOr, titleEn, allcost);
	//	if (!rfind)
	//	{
	//		return false;
	//	}
	//}

	for (std::vector<POINT>::iterator it = vec_points.begin(); it != vec_points.end(); ++it)
	{
		POINT pa;
		pa.x = (*it).x;
		pa.y = (*it).y;

		bool  bfind = SeekPath(pa, titleOr, titleEn, allcost);
		if (bfind)
		{
			this_cur_path.push_back(pa);
			//处理完titleOr后肯定要清理this_map为'2'的点
			ClearMap();
			return true;

		}
		else
		{
			this_map[pa.x][pa.y] = '2';

		}
	}
	////处理完titleOr后肯定要清理this_map为'2'的点
	ClearMap();
	return false;
}

//************************************
// Method:    OnLButtonDown
// FullName:  CAStarDlg::OnLButtonDown
// Access:    protected 
// Returns:   void
// Qualifier:鼠标左击事件
// Parameter: UINT nFlags
// Parameter: CPoint point
//************************************
void CAStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (this_cur_menu == ID_SEEK_PATH)
	{
		InitPoints();
		ClearPath();
		this_point1 = POINT{ point.x, point.y };
	}
	//左击布置障碍物
	else if (this_cur_menu == ID_LAYOUT_BAR)
	{
		POINT pindex = GetTitle(POINT{ point.x, point.y });
		this_map[pindex.x][pindex.y] = '1';
	}
	else
	{
		
	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
	SendMessage(WM_PAINT);
}


void CAStarDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//右击消除障碍物
	if (this_cur_menu == ID_SEEK_PATH)
	{
		this_point2 = POINT{ point.x, point.y };
		GetPath(GetTitle(this_point1), GetTitle(this_point2));
	}
	if (this_cur_menu == ID_LAYOUT_BAR)
	{
		POINT pindex = GetTitle(POINT{ point.x, point.y });
		this_map[pindex.x][pindex.y] = '0';
	}

	
	CDialogEx::OnRButtonDown(nFlags, point);
	SendMessage(WM_PAINT);
}

void CAStarDlg::OnLayoutBar()
{
	// TODO:  在此添加命令处理程序代码
	//MessageBoxA(NULL, "ID_LAYOUT_BAR", "WARN", 0);
	this_cur_menu = ID_LAYOUT_BAR;
}


void CAStarDlg::OnSeekPath()
{
	// TODO:  在此添加命令处理程序代码
	//MessageBoxA(NULL, "ID_SEEK_PATH", "WARN", 0);
	this_cur_menu = ID_SEEK_PATH;
}


BOOL CAStarDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return CDialogEx::OnEraseBkgnd(pDC);
}

void CAStarDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	// TODO:  在此处添加消息处理程序代码
}
