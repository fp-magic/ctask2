#include "acllib.h"
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<math.h>
#include<time.h>
#include<windows.h>
int s,m,h,t,mx,my,l,lalarm,alarmnum,state;
int alarm[20];
char ch[200];
const double pi=3.1415926;
void view()
{
	setPenWidth(10);
	setPenColor(BLACK);
	//setPenStyle(PEN_STYLE_DASH);
	setBrushColor(GREEN);
	setBrushStyle(BRUSH_STYLE_SOLID);
	setTextColor(BLACK);
	setTextSize(22);
	//setTextBkColor(RGB(50,30,10)); 
}

void time1(int id)//main painting
{
	s++;if(s==60){m++;s=0;}if(m==60){h++;m=0;}if(h==12)h=0;//printf("%d:%d:%d\n",h,m,s);
	if(state==1)Beep(4000,600);
	beginPaint();
	clearDevice();
	setPenWidth(5);line(mx,my,mx+l*sin(2*pi*s/60),my-l*cos(2*pi*s/60));
	setPenWidth(8);line(mx,my,mx+l*sin(2*pi*m/60),my-l*cos(2*pi*m/60));
	setPenWidth(10);line(mx,my,mx+l*sin(2*pi*h/12)*2/3,my-l*cos(2*pi*h/12)*2/3);
	endPaint();
	int i;printf("%d\n",alarmnum);
	for(i=1;i<=alarmnum;i++)
	{
		//printf("alarm %d : %d seconds left\n",p[i],alarm[i]);
		sprintf(ch,"alarm:     %d seconds left",alarm[i]);
		beginPaint();
		paintText(50,370+30*i,ch);
		endPaint();
		alarm[i]--;
	}
	if(alarmnum>=1&&alarm[1]==0)ring(); 
}
void ring()
{
	state=1;
	int i;
	for(i=2;i<=alarmnum;i++)
	{
		alarm[i-1]=alarm[i];	
	}
	alarm[alarmnum]=0;
	alarmnum--;
}
void mouse1(int x,int y,int button,int event)
{
	if(state==1)state=0;
}

void key1(int key,int event)
{
	if(key>=48&&key<=57&&event==1)
	{
		alarm[alarmnum+1]=alarm[alarmnum+1]*10+key-48;
	}//printf("%d:%d\n",alarmnum,alarm[alarmnum+1]);
	if((key==13||key==32)&&event==1)
	{
		if(alarm[alarmnum+1]>0)alarmnum++;
		int temp,i;
		if(alarmnum>=2)for(i=alarmnum;i>=1;i--)
		{
			if(alarm[i]<alarm[i-1])
			{
				temp=alarm[i];
				alarm[i]=alarm[i-1];
				alarm[i-1]=temp;
			}
		}
	}
	//printf("%d %d\n",key,event);
}

int Setup()
{
	initConsole();
	initWindow("clock 0.8",DEFAULT,DEFAULT,400,600);
	time_t t=time(NULL);
	s=t%60;m=t%3600/60;h=(t%(3600*24)/3600+8);//get time
	mx=200;my=200;l=180;//basic inf of clock
	view();//basic view
	memset(alarm,0,sizeof(alarm));
	alarmnum=0;state=0;
	registerMouseEvent(mouse1);
	registerKeyboardEvent(key1);
	registerTimerEvent(time1);
	startTimer(0,1000);
	//²Î¿¼´úÂë 
	//beginPaint();
	//arc(0,100,30,40,50,60,70,80); 
	//putPixel(100,150,RGB(255,0,0));
	//line(0,0,width,width);
	//rectangle(10,10,22,22);
	//endPaint();
	return 0;
}

