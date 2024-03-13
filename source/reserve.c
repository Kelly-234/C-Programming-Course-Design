/**
 * @file reserve.c
 * @author yangchunru
 * @brief reserve nucleic acid testing and cancle the appointment, view test results
 * @date 2021-04-24 
 */
#include "public.h"
#include "reserve.h"

/**
 * @param u pointer stores user info
 * @param Flag sign login state(1 for login; 0 for not)
 */
int p14_reserve(USER* u, int* Flag)
{
    FILE* fp;
	USER us;
	int i, len, page = 13;
	int reserve_state;	//1 for reserving now; 2 for waiting for result; 3 for appointment been cancel or receive result-reserve available
	int state_reserve = 0;	//reserve button(1 for yes-reserving now; 2 for no-check the appointment)
    int state_hospital = 1;	//1 for SZY; 2 for HUST
	int state_time1 = 1, state_time2 = 1;	//time1 for date; time2 for quantum
	char id[19] = { '\0' };
    char Name[20] = { '\0' };
	char time[10] = { '\0' };	//string to store the date

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
			strcpy(id,us.ID);
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
	reserve_screen(Name);
    reserve_state = getreserveinfo(id);	//get reserve state
	delay(300);
    
    while(1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if(mouse_press(640-68*2-20,480-34,640-68-20,480) == 1)	//return button(go to grhome.c)
		{
			page = 3;
			return page;
		}
		else if(mouse_press(640-68,2,640,34) == 1)	//log out button(go to welcome.c)
		{
			*Flag = 0;
			page = 0;
			return page;
		}
		else if(mouse_press(640-68,480-34,640,480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
		else if((mouse_press(170,110,330,136) == 1) && (reserve_state == 0) && (state_reserve == 0))	//add new reserve button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(170,110,330,136) == 1);
			state_reserve = 1;
			clrmous(MouseX,MouseY);
			draw_reserve(i);
			draw_SZY();
        }
		else if((mouse_press(117,200,231,230) == 1) && (reserve_state == 1) && (state_reserve == 0))	//cancel appointment button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(117,200,231,230) == 1);
			clrmous(MouseX,MouseY);
			delete_reserveinfo(id);
			reserve_state = getreserveinfo(id);
        }
		else if((mouse_press(230,390,300,420) == 1) && (state_reserve == 1))	//cancel button(while making appointment)
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(230,390,300,420) == 1);
			clrmous(MouseX,MouseY);
			getreserveinfo(id);
			state_reserve = 0;
        }
		else if((mouse_press(144,110,292,150) == 1) && (state_reserve == 1))	//hospital-SZY
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(144,110,292,150) == 1);
			clrmous(MouseX,MouseY);
			draw_SZY();
			state_hospital = 1;
			state_time1 = 1;
			state_time2 = 1;
		}
		else if((mouse_press(322,110,434,150) == 1) && (state_reserve == 1))	//hospital-HUST
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(322,110,434,150) == 1);
			clrmous(MouseX,MouseY);
			draw_HUST();
			state_hospital = 2;
			state_time1 = 1;
			state_time2 = 1;
		}
		else if((mouse_press(216,195,311,221) == 1) && (state_reserve == 1))	//date-1
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(216,195,311,221) == 1);
			clrmous(MouseX,MouseY);
			state_time1 = 1;
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
			setfillstyle(SOLID_FILL,WHITE);
			bar(321,195,416,221);	//date2
			bar(426,195,521,221);	//date3
			setfillstyle(SOLID_FILL,LIGHTBLUE);
			bar(216,195,311,221);	//date1
			setcolor(LIGHTGRAY);
			rectangle(216,195,311,221);	//date1
			rectangle(321,195,416,221);	//date2
			rectangle(426,195,521,221);	//date3
			Get_time(2, time, 1);
			outtextxy(343,195-1,time);
			Get_time(3, time, 1);
			outtextxy(50+6*26+20+12+210,195-1,time);
			setcolor(WHITE);
			Get_time(1, time, 1);
			outtextxy(50+6*26+20+12,195-1,time);
			if (state_hospital == 2)
			{
				bar(216+102,192,640,195+30);
			}
		}
		else if((mouse_press(321,195,416,221) == 1) && (state_hospital == 1) && (state_reserve == 1))	//date-2
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(321,195,416,221) == 1);
			clrmous(MouseX,MouseY);
			state_time1 = 2;
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
			setfillstyle(SOLID_FILL,WHITE);
			bar(216,195,311,221);	//date1
			bar(426,195,521,221);	//date3
			setfillstyle(SOLID_FILL,LIGHTBLUE);
			bar(321,195,416,221);	//date2
			setcolor(LIGHTGRAY);
			rectangle(216,195,311,221);
			rectangle(321,195,416,221);
			rectangle(426,195,521,221);
			Get_time(1, time, 1);
			outtextxy(50+6*26+20+12,195-1,time);
			Get_time(3, time, 1);
			outtextxy(50+6*26+20+12+210,195-1,time);
			setcolor(WHITE);
			Get_time(2, time, 1);
			outtextxy(343,195-1,time);
		}
		else if((mouse_press(426,195,521,221) == 1) && (state_hospital == 1) && (state_reserve == 1))	//date-3
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(426,195,521,221) == 1);
			clrmous(MouseX,MouseY);
			state_time1 = 3;
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
			setfillstyle(SOLID_FILL,WHITE);
			bar(216,195,311,221);	//date1
			bar(321,195,416,221);	//date2
			setfillstyle(SOLID_FILL,LIGHTBLUE);
			bar(426,195,521,221);	//date3
			setcolor(LIGHTGRAY);
			rectangle(216,195,311,221);
			rectangle(321,195,416,221);
			rectangle(426,195,521,221);
			Get_time(1, time, 1);
			outtextxy(50+6*26+20+12,195-1,time);
			Get_time(2, time, 1);
			outtextxy(343,195-1,time);
			setcolor(WHITE);
			Get_time(3, time, 1);
			outtextxy(50+6*26+20+12+210,195-1,time);
		}
		else if((mouse_press(117,237,262,257) == 1) && (state_reserve == 1))	//quantum-1
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(117,237,262,257) == 1);
			clrmous(MouseX,MouseY);
			state_time2 = 1;
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
			setfillstyle(SOLID_FILL,WHITE);
			bar(272,237,417,257);
			bar(427,237,572,257);
			setcolor(LIGHTGRAY);
			outtextxy(291,234,"14:00-17:30");
			outtextxy(446,234,"19:00-21:30");
			setfillstyle(SOLID_FILL,LIGHTBLUE);
			bar(117,237,262,257);
			rectangle(117,237,262,257);
			rectangle(272,237,417,257);
			rectangle(427,237,572,257);
			setcolor(WHITE);
			outtextxy(136,234,"07:50-11:00");
			if (state_hospital == 1)
			{
				bar(25+18*4+20,240-3,640,240-3+20);
			}
		}
		else if((mouse_press(272,237,417,257) == 1) && (state_hospital == 2) && (state_reserve == 1))	//quantum-2
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(272,237,417,257) == 1);
			clrmous(MouseX,MouseY);
			state_time2 = 2;
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
			setfillstyle(SOLID_FILL,WHITE);
			bar(117,237,262,257);
			bar(427,237,572,257);
			setcolor(LIGHTGRAY);
			outtextxy(136,234,"07:50-11:00");
			outtextxy(446,234,"19:00-21:30");
			setfillstyle(SOLID_FILL,LIGHTBLUE);
			bar(272,237,417,257);
			rectangle(117,237,262,257);
			rectangle(272,237,417,257);
			rectangle(427,237,572,257);
			setcolor(WHITE);
			outtextxy(291,234,"14:00-17:30");
		}
		else if((mouse_press(427,237,572,257) == 1) && (state_hospital == 2) && (state_reserve == 1))	//quantum-3
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(427,237,572,257) == 1);
			clrmous(MouseX,MouseY);
			state_time2 = 3;
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
			setfillstyle(SOLID_FILL,WHITE);
			bar(117,237,262,257);
			bar(272,237,417,257);
			setcolor(LIGHTGRAY);
			outtextxy(136,234,"07:50-11:00");
			outtextxy(291,234,"14:00-17:30");
			setfillstyle(SOLID_FILL,LIGHTBLUE);
			bar(427,237,572,257);
			rectangle(117,237,262,257);
			rectangle(272,237,417,257);
			rectangle(427,237,572,257);
			setcolor(WHITE);
			outtextxy(446,234,"19:00-21:30");
		}
		else if((mouse_press(340,390,410,420) == 1) && (state_reserve == 1))	//confirm button
        {
			do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(340,390,410,420) == 1);
			clrmous(MouseX,MouseY);
			if (inputreserveinfo(i, state_hospital, state_time1, state_time2))
			{
				reserve_state = getreserveinfo(id);
				state_reserve = 0;
			}
		}
    }
}

