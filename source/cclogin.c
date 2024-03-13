/**
 * @file cclogin.c
 * @author yangchunru
 * @brief login for the first time
 * @date 2021-04-24
 */
#include "public.h"
#include "cclogin.h"

/**
 * @param u pointer stores user info
 */
int p7_cclogin(USER *u)
{
	int page = 6;
	int len = 0;	//store the len for name, len=0 means not input yet
	int state_idtype = 1;	//id type(1 for common; 2 for others)
	int state_health = 1;	//health condition(1 for health; 2 for suspected; 3 for defined)
	int state_touch = 2;	//touch experience(1 for yes; 2 for no)

	memset(u,'\0',sizeof(USER));	//clear u
	clrmous(MouseX,MouseY);
	cclogin_screen();
	delay(300);
	
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(196,80,540,114) == 1)	//input name
		{
		    u->name[0] = '\0';
			setfillstyle(SOLID_FILL, WHITE);
			bar(196,80,540,114);
			len = hz_input(202,82,382,114,u->name,0,WHITE,DARKGRAY,32);
		}
		else if(mouse_press(196,180,540,214) == 1)	//input id number
		{
			u->ID[0] = '\0';
			inputadmin(u->ID, 196,180, 18, WHITE, 32);
		}
		else if(mouse_press(196,230,540,264) == 1)	//input phone number
		{
			u->phone[0] = '\0';
			inputadmin(u->phone, 196,230, 11, WHITE, 32);
		}
		else if(mouse_press(196,139,212,155) == 1)	//id type-common
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
			bar(196,139,212,155);
			bar(358,139,374,155);
			setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL, DARKGRAY);
			bar(198,141,210,153);
			state_idtype = 1;
		}
		else if(mouse_press(358,139,374,155) == 1)	//id type-others
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
			bar(196,139,212,155);
			bar(358,139,374,155);
			setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL, DARKGRAY);
			bar(360,141,372,153);
			state_idtype = 2;
		}
		else if(mouse_press(264,289,280,305) == 1)	//health condition-health
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
			bar(264,289,280,305);
			bar(372,289,388,305);
			bar(482,289,482+16,305);
			setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL, DARKGRAY);
			bar(30+34*6+32,280+11,264+14,280+23);
			state_health = 1;
		}
		else if(mouse_press(372,289,388,305) == 1)	//health condition-suspected
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
			bar(264,289,280,305);
			bar(372,289,388,305);
			bar(482,289,482+16,305);
			setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL, DARKGRAY);
			bar(60+34*7+12+30+34,280+11,60+34*7+30+14+10+34,280+23);
			state_health = 2;
		}
		else if(mouse_press(482,289,482+16,305) == 1)	//health condition-difined
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
			bar(264,289,280,305);
			bar(372,289,388,305);
			bar(482,289,482+16,305);
			setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL, DARKGRAY);
			bar(30+34*13+12,280+11,482+14,280+23);
			state_health = 3;
		}
		else if(mouse_press(482,30+50*6+9,482+16,30+50*6+25) == 1)	//touch experience-yes
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
			bar(482,30+50*6+9,482+16,30+50*6+25);
			bar(60+34*13+10+10+34,30+50*6+9,60+34*13+10+16+10+34,30+50*6+25);
			setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL, DARKGRAY);
			bar(30+34*13+12,30+50*6+11,482+14,30+50*6+23);
			state_touch = 1;
		}
		else if(mouse_press(60+34*13+10+10+34,30+50*6+9,60+34*13+10+16+10+34,30+50*6+25) == 1)	//touch experience-no
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
            setfillstyle(SOLID_FILL, WHITE);
			bar(482,30+50*6+9,482+16,30+50*6+25);
			bar(60+34*13+10+10+34,30+50*6+9,60+34*13+10+16+10+34,30+50*6+25);
			setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL, DARKGRAY);
			bar(558,30+50*6+11,60+34*13+10+14+10+34,30+50*6+23);
			state_touch = 2;
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
		else if (mouse_press(320-38,60+240+17+34+34,320+38,60+240+17+34+34+34) == 1)	//confirm button(go to login.c)
		{
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, LIGHTGREEN);
			bar(540+10,80-10,640,124);
			bar(540,180-8,640,214+8);
			bar(540,230-8,640,264+8);
			if (register_complete(u->name, u->ID, u->phone, len, state_idtype, state_health, state_touch))	//determine whether user can register
			{
				page = 4;
			    return page;
			}
			else
			{
				continue;
			}
		}
	}
}

