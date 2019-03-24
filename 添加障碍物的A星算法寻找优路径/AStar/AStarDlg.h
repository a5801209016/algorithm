
// AStarDlg.h : ͷ�ļ�
//

#pragma once


// CAStarDlg �Ի���
class CAStarDlg : public CDialogEx
{
// ����
public:
	CAStarDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ASTAR_DIALOG };

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
	POINT GetXY(POINT titlep);
	POINT GetTitle(POINT xy);
	
	void ClearPath();
	void InitPoints();
	bool SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost);

	//��ȡһ�������CDC
	void GetMemCDC(CWnd* wnd, CDC* memdc);

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	void CopyShows(CWnd* wnd, CDC* memdc);

//��·����صĳ�Ա����
private:
	char this_map[20][15];
	std::vector<POINT> this_for_path;
	std::vector<POINT> this_cur_path;

	void ClearMap();
	//��ؼ���صĳ�Ա����
private:
	CMenu this_menu;
	int this_cur_menu=0;

private:
	POINT this_point1;//���
	POINT this_point2;//�յ�

public:
	
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
