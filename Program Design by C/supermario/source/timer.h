#ifndef _timer_h
#define _timer_h

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
#include"control.h"
#include"map.h"
#include"monsters.h"
#include"bonus.h"
#include"music.h"
#include"ranking.h"

/*present moving state of Mario*/
extern int state;
extern int prestate;

/*which side mario face*/
extern int flag;

/*the degree of jumping*/
extern int jumptimer;

extern int mapx, mapy;
extern int premapx[4];
extern int windowheight, windowwidth;

/*-----------function declaration-------------*/

void GlobalTimerEventProcess(int timerID);			/*the timer process for the whole program*/

void InitTimer();			/*initialize the timer process*/

void TimerIDAnalyse();			/*break up timerID for various uses*/

void ControlTimer(int counter);			/*mario's movement feedback from controling*/

void MonstersTimer(int counter);			/*the running logic of monsters*/

void MapTimer(int counter);			/*generate map*/

void StatusPrint();			/*print player's status : life  grade  distance*/

#endif