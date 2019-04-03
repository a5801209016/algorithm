
char buff[15][15] = 
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//4
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//5
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//6
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//7
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//8
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//9
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//10
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//11
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//12
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//13
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//14
};

bool WhoWin(int who)
{
   //����
   int col = 15;
   int row = 15;

   //ÿһ�е�����
   char c_old_step='0';
   int c_cout=1;

   //ÿһ�е�����
   char r_old_step='0';
   int r_cout=1;

   for(int i=0;i<row;++i)
   {
		for(int j=0;j<col;++j)
	   {
			//���ÿһ��
		   if(buff[i][j]==c_old_step&&buff[i][j]==who)
		   {
				++c_cout;
		   }
		   else
		   {
				c_old_step = buff[i][j];
				c_cout = 1;
		   }
		   if(c_cout>=5)
		   {
				return true;
		   }

		   //���ÿһ��
		   if(buff[j][i]==r_old_step&&buff[j][i]==who)
		   {
				++r_cout;
		   }
		   else
		   {
				r_old_step = buff[j][i];
				r_cout = 1;
		   }
		   if(r_cout>=5)
		   {
				return true;
		   }
	   }
   }


   //ֱ�߷���i= j+b�������ǳ�ʼ������
   char plus_bottom_old_step='0';
   int  plus_bottom_cout=1;

   //ֱ�߷���i= j+b�������ǳ�ʼ������
   char plus_top_old_step='0';
   int  plus_top_cout=1;
    
   /*Ҫ��*/
   //ֱ�߷���i= j+b��iΪ���ᣬjΪ���ᣩ
   for(int b=5-1;b<15;++b)
   {
		for(int c=0;c<15-b;++c)
		{
		   //���������
		   if(buff[b+c][c]==plus_bottom_old_step&&buff[b+c][c]==who)
		   {
				++plus_bottom_cout;
		   }
		   else
		   {
				plus_bottom_old_step = buff[b+c][c];
				plus_bottom_cout = 1;
		   }
		   if(plus_bottom_cout>=5)
		   {
				return true;
		   }
		   
		   //���������
		   if(buff[c][b+c]==plus_top_old_step&&buff[c][b+c]==who)
		   {
				++plus_top_cout;
		   }
		   else
		   {
				plus_top_old_step = buff[c][b+c];
				plus_top_cout = 1;
		   }
		   if(plus_top_cout>=5)
		   {
				return true;
		   }
		}
   }

   //ֱ�߷���j+i=k�������ǳ�ʼ������
   char minu_bottom_old_step='0';
   int  minu_bottom_cout=1;

   //ֱ�߷���j+i=b�������ǳ�ʼ������
   char minu_top_old_step='0';
   int  minu_top_cout=1;
    
   //ֱ�߷���j+i=k��iΪ���ᣬjΪ���ᣩ
   for(int k=4;k<15;++k)
   {
		for(int e=0;e<=k;++e)
		{
		   //���������
		   if(buff[k-e][e]==minu_bottom_old_step&&buff[k-e][e]==who)
		   {
				++minu_bottom_cout;
		   }
		   else
		   {
				minu_bottom_old_step = buff[k-e][e];
				minu_bottom_cout = 1;
		   }
		   if(minu_bottom_cout>=5)
		   {
				return true;
		   }
		   
		   //���������
		   if(buff[14-e][14-k+e]==minu_top_old_step&&buff[14-e][14-k+e]==who)
		   {
				++minu_top_cout;
		   }
		   else
		   {
				minu_top_old_step = buff[14-e][14-k+e];
				minu_top_cout = 1;
		   }
		   if(minu_top_cout>=5)
		   {
				return true;
		   }
		}
   }
   
   return false;
}

