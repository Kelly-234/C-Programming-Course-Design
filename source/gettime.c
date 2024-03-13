/**
 * @file gettime.c
 * @author yangchunru
 * @brief time info acquisition, legality determination
 * @date 2021-05-02
 */
#include "public.h"
#include "gettime.h"

/**
 * @brief get time needed in risknew.c
 * @param t 
 */
void get_time(char* t)
{
	time_t timep;
    struct tm *p;

	time(&timep);
	timep-=4*3600;
    p = gmtime(&timep);
	sprintf(t,"%d-%d-%d %02d:%02d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min);
}

/**
 * @brief get time needed in reserve.c
 * @param t add day number
 * @param Time string for store
 * @param flag type required
 */
void Get_time(int t, char* Time, int flag)
{
	time_t timep;
    struct tm *p;
	
	time(&timep);
	timep-=(4*3600-24*3600l*t);
    p = gmtime(&timep);
	if (flag == 1)
	{
		sprintf(Time,"%d/%d",1+p->tm_mon,p->tm_mday);	//show date with only month and day
	}
	else
	{
		sprintf(Time,"%d/%d/%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday);	//show whole date
	}
}

/**
 * @brief determine whether the latest travel return time is more than 14 days ago
 * @param year newest travel time-year
 * @param month newest travel time-month
 * @param date newest travel time-date
 * @param flag 1 for compare with the date 14 days ago; 0 for compare with now 
 * @return int return 0 for yes; return 1 for no
 */
int time_compare(char* year, char* month, char* date, int flag)
{
	time_t timep;
    struct tm *p;

	time(&timep);
	timep-=(4*3600+flag*14*24*3600l);
    p = gmtime(&timep);
	if (1900+p->tm_year < atoi(year))
		return 1;
	else if ((1900+p->tm_year == atoi(year)) && (1+p->tm_mon < atoi(month)))
		return 1;
	else if ((1+p->tm_mon == atoi(month)) && (p->tm_mday < atoi(date)))
		return 1;
	else
		return 0;
}

/**
 * @brief compare departure time and return time(or last return time and current departure time) and get legality determination
 * @param Time1_1 departure time-year or last return time-year
 * @param Time1_2 departure time-month or last return time-month
 * @param Time1_3 departure time-date or last return time-date
 * @param Time2_1 return time-year or current departure time-year
 * @param Time2_2 return time-month or current departure time-month
 * @param Time2_3 return time-date or current departure time-date
 * @return int return 1 for legitimate; return 0 for illegitimate
 */
int traveltime_compare(char* Time1_1, char* Time1_2, char* Time1_3, char* Time2_1, char* Time2_2, char* Time2_3)
{
	if (atoi(Time1_1) < atoi(Time2_1))
		return 1;
	else if ((atoi(Time1_1) == atoi(Time2_1)) && (atoi(Time1_2) < atoi(Time2_2)))
		return 1;
	else if ((atoi(Time1_2) == atoi(Time2_2)) && (atoi(Time1_3) < atoi(Time2_3)))
		return 1;
	else
		return 0;
}