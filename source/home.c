/**
 * @file home.c
 * @author yangchunru
 * @brief main interface, show newest epidemic situation data of top 11 cities, can rank by different kinds of data
 * @date 2021-04-24
 */
#include "public.h"
#include "home.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p2_home(USER* u, int* Flag)
{
	FILE* fp;
	USER us;
	int i, len, page = 1;
	char Name[10] = { '\0' };
	
	//get user's name when logged in
	if (*Flag == 1)
	{
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
	}
	
	clrmous(MouseX,MouseY);
	home_screen(Name);
	show_riskinfo(3);
	delay(300);
	
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);

		if ((mouse_press(640-68,2,640,34) == 1) && (*Flag == 1))	//log out button(go to home.c)
		{
			*Flag = 0;
			page = 1;
			return page;
		}
		else if ((mouse_press(640-68,2,640,34) == 1) && (*Flag == 0))	//login button(go to login.c)
		{
			page = 4;
			return page;
		}
		else if ((mouse_press(640-68-136-20,2,640-88,34) == 1) && (*Flag == 1))	//personal center button(go to grhome.c)
		{
			page = 3;
			return page;
		}
		else if (mouse_press(640-68,480-34,640,480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
		else if ((mouse_press(640-68*2-20,480-34,640-68-20,480) == 1) && (*Flag == 0))	//return button(go to welcome.c)
		{
			page = 0;
			return page;
		}
		else if ((mouse_press(20+170+110+18*5+20,94+66+46*3+86,413+180+14,384+14) == 1) && (*Flag == 0))	//risklook button(go to risklook.c)
		{
			page = 9;
			return page;
		}
		else if (mouse_press(20+130,60+34+20,20+130+18*4,60+34+20+18) == 1)	//rank by bentunew
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+130,60+34+20,20+130+18*4,60+34+20+18) == 1);
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0,40+34+20+46,640,40+34+20+46+220);
			show_riskinfo(1);
		}
		else if (mouse_press(20+130+120,60+34+20,20+130+120+18*5,60+34+20+18) == 1)	//rank by wuzhengzhuangnew
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+130+120,60+34+20,20+130+120+18*5,60+34+20+18) == 1);
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0,40+34+20+46,640,40+34+20+46+220);
			show_riskinfo(2);
		}
		else if (mouse_press(20+130+120+130,60+34+20,20+130+120+130+18*5,60+34+20+18) == 1)	//rank by totalnew
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+130+120+130,60+34+20,20+130+120+130+18*5,60+34+20+18) == 1);
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0,40+34+20+46,640,40+34+20+46+220);
			show_riskinfo(3);
		}
		else if (mouse_press(20+130+120+130+130,60+34+20,20+130+120+130+130+18*4,60+34+20+18) == 1)	//rank by existing
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+130+120+130+130,60+34+20,20+130+120+130+130+18*4,60+34+20+18) == 1);
			clrmous(MouseX,MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0,40+34+20+46,640,40+34+20+46+220);
			show_riskinfo(4);
		}
	}
}

/**
 * @param n user's name
 */
