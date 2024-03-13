/**
 * @file choose.c
 * @author yangchunru
 * @brief choose place or time and riskinfo input
 * @date 2021-04-24
 */
#include "public.h"
#include "choose.h"

/**
 * @brief show province and city for user to choose
 * @param Province 
 * @param City 
 * @param X the horizontal position of the choose box
 * @param Y the vertical position of the choose box
 * @param Flag check choose or not(1 for no;0 for yes)
 */
void showplace(char* Province, char* City, int X, int Y, int* Flag)
{
	FILE* fp;
	AREA a;
	int i, total, len, x=X+20, y=Y+20, state, p=1;
	char city[30] = {'\0'};
	char area[50] = {'\0'};
	int coordinate[34][4];	//[0] for x1;[1] for y1;[2] for x2;[3] for y2
	char PROVINCE[][20]={"北京","上海","天津","重庆",
	                       "香港","澳门",
						   "内蒙古","新疆维吾尔","广西壮族","西藏","宁夏回族",
						   "辽宁","吉林","黑龙江","河北","山西",
						   "陕西","甘肃","青海","山东","安徽",
						   "江苏","浙江","河南","湖北","湖南",
						   "江西","台湾","福建","云南","海南",
						   "四川","贵州","广东"};
	char PROVINCE1[][20]={"bj","sh","tj","cq",
	                        "xg","am",
							"nmg","xj","gx","xz","nx",
							"ln","jl","hlj","hebei","sx",
							"sx3","gs","qh","sd","ah",
							"js","zj","henan","hubei","hunan",
							"jx","tw","fj","yn","hainan",
							"sc","gz","gd"};
	if (strcmp(Province, "") == 0)	//show province
	{
		state = 1;
		total = 34;
		setfillstyle(SOLID_FILL, WHITE);
		bar(X,Y,X+370,Y+40+(total*(3*18+10)/330)*23-7);
		setlinestyle(SOLID_LINE,0,3);
		setcolor(DARKGRAY);
		rectangle(X,Y,X+370,Y+40+(total*(3*18+10)/330)*23-7);
		for (i = 0; i < 34; i++)
		{
			len = strlen(PROVINCE[i])/2;
			if ((x+18*len+10) < X+360)
			{
				coordinate[i][0] = x;
				coordinate[i][1] = y;
				coordinate[i][3] = y+16;
				puthz(x,y,PROVINCE[i],16,18,DARKGRAY);
				x=x+18*len+10;
				coordinate[i][2] = x-10;
			}
			else
			{
				y=y+23;
				x=X+20;
				coordinate[i][0] = x;
				coordinate[i][1] = y;
				coordinate[i][3] = y+16;
				puthz(x,y,PROVINCE[i],16,18,DARKGRAY);
				x=x+18*len+10;
				coordinate[i][2] = x-10;
			}
		}
	}
	else	//show city
	{
		state = 2;
		strcpy(area, "database\\place\\");
		for (i=0;i<34;i++)
		{
			if (strcmp(PROVINCE[i], Province) == 0)
			{
				strcat(area,PROVINCE1[i]);
				strcat(area,".dat");
			}
		}
		if ((fp = fopen(area, "rb" )) == NULL)
		{
			printf(area);
			delay(3000);
			exit(1);
		}
		fseek(fp, 0, SEEK_END);
		total = ftell(fp) / sizeof(AREA);
		setfillstyle(SOLID_FILL, WHITE);
		for (i = 0; i < total; i++)
		{
			fseek(fp, i * sizeof(AREA), SEEK_SET);
			if (!fread(&a, sizeof(AREA), 1, fp))
			{
				break;
			}
			len = strlen(a.city)/2;
			if ((x+18*len+10) < X+360)
			{
				x=x+18*len+10;
			}
			else
			{
				p++;
				y=y+23;
				x=X+20;
				x=x+18*len+10;
			}
		}
		bar(X,Y,X+370,Y+40+p*23-7);
		setlinestyle(SOLID_LINE,0,3);
		setcolor(DARKGRAY);
		rectangle(X,Y,X+370,Y+40+p*23-7);
		x=X+20;
		y=Y+20;
		for (i = 0; i < total; i++)
		{
			if (i == 11)
			{
				delay(100);
			}
			fseek(fp, i * sizeof(AREA), SEEK_SET);
			if (!fread(&a, sizeof(AREA), 1, fp))
			{
				break;
			}
			strcpy(city, a.city);
			len = strlen(city)/2;
			if ((x+18*len+10) < X+360)
			{
				coordinate[i][0] = x;
				coordinate[i][1] = y;
				coordinate[i][3] = y+16;
				puthz(x,y,city,16,18,DARKGRAY);
				x=x+18*len+10;
				coordinate[i][2] = x-10;
			}
			else
			{
				y=y+23;
				x=X+20;
				coordinate[i][0] = x;
				coordinate[i][1] = y;
				coordinate[i][3] = y+16;
				puthz(x,y,city,16,18,DARKGRAY);
				x=x+18*len+10;
				coordinate[i][2] = x-10;
			}
		}
		if (fclose(fp) != 0)
		{
			printf("\n cannot close Database");
			delay(3000);
			exit(1);
		}
	}
	while (*Flag)
	{
		newmouse(&MouseX, &MouseY, &press);
		if (mouse_press(X,Y,X+370,coordinate[total-1][3]) == 1)
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(X,Y,X+370,coordinate[total-1][3]) == 1);
			for (i = 0; i < total; i++)
			{
				if (MouseX > coordinate[i][0] && MouseX < coordinate[i][2] && MouseY> coordinate[i][1] && MouseY < coordinate[i][3])
				{
					if (state == 1)
					{
						strcpy(Province, PROVINCE[i]);
						*Flag = 0;
					}
					else
					{
						if ((fp = fopen(area, "rb" )) == NULL)
						{
							printf(area);
							delay(3000);
							exit(1);
						}
						fseek(fp, i * sizeof(AREA), SEEK_SET);
						fread(&a, sizeof(AREA), 1, fp);
						strcpy(City, a.city);
						*Flag = 0;
					}
					break;
				}
			}
		}
	}
}

