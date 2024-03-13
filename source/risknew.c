/**
 * @file risknew.c
 * @author yangchunru
 * @brief check and update riskinfo(admin)
 * @date 2021-04-23
 */
#include "public.h"
#include "risknew.h"

int p13_risknew(void)
{
	FILE* fp;
	ADMIN ad;
	int i, page = 12;
	int total= 0;	//total page number
	int p = 0;	//current page
	int term;	//max line number of the last page
	int item = 0;	//the line number of the one being changing
	char province[30] = { '\0' };
	int flag = 2;	//0 for checking state; 1 for changing state; 2 for initialization state
	char Time[100]={'\0'};	//record the logout time

    clrmous(MouseX,MouseY);
	risknew_screen();
    delay(300);
	
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(640-68,2,640,34) == 1)	//log out button(go to welcome.c)
        {
			if ((fp = fopen("database\\Admin.dat", "rb+" )) == NULL)
			{
				printf("cannot open database\\Admin.dat");
				delay(3000);
				exit(1);
			}
			i=0;
			fseek(fp, i * sizeof(ADMIN), SEEK_SET);
			fread(&ad, sizeof(ADMIN), 1, fp);
			get_time(Time);
			strcpy(ad.time_rankinfo,Time);
			fseek(fp, i * sizeof(ADMIN), SEEK_SET);
			fwrite(&ad, sizeof(ADMIN), 1, fp);
			if (fclose(fp) != 0)
			{
				printf("cannot open database\\Admin.dat");
				delay(3000);
				exit(1);
			}
			page = 0;
			return page;
		}
		else if(mouse_press(640-68,480-32,640,480) == 1)	//exit button
        {
			page = 18;
			return page;
        }
		else if(mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to glhome.c)
        {
			page = 2;
			return page;
        }
		else if(mouse_press(20+34*5+20,80,20+34*5+20+34*5+20,114) == 1)	//input province name
        {
			province[0] = '\0';
			setfillstyle(SOLID_FILL, LIGHTGRAY);
  			bar(20+34*5+20,80,20+34*5+20+34*5+20,114);
			hz_input(20+34*5+26,82,20+34*5+20+34*5+20,114,province,0,LIGHTGRAY,WHITE,32);
        } 
		else if(mouse_press(20+34*5+20+34*5+20+20,80,20+34*5+20+34*5+20+20+70,114) == 1)	//confirm button
        {
			clrmous(MouseX,MouseY);
			if (strcmp(province, "") == 0)
			{
				setcolor(DARKGRAY);
				setfillstyle(SOLID_FILL, WHITE);	
				setlinestyle(SOLID_LINE,0,3);
				bar(320-70,220,320+70,260);
				rectangle(320-70,220,320+70,260);
				puthz(320-2.5*18,240-9,"未输入省份",16,18,RED);
				delay(1500);
				risknew_screen();
			}
			else
			{
				flag = 0;
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0,120-2+52,640,440+2);
				setcolor(DARKGRAY);
				setfillstyle(SOLID_FILL, DARKGRAY);
				line(0,120-2+52,640,120-2+52);
				line(0,440+2,640,440+2);
				setlinestyle(SOLID_LINE,0,1);
				for (i=1; i<14; i++)
				{
					line(0,120-2+52+20.9*i,640,120-2+52+20.9*i);
				}
				line(12+5*18,120,12+5*18,440);	//province
				line(24+13*18,120,24+13*18,440);	//city
				line(640-56-26*10,120,640-56-26*10,440);	//wuzhengzhuang new
				line(640-42-26*7,120,640-42-26*7,440);	//total new
				line(640-28-26*4,120,640-28-26*4,440);	//existing number
				line(640-14-26*2,120,640-14-26*2,440);	//risk rank
				p = 0;
				total = getriskinfo(province, p);	//get total number of data items
				if (total%13 == 0)	//count total pages
				{
					total = total/13;
				}
				else
				{
					term = total%13;	//record max line number of the last page
					total = total/13 + 1;
				}
			}
        }
		else if(mouse_press(320-20-2.5,440+2+5,320-2.5,440+2+5+20) == 1)	//last_page button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(320-20-2.5,440+2+5,320-2.5,440+2+5+20) == 1);
			if (p != 0)
			{
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0,120-2+52,640,440+2);
				setcolor(DARKGRAY);
				setfillstyle(SOLID_FILL, DARKGRAY);
				line(0,120-2+52,640,120-2+52);
				line(0,440+2,640,440+2);
				setlinestyle(SOLID_LINE,0,1);
					for (i=1; i<14; i++)
				{
					line(0,120-2+52+20.9*i,640,120-2+52+20.9*i);
				}
				line(12+5*18,120,12+5*18,440);	//province
				line(24+13*18,120,24+13*18,440);	//city
				line(640-56-26*10,120,640-56-26*10,440);	//wuzhengzhuang new
				line(640-42-26*7,120,640-42-26*7,440);	//total new
				line(640-28-26*4,120,640-28-26*4,440);	//existing number
				line(640-14-26*2,120,640-14-26*2,440);	//risk rank
				p = p - 1;
				getriskinfo(province, p);
			}
			else
			{
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0,120-2+52,640,440+2);
				setcolor(DARKGRAY);
				setfillstyle(SOLID_FILL, DARKGRAY);
				line(0,120-2+52,640,120-2+52);
				line(0,440+2,640,440+2);
				setlinestyle(SOLID_LINE,0,1);
				for (i=1; i<14; i++)
				{
					line(0,120-2+52+20.9*i,640,120-2+52+20.9*i);
				}
				line(12+5*18,120,12+5*18,440);	//province
				line(24+13*18,120,24+13*18,440);	//city
				line(640-56-26*10,120,640-56-26*10,440);	//wuzhengzhuang new
				line(640-42-26*7,120,640-42-26*7,440);	//total new
				line(640-28-26*4,120,640-28-26*4,440);	//existing number
				line(640-14-26*2,120,640-14-26*2,440);	//risk rank
				p = total - 1;
				getriskinfo(province, p);
			}
        }
		else if(mouse_press(320+2.5,440+2+5,320+20+2.5,440+2+5+20) == 1)	//next_page button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(320+2.5,440+2+5,320+20+2.5,440+2+5+20) == 1);
			if (p < total-1)
			{
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0,120-2+52,640,440+2);
				setcolor(DARKGRAY);
				setfillstyle(SOLID_FILL, DARKGRAY);
				line(0,120-2+52,640,120-2+52);
				line(0,440+2,640,440+2);
				setlinestyle(SOLID_LINE,0,1);
				for (i=1; i<14; i++)
				{
					line(0,120-2+52+20.9*i,640,120-2+52+20.9*i);
				}
				line(12+5*18,120,12+5*18,440);	//province
				line(24+13*18,120,24+13*18,440);	//city
				line(640-56-26*10,120,640-56-26*10,440);	//wuzhengzhuang new
				line(640-42-26*7,120,640-42-26*7,440);	//total new
				line(640-28-26*4,120,640-28-26*4,440);	//existing number
				line(640-14-26*2,120,640-14-26*2,440);	//risk rank
				p = p + 1;
				getriskinfo(province, p);
			}
			else
			{
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0,120-2+52,640,440+2);
				setcolor(DARKGRAY);
				setfillstyle(SOLID_FILL, DARKGRAY);
				line(0,120-2+52,640,120-2+52);
				line(0,440+2,640,440+2);
				setlinestyle(SOLID_LINE,0,1);
				for (i=1; i<14; i++)
				{
					line(0,120-2+52+20.9*i,640,120-2+52+20.9*i);
				}
				line(12+5*18,120,12+5*18,440);	//province
				line(24+13*18,120,24+13*18,440);	//city
				line(640-56-26*10,120,640-56-26*10,440);	//wuzhengzhuang new
				line(640-42-26*7,120,640-42-26*7,440);	//total new
				line(640-28-26*4,120,640-28-26*4,440);	//existing number
				line(640-14-26*2,120,640-14-26*2,440);	//risk rank
				p = 0;
				getriskinfo(province, p);
			}
        }
		else if((mouse_press(0,120-2+52,640,440+2) == 1) && (flag == 0))	//update risk info
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(0,120-2+52,640,440+2) == 1);
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0,120-2+52,640,440+2);
			for (i=0;i<13;i++)	//calculates the number of rows of info currently modified
			{
				if ((MouseY > (120-2+52+i*20.9)) && (MouseY < (120-2+72+i*20.9)))
				{
					item = i;
					break;
				}
			}
			if ((p < total-1) || ((i+1) <= term))	//the click line is in the modifiable range
			{
				flag = 1;
				setfillstyle(SOLID_FILL, LIGHTCYAN);
				bar(0,120-2+52+i*20.9,640,120-2+72.9+i*20.9);
				setcolor(DARKGRAY);
				setlinestyle(SOLID_LINE,0,3);
				line(0,120-2+52,640,120-2+52);
				line(0,440+2,640,440+2);
				setlinestyle(SOLID_LINE,0,1);
				for (i=1; i<14; i++)
				{
					line(0,120-2+52+20.9*i,640,120-2+52+20.9*i);
				}
				line(12+5*18,120,12+5*18,440);	//province
				line(24+13*18,120,24+13*18,440);	//city
				line(640-56-26*10,120,640-56-26*10,440);	//wuzhengzhuang new
				line(640-42-26*7,120,640-42-26*7,440);	//total new
				line(640-28-26*4,120,640-28-26*4,440);	//existing number
				line(640-14-26*2,120,640-14-26*2,440);	//risk rank
				getriskinfo(province, p);
				change_riskinfo(item, &flag, province, p);
			}
			clrmous(MouseX,MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0,120-2+52,640,440+2);
			setcolor(DARKGRAY);
			setlinestyle(SOLID_LINE,0,3);
			line(0,120-2+52,640,120-2+52);
			line(0,440+2,640,440+2);
			setlinestyle(SOLID_LINE,0,1);
			for (i=1; i<14; i++)
			{
				line(0,120-2+52+20.9*i,640,120-2+52+20.9*i);
			}
			line(12+5*18,120,12+5*18,440);	//province
			line(24+13*18,120,24+13*18,440);	//city
			line(640-56-26*10,120,640-56-26*10,440);	//wuzhengzhuang new
			line(640-42-26*7,120,640-42-26*7,440);	//total new
			line(640-28-26*4,120,640-28-26*4,440);	//existing number
			line(640-14-26*2,120,640-14-26*2,440);	//riak rank
			getriskinfo(province, p);
        }
	}
}

