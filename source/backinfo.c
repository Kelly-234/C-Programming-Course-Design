/**
 * @file backinfo.c
 * @author yangchunru
 * @brief check user's feedback by choosing different types(admin)
 * @date 2021-05-01
 */
#include "public.h"
#include "backinfo.h"

int p17_backinfo(void)
{
    int page = 16, i;
    int total= 0;	//total page number
	int p = 0;	//current page
	int button_coordinate[5][4] = {{20,80,20+7*18+30,80+30},{20+7*18+30,80,20+7*18+30+30+7*18,80+30},
                                   {20+7*18+30+7*18+30,80,20+7*18+30+30+7*18+11*18+30,80+30},{20,80+30,20+10*18+30,80+30+30},
                                   {20+10*18+30,80+30,20+10*18+30+30+6*18,80+30+30}};
    
    clrmous(MouseX,MouseY);
    backinfo_screen();
	delay(300);
    
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(640-68,2,640,34) == 1)   //log out button(go to welcome.c)
        {
			page = 0;
			return page;
		}
		else if(mouse_press(640-68,480-32,640,480) == 1)    //exit button
        {
			page = 18;
			return page;
        }
		else if(mouse_press(640-68*2-20,480-34,640-68-20,480) == 1) //return button(go to glhome.c)
        {
			page = 2;
			return page;
        }
        else if(mouse_press(20,80,20+7*18+30+30+7*18+11*18+30,80+30+30) == 1) //check feedback type choose button
        {
			for (i=0;i<5;i++)
            {
                if (mouse_press(button_coordinate[i][0],button_coordinate[i][1],button_coordinate[i][2],button_coordinate[i][3]) == 1)
                    break;
            }
            do {
				newmouse(&MouseX, &MouseY, &press);
			}while (mouse_press(20,80,20+7*18+30+30+7*18+11*18+30,80+30+30) == 1);
            clrmous(MouseX,MouseY);
            lightbutton(i);
            p = 0;
            total = getfeedback(i, p);
        }
        else if (mouse_press(320 - 20 - 2.5, 440 + 2 + 5, 320 - 2.5, 440 + 2 + 5 + 20) == 1)	//last_page button
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(320 - 20 - 2.5, 440 + 2 + 5, 320 - 2.5, 440 + 2 + 5 + 20) == 1);
            if (p != 0)
			{
				clrmous(MouseX, MouseY);
                p = p - 1;
				getfeedback(i, p);
			}
			else
			{
				clrmous(MouseX, MouseY);
                p = total - 1;
                getfeedback(i, p);
			}
        }
        else if (mouse_press(320 + 2.5, 440 + 2 + 5, 320 + 20 + 2.5, 440 + 2 + 5 + 20) == 1)	//next_page button
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(320 + 2.5, 440 + 2 + 5, 320 + 20 + 2.5, 440 + 2 + 5 + 20) == 1);
            if (p < total - 1)
			{
				clrmous(MouseX, MouseY);
                p = p + 1;
				getfeedback(i, p);
			}
			else
			{
				clrmous(MouseX, MouseY);
                p = 0;
                getfeedback(i, p);
			}
        }
    }
}

void backinfo_screen(void)
{
    int zuo[] = {315 - 2.5, 452, 315 - 2.5, 462, 305 - 2.5, 457, 315 - 2.5, 452};
	int you[] = {325 + 2.5, 452, 325 + 2.5, 462, 335 + 2.5, 457, 325 + 2.5, 452};

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
    setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE,0,1);
	puthz(20,40,"查看用户反馈信息",32,34,BROWN);
    rectangle(20,80,20+7*18+30,80+30);
	puthz(20+16,87,"健康码及行程码",16,18,DARKGRAY);	//jkm
	rectangle(20+7*18+30,80,20+7*18+30+30+7*18,80+30);
	puthz(20+7*18+30+16,87,"防疫行程记录卡",16,18,DARKGRAY);	//record
	rectangle(20+7*18+30+7*18+30,80,20+7*18+30+30+7*18+11*18+30,80+30);
	puthz(20+7*18+30+30+7*18+16,87,"核酸检测预约及结果查询",16,18,DARKGRAY);	//reserve
	rectangle(20,80+30,20+10*18+30,80+30+30);
	puthz(20+16,117,"区域疫情风险等级查询",16,18,DARKGRAY);	//risklook
	rectangle(20+10*18+30,80+30,20+10*18+30+30+6*18,80+30+30);
	puthz(20+10*18+30+16,117,"个人信息完善",16,18,DARKGRAY);	//xxchange
    setlinestyle(SOLID_LINE, 0, 3);
	rectangle(320 - 20 - 2.5, 440 + 2 + 5, 320 - 2.5, 440 + 2 + 5 + 20);
	rectangle(320 + 2.5, 440 + 2 + 5, 320 + 20 + 2.5, 440 + 2 + 5 + 20);
	setlinestyle(SOLID_LINE, 0, 1);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL, BLUE);
	fillpoly(4, zuo);
	fillpoly(4, you);
}