void home_screen(char* n)
{
	int jt[]={413+180,384,413+180+14,384+7,413+180,384+14,413+180,384};

	cleardevice();
	setbkcolor(WHITE);
	if (strcmp(n, "") != 0)
	{
		//bar(640-68,2,640,34);
		puthz(640-68,2,"登出",32,34,LIGHTGRAY);
		//bar(640-68-136-20,2,640-88,34);
		puthz(640-68-136-20,2,"个人中心",32,34,LIGHTGRAY);
		//bar(640-68-136-20-102-20,2,640-68-136-40,34);
		puthz(640-68-136-20-102-20,2,n,32,34,LIGHTGRAY);
		//bar(640-68,480-32,640,480);
		puthz(640-68,480-34,"退出",32,34,LIGHTGRAY);
	}
	else
	{
		//bar(640-68,2,640,34);
		puthz(640-68,2,"登录",32,34,LIGHTGRAY);
		//bar(640-68,480-32,640,480);
		puthz(640-68,480-34,"退出",32,34,LIGHTGRAY);
		//bar(640-68*2-20,480-34,640-68-20,480);
		puthz(640-68*2-20,480-34,"返回",32,34,LIGHTGRAY);
		puthz(20+170+110+18*5+20,94+66+46*3+86,"区域疫情风险等级查询",16,18,LIGHTBLUE);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		setcolor(LIGHTBLUE);
		fillpoly(4,jt);
	}
	puthz(20,60,"最新全国疫情",32,32,LIGHTBLUE);
	puthz(20+34*6.5,60+34-16,"截止",16,18,LIGHTBLUE);
	puthz(20,60+34+20,"地区",16,18,DARKGRAY);
	puthz(20+130,60+34+20,"本土新增",16,18,DARKGRAY);
	puthz(20+130+120,60+34+20,"无症状新增",16,18,DARKGRAY);
	puthz(20+130+120+130,60+34+20,"总新增确诊",16,18,DARKGRAY);
	puthz(20+130+120+130+130,60+34+20,"现存确诊",16,18,DARKGRAY);
	setlinestyle(SOLID_LINE,0,3);
	setcolor(DARKGRAY);
	line(20,60+34+20+46+46+46+46+66,620,60+34+20+46+46+46+46+66);
	puthz(20,60+34+20+46+46+46+46+66+20,"全国中高风险区",16,18,DARKGRAY);
	puthz(20+140,94+66+46*3+86,"高风险",16,18,DARKGRAY);
	puthz(180+18*4,94+66+46*3+86,"个",16,18,DARKGRAY);
	puthz(170+110,94+66+46*3+86,"中风险",16,18,DARKGRAY);
	puthz(20+170+110+18*4,94+66+46*3+86,"个",16,18,DARKGRAY);
}

/**
 * @param r sign structure data to rank by
 */
