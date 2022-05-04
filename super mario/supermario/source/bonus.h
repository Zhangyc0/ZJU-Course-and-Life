#ifndef _bonus_h
#define _bonus_h

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

/*the status of bonus box*/
#define Unbroken 1
#define Broken 0

/*type of bonus box*/
#define BONUS_BIG 1
#define BONUS_STRONG 2

/*the status of mario*/
#define STATE_SMALL 1
#define STATE_BIG 0
#define STATE_DEAD 2

/*the state of mario*/
typedef struct Condition
{
	int life;
	int condition;
	int grade;
	int invincible;
	int strong;
	int world;
	int lastmapx;
}condition;

/*bonus link node*/
typedef struct Bonus
{
	int type;
	int x;
	int y;
	int premapx;
	int prey;
	int condition;
	struct Bouns *next;
}bonus;

extern mapx;

/*-----------function declaration-------------*/

void CreateBonusLink();			/*create the head node of bonus link*/

void AddBonus(int btype, int bx, int by);			/*add a node into the bonus link*/

#endif