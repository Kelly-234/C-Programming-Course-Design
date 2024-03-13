/**
 * @file jkm.c
 * @author yangchunru
 * @brief show jkm and xcm according to user data and user's travel data
 * @date 2021-04-30
 */
#include "public.h"
#include "jkm.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p9_jkm(USER *u, int* Flag)
{
	FILE* fp;
	USER us;
	int i, len, page=8;
	int flag;	//whether the trip record is empty(1 for no; 2 for yes)
	char Name[20] = { '\0' };	//store user's name
	char Health[5] = { '\0' };	//store usre's health condition(1 for health(green); 2 for suspected(yellow); 3 for defined(red))
	
	if ((fp = fopen("database\\UserData.dat", "rb" )) == NULL)
	{
		printf("cannot open file UserData.dat in jkm.c");
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
			strcpy(Health,us.condition);
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
	jkm_screen(Name);
	flag = Gettravelinfo(i);
	draw_jkm(Health);
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
		else if(mouse_press(125+26*3+20+150+50+20+20,350,125+26*3+20+150+50+20+60,368) == 1)	//update button(redraw jkm)
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(125+26*3+20+150+50+20+20,350,125+26*3+20+150+50+20+60,368) == 1);
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(80,140,80+200,140+200);
			bar(125+26*3+20,344,125+26*3+20+150+50+20+15,350+18);
			draw_jkm(Health);
		}
		else if(mouse_press(640-68,480-34,640,480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
		else if((mouse_press(95+18*12+10+5-20+18*10,350+70,95+18*12+10+5-20+18*10+18*3,350+70+18) == 1) && ((flag == 0) || (flag == 1)))	//fill in itinerary info button(go to record.c)
		{
			page = 11;
			return page;
		}
		else if((mouse_press(95+18*12+10+5-20+18*10,350+50,95+18*12+10+5-20+18*10+18*3,350+50+18) == 1) && (flag == 0))	//fill in living address info button(go to xxchange.c)
		{
			page = 10;
			return page;
		}
	}
}

/**
 * @param n user's name
 */
void jkm_screen(char* n)
{
	cleardevice();
	setbkcolor(WHITE);
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
	puthz(20,40,"健康码及行程码",32,34,LIGHTGREEN);
}

/**
 * @brief get user's newest travel info
 * @param I the rank of the user in total data file, also the file name serial number of corresponding travel info file
 * @return int return a value to sign whether the trip record is empty(1 for no; 2 for yes)
 */