void cclogin_screen(void)
{
    cleardevice();
    setbkcolor(LIGHTGREEN);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    //bar(640-68,480-32,640,480);
    puthz(640-68,480-34,"退出",32,34,WHITE);
    //bar(640-68*2-20,480-34,640-68-20,480);
    puthz(640-68*2-20,480-34,"返回",32,34,WHITE);
    puthz(640-68*2-20-20-34*4,480-34,"忘记密码",32,34,WHITE);
    puthz(640-68*2-20-20-34*4-20-34*4,480-34,"初次登录",32,34,DARKGRAY);
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(320-38,60+240+17+34+34,320+38,60+240+17+34+34+34);
    puthz(320-36+3,60+240+17+34+34+2,"注册",32,36,WHITE);
	
    puthz(30+1,30+50+1,"姓名",32,34,DARKGRAY);
    puthz(30,30+50,"姓名",32,34,WHITE);
    puthz(30+1,30+50*2+1,"证件类型",32,34,DARKGRAY);
    puthz(30,30+50*2,"证件类型",32,34,WHITE);
    puthz(30+1,180+1,"证件号码",32,34,DARKGRAY);
    puthz(30,180,"证件号码",32,34,WHITE);
    puthz(30+1,230+1,"手机号",32,34,DARKGRAY);
    puthz(30,230,"手机号",32,34,WHITE);
    puthz(30+1,281,"本人健康状况",32,34,DARKGRAY);
    puthz(30,280,"本人健康状况",32,34,WHITE);
    puthz(30+1,30+50*6+1,"十四天内是否接触过疑似人员",32,34,DARKGRAY);
    puthz(30,30+50*6,"十四天内是否接触过疑似人员",32,34,WHITE);
	
	setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
	bar(196,80,540,114);	//name box
	bar(196,180,540,214);	//id number box
	bar(196,230,540,264);	//phonenumber box
	
	bar(196,139,212,155);
	puthz(212+10+1,30+50*2+1,"身份证",32,34,DARKGRAY);
	puthz(212+10,30+50*2,"身份证",32,34,WHITE);
	bar(358,139,374,155);
	puthz(196+30+16+10+1+30+34*3,30+50*2+1,"其他类型",32,34,DARKGRAY);
	puthz(196+30+16+10+30+34*3,30+50*2,"其他类型",32,34,WHITE);
	
	bar(482,30+50*6+9,482+16,30+50*6+25);
	puthz(482+16+10+1,30+50*6+1,"是",32,34,DARKGRAY);
	puthz(482+16+10,30+50*6,"是",32,34,WHITE);
	bar(60+34*13+10+10+34,30+50*6+9,60+34*13+10+16+10+34,30+50*6+25);
	puthz(60+34*13+10+16+10+1+10+34,30+50*6+1,"否",32,34,DARKGRAY);
	puthz(60+34*13+10+16+10+10+34,30+50*6,"否",32,34,WHITE);
	
	bar(264,289,280,305);
	puthz(280+10+1,281,"健康",32,34,DARKGRAY);
	puthz(280+10,280,"健康",32,34,WHITE);
	bar(372,289,388,305);
	puthz(60+34*7+30+16+10+1+10+34,281,"疑似",32,34,DARKGRAY);
	puthz(60+34*7+30+16+10+10+34,280,"疑似",32,34,WHITE);
	bar(482,289,482+16,305);
	puthz(60+34*10+30+16+20+1+10+34,281,"确诊",32,34,DARKGRAY);
	puthz(60+34*10+30+16+20+10+34,280,"确诊",32,34,WHITE);
	
	setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
	bar(198,141,210,153);
	bar(30+34*6+32,280+11,264+14,280+23);
	bar(558,30+50*6+11,60+34*13+10+14+10+34,30+50*6+23);	
}