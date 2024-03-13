#ifndef _JUDGE_H_
#define _JUDGE_H_
#include "database.h"

int admin_judge(char* admin, char* pass);
//管理员身份是否匹配

int login_complete(char* u, char* p);
//用来判断登录信息是否输入完全和正确

int judge_rightpassword(char* name, char* pass, int y);
//用户名和密码是否匹配

int register_complete(char* n, char* id, char* phonenumber, int Len, int state_1, int state_2, int state_3);
//用来判断注册信息是否输入完全和正确

int judge_sameuser(char* new_user);
//判断账户是否出现重名

int checkright_ID(char* str, int x, int y, int zjlx);
//检查身份证位数与格式

int checkright_phonenumber(char* str, int x, int y);
//检查手机号位数与格式

int judge_health(int jkzk, int jcs);
//健康码及行程码状态判定

int input_database(char* n, char* id, char* phonenumber, int health);
//把用户注册信息写入文件

void judge(char* str, int* state, int x, int y); 
//判断注册的状态

int input_uinfo(USER* us);
//登陆后把用户信息读入u

int forgetpass_complete(char* id, char* phonenumber, char* np, char* cp, int y);
//检查是否可以更改新密码

int judge_passchange(char* id, char* phonenumber, char* pass, int x, int y, int Y);
//判断账户是否存在并更改新密码

int checkright_password(char* str, int x, int y);
//检查密码是否大于6位小于8位

int checkright_confirmedpassword(char* str1, char* str2, int x, int y);
//检查确认密码是否一致

#endif