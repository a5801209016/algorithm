
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
	DECLARE_MESSAGE_MAP()
	
	
protected:
	POINT GetXY(POINT titlep);
	
	void ClearPath();
	bool SeekPath(POINT titleOr, POINT titlePr, POINT titleEn, int allcost);
private:
	char this_map[20][15];
	std::vector<POINT> this_for_path;
	std::vector<POINT> this_cur_path;
};