/**
 * @param n user's name
 */
void reserve_screen(char* n)
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
	puthz(20,40,"核酸检测预约及结果查询",32,34,BLUE);
}

/**
 * @param ID user's id
 */
int getreserveinfo(char* ID)
{
    FILE* fp;
	RESERVE r;
	int i, len;
	int reserve_state = 0;	//1 for reserving now; 2 for waiting for result; 3 for appointment been cancel or receive result-reserve available
	int flag_reserve = 0;	//find a appointment to show-stop find record of state 4
	int flag_result = 0;	//find a test result to show-stop find record of state 1 or 3
    char time[70] = { '\0' };	//string to store the whole time
	
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,105,640,440);
    puthz(20,80,"预约记录",24,26,LIGHTBLUE);
    puthz(20,240,"上次核酸检测结果",24,26,LIGHTBLUE);
    if ((fp = fopen("database\\Reserve.dat", "rb" )) == NULL)
	{
		printf("cannot open file Reserve.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(RESERVE);
	for (i = (len-1); i >= 0; i--)
	{
		fseek(fp, i * sizeof(RESERVE), SEEK_SET);
		fread(&r, sizeof(RESERVE), 1, fp);
		if (strcmp(ID, r.ID) == 0)
		{
			if (((strcmp(r.state,"1") == 0) || (strcmp(r.state, "3") == 0)) && (flag_reserve == 0))	//have a appointment
            {
                reserve_state = 1;	//can not reserve
				flag_reserve = 1;
				strcpy(time,r.test_time1);
				strcat(time,"  ");
                strcat(time,r.test_time2);
				puthz(20,80+30,"预约时间",16,18,DARKGRAY);
                puthz(20,80+55,"预约医院",16,18,DARKGRAY);
                puthz(20,80+80,"预约状态",16,18,DARKGRAY);
                setcolor(DARKGRAY);
                settextjustify(LEFT_TEXT, TOP_TEXT);
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
                outtextxy(20+4*18,80+30-5,":");
                outtextxy(20+4*18,80+55-5,":");
                outtextxy(20+4*18,80+80-5,":");
                outtextxy(20+18*4+15+10,80+30-5,time);
                if (strcmp(r.hospital, "1") == 0)
                {
                    puthz(20+18*4+25,80+55,"湖北省中医院光谷院区",16,18,DARKGRAY);
                }
                else
                {
                    puthz(20+18*4+25,80+55,"华中科技大学医院",16,18,DARKGRAY);
                }
				if (strcmp(r.state,"1") == 0)
				{
					puthz(20+18*4+25,80+80,"预约成功",16,18,RED);
					setcolor(RED);
					outtextxy(20+4*18+25+18*4,80+80-5,"!");
					puthz(20+18*4+25,80+100,"请在预约时间段内前往预约医院进行核酸检测",16,18,RED);
					setfillstyle(SOLID_FILL, LIGHTGRAY);
					bar(20+18*4+25,80+120,20+18*4+25+26*4+10,80+150);
					puthz(20+18*4+25+6,80+123,"取消预约",24,26,WHITE);
				}
				else
				{
					reserve_state = 2;
					puthz(20+18*4+25,80+80,"等待结果中",16,18,BROWN);
					puthz(20+18*4+25,80+100,"检测结果预计在完成检测半个工作日后更新",16,18,RED);
				}
            }
            else if ((strcmp(r.state, "4") == 0) && (flag_result == 0))	//receive result
            {
                flag_result = 1;
				strcpy(time,r.test_time1);
				strcat(time,"  ");
                strcat(time,r.test_time2);
                puthz(20,240+30,"检测时间",16,18,DARKGRAY);
                puthz(20,240+55,"检测医院",16,18,DARKGRAY);
                puthz(20,240+80,"检测结果",16,18,DARKGRAY);
				puthz(20,240+105,"结果更新时间",16,18,DARKGRAY);
                setcolor(DARKGRAY);
                settextjustify(LEFT_TEXT, TOP_TEXT);
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
                outtextxy(20+4*18,240+30-5,":");
                outtextxy(20+4*18,240+55-5,":");
                outtextxy(20+4*18,240+80-5,":");
				outtextxy(20+6*18,240+105-5,":");
                outtextxy(20+18*4+15+10,240+30-5,time);
				outtextxy(20+18*6+15+10,240+105-5,r.result_time);
                if (strcmp(r.hospital, "1") == 0)
                {
                    puthz(20+18*4+25,240+55,"湖北省中医院光谷院区",16,18,DARKGRAY);
                }
                else
                {
                    puthz(20+18*4+25,240+55,"华中科技大学医院",16,18,DARKGRAY);
                }
                if (strcmp(r.result,"1") == 0)
                {
                    puthz(20+18*4+25,240+80,"阴性",16,18,GREEN);
                }
                else
                {
                    puthz(20+18*4+25,240+80,"阳性",16,18,RED);
                }
            }
		}
		if ((flag_reserve == 1) && (flag_result == 1))
		{
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Reserve.dat");
		delay(3000);
		exit(1);
	}
	if (flag_reserve == 0)
	{
		puthz(20,110,"无预约记录",24,26,LIGHTRED);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		bar(170,110,330,136);
		puthz(20+26*5+20+2,110+1,"预约核酸检测",24,26,WHITE);
	}
	if (flag_result == 0)
	{
		puthz(20,240+30,"无结果",24,26,LIGHTRED);
	}
    return reserve_state;
}

/**
 * @param I the rank of the user in total data file
 */
void draw_reserve(int I)
{
	FILE* fp;
	USER us;

    setfillstyle(SOLID_FILL,WHITE);
	bar(0,105,640,440);
	puthz(20,110,"选择医院",24,26,DARKGRAY);
	puthz(20,195,"可预约检测时间",24,26,DARKGRAY);
	puthz(20,240,"选择时间",16,18,DARKGRAY);
	puthz(20,270,"检测人信息",24,26,DARKGRAY);
	puthz(20,305,"真实姓名",16,18,DARKGRAY);
	puthz(20,330,"身份证号",16,18,DARKGRAY);
	puthz(20,355,"联系电话",16,18,DARKGRAY);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(230,390,300,420);
	puthz(230+10,393,"取消",24,26,WHITE);
	bar(340,390,410,420);
	puthz(340+10,393,"确定",24,26,WHITE);
	if ((fp = fopen("database\\UserData.dat", "rb" )) == NULL)
	{
		printf("cannot open file UserData.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, I * sizeof(USER), SEEK_SET);
	fread(&us, sizeof(USER), 1, fp);
	setcolor(DARKGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	puthz(20+18*4+10,300,us.name,16,18,DARKGRAY);
	outtextxy(20+18*4+10,325,us.ID);
	outtextxy(20+18*4+10,350,us.phone);
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		delay(3000);
		exit(1);
	}
}

void draw_SZY(void)
{
	char time[10] = {'\0'};
	setlinestyle(SOLID_LINE,0,1);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL,WHITE);
	bar(322,110,322+4*18+40,150);
	bar(25+18*4+20,240-3,640,240-3+20);
	bar(20+26*4+15,150+5,640,150+8+30);
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	bar(20+26*4+20,110,20+26*4+20+6*18+40,150);
	rectangle(20+26*4+20,110,20+26*4+20+6*18+40,150);
	puthz(20+26*4+20+21,110+3,"湖北省中医院",16,18,WHITE);
	puthz(20+26*4+20+20+19,110+2+18+2,"光谷院区",16,18,WHITE);
	rectangle(322,110,322+4*18+40,150);
	puthz(322+21,110+2,"华中科技",16,18,LIGHTGRAY);
	puthz(322+21,110+2+18+2,"大学医院",16,18,LIGHTGRAY);
	puthz(20+26*4+20,150+8,"据您",16,18,LIGHTGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(20+26*4+20+36,158-5,"1.2km | ");
	puthz(20+26*4-20+36+15*8,158,"珞瑜路",16,18,LIGHTGRAY);
	outtextxy(20+26*4-20+36+15*8+18*3,158-5,"856");
	puthz(20+26*4-30+36+15*11+18*3,158,"号",16,18,LIGHTGRAY);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
	bar(216,195,311,221);	//date1
	rectangle(216,195,311,221);
	Get_time(1, time, 1);
	setcolor(WHITE);
	outtextxy(50+6*26+20+12,195-1,time);
	setcolor(LIGHTGRAY);
	rectangle(321,195,416,221);
	Get_time(2, time, 1);
	outtextxy(343,195-1,time);
	rectangle(426,195,521,221);
	Get_time(3, time, 1);
	outtextxy(50+6*26+20+12+210,195-1,time);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	bar(117,237,262,257);
	rectangle(117,237,262,257);
	setcolor(WHITE);
	outtextxy(136,234,"07:50-11:00");
}

void draw_HUST(void)
{
	char time[10] = {'\0'};
	setfillstyle(SOLID_FILL,WHITE);
	bar(20+26*4+15,150+5,640,150+8+30);
	bar(216+102,192,640,195+30);
	bar(20+26*4+20,110,20+26*4+20+6*18+40,150);	//SZY
	bar(272,237,417,257);	//quantum2
	bar(427,237,572,257);	//quantum3
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	bar(322,110,322+4*18+40,150);	//HUST
	bar(216,195,311,221);	//date1
	bar(117,237,262,257);	//quantum1
	puthz(20+26*4+20+21,110+3,"湖北省中医院",16,18,LIGHTGRAY);
	puthz(20+26*4+20+20+19,110+2+18+2,"光谷院区",16,18,LIGHTGRAY);
	puthz(322+21,110+2,"华中科技",16,18,WHITE);
	puthz(322+21,110+2+18+2,"大学医院",16,18,WHITE);
	puthz(20+26*4+20,150+8,"据您",16,18,LIGHTGRAY);
	setcolor(LIGHTGRAY);
	setlinestyle(SOLID_LINE,0,1);
	rectangle(20+26*4+20,110,20+26*4+20+6*18+40,150);	//SZY
	rectangle(322,110,322+4*18+40,150);	//HUST
	rectangle(216,195,311,221);	//date
	rectangle(117,237,262,257);	//quantum1
	rectangle(272,237,417,257);	//quantum2
	rectangle(427,237,572,257);	//quantum3
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	outtextxy(20+26*4+20+36,158-5,"607m | ");
	puthz(20+26*4-20+36+15*8,158,"珞瑜路",16,18,LIGHTGRAY);
	outtextxy(20+26*4-20+36+15*8+18*3,158-5,"1037");
	puthz(20+26*4-30+36+15*12+18*3,158,"号",16,18,LIGHTGRAY);
	outtextxy(291,234,"14:00-17:30");
	outtextxy(446,234,"19:00-21:30");
	setcolor(WHITE);
	outtextxy(136,234,"07:50-11:00");
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
	Get_time(1, time, 1);
	outtextxy(50+6*26+20+12,195-1,time);
}

/**
 * @param ID user's id
 */
void delete_reserveinfo(char* ID)
{
    FILE* fp;
	RESERVE r;
	int i, len;

    if ((fp = fopen("database\\Reserve.dat", "rb+" )) == NULL)
	{
		printf("cannot open file Reserve.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(RESERVE);
	for (i = (len-1); i >= 0; i--)
	{
		fseek(fp, i * sizeof(RESERVE), SEEK_SET);
		fread(&r, sizeof(RESERVE), 1, fp);
		if (strcmp(ID, r.ID) == 0)
		{
			strcpy(r.state,"2");
			fseek(fp, i * sizeof(RESERVE), SEEK_SET);
			fwrite(&r, sizeof(RESERVE), 1, fp);
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Reserve.dat");
		delay(3000);
		exit(1);
	}
}

/**
 * @param I  the rank of the user in total data file
 * @param State_hospital 1 for SZY; 2 for HUST
 * @param State_time1 time for date
 * @param State_time2 time for quantum
 * @return int return 1 for appointment added succefully; return 2 for not
 */
int inputreserveinfo(int I, int State_hospital, int State_time1, int State_time2)
{
	FILE* fp;
	USER u;
	RESERVE r;
	char name[20] = { '\0' };
	char id[19] = { '\0' };
	char phone[12] = { '\0' };
	char temp[50] = { '\0' };	//store the string convert by user's serial number
	char temp_time[50] = { '\0' };	//store the string convert by reserve date
	
	if ((fp = fopen("database\\UserData.dat", "rb" )) == NULL)
	{
		printf("cannot open file UserData.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, I * sizeof(USER), SEEK_SET);
	fread(&u, sizeof(USER), 1, fp);
	strcpy(id,u.ID);
	strcpy(name,u.name);
	strcpy(phone,u.phone);
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		delay(3000);
		exit(1);
	}
	if ((fp = fopen("database\\Reserve.dat", "rb+" )) == NULL)
	{
		printf("cannot open file Reserve.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	fread(&r, sizeof(RESERVE), 1, fp);
	strcpy(r.name,name);
	strcpy(r.ID,id);
	strcpy(r.phone,phone);
	itoa(State_hospital,temp,10);
	strcpy(r.hospital,temp);
	Get_time(State_time1, temp_time, 2);
	strcpy(r.test_time1,temp_time);
	if (State_time2 == 1)
	{
		strcpy(r.test_time2,"07:50-11:00");
	}
	else if (State_time2 == 2)
	{
		strcpy(r.test_time2,"14:00-17:30");
	}
	else
	{
		strcpy(r.test_time2,"19:00-21:30");	
	}
	strcpy(r.result_time,"");
	strcpy(r.result,"");
	strcpy(r.state,"1");
	if (fwrite(&r, sizeof(RESERVE), 1, fp))
	{
		if (fclose(fp) != 0)
		{
			printf("\n cannot close Reserve.dat");
			delay(3000);
			exit(1);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}