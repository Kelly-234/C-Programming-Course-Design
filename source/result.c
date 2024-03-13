/**
 * @file result.c
 * @author yangchunru
 * @brief update appointment state and nucleic acid testing result(admin)
 * @date 2021-04-23
 */
#include "public.h"
#include "result.h"

int p15_result(void)
{
	FILE *fp;
	ADMIN ad;
	int page = 14, i;
	int p = 0;	//current page
	int total = 0;	//total page
	int term = 0;	//the number of users of the current page
	int item = 0;	//the line number of the one being changing
	int flag = 0;	//whether reserveinfo is in modified state
	int reserve_state = 1;	//1 for reserving now; 2 for waiting for result; 3 for receive result
	int result_state = 0;	//1 for negative; 2 for positive

	clrmous(MouseX, MouseY);
	result_screen();
	total = Getreserveinfo(p);	//get total number of reserve info
	if (total % 13 == 0)	//calculate total page
	{
		total = total / 13;
	}
	else
	{
		term = total % 13;
		total = total / 13 + 1;
	}
	delay(300);

	while (1)
	{
		newmouse(&MouseX, &MouseY, &press);
		if (mouse_press(640 - 68, 2, 640, 34) == 1)	//log out button(go to welcome.c)
		{
			page = 0;
			return page;
		}
		else if (mouse_press(640 - 68, 480 - 32, 640, 480) == 1)	//exit button
		{
			page = 18;
			return page;
		}
		else if (mouse_press(640 - 68 * 2 - 20, 480 - 34, 640 - 68 - 20, 480) == 1)	//return button(go to glhome.c)
		{
			page = 2;
			return page;
		}
		else if ((mouse_press(320 - 20 - 2.5, 440 + 2 + 5, 320 - 2.5, 440 + 2 + 5 + 20) == 1) && (flag == 0))	//last_page button
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(320 - 20 - 2.5, 440 + 2 + 5, 320 - 2.5, 440 + 2 + 5 + 20) == 1);
			if (p != 0)
			{
				clrmous(MouseX, MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 120 - 2 + 52, 640, 440 + 2);
				setcolor(DARKGRAY);
				setlinestyle(SOLID_LINE, 0, 3);
				line(0, 120 - 2 + 52, 640, 120 - 2 + 52);
				line(0, 440 + 2, 640, 440 + 2);
				setlinestyle(SOLID_LINE, 0, 1);
				for (i = 1; i < 14; i++)
				{
					line(0, 120 - 2 + 52 + 20.9 * i, 640, 120 - 2 + 52 + 20.9 * i);
				}
				line(20 + 4 * 18, 120 - 2 + 26, 20 + 4 * 18, 440);	//name
				line(40 + 4 * 18 + 15 * 18, 120 - 2 + 26, 40 + 4 * 18 + 15 * 18, 440);	//id
				line(60 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 2 + 26, 60 + 4 * 18 + 15 * 18 + 26 * 4, 440);	//reserve state
				p = p - 1;
				Getreserveinfo(p);
			}
			else
			{
				clrmous(MouseX, MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 120 - 2 + 52, 640, 440 + 2);
				setcolor(DARKGRAY);
				setlinestyle(SOLID_LINE, 0, 3);
				line(0, 120 - 2 + 52, 640, 120 - 2 + 52);
				line(0, 440 + 2, 640, 440 + 2);
				setlinestyle(SOLID_LINE, 0, 1);
				for (i = 1; i < 14; i++)
				{
					line(0, 120 - 2 + 52 + 20.9 * i, 640, 120 - 2 + 52 + 20.9 * i);
				}
				line(20 + 4 * 18, 120 - 2 + 26, 20 + 4 * 18, 440);	//name
				line(40 + 4 * 18 + 15 * 18, 120 - 2 + 26, 40 + 4 * 18 + 15 * 18, 440);	//id
				line(60 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 2 + 26, 60 + 4 * 18 + 15 * 18 + 26 * 4, 440);	//reserve state
				p = total - 1;
				Getreserveinfo(p);
			}
		}
		else if ((mouse_press(320 + 2.5, 440 + 2 + 5, 320 + 20 + 2.5, 440 + 2 + 5 + 20) == 1) && (flag == 0))	//next_page button
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(320 + 2.5, 440 + 2 + 5, 320 + 20 + 2.5, 440 + 2 + 5 + 20) == 1);
			if (p < total - 1)
			{
				clrmous(MouseX, MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 120 - 2 + 52, 640, 440 + 2);
				setcolor(DARKGRAY);
				setlinestyle(SOLID_LINE, 0, 3);
				line(0, 120 - 2 + 52, 640, 120 - 2 + 52);
				line(0, 440 + 2, 640, 440 + 2);
				setlinestyle(SOLID_LINE, 0, 1);
				for (i = 1; i < 14; i++)
				{
					line(0, 120 - 2 + 52 + 20.9 * i, 640, 120 - 2 + 52 + 20.9 * i);
				}
				line(20 + 4 * 18, 120 - 2 + 26, 20 + 4 * 18, 440);	//name
				line(40 + 4 * 18 + 15 * 18, 120 - 2 + 26, 40 + 4 * 18 + 15 * 18, 440);	//id
				line(60 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 2 + 26, 60 + 4 * 18 + 15 * 18 + 26 * 4, 440);	//reserve state
				p = p + 1;
				Getreserveinfo(p);
			}
			else
			{
				clrmous(MouseX, MouseY);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, WHITE);
				bar(0, 120 - 2 + 52, 640, 440 + 2);
				setcolor(DARKGRAY);
				setlinestyle(SOLID_LINE, 0, 3);
				line(0, 120 - 2 + 52, 640, 120 - 2 + 52);
				line(0, 440 + 2, 640, 440 + 2);
				setlinestyle(SOLID_LINE, 0, 1);
				for (i = 1; i < 14; i++)
				{
					line(0, 120 - 2 + 52 + 20.9 * i, 640, 120 - 2 + 52 + 20.9 * i);
				}
				line(20 + 4 * 18, 120 - 2 + 26, 20 + 4 * 18, 440);	//name
				line(40 + 4 * 18 + 15 * 18, 120 - 2 + 26, 40 + 4 * 18 + 15 * 18, 440);	//id
				line(60 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 2 + 26, 60 + 4 * 18 + 15 * 18 + 26 * 4, 440);	//reserve state
				p = 0;
				Getreserveinfo(p);
			}
		}
		else if ((mouse_press(0, 120 - 2 + 52, 640, 440 + 2) == 1) && (flag == 0))	//make change
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(0, 120 - 2 + 52, 640, 440 + 2) == 1);
			clrmous(MouseX, MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 120 - 2 + 52, 640, 440 + 2);
			for (i = 1; i < 14; i++)
			{
				if ((MouseY > (120 - 2 + 52 + (i - 1) * 20.9)) && (MouseY < (120 - 2 + 72.9 + (i - 1) * 20.9)))
				{
					item = i - 1;	//get the line number of the changing item
					break;
				}
			}
			if ((p < total - 1) || (i <= term))	//the click line is in the modifiable range
			{
				flag = 1;
				setfillstyle(SOLID_FILL, LIGHTCYAN);
				bar(0, 120 - 2 + 52 + (i - 1) * 20.9, 640, 120 - 2 + 72.9 + (i - 1) * 20.9);
				draw_statechange();
			}
			else	//click on the blank area
			{
				flag = 0;
			}
			clrmous(MouseX, MouseY);
			setcolor(DARKGRAY);
			setlinestyle(SOLID_LINE, 0, 3);
			line(0, 120 - 2 + 52, 640, 120 - 2 + 52);
			line(0, 440 + 2, 640, 440 + 2);
			setlinestyle(SOLID_LINE, 0, 1);
			for (i = 1; i < 14; i++)
			{
				line(0, 120 - 2 + 52 + 20.9 * i, 640, 120 - 2 + 52 + 20.9 * i);
			}
			line(20 + 4 * 18, 120 - 2 + 26, 20 + 4 * 18, 440);	//name
			line(40 + 4 * 18 + 15 * 18, 120 - 2 + 26, 40 + 4 * 18 + 15 * 18, 440);	//id
			line(60 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 2 + 26, 60 + 4 * 18 + 15 * 18 + 26 * 4, 440);	//reserve state
			Getreserveinfo(p);
			reserve_state = 1;
			result_state = 0;
		}
		else if ((mouse_press(20, 85 + 30, 20 + 16, 85 + 30 + 16) == 1) && (flag == 1))	//reserve state-reserving
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(20, 85 + 30, 20 + 16, 85 + 30 + 16) == 1);
			clrmous(MouseX, MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(40 + 4 * 18 + 15 * 18, 80, 555, 140);
			fillellipse(20 + 8, 85 + 30 + 8, 8, 8);	//waiting for result
			fillellipse(20 + 8 + 4 * 18 + 10, 85 + 30 + 8, 8, 8);	//receive result
			setlinestyle(SOLID_LINE, 0, 1);
			circle(20 + 8, 85 + 30 + 8, 8);	//reserving
			circle(20 + 8 + 4 * 18 + 10, 85 + 30 + 8, 8);	//waiting for result
			circle(20 + 8 + 9 * 18 + 20, 85 + 30 + 8, 8);	//receive result
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(20 + 8, 85 + 30 + 8, 5, 5);	//reserving
			reserve_state = 1;
		}
		else if ((mouse_press(20 + 4 * 18 + 10, 85 + 30, 20 + 4 * 18 + 26, 85 + 56) == 1) && (flag == 1))	//reserve state-waiting for result
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(20 + 4 * 18 + 10, 85 + 30, 20 + 4 * 18 + 26, 85 + 56) == 1);
			clrmous(MouseX, MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			bar(40 + 4 * 18 + 15 * 18, 80, 555, 140);
			fillellipse(20 + 8, 85 + 30 + 8, 8, 8);	//reserving
			fillellipse(20 + 8 + 9 * 18 + 20, 85 + 30 + 8, 8, 8);	//receive result
			setlinestyle(SOLID_LINE, 0, 1);
			circle(20 + 8, 85 + 30 + 8, 8);	//reserving
			circle(20 + 8 + 4 * 18 + 10, 85 + 30 + 8, 8);	//waiting for result
			circle(20 + 8 + 9 * 18 + 20, 85 + 30 + 8, 8);	//receive result
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(20 + 8 + 4 * 18 + 10, 85 + 30 + 8, 5, 5);	//reserving
			reserve_state = 2;
		}
		else if ((mouse_press(20 + 9 * 18 + 20, 85 + 30, 20 + 16 + 9 * 18 + 20, 85 + 30 + 16) == 1) && (flag == 1)) //reserve state-receive result
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(20 + 9 * 18 + 20, 85 + 30, 20 + 16 + 9 * 18 + 20, 85 + 30 + 16) == 1);
			clrmous(MouseX, MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(20 + 8, 85 + 30 + 8, 8, 8);	//reserving
			fillellipse(20 + 8 + 4 * 18 + 10, 85 + 30 + 8, 8, 8);	//waiting for result
			setlinestyle(SOLID_LINE, 0, 1);
			circle(20 + 8, 85 + 30 + 8, 8);	//reserving
			circle(20 + 8 + 4 * 18 + 10, 85 + 30 + 8, 8);	//waiting for result
			circle(20 + 8 + 9 * 18 + 20, 85 + 30 + 8, 8);	//receive result
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(20 + 8 + 9 * 18 + 20, 85 + 30 + 8, 5, 5);	//reserving
			reserve_state = 3;
			result_state = 1;
			draw_result();
		}
		else if ((mouse_press(40 + 4 * 18 + 15 * 18 + 10, 85 + 30, 40 + 4 * 18 + 15 * 18 + 10 + 16, 85 + 30 + 16) == 1) && (flag == 1) && (reserve_state == 3))	//result-negative
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(40 + 4 * 18 + 15 * 18 + 10, 85 + 30, 40 + 4 * 18 + 15 * 18 + 10 + 16, 85 + 30 + 16) == 1);
			clrmous(MouseX, MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(40 + 4 * 18 + 15 * 18 + 10 + 8 + 36 + 20, 115 + 8, 8, 8);	//positive
			setlinestyle(SOLID_LINE, 0, 1);
			circle(40 + 4 * 18 + 15 * 18 + 10 + 8, 85 + 30 + 8, 8);	//negative
			circle(40 + 4 * 18 + 15 * 18 + 10 + 8 + 36 + 20, 115 + 8, 8);	//positive
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(40 + 4 * 18 + 15 * 18 + 10 + 8, 85 + 30 + 8, 5, 5);	//negative
			result_state = 1;
		}
		else if ((mouse_press(40 + 4 * 18 + 15 * 18 + 10 + 36 + 20, 115, 40 + 4 * 18 + 15 * 18 + 10 + 16 + 36 + 20, 115 + 16) == 1) && (flag == 1) && (reserve_state == 3))	//result-positive
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(40 + 4 * 18 + 15 * 18 + 10 + 36 + 20, 115, 40 + 4 * 18 + 15 * 18 + 10 + 16 + 36 + 20, 115 + 16) == 1);
			clrmous(MouseX, MouseY);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(40 + 4 * 18 + 15 * 18 + 10 + 8, 85 + 30 + 8, 8, 8);	//negative
			setlinestyle(SOLID_LINE, 0, 1);
			circle(40 + 4 * 18 + 15 * 18 + 10 + 8, 85 + 30 + 8, 8);	//negative
			circle(40 + 4 * 18 + 15 * 18 + 10 + 8 + 36 + 20, 115 + 8, 8);	//positive
			setfillstyle(SOLID_FILL, DARKGRAY);
			fillellipse(40 + 4 * 18 + 15 * 18 + 10 + 8 + 36 + 20, 115 + 8, 5, 5);	//positive
			result_state = 2;
		}
		else if ((mouse_press(560, 85, 620, 85 + 26) == 1) && (flag == 1))	//cancel button
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(560, 85, 620, 85 + 26) == 1);
			clrmous(MouseX, MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 80, 640, 140);
			bar(0, 120 - 2 + 52, 640, 440 + 2);
			setcolor(DARKGRAY);
			setlinestyle(SOLID_LINE, 0, 3);
			line(0, 120 - 2 + 52, 640, 120 - 2 + 52);
			line(0, 440 + 2, 640, 440 + 2);
			setlinestyle(SOLID_LINE, 0, 1);
			for (i = 1; i < 14; i++)
			{
				line(0, 120 - 2 + 52 + 20.9 * i, 640, 120 - 2 + 52 + 20.9 * i);
			}
			line(20 + 4 * 18, 120 - 2 + 26, 20 + 4 * 18, 440);	//name
			line(40 + 4 * 18 + 15 * 18, 120 - 2 + 26, 40 + 4 * 18 + 15 * 18, 440);	//id
			line(60 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 2 + 26, 60 + 4 * 18 + 15 * 18 + 26 * 4, 440);	//reserve state
			Getreserveinfo(p);
			flag = 0;
		}
		else if ((mouse_press(560, 85 + 30, 620, 85 + 30 + 26) == 1) && (flag == 1))	//confirm button
		{
			do
			{
				newmouse(&MouseX, &MouseY, &press);
			} while (mouse_press(560, 85 + 30, 620, 85 + 30 + 26) == 1);
			Inputreserveinfo(item, p, reserve_state, result_state);
			clrmous(MouseX, MouseY);
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			bar(0, 80, 640, 140);
			bar(0, 120 - 2 + 52, 640, 440 + 2);
			setcolor(DARKGRAY);
			setlinestyle(SOLID_LINE, 0, 3);
			line(0, 120 - 2 + 52, 640, 120 - 2 + 52);
			line(0, 440 + 2, 640, 440 + 2);
			setlinestyle(SOLID_LINE, 0, 1);
			for (i = 1; i < 14; i++)
			{
				line(0, 120 - 2 + 52 + 20.9 * i, 640, 120 - 2 + 52 + 20.9 * i);
			}
			line(20 + 4 * 18, 120 - 2 + 26, 20 + 4 * 18, 440);	//name
			line(40 + 4 * 18 + 15 * 18, 120 - 2 + 26, 40 + 4 * 18 + 15 * 18, 440);	//id
			line(60 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 2 + 26, 60 + 4 * 18 + 15 * 18 + 26 * 4, 440);	//reserve state
			Getreserveinfo(p);
			flag = 0;
		}
	}
}

