#ifndef _GETTIME_H_
#define _GETTIME_H_

void get_time(char* t);
void Get_time(int t, char* Time, int flag);
int time_compare(char* year, char* month, char* date, int flag);
int traveltime_compare(char* Time1_1, char* Time1_2, char* Time1_3, char* Time2_1, char* Time2_2, char* Time2_3);

#endif