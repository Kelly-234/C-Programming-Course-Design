#ifndef _CHOOSE_H_
#define _CHOOSE_H_
#include "database.h"
#include "input.h"

void showplace(char* Province, char* City, int X, int Y, int* Flag);
void showtime(char* Year, char* Month, char* Date, int X, int Y, int* Flags);
void change_riskinfo(int I, int* Flag, char* Province, int P);

#endif