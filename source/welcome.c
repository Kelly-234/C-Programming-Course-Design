/**
 * @file welcome.c
 * @author yangchunru
 * @brief welcome page
 * @date 2021-04-29 
 */
#include "public.h"
#include "welcome.h"

int p1_welcome(void)
{
	int page = 0;
	
	clrmous(MouseX,MouseY);
	welcome_screen();
	delay(300);
	
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(320-32,260,320+32,260+32) == 1)	//enter button(go to home.c)
		{
			page = 1;
			return page;
		}
		else if(mouse_press(320-34*2.5,260+45,320+34*2.5,260+45+32) == 1)	//login for admin button(go to gllogin.c)
		{
			page = 5;
			return page;
		}
		else if(mouse_press(320-32,260+90,320+32,260+32+90) == 1)	//exit button
		{
			page = 18;
			return page;
		}
	}
}

void welcome_screen(void)
{
	cleardevice();
	setbkcolor(LIGHTGREEN);
	setfillstyle(SOLID_FILL, BLUE);
	puthz(320-34*6.5+1,120+1,"�����г̿��뽡����ģ�����",32,34,DARKGRAY);
	puthz(320-34*6.5,120,"�����г̿��뽡����ģ�����",32,34,WHITE);
	puthz(320-26*5,160,"�������",24,26,WHITE);
	puthz(320+26,160,"��������",24,26,WHITE);
	//bar(320-32,260,320+32,260+32);
	puthz(320-32,260,"����",32,34,WHITE);
	//bar(320-34*2.5,260+45,320+34*2.5,260+45+32);
	puthz(320-34*2.5,260+45,"����Ա����",32,34,WHITE);
	//bar(320-32,260+90,320+32,260+32+90);
	puthz(320-32,260+90,"�˳�",32,34,WHITE);
	setcolor(WHITE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
	outtextxy(200,450,"Made by Automation 2004 YCR and ZSM.");
}