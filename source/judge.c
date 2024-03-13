/**
 * @file judge.c
 * @author ancestral code
 * @brief judgment of information legitimacy, whether can log in and register
 */
#include "public.h"
#include "judge.h"

/*********************************************
FUNCTION:admin_judge
DESCRIPTION：判断管理员身份是否匹配
INPUT:admin,pass
RETURN:无
***********************************************/

int admin_judge(char* admin, char* pass)
{
	int state = 0;
	setfillstyle(SOLID_FILL, LIGHTGREEN);
	bar(320-3.5*26, 240-17-34-34-24, 320+3.5*26, 240-17-34-34+2);
	if (strlen(admin) == 0)
	{
		puthz(320+10, 240-34-17+5, "未输入", 24, 26, RED);
		state = 1;
	}
	if (strlen(pass) == 0)
	{
		puthz(320+10,240+17+5, "未输入", 24, 26, RED);
		state = 1;
	}
	if (state == 0)
	{
		if (strcmp(admin, "yangchunru") == 0
		 || strcmp(admin, "zhushumin") == 0
		 || strcmp(admin, "zhoulaoshi") == 0
		 || strcmp(admin, "helaoshi") == 0
	   	 || strcmp(admin, "penglaoshi") == 0
		 || strcmp(admin, "sanglaoshi") == 0
	  	 || strcmp(admin, "zuolaoshi") == 0
		 || strcmp(admin, "gaolaoshi") == 0
		 || strcmp(admin, "wanglaoshi") == 0
		 || strcmp(admin, "chenlaoshi") == 0)
		{
			if (strcmp(pass, "12345678") == 0)
	        {
				state = 2;
				puthz(320-52, 240-17-34-34-24, "登录成功", 24, 26, RED);
		        delay(1000);
	        	return 1;
	        }
	    }
	}
	if (state == 0)
	{
		puthz(320-3.5*26, 240-17-34-34-24, "管理员信息有误", 24, 26, RED);
	    return 0;
	}
	else 
	{
		return 0;
	}
}

/*********************************************
FUNCTION:login_complete
DESCRIPTION：用来判断登录信息是否输入完全和正确
INPUT:u,p
RETURN:1/0
***********************************************/

