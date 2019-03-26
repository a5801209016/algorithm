
// TankDlg.h : ͷ�ļ�
//

#pragma once
#include "SelfTank.h"

// CTankDlg �Ի���
class CTankDlg : public CDialogEx
{
// ����
public:
	CTankDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_Tank_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	void GetPath(POINT titleOr, POINT titleEn);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLayoutBar();
	afx_msg void OnSeekPath();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	DECLARE_MESSAGE_MAP()
	
	
protected:
	//���ݴ��ڿͻ������ô���
	void SetClientRect(CRect clientrt);

	POINT GetXY(POINT titlep);
	POINT GetTitle(POINT xy);
	
	void ClearPath();
	void InitPoints();
	bool SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost);

	//IDΪλͼ��ID�ţ�locateΪλͼ�����Ͻ����꣬siΪλͼ�ĳߴ�
	void ShowBitmap(UINT ID, CDC* dc, POINT locate, SIZE si);

	//��CDC����pngͼƬ
	void ShowImage(LPCTSTR filepath, CDC* dc, POINT locate, SIZE si, UINT rgb);

	//��ȡһ�������CDC
	void GetMemCDC(CWnd* wnd, CDC* memdc);

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	void CopyShows(CWnd* wnd, CDC* memdc);

	//���this_mapΪ'2'�ĵ�
	void ClearMap();

	//ȥ��·���еĻ������磺this_cur_path���Ϊ{[0,0]},[1,0],[1,1],[2,1],[2,0],[3,0]}����ô{[1,0],[1,1],[2,1],[2,0]}����һ������Ҫȥ����
	void ClearLoop();

	//���ô��ڱ���
	void SetBkColor(CDC* dc, COLORREF color);

	//��·����صĳ�Ա����
private:
	//��Ӧ������ʾ�Ĵ�С
	static const int this_map_x = 13;//���������
	static const int this_map_y = 13;//���������
	char this_map[this_map_x][this_map_y];

	//ÿ�����ӵ����ش�С
	int this_grid_width = 32;//���������
	int this_grid_height = 32;//���������

	//��̹����ص�
private:
	//̹�˵ĳߴ��С(����)
	SIZE tank_size = SIZE{ 26, 26 };

	//̹�˵�λ������(�߿�)
	POINT tank_location_tit = POINT{ 0, 0 };

	//̹�˵�λ������(����)
	POINTF tank_location_dlg =POINTF{ tank_location_tit.x*this_grid_width + tank_size.cx/2, tank_location_tit.y *this_grid_height+tank_size.cy/2 };
	
	//̹��
	SelfTank this_self_tank;
	//��ؼ���صĳ�Ա����
private:
	CMenu this_menu;
	int this_cur_menu=0;

	//��·����ص�
private:
	POINT this_point1;//���
	POINT this_point2;//�յ�
	std::vector<POINT> this_for_path;
	std::vector<POINT> this_cur_path;

public:
	
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};