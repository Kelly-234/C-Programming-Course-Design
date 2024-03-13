/*#include "public.h"
#include "riskinfo.h"

int p18_riskinfo(void)
{
	int page = 17;
	int state = 0;
	char province[30] = {'\0'};
	char city[30] = {'\0'};
	char bentunew[20] = {'\0'};//本土新增
	char wzznew[20] = {'\0'};//无症状新增
	char totalnew[20] = {'\0'};//总新增确诊
	char existing[20] = {'\0'};//现存确诊
	char rank[2] = {'\0'};//地区风险等级
	clrmous(MouseX,MouseY);
	delay(300);
	
	riskinfo_screen();
	
	while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)//返回按钮点击
		{
			page = 2;
			return page;
		}
		else if(mouse_press(640-68,480-32,640,480) == 1)//退出按钮点击
		{
			page = 9;
			return page;
		}
		else if (mouse_press(20+68+20,40,20+68+20+20+34*8,40+34) == 1)
		{
			province[0] = '\0';
			hz_input(20+68+20,40,20+68+20+20+34*8,40+34,province,0,LIGHTGRAY,WHITE,32);
		}
		else if (mouse_press(20+68+20,40*2,20+68+20+20+34*8,40*2+34) == 1)
		{
			city[0] = '\0';
			hz_input(20+68+20,40*2,20+68+20+20+34*8,40*2+34,city,0,LIGHTGRAY,WHITE,32);
		}
		else if (mouse_press(20+136+20,40*3,20+136+20+20+100,40*3+34) == 1)
		{
			bentunew[0] = '\0';
			inputadmin(bentunew, 20+136+20,40*3, 3, LIGHTGRAY);
		}
		else if (mouse_press(20+170+20,40*4,20+170+20+20+100,40*4+34) == 1)
		{
			wzznew[0] = '\0';
			inputadmin(wzznew, 20+170+20,40*4, 3, LIGHTGRAY);
		}
		else if (mouse_press(20+170+20,40*5,20+170+20+20+100,40*5+34) == 1)
		{
			totalnew[0] = '\0';
			inputadmin(totalnew, 20+170+20,40*5, 3, LIGHTGRAY);
		}
		else if (mouse_press(20+136+20,40*6,20+136+20+20+100,40*6+34) == 1)
		{
			existing[0] = '\0';
			inputadmin(existing, 20+136+20,40*6, 3, LIGHTGRAY);
		}
		else if (mouse_press(20+136+20,40*7,20+136+20+20+40,40*7+34) == 1)
		{
			rank[0] = '\0';
			hz_input(20+136+20,40*7,20+136+20+20+40,40*7+34,rank,0,LIGHTGRAY,WHITE,32);
		}
		else if (mouse_press(320-34,40*8,320+34,40*8+34) == 1)
		{
			do {
				mread(&MouseX, &MouseY, &press);
			}while (mouse_press(320-34,40*8,320+34,40*8+34) == 1);
			MouseS = 0;
			input(province, city, bentunew, wzznew, totalnew, existing, rank);
		}
	}
	return page;
}

void riskinfo_screen(void)
{
	cleardevice();
	setbkcolor(WHITE);
	//bar(640-68,480-32,640,480);
	puthz(640-68,480-34,"退出",32,34,LIGHTGRAY);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640-68*2-20,480-34,"返回",32,34,LIGHTGRAY);
	puthz(0,0,"区域疫情信息修改",32,34,DARKGRAY);
	puthz(20,40,"省份",32,34,DARKGRAY);
	puthz(20,40*2,"城市",32,34,DARKGRAY);
	puthz(20,40*3,"本土新增",32,34,DARKGRAY);
	puthz(20,40*4,"无症状新增",32,34,DARKGRAY);
	puthz(20,40*5,"总新增确诊",32,34,DARKGRAY);
	puthz(20,40*6,"现存确证",32,34,DARKGRAY);
	puthz(20,40*7,"风险等级",32,34,DARKGRAY);
	setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(20+68+20,40,20+68+20+20+34*8,40+34);
	bar(20+68+20,40*2,20+68+20+20+34*8,40*2+34);
	bar(20+136+20,40*3,20+136+20+20+100,40*3+34);
	bar(20+170+20,40*4,20+170+20+20+100,40*4+34);
	bar(20+170+20,40*5,20+170+20+20+100,40*5+34);
	bar(20+136+20,40*6,20+136+20+20+100,40*6+34);
	bar(20+136+20,40*7,20+136+20+20+40,40*7+34);
	bar(320-34,40*8,320+34,40*8+34);
	puthz(320-33,40*8,"确定",32,34,WHITE);
}

void input(char* Province, char* City, char* Bentunew, char* Wzznew, char* Totalnew, char* Existing, char* Rank)
{
	FILE* fp;
	AREA a;
	int i;
	char area[50] = {'\0'};
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
	strcpy(area, "database\\place\\");
	for (i=0;i<34;i++)
	{
		if (strcmp(PROVINCE[i], Province) == 0)
		{
			strcat(area,PROVINCE1[i]);
			strcat(area,".dat");
		}
	}
	if ((fp = fopen(area, "rb+" )) == NULL)//建立数据库
	{
		printf(area);
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	strcpy(a.city, City);
	strcpy(a.bentunew, Bentunew);
	strcpy(a.wzznew, Wzznew);
	strcpy(a.totalnew, Totalnew);
	strcpy(a.existing, Existing);
	if (strcmp(Rank, "低") == 0)
	{
		strcpy(a.rank, "1");
	}
	else if (strcmp(Rank, "中") == 0)
	{
		strcpy(a.rank, "2");
	}
	else
	{
		strcpy(a.rank, "3");
	}
	if (fwrite(&a, sizeof(AREA), 1, fp)==1)//把用户信息写入文件 余额默认为0
	{
		setcolor(DARKGRAY);
		setfillstyle(SOLID_FILL, WHITE);
		bar(20,40*9,640,480-34);
		puthz(20,40*9,Province,24,26,DARKGRAY);
		puthz(20+26*5,40*9,a.city,24,26,DARKGRAY);
		puthz(20+26*5+26*8,40*9,"信息录入成功",24,26,DARKGRAY);
		outtextxy(20,40*10,a.bentunew);
		outtextxy(20+50,40*10,a.wzznew);
		outtextxy(120,40*10,a.totalnew);
		outtextxy(170,40*10,a.existing);
		outtextxy(220,40*10,a.rank);
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close");
		printf(area);
		delay(3000);
		exit(1);
	}
}*/