/**
 * @param t the serial number of the button that was clicked
 */
void lightbutton(int t)
{
    char strategy_color[5] = {LIGHTGREEN, GREEN, BLUE, LIGHTBLUE, BROWN};
    int button_coordinate[5][4] = {{20,80,20+7*18+30,80+30},{20+7*18+30,80,20+7*18+30+30+7*18,80+30},
                                   {20+7*18+30+7*18+30,80,20+7*18+30+30+7*18+11*18+30,80+30},{20,80+30,20+10*18+30,80+30+30},
                                   {20+10*18+30,80+30,20+10*18+30+30+6*18,80+30+30}};
    char button_name[5][30] = {"健康码及行程码","防疫行程记录卡","核酸检测预约及结果查询","区域疫情风险等级查询","个人信息完善"};
	int i;
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, WHITE);
    setlinestyle(SOLID_LINE,0,1);
    bar(0,79,640,141);
    for (i=0;i<5;i++)
    {
        rectangle(button_coordinate[i][0],button_coordinate[i][1],button_coordinate[i][2],button_coordinate[i][3]);
        puthz(button_coordinate[i][0]+16,button_coordinate[i][1]+7,button_name[i],16,18,DARKGRAY);
    }
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, strategy_color[t]);
	bar(button_coordinate[t][0],button_coordinate[t][1],button_coordinate[t][2],button_coordinate[t][3]);
    rectangle(button_coordinate[t][0],button_coordinate[t][1],button_coordinate[t][2],button_coordinate[t][3]);
    puthz(button_coordinate[t][0]+16,button_coordinate[t][1]+7,button_name[t],16,18,WHITE);
}

/**
 * @param t the serial number of the button that was clicked-the feedback type to check
 * @param p current page
 * @return int return total page number
 */
int getfeedback(int t, int P)
{
    FILE* fp;
	FEEDBACK fe;
	int i, j, k, len, len_feedback;
    int term = 0;   //the amount of feedback that has been displayed
    char temp_feedback[65] = { '\0' };  //store the truncated string

	setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, WHITE);
    setlinestyle(SOLID_LINE,0,1);
    bar(0,145,640,440);
    rectangle(20,170,620,410);
    for (i=1;i<4;i++)
    {
        line(20,170+20+80*(i-1),620,170+20+80*(i-1));
        line(20,170+80*i,620,170+80*i);
    }
    
	if ((fp = fopen("database\\Feedback.dat", "rb" )) == NULL)
	{
		printf("cannot open database\\Feedback.dat");
		delay(3000);
		exit(1);
	}
    fseek(fp, 0, SEEK_END);
    len = ftell(fp) / sizeof(FEEDBACK);
    for (i = 0; i < len; i++)
    {
        if ((term > (P*3-1)) && (term < (3+P*3)))
		{
            fseek(fp, i * sizeof(FEEDBACK), SEEK_SET);
            if (!fread(&fe, sizeof(FEEDBACK), 1, fp))
            {
                break;
            }
            if (fe.type == (t+1))
            {
                term++;
                if (fe.anonymous_state == 1)    //anonymous feedback
                {
                    puthz(30,170+80*(term-1)+2,"匿名反馈",16,18,DARKGRAY);
                }
                else
                {
                    puthz(30,170+80*(term-1)+2,fe.name,16,18,BLUE);
                    settextjustify(LEFT_TEXT, TOP_TEXT);
                    setcolor(BLUE);
                    outtextxy(40+9*(strlen(fe.name)),170+80*(term-1)+2-5,fe.phone);
                }
                len_feedback = strlen(fe.feedback);
                if (len_feedback%60 == 0)	//count the length of feedback
                {
                    len_feedback = len_feedback/60;
                }
                else
                {
                    len_feedback = len_feedback/60 + 1;
                }
                for (j=0;j<len_feedback;j++)
                {
                    strcpy(temp_feedback,"");
                    strncpy(temp_feedback,fe.feedback+60*j,60);
                    if (temp_feedback[0]>='A' && temp_feedback[0]<='z')
                    {
                        setcolor(DARKGRAY);
                        outtextxy(51,190+80*(term-1)+20*j+2-5,temp_feedback);
                    }
                    else
                    {
                        puthz(51,190+80*(term-1)+20*j+2,temp_feedback,16,18,DARKGRAY);
                    }
                }
            }
        }
    }
    if (fclose(fp) != 0)
    {
        printf("\n cannot database\\Feedback.dat in backinfo.c");
        delay(3000);
        exit(1);
    }
    if (len%3 == 0)	//count total pages
    {
        len = len/3;
    }
    else
    {
        len = len/3 + 1;
    }
	return len;
}