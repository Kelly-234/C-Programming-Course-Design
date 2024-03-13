#ifndef _RECORD_H_
#define _RECORD_H_
#include "database.h"
#include "choose.h"

int p12_record(USER* u, int* Flag);
void record_screen(char* n, int Flag);
int gettravelinfo(int I, int P, int Flag);
int inputtravelinfo(int I, char* Province, char* City, char* Time1_1, char* Time1_2, char* Time1_3, char* Time2_1, char* Time2_2, char* Time2_3);

#endif