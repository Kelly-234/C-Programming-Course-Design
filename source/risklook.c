/**
 * @file risklook.c
 * @author yangchunru
 * @brief enquiry risk rank of each city
 * @date 2021-04-28
 */
#include "public.h"
#include "risklook.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p10_risklook(USER *u, int* Flag)
{
	FILE* fp;
	USER us;
	int i, len, page = 9;
	char Name[10] = { '\0' };
	char province[30] = { '\0' };
	char city[30] = { '\0' };
	int flag = 0;	//1 for choosing province or city now; 0 for not
	
	//get user's name
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
	risklook_screen(Name, *Flag);
	delay(300);
	
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to home.c when not login; go to grhome.c when login)
		{
			if (*Flag == 1)	//be logged in
				page = 3;
			else
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
		else if(mouse_press(60+26*4+10,80,60+26*4+10+26*5+4,80+26) == 1)	//choose province
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(60+26*4+10,80,60+26*4+10+26*5+4,80+26) == 1);
			flag = 1;
			province[0] = '\0';
			clrmous(MouseX,MouseY);
			showplace(province, city, 60+26*4+10, 80+26, &flag);
			clrmous(MouseX,MouseY);
			risklook_screen(Name, *Flag);
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(60+26*4+10,80,60+26*4+10+26*5+4,80+26);
			bar(60+26*4+10+26*5+4+5,80,60+26*4+10+26*5+9+4+26*8,80+26);
			puthz(60+26*4+10+2+(5*26-strlen(province)/2*26)/2,80+1,province,24,26,WHITE);
			puthz(60+26*4+10+26*5+4+5+52+2,80+1,"选择城市",24,26,WHITE);
		}
		if(mouse_press(60+26*4+10+26*5+4+5,80,60+26*4+10+26*5+9+4+26*8,80+26) == 1)	//choose city
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(60+26*4+10+26*5+4+5,80,60+26*4+10+26*5+9+4+26*8,80+26) == 1);
			flag = 1;
			city[0] = '\0';
			clrmous(MouseX,MouseY);
			showplace(province, city, 60+26*4+10+26*5+9+4+26*8-370, 80+26, &flag);
			clrmous(MouseX,MouseY);
			risklook_screen(Name, *Flag);
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(60+26*4+10,80,60+26*4+10+26*5+4,80+26);
			bar(60+26*4+10+26*5+4+5,80,60+26*4+10+26*5+9+4+26*8,80+26);
			puthz(60+26*4+10+2+(5*26-strlen(province)/2*26)/2,80+1,province,24,26,WHITE);
			puthz(60+26*4+10+26*5+4+5+2+(8*26-strlen(city)/2*26)/2,80+1,city,24,26,WHITE);
		}
		else if(mouse_press(640-96,77,640-60,83+26) == 1)	//enquiry button
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(640-96,77,640-60,83+26) == 1);
			if (strcmp(province, "") == 0)
			{
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0,116,640,445);
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
				bar(250,220,390,260);
				setlinestyle(SOLID_LINE,0,3);
				setcolor(DARKGRAY);
				rectangle(250,220,390,260);
				puthz(320-18*3,240-9,"请先选择城市",16,18,RED);
				delay(2000);
				bar(245,215,395,265);
			}
			else	//show risk info
			{
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				risklook_screen(Name, *Flag);
				result(province, city);
				strcpy(province,"");
				strcpy(city,"");
				setcolor(LIGHTGRAY);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(60+26*4+10,80,60+26*4+10+26*5+4,80+26);
				puthz(60+26*4+10+15,80+1,"选择省份",24,26,WHITE);
				bar(60+26*4+10+26*5+4+5,80,60+26*4+10+26*5+9+4+26*8,80+26);
				puthz(60+26*4+10+26*5+4+5+52+2,80+1,"选择城市",24,26,WHITE);
			}
		}
	}
}

/**
 * @param n user's name
 * @param flag 1 for be logged in; 2 for not
 */
void risklook_screen(char* n, int flag)
{
	int bk[]={569,95,569+8,95+8,569+8-4,95+8+4,569-4,95+4,569,95};

	cleardevice();
	setbkcolor(WHITE);
	if (flag == 1)
	{
		//bar(640-68,2,640,34);
		puthz(640-68,2,"登出",32,34,LIGHTGRAY);
		//bar(640-68-136-20,2,640-88,34);
		puthz(640-68-136-20,2,"个人中心",32,34,DARKGRAY);
		//bar(640-68-136-20-102-20,2,640-68-136-40,34);
		puthz(640-68-136-20-102-20,2,n,32,34,LIGHTGRAY);
	}
	//bar(640-68,480-32,640,480);
	puthz(640-68,480-34,"退出",32,34,LIGHTGRAY);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640-68*2-20,480-34,"返回",32,34,LIGHTGRAY);
	puthz(20,40,"区域疫情风险等级查询",32,34,LIGHTBLUE);
	puthz(60,81,"查询地区",24,26,DARKGRAY);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(60+26*4+10,80,60+26*4+10+26*5+4,80+26);
	puthz(60+26*4+10+15,80+1,"选择省份",24,26,WHITE);
	bar(60+26*4+10+26*5+4+5,80,60+26*4+10+26*5+9+4+26*8,80+26);
	puthz(60+26*4+10+26*5+4+5+52+2,80+1,"选择城市",24,26,WHITE);
	bar(640-96,77,640-60,83+26);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(580-40+19,75+15,11,11);
	fillpoly(5,bk);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	fillellipse(580-40+19,75+15,5,5);
}

