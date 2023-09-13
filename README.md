# C语言实现贪吃蛇

思路：

- 数据初始化，引入画布值，边框为-1，空白为0，蛇头为1，蛇身大于1，食物为-2；输入的方向，用1234表示，食物的位置，标记边框、蛇头蛇身画布值
- 遍历画布值，输出对应内容
- 与输入有关的刷新
- 蛇位置的刷新
  - 扫描找到所有正数，即为蛇，加1
  - 在正数基础上遍历找到最大，即为蛇尾，设置为0即为空白
  - 找到值为2的，即为蛇头，同时将蛇尾蛇头都标记
  - 根据移动方向，将新蛇头移动
  - 判断，若吃到食物，随机产生新食物，否则将蛇尾设为空白
  - 判断小蛇和自身或者墙壁相撞，游戏失败
  - 同时，将新蛇头设置为1

代码：

```
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 30  
#define Width 50

//全局变量
int move;
int food_x,food_y;
int x,y;
int canvas[High][Width]={0};

void gotoxy(int x,int y) 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void moveF()
{
	int i,j,tail_x,tail_y,head_x,head_y,new_x,new_y;
	int max=0;
	for(i=1;i<High-1;i++)//找到蛇，全加1
	{
		for(j=1;j<Width-1;j++)
		{
			if(canvas[i][j]>0)
				canvas[i][j]++;
		}
	}
	for(i=1;i<High-1;i++)//标记蛇头蛇尾
	{
		for(j=1;j<Width-1;j++)
		{
			if(max<canvas[i][j])
			{
				max=canvas[i][j];
				tail_x=i;
				tail_y=j;
			}
			if(canvas[i][j]==2)
			{
				head_x=i;
				head_y=j;
			}
		}
	}
	if(move==1)//根据移动方向，将新蛇头移动
	{
		new_x=head_x-1;
		new_y=head_y;
	}
	if(move==2)
	{
		new_x=head_x+1;
		new_y=head_y;
	}
	if(move==3)
	{
		new_x=head_x;
		new_y=head_y-1;
	}
	if(move==4)
	{
		new_x=head_x;
		new_y=head_y+1;
	}
	
	if(canvas[new_x][new_y]==-2)//新蛇头吃到食物
	{
		canvas[food_x][food_y]=0;
		food_x = rand()%(High-5) + 2;
		food_y = rand()%(Width-5) + 2;
		canvas[food_x][food_y] = -2;
	}
	else canvas[tail_x][tail_y]=0;
	if((canvas[new_x][new_y]>0)||(canvas[new_x][new_y]==-1))
	{
		printf("游戏失败\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	else canvas[new_x][new_y]=1;
}

void startup()
{
	int i,j;
	x=High/2;
	y=Width/2;
	
	
	for(i=0;i<High;i++)
	{
		canvas[i][0]=-1;
		canvas[i][Width-1]=-1;
	}
	for(j=0;j<Width;j++)
	{
		canvas[0][j]=-1;
		canvas[High-1][j]=-1;
	}
	canvas[x][y]=1;
	for (i=1;i<=4;i++)
		canvas[x][y-i] = i+1;
	move=4;
	
	food_x=rand()%(High-5)+2;
	food_y=rand()%(Width-5)+2;
	canvas[food_x][food_y] = -2;
}

void show()
{
	gotoxy(0,0);  // 光标移动到原点位置，以下重画清屏
	int i,j;
	for(i=0;i<High;i++)//遍历输出内容
	{		
		for(j=0;j<Width;j++)
		{
			if(canvas[i][j]==0)//空白
				printf(" ");
			else if(canvas[i][j]==-1)//边框
				printf("#");
			else if(canvas[i][j]==1)//蛇头
				printf("@");
			else if(canvas[i][j]>1)//蛇身
				printf("*");
			else if(canvas[i][j]==-2)//食物 
				printf("F");
			
		}
        printf("\n");
	}
	Sleep(100);
}

void updateWithoutInput() 
{
	moveF();
}

void updateWithInput()
{
	int input;
	if(kbhit())
	{
		input=getch();
		if(input=='w')
		{
			move=1;
			moveF();			
		}
		else if(input=='s')
		{
			move=2;
			moveF();			
		}
		else if(input=='a')
		{
			move=3;
			moveF();			
		}
		else if(input=='d')
		{
			move=4;
			moveF();		
		}
	}
}

int main()
{
	startup();
	while(1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	return 0;
}
```