int login_complete(char* u, char* p)
{
	int state = 0;//是否输入的变量
	while (1)
	{
		judge(u, &state, 277,240-34-17);
		judge(p, &state, 277,240+17);
		if (state != 0)
		{
			return 0;
		}
		else if (state == 0)
		{
			if (judge_rightpassword(u, p, 240-17-34-34-24))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}

/*********************************************
FUNCTION:judge_rightpassword
DESCRIPTION：判断手机号和密码是否匹配，匹配则登录
INPUT:phone,pass
RETURN:1/0
***********************************************/

int judge_rightpassword(char* phone, char* pass, int y)	
{
	int len;
	int i;
	FILE* fp;
	USER u;
	if ((fp = fopen("database\\UserData.dat", "rb")) == NULL)
	{
		printf("cannot open file UserData.dat in lgfunc.c");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(USER);
	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(USER), SEEK_SET);
		fread(&u, sizeof(USER), 1, fp);
		if (strcmp(phone, u.phone) == 0)//手机号匹配
		{
			if (strcmp(pass, u.password) != 0)	//密码不配
			{
				puthz(320-52, y, "密码错误", 24, 26, RED);
			}
			else 								//密码匹配
			{
				puthz(320-52, y, "登录成功", 24, 26, RED);
				delay(2000);
				if (fclose(fp) != 0)
				{
					printf("\n cannot close Database");
					delay(3000);
					exit(1);
				}
				return 1;
				//切换界面
			}
			break;
		}
	}	
	if (fclose(fp) != 0)
	{
		printf("cannot close Database in lgfunc.c");
		delay(3000);
		exit(1);
	}
	if (i == len)
	{
		puthz(320-26*2.5, y, "账户未注册", 24, 26, RED);//走到最后一位
		delay(1000);
	}
	return 0;
}

/*********************************************
FUNCTION:register_complete
DESCRIPTION：用来判断注册信息是否输入完全和正确
INPUT:n,id,phonenumber,state_1(身份证格式),state_2(健康状况),state_3(密接经历)
RETURN:1/0
***********************************************/

int register_complete(char* n, char* id, char* phonenumber, int Len, int state_1, int state_2, int state_3)
{
	int i;
	int state = 0;//是否输入的变量
	int state1 = 1;//身份证号输入格式是否正确的变量
	int state2 = 1;//手机号输入格式是否正确的变量
	int state3 = 0;//健康码及行程码状态判定结果
	while (1)
	{
		state = (!Len);
		judge(n, &state, 60+34*4,30+50*1);          //judge:未输入就state=1
		judge(id, &state, 60+34*4,30+50*3); 
		judge(phonenumber, &state, 60+34*4,30+50*4);
		if (state == 1)
		{
			return 0;
		}
		else if (state == 0)
		{
			if (judge_sameuser(n))//用户名没有重名
			{
				puthz(60+34*4+20+18*18,30+50*1+5, "姓名可用", 24, 25, RED);
				state1 = checkright_ID(id, 60+34*4+20+18*18+20,30+50*3, state_1);
				state2 = checkright_phonenumber(phonenumber, 60+34*4+20+18*18+20,30+50*4);
				state3 = judge_health(state_2, state_3);
				if (state1 != 0 || state2 != 0)
				{
					return 0;
				}
				else if ((state1 == 0) && (state2 == 0))
				{
					if (input_database(n, id, phonenumber, state3))//写入数据库
					{
						puthz(142,20,"注册成功",24,26,RED);
			            setcolor(RED);
			            outtextxy(142+26*4,20,"!");
			            puthz(142+26*4+18,20,"默认密码为",24,26,RED);
			            outtextxy(142+26*4+18+26*5,20,"12345678");
			            delay(3000);
		                return 1;//返回
					}
					else
					{
						printf("something wrong");
				        delay(3000);
				        exit(1);
					}
				}
			}
			else
			{
				return 0;
			}
		}
	}
}

/*********************************************
FUNCTION:judge_sameuser
DESCRIPTION：判断账户是否出现重名(根据姓名)
INPUT:new_user
RETURN:1/0
***********************************************/

int judge_sameuser(char* new_user)
{
	int len;
	int i;
	FILE* fp;
	USER u;
	if ((fp = fopen("database\\UserData.dat", "rb")) == NULL)//建立数据库
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
		fread(&u, sizeof(USER), 1, fp);
		if (strcmp(u.name, new_user) == 0)
		{
			puthz(60+34*4+20+18*18+10,30+50*1-8, "用户已", 24, 25, RED);
			puthz(60+34*4+20+18*18+10,30+50*1+34+8-24, "被注册", 24, 25, RED);
			return 0;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database in lgfunc.c");
		delay(3000);
		exit(1);
	}
	return 1;
}

/*********************************************
FUNCTION:judge_passchange
DESCRIPTION：判断账户是否存在并更改新密码
INPUT:id
RETURN:1/0
***********************************************/

int judge_passchange(char* id, char* phonenumber, char* pass, int x, int y, int Y)
{
	int len;
	int i;
	FILE* fp;
	USER u;
	while(1)
	{
	    if ((fp = fopen("database\\UserData.dat", "rb+")) == NULL)//建立数据库
	    {
	    	printf("cannot open file UserData.dat in lgfunc.c");
	    	delay(3000);
	    	exit(1);
	    }
	    fseek(fp, 0, SEEK_END);
	    len = ftell(fp) / sizeof(USER);
		for (i = 0; i < len; i++)
	    {
	    	fseek(fp, i * sizeof(USER), SEEK_SET);
	    	fread(&u, sizeof(USER), 1, fp);
	    	if (strcmp(u.ID, id) == 0)
	    	{
		    	if (strcmp(phonenumber, u.phone) != 0)
		    	{
		    		puthz(320-26*2.5, Y, "证件不匹配", 24, 26, RED);
		    		if (fclose(fp) != 0)
		            {
   		            	printf("\n cannot close Database in lgfunc.c");
		            	delay(3000);
 		            	exit(1);
    	            }
					return 0;
		    	}
		    	else if (strcmp(phonenumber, u.phone) == 0)
		    	{
			    	setcolor(BLUE);
		    		setlinestyle(SOLID_LINE, 0, 3);
		    		line(x - 2, y + 13, x + 8, y + 23);
		            line(x + 8, y + 23, x + 18, y +3);
					strcpy(u.password, pass);
		    		fseek(fp, i * sizeof(USER), SEEK_SET);
		    		if (fwrite(&u, sizeof(USER), 1, fp) == 1)//修改完后一定要记得写入数据
					{
					    puthz(320-26*3, Y, "密码修改成功", 24, 26, RED);
					    delay(2000);
					}
			    	if (fclose(fp) != 0)
		            {
   			            printf("\n cannot close Database in lgfunc.c");
			            delay(3000);
 		               	exit(1);
    	            }
					return 1;
			    }
		    }
		}
	    if (i == len)
	    {
	    	puthz(320-26*2.5, Y, "用户不存在", 24, 26, RED);
	    	if (fclose(fp) != 0)
		    {
   		    	printf("\n cannot close Database in lgfunc.c");
		    	delay(3000);
 		    	exit(1);
    	    }
			return 0;
	    }
		if (fclose(fp) != 0)
		{
   			printf("\n cannot close Database in lgfunc.c");
			delay(3000);
 			exit(1);
    	}
	}
}

/*********************************************
FUNCTION:checkright_ID
DESCRIPTION：检查身份证位数与格式
INPUT:str,x,y,zjlx(证件类型)
RETURN:1/0
***********************************************/

int checkright_ID(char* str, int x, int y, int zjlx)
{
	int i;
	int state = 1;
	if (zjlx == 1)
	{
		if (strlen(str) != 18)
	    {
	    	puthz(x-5, y-8, "证件为", 24, 25, RED);
		    setcolor(RED);
		    settextjustify(LEFT_TEXT, TOP_TEXT);
		    settextstyle(1, HORIZ_DIR, 2);
		    outtextxy(x+2, y+34+8-24, "18");
		    puthz(x-3+36, y+34+8-24, "位", 24, 25, RED);//长度不符合
		    return 1;
	    }
	    else if (strlen(str) == 18)
	    {
    		for (i = 0; i < 17; i++)
	    	{
		    	if (str[i] >= '0' && str[i] <= '9')
			    {
				    continue;
			    }
			    else
			    {
				    puthz(x, y, "格式不正确", 24, 26, RED);
				    return 1;
			    }
			
		    }
		    if (str[17] == 'X' || str[17] == 'x' || (str[17]>='0' && str[17]<='9'))
		    {
				state = 0;//判断最后一位是否为数字和X
	    	}
		    else
		    {
			    puthz(x, y, "格式不正确", 24, 26, RED);
			    return 1;
		    }
	    }
	}
	else
	{
		state = 0;
	}
	if (state == 0)
	{
		setcolor(BLUE);
		setlinestyle(SOLID_LINE, 0, 3);
		line(x + 3, y + 8, x + 13, y + 18);
		line(x + 13, y + 18, x + 23, y - 2);
	}
	return 0;
}

/*********************************************
FUNCTION:checkright_phonenumber
DESCRIPTION：检查手机号位数与格式
INPUT:str,x,y
RETURN:1/0
***********************************************/

int checkright_phonenumber(char* str, int x, int y)
{
	if (strlen(str) != 11)
    {
    	puthz(x-9, y-8, "手机号", 24, 27, RED);
	    setcolor(RED);
	    settextjustify(LEFT_TEXT, TOP_TEXT);
	    settextstyle(1, HORIZ_DIR, 2);
		puthz(x-12, y+34+8-24, "为", 24, 25, RED);
	    outtextxy(x+15, y+34+8-24, "11");
	    puthz(x+11+36, y+34+8-24, "位", 24, 25, RED);//长度不符合
	    return 1;
    }
    else 
	{
		setcolor(BLUE);
		setlinestyle(SOLID_LINE, 0, 3);
		line(x + 3, y + 8, x + 13, y + 18);
		line(x + 13, y + 18, x + 23, y - 2);
		return 0;
	}
}

/*********************************************
FUNCTION:judge_health
DESCRIPTION：健康码及行程码状态判定
INPUT:jkzk,jcs
RETURN:1/2/3
***********************************************/

int judge_health(int jkzk, int jcs)
{
	if (jkzk == 1 && jcs == 2)
	{
		return 1;//显示绿码
	}
	else if (jkzk == 3)
	{
		return 3;//显示红码
	}
	else
	{
		return 2;//显示黄码
	}
}

/*********************************************
FUNCTION:input_database
DESCRIPTION：把用户注册或者开户信息写入文件
INPUT:user,id,pass,phonenumber,health
RETURN:1/0
***********************************************/

int input_database(char* n, char* id, char* phonenumber, int health)
{
	FILE* fp;
	USER u;
	if ((fp = fopen("database\\UserData.dat", "rb+" )) == NULL)//建立数据库
	{
		printf("cannot open file UserData.dat in lgfunc.c");
		delay(3000);
		exit(1);
	}
	memset(&u,'\0',sizeof(USER));
	strcpy(u.name, n);
	strcpy(u.ID, id);
	strcpy(u.phone, phonenumber);
	strcpy(u.password, "12345678");
	if (health == 1)
	{
		strcpy(u.condition, "1");
	}
	else if (health == 2)
	{
		strcpy(u.condition, "2");
	}
	else
	{
		strcpy(u.condition, "3");
	}
	fseek(fp, 0, SEEK_END);//跳转至文件末尾
	fwrite(&u, sizeof(USER), 1, fp);//把用户信息写入文件 余额默认为0
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database in lgfunc.c");
		delay(3000);
		exit(1);
	}
	return 1;
}

