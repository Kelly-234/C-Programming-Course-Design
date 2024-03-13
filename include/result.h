#ifndef _RESULT_H_
#define _RESULT_H_
#include "database.h"
#include "gettime.h"

int p15_result(void);
int Getreserveinfo(int P);
void result_screen(void);
void draw_statechange(void);
void draw_result(void);
void Inputreserveinfo(int I, int P, int Reserve_state, int Result_state);

#endif