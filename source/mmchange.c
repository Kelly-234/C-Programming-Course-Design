/**
 * @file mmchange.c
 * @author yangchunru
 * @brief change the password by right id and phone number
 * @date 2021-04-30
 */
#include "public.h"
#include "mmchange.h"

/**
 * @param u pointer stores user info
 */
int p8_mmchange(USER *u)
{
	int page = 7;
	char CP[20] = { '\0' };	//store new password again
	
	memset(u,'\0',sizeof(USER));	//clear u
	clrmous(MouseX, MouseY);
	mmchange_screen();
	delay(300);
	
	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if (mouse_press(236,240-34-17-68,580,240-17-68) == 1)	//input id
		{
			u->phone[0] = '\0';
			inputadmin(u->ID, 236,240-34-68-17, 18, WHITE, 32);
		}
		else if (mouse_press(236,240-34-17,580,240-17) == 1)	//input phone number
		{
			u->phone[0] = '\0';
			inputadmin(u->phone, 236, 240-34-17, 11, WHITE, 32);
		}
		else if (mouse_press(320-80,240+17,580,240+17+34) == 1)	//input new password
		{
			u->password[0] = '\0';
			inputpassword(u->password, 320-80, 240+17, 8, WHITE);
		}
		else if (mouse_press(236,240+68+17,580,240+17+34+68) == 1)	//input new password again
		{
			CP[0] = '\0';
			inputpassword(CP, 236,240+68+17, 8, WHITE);
		}
		else if (mouse_press(320-38,240+17+34+34+68,320+38,240+17+34+34+34+68) == 1)	//confirm button(go to login.c)
		{
			clrmous(MouseX, MouseY);
			setfillstyle(SOLID_FILL, LIGHTGREEN);
			bar(0,240-34-17-68-44,640,240-17-68-34);
			bar(580,240-17-67,640,240+17+34+68);
			if (forgetpass_complete(u->ID, u->phone, u->password, CP, 240-34-17-68-24-20))	//determine whether user can change tha password
			{
				page = 4;
				return page;
			}
			else
			{
				continue;
			}
		}
		else if (mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to login.c)
		{
			page = 4;
			return page;
		}
		else if (mouse_press(640-68,480-32,640,480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
	}
}

void mmchange_screen(void)
{
    cleardevice();
	setbkcolor(LIGHTGREEN);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	//bar(640-68,480-32,640,480);
	puthz(640-68,480-34,"退出",32,34,WHITE);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640-68*2-20,480-34,"返回",32,34,WHITE);
	puthz(640-68*2-20-20-34*4,480-34,"忘记密码",32,34,DARKGRAY);
	puthz(640-68*2-20-20-34*4-20-34*4,480-34,"初次登录",32,34,WHITE);
	bar(236,240-34-68-17,580,240-17-68);
	bar(236,240-34-17,580,240-17);
	bar(236,240+17,580,240+17+34);
	bar(236,240+68+17,580,240+17+34+68);
	puthz(60,240-33-17+1-68,"身份证号",32,34,DARKGRAY);
	puthz(60,240-33-17-68,"身份证号",32,34,WHITE);
	puthz(60,240-33-17+1,"手机号",32,34,DARKGRAY);
	puthz(60,240-33-17,"手机号",32,34,WHITE);
	puthz(60,240+17+1,"新密码",32,34,DARKGRAY);
	puthz(60,240+17,"新密码",32,34,WHITE);
	puthz(60,240+17+1+68,"确认密码",32,34,DARKGRAY);
	puthz(60,240+17+68,"确认密码",32,34,WHITE);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(320-38,240+17+34+34+68,320+38,240+17+34+34+34+68);
	puthz(320-36+3,240+17+34+34+2+68,"确定",32,36,WHITE);
}
