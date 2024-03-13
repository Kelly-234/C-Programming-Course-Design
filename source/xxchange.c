/**
 * @file xxchange.c 
 * @author yangchunru
 * @brief show user's personal info, can add or change some of them
 * @date 2021-04-30
 */
#include "public.h"
#include "xxchange.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p11_xxchange(USER *u, int* Flag)
{
	int page = 10;
	int state_vaccine = 0;	//whether have filled vaccine state(0 for yes; 1 for no)
	int state_address = 0;	//whether have filled living address(0 for yes; 1 for no)
	int vaccine = 2;	//vaccine state(1 for yes; 2 for no)
	int flag = 0;	//1 for choosing province or city now; 0 for not
	char province[30] = { '\0' };
	char city[30] = { '\0' };
	
	clrmous(MouseX,MouseY);
	xxchange_screen();
	getinfo(u, &state_vaccine, &state_address);
	delay(300);
	
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to grhome.c)
		{
			page = 3;
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
		else if ((mouse_press(20+34*8+28,40*7+9,20+34*8+28+16,40*7+16+9) == 1) && (state_vaccine == 1) && (flag == 0))	//vaccnie-yes
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+34*8+28,40*7+9,20+34*8+28+16,40*7+16+9) == 1);
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(20+34*8+28+16+10+34+12,40*7+11,20+34*8+28+16+10+34+24,40*7+16+7);
			setcolor(DARKGRAY);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(20+34*8+30,40*7+11,20+34*8+28+14,40*7+16+7);
			vaccine = 1;
		}
		else if ((mouse_press(20+34*8+28+16+10+34+10,40*7+9,20+34*8+28+16+10+34+26,40*7+16+9) == 1) && (state_vaccine == 1) && (flag == 0))	//vaccine-no
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+34*8+28+16+10+34+10,40*7+9,20+34*8+28+16+10+34+26,40*7+16+9) == 1);
			clrmous(MouseX,MouseY);
			setcolor(DARKGRAY);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(20+34*8+28+16+10+34+12,40*7+11,20+34*8+28+16+10+34+24,40*7+16+7);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(20+34*8+30,40*7+11,20+34*8+28+14,40*7+16+7);
			vaccine = 2;
		}
		else if ((mouse_press(20+34*8+28+16+10+34+10+16+10+34+20,40*7,20+34*8+28+16+10+34+10+16+10+34+20+70,40*7+34) == 1) && (state_vaccine == 1) && (flag == 0))	//confirm button for vaccine
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+34*8+28+16+10+34+10+16+10+34+20,40*7,20+34*8+28+16+10+34+10+16+10+34+20+70,40*7+34) == 1);
			state_vaccine = 0;
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(20+34*8+18,40*7,640,40*7+34);
			input_vaccine(u, vaccine);
			getinfo(u, &state_vaccine, &state_address);
		}
		else if ((mouse_press(130,40*6,130+32*5+4,40*6+34) == 1) && (state_address == 1))	//choose province button
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(130,40*6,130+32*5+4,40*6+34) == 1);
			province[0] = '\0';
			flag = 1;
			clrmous(MouseX,MouseY);
			showplace(province, city, 20+102+18, 40*7, &flag);
			clrmous(MouseX,MouseY);
			xxchange_screen();
			getinfo(u, &state_vaccine, &state_address);
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130,40*6,130+32*5+4,40*6+34);
			bar(130+32*5+4+5,40*6,130+32*5+9+4+32*8,40*6+34);
			puthz(130+(5*32-strlen(province)/2*32)/2,40*6,province,32,32,WHITE);
			puthz(130+32*5+4+5+62,40*6+1,"选择城市",32,34,WHITE);
		}
		else if (mouse_press(130+32*5+4+5,40*6,130+32*5+9+4+32*8,40*6+34) == 1 && strcmp(province, "") != 0 && state_address == 1)	//choose city button
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(130+32*5+4+5,40*6,130+32*5+9+4+32*8,40*6+34) == 1);
			city[0] = '\0';
			flag = 1;
			clrmous(MouseX,MouseY);
			showplace(province, city, 20+102+18+26*8+4+10+10+34*6-370, 40*7, &flag);
			clrmous(MouseX,MouseY);
			xxchange_screen();
			getinfo(u, &state_vaccine, &state_address);
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130,40*6,130+32*5+4,40*6+34);
			bar(130+32*5+4+5,40*6,130+32*5+9+4+32*8,40*6+34);
			puthz(130+(5*32-strlen(province)/2*32)/2,40*6,province,32,32,WHITE);
			puthz(130+32*5+4+5+(8*32-strlen(city)/2*32)/2,40*6,city,32,32,WHITE);
		}
		else if (mouse_press(15+102+18+26*8+4+5+10+34*6+5,40*6,15+102+18+26*8+4+5+10+34*6+5+70,40*6+34) == 1 && state_address == 1)	//confirm button for living address
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(15+102+18+26*8+4+5+10+34*6+5,40*6,15+102+18+26*8+4+5+10+34*6+5+70,40*6+34) == 1);
			if (strcmp(province, "") == 0)
			{
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0,116,640,445);
				setfillstyle(SOLID_FILL, WHITE);
				bar(250,220,390,260);
				setlinestyle(SOLID_LINE,0,3);
				setcolor(DARKGRAY);
				rectangle(250,220,390,260);
				puthz(320-18*3,240-9,"请先选择省份",16,18,RED);
				delay(2000);
				bar(245,215,395,265);
			}
			else if (strcmp(city, "") == 0)
			{
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0,116,640,445);
				setfillstyle(SOLID_FILL, WHITE);
				bar(250,220,390,260);
				setlinestyle(SOLID_LINE,0,3);
				setcolor(DARKGRAY);
				rectangle(250,220,390,260);
				puthz(320-18*3,240-9,"请先选择城市",16,18,RED);
				delay(2000);
				bar(245,215,395,265);
			}
			else	//input living adress info
			{
				state_address = 0;
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(130,40*6,640,40*6+34);
				input_home(u,province,city);
				getinfo(u, &state_vaccine, &state_address);
			}
		}
	}
}

