#ifndef _ranking_h
#define _ranking_h

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
#include"bonus.h"
#include"score.h"

/*transform coordinate information from or to pixel*/
#define TOPIXEL(x) (int)((x) * 25)
#define FROMPIXEL(x) (double)((x) * 1.0 / 25)

extern int windowheight, windowwidth;

/*-----------function declaration-------------*/

void NameText(int bx, int by);			/*draw the name text box*/

void MouseEventProcess(int x, int y, int button, int event);			/*get mouse coordination for name box*/

void Ranking(int bx, int by);			/*print player's score and rankings of players*/

#endif