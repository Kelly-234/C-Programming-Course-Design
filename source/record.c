/**
 * @file record.c
 * @author yangchunru
 * @brief check and add travel record info
 * @date 2021-04-30
 */
#include "public.h"
#include "record.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p12_record(USER* u, int* Flag)
{
	FILE* fp;
	USER us;
	int i, len, page = 11;
	int flag = 0;	//1 for adding new travel record info now; 2 for not
	int time_flag = 0;	//1 for choosing travel time now; 2 for not
	int place_flag = 0;	//1 for choosing travel place now; 2 for not
	int total;	//total page number
	int p = 0;	//current page
	char Name[20] = { '\0' };
	char province[30] = { '\0' };
	char city[30] = { '\0' };
	char time1_1[10] = { '\0' };	//departure time-year
	char time1_2[5] = { '\0' };	//departure time-month
	char time1_3[5] = { '\0' };	//departure time-date
	char time2_1[10] = { '\0' };	//return time-year
	char time2_2[5] = { '\0' };	//return time-month
	char time2_3[5] = { '\0' };	//return time-date
	strcpy(province, "选择省份");
	strcpy(city, "选择城市");
	
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
	record_screen(Name, flag);
	total = gettravelinfo(i, p, flag);
	if (total%14 == 0)
	{
		total = total/14;
	}
	else
	{
		total = total/14 + 1;
	}
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
		else if((mouse_press(320-20-2.5,425+2+5,320-2.5,425+2+5+20) == 1) && (flag == 0) && (place_flag == 0) && (time_flag == 0))	//last_page button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(320-20-2.5,425+2+5,320-2.5,425+2+5+20) == 1);
			if (p != 0)
			{
				p = p - 1;
				clrmous(MouseX,MouseY);
				record_screen(Name, flag);
				gettravelinfo(i, p, flag);
			}
			else
			{
				p = total - 1;
				clrmous(MouseX,MouseY);
				record_screen(Name, flag);
				gettravelinfo(i, p, flag);
			}
        }
		else if((mouse_press(320+2.5,425+2+5,320+20+2.5,425+2+5+20) == 1) && (flag == 0) && (place_flag == 0) && (time_flag == 0))	//next_page button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(320+2.5,425+2+5,320+20+2.5,425+2+5+20) == 1);
			if (p < total-1)
			{
				clrmous(MouseX,MouseY);
				p = p + 1;
				record_screen(Name, flag);
				gettravelinfo(i, p, flag);
			}
			else
			{
				p = 0;
				clrmous(MouseX,MouseY);
				record_screen(Name, flag);
				gettravelinfo(i, p, flag);
			}
        }
		else if ((mouse_press(20,80,20+26*6+10,110) == 1) && (flag == 0) && (place_flag == 0) && (time_flag == 0))	//add new travel record info button
		{
			clrmous(MouseX,MouseY);
			flag = 1;
			record_screen(Name, flag);
			gettravelinfo(i, p, flag);
		}
		else if ((mouse_press(20+26*3+20,110,20+26*3+20+26*5+4,110+26) == 1) && (flag == 1) && (time_flag == 0))	//choose province
		{
			place_flag = 1;
			province[0] = '\0';
			clrmous(MouseX,MouseY);
			showplace(province, city, 20+26*3+20, 110+26, &place_flag);
			clrmous(MouseX,MouseY);
			record_screen(Name, flag);
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(20+26*3+20,110,20+26*3+20+26*5+4,110+26);
			puthz(20+26*3+20+2+(5*26-strlen(province)/2*26)/2,110+1,province,24,26,WHITE);
			setcolor(WHITE);
			outtextxy(22+26*4+10,80,time1_1);
			outtextxy(20+26*4+12+15*5,80,time1_2);
			outtextxy(20+26*4+14+15*8,80,time1_3);
			outtextxy(22+26*4+9+15*10+12+26*4+5,80,time2_1);
			outtextxy(20+26*4+14+15*15+5+26*4+7,80,time2_2);
			outtextxy(20+26*4+16+15*18+26*4+12,80,time2_3);
			gettravelinfo(i, p, flag);
		}
		else if ((mouse_press(20+26*3+20+26*5+4+5,110,20+26*3+20+26*5+9+4+26*8,110+26) == 1) && (flag == 1) && (time_flag == 0))	//choose city
		{
			if (strcmp(province,"选择省份") != 0)
			{
				place_flag = 1;
				city[0] = '\0';
				clrmous(MouseX,MouseY);
				showplace(province, city, 20+26*3+20+26*5+9+4+26*8-370, 110+26, &place_flag);
				clrmous(MouseX,MouseY);
				record_screen(Name, flag);
				setcolor(LIGHTGRAY);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(20+26*3+20,110,20+26*3+20+26*5+4,110+26);
				puthz(20+26*3+20+2+(5*26-strlen(province)/2*26)/2,110+1,province,24,26,WHITE);
				bar(20+26*3+20+26*5+4+5,110,20+26*3+20+26*5+9+4+26*8,110+26);
				puthz(20+26*3+20+26*5+4+5+(8*26-strlen(city)/2*26)/2,111,city,24,26,WHITE);
				setcolor(WHITE);
				outtextxy(22+26*4+10,80,time1_1);
				outtextxy(20+26*4+12+15*5,80,time1_2);
				outtextxy(20+26*4+14+15*8,80,time1_3);
				outtextxy(22+26*4+9+15*10+12+26*4+5,80,time2_1);
				outtextxy(20+26*4+14+15*15+5+26*4+7,80,time2_2);
				outtextxy(20+26*4+16+15*18+26*4+12,80,time2_3);
				gettravelinfo(i, p, flag);
			}
			else
			{
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(250,220,390,260);
				setlinestyle(SOLID_LINE,0,3);
				setcolor(DARKGRAY);
				rectangle(250,220,390,260);
				puthz(320-18*3,240-9,"请先选择省份",16,18,RED);
				delay(2000);
				record_screen(Name, flag);
				setcolor(LIGHTGRAY);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(20+26*3+20,110,20+26*3+20+26*5+4,110+26);
				puthz(20+26*3+20+2+(5*26-strlen(province)/2*26)/2,110+1,province,24,26,WHITE);
				bar(20+26*3+20+26*5+4+5,110,20+26*3+20+26*5+9+4+26*8,110+26);
				puthz(20+26*3+20+26*5+4+5+(8*26-strlen(city)/2*26)/2,111,city,24,26,WHITE);
				setcolor(WHITE);
				outtextxy(22+26*4+10,80,time1_1);
				outtextxy(20+26*4+12+15*5,80,time1_2);
				outtextxy(20+26*4+14+15*8,80,time1_3);
				outtextxy(22+26*4+9+15*10+12+26*4+5,80,time2_1);
				outtextxy(20+26*4+14+15*15+5+26*4+7,80,time2_2);
				outtextxy(20+26*4+16+15*18+26*4+12,80,time2_3);
			}
		}
		else if ((mouse_press(20+26*4+5,80,20+26*4+9+15*10,80+26) == 1) && (flag == 1) && (place_flag == 0))	//choose departure time button
		{
			time_flag = 1;
			if (mouse_press(20+26*4+5,80,20+26*4+5+15*4,80+26) == 1)
			{
				time1_1[0] = '\0';
			}
			else if (mouse_press(20+26*4+7+15*5,80,20+26*4+7+15*7,80+26) == 1)
			{
				time1_2[0] = '\0';
			}
			else
			{
				time1_3[0] = '\0';
			}
			clrmous(MouseX,MouseY);
			showtime(time1_1, time1_2, time1_3, 20+26*4+5, 80+26, &time_flag);
			clrmous(MouseX,MouseY);
			record_screen(Name, flag);
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(20+26*3+20,110,20+26*3+20+26*5+4,110+26);
			puthz(20+26*3+20+2+(5*26-strlen(province)/2*26)/2,110+1,province,24,26,WHITE);
			bar(20+26*3+20+26*5+4+5,110,20+26*3+20+26*5+9+4+26*8,110+26);
			puthz(20+26*3+20+26*5+4+5+(8*26-strlen(city)/2*26)/2,111,city,24,26,WHITE);
			setcolor(WHITE);
			outtextxy(22+26*4+10,80,time1_1);
			outtextxy(20+26*4+12+15*5,80,time1_2);
			outtextxy(20+26*4+14+15*8,80,time1_3);
			outtextxy(22+26*4+9+15*10+12+26*4+5,80,time2_1);
			outtextxy(20+26*4+14+15*15+5+26*4+7,80,time2_2);
			outtextxy(20+26*4+16+15*18+26*4+12,80,time2_3);
			gettravelinfo(i, p, flag);
		}
		else if ((mouse_press(20+26*4+9+15*10+5+26*4+5,80,20+26*4+11+15*20+26*4+12,80+26) == 1) && (flag == 1) && (place_flag == 0))	//choose return time button
		{
			time_flag = 1;
			if (mouse_press(20+26*4+9+15*10+5+26*4+5,80,20+26*4+9+15*14+5+26*4+5,80+26) == 1)
			{
				time2_1[0] = '\0';
			}
			else if (mouse_press(20+26*4+9+15*15+5+26*4+7,80,20+26*4+9+15*17+5+26*4+7,80+26) == 1)
			{
				time2_2[0] = '\0';
			}
			else
			{
				time2_3[0] = '\0';
			}
			clrmous(MouseX,MouseY);
			showtime(time2_1, time2_2, time2_3, 20+26*4+9+15*10+5+26*4+5,80+26, &time_flag);
			clrmous(MouseX,MouseY);
			record_screen(Name, flag);
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(20+26*3+20,110,20+26*3+20+26*5+4,110+26);
			puthz(20+26*3+20+2+(5*26-strlen(province)/2*26)/2,110+1,province,24,26,WHITE);
			bar(20+26*3+20+26*5+4+5,110,20+26*3+20+26*5+9+4+26*8,110+26);
			puthz(20+26*3+20+26*5+4+5+(8*26-strlen(city)/2*26)/2,111,city,24,26,WHITE);
			setcolor(WHITE);
			outtextxy(22+26*4+10,80,time1_1);
			outtextxy(20+26*4+12+15*5,80,time1_2);
			outtextxy(20+26*4+14+15*8,80,time1_3);
			outtextxy(22+26*4+9+15*10+12+26*4+5,80,time2_1);
			outtextxy(20+26*4+14+15*15+5+26*4+7,80,time2_2);
			outtextxy(20+26*4+16+15*18+26*4+12,80,time2_3);
			gettravelinfo(i, p, flag);
		}
		else if ((mouse_press(20+26*3+20+26*5+9+4+26*8+5,110,20+26*3+20+26*5+9+4+26*8+5+56,110+26) == 1) && (flag == 1) && (place_flag == 0) && (time_flag == 0))	//confirm button
		{
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20+26*3+20+26*5+9+4+26*8+5,110,20+26*3+20+26*5+9+4+26*8+5+56,110+26) == 1);
			if ((strcmp(province, "选择省份") != 0) && (strcmp(province, "选择城市") != 0) && (strcmp(time1_1, "") != 0) && (strcmp(time1_2, "") != 0) && (strcmp(time1_3, "") != 0) && (strcmp(time2_1, "") != 0) && (strcmp(time2_2, "") != 0) && (strcmp(time2_3, "") != 0))
			{
				if ((traveltime_compare(time1_1, time1_2, time1_3, time2_1, time2_2, time2_3)) && 
				    (inputtravelinfo(i, province, city, time1_1, time1_2, time1_3, time2_1, time2_2, time2_3)))	//travel time legitimate
				{
					clrmous(MouseX,MouseY);
					record_screen(Name, flag);
					strcpy(province, "选择省份");
					strcpy(city, "选择城市");
					time1_1[0] = '\0';	//departure time-year
					time1_2[0] = '\0';	//departure time-month
					time1_3[0] = '\0';	//departure time-date
					time2_1[0] = '\0';	//return time-year
					time2_2[0] = '\0';	//return time-month
					time2_3[0] = '\0';	//return time-date
				}
				else
				{
					clrmous(MouseX,MouseY);
					setcolor(WHITE);
					setfillstyle(SOLID_FILL, WHITE);
					bar(250,220,390,260);
					setlinestyle(SOLID_LINE,0,3);
					setcolor(DARKGRAY);
					rectangle(250,220,390,260);
					puthz(320-18*3,240-9,"时间信息有误",16,18,RED);
					delay(2000);
					record_screen(Name, flag);
					setcolor(LIGHTGRAY);
					setfillstyle(SOLID_FILL, LIGHTGRAY);
					bar(20+26*3+20,110,20+26*3+20+26*5+4,110+26);
					puthz(20+26*3+20+2+(5*26-strlen(province)/2*26)/2,110+1,province,24,26,WHITE);
					bar(20+26*3+20+26*5+4+5,110,20+26*3+20+26*5+9+4+26*8,110+26);
					puthz(20+26*3+20+26*5+4+5+(8*26-strlen(city)/2*26)/2,111,city,24,26,WHITE);
					setcolor(WHITE);
					outtextxy(22+26*4+10,80,time1_1);
					outtextxy(20+26*4+12+15*5,80,time1_2);
					outtextxy(20+26*4+14+15*8,80,time1_3);
					outtextxy(22+26*4+9+15*10+12+26*4+5,80,time2_1);
					outtextxy(20+26*4+14+15*15+5+26*4+7,80,time2_2);
					outtextxy(20+26*4+16+15*18+26*4+12,80,time2_3);
				}
			}
			else
			{
				clrmous(MouseX,MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(250,220,390,260);
				setlinestyle(SOLID_LINE,0,3);
				setcolor(DARKGRAY);
				rectangle(250,220,390,260);
				puthz(320-18*3,240-9,"信息选择不全",16,18,RED);
				delay(2000);
				record_screen(Name, flag);
				setcolor(LIGHTGRAY);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(20+26*3+20,110,20+26*3+20+26*5+4,110+26);
				puthz(20+26*3+20+2+(5*26-strlen(province)/2*26)/2,110+1,province,24,26,WHITE);
				bar(20+26*3+20+26*5+4+5,110,20+26*3+20+26*5+9+4+26*8,110+26);
				puthz(20+26*3+20+26*5+4+5+(8*26-strlen(city)/2*26)/2,111,city,24,26,WHITE);
				setcolor(WHITE);
				outtextxy(22+26*4+10,80,time1_1);
				outtextxy(20+26*4+12+15*5,80,time1_2);
				outtextxy(20+26*4+14+15*8,80,time1_3);
				outtextxy(22+26*4+9+15*10+12+26*4+5,80,time2_1);
				outtextxy(20+26*4+14+15*15+5+26*4+7,80,time2_2);
				outtextxy(20+26*4+16+15*18+26*4+12,80,time2_3);
			}
			gettravelinfo(i,p,flag);
		}
		else if ((mouse_press(20+26*3+20+26*5+9+4+26*8+5+56+25,120,20+26*3+20+26*5+9+4+26*8+5+56+25+56,120+26) == 1) && (flag == 1) && (place_flag == 0) && (time_flag == 0))	//complete button
		{
			clrmous(MouseX,MouseY);
			flag = 0;
			record_screen(Name, flag);
			gettravelinfo(i, p, flag);
		}
	}
}

