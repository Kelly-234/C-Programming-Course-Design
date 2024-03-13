#ifndef _XXCHANGE_H_
#define _XXCHANGE_H_
#include "database.h"
#include "choose.h"

int p11_xxchange(USER* u, int* Flag);
void getinfo(USER *us, int* State_vaccine, int* State_address);
void xxchange_screen(void);
void input_vaccine(USER *us, int Vaccine);
void input_home(USER* us, char* p, char* c);

#endif