/**
 * @brief get user's personal info
 * @param us pointer stores user info
 * @param State_vaccine whether have filled vaccine state(0 for yes; 1 for no)
 * @param State_address whether have filled living address(0 for yes; 1 for no)
 */
void getinfo(USER *us, int* State_vaccine, int* State_address)
{
	FILE* fp;
	USER u;
	int i, len;
	char home[50] = { '\0' };
	
	if ((fp = fopen("database\\UserData.dat", "rb" )) == NULL)
	{
		printf("cannot open file UserData.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(USER);
	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(USER), SEEK_SET);
		fread(&u, sizeof(USER), 1, fp);
		if (strcmp(us->phone, u.phone) == 0)
		{
			puthz(640-68-136-20-102-20,2,u.name,32,34,LIGHTGRAY);
			setcolor(DARKGRAY);
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
			puthz(20,40*2,"姓名",32,34,DARKGRAY);
			outtextxy(20+68,40*2,":");
			puthz(20+68+18,40*2,u.name,32,34,DARKGRAY);
			puthz(20,40*3,"身份证号",32,34,DARKGRAY);
			outtextxy(20+136,40*3,":");
			outtextxy(20+136+18,40*3,u.ID);
			puthz(20,40*4,"手机号",32,34,DARKGRAY);
			outtextxy(20+102,40*4,":");
			outtextxy(20+102+18,40*4,u.phone);
			puthz(20,40*5,"健康状况",32,34,DARKGRAY);
			outtextxy(20+136,40*5,":");
			if (strcmp(u.condition,"1") == 0)
			{
				
				puthz(20+136+18,40*5,"健康",32,34,DARKGRAY);
			}
			else if (strcmp(u.condition,"2") == 0)
			{
				puthz(20+136+18,40*5,"发热或疑似",32,34,DARKGRAY);
			}
			else
			{
				puthz(20+136+18,40*5,"确诊",32,34,DARKGRAY);
			}
			puthz(20,40*6,"常住地",32,34,DARKGRAY);
			outtextxy(20+102,40*6,":");
			if (strcmp(u.province0, "") != 0)	//have filled vaccine state
			{
				if ((strcmp(u.province0, "香港") == 0) || (strcmp(u.province0, "澳门") == 0))
				{
					strcpy(home,u.province0);
					strcat(home, "特别行政区");
				}
				else if (strcmp(u.province0, u.city0) == 0)
				{
					strcpy(home, u.province0);
					strcat(home, "市");
				}
				else if ((strcmp(u.province0, "新疆维吾尔") == 0) || (strcmp(u.province0, "西藏") == 0) || (strcmp(u.province0, "内蒙古") == 0) || (strcmp(u.province0, "广西壮族") == 0) || (strcmp(u.province0, "宁夏回族") == 0))
				{
					strcpy(home, u.province0);
					strcat(home, u.city0);
					strcat(home, "自治区");
				}
				else
				{
					strcpy(home, u.province0);
					strcat(home, "省");
					strcat(home, u.city0);
					strcat(home, "市");
				}
				puthz(20+102+18,40*6,home,32,34,DARKGRAY);
			}
			else
			{
				*State_address = 1;
				setcolor(LIGHTGRAY);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(130,40*6,130+32*5+4,40*6+34);
				puthz(130+14,40*6+1,"选择省份",32,34,WHITE);
				bar(130+32*5+4+5,40*6,130+32*5+9+4+32*8,40*6+34);
				puthz(130+32*5+4+5+62,40*6+1,"选择城市",32,34,WHITE);
				bar(130+32*5+9+4+32*8+5,40*6,130+32*5+9+4+32*8+5+70,40*6+34);
				puthz(130+32*5+9+4+32*8+5+1,40*6+1,"确定",32,34,WHITE);
			}
			puthz(20,40*7,"是否接种新冠疫苗",32,34,DARKGRAY);
			setcolor(DARKGRAY);
			outtextxy(20+34*8,40*7,":");
			if (strcmp(u.vaccine,"") != 0)	//have filled living address info
			{
				puthz(20+34*8+18,40*7,u.vaccine,32,34,DARKGRAY);
			}
			else
			{
				*State_vaccine = 1;
				setcolor(DARKGRAY);
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(20+34*8+28,40*7+9,20+34*8+28+16,40*7+16+9);
				puthz(20+34*8+28+16+10,40*7,"是",32,34,DARKGRAY);
				bar(20+34*8+28+16+10+34+10,40*7+9,20+34*8+28+16+10+34+26,40*7+16+9);
				puthz(20+34*8+28+16+10+34+10+16+10,40*7,"否",32,34,DARKGRAY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(20+34*8+30,40*7+11,20+34*8+28+14,40*7+16+7);
				setcolor(LIGHTGRAY);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(20+34*8+28+16+10+34+10+16+10+34+20,40*7,20+34*8+28+16+10+34+10+16+10+34+20+70,40*7+34);
				puthz(20+34*8+28+16+10+34+10+16+10+34+20+2,40*7+1,"确定",32,34,WHITE);
			}
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		delay(3000);
		exit(1);
	}
}

void xxchange_screen(void)
{
	cleardevice();
	setbkcolor(WHITE);
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	//bar(640-68,2,640,34);
	puthz(640-68,2,"登出",32,34,LIGHTGRAY);
	//bar(640-68-136-20,2,640-88,34);
	puthz(640-68-136-20,2,"个人中心",32,34,DARKGRAY);
	//bar(640-68,480-32,640,480);
	puthz(640-68,480-34,"退出",32,34,LIGHTGRAY);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640-68*2-20,480-34,"返回",32,34,LIGHTGRAY);
	puthz(20,40,"个人信息",32,34,BROWN);
}

/**
 * @brief input vaccine state
 * @param us pointer stores user info
 * @param Vaccine vaccine state(1 for yes; 2 for no)
 */
void input_vaccine(USER *us, int Vaccine)
{
	FILE* fp;
	USER u;
	int i, len;
	
	if ((fp = fopen("database\\UserData.dat", "rb+" )) == NULL)
	{
		printf("cannot open file UserData.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(USER);
	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(USER), SEEK_SET);
		fread(&u, sizeof(USER), 1, fp);
		if (strcmp(us->phone, u.phone) == 0)
		{
			if (Vaccine == 1)
			{
				strcpy(u.vaccine,"是");
			}
			else
			{
				strcpy(u.vaccine,"否");
			}
			fseek(fp, i * sizeof(USER), SEEK_SET);
			fwrite(&u, sizeof(USER), 1, fp);
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		delay(3000);
		exit(1);
	}
}

/**
 * @brief input living address info
 * @param us pointer stores user info
 * @param p living province
 * @param c living city
 */
void input_home(USER *us, char* p, char* c)
{
	FILE* fp;
	USER u;
	int i, len;
	
	if ((fp = fopen("database\\UserData.dat", "rb+" )) == NULL)
	{
		printf("cannot open file UserData.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(USER);
	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(USER), SEEK_SET);
		fread(&u, sizeof(USER), 1, fp);
		if (strcmp(us->phone, u.phone) == 0)
		{
			strcpy(u.province0,p);
			strcpy(u.city0,c);
			fseek(fp, i * sizeof(USER), SEEK_SET);
			fwrite(&u, sizeof(USER), 1, fp);
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		delay(3000);
		exit(1);
	}
}