int Gettravelinfo(int I)
{
	FILE* fp;
	TRAVEL t;
	SEARCH s;
	AREA a;
	USER u;
	int i, len;
	int bk1[] = {420+40,240-50,460+57,240-50+57,460+57-15,240-50+57+15,460-15,240-50+15,460,240-50};
	int bk2[] = {420+40,240-50,460-57,240-50+57,460-57+15,240-50+57+15,460+15,240-50+15,460,240-50};
	int bk3[] = {460-25,240-45,460+25,240-45,470,240+10,450,240+10,460-25,240-45};
	int flag = 2;	//whether the trip record is empty and whether the living address info has been filled(0 for both are null; 1 for only record is null; 2 for both are filled)
	char Rank[5] = { '\0' };	//store the risk rank of the newest travel city
	char filename[50] = { '\0' };	//store the name of the file to open
	char province[30] = { '\0' };	//store the newest travel province or living province
	char city[30] = { '\0' };	//store the newest travel city or living city
	char name[5] = { '\0' };	//store the string convert by user's serial number
	char place[70] = { '\0' };	//store the whole name the travel info to show
	char newest_time1[10] = { '\0' };	//store the year of the newest one
	char newest_time2[5] = { '\0' };	//store the month of the newest one
	char newest_time3[5] = { '\0' };	//store the date of the newest one
	
	//get user's travel info
	strcpy(filename, "database\\travel\\User\\");
	itoa(I, name, 10);
	strcat(filename, name);
	strcat(filename, ".dat");
	if ((fp = fopen(filename, "rb" )) == NULL)
	{
		printf(filename);
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(TRAVEL);
	if (len > 0)	//trip record do not empty, then get the newest travel info
	{
		for (i=0;i<len;i++)
		{
			fseek(fp, i * sizeof(TRAVEL), SEEK_SET);
			fread(&t, sizeof(TRAVEL), 1, fp);
			if (traveltime_compare(newest_time1, newest_time2, newest_time3, t.time2_1, t.time2_2, t.time2_3))
			{
				strcpy(newest_time1,t.time2_1);
				strcpy(newest_time2,t.time2_2);
				strcpy(newest_time3,t.time2_3);
				strcpy(province,t.province);
				strcpy(city,t.city);
			}
		}
		if (!time_compare(newest_time1, newest_time2, newest_time3, 1))	//the latest travel return time is more than 14 days ago-travel info invalid
		{
			flag = 1;
		}
	}
	else	//travel info is null
	{
		flag = 1;
	}
	if (fclose(fp) != 0)
	{
		printf(filename);
		delay(3000);
		exit(1);
	}
	if (flag == 1)	//travel info is null, get living address info
	{
		if ((fp = fopen("database\\UserData.dat", "rb" )) == NULL)
		{
			printf("cannot open file UserData.dat in jkm.c");
			delay(3000);
			exit(1);
		}
		fseek(fp, I * sizeof(USER), SEEK_SET);
		fread(&u, sizeof(USER), 1, fp);
		strcpy(province,u.province0);
		strcpy(city,u.city0);
		if (fclose(fp) != 0)
		{
			printf(filename);
			delay(3000);
			exit(1);
		}
		puthz(95+18*12+10+5-20,350+70,"防疫行程卡无记录",16,18,LIGHTRED);
		puthz(95+18*12+10+5-20+18*10,350+70,"去填写",16,18,LIGHTGREEN);
		if (strcmp(u.province0, "") == 0)	//living address info is null
		{
			puthz(95+18*12+10+5-20,350+50,"常住地信息未填写",16,18,LIGHTRED);
			puthz(95+18*12+10+5-20+18*10,350+50,"去填写",16,18,LIGHTGREEN);
			flag = 0;
		}
	}
	puthz(95-18,350+30+20,"您十四天内曾到达或途经",16,18,DARKGRAY);
	if (flag)	//both travel info and living address info are not empty, get the risk rank of the city
	{
		if ((strcmp(province, "香港") == 0) || (strcmp(province, "澳门") == 0))
		{
			strcpy(place, province);
			strcat(place, "特别行政区");
		}
		else if (strcmp(province, city) == 0)
		{
			strcpy(place, province);
			strcat(place, "市");
		}
		else if ((strcmp(province, "新疆维吾尔") == 0) || (strcmp(province, "西藏") == 0) || (strcmp(province, "内蒙古") == 0) || (strcmp(province, "广西壮族") == 0) || (strcmp(province, "宁夏回族") == 0))
		{
			strcpy(place, province);
			strcat(place, city);
			strcat(place, "自治区");
		}
		else
		{
			strcpy(place, province);
			strcat(place, "省");
			strcat(place, city);
			strcat(place, "市");
		}
		if ((fp = fopen("database\\place\\province.dat", "rb" )) == NULL)//建立数据库
		{
			printf("cannot open database\\place\\province.dat");
			delay(3000);
			exit(1);
		}
		for (i=0;i<34;i++)
		{
			fseek(fp, i * sizeof(SEARCH), SEEK_SET);
			fread(&s, sizeof(SEARCH), 1, fp);
			if (strcmp(s.provinceall,province) == 0)
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
		for (i=0;i<len;i++)
		{
			fseek(fp, i * sizeof(AREA), SEEK_SET);
			fread(&a, sizeof(AREA), 1, fp);
			if (strcmp(a.city, city) == 0)
			{
				strcpy(Rank, a.rank);
				break;
			}
		}
		if (fclose(fp) != 0)
		{
			printf(filename);
			delay(3000);
			exit(1);
		}
		if(strcmp(Rank, "3") == 0)
		{
			puthz(95+18*10+(288-strlen(place)*9)/2,350+50,place,16,18,RED);
		}
		else if(strcmp(Rank, "2") == 0)
		{
			puthz(95+18*10+(288-strlen(place)*9)/2,350+50,place,16,18,YELLOW);
		}
		else
		{
			puthz(95+18*10+(288-strlen(place)*9)/2,350+50,place,16,18,GREEN);
		}
	}
	if (flag)
	{
		if(strcmp(Rank, "3") == 0)
		{
			setcolor(RED);
			setfillstyle(SOLID_FILL, RED);
		}
		else if(strcmp(Rank, "2") == 0)
		{
			setcolor(YELLOW);
			setfillstyle(SOLID_FILL, YELLOW);
		}
		else
		{
			setcolor(GREEN);
			setfillstyle(SOLID_FILL, GREEN);
		}
		fillellipse(460,240,100,100);
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		fillellipse(460,240,80,80);
		if(strcmp(Rank, "3") == 0)
		{
			setcolor(RED);
			setfillstyle(SOLID_FILL, RED);
		}
		else if(strcmp(Rank, "2") == 0)
		{
			setcolor(YELLOW);
			setfillstyle(SOLID_FILL, YELLOW);
		}
		else
		{
			setcolor(GREEN);
			setfillstyle(SOLID_FILL, GREEN);
		}
		bar(450,240-40,470,240+80);
		fillpoly(5,bk1);
		fillpoly(5,bk2);
	}
	else
	{
		setcolor(LIGHTRED);
		setfillstyle(SOLID_FILL, LIGHTRED);
		fillellipse(460,240,100,100);
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		fillellipse(460,240,80,80);
		setcolor(LIGHTRED);
		setfillstyle(SOLID_FILL, LIGHTRED);
		fillellipse(460,240-45,25,25);
		fillellipse(460,240+10,10,10);
		fillellipse(460,240+50,20,20);
		fillpoly(5,bk3);		
	}
	return flag;
}

/**
 * @param h user's health condition
 */
void draw_jkm(char* h)
{
	int i,j,n;
	char Time[40] = { '\0' };
	char strategy_color[3] = {GREEN, YELLOW, RED};	//the color of the jkm
	
	setcolor(strategy_color[atoi(h)-1]);
	setfillstyle(SOLID_FILL, strategy_color[atoi(h)-1]);
	srand((unsigned)time(NULL));
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			n = rand() % 20;
			if(n<10)
			{
				bar(80+i*10,140+j*10,80+(i+1)*10,140+(j+1)*10);
			}
		}
	}
	bar(80,140,80+50,140+50);
	bar(280-50,140,280,140+50);
	bar(80,340-50,80+50,340);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	bar(90,150,120,180);
	bar(280-40,150,270,180);
	bar(90,340-40,120,330);
	setcolor(strategy_color[atoi(h)-1]);
	setfillstyle(SOLID_FILL, strategy_color[atoi(h)-1]);
	bar(100,160,110,170);
	bar(250,160,260,170);
	bar(100,310,110,320);
	puthz(125,350,"更新于",16,18,DARKGRAY);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);
	setcolor(DARKGRAY);
	get_time(Time);
	outtextxy(125+26*3+20,344,Time);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(125+26*3+20+150+50+20+20,350,125+26*3+20+150+50+20+60,368);
	puthz(125+26*3+20+150+50+20+20+4,350+1,"更新",16,18,WHITE);
	puthz(95+2.5*18,350+30,"健康状况",16,18,DARKGRAY);
	if(strcmp(h, "3") == 0)
	{
	    puthz(95+18*9+(288-3*18)/2,350+30,"已确诊",16,18,RED);
	}
	else if(strcmp(h, "2") == 0)
	{
	    puthz(95+18*9+(288-14*18)/2,350+30,"有密切接触经历并处于隔离期间",16,18,YELLOW);
	}
	else
	{
        puthz(95+18*9+(288-36)/2,350+30,"健康",16,18,GREEN);
	}
}