#ifndef _JUDGE_H_
#define _JUDGE_H_
#include "database.h"

int admin_judge(char* admin, char* pass);
//����Ա����Ƿ�ƥ��

int login_complete(char* u, char* p);
//�����жϵ�¼��Ϣ�Ƿ�������ȫ����ȷ

int judge_rightpassword(char* name, char* pass, int y);
//�û����������Ƿ�ƥ��

int register_complete(char* n, char* id, char* phonenumber, int Len, int state_1, int state_2, int state_3);
//�����ж�ע����Ϣ�Ƿ�������ȫ����ȷ

int judge_sameuser(char* new_user);
//�ж��˻��Ƿ��������

int checkright_ID(char* str, int x, int y, int zjlx);
//������֤λ�����ʽ

int checkright_phonenumber(char* str, int x, int y);
//����ֻ���λ�����ʽ

int judge_health(int jkzk, int jcs);
//�����뼰�г���״̬�ж�

int input_database(char* n, char* id, char* phonenumber, int health);
//���û�ע����Ϣд���ļ�

void judge(char* str, int* state, int x, int y); 
//�ж�ע���״̬

int input_uinfo(USER* us);
//��½����û���Ϣ����u

int forgetpass_complete(char* id, char* phonenumber, char* np, char* cp, int y);
//����Ƿ���Ը���������

int judge_passchange(char* id, char* phonenumber, char* pass, int x, int y, int Y);
//�ж��˻��Ƿ���ڲ�����������

int checkright_password(char* str, int x, int y);
//��������Ƿ����6λС��8λ

int checkright_confirmedpassword(char* str1, char* str2, int x, int y);
//���ȷ�������Ƿ�һ��

#endif