#ifndef _DATABASE_H_
#define _DATABASE_H_

typedef struct userinfo
{
	char name[20];	//unlimited length
	char ID[19];	//18 bit for common; unlimited for others
	char password[9];	//6-8 bit
	char phone[12];	//11 bit
	char condition[2];	//1 for health;2 for suspected;3 for defined
	char vaccine[3];	//vaccine state(1 for yes; 2 for no)
	char province0[15];	//living address-province
	char city0[20];	//living address-city
}USER;

typedef struct travelinfo
{
	char id[10];	//user's id
	char province[20];	//travel province
	char city[20];	//travel city
	char time1_1[10];	//departure time-year
	char time1_2[5];	//departure time-month
	char time1_3[5];	//departure time-date
	char time2_1[10];	//return time-year
	char time2_2[5];	//return time-month
	char time2_3[5];	//return time-date
}TRAVEL;

typedef struct areainfo
{
	char province[30];
	char city[30];
	char bentunew[5];
	char wzznew[5];
	char totalnew[5];
	char existing[5];
	char rank[2];
}AREA;

typedef struct search
{
	char provinceall[30];	//store chinese name of all province
	char provinceall1[30];	//store pinyin name of all province
}SEARCH;

typedef struct admininfo
{
	char time_rankinfo[35];	//the last time the risk info been changed
}ADMIN;

typedef struct reserveinfo
{
	char name[20];	//user's name
	char ID[19];	//user's id
	char phone[12];	//user's phone
	char hospital[3];	//reserve hospital(1 for SZY; 2 for HUST)
	char test_time1[35];	//reserve date
	char test_time2[35];	//reserve quantum
	char result_time[35];	//time for receiving result
	char result[3];	//testing result(1 for negative; 2 for positive)
	char state[3];	//reserve state(1 for reserving now; 2 for appointment been cancel; 3 for waiting for result; 4 for receive result)
}RESERVE;

typedef struct feedback
{
	char feedback[170];	//string to store the feedback
	char name[20];	//user's name
	char phone[12];	//user's phone
	int type;	//1 for jkm and xcm; 2 for record; 3 for reserve; 4 for risk rank info; 5 for personal info change
	int anonymous_state;	//1 for anonymous; 2 for not
}FEEDBACK;

#endif