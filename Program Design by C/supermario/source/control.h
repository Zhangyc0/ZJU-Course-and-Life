#ifndef _control_h
#define _control_h

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
#include "imgui.h"
#include"timer.h"
#include"map.h"
#include"bonus.h"
#include"music.h"
#include"ranking.h"

/*transform coordinate information from or to pixel*/
#define TOPIXEL(x) (int)((x) * 25)
#define FROMPIXEL(x) (double)((x) * 1.0 / 25)

/*timer type*/
#define MARIO_STAND 0
#define MARIO_RUN_FORWARD 1
#define MARIO_RUN_BACK 2
#define MARIO_JUMP 3
#define MARIO_JUMP_END 4

/*coordination of player*/
extern int px, py;
extern int prex, prey;
extern int mapx, mapy;
extern int windowheight, windowwidth;

extern int timerIDbackup;

/*event feedback*/
void KeyboardEventProcess(int key, int event);
void CharEventProcess(char c);
void TimerEventProcessMario(int timerID);

/*-----------function declaration-------------*/

void InitControler();			/*initialize the control module*/

int GroundCheck(int x, int y);			/*return the nearest stage ground*/

int TopCheck(int x, int y);			/*return the nearest stage top*/

int SideCheck(int x, int y, int shiftx);			/*return the nearest stage side*/

#endif