/**
 * @brief show year month and date for user to choose
 * @param Year 
 * @param Month 
 * @param Date 
 * @param X the horizontal position of the choose box
 * @param Y the vertical position of the choose box
 * @param Flag check choose or not(1 for no;0 for yes)
 */
void showtime(char* Year, char* Month, char* Date, int X, int Y, int* Flag)
{
	int i, x=X+5, y=Y-3, YEAR=2019, MONTH=1, DATE=1, dateall;
	char year[10] = {'\0'};
	char month[5] = {'\0'};
	char date[5] = {'\0'};
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	if (Year[0] == '\0')	//show year
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(X,Y,X+60,Y+90);
		setlinestyle(SOLID_LINE,0,1);
		setcolor(DARKGRAY);
		rectangle(X,Y,X+60,Y+90);
		for (i = 0; i < 5; i++)
		{
			outtextxy(x,y,itoa(YEAR, year, 10));
			y=y+18;
			YEAR++;
		}
	}
	else if (strcmp(Month, "") == 0)	//show month
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(X+2+15*5,Y,X+2+15*5+30,Y+12*18);
		setlinestyle(SOLID_LINE,0,1);
		setcolor(DARKGRAY);
		rectangle(X+15*5+2,Y,X+15*5+2+30,Y+12*18);
		for (i = 0; i < 12; i++)
		{
			outtextxy(x+15*5+2,y,itoa(MONTH, month, 10));
			y=y+18;
			MONTH++;
		}
	}
	else	//show date
	{
		setfillstyle(SOLID_FILL, WHITE);
		setlinestyle(SOLID_LINE,0,1);
		setcolor(DARKGRAY);
		bar(X+15*8+4,Y,X+15*8+4+65,Y+16*18);
		rectangle(X+15*8+4,Y,X+15*8+4+65,Y+16*18);
		if ((strcmp(Year, "2020") == 0) && (strcmp(Month, "2") == 0))
		{
			dateall = 29;
			for (i = 0; i < 16; i++)
			{
				outtextxy(x+15*8+4,y,itoa(DATE, date, 10));
				y=y+18;
				DATE++;
			}
			y=Y-3;
			for (i = 0; i < 13; i++)
			{
				outtextxy(x+35+15*8+4,y,itoa(DATE, date, 10));
				y=y+18;
				DATE++;
			}
		}
		else if (strcmp(Month, "2") == 0)
		{
			dateall = 28;
			for (i = 0; i < 16; i++)
			{
				outtextxy(x+15*8+4,y,itoa(DATE, date, 10));
				y=y+18;
				DATE++;
			}
			y=Y-3;
			for (i = 0; i < 12; i++)
			{
				outtextxy(x+35+15*8+4,y,itoa(DATE, date, 10));
				y=y+18;
				DATE++;
			}
		}
		else if ((strcmp(Month, "4") == 0) || (strcmp(Month, "6") == 0) || (strcmp(Month, "9") == 0) || (strcmp(Month, "11") == 0))
		{
			dateall = 30;
			for (i = 0; i < 16; i++)
			{
				outtextxy(x+15*8+4,y,itoa(DATE, date, 10));
				y=y+18;
				DATE++;
			}
			y=Y-3;
			for (i = 0; i < 14; i++)
			{
				outtextxy(x+35+15*8+4,y,itoa(DATE, date, 10));
				y=y+18;
				DATE++;
			}
		}
		else
		{
			dateall = 31;
			for (i = 0; i < 16; i++)
			{
				outtextxy(x+15*8+4,y,itoa(DATE, date, 10));
				y=y+18;
				DATE++;
			}
			y=Y-3;
			for (i = 0; i < 15; i++)
			{
				outtextxy(x+35+15*8+4,y,itoa(DATE, date, 10));
				y=y+18;
				DATE++;
			}
		}
	}
	while (*Flag)
	{
		newmouse(&MouseX, &MouseY, &press);
		if (strcmp(Year, "") == 0)
		{
			if (mouse_press(X,Y,X+60,Y+90) == 1)
			{
				do {
					newmouse(&MouseX, &MouseY, &press);
				}while (mouse_press(X,Y,X+60,Y+90) == 1);
				YEAR=2019;
				for (i = 0; i < 5; i++)
				{
					if (MouseY> Y && MouseY < Y+18+i*18)
					{
						itoa(YEAR,Year,10);
						*Flag = 0;
						break;
					}
					YEAR++;
				}
			}
		}
		else if (strcmp(Month, "") == 0)
		{
			if (mouse_press(X+15*5+2,Y,X+15*5+2+30,Y+12*18) == 1)
			{
				do {
					newmouse(&MouseX, &MouseY, &press);
				}while (mouse_press(X+15*5+2,Y,X+15*5+2+30,Y+12*18) == 1);
				MONTH=1;
				for (i = 0; i < 12; i++)
				{
					if (MouseY> Y && MouseY < Y+18+i*18)
					{
						itoa(MONTH,Month,10);
						*Flag = 0;
						break;
					}
					MONTH++;
				}
			}
		}
		else
		{
			if (mouse_press(X+15*8+4,Y,X+15*8+4+65,Y+16*18) == 1)
			{
				do {
					newmouse(&MouseX, &MouseY, &press);
				}while (mouse_press(X+15*8+4,Y,X+15*8+4+65,Y+16*18) == 1);
				DATE=1;
				for (i = 0; i < 16; i++)
				{
					if (MouseX > X+15*8+4 && MouseX < X+15*8+4+30 && MouseY> Y && MouseY < Y+18+i*18)
					{
						itoa(DATE,Date,10);
						*Flag = 0;
						break;
					}
					DATE++;
				}
				for (i = 0; i < dateall-16; i++)
				{
					if (MouseX > X+15*8+4+35 && MouseX < X+15*8+4+65 && MouseY> Y && MouseY < Y+18+i*18)
					{
						itoa(DATE,Date,10);
						*Flag = 0;
						break;
					}
					DATE++;
				}
			}
		}
	}
}

