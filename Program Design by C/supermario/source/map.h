
//the width of the screen is 375
//the width of a block is 16
//the height of mario is 32

#ifndef _map_h
#define _map_h

/*basic resources*/
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include<time.h>
#include"visualization.h"
#include"bonus.h"
#include"monsters.h"

/*transform coordinate information from or to pixel*/
#define TOPIXEL(x) (int)((x) * 25)
#define FROMPIXEL(x) (double)((x) * 1.0 / 25)

#define MAP_ROLLING 0			/*abolished*/

/*operation of MakeGround*/
#define OP_READ 0
#define OP_MAKE 1

extern int windowwidth, windowheight;
extern time_t nowtime;

extern int timerIDbackup;

/*-----------function declaration-------------*/

void InitMap();			/*initialize the map generating module*/

void DrawGround(int n);			/*generate a series of random number through mapx and starttime*/

int* MakeGround(int x, int operation);			/*make ground or read ground info through mapx by randomized number*/

int* GenerateRand(int x);			/*draw the ground maked by MakeGround function*/

#endif