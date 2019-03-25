
// TankDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tank.h"
#include "TankDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTankDlg �Ի���



CTankDlg::CTankDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTankDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTankDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_NCLBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_COMMAND(ID_LAYOUT_BAR, &CTankDlg::OnLayoutBar)
ON_COMMAND(ID_SEEK_PATH, &CTankDlg::OnSeekPath)
ON_WM_RBUTTONDOWN()
ON_WM_ERASEBKGND()
ON_WM_ACTIVATE()
//ON_WM_TIMER()
ON_WM_TIMER()
END_MESSAGE_MAP()


// CTankDlg ��Ϣ�������

BOOL CTankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//��menu�ؼ���صĴ���
	this_menu.LoadMenu(IDR_MENU1);
	SetMenu(&this_menu);


	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	SetWindowPos(NULL, 300, 300, 1018, 810, WS_EX_TOPMOST);
	for (int i = 0; i < this_map_x; ++i)
	{
		for (int j = 0; j < this_map_y; ++j)
		{
			this_map[i][j] = '0';
		}
	}
	
	//·���������յ������
	CRect rt(POINT{ 500, 500 }, SIZE{ 416, 416 });
	SetClientRect(rt);
	InitPoints();
	SetTimer(1, 0.0, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTankDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTankDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//��ʼ
		CDC* dc = new CDC;
		GetMemCDC(this, dc);

		//��ͼ
		SetBkColor(dc, RGB(0, 0, 0));
		for (int i = 0; i < 1500; i += this_grid_width)
		{
			dc->MoveTo(POINT{ i, 0 });
			dc->LineTo(POINT{ i, 1000 });
		}
		for (int j = 0; j < 1000; j += this_grid_height)
		{
			dc->MoveTo(POINT{ 0, j });
			dc->LineTo(POINT{ 1500, j });
		}

		//���ϰ���
		for (int i = 0; i < this_map_x; ++i)
		{
			for (int j = 0; j < this_map_y; ++j)
			{
				if (this_map[i][j] == '1')
				{
					POINT p = GetXY(POINT{ i, j });
					CRect rt(p.x - this_grid_width / 2, p.y - this_grid_height / 2, p.x + this_grid_width / 2, p.y + this_grid_height/2);
					ShowBitmap(IDB_BITMAP1, dc, rt.TopLeft(), rt.Size());
				}
			}
		}

		ShowImage(_T("res/tank.png"), dc, POINT{ tank_location_dlg.x, tank_location_dlg.y}, SIZE{ 26, 26 }, RGB(0, 0, 0));

		//������
		//CFont font;
		//font.CreateFont(13,                                    //   ����ĸ߶�   
		//	0,                                          //   ����Ŀ��  
		//	0,                                          //  nEscapement 
		//	0,                                          //  nOrientation   
		//	FW_NORMAL,                                  //   nWeight   
		//	FALSE,                                      //   bItalic   
		//	FALSE,                                      //   bUnderline   
		//	0,                                                   //   cStrikeOut   
		//	ANSI_CHARSET,                             //   nCharSet   
		//	OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		//	CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		//	DEFAULT_QUALITY,                       //   nQuality   
		//	DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		//	_T("����"));
		//dc->SelectObject(&font);
		//dc->SetBkMode(TRANSPARENT);
		//dc->SetTextColor(RGB(255, 0, 0));

		//for (int i = 0; i < 1500; i += this_grid_width)
		//{
		//	for (int j = 0; j < 1000; j += this_grid_height)
		//	{
		//		char buff[128] = { 0 };
		//		POINT windp = POINT{ i, j + this_grid_height / 4 };
		//		sprintf(buff, "(%d,\r\n%d)", i / this_grid_width, j / this_grid_height);
		//		dc->TextOut(windp.x, windp.y, CString(buff));
		//	}
		//}


		//��·��
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

		//����㡢�յ�
		//if (!this_cur_path.empty())
		{
			//ȡ��������
			POINT tilep1 = GetTitle(this_point1);
			POINT p1 = GetXY(tilep1);
			//��С����
			CRect rt1(p1.x - 10, p1.y - 10, p1.x + 10, p1.y + 10);
			dc->FillSolidRect(&rt1, RGB(0, 0, 255));

			//ȡ��������
			POINT tilep2 = GetTitle(this_point2);
			POINT p2 = GetXY(tilep2);
			//��С����
			CRect rt2(p2.x - 10, p2.y - 10, p2.x + 10, p2.y + 10);
			dc->FillSolidRect(&rt2, RGB(255, 20, 147));
		}

		//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
		CopyShows(this, dc);
		CDialogEx::OnPaint();
	}
}

