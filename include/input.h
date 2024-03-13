#ifndef _INPUT_H_
#define _INPUT_H_
#include "database.h"

void inputadmin(char* id, int x1, int y1, int charnum, int color, int size);
//x1,y1分别是账号，验证码等输入信息的左端点和上端点

void inputpassword(char* id, int x1, int y1, int charnum, int color);
//x1,y1分别是密码等隐藏信息输入的左端点和上端点

int hz_input(int x1,int y1,int x2,int y2,char *s,int len,int color,int color2, int size);
//汉字输入法

int input_method(int x,int y,char *str,int value,char *py) ;
//汉字输入法调入

char *itostr(int a,char *s);
//数字标号

void pyFrm(int x1,int y1,int x2,int y2);
//输入法小框

int xouttextxy(int x,int y,char *s,int color);
//字符输入法

#endif
