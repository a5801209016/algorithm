
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once
struct COLOR
{
	COLOR(int x, int y, int z)
	{
		r = x;
		g = y;
		b = z;
	}

	int r;
	int g;
	int b;
}; 

class DOT//��
{
public:
	DOT()
	{
		m_x = 0;
		m_y = 0;
	}
	DOT(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	~DOT()
	{

	}

	int X()
	{
		return m_x;
	}

	int Y()
	{
		return m_y;
	}

	DOT& operator = (DOT &a)
	{
		m_x = a.X();
		m_y = a.Y();
		return *this;
	}

	DOT& operator + (const DOT &a)
	{
		DOT r(m_x + a.m_x, m_y + a.m_y);
		return r;
	}

	DOT& operator () (const int &x, const int& y)
	{
		m_x = x;
		m_y = y;
	}

	bool operator == ( DOT &a)
	{
		if (m_x == a.X() && m_y == a.Y())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

protected:
	int m_x;
	int m_y;
};

//����
class AXES
{
public:
	AXES()
	{
		min = DOT(0,0);
		max = DOT(0,0);
		mid = 0;
		length = 0.0;
		k = 0.0;
	}
	AXES(DOT l, DOT r, int md, int b)
	{
		min = l;
		max = r;
		mid = md;
		mbe = b;
		length = pow(pow(max.X() - min.X(), 2) + pow(max.Y() - min.Y(), 2), 0.5);
		k = atan2((max.Y() - min.Y()),(max.X() - min.X()));
	}
	void SetValue(DOT l, DOT r, int md, int b)
	{
		min = l;
		max = r;
		mid = md;
		mbe = b;
		length = pow(pow(max.X() - min.X(), 2) + pow(max.Y() - min.Y(), 2), 0.5);
		k = atan2((max.Y() - min.Y()), (max.X() - min.X()));
	}
public:
	void OnPaint( CClientDC* dc)
	{
		POINT p1;
		p1.x = GetXY(min).X();
		p1.y = GetXY(min).Y();

		POINT p2;
		p2.x = GetXY(max).X();
		p2.y = GetXY(max).Y();

		//������
		CPen* newpen = new CPen(PS_SOLID, 1, RGB(255,0,0));
		CPen* oldpen = dc->GetCurrentPen();
		dc->SelectObject(newpen);
		dc->MoveTo(p1);
		dc->LineTo(p2);

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
		for (int dis = 0; dis <= length; dis += mid)
		{
			//��
			char buff[128] = { 0 };
			sprintf(buff, "%d", mbe + dis);
			DOT point = DOT(min.X() + dis*cos(k), min.Y() + dis*sin(k));
			DOT windp = GetXY(point);
			//��
			RECT rt;
			rt.left = windp.X() - 2;
			rt.right = windp.X() + 2;
			rt.top = windp.Y()-2;
			rt.bottom = windp.Y() + 2;
			CBrush* oldbrush = dc->GetCurrentBrush();
			CBrush newbrush(RGB(255, 0, 0));
			dc->SelectObject(&newbrush);
			dc->Ellipse(&rt);
			dc->SelectObject(&oldbrush);
			dc->TextOut(windp.X(), windp.Y(), CString(buff));
		}

	

		dc->SelectObject(oldpen);
		delete newpen;
		newpen = NULL;
	}
protected:
	DOT min;//һ�����������С����
	DOT max;//һ�����������󲿷�
	int mid;//һ��������ļ����С
	int mbe;//�����min��X����Y��
	//(x-min.X())/(max.X()-min.X()) = (y-min.Y())/(max.Y()-min.Y())

	double length;
	double k;//�Ƕ�
protected:
	//���е�����ת��Ϊ��������
	DOT GetXY(DOT d2)
	{
		DOT d(d2.X() + 500, 300 - d2.Y());
		return d;
	}
};

class MAP
{
public:
	MAP(int mix, int miy, int max, int may)
	{
		m_mix = mix;
		m_miy = miy;
		m_max = max;
		m_may = may;
		sizex = max - mix + 1;
		sizey = may - miy + 1;

		//��ά����Ŀռ���䷽ʽ
		m_map = (char **)malloc(sizeof(char*)*sizey);       //arr��������Կ��������飬�����ÿ����Ա����ָ��int���͵�ָ�룬����ÿ��ָ��ָ��Ĵ���һ�У���row��   
		for (int i = 0; i<sizey; i++)            //Ϊÿ������ռ�
		{
			m_map[i] = (char*)malloc(sizeof(char)*sizex);       //ÿһ����col��
		}
	}

	~MAP()
	{
		//��ά����Ŀռ��ͷŷ�ʽ
		for (int i = 0; i<sizey; i++)            //Ϊÿ������ռ�
		{
			delete[] m_map[i];       //ÿһ����col��
			m_map[i] = NULL;
		}
		delete[] m_map;
		m_map = NULL;
	}

	char& Node(int x, int y)
	{
		return m_map[x - m_mix][y - m_miy];
	}

protected:
	int m_mix;
	int m_miy;
	int m_max;
	int m_may;
	int sizex;
	int sizey;
	char **m_map;
};



// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CMFCApplication1Dlg()
	{
		delete m_map;
		m_map = NULL;
	}
// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	MAP* m_map;
	AXES m_x;
	AXES m_y;
	std::vector<DOT> m_path; 
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	//���е�����ת��Ϊ��������
	DOT GetXY(DOT d2)
	{
		DOT d(d2.X() + 500, 300 - d2.Y());
		return d;
	}
	void DrawPath()
	{
		int size = 0;
		/*for (int i=-500;i<=500;++i)
		{
			for (int j=-300;j<=300;++j)
			{
				float r = float(i*i) / float(100 * 100) + float(j*j) / float(200 * 200);
				double d = 2.0 / (100.0*100.0) + 2.0 / (200.0*200.0);
				if (r <= 1.0 + d&&r >= 1.0 - d)
				{
					m_map->Node(i,j) = 1;
					m_path.push_back(DOT(i, j));
					++size;
				}
			}
		}*/

		for (float i = -4; i <= 4; i+=0.01)
		{
			for (float j = -5; j <= 5; j+=0.01)
			{
				float r = i*i+j;
				if (r <= 1.0 + 0.01&&r >= 1.0 - 0.01)
				{
					//m_map->Node(i, j) = 1;
					m_path.push_back(DOT(i*80, j*80));//�Ŵ���ٱ�����ʾ
					++size;
				}
			}
		}
		for (int i = 0; i < m_path.size() - 1; i++)
		{
			for (int j = 0; j < m_path.size() - 1 - i; j++)
			{
				float anglej = atan2(m_path[j].Y(), m_path[j].X());
				float anglej1 = atan2(m_path[j+1].Y(), m_path[j+1].X());
				if (anglej>anglej1)
				{
					DOT temp = m_path[j];
					m_path[j] = m_path[j + 1];
					m_path[j + 1] = temp;
				}
			}
		}
		std::vector<DOT>::iterator preit = m_path.begin();
		for (std::vector<DOT>::iterator it = m_path.begin()+1; it != m_path.end(); ++it)
		{
			DOT pe = *preit;
			DOT cu = *it;
			float dis = pow(pow(cu.X()-pe.X(),2)+pow(cu.Y()-pe.Y(),2), 0.5);
			if (dis<20.0)
			{
				DrawLine(*preit, *it, COLOR(255, 0, 0));
			}
			
			preit = it;
		}
	}
	//��һ����
	void DrawLine(DOT d1, DOT d2, COLOR c)
	{
		DOT dd1 = GetXY(d1);
		DOT dd2 = GetXY(d2);
		POINT p1,p2;
		p1.x = dd1.X();
		p1.y = dd1.Y();
		p2.x = dd2.X();
		p2.y = dd2.Y();

		CClientDC dc(this);
		CPen* newpen = new CPen(PS_SOLID, 1, RGB(c.r, c.g, c.b));
		CPen* oldpen = dc.GetCurrentPen();
		dc.SelectObject(newpen);
		dc.MoveTo(p1);
		dc.LineTo(p2);
		dc.SelectObject(oldpen);
		delete newpen;
		newpen = NULL;
	}

	//���ô��屳����ɫ
	void SetBkColor(COLOR c)
	{
		CPaintDC dc(this); // device context for painting
		CRect rect;
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(c.r, c.g, c.b));
	}