/**
 * @brief input new riskinfo
 * @param I the line of the city been changed
 * @param Flag whether it is in edit state(1 for yes;0 for no)
 * @param Province current display province
 * @param P current page
 */
void change_riskinfo(int I, int* Flag, char* Province, int P)
{
	FILE* fp;
	SEARCH s;
	AREA a;
	int i;
	char filename[50] = {'\0'};
	char bentunew[20] = {'\0'};
	char wzznew[20] = {'\0'};
	char totalnew[20] = {'\0'};
	char existing[20] = {'\0'};
	char rank[5] = {'\0'};
	int state = 1;//risk rank(1 for low;2 for middle;3 for high)

	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	setlinestyle(SOLID_LINE,0,3);
	bar(320-125,295-70,320+125,295+90);
	rectangle(320-125,295-70,320+125,295+90);
	puthz(320-105+1,295-60+1,"本土新增",16,18,DARKGRAY);
	puthz(320-105,295-60,"本土新增",16,18,WHITE);
	puthz(320-105+1,295-35+1,"无症状新增",16,18,DARKGRAY);
	puthz(320-105,295-35,"无症状新增",16,18,WHITE);
	puthz(320-105+1,295-10+1,"总新增确诊",16,18,DARKGRAY);
	puthz(320-105,295-10,"总新增确诊",16,18,WHITE);
	puthz(320-105+1,295+15+1,"现存确诊",16,18,DARKGRAY);
	puthz(320-105,295+15,"现存确诊",16,18,WHITE);
	puthz(320-105+1,295+40+1,"风险等级",16,18,DARKGRAY);
	puthz(320-105,295+40,"风险等级",16,18,WHITE);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	puthz(320-50,295+25+41,"取消",16,18,WHITE);
	puthz(320+50-36,295+25+41,"确定",16,18,WHITE);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	bar(320-105+4*18+5,295-60,320-105+4*18+5+74,295-60+20);
	bar(320-105+5*18+5,295-35,320-105+5*18+5+74,295-35+20);
	bar(320-105+5*18+5,295-10,320-105+5*18+5+74,295-10+20);
	bar(320-105+4*18+5,295+15,320-105+4*18+5+74,295+15+20);
	fillellipse(320-105+4*18+5+10,295+40+7,4,4);
	fillellipse(320-105+4*18+5+10+40,295+40+7,4,4);
	fillellipse(320-105+4*18+5+10+80,295+40+7,4,4);
	puthz(320-105+4*18+5+10+10,295+40,"低",16,18,WHITE);
	puthz(320-105+4*18+5+10+50,295+40,"中",16,18,WHITE);
	puthz(320-105+4*18+5+10+90,295+40,"高",16,18,WHITE);
	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, DARKGRAY);
	fillellipse(320-105+4*18+5+10,295+40+7,2,2);

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
		if (strcmp(Province, s.provinceall) == 0)
		{
			strcpy(filename, "database\\place\\");
			strcat(filename,s.provinceall1);
			strcat(filename,".dat");
			if (fclose(fp) != 0)
			{
				printf("\n cannot close province.dat");
				delay(3000);
				exit(1);
			}
			break;
		}
	}
	if ((fp = fopen(filename, "rb+" )) == NULL)
	{
		printf(filename);
		delay(3000);
		exit(1);
	}

	while (*Flag)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(320-50,295+25+40,320-10,295+25+60) == 1)	//cancel button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(320-50,295+25+40,320-10,295+25+60) == 1);
			if (fclose(fp) != 0)
			{
				printf("\n cannot close province.dat");
				delay(3000);
				exit(1);
			}
			*Flag = 0;
        } 
		else if (mouse_press(320-105+4*18+5,295-60,320-105+4*18+5+70,295-60+18) == 1)	//input bentunew number
		{
			bentunew[0] = '\0';
			inputadmin(bentunew, 320-105+4*18+5,295-60, 3, WHITE, 16);
		}
		else if (mouse_press(320-105+5*18+5,295-35,320-105+5*18+5+60,295-35+18) == 1)	//input wuzhengzhuangnew number
		{
			wzznew[0] = '\0';
			inputadmin(wzznew, 320-105+5*18+5,295-35, 3, WHITE, 16);
		}
		else if (mouse_press(320-105+5*18+5,295-10,320-105+5*18+5+60,295-10+18) == 1)	//input totalnew number
		{
			totalnew[0] = '\0';
			inputadmin(totalnew, 320-105+5*18+5,295-10, 3, WHITE, 16);
		}
		else if (mouse_press(320-105+4*18+5,295+15,320-105+4*18+5+60,295+15+18) == 1)	//input existing number
		{
			existing[0] = '\0';
			inputadmin(existing, 320-105+4*18+5,295+15, 3, WHITE, 16);
		}
		else if (mouse_press(320-105+4*18+10,295+40+2,320-105+4*18+10+10,295+40+12) == 1)	//risk rank-low
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(320-105+4*18+5+10,295+40+7,4,4);
			fillellipse(320-105+4*18+5+10+40,295+40+7,4,4);
			fillellipse(320-105+4*18+5+10+80,295+40+7,4,4);
			setcolor(DARKGRAY);
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(320-105+4*18+5+10,295+40+7,2,2);
			state = 1;
		}
		else if (mouse_press(320-105+4*18+5+5+40,295+40+2,320-105+4*18+10+10+40,295+40+12) == 1)	//risk rank-middle
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(320-105+4*18+5+10,295+40+7,4,4);
			fillellipse(320-105+4*18+5+10+40,295+40+7,4,4);
			fillellipse(320-105+4*18+5+10+80,295+40+7,4,4);
			setcolor(DARKGRAY);
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(320-105+4*18+5+10+40,295+40+7,2,2);
			state = 2;
		}
		else if (mouse_press(320-105+4*18+5+5+80,295+40+2,320-105+4*18+10+10+80,295+40+12) == 1)	//risk rank-high
		{
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(320-105+4*18+5+10,295+40+7,4,4);
			fillellipse(320-105+4*18+5+10+40,295+40+7,4,4);
			fillellipse(320-105+4*18+5+10+80,295+40+7,4,4);
			setcolor(DARKGRAY);
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(320-105+4*18+5+10+80,295+40+7,2,2);
			state = 3;
		}
		else if(mouse_press(320+50-36,295+25+40,320+90-36,295+25+60) == 1)	//confirm button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(320+50-36,295+25+40,320+90-36,295+25+60) == 1);
			i = 13*P+I;
			fseek(fp, i * sizeof(AREA), SEEK_SET);
			if (fread(&a, sizeof(AREA), 1, fp))
			{
				if (strcmp(bentunew,"") != 0)
				{
					strcpy(a.bentunew, bentunew);
				}
				if (strcmp(wzznew,"") != 0)
				{
					strcpy(a.wzznew, wzznew);
				}
				if (strcmp(totalnew,"") != 0)
				{
					strcpy(a.totalnew, totalnew);
				}
				if (strcmp(existing,"") != 0)
				{
					strcpy(a.existing, existing);
				}
				itoa(state, rank, 10);
				strcpy(a.rank, rank);
				fseek(fp, i * sizeof(AREA), SEEK_SET);
				fwrite(&a, sizeof(AREA), 1, fp);
				fflush(fp);
			}
			else
			{
				setfillstyle(SOLID_FILL, WHITE);
				bar(250,200,390,220);
				puthz(320-18*3,201,"写入位置无效",16,18,RED);
				delay(300);
			}
			if (fclose(fp) != 0)
			{
				printf("\n cannot close province.dat");
				delay(3000);
				exit(1);
			}
			*Flag = 0;
        } 
	}
}