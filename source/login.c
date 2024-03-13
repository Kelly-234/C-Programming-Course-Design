/**
 * @file login.c
 * @author yangchunru
 * @brief for users to log in
 * @date 2021-04-30
 */
#include "public.h"
#include "login.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p5_login(USER *u, int* Flag)
{
	int page = 4;

	memset(u,'\0',sizeof(USER));	//clear u
	clrmous(MouseX, MouseY);
	login_screen();
	delay(300);
	
	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(277,240-34-17,277+218,240-17) == 1)	//input phone number
		{
			u->phone[0] = '\0';
			inputadmin(u->phone, 277,240-34-17, 11, WHITE, 32);
		}
		else if (mouse_press(277,240+17,277+218,240+17+34) == 1)	//input password
		{
			u->password[0] = '\0';
			inputpassword(u->password, 277, 240+17, 8, WHITE);
		}
		else if (mouse_press(320-38,240+17+34+34,320+38,240+17+34+34+34) == 1)	//log in button(go to home.c)
		{
			setfillstyle(SOLID_FILL, LIGHTGREEN);
			bar(0,240-17-34-34-24,640,240-17-34-34);
			if (login_complete(u->phone, u->password))	//determine whether the user can log in
			{
				if (input_uinfo(u))	//transmit to store user's info
				{
					*Flag = 1;
					page = 1;
				    return page;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		else if (mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to home.c)
		{
			page = 1;
			return page;
		}
		else if (mouse_press(640-68*2-20-20-34*4-20-34*4,480-34,640-68*2-20-20-34*4-20,480) == 1)	//login for the first time button(go to cclogin.c)
		{
			page = 6;
			return page;
		}
		else if (mouse_press(640-68*2-20-20-34*4,480-34, 640-68*2-20-20, 480) == 1)	//change password button(go to mmchange.c)
		{
			page = 7;
			return page;
		}
		else if (mouse_press(640-68,480-32,640,480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
	}
}

void login_screen(void)
{
    cleardevice();
	setbkcolor(LIGHTGREEN);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	//bar(640-68,480-32,640,480);
	puthz(640-68,480-34,"ÍË³ö",32,34,WHITE);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640-68*2-20,480-34,"·µ»Ø",32,34,WHITE);
	puthz(640-68*2-20-20-34*4,480-34,"Íü¼ÇÃÜÂë",32,34,WHITE);
	puthz(640-68*2-20-20-34*4-20-34*4,480-34,"³õ´ÎµÇÂ¼",32,34,WHITE);
	bar(277,240-34-17,277+218,240-17);
	bar(277,240+17,277+218,240+17+34);
	puthz(320-175+1,240-33-17+1,"ÊÖ»úºÅ",32,34,DARKGRAY);
	puthz(320-175,240-33-17,"ÊÖ»úºÅ",32,34,WHITE);
	puthz(320-175+1,240+18+1,"ÃÜÂë",32,34,DARKGRAY);
	puthz(320-175,240+18,"ÃÜÂë",32,34,WHITE);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(320-38,240+17+34+34,320+38,240+17+34+34+34);
	puthz(320-36+3,240+17+34+34+2,"µÇÂ¼",32,36,WHITE);
}