//************************************
// Method:    GetCDC
// FullName:  CTankDlg::GetCDC
// Access:    protected 
// Returns:   CDC
// Qualifier:��ȡһ�������CDC
//************************************
void CTankDlg::GetMemCDC(CWnd* wnd, CDC* memdc)
{
	CClientDC dc(wnd);
	CBitmap MemBitmap;//����һ��λͼ����

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	memdc->CreateCompatibleDC(NULL);
	//��ʱ�����ܻ�ͼ����Ϊû�еط��� ^_^
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С
	CRect rcWnd;
	GetClientRect(rcWnd);
	MemBitmap.CreateCompatibleBitmap(wnd->GetDC(), rcWnd.Width(), rcWnd.Height());

	//��λͼѡ�뵽�ڴ���ʾ�豸��
	//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
	CBitmap *pOldBit = memdc->SelectObject(&MemBitmap);

	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����
	//��Ҳ�������Լ�Ӧ���õ���ɫ
	memdc->FillSolidRect(0, 0, rcWnd.Width(), rcWnd.Height(), RGB(255, 255, 255));

	return;
}

//************************************
// Method:    CopyShows
// FullName:  CTankDlg::CopyShows
// Access:    protected 
// Returns:   void
// Qualifier:������memdc��ʾ��wnd��
// Parameter: CWnd * wnd
// Parameter: CDC memdc
//************************************
void CTankDlg::CopyShows(CWnd* wnd, CDC* memdc)
{
	CClientDC dc(wnd);
	CRect rcWnd;
	wnd->GetWindowRect(&rcWnd);
	dc.BitBlt(0, 0, rcWnd.Width(), rcWnd.Height(), memdc, 0, 0, SRCCOPY);
	//��ͼ��ɺ������
	memdc->GetCurrentBitmap()->DeleteObject();
	memdc->DeleteDC();
	delete memdc;
	memdc = NULL;
}

//���ô��屳����ɫ
void CTankDlg::SetBkColor(CDC* dc, COLORREF color)
{
	CRect rect;
	GetClientRect(rect);
	dc->FillSolidRect(rect, color);
}

