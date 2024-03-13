/**
 * @file glhome.c
 * @author yangchunru
 * @brief main interface for admin
 * @date 2021-04-24
 */
#include "public.h"
#include "glhome.h"

int p3_glhome(void)
{
    FILE* fp;
	ADMIN ad;
	int page = 2, i;
	char Time[40]={'\0'};	//record the logout time

    clrmous(MouseX,MouseY);
    glhome_screen();
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
		else if(mouse_press(120,140,520,190) == 1)	//change riskinfo(go to risknew.c) 
        {
			page = 12;
			return page;
        } 
		else if(mouse_press(120,210,520,290) == 1)  //change reserve state(go to result.c)
        {
			page = 14;
			return page;
        }
		else if(mouse_press(120,310,520,360) == 1)  //look feedback(go to backinfo.c)
        {
			page = 16;
			return page;
        }
	}
}

void glhome_screen(void)
{
	cleardevice();
	//bar(640-68,2,640,34);
	puthz(640-68,2,"登出",32,34,LIGHTGRAY);
	//bar(640-68-136-20,2,640-88,34);
	puthz(640-68-136+14,2,"管理员",32,34,DARKGRAY);
	//bar(640-68,480-32,640,480);
    puthz(640-68,480-34,"退出",32,34,LIGHTGRAY);
    setbkcolor(WHITE);
    setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTRED);
	bar(120,140,520,190);
	rectangle(120,140,520,190);
	puthz(191,153,"区域疫情数据信息修改",24,26,WHITE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar(120,210,520,290);
	rectangle(120,210,520,290);
	puthz(191,223,"用户核酸检测预约状态",24,26,WHITE);
	puthz(204,290-13-24,"查看及检测结果通知",24,26,WHITE);
	setfillstyle(SOLID_FILL, BROWN);
	bar(120,310,520,360);
	rectangle(120,310,520,360);
	puthz(243,323,"查看用户反馈",24,26,WHITE);
}