/*********************************************
FUNCTION:checkright_password
DESCRIPTION：检查密码是否为6-8位
INPUT:str,x,y
RETURN:1/0
***********************************************/

int checkright_password(char* str, int x, int y)
{
	if (strlen(str) < 6 || strlen(str) > 8)//小于6位或大于8位
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(320-80,240+17,640-320+80+20+34*3+30,240+17+34);
		puthz(320-70,245+17, "密码应为", 24, 25, RED);
		setcolor(RED);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(1, HORIZ_DIR, 2);
		outtextxy(320-70+100+2,245+17, "6-8");
		puthz(320-70+100+18*3+4,245+17, "位", 24, 25, RED);
		return 1;
	}
	else if (strlen(str) >= 6 && strlen(str) <= 8)
	{
		setcolor(BLUE);
		setlinestyle(SOLID_LINE, 0, 3);
		line(x -2, y + 13, x + 8, y + 23);
		line(x + 8, y + 23, x + 18, y +3);
		return 0;
	}
	return 1;
}

/*********************************************
FUNCTION:checkright_confirmedpassword
DESCRIPTION：检查确认密码是否一致
INPUT:str1,str2,x,y
RETURN:1/0
***********************************************/

int checkright_confirmedpassword(char* str1, char* str2, int x, int y)
{
	if (strcmp(str1, str2) != 0)
	{
		puthz(246,245+68+17, "两次不一致", 24, 26, RED);
		return 1;
	}
	else if (strcmp(str1, str2) == 0)
	{
		setcolor(BLUE);
		setlinestyle(SOLID_LINE, 0, 3);
		line(x -2, y + 13, x + 8, y + 23);
		line(x + 8, y + 23, x + 18, y +3);
		return 0;
	}
	return 1;
}

