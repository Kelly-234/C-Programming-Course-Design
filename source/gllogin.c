/**
 * @file gllogin.c
 * @author yangchunru
 * @brief for admin to log in
 * @date 2021-04-30
 */
#include "public.h"
#include "gllogin.h"

int p6_gllogin(void)
{
	int page = 0;
	char A[15] = { '\0' };	//store account number
	char P[10] = { '\0' };	//store password

	clrmous(MouseX, MouseY);
	gllogin_screen();
	delay(300);

	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if (mouse_press(320,240-34-17,520,240-17) == 1)	//input account number
		{
			A[0] = '\0';
			inputadmin(A, 320,240-34-17, 10, WHITE, 32);
		}
		else if (mouse_press(320,240+17,520,240+17+34) == 1)	//input password
		{
			P[0] = '\0';
			inputpassword(P, 320,240+17, 8, WHITE);
		}
        else if (mouse_press(320-38,240+17+34+34,320+38,240+17+34+34+34) == 1)	//log in button(go to glhome.c)
		{
			if (admin_judge(A, P))	//determine whether the admin can log in
			{
				page = 2;
				return page;
			}
		}
		else if (mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to welcome.c)
		{
			page = 0;
			return page;
		}
		else if (mouse_press(640-68,480-32,640,480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
	}
}

void gllogin_screen(void)
{
	cleardevice();
	setbkcolor(LIGHTGREEN);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	//bar(640-68,480-32,640,480);
	puthz(640-68,480-34,"退出",32,34,WHITE);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640-68*2-20,480-34,"返回",32,34,WHITE);
	bar(320,240-34-17,520,240-17);
	bar(320,240+17,520,240+17+34);
	puthz(120+1,240-33-17+1,"管理员账号",32,34,DARKGRAY);
	puthz(120,240-33-17,"管理员账号",32,34,WHITE);
	puthz(120+1,240+17+1,"密码",32,34,DARKGRAY);
	puthz(120,240+17,"密码",32,34,WHITE);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(320-38,240+17+34+34,320+38,240+17+34+34+34);
	puthz(320-36+3,240+17+34+34+2,"登录",32,36,WHITE);
}