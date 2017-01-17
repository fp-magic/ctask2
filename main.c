#include "acllib.h"
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<math.h>
#include<time.h>
int s,m,h,t,mx,my,l;
const double pi=3.1415926;
void view()
{
	setPenWidth(10);
	setPenColor(BLACK);
	//setPenStyle(PEN_STYLE_DASH);
	setBrushColor(GREEN);
	setBrushStyle(BRUSH_STYLE_SOLID); 
}

void time1(int id)//main painting
{
	s++;if(s==60){m++;s=0;}if(m==60){h++;m=0;}if(h==12)h=0;printf("%d:%d:%d\n",h,m,s);
	beginPaint();
	clearDevice();
	line(mx,my,mx+l*sin(2*pi*s/60),my-l*cos(2*pi*s/60));
	line(mx,my,mx+l*sin(2*pi*m/60),my-l*cos(2*pi*m/60));
	line(mx,my,mx+l*sin(2*pi*h/12)*2/3,my-l*cos(2*pi*h/12)*2/3);
	endPaint();
}
void mouse1(int x,int y,int button,int event)
{

}

void key1(int key,int event)
{
	
}

int Setup()
{
	initConsole();
	initWindow("clock 0.8",DEFAULT,DEFAULT,400,500);
	time_t t=time(NULL);
	s=t%60;m=t%3600/60;h=(t%(3600*24)/3600+8);//get time
	mx=200;my=200;l=180;//basic inf of clock
	view();//basic view
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

