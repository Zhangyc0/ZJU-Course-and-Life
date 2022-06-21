#ifndef _monsters_h
#define _monsters_h

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
#include"visualization.h"
#include"bonus.h"

/*monsters*/
#define GOOMBAS				7
#define PIRHANA				21
#define COIN				23
#define CCHEEP				27
#define BULLET_BILL			31
#define LAUNCHER			29
#define LAKITU				32
#define SPINY				34
#define KOOPAS				38
#define FIREWALL			41
#define BONUS_MUSHROOM		11
#define BONUS_STAR			18
#define BONUS_COIN			COIN

/*status of monsters*/
#define ALIVE 1
#define DEAD 0
#define ALREADYDEAD 2

/*the state of monsters*/
typedef struct Monsters
{
	int type;
	int x;
	int y;
	int prex;
	int premapx;
	int prey;
	int height;
	int width;
	int condition;
	int mflag;
	struct Monsters *next;
}monsters;

extern int px, py;
extern int prex, prey;
extern int mapx, mapy;
extern int windowheight, windowwidth;
extern int state;

/*-----------function declaration-------------*/

void AddMonster(int mtype, int mx, int my, int mheight, int mwidth, int flag);			/*create the head node of monsters link*/

void CreateMonstersLink();			/*add a node into monsters link*/

int CheckMonsters();			/*check if the monsters are interacted : hit or hitted*/

#endif