/**
 * @file grhome.c
 * @author yangchunru
 * @brief main interface for login user
 * @date 2021-04-30
 */
#include "public.h"
#include "grhome.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p4_grhome(USER *u, int*Flag)
{
	FILE* fp;
	USER us;
	int i, len, page = 3;
	char Name[10] = { '\0' };
	
	//get user's name when logged in
	if ((fp = fopen("database\\UserData.dat", "rb" )) == NULL)
	{
		printf("cannot open file UserData.dat in grhome.c");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(USER);
	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(USER), SEEK_SET);
		fread(&us, sizeof(USER), 1, fp);
		if (strcmp(u->phone, us.phone) == 0)
		{
			strcpy(Name,us.name);
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		delay(3000);
		exit(1);
	}
	
	clrmous(MouseX,MouseY);
	grhome_screen(Name);
	delay(300);
	
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to home.c)
		{
			page = 1;
			return page;
		}
		else if(mouse_press(640-68,2,640,34) == 1)	//log out button(go to home.c)
		{
			*Flag = 0;
			page = 1;
			return page;
		}
		else if(mouse_press(640-68,480-34,640,480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
		else if(mouse_press(150-60,240-75-60,150+60,240-75+60) == 1)	//check jkm and xcm button(go to jkm.c)
		{
			page = 8;
			return page;
		}
		else if(mouse_press(150-60,240+75-60,150+60,240+75+60) == 1)	//risk rank info enquiry button(go to risklook.c)
		{
			page = 9;
			return page;
		}
		else if(mouse_press(320-60,240+75-60,320+60,240+75+60) == 1)	//change personal info button(go to xxchange.c)
		{
			page = 10;
			return page;
		}
		else if(mouse_press(320-60,240-75-60,320+60,240-75+60) == 1)	//record check and change button(go to record.c)
		{
			page = 11;
			return page;
		}
		else if(mouse_press(640-150-60,240-75-60,640-150+60,240-75+60) == 1)	//reserve info check and add button(go to reserve.c)
		{
			page = 13;
			return page;
		}
		else if(mouse_press(640-150-60,240+75-60,640-150+60,240+75+60) == 1)	//write feedback button(go to feedback.c)
		{
			page = 15;
			return page;
		}
	}
}

/**
 * @param n user's name
 */
void grhome_screen(char* n)
{
	cleardevice();
	setbkcolor(WHITE);
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	//bar(640-68,2,640,34);
	puthz(640-68,2,"登出",32,34,LIGHTGRAY);
	//bar(640-68-136-20,2,640-88,34);
	puthz(640-68-136-20,2,"个人中心",32,34,DARKGRAY);
	//bar(640-68-136-20-102-20,2,640-68-136-40,34);
	puthz(640-68-136-20-102-20,2,n,32,34,LIGHTGRAY);
	//bar(640-68,480-32,640,480);
	puthz(640-68,480-34,"退出",32,34,LIGHTGRAY);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640-68*2-20,480-34,"返回",32,34,LIGHTGRAY);
	setcolor(LIGHTGREEN);
	setfillstyle(SOLID_FILL, LIGHTGREEN);
	fillellipse(150,240-75,60,60);
	puthz(150-26*1.5,245-75-25*1.5,"健康码",24,26,WHITE);
	puthz(150-26*0.5,245-75-25*0.5,"及",24,26,WHITE);
	puthz(150-26*1.5,245-75+25*0.5-2,"行程码",24,26,WHITE);
	setcolor(GREEN);
	setfillstyle(SOLID_FILL, GREEN);
	fillellipse(320,240-75,60,60);
	puthz(320-26*1.5,245-75-25*1.5,"防疫行",24,26,WHITE);
	puthz(320-26*1.5,245-75-25*0.5,"程记录",24,26,WHITE);
	puthz(320-26*0.5,245-75+25*0.5-2,"卡",24,26,WHITE);
	setcolor(LIGHTBLUE);
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	fillellipse(150,240+75,60,60);
	puthz(150-26*1.5,245+74-25*1.5,"区域疫",24,26,WHITE);
	puthz(150-26*1.5,245+74-25*0.5,"情风险",24,26,WHITE);
	puthz(150-26*2,245+75+25*0.5-2,"等级查询",24,26,WHITE);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL, BLUE);
	fillellipse(640-150,240-75,60,60);
	puthz(640-150-26*2,245-75-25*1.5,"核酸检测",24,26,WHITE);
	puthz(640-150-26*2,245-75-25*0.5,"预约及结",24,26,WHITE);
	puthz(640-150-26*1.5,245-75+25*0.5-2,"果查询",24,26,WHITE);
	setcolor(BROWN);
	setfillstyle(SOLID_FILL, BROWN);
	fillellipse(320,240+75,60,60);
	puthz(320-26*1.5,245+75-25,"个人信",24,26,WHITE);
	puthz(320-26*1.5,245+75+1,"息完善",24,26,WHITE);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	fillellipse(640-150,240+75,60,60);
	puthz(640-150-26,245+75-25,"用户",24,26,WHITE);
	puthz(640-150-26,245+75+1,"反馈",24,26,WHITE);
}