/**
 * @brief update riskinfo
 * @param Province current check province
 * @param P current page
 * @return int current province total city number
 */
int getriskinfo(char* Province, int P)
{
	FILE* fp;
	SEARCH s;
	AREA a;
	int i, j, len;
	char filename[50] = {'\0'};
	char rank[5] = {'\0'};	//store the risk rank
	
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
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close province.dat");
		delay(3000);
		exit(1);
	}
			
	if (i == 34)
	{
		if (Province[0])
		{
			setcolor(DARKGRAY);
			setfillstyle(SOLID_FILL, WHITE);	
			setlinestyle(SOLID_LINE,0,3);
			bar(320-70,220,320+70,260);
			rectangle(320-70,220,320+70,260);
			puthz(320-2.5*18,240-9,"省份不存在",16,18,RED);
			delay(1500);
			risknew_screen();
		}
	}
	else
	{
		if ((fp = fopen(filename, "rb" )) == NULL)
		{
			printf(filename);
			delay(3000);
			exit(1);
		}
		fseek(fp, 0, SEEK_END);
		len = ftell(fp) / sizeof(AREA);
		for (i = 0; i < 13; i++)
		{
			j = i+P*13;
			fseek(fp, j * sizeof(AREA), SEEK_SET);
			if (!fread(&a, sizeof(AREA), 1, fp))
			{
				break;
			}
			puthz(6,120-2+52+20.9*i+2.5,Province,16,18,BLUE);
			puthz(12+5*18+6,120-2+52+20.9*i+2.5,a.city,16,18,BLUE);
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
			setcolor(BLUE);
			outtextxy(24+13*18+7,115-2+52+20.9*i+2.5,a.bentunew);
			outtextxy(640-56-26*10+7,115-2+52+20.9*i+2.5,a.wzznew);
			outtextxy(640-42-26*7+7,115-2+52+20.9*i+2.5,a.totalnew);
			outtextxy(640-28-26*4+7,115-2+52+20.9*i+2.5,a.existing);
			if (strcmp(a.rank,"1") == 0)
			{
				strcpy(rank, "低");
			}
			else if (strcmp(a.rank,"2") == 0)
			{
				strcpy(rank, "中");
			}
			else if (strcmp(a.rank,"3") == 0)
			{
				strcpy(rank, "高");
			}
			puthz(640-14-26*2+7,120-2+52+20.9*i+2.5,rank,16,18,BLUE);
		}
		if (fclose(fp) != 0)
		{
			printf("\n cannot close Database");
			delay(3000);
			exit(1);
		}
	}
	return len;
}

