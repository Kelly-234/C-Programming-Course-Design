#ifndef _RESERVE_H_
#define _RESERVE_H_
#include "database.h"
#include "gettime.h"

int p14_reserve(USER* u, int* Flag);
void reserve_screen(char* n);
int getreserveinfo(char* ID);
void draw_reserve(int I);
void draw_SZY(void);
void draw_HUST(void);
void delete_reserveinfo(char* ID);
int inputreserveinfo(int I, int State_hospital, int State_time1, int State_time2);

#endif