//************************************
// Method:    ClearMap
// FullName:  CTankDlg::ClearMap
// Access:    private 
// Returns:   void
// Qualifier:���this_mapΪ'2'�ĵ�
//************************************
void CTankDlg::ClearMap()
{
	for (int i = 0; i < this_map_x;++i)
	{
		for (int j = 0; j < this_map_y;++j)
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
// FullName:  CTankDlg::ClearLoop
// Access:    protected 
// Returns:   void
// Qualifier:ȥ��·���еĻ������磺this_cur_path���Ϊ{[0,0]},[1,0],[1,1],[2,1],[2,0],[3,0]}��
// ��ô{[1,0],[1,1],[2,1],[2,0]}����һ������Ҫȥ����
//************************************
void CTankDlg::ClearLoop()
{
	if (this_cur_path.size()>=4)
	{
		for (std::vector<POINT>::iterator i = this_cur_path.begin(); i != this_cur_path.end()-2;)
		{
			POINT p = *i;
			for (std::vector<POINT>::iterator j = i + 2; j != this_cur_path.end();)
			{
				POINT memp = *j;
				//�����ж�

				if ((abs(p.x - memp.x) == 0 && abs(p.y - memp.y) == 1) ||
					(abs(p.x - memp.x) == 1 && abs(p.y - memp.y) == 0))
				{
					//ɾ���м�ڵ�
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTankDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//************************************
// Method:    GetXY
// FullName:  CTankDlg::GetXY
// Access:    protected 
// Returns:   POINT
// Qualifier:�߿������ɴ�������
// Parameter: POINT titlep
//************************************
POINT CTankDlg::GetXY(POINT titlep)
{
	return POINT{ (titlep.x + 0.5) * this_grid_width, (titlep.y + 0.5) * this_grid_height };
}

POINT CTankDlg::GetTitle(POINT xy)
{
	return POINT{ int(xy.x / this_grid_width), int(xy.y / this_grid_height) };
}

//************************************
// Method:    GetPath
// FullName:  CTankDlg::GetPath
// Access:    protected 
// Returns:   void
// Qualifier:��ȡ·����this_cur_path
// Parameter: POINT titleOr//���
// Parameter: POINT titleEn//�յ�
//************************************
void CTankDlg::GetPath(POINT titleOr, POINT titleEn)
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
// FullName:  CTankDlg::ClearPath
// Access:    protected 
// Returns:   void
// Qualifier:��Ԥ��·������ȷ·������
//************************************
void CTankDlg::ClearPath()
{
	this_for_path.clear();
	this_cur_path.clear();
}

void CTankDlg::InitPoints()
{
	this_point1 = POINT{ INT_MAX, INT_MAX };
	this_point2 = POINT{ INT_MAX, INT_MAX };
}

//************************************
// Method:    SeekPath
// FullName:  CTankDlg::SeekPath
// Access:    protected 
// Returns:   bool
// Qualifier:����A���㷨
// Parameter: POINT titleOr
// Parameter: POINT titlePr
// Parameter: POINT titleEn
// Parameter: int allcost
//************************************
bool CTankDlg::SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost)
{
	//1���ж�titleOr�Ƿ����ϰ���
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
	//2����ȡtitleOr���ϡ��¡����ң��Ȱ˸���ŵ�vec_points
	std::vector<POINT> vec_points;
	/*vec_points.push_back(POINT{ titleOr.x - 1, titleOr.y - 1 });
	vec_points.push_back(POINT{ titleOr.x - 1, titleOr.y - 0 });
	vec_points.push_back(POINT{ titleOr.x + 1, titleOr.y - 0 });
	vec_points.push_back(POINT{ titleOr.x - 0, titleOr.y - 1 });
	vec_points.push_back(POINT{ titleOr.x - 0, titleOr.y + 1 });
	vec_points.push_back(POINT{ titleOr.x + 1, titleOr.y + 1 });
	vec_points.push_back(POINT{ titleOr.x - 1, titleOr.y + 1 });
	vec_points.push_back(POINT{ titleOr.x + 1, titleOr.y - 1 });*/

	//�ĸ����
	vec_points.push_back(POINT{ titleOr.x - 1, titleOr.y - 0 });
	vec_points.push_back(POINT{ titleOr.x + 1, titleOr.y - 0 });
	vec_points.push_back(POINT{ titleOr.x - 0, titleOr.y - 1 });
	vec_points.push_back(POINT{ titleOr.x - 0, titleOr.y + 1 });


	//3������vec_points���߳��Ƿ���
	for (std::vector<POINT>::iterator it = vec_points.begin(); it != vec_points.end();)
	{
		POINT pit{ (*it).x, (*it).y };


		//����this_path�ĵ�
		//std::vector<POINT>::iterator iterp = std::find(this_path.begin(), this_path.end(), pit);
		//�����this_path�ҵ�����ô�߳�
		bool b = false;
		for (std::vector<POINT>::iterator it = this_for_path.begin(); it != this_for_path.end(); ++it)
		{
			if (pit.x == (*it).x&&pit.y == (*it).y)
			{
				b = true;
			}
		}

		//������Χ�ĵ�
		if (pit.x < 0 || pit.y < 0 || pit.x>19 || pit.y>14)
		{
			it = vec_points.erase(it);
		}
		else if (b)
		{
			it = vec_points.erase(it);
		}
		//�ϰ����߳�
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

	//���������ͬ
	if (vec_points.empty())
	{
		this_for_path.pop_back();
		return false;
	}

	//4������ʣ�ºϷ��㣬��Ŀ���Ĳ�������̵ĵ����ΪA��,����Ӷ̵���

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
				//��ת���ĸ���
				POINT e1{ vec_points[j].x - titleOr.x, vec_points[j].y - titleOr.y };
				POINT e2{ vec_points[j + 1].x - titleOr.x, vec_points[j + 1].y - titleOr.y };
				POINT eb{ titleOr.x - titlePr.x, titleOr.y - titlePr.y };
				float ��1 = acos(e1.x *eb.x + e1.y * eb.y);
				float ��2 = acos(e2.x *eb.x + e2.y * eb.y);
				if (��1>��2)
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
				//��������
			}
		}
	}

	//POINT pa;
	//if (!vec_points.empty())
	//{
	//	pa.x = vec_points[0].x;
	//	pa.y = vec_points[0].y;
	//}


	////5����A�ظ���1������5��
	//bool  bfind = SeekPath(pa, titleOr, titleEn, allcost);

	////6����A�����this_path

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
			//������titleOr��϶�Ҫ����this_mapΪ'2'�ĵ�
			ClearMap();
			return true;

		}
		else
		{
			this_map[pa.x][pa.y] = '2';

		}
	}
	////������titleOr��϶�Ҫ����this_mapΪ'2'�ĵ�
	ClearMap();
	return false;
}

//************************************
// Method:    OnLButtonDown
// FullName:  CTankDlg::OnLButtonDown
// Access:    protected 
// Returns:   void
// Qualifier:�������¼�
// Parameter: UINT nFlags
// Parameter: CPoint point
//************************************
void CTankDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (this_cur_menu == ID_SEEK_PATH)
	{
		InitPoints();
		ClearPath();
		this_point1 = POINT{ point.x, point.y };
	}
	//��������ϰ���
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


void CTankDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�һ������ϰ���
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

void CTankDlg::OnLayoutBar()
{
	// TODO:  �ڴ���������������
	//MessageBoxA(NULL, "ID_LAYOUT_BAR", "WARN", 0);
	this_cur_menu = ID_LAYOUT_BAR;
}


void CTankDlg::OnSeekPath()
{
	// TODO:  �ڴ���������������
	//MessageBoxA(NULL, "ID_SEEK_PATH", "WARN", 0);
	this_cur_menu = ID_SEEK_PATH;
}


BOOL CTankDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return CDialogEx::OnEraseBkgnd(pDC);
}

void CTankDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	SendMessage(WM_PAINT);
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	// TODO:  �ڴ˴������Ϣ����������
}

