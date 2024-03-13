/**
 * @file main.c
 * @author yangchunru
 * @brief main control function, including program initialization page turns
 * @date 2021-04-30
 */
#include "public.h"
#include "main.h"

void main(void)
{
	//initialize
	int page = 0, flag = 0;
	int graphdriver = VGA;
	int graphmode = VGAHI;
	USER u;
	memset(&u,'\0',sizeof(USER));
	initgraph(&graphdriver, &graphmode, "C:\\borlandc\\bgi");
	mouseinit();
	
	//page forwarding
	while(1)
	{
		switch(page)
		{
			case 0:	//go to welcome.c
			    page = p1_welcome();
				break;
				
			case 1:	//go to home.c
			    page = p2_home(&u, &flag);
				break;
			
			case 2:	//go to glhome.c
			    page = p3_glhome();
				break;
				
			case 3:	//go to grhome.c
			    page = p4_grhome(&u, &flag);
				break;
				
			case 4:	//go to login.c
			    page = p5_login(&u, &flag);
				break;
			
			case 5:	//go to gllogin.c
			    page = p6_gllogin();
				break;
				
			case 6:	//go to cclogin.c
			    page = p7_cclogin(&u);
				break;
				
			case 7:	//go to mmchange.c
			    page = p8_mmchange(&u);
				break;
				
			case 8:	//go to jkm.c
			    page = p9_jkm(&u, &flag);
				break;
					
			case 9:	//go to risklook.c
			    page = p10_risklook(&u, &flag);
				break;
				
			case 10:	//go to xxchange.c
			    page = p11_xxchange(&u, &flag);
				break;
				
			case 11:	//go to record.c
				page = p12_record(&u, &flag);
				break;
				
			case 12:	//go to risknew.c
				page = p13_risknew();
				break;

			case 13:	//go to reserve.c
				page = p14_reserve(&u, &flag);
				break;

			case 14:	//go to result.c
				page = p15_result();
				break;

			case 15:	//go to feedback.c
				page = p16_feedback(&u, &flag);
				break;

			case 16:	//go to backinfo.c
				page = p17_backinfo();
				break;

			/*case 17:	//go to riskinfo.c
				page = p18_riskinfo();
				break;*/
				
			case 18:	//normal exit
				do
				{
					newmouse(&MouseX,&MouseY,&press);
				} while (mouse_press(0,0,640,480)==1);
			    closegraph();
				fcloseall();
				exit(0);

			default:
			    closegraph();
				fcloseall();
				exit(0);
		}
	}
}