/**
 * @param P current page
 * @return int return total number of vaid reservation info
 */
int Getreserveinfo(int P)
{
	FILE *fp;
	RESERVE r;
	int i, len;
	int total = 0;	//total number of valid reserve info
	int term = 0;	//the interval of reservation info to be displayed

	if ((fp = fopen("database\\Reserve.dat", "rb")) == NULL)
	{
		printf("cannot open database\\Reserve.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(RESERVE);
	if (P == 0) //obtain the amount of information available
	{
		for (i = 0; i < len; i++)
		{
			fseek(fp, i * sizeof(RESERVE), SEEK_SET);
			fread(&r, sizeof(RESERVE), 1, fp);
			if (strcmp(r.state, "2") != 0)
			{
				total++;
			}
		}
	}
	for (i = 0; i < len; i++)
	{
		if ((term > (P * 13 - 1)) && (term < (13 + P * 13)))
		{
			fseek(fp, i * sizeof(RESERVE), SEEK_SET);
			fread(&r, sizeof(RESERVE), 1, fp);
			if (strcmp(r.state, "2") != 0)
			{
				puthz(11, 120 - 1 + 52 + 20.9 * term + 2.5, r.name, 16, 18, BLUE);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
				setcolor(BLUE);
				outtextxy(31 + 4 * 18, 115 - 1 + 52 + 20.9 * term + 2.5, r.ID);
				if (strcmp(r.state, "1") == 0)
				{
					puthz(67 + 4 * 18 + 15 * 18, 120 - 1 + 52 + 20.9 * term + 2.5, "预约中", 16, 18, BLUE);
				}
				else if (strcmp(r.state, "3") == 0)
				{
					puthz(67 + 4 * 18 + 15 * 18, 120 - 1 + 52 + 20.9 * term + 2.5, "等待结果", 16, 18, BLUE);
				}
				else
				{
					puthz(67 + 4 * 18 + 15 * 18, 120 - 1 + 52 + 20.9 * term + 2.5, "结果已出", 16, 18, BLUE);
					if (strcmp(r.result, "1") == 0)
					{
						puthz(110 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 1 + 52 + 20.9 * term + 2.5, "阴性", 16, 18, GREEN);
					}
					else
					{
						puthz(110 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 1 + 52 + 20.9 * term + 2.5, "阳性", 16, 18, RED);
					}
				}
				term++;
			}
		}
		else
		{
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Reserve.dat in result.c");
		delay(3000);
		exit(1);
	}
	return total;
}

void result_screen(void)
{
	int i;
	int zuo[] = {315 - 2.5, 452, 315 - 2.5, 462, 305 - 2.5, 457, 315 - 2.5, 452};
	int you[] = {325 + 2.5, 452, 325 + 2.5, 462, 335 + 2.5, 457, 325 + 2.5, 452};

	cleardevice();
	setbkcolor(WHITE);
	setcolor(DARKGRAY);
	//bar(640-68,2,640,34);
	puthz(640 - 68, 2, "登出", 32, 34, LIGHTGRAY);
	//bar(640-68-136-20,2,640-88,34);
	puthz(640 - 68 - 136 + 14, 2, "管理员", 32, 34, DARKGRAY);
	//bar(640-68,480-32,640,480);
	puthz(640 - 68, 480 - 34, "退出", 32, 34, LIGHTGRAY);
	//bar(640-68*2-20,480-34,640-68-20,480);
	puthz(640 - 68 * 2 - 20, 480 - 34, "返回", 32, 34, LIGHTGRAY);
	puthz(20, 6, "用户核酸检测预约状态", 32, 34, LIGHTBLUE);
	puthz(20, 40, "查看及检测结果通知", 32, 34, LIGHTBLUE);
	setlinestyle(SOLID_LINE, 0, 3);
	line(0, 120 - 2 + 26, 640, 120 - 2 + 26);
	puthz(20, 120 + 26, "姓名", 24, 26, DARKGRAY);
	puthz(114 + 4 * 18, 120 + 26, "身份证号", 24, 26, DARKGRAY);
	puthz(51 + 4 * 18 + 15 * 18, 120 + 26, "预约状态", 24, 26, DARKGRAY);
	puthz(76 + 4 * 18 + 15 * 18 + 26 * 4, 120 + 26, "检测结果", 24, 26, DARKGRAY);
	line(0, 120 - 2 + 52, 640, 120 - 2 + 52);
	line(0, 440 + 2, 640, 440 + 2);
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 1; i < 14; i++)
	{
		line(0, 120 - 2 + 52 + 20.9 * i, 640, 120 - 2 + 52 + 20.9 * i);
	}
	line(20 + 4 * 18, 120 - 2 + 26, 20 + 4 * 18, 440);	//name
	line(40 + 4 * 18 + 15 * 18, 120 - 2 + 26, 40 + 4 * 18 + 15 * 18, 440);	//id
	line(60 + 4 * 18 + 15 * 18 + 26 * 4, 120 - 2 + 26, 60 + 4 * 18 + 15 * 18 + 26 * 4, 440);	//reserve state
	setlinestyle(SOLID_LINE, 0, 3);
	rectangle(320 - 20 - 2.5, 440 + 2 + 5, 320 - 2.5, 440 + 2 + 5 + 20);
	rectangle(320 + 2.5, 440 + 2 + 5, 320 + 20 + 2.5, 440 + 2 + 5 + 20);
	setlinestyle(SOLID_LINE, 0, 1);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL, BLUE);
	fillpoly(4, zuo);
	fillpoly(4, you);
}

void draw_statechange(void)
{
	puthz(20, 85, "预约状态修改", 24, 26, DARKGRAY);
	setcolor(DARKGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	circle(20 + 8, 85 + 30 + 8, 8);
	puthz(20 + 18 + 3, 115, "预约中", 16, 18, DARKGRAY);
	circle(20 + 8 + 4 * 18 + 10, 85 + 30 + 8, 8);
	puthz(20 + 18 + 4 * 18 + 10 + 3, 115, "等待结果", 16, 18, DARKGRAY);
	circle(20 + 8 + 9 * 18 + 20, 85 + 30 + 8, 8);
	puthz(20 + 18 + 9 * 18 + 20 + 3, 115, "结果已出", 16, 18, DARKGRAY);
	setfillstyle(SOLID_FILL, DARKGRAY);
	fillellipse(20 + 8, 85 + 30 + 8, 5, 5);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(560, 82, 620, 82 + 26);
	bar(560, 82 + 30, 620, 82 + 30 + 26);
	puthz(560 + 7, 83, "取消", 24, 26, WHITE);
	puthz(560 + 7, 82 + 31, "确定", 24, 26, WHITE);
}

void draw_result(void)
{
	puthz(40 + 4 * 18 + 15 * 18 + 10, 85, "检测结果", 24, 26, DARKGRAY);
	setcolor(DARKGRAY);
	circle(40 + 4 * 18 + 15 * 18 + 10 + 8, 85 + 30 + 8, 8);
	puthz(40 + 4 * 18 + 15 * 18 + 10 + 18, 115, "阴性", 16, 18, DARKGRAY);
	circle(40 + 4 * 18 + 15 * 18 + 10 + 8 + 36 + 20, 115 + 8, 8);
	puthz(40 + 4 * 18 + 15 * 18 + 10 + 18 * 3 + 20 + 18, 115, "阳性", 16, 18, DARKGRAY);
	setfillstyle(SOLID_FILL, DARKGRAY);
	fillellipse(40 + 4 * 18 + 15 * 18 + 10 + 8, 85 + 30 + 8, 5, 5);
}

/**
 * @brief input appointment state change and nucleic acid testing result to the file
 * @param I the line number of the one being changing
 * @param P current page
 * @param Reserve_state new reserve state
 * @param Result_state new testing result
 */
void Inputreserveinfo(int I, int P, int Reserve_state, int Result_state)
{
	FILE *fp;
	RESERVE r;
	USER u;
	int i, len;
	int total = 0;	// number of valid info read
	char ID[19] = {'\0'};	//to identifying user info
	char time[100] = {'\0'};

	if ((fp = fopen("database\\Reserve.dat", "rb+")) == NULL)
	{
		printf("cannot open database\\Reserve.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(RESERVE);
	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(RESERVE), SEEK_SET);
		fread(&r, sizeof(RESERVE), 1, fp);
		if (strcmp(r.state, "2") != 0)	//info is valid
		{
			total++;
		}
		if ((total-1) == (I + P * 13))	//info needs to be modified
		{
			strcpy(ID, r.ID);
			if (Reserve_state == 1)
			{
				strcpy(r.state, "1");
			}
			else if (Reserve_state == 2)
			{
				strcpy(r.state, "3");
			}
			else
			{
				strcpy(r.state, "4");
				if (Result_state == 1)
				{
					strcpy(r.result, "1");
				}
				else
				{
					strcpy(r.result, "2");
				}
			}
			get_time(time);
			strcpy(r.result_time, time);
			fseek(fp, i * sizeof(RESERVE), SEEK_SET);
			fwrite(&r, sizeof(RESERVE), 1, fp);
			break;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Reserve.dat in result.c");
		delay(3000);
		exit(1);
	}
	if (Reserve_state == 3)	//if the reserve state is receive, user's health condition also needs update
	{
		if ((fp = fopen("database\\UserData.dat", "rb+")) == NULL)
		{
			printf("cannot open database\\UserData.dat");
			delay(3000);
			exit(1);
		}
		fseek(fp, 0, SEEK_END);
		len = ftell(fp) / sizeof(USER);
		for (i = 0; i < len; i++)
		{
			fseek(fp, i * sizeof(USER), SEEK_SET);
			fread(&u, sizeof(USER), 1, fp);
			if (strcmp(ID,u.ID) == 0)
			{
				if (Result_state == 1)
				{
					strcpy(u.condition, "1");
				}
				else
				{
					strcpy(u.condition, "3");
				}
				fseek(fp, i * sizeof(USER), SEEK_SET);
				fwrite(&u, sizeof(USER), 1, fp);
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
}