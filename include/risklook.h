#ifndef _RISKLOOK_H_
#define _RISKLOOK_H_
#include "database.h"
#include "choose.h"

int p10_risklook(USER *u, int* Flag);
void risklook_screen(char* n, int flag);
void result(char* Province, char* City);

#endif