void show_riskinfo(int r)
{
	FILE* fp;
	FILE* fp2;
	SEARCH s;
	AREA a;
	ADMIN ad;
	int i, j, len, k, l, temp, highrisk = 0, middlerisk = 0;
	char filename[50] = {'\0'};	//the file name currently open
	char show_filename[11][50] = {'\0'};	//store the file name of the file to open when display data
	int term[11][2] = {0};	//[][0]new data number rank by now; [][1]term of the city in the file(i)
	char num[10] = {'\0'};	//store the string convert by the risk number to show
	char* strategy_name[4];	//store the structure data to look for
	char strategy_color[4][4] = {BLUE, DARKGRAY, DARKGRAY, DARKGRAY, DARKGRAY, BLUE, DARKGRAY, DARKGRAY, DARKGRAY, DARKGRAY, BLUE, DARKGRAY, DARKGRAY, DARKGRAY, DARKGRAY, BLUE};
	strategy_name[0] = a.bentunew;
	strategy_name[1] = a.wzznew;
	strategy_name[2] = a.totalnew;
	strategy_name[3] = a.existing;
	
	//input province info
	/*char PROVINCE[][20]={"北京","上海","天津","重庆",
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
	if ((fp = fopen("database\\place\\province.dat", "rb+" )) == NULL)//建立数据库
	{
		printf("cannot open datebase\\place\\province.dat");
		delay(3000);
		exit(1);
	}
	for (i=0;i<34;i++)
	{
		fseek(fp, i * sizeof(SEARCH), SEEK_SET);
		strcpy(s.provinceall, PROVINCE[i]);
		strcpy(s.provinceall1, PROVINCE1[i]);
		fseek(fp, i * sizeof(SEARCH), SEEK_SET);
		fwrite(&s, sizeof(SEARCH), 1, fp);
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close");
		delay(3000);
		exit(1);
	}*/

	if ((fp2 = fopen("database\\place\\province.dat", "rb" )) == NULL)	//to seek the province name
	{
		printf("cannot open database\\place\\province.dat");
		delay(3000);
		exit(1);
	}
	for (i=0;i<34;i++)
	{
		
		fseek(fp2, i * sizeof(SEARCH), SEEK_SET);
		fread(&s, sizeof(SEARCH), 1, fp2);
		strcpy(filename, "database\\place\\");
		strcat(filename,s.provinceall1);
		strcat(filename,".dat");	//get the file name for each province
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
			for (k=0;k<11;k++)
			{
				if (atoi(strategy_name[r-1]) > term[k][0])
				{
					for (l=10;l>k;l--)
					{
						strcpy(show_filename[l],show_filename[l-1]);
						term[l][0]=term[l-1][0];
						term[l][1]=term[l-1][1];
					}
					strcpy(show_filename[k],filename);
					term[k][0]=atoi(strategy_name[r-1]);
					term[k][1]=j;
					break;
				}
			}
			if (strcmp(a.rank, "2") == 0)
			{
				middlerisk++;
			}
			else if (strcmp(a.rank, "3") == 0)
			{
				highrisk++;
			}
		}
		if (fclose(fp) != 0)
		{
			printf("\n cannot close province.dat");
			delay(3000);
			exit(1);
		}
	}
	if (fclose(fp2) != 0)
	{
		printf("cannot close province.dat in dlhome.c");
		delay(3000);
		exit(1);
	}
	for (i=0;i<11;i++)	//show riskinfo
	{
		if ((fp = fopen(show_filename[i], "rb" )) == NULL)
		{
			printf(show_filename[i]);
			delay(3000);
			exit(1);
		}
		fseek(fp, term[i][1] * sizeof(AREA), SEEK_SET);
		fread(&a, sizeof(AREA), 1, fp);
		if (strcmp(a.rank, "1") == 0)
		{
			puthz(20,40+34+20+46+20*i,a.city,16,18,GREEN);
			setcolor(GREEN);
		}
		else if (strcmp(a.rank, "2") == 0)
		{
			puthz(20,40+34+20+46+20*i,a.city,16,18,BROWN);
			setcolor(BROWN);
		}
		else
		{
			puthz(20,40+34+20+46+20*i,a.city,16,18,RED);
			setcolor(RED);
		}
		settextjustify(RIGHT_TEXT, TOP_TEXT);
		settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
		outtextxy(200,35+34+20+46+20*i,a.bentunew);
		outtextxy(79+130+120,35+34+20+46+20*i,a.wzznew);
		outtextxy(79+130+120+130,35+34+20+46+20*i,a.totalnew);
		outtextxy(200+120+130+130,35+34+20+46+20*i,a.existing);
		if (fclose(fp) != 0)
		{
			printf("cannot close province.dat in dlhome.c");
			delay(3000);
			exit(1);
		}
	}
	puthz(20+130,60+34+20,"本土新增",16,18,strategy_color[r-1][0]);
	puthz(20+130+120,60+34+20,"无症状新增",16,18,strategy_color[r-1][1]);
	puthz(20+130+120+130,60+34+20,"总新增确诊",16,18,strategy_color[r-1][2]);
	puthz(20+130+120+130+130,60+34+20,"现存确诊",16,18,strategy_color[r-1][3]);
	settextjustify(CENTER_TEXT, TOP_TEXT);
	itoa(highrisk,num,10);
	setcolor(RED);
	outtextxy(179+18*3,94+66+46*3+86-5,num);
	itoa(middlerisk,num,10);
	setcolor(BROWN);
	outtextxy(189+110+18*3,94+66+46*3+86-5,num);
	if ((fp = fopen("database\\Admin.dat", "rb" )) == NULL)
	{
		printf("cannot open database\\Admin.dat");
		delay(3000);
		exit(1);
	}
	i=0;
	fseek(fp, i * sizeof(ADMIN), SEEK_SET);
	fread(&ad, sizeof(ADMIN), 1, fp);
	setcolor(LIGHTBLUE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(20+34*6.5+36,60+34-16-5,ad.time_rankinfo);
	if (fclose(fp) != 0)
	{
		printf("cannot open database\\Admin.dat");
		delay(3000);
		exit(1);
	}
}