/*********************************************
FUNCTION:forgetpass_complete
DESCRIPTION：检查是否可以更改新密码
INPUT:u,id,np,cp
RETURN:1/0
***********************************************/

int forgetpass_complete(char* id, char* phonenumber, char* np, char* cp, int y)
{
	int state = 0;//是否输入的变量
	int state1 = 1;//密码输入格式是否正确的变量
	int state2 = 1;//确认密码是否一致的变量
	int state3 = 0;//手机号输入格式是否正确的变量
	while (1)
	{
		judge(id, &state, 236,240-34-17-68); //判断是否输入,未输入会=1
		judge(phonenumber, &state, 236,240-34-17);
		judge(np, &state, 236,240+17);
		judge(cp, &state, 236,240+68+17);
		if (state != 0)
		{
			return 0;
		}
		else if (state == 0)
		{
			state1 = checkright_password(np, 600,240+17);
			state1 = checkright_password(cp, 600,240+17+34+34);
			state2 = checkright_confirmedpassword(np, cp, 600,240+17+34+34);
			if (strlen(phonenumber) != 11)
			{
				setfillstyle(SOLID_FILL, WHITE);
	        	bar(236,240-34-17,580,240-17);
	        	puthz(246,245-34-17,"手机号应为",24,26,RED);
				setcolor(RED);
	           	settextjustify(LEFT_TEXT, TOP_TEXT);
	           	settextstyle(1, HORIZ_DIR, 2);
	           	outtextxy(246+26*5+2,245-34-17, "11");
				puthz(246+26*5+36+4,245-34-17,"位",24,26,RED);
				state3 = 1;
			}
			if (state1 != 0 || state2 != 0 || state3 != 0)
			{
				return 0;
			}	
			else
			{
				if (judge_passchange(id, phonenumber, np, 600, 240-17-34, y))//写入数据库
				{
					return 1;//返回登录界面
				}
				else
				{
				    return 0;
				}
			}
		}
	}
}

