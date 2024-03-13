/**
 * @file feedback.c
 * @author yangchunru
 * @brief write feedback
 * @date 2021-05-01
 */
#include "public.h"
#include "feedback.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p16_feedback(USER *u, int*Flag)
{
    FILE* fp;
	USER us;
	int i, len, page = 15, len_hz = 0;
	int type = 1;	//1 for jkm and xcm; 2 for record; 3 for reserve; 4 for risk rank info; 5 for personal info change
	int anonymous_state = 0;	//1 for anonymous; 2 for not
	int count = 0;	//counts the number of clicks of the anonymous button
	char Name[20] = { '\0' };
	char Phone[20] = { '\0' };
	char feedback[170] = { '\0' };
	char temp_remain[5] = { '\0' };	//store the string convert by remain input number
	
	if ((fp = fopen("database\\UserData.dat", "rb" )) == NULL)
	{
		printf("cannot open file UserData.dat in feedback.c");
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
			strcpy(Phone,u->phone);
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
	feedback_screen(Name, Phone);
	delay(300);
	
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(640-68,2,640,34) == 1)	//log out button(go to home.c)
		{
			*Flag = 0;
			page = 1;
			return page;
		}
		else if(mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to grhome.c)
		{
			page = 3;
			return page;
		}
		else if(mouse_press(640-68,480-34,640,480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
		else if(mouse_press(20,110,20+16,110+16) == 1)	//type-jkm
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20,110,20+16,110+16) == 1);
			type = 1;
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(20+8,110+8,6,6);	//jkm
			fillellipse(20+8*18+8+30+5,110+8,6,6);	//record
			fillellipse(20+8*18+30+8*18+30+10+8,110+8,6,6);	//reserve
			fillellipse(20+8,140+8,6,6);	//risklook
			fillellipse(20+11*18+8+30+5,140+8,6,6);	//xxchange
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(20+8,110+8,5,5);	//jkm
		}
		else if(mouse_press(20+8*18+30+5,110,20+8*18+16+30+5,110+16) == 1)	//type-record
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+8*18+30+5,110,20+8*18+16+30+5,110+16) == 1);
			type = 2;
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(20+8,110+8,6,6);	//jkm
			fillellipse(20+8*18+8+30+5,110+8,6,6);	//record
			fillellipse(20+8*18+30+8*18+30+10+8,110+8,6,6);	//reserve
			fillellipse(20+8,140+8,6,6);	//risklook
			fillellipse(20+11*18+8+30+5,140+8,6,6);	//xxchange
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(20+8*18+8+30+5,110+8,5,5);	//record
		}
		else if(mouse_press(20+8*18+30+8*18+30+10,110,20+8*18+30+8*18+30+10+16,110+16) == 1)	//type-reserve
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+8*18+30+8*18+30+10,110,20+8*18+30+8*18+30+10+16,110+16) == 1);
			type = 3;
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(20+8,110+8,6,6);	//jkm
			fillellipse(20+8*18+8+30+5,110+8,6,6);	//record
			fillellipse(20+8*18+30+8*18+30+10+8,110+8,6,6);	//reserve
			fillellipse(20+8,140+8,6,6);	//risklook
			fillellipse(20+11*18+8+30+5,140+8,6,6);	//xxchange
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(20+8*18+30+8*18+30+10+8,110+8,5,5);	//reserve
		}
		else if(mouse_press(20,140,20+16,140+16) == 1)	//type-risklook
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20,140,20+16,140+16) == 1);
			type = 4;
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(20+8,110+8,6,6);	//jkm
			fillellipse(20+8*18+8+30+5,110+8,6,6);	//record
			fillellipse(20+8*18+30+8*18+30+10+8,110+8,6,6);	//reserve
			fillellipse(20+8,140+8,6,6);	//risklook
			fillellipse(20+11*18+8+30+5,140+8,6,6);	//xxchange
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(20+8,140+8,5,5);	//risklook
		}
		else if(mouse_press(20+11*18+30+5,140,20+11*18+16+30+5,140+16) == 1)	//type-xxchange
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+11*18+30+5,140,20+11*18+16+30+5,140+16) == 1);
			type = 5;
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(20+8,110+8,6,6);	//jkm
			fillellipse(20+8*18+8+30+5,110+8,6,6);	//record
			fillellipse(20+8*18+30+8*18+30+10+8,110+8,6,6);	//reserve
			fillellipse(20+8,140+8,6,6);	//risklook
			fillellipse(20+11*18+8+30+5,140+8,6,6);	//xxchange
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(20+11*18+8+30+5,140+8,5,5);	//xxchange
		}
		else if(mouse_press(500-4,400,500-4+15,400+15) == 1)	//anonymity button
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(500-4,400,500-4+15,400+15) == 1);
			count++;
			clrmous(MouseX,MouseY);
			if (count%2 == 1)
			{
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(500-4+3,400+3,500-4+15-3,400+15-3);
				setfillstyle(SOLID_FILL, WHITE);
				bar(20+18*4+20+18*2+10,400,480,420);
				bar(20+18*4+20+18*4+10,420,480,440);
				outtextxy(20+18*4+20+18*2+10,397,"***");
				outtextxy(20+18*4+20+18*4+10,417,"***********");
				anonymous_state = 1;
			}
			else
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(500-4+3,400+3,500-4+15-3,400+15-3);
				setfillstyle(SOLID_FILL, WHITE);
				bar(20+18*4+20+18*2+10,400,480,420);
				bar(20+18*4+20+18*4+10,420,480,440);
				puthz(20+18*4+20+18*2+10,400,Name,16,18,DARKGRAY);
				outtextxy(20+18*4+20+18*4+10,415,Phone);
				anonymous_state = 0;
			}
		}
		else if(mouse_press(60,165,580,370) == 1)	//input feedback
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(60,165,580,370) == 1);
			if(!feedback[0])
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(70,170,570,365);
			}
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(80,368,320,389);
			len_hz = hz_input(80,185,560,275,feedback,len_hz,WHITE,DARKGRAY,16);
			clrmous(MouseX,MouseY);
			settextjustify(LEFT_TEXT,TOP_TEXT);
			settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);
			setfillstyle(SOLID_FILL, WHITE);
			itoa((160-len_hz)/2,temp_remain,10);
			bar(80+18*4,370,320,389);
			setcolor(DARKGRAY);
			puthz(80,370,"还可输入",16,18,DARKGRAY);
			outtextxy(80+18*4,365,temp_remain);
			puthz(80+18*4+strlen(temp_remain)*15-3,370,"字",16,18,DARKGRAY);
		}
		else if(mouse_press(480,370,480+18*2,390) == 1)	//clear feedback
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(480,370,480+18*2,39) == 1);
			feedback[0] = '\0';
			len_hz = 0;
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(70,175,570,365);
			puthz(80,185,"请写下您宝贵的意见和建议",16,18,LIGHTBLUE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(80,370,320,389);
			setcolor(DARKGRAY);
			rectangle(500-4,400,500-4+15,400+15);
			puthz(80,370,"还可输入",16,18,DARKGRAY);
			outtextxy(80+18*4,365,"80");
			puthz(80+18*4+2*15-3,370,"字",16,18,DARKGRAY);
		}
		else if(mouse_press(530,370,530+18*2,390) == 1)	//input feedback button
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(530,370,530+18*2,390) == 1);
			if (len_hz == 0)
			{
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(250,250,390,280);
				setcolor(DARKGRAY);
				rectangle(250,250,390,280);
				puthz(320-18*2.5,265-8,"请填写内容",16,18,RED);
				delay(2000);
				feedback_screen(Name, Phone);
			}
			else
			{
				clrmous(MouseX,MouseY);
				inputfeedback(feedback, Name, Phone, type, anonymous_state);
				clrmous(MouseX,MouseY);
				feedback_screen(Name, Phone);
				feedback[0] = '\0';
				len_hz = 0;
			}
		}
	}
}

