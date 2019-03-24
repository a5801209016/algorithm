
// AStarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AStar.h"
#include "AStarDlg.h"
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


// CAStarDlg �Ի���



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


// CAStarDlg ��Ϣ�������

BOOL CAStarDlg::OnInitDialog()
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
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			this_map[i][j] = '0';
		}
	}
	
	//·���������յ������
	InitPoints();

	SetTimer(1, 1, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAStarDlg::OnPaint()
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
		CDC* dc = new CDC;
		GetMemCDC(this, dc);

		//��ͼ
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


		//���ϰ���
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

		//������
		CFont font;
		font.CreateFont(13,                                    //   ����ĸ߶�   
			0,                                          //   ����Ŀ��  
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
			_T("����"));
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
// FullName:  CAStarDlg::GetCDC
// Access:    protected 
// Returns:   CDC
// Qualifier:��ȡһ�������CDC
//************************************
void CAStarDlg::GetMemCDC(CWnd* wnd, CDC* memdc)
{
	CClientDC dc(wnd);
	CBitmap MemBitmap;//����һ��λͼ����

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	memdc->CreateCompatibleDC(NULL);
	//��ʱ�����ܻ�ͼ����Ϊû�еط��� ^_^
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С
	CRect rcWnd;
	GetClientRect(rcWnd);
	MemBitmap.CreateCompatibleBitmap(this->GetDC(), rcWnd.Width(), rcWnd.Height());

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
// FullName:  CAStarDlg::CopyShows
// Access:    protected 
// Returns:   void
// Qualifier:������memdc��ʾ��wnd��
// Parameter: CWnd * wnd
// Parameter: CDC memdc
//************************************
void CAStarDlg::CopyShows(CWnd* wnd, CDC* memdc)
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

//************************************
// Method:    ClearMap
// FullName:  CAStarDlg::ClearMap
// Access:    private 
// Returns:   void
// Qualifier:���this_mapΪ'2'�ĵ�
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
// Qualifier:ȥ��·���еĻ������磺this_cur_path���Ϊ{[0,0]},[1,0],[1,1],[2,1],[2,0],[3,0]}��
// ��ô{[1,0],[1,1],[2,1],[2,0]}����һ������Ҫȥ����
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
HCURSOR CAStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//************************************
// Method:    GetXY
// FullName:  CAStarDlg::GetXY
// Access:    protected 
// Returns:   POINT
// Qualifier:�߿������ɴ�������
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
// Qualifier:��ȡ·����this_cur_path
// Parameter: POINT titleOr//���
// Parameter: POINT titleEn//�յ�
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
// Qualifier:��Ԥ��·������ȷ·������
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
// Qualifier:����A���㷨
// Parameter: POINT titleOr
// Parameter: POINT titlePr
// Parameter: POINT titleEn
// Parameter: int allcost
//************************************
bool CAStarDlg::SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost)
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
// FullName:  CAStarDlg::OnLButtonDown
// Access:    protected 
// Returns:   void
// Qualifier:�������¼�
// Parameter: UINT nFlags
// Parameter: CPoint point
//************************************
void CAStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
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


void CAStarDlg::OnRButtonDown(UINT nFlags, CPoint point)
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

void CAStarDlg::OnLayoutBar()
{
	// TODO:  �ڴ���������������
	//MessageBoxA(NULL, "ID_LAYOUT_BAR", "WARN", 0);
	this_cur_menu = ID_LAYOUT_BAR;
}


void CAStarDlg::OnSeekPath()
{
	// TODO:  �ڴ���������������
	//MessageBoxA(NULL, "ID_SEEK_PATH", "WARN", 0);
	this_cur_menu = ID_SEEK_PATH;
}


BOOL CAStarDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return CDialogEx::OnEraseBkgnd(pDC);
}

void CAStarDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	// TODO:  �ڴ˴������Ϣ����������
}
