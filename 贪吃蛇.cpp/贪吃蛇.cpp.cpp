#include <stdafx.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

using namespace std;

const int N=21;      //N为蛇所能移动的正方形的边长

void Get_xy(int x,int y)   //定位光标位置
{
	HANDLE hout;//handle句柄类可理解为申请资源在系统内部的一个编号减少复制以及内存管理.
	COORD pos;  //用pos表示在控制台上显示坐标
	pos.X=x*2;
	pos.Y=y;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);// STD_OUTPUT_HANDLE 也就是指向了标准输出设备
	SetConsoleCursorPosition(hout,pos);//定义了方向与X,Y地址
}

void Color(int num)   //设置颜色
{
	HANDLE hout;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout,num);
}

void Initial()   //初始化
{
	int i,j;
	int wall[N+2][N+2]={{0}};
	for(i=1;i<=N;i++)//两层数组构成了平台
		for(j=1;j<=N;j++)
			wall[i][j]=1;
	Color(11);
	for(i=0;i<N+2;i++)
	{
		for(j=0;j<N+2;j++)
		{
			if(wall[i][j])//定义平台为红色方块
				cout<<"■";
			else cout<<"□";//边界为空白方块
		}
		cout<<endl;
	}
	Get_xy(N+3,1);
	Color(20);
	cout<<"按'W','S','A','D'进行操作"<<endl;
	Get_xy(N+3,2);
	Color(20);
	cout<<"按任意键暂停"<<endl;
	Get_xy(N+3,3);
	Color(20);
	cout<<"得分："<<endl;//设置控制台右侧为提示与得分显示处
}

void game()
{
	int** snake=NULL;   //snake为存储蛇身的每一点的位置的二维数组
	int len=1;
	int i;
	int score=0;
	int apple[2];
	int tail[2];
	char ch='p';

	Initial();//先初始化获得平台

	//获得一个随机的食物位置
	srand((unsigned)time(NULL));//因为srand为无符整形故需要获得的time函数强制转换成无符整形才不会提示
	apple[0]=rand()%N+1;//加一因为不可以和边界重合
	apple[1]=rand()%N+1;

	Get_xy(apple[0],apple[1]);
	Color(12);
	cout<<"●"<<endl;

	//给snake数组分配内存空间
	snake=(int**)realloc(snake,sizeof(int*)*len);//动态内存调整，通过realloc扩大snake的空间，并把新的地址赋值给snake
	for(i=0;i<len;i++)
	{
		snake[i]=(int*)malloc(sizeof(int)*2);//使用动态内存分配用于指明一个整型数据需要的大小
	}
	//开始将蛇置于页面正中间
	snake[0][0]=N/2;
	snake[0][1]=N/2+1;
	Get_xy(snake[0][0],snake[0][1]); //10，11
	Color(14);
	cout<<"⊙"<<endl;

	int flag=1;   //

	while(1)
	{
		//每移动一次，就把上次的尾巴还原为背景色
		if(flag)
		{
		tail[0]=snake[len-1][0];//从后向前遍历因为从前向后遍历的话会出现不动的情况
        tail[1]=snake[len-1][1];
        Get_xy(tail[0],tail[1]);
        Color(11);
        cout<<"■"<<endl;//还原
		}

		flag=1;
		for(i=len-1;i>0;i--)//使蛇获得食物后增加的长度
		{
			snake[i][0]=snake[i-1][0];
			snake[i][1]=snake[i-1][1];
			Get_xy(snake[i][0],snake[i][1]);
			Color(14);
			cout<<"★"<<endl;
		}
		/*====================================================================
		函数名：kbhit()（VC++6.0下为_kbhit()）
		功 能及返回值： 检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
		用 法：int kbhit(void);
		包含头文件： include <conio.h>
		=====================================================================*/
		if(kbhit())
		{
			Get_xy(0,N+3);
			ch=getche();
		}
		switch(ch)
		{
		case 'W':
		case 'w': snake[0][1]--; break;//X,Y分别对应纵轴与横轴
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
			//蛇咬到蛇身，游戏结束！
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
		cout<<"⊙"<<endl;

		/*==================================================================
		函数名: sleep
		功 能: 执行挂起一段时间
		用 法: unsigned sleep(unsigned milliseconds);
		在VC中使用带上头文件
		#include <windows.h>
		在gcc编译器中，使用的头文件因gcc版本的不同而不同
		#include <unistd.h>
		===================================================================*/
		//分数越高，蛇的移动速度越快
		Sleep(abs(200-0.5*score));

		//蛇吃到食物
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
			cout<<"●"<<endl;
		}
		//蛇头撞墙了，游戏结束！
		if(snake[0][0]==0 || snake[0][0]==N || snake[0][1]==0 || snake[0][1]==N)
		{
			Get_xy(N/2,N/2);
			Color(30);
			cout<<"Game Over!"<<endl;
			for(i=0;i<len;i++)
				free(snake[i]);//释放掉snake的动态内存分配
			Sleep(INFINITE);
			exit(0);
		}
		//游戏通关！
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