/**
 * @param n user's name
 * @param p user's phone
 */
void feedback_screen(char* n, char* p)
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
	puthz(20,40,"用户反馈",32,34,LIGHTGRAY);
	puthz(20,83,"请选择出现问题的功能模块",16,18,BLUE);
	puthz(20+18+5,110,"健康码及行程码",16,18,DARKGRAY);	//jkm
	puthz(20+9*18+30+10,110,"防疫行程记录卡",16,18,DARKGRAY);	//record
	puthz(20+8*18+30+9*18+30+15,110,"核酸检测预约及结果查询",16,18,DARKGRAY);	//reserve
	puthz(20+18+5,140,"区域疫情风险等级查询",16,18,DARKGRAY);	//risklook
	puthz(20+12*18+30+10,140,"个人信息完善",16,18,DARKGRAY);	//xxchange
	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, WHITE);
	circle(20+8,110+8,8);	//jkm
	circle(20+8*18+8+30+5,110+8,8);	//record
	circle(20+8*18+30+8*18+30+10+8,110+8,8);	//reserve
	circle(20+8,140+8,8);	//risklook
	circle(20+11*18+8+30+5,140+8,8);	//xxchange
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, DARKGRAY);
	fillellipse(20+8,110+8,5,5);
	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE,0,1);
	rectangle(60,165,580,390);
	puthz(80,185,"请写下您宝贵的意见和建议",16,18,LIGHTBLUE);
	puthz(480,370,"清空",16,18,LIGHTBLUE);
	puthz(530,370,"提交",16,18,LIGHTBLUE);
	puthz(20,400,"联系方式",16,18,DARKGRAY);
	puthz(20+18*4+20,400,"姓名",16,18,DARKGRAY);
	puthz(20+18*4+20+18*2+10,400,n,16,18,DARKGRAY);
	puthz(20+18*4+20,420,"联系电话",16,18,DARKGRAY);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);
	outtextxy(20+18*4+20+18*4+10,415,p);
	puthz(20,440,"留下联系方式",16,18,LIGHTRED);
	puthz(20+6*18+15,440,"工作人员将优先处理您的反馈",16,18,LIGHTRED);
	setcolor(LIGHTRED);
	outtextxy(20+18*6,435,",");
	puthz(500+18,400,"匿名反馈",16,18,DARKGRAY);
	setcolor(DARKGRAY);
	rectangle(500-4,400,500-4+15,400+15);
	puthz(80,370,"还可输入",16,18,DARKGRAY);
	outtextxy(80+18*4,365,"80");
	puthz(80+18*4+2*15-3,370,"字",16,18,DARKGRAY);
}

/**
 * @brief input feedback to the file for admin to check
 * @param f string of feedback
 * @param n user's name
 * @param p user's phone
 * @param Type feedback type
 * @param Anonymous_state whether be anonymous
 */
void inputfeedback(char* f, char* n, char* p, int Type, int Anonymous_state)
{
	FILE* fp;
	FEEDBACK fe;
	
	if ((fp = fopen("database\\Feedback.dat", "rb+" )) == NULL)
	{
		printf("cannot open file Feedback.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	fread(&fe, sizeof(FEEDBACK), 1, fp);
	strcpy(fe.feedback,f);
	strcpy(fe.name,n);
	strcpy(fe.phone,p);
	fe.type = Type;
	fe.anonymous_state = Anonymous_state;
	if (fwrite(&fe, sizeof(FEEDBACK), 1, fp))
	{
		if (fclose(fp) != 0)
		{
			printf("\n cannot close Reserve.dat");
			delay(3000);
			exit(1);
		}
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		bar(250,250,390,280);
		setcolor(DARKGRAY);
		rectangle(250,250,390,280);
		puthz(320-18*2,265-8,"提交成功",16,18,RED);
		delay(2000);
	}
}