/**
 * @brief show user's travel record info
 * @param I	 the rank of the user in total data file, also the file name serial number of corresponding travel info file
 * @param P current page number
 * @param Flag 1 for adding new travel record info now; 2 for not
 * @return int return total number of user's travel record info
 */
int gettravelinfo(int I, int P, int Flag)
{
	FILE* fp;
	TRAVEL t;
	int i, j, len;
	char filename[50] = {'\0'};	//store the name of the file to open
	char time1[25] = {'\0'};	//departure time
	char time2[25] = {'\0'};	//return time
	char name[5] = {'\0'};	//store the string convert by user's serial number

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
	len = ftell(fp) / sizeof(AREA);
	if (Flag == 0)	//while reading state
	{
		for (i = 0; i < 14; i++)
		{
			j = i+P*14;
			fseek(fp, j * sizeof(TRAVEL), SEEK_SET);
			if (!fread(&t, sizeof(TRAVEL), 1, fp))
			{
				break;
			}
			strcpy(time1, t.time1_1);
			strcat(time1, "/");
			strcat(time1, t.time1_2);
			strcat(time1, "/");
			strcat(time1, t.time1_3);
			strcpy(time2, t.time2_1);
			strcat(time2, "/");
			strcat(time2, t.time2_2);
			strcat(time2, "/");
			strcat(time2, t.time2_3);
			puthz(35,119+25+i*20+40*Flag,t.province,16,18,DARKGRAY);
			puthz(35+30+18*5,119+25+i*20+40*Flag,t.city,16,18,DARKGRAY);
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
			setcolor(DARKGRAY);
			outtextxy(55+18*13+45,114+25+i*20+40*Flag,time1);
			outtextxy(55+18*13+15*10+50,114+25+i*20+40*Flag,time2);
		}
	}
	else	//while adding new travel record info
	{
		for (i = 0; i < len; i++)
		{
			if (len > 12)	//total number of records is more than 12, show the last 12
			{
				j = i+len-13;
			}
			else	//displays all records sequentially
			{
				j = i;
			}
			fseek(fp, j * sizeof(TRAVEL), SEEK_SET);
			if (!fread(&t, sizeof(TRAVEL), 1, fp))
			{
				break;
			}
			strcpy(time1, t.time1_1);
			strcat(time1, "/");
			strcat(time1, t.time1_2);
			strcat(time1, "/");
			strcat(time1, t.time1_3);
			strcpy(time2, t.time2_1);
			strcat(time2, "/");
			strcat(time2, t.time2_2);
			strcat(time2, "/");
			strcat(time2, t.time2_3);
			puthz(35,119+25+i*20+40*Flag,t.province,16,18,DARKGRAY);
			puthz(35+30+18*5,119+25+i*20+40*Flag,t.city,16,18,DARKGRAY);
			settextjustify(LEFT_TEXT, TOP_TEXT);
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
			setcolor(DARKGRAY);
			outtextxy(55+18*13+45,114+25+i*20+40*Flag,time1);
			outtextxy(55+18*13+15*10+50,114+25+i*20+40*Flag,time2);
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		delay(3000);
		exit(1);
	}
	return len;
}

/**
 * @brief input user's travel record info
 * @param I	 the rank of the user in total data file, also the file name serial number of corresponding travel info file
 * @param Province the name of the travel province
 * @param City the name of the travel city
 * @param Time1_1 departure time-year
 * @param Time1_2 departure time-month
 * @param Time1_3 departure time-date
 * @param Time2_1 return time-year
 * @param Time2_2 return time-month
 * @param Time2_3 return time-date
 * @return int return 1 for legitimate; return 0 for illegitimate
 */
int inputtravelinfo(int I, char* Province, char* City, char* Time1_1, char* Time1_2, char* Time1_3, char* Time2_1, char* Time2_2, char* Time2_3)
{
	FILE* fp;
	TRAVEL t;
	SEARCH s;
	int i, len;
	char filename[50] = {'\0'};	//store the name of the file to open
	char name[5] = {'\0'};	//store the string convert by user's serial number
	
	strcpy(filename, "database\\travel\\User\\");
	itoa(I, name, 10);
	strcat(filename, name);
	strcat(filename, ".dat");
	if ((fp = fopen(filename, "rb+" )) == NULL)
	{
		printf(filename);
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(TRAVEL);
	for (i=0;i<len;i++)
	{
		fseek(fp, i * sizeof(TRAVEL), SEEK_SET);
		fread(&t, sizeof(TRAVEL), 1, fp);
		if ((!(traveltime_compare(Time2_1, Time2_2, Time2_3, t.time1_1, t.time1_2, t.time1_3) || traveltime_compare(t.time2_1, t.time2_2, t.time2_3, Time1_1, Time1_2, Time1_3))) || time_compare(Time1_1, Time1_2, Time1_3, 0))
			return 0;
	}
	fseek(fp, 0, SEEK_END);
	strcpy(t.province, Province);
	strcpy(t.city, City);
	strcpy(t.time1_1, Time1_1);
	strcpy(t.time1_2, Time1_2);
	strcpy(t.time1_3, Time1_3);
	strcpy(t.time2_1, Time2_1);
	strcpy(t.time2_2, Time2_2);
	strcpy(t.time2_3, Time2_3);
	fwrite(&t, sizeof(TRAVEL), 1, fp);
	if (fclose(fp) != 0)
	{
		printf(filename);
		delay(3000);
		exit(1);
	}
	return 1;
}

/**
 * @param n user's name
 * @param flag 1 for adding new travel record info now; 2 for not
 */
void record_screen(char* n, int Flag)
{
	int i;
	int zuo[] = {315-2.5,452-15,315-2.5,462-15,305-2.5,457-15,315-2.5,452-15};
	int you[] = {325+2.5,452-15,325+2.5,462-15,335+2.5,457-15,325+2.5,452-15};
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
	puthz(20,40,"防疫行程记录卡",32,34,GREEN);
	setlinestyle(SOLID_LINE,0,3);
	setcolor(DARKGRAY);
	rectangle(20,117+40*Flag,620,117+25+20*14);
	line(35+18*5+15,117+40*Flag,35+18*5+15,117+25+20*14);
	line(35+18*13+45,117+40*Flag,35+18*13+45,117+25+20*14);
	line(35+18*13+15*10+50,117+40*Flag,35+18*13+15*10+50,117+25+20*14);
	setlinestyle(SOLID_LINE,0,1);
	line(20,117+25+40*Flag,620,117+25+40*Flag);
	for (i=1;i<14-2*Flag;i++)
	{
		line(20,117+25+i*20+40*Flag,620,117+25+i*20+40*Flag);
	}
	puthz(35+1.5*18,123+40*Flag,"省份",16,18,DARKGRAY);
	puthz(35+18*8+30,123+40*Flag,"城市",16,18,DARKGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	setcolor(DARKGRAY);
	puthz(35+18*13+45+41.5,123+40*Flag,"去程时间",16,18,DARKGRAY);
	puthz(35+18*13+15*10+50+39.5,123+40*Flag,"返程时间",16,18,DARKGRAY);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	if (Flag == 0)
	{
		bar(20,80,20+26*6+10,110);
		puthz(25,83,"新增行程记录",24,26,WHITE);
		setcolor(DARKGRAY);
		setfillstyle(SOLID_FILL, DARKGRAY);
		setlinestyle(SOLID_LINE,0,3);
		rectangle(320-20-2.5,425+2+5,320-2.5,425+2+5+20);
		rectangle(320+2.5,425+2+5,320+20+2.5,425+2+5+20);
		setlinestyle(SOLID_LINE,0,1);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL, BLUE);
		fillpoly(4,zuo);
		fillpoly(4,you);
	}
	else
	{
		puthz(20,81,"去程时间",24,26,DARKGRAY);
		bar(20+26*4+5,80,20+26*4+5+15*4,80+26);
		outtextxy(20+26*4+8+15*4,80,"/");
		bar(20+26*4+7+15*5,80,20+26*4+7+15*7,80+26);
		outtextxy(20+26*4+10+15*7,80,"/");
		bar(20+26*4+9+15*8,80,20+26*4+9+15*10,80+26);
		puthz(20+26*4+9+15*10+5,81,"返程时间",24,26,DARKGRAY);
		bar(20+26*4+9+15*10+5+26*4+5,80,20+26*4+9+15*14+5+26*4+5,80+26);
		outtextxy(20+26*4+9+15*14+5+26*4+8,80,"/");
		bar(20+26*4+9+15*15+5+26*4+7,80,20+26*4+9+15*17+5+26*4+7,80+26);
		outtextxy(20+26*4+12+15*17+26*4+7+5,80,"/");
		bar(20+26*4+11+15*18+26*4+12,80,20+26*4+11+15*20+26*4+12,80+26);
		puthz(20,111,"目的地",24,26,DARKGRAY);
		bar(20+26*3+20,110,20+26*3+20+26*5+4,110+26);
		puthz(20+26*3+20+15,110+1,"选择省份",24,26,WHITE);
		bar(20+26*3+20+26*5+4+5,110,20+26*3+20+26*5+9+4+26*8,110+26);
		puthz(20+26*3+20+26*5+4+5+52+2,110+1,"选择城市",24,26,WHITE);
		bar(20+26*3+20+26*5+9+4+26*8+5,110,20+26*3+20+26*5+9+4+26*8+5+56,110+26);
		puthz(20+26*3+20+26*5+9+4+26*8+7,110+1,"确定",24,26,WHITE);
		setcolor(GREEN);
		setfillstyle(SOLID_FILL, GREEN);
		bar(20+26*3+20+26*5+9+4+26*8+5+56+25,120,20+26*3+20+26*5+9+4+26*8+5+56+25+56,120+26);
		puthz(20+26*3+20+26*5+9+5+26*8+32+56,120+1,"完成",24,26,WHITE);
	}
}