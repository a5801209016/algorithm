
// drawDlg.h : ͷ�ļ�
//

#pragma once


// CdrawDlg �Ի���
class CdrawDlg : public CDialogEx
{
// ����
public:
	CdrawDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	//��ȡһ�������CDC
	void GetMemCDC(CWnd* wnd, CDC* memdc);

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	void CopyShows(CWnd* wnd, CDC* memdc);

private:
	POINT this_point;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
