
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	SetWindowPos(NULL, 300, 300, 1018, 790, WS_EX_TOPMOST);
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			this_map[i][j] = '0';
		}
	}
	//�����ϰ���
	this_map[8][1] = '1';
	this_map[8][2] = '1';
	this_map[8][3] = '1';
	this_map[9][3] = '1';
	this_map[10][3] = '1';
	this_map[10][2] = '1';
	this_map[10][1] = '1';

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


		//���ϰ���
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


		//��·��
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

		//����㡢�յ�
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CAStarDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnNcLButtonDown(nHitTest, point);
//}


void CAStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	//1���ж�titleOr�Ƿ���titleEn��ȣ������ȷ�������㣩
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

	POINT pa;
	if (!vec_points.empty())
	{
		pa.x = vec_points[0].x,
			pa.y = vec_points[0].y;
	}


	//5����A�ظ���1������5��
	bool  bfind = SeekPath(pa, titleOr, titleEn, allcost);

	//6����A�����this_path

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