/*********************************************
FUNCTION:judge
DESCRIPTION：判断注册的状态
INPUT:str,p,x,y
RETURN:无
***********************************************/

void judge(char* str, int* p, int x, int y)
{
	if (strlen(str) == 0)
	{
		*p = 1;
		puthz(x+10, y+5, "未输入", 24, 26, RED);
	}
}

/*********************************************
FUNCTION:input_uinfo
DESCRIPTION：输入用户信息
INPUT:us
RETURN:无
***********************************************/

int input_uinfo(USER* us)
{
	int i;
	int len;
	FILE* fp;
	USER u;
	if ((fp = fopen("database\\UserData.dat", "rb" )) == NULL)
	{
		printf("cannot open file UserData.dat in lgfunc.c");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);//文件指针定位到最后一位
	len = ftell(fp) / sizeof(USER);//计算用户个数
	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(USER), SEEK_SET);//每次往后移一个用户
		fread(&u, sizeof(USER), 1, fp);		  //将信息读入u
		if (strcmp(us->phone, u.phone) == 0)
		{
			memset(us,'\0',sizeof(USER));              //先重置
			strcpy(us->name,u.name); 
			strcpy(us->ID,u.ID); 
			strcpy(us->phone,u.phone);
			strcpy(us->condition,u.condition);
			if (fclose(fp) != 0)
			{
				printf("\n cannot close Database in lgfunc.c");
				exit(1);
			}
			return 1;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database in lgfunc.c");
		exit(1);
	}
	return 0;
}