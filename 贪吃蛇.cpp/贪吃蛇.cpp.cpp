#include <stdafx.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

using namespace std;

const int N=21;      //NΪ�������ƶ��������εı߳�

void Get_xy(int x,int y)   //��λ���λ��
{
	HANDLE hout;//handle���������Ϊ������Դ��ϵͳ�ڲ���һ����ż��ٸ����Լ��ڴ����.
	COORD pos;  //��pos��ʾ�ڿ���̨����ʾ����
	pos.X=x*2;
	pos.Y=y;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);// STD_OUTPUT_HANDLE Ҳ����ָ���˱�׼����豸
	SetConsoleCursorPosition(hout,pos);//�����˷�����X,Y��ַ
}

void Color(int num)   //������ɫ
{
	HANDLE hout;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout,num);
}

void Initial()   //��ʼ��
{
	int i,j;
	int wall[N+2][N+2]={{0}};
	for(i=1;i<=N;i++)//�������鹹����ƽ̨
		for(j=1;j<=N;j++)
			wall[i][j]=1;
	Color(11);
	for(i=0;i<N+2;i++)
	{
		for(j=0;j<N+2;j++)
		{
			if(wall[i][j])//����ƽ̨Ϊ��ɫ����
				cout<<"��";
			else cout<<"��";//�߽�Ϊ�հ׷���
		}
		cout<<endl;
	}
	Get_xy(N+3,1);
	Color(20);
	cout<<"��'W','S','A','D'���в���"<<endl;
	Get_xy(N+3,2);
	Color(20);
	cout<<"���������ͣ"<<endl;
	Get_xy(N+3,3);
	Color(20);
	cout<<"�÷֣�"<<endl;//���ÿ���̨�Ҳ�Ϊ��ʾ��÷���ʾ��
}

void game()
{
	int** snake=NULL;   //snakeΪ�洢�����ÿһ���λ�õĶ�ά����
	int len=1;
	int i;
	int score=0;
	int apple[2];
	int tail[2];
	char ch='p';

	Initial();//�ȳ�ʼ�����ƽ̨

	//���һ�������ʳ��λ��
	srand((unsigned)time(NULL));//��ΪsrandΪ�޷����ι���Ҫ��õ�time����ǿ��ת�����޷����βŲ�����ʾ
	apple[0]=rand()%N+1;//��һ��Ϊ�����Ժͱ߽��غ�
	apple[1]=rand()%N+1;

	Get_xy(apple[0],apple[1]);
	Color(12);
	cout<<"��"<<endl;

	//��snake��������ڴ�ռ�
	snake=(int**)realloc(snake,sizeof(int*)*len);//��̬�ڴ������ͨ��realloc����snake�Ŀռ䣬�����µĵ�ַ��ֵ��snake
	for(i=0;i<len;i++)
	{
		snake[i]=(int*)malloc(sizeof(int)*2);//ʹ�ö�̬�ڴ��������ָ��һ������������Ҫ�Ĵ�С
	}
	//��ʼ��������ҳ�����м�
	snake[0][0]=N/2;
	snake[0][1]=N/2+1;
	Get_xy(snake[0][0],snake[0][1]); //10��11
	Color(14);
	cout<<"��"<<endl;

	int flag=1;   //

	while(1)
	{
		//ÿ�ƶ�һ�Σ��Ͱ��ϴε�β�ͻ�ԭΪ����ɫ
		if(flag)
		{
		tail[0]=snake[len-1][0];//�Ӻ���ǰ������Ϊ��ǰ�������Ļ�����ֲ��������
        tail[1]=snake[len-1][1];
        Get_xy(tail[0],tail[1]);
        Color(11);
        cout<<"��"<<endl;//��ԭ
		}

		flag=1;
		for(i=len-1;i>0;i--)//ʹ�߻��ʳ������ӵĳ���
		{
			snake[i][0]=snake[i-1][0];
			snake[i][1]=snake[i-1][1];
			Get_xy(snake[i][0],snake[i][1]);
			Color(14);
			cout<<"��"<<endl;
		}
		/*====================================================================
		��������kbhit()��VC++6.0��Ϊ_kbhit()��
		�� �ܼ�����ֵ�� ��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
		�� ����int kbhit(void);
		����ͷ�ļ��� include <conio.h>
		=====================================================================*/
		if(kbhit())
		{
			Get_xy(0,N+3);
			ch=getche();
		}
		switch(ch)
		{
		case 'W':
		case 'w': snake[0][1]--; break;//X,Y�ֱ��Ӧ���������
		case 'S':
		case 's': snake[0][1]++; break;
		case 'A':
		case 'a': snake[0][0]--; break;
		case 'D':
		case 'd': snake[0][0]++; break;
		default :break;
		}

		for(i=1;i<len;i++)
		{
			//��ҧ��������Ϸ������
			if(snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1])
			{
				Get_xy(N/2,N/2);
				Color(30);
				cout<<"Game over!"<<endl;
				exit(0);
			}
		}

		Get_xy(snake[0][0],snake[0][1]);
		Color(14);
		cout<<"��"<<endl;

		/*==================================================================
		������: sleep
		�� ��: ִ�й���һ��ʱ��
		�� ��: unsigned sleep(unsigned milliseconds);
		��VC��ʹ�ô���ͷ�ļ�
		#include <windows.h>
		��gcc�������У�ʹ�õ�ͷ�ļ���gcc�汾�Ĳ�ͬ����ͬ
		#include <unistd.h>
		===================================================================*/
		//����Խ�ߣ��ߵ��ƶ��ٶ�Խ��
		Sleep(abs(200-0.5*score));

		//�߳Ե�ʳ��
		if(snake[0][0]==apple[0] && snake[0][1]==apple[1])
		{
			flag=0;
			score++;
			len++;
			srand((unsigned)time(NULL));
			snake=(int**)realloc(snake,sizeof(int*)*len);
			snake[len-1]=(int*)malloc(sizeof(int)*2);
			Get_xy(N+6,3);
			Color(20);
			cout<<score<<endl;
			apple[0]=rand()%N+1;
			apple[1]=rand()%N+1;
			Get_xy(apple[0],apple[1]);
			Color(12);
			cout<<"��"<<endl;
		}
		//��ͷײǽ�ˣ���Ϸ������
		if(snake[0][0]==0 || snake[0][0]==N || snake[0][1]==0 || snake[0][1]==N)
		{
			Get_xy(N/2,N/2);
			Color(30);
			cout<<"Game Over!"<<endl;
			for(i=0;i<len;i++)
				free(snake[i]);//�ͷŵ�snake�Ķ�̬�ڴ����
			Sleep(INFINITE);
			exit(0);
		}
		//��Ϸͨ�أ�
		if(len>=N*N/20)
		{
			Get_xy(N/2,N/2);
			Color(30);
			cout<<"Win!"<<endl;
			for(i=0;i<len;i++)
				free(snake[i]);
			Sleep(INFINITE);
			exit(0);
		}
	}

}
int main()
{
	game();
	return 0;
}