//************************************
// Method:    SetClientRect
// FullName:  CTankDlg::SetClientRect
// Access:    protected 
// Returns:   void
// Qualifier:���ݴ��ڿͻ������ô���
// Parameter: CRect clientrt
//************************************
void CTankDlg::SetClientRect(CRect clientrt)
{
	CRect c_rt;
	GetClientRect(&c_rt);
	CRect w_rt;
	GetWindowRect(&w_rt);
	int width = clientrt.Width() + w_rt.Width() - c_rt.Width();
	int height = clientrt.Height() + w_rt.Height() - c_rt.Height();
	SetWindowPos(NULL, clientrt.TopLeft().x, clientrt.TopLeft().y, width, height, SWP_NOMOVE);
}

//************************************
// Method:    ShowBitmap
// FullName:  CDrawDlg::ShowBitmap
// Access:    private 
// Returns:   void
// Qualifier: �����Ͻ�locate�����ߴ�Ϊsi��λͼ
// Parameter: POINT locate
// Parameter: SIZE si
//************************************
void CTankDlg::ShowBitmap(UINT ID, CDC* dc, POINT locate, SIZE si)
{
	CBitmap bitmap;
	//����λͼ��Դ
	bitmap.LoadBitmap(ID);
	//��������ȡ�豸������
	CBrush brush(&bitmap);
	//����λͼ��ˢ����������
	dc->FillRect(CRect(locate, si), &brush);
}

void CTankDlg::ShowImage(LPCTSTR filepath, CDC* dc, POINT locate, SIZE si, UINT rgb)
{
	CImage cImg;
	CBrush brush;
	if (cImg.Load(filepath) == S_OK)
	{
		CImage cImg;
		CBrush brush;
		if (cImg.Load(filepath) == S_OK)
		{

			CBitmap bitMap;
			bitMap.Attach(cImg.Detach());

			CDC memdc;
			memdc.CreateCompatibleDC(NULL);
			memdc.SelectObject(&bitMap);

			dc->TransparentBlt(locate.x, locate.y, si.cx, si.cy, &memdc, 0, 0, si.cx, si.cy, rgb);
			bitMap.DeleteObject();

		}
	}
}


void CTankDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent==1)
	{
		if (timer_cout%100==0)
		{
			tank_location_dlg = POINTF{ tank_location_dlg.x + 1.0, tank_location_dlg.y };
		}
	} 
	else
	{
	}
	SendMessage(WM_PAINT);
	++timer_cout;
	CDialogEx::OnTimer(nIDEvent);
}
