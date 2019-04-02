#include <stdio.h>

char buff[15][15] = 
{
	2,1,1,1,1,1,1,1,1,1,2,1,1,1,1,//0
	2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,//1
	2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//2
	2,1,2,1,2,2,2,1,1,2,1,2,2,2,1,//3
	1,1,2,1,1,1,1,1,1,1,2,2,2,1,2,//4
	1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,//5
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//6
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//7
	2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//8
	1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,//9
	1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,//10
	1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,//11
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,//12
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,//13
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//14
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
    
   //ֱ�߷���i= j+b��iΪ���ᣬjΪ���ᣩ
   for(int b=0;b<=15-5;++b)
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


   //ֱ�߷���j= i+b�������ǳ�ʼ������
   char minu_bottom_old_step='0';
   int  minu_bottom_cout=1;

   //ֱ�߷���i= j+b�������ǳ�ʼ������
   char plus_top_old_step='0';
   int  plus_top_cout=1;
    
   //ֱ�߷���i= j+b��iΪ���ᣬjΪ���ᣩ
   for(int b=0;b<=15-5;++b)
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
   
   return false;
}

void main()
{
	bool r = WhoWin(2);
	printf("%d\n",r);
}