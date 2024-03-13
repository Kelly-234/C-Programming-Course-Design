#ifndef _FEEDBACK_H
#define _FEEDBACK_H
#include "database.h"
#include "input.h"

int p16_feedback(USER *u, int*Flag);
void feedback_screen(char* n, char* p);
void inputfeedback(char* f, char* n, char* p, int Type, int Anonymous_state);

#endif