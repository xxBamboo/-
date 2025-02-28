#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <conio.h>
using namespace std;

class puzzle{
private:
	int n[9] = {0,1,2,3,4,5,6,7,8};
	PIMAGE m[9];
	char fileName[20];
public:
	int i,j,p;
	void how()//游戏说明；
	{
		setcolor(BLACK);
		setbkcolor(LIGHTYELLOW);
		setfont(35,0,"Cooper Black");
		char s1[] = "Please press 'w' 'a' 's' 'd' to make the picture move in the direction of '↑' '←' '↓' '→'.";
		char s2[] = "Press any key to start.(‵▽′)/";
		outtextrect(80,160,440,200,s1);
		outtextxy(80,400,s2);
		getch();
		cleardevice();
	}
	void get_swap (int &a, int &b)
	{
		int t = b;
		b = a;
		a = t;
	}
	void in()
	{
		srand((unsigned)time(0));
		for (i = 8; i >=0 ; i--)//产生随机数组n[]；
		{
			j= rand()%(i+1);
			get_swap(n[i],n[j]);
		}
	}
	void out()//铺图；
	{
		cleardevice();
		for (i = 0; i < 9; i++)//图片标号对应；
		{
			sprintf (fileName, "grid_%d.png", n[i]);
			if(n[i] == 0){p = i;}     //记录0的位置；
			m[i] = newimage();
			getimage (m[i], fileName);
		}
		for (int i = 0; i < 9; i++)
		{
			int x = i % 3 * 200;
			int y = i / 3 * 200;
			putimage (x, y, m[i]);
		}
	}
	int value()//求逆序数；
	{
		int m = 0;
		for(i = 8; i >= 0; i--)
		{
			if(n[i] == 0)
				continue;
			for(j = i - 1; j >= 0; j--)
			{
				if(n[j] == 0)
				{
					continue;
				}
				if(n[i] < n[j])
				{
					m++;
				}
			}
		}
		return m;
	}
	void get_move()//移动；
	{
		char k;
		k = getch();
		int q = p % 3, r = p/3;
		if(k == 'd' && q != 0){
			get_swap(n[p],n[p-1]);
		}
		if(k == 'w' && r != 2){
			get_swap(n[p],n[p+3]);
		}
		if(k == 'a' && q != 2){
			get_swap(n[p],n[p+1]);
		}if(k == 's' && r != 0){
			get_swap(n[p],n[p-3]);
		}
	}
	bool isFinish()//判断结束；
	{
		if(value() == 0 && n[8] == 0)
			return true;
		else
			return false;
	}
	void over()
	{
		cleardevice();
		char s3[] = "Congratulation!";
		outtextxy(170,280,s3);
		getch();
	}
};
int main()
{
	initgraph(600, 600, 0);
	setcaption("拼图游戏");
	puzzle a;
	a.how();
	int t;
	do{
		a.in();
		t = a.value()%2;
	}while(t != 0);
	a.out();
	while(a.isFinish() == false){
		a.get_move();
		a.out();
	}
	a.over();
	return 0;
}
