#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include "hz.h"
#include "mouse.h"
#include "main.h"
#include "database.h"

#define NUM0 0x5230
#define NUM1 0x4f31
#define NUM2 0x5032
#define NUM3 0x5133
#define NUM4 0x4134
#define NUM5 0x4c35
#define NUM6 0x4d36
#define NUM7 0x4737
#define NUM8 0x4838
#define NUM9 0x4939

#define ENTER 0x1c0d
#define BACK 0x0e08
#define ESC 0x011b
#define UP 0x4800
#define DOWN 0x5000
#define RIGHT 0x4d00
#define LEFT 0x4b00
#define ONE 0x0231
#define TWO 0x0332
#define THREE 0x0433
#define FOUR 0x0534
#define FIVE 0x0635
#define SIX 0x0736
#define SEVEN 0x0837
#define EIGHT 0x0938
#define NINE 0x0a39
#define ZERO 0x0b30
#define DELETE 0x5300
#define SPACE 0x3920

#define LASTLINE 0x1a5b
#define NEXTLINE 0x1b5d

#define FIRST 0x0231
#define SECOND 0x0332
#define THIRD 0x0433
#define FOURTH 0x0534

#define MAXPY 12      //最大拼音（西文）数量

#define FAIL 0
#define SUCCESS 1

#endif