void risknew_screen(void)
{
	int i;
	int zuo[] = {315-2.5,452,315-2.5,462,305-2.5,457,315-2.5,452};
	int you[] = {325+2.5,452,325+2.5,462,335+2.5,457,325+2.5,452};
	
	cleardevice();
    setbkcolor(WHITE);
    //bar(640-68,2,640,34);
	puthz(640-68,2,"登出",32,34,LIGHTGRAY);
	//bar(640-68-136-20,2,640-88,34);
	puthz(640-68-136+14,2,"管理员",32,34,DARKGRAY);
	//bar(640-68,480-32,640,480);
    puthz(640-68,480-34,"退出",32,34,LIGHTGRAY);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640-68*2-20,480-34,"返回",32,34,LIGHTGRAY);
	puthz(20,40,"区域疫情风险等级修改",32,34,LIGHTRED);
	puthz(20,80,"查看省份",32,34,DARKGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
	setcolor(DARKGRAY);
	outtextxy(20+34*4,80,":");
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(20+34*5+20,80,20+34*5+20+34*5+20,114);
	bar(20+34*5+20+34*5+20+20,80,20+34*5+20+34*5+20+20+70,114);
	puthz(20+34*5+20+34*5+20+20+1,80,"确定",32,34,WHITE);
	setlinestyle(SOLID_LINE,0,3);
	line(0,120-2,640,120-2);
	puthz(25,120+13,"省份",24,26,DARKGRAY);
	puthz(154,120+13,"城市",24,26,DARKGRAY);
	puthz(640-70-26*12+7,120,"本土",24,26,DARKGRAY);
	puthz(640-70-26*12+7,120+26,"新增",24,26,DARKGRAY);
	puthz(640-56-26*10+7,120,"无症状",24,26,DARKGRAY);
	puthz(640-56-26*10+7+13,120+26,"新增",24,26,DARKGRAY);
	puthz(640-42-26*7+7,120,"总新增",24,26,DARKGRAY);
	puthz(640-42-26*7+20,120+26,"确诊",24,26,DARKGRAY);
	puthz(640-28-26*4+7,120,"现存",24,26,DARKGRAY);
	puthz(640-28-26*4+7,120+26,"确诊",24,26,DARKGRAY);
	puthz(640-14-26*2+7,120,"风险",24,26,DARKGRAY);
	puthz(640-14-26*2+7,120+26,"等级",24,26,DARKGRAY);
	line(0,120-2+52,640,120-2+52);
	line(0,440+2,640,440+2);
	setlinestyle(SOLID_LINE,0,1);
	for (i=1; i<14; i++)
	{
		line(0,120-2+52+20.9*i,640,120-2+52+20.9*i);
	}
	line(12+5*18,120,12+5*18,440);	//province
	line(24+13*18,120,24+13*18,440);	//city
	line(640-56-26*10,120,640-56-26*10,440);	//wuzhengzhuang new
	line(640-42-26*7,120,640-42-26*7,440);	//total new
	line(640-28-26*4,120,640-28-26*4,440);	//existing number
	line(640-14-26*2,120,640-14-26*2,440);	//risk rank
	setlinestyle(SOLID_LINE,0,3);
	rectangle(320-20-2.5,440+2+5,320-2.5,440+2+5+20);
	rectangle(320+2.5,440+2+5,320+20+2.5,440+2+5+20);
	setlinestyle(SOLID_LINE,0,1);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL, BLUE);
    fillpoly(4,zuo);
	fillpoly(4,you);
}