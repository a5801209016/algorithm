
// drawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "draw.h"
#include "drawDlg.h"
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


// CdrawDlg �Ի���



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


// CdrawDlg ��Ϣ�������

BOOL CdrawDlg::OnInitDialog()
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
	this_point = POINT{100,100};
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CdrawDlg::OnPaint()
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
		//��ʼ����
		CDC* dc = new CDC;
		GetMemCDC(this, dc);

		//��ͼ(��Ͳ���Ҫ�����Ƿ�Ҫ��ձ���ͼƬ��ÿ��this_point���ģ�����һ���µ�ֱ��)
		dc->MoveTo(POINT{ 0, 0 });
		dc->LineTo(this_point);

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
void CdrawDlg::GetMemCDC(CWnd* wnd, CDC* memdc)
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
void CdrawDlg::CopyShows(CWnd* wnd, CDC* memdc)
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
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CdrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdrawDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this_point = point;
	SendMessage(WM_PAINT);
	CDialogEx::OnLButtonDown(nFlags, point);
}