	bool HaseDOT(std::vector<DOT> vec, DOT d)
	{
		bool result = false;
		for (std::vector<DOT>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			if ((*it)== d)
			{
				return true;
			}
		}
		 return false;
	}

	void FindPath(DOT orginal)
	{
		std::list<DOT> list_dot;
		m_path.push_back(orginal);
		for (int i = 1; i <= 8; ++i)
		{
			list_dot = FindNodes(m_path.back(), i);

			//ɾ�����еĽڵ�
			for (std::list<DOT>::iterator it = list_dot.begin(); it != list_dot.end(); ++it)
			{
				if (HaseDOT(m_path, *it))
				{
					it = list_dot.erase(it);
				}
			}
			if (!list_dot.empty())
			{
				break;
			}
			else
			{
				return;
			}
		}
		
		FindPath(*list_dot.begin());
	}

	//����centerΪ���ģ�����Ϊ2r����������Ѱ�ҷ���Ҫ��Ľڵ�
	std::list<DOT> FindNodes(DOT center, int r)
	{
		std::list<DOT> vec_dot;
		DOT lef_top(center.X() - r, center.Y() + r);
		DOT right_top(center.X() + r, center.Y() + r);
		DOT lef_bottom(center.X() - r, center.Y() - r);
		DOT right_bottom(center.X() + r, center.Y() - r);
		for (int i = lef_top.X(); i <= right_top.X();++i)
		{
			//center.Y()+r
			//std::vector<DOT>::iterator it = std::find(m_path.begin(), m_path.end(), DOT(i, center.Y() + r));
			if (m_map->Node(i, center.Y() + r))
			{
				vec_dot.push_back(DOT(i, center.Y() + r));
			}
		}
		for (int i = lef_bottom.X(); i <= right_bottom.X(); ++i)
		{
			//center.Y()-r
			//std::vector<DOT>::iterator it = std::find(m_path.begin(), m_path.end(), DOT(i, center.Y() - r));
			if (m_map->Node(i, center.Y() - r))
			{
				vec_dot.push_back(DOT(i, center.Y() - r));
			}
		}
		for (int i = lef_bottom.Y(); i <= lef_top.Y(); ++i)
		{
			//center.X()-r
			//std::vector<DOT>::iterator it = std::find(m_path.begin(), m_path.end(), DOT(center.X() - r, i));
			if (m_map->Node(center.X() - r, i))
			{
				vec_dot.push_back(DOT(center.X() - r, i));
			}
		}
		for (int i = right_bottom.Y(); i <= right_top.Y(); ++i)
		{
			//center.X()+r
			//std::vector<DOT>::iterator it = std::find(m_path.begin(), m_path.end(), DOT(center.X() + r, i));
			if (m_map->Node(center.X() + r, i))
			{
				vec_dot.push_back(DOT(center.X() + r, i));
			}
		}
		return vec_dot;
	}
};
