
// DrawDlg.h : ͷ�ļ�
//

#pragma once


// CDrawDlg �Ի���
class CDrawDlg : public CDialogEx
{
// ����
public:
	CDrawDlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	//ˢbmp��ͼƬ
	void ShowBitmap(UINT ID, CDC* dc, POINT locate, SIZE si);

	//ˢpng��ͼƬ,rgbΪ���Ե���ɫ
	void ShowImage(LPCTSTR filepath, CDC* dc, POINT locate, SIZE si, UINT rgb);
};