/**
 * @brief get and show the risk rank of the inquired city
 * @param Province province name of the place
 * @param City city name of the place
 */
void result(char* Province, char* City)
{
	FILE* fp;
	SEARCH s;
	AREA a;
	ADMIN ad;
	int i, j, len;
	int bk[]={255,260,305,300,380,210,380+15,210+15,305,300+30,255-15,260+15,255,260};
	int bk2[]={350,200,290,200,310,290,330,290,350,200};
	int bk3[]={370+10.6,210+10.6,270+10.6,310+10.6,270-10.6,310-10.6,370-10.6,210-10.6,370+10.6,210+10.6};
	int bk4[]={270-10.6,210+10.6,370-10.6,310+10.6,370+10.6,310-10.6,270+10.6,210-10.6,270-10.6,210+10.6};
	char place[60] = { '\0' };
	char filename[50] = { '\0' };
	if ((strcmp(Province, "香港") == 0) || (strcmp(Province, "澳门") == 0))
	{
		strcpy(place,Province);
		strcat(place, "特别行政区");
	}
	else if (strcmp(Province, City) == 0)
	{
		strcpy(place, Province);
		strcat(place, "市");
	}
	else if ((strcmp(Province, "新疆维吾尔") == 0) || (strcmp(Province, "西藏") == 0) || (strcmp(Province, "内蒙古") == 0) || (strcmp(Province, "广西壮族") == 0) || (strcmp(Province, "宁夏回族") == 0))
	{
		strcpy(place, Province);
		strcat(place, City);
		strcat(place, "自治区");
	}
	else
	{
		strcpy(place, Province);
		strcat(place, "省");
		strcat(place, City);
		strcat(place, "市");
	}
	puthz(320-strlen(place)*34/4,120,place,32,34,DARKGRAY);
	if ((fp = fopen("database\\place\\province.dat", "rb" )) == NULL)
	{
		printf("cannot open database\\place\\province.dat");
		delay(3000);
		exit(1);
	}
	for (i=0;i<34;i++)
	{
		fseek(fp, i * sizeof(SEARCH), SEEK_SET);
		fread(&s, sizeof(SEARCH), 1, fp);
		if (strcmp(Province,s.provinceall) == 0)
		{
			strcpy(filename, "database\\place\\");
			strcat(filename,s.provinceall1);
			strcat(filename,".dat");
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close province.dat");
		delay(3000);
		exit(1);
	}
	if ((fp = fopen(filename, "rb" )) == NULL)
	{
		printf(filename);
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(AREA);
	for (j=0;j<len;j++)
	{
		fseek(fp, j * sizeof(AREA), SEEK_SET);
		fread(&a, sizeof(AREA), 1, fp);
		if (strcmp(a.city, City) == 0)
		{
			if (strcmp(a.rank, "1") == 0)
			{
				setcolor(LIGHTGREEN);
				setfillstyle(SOLID_FILL, LIGHTGREEN);
				fillellipse(320,260,100,100);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				fillpoly(7,bk);
				fillellipse(255-7.5,260+7.5,10.6,10.6);
				fillellipse(380+7.5,210+7.5,10.6,10.6);
				setcolor(LIGHTGREEN);
				setfillstyle(SOLID_FILL, LIGHTGREEN);
				bar(305-15,300+23,320,330);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				sector(304,300+15,180,360,10.6,10.6);
				puthz(320-34*1.5,370,"低风险",32,34,LIGHTGREEN);
			}
			else if (strcmp(a.rank, "2") == 0)
			{
				setcolor(YELLOW);
				setfillstyle(SOLID_FILL, YELLOW);
				fillellipse(320,260,100,100);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				sector(320,260-60,0,180,30,30);
				sector(320,260+30,180,360,10,10);
				fillpoly(5,bk2);
				fillellipse(320,260+70,15,15);
				puthz(320-34*1.5,370,"中风险",32,34,YELLOW);
			}
			else if (strcmp(a.rank, "3") == 0)
			{
				setcolor(RED);
				setfillstyle(SOLID_FILL, RED);
				fillellipse(320,260,100,100);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				fillellipse(320+50,260+50,15,15);
				fillellipse(320+50,260-50,15,15);
				fillellipse(320-50,260+50,15,15);
				fillellipse(320-50,260-50,15,15);
				fillpoly(5,bk3);
				fillpoly(5,bk4);
				puthz(320-34*1.5,370,"高风险",32,34,RED);
			}
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf(filename);
		delay(3000);
		exit(1);
	}
	puthz(320-18*5.5-4,370+36,"截至",16,18,DARKGRAY);
	puthz(320-18*8.5,370+34+5+16+5,"有关信息来自各地确定的疫情风险等级",16,18,DARKGRAY);
	if ((fp = fopen("database\\Admin.dat", "rb" )) == NULL)
	{
		printf("cannot open database\\Admin.dat");
		delay(3000);
		exit(1);
	}
	i=0;
	fseek(fp, i * sizeof(ADMIN), SEEK_SET);
	fread(&ad, sizeof(ADMIN), 1, fp);
	setcolor(DARKGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(320-18*3.5-4,370+36-5,ad.time_rankinfo);
	if (fclose(fp) != 0)
	{
		printf("cannot open database\\Admin.dat");
		delay(3000);
		exit(1);
	}
}