#ifndef _visualization_h
#define _visualization_h

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
#include<string.h>

/*transform coordinate information from or to pixel*/
#define TOPIXEL(x) (int)((x) * 25)
#define FROMPIXEL(x) (double)((x) * 1.0 / 25)

/*draw cell type*/
#define MARIO 0
#define BLOCK 1

/*coordination of player*/
extern int px, py;

/*models file*/
static FILE *models;
/*
 * the file "models.mds" includes the following models:
 * ----------------------------------------------------
 *  index	name				model type
 *  1		mario_run_frame1	MARIO
 *	2		mario_run_frame2	MARIO
 *  3		mario_run_frame3	MARIO
 *	4		mario_stand			MARIO
 *	5		mario_jump			MARIO
 *  6		ground_block		MARIO
 *	7		goombas				BLOCK
 *	8		goombas_dead		BLOCK
 *	9		bonusbox			BLOCK
 *	10		bonusbox_broken		BLOCK
 *	11		bonus_mushroom		BLOCK
 *	12		tinymario_r_f1		BLOCK
 *	13		tinymario_r_f2		BLOCK
 *	14		tinymario_r_f3		BLOCK
 *	15		tinymario_s			BLOCK
 *	16		tinymario_j			BLOCK
 *	17		tinymario_dead		BLOCK
 *	18		bonus_star			BLOCK
 *	19		chemney_head		BLOCK
 *	20		chemney_body		BLOCK
 *	21		pirhana_f1			BLOCK
 *	22		pirhana_f2			BLOCK
 *	23		coin_f1				BLOCK
 *	24		coin_f2				BLOCK
 *	25		coin_f3				BLOCK
 *	26		coin_f4				BLOCK
 *	27		bird_f1				BLOCK
 *	28		bird_f2				BLOCK
 *	29		launcher_head		BLOCK
 *	30		launcher_foot		BLOCK
 *	31		bullet_bill			BLOCK
 *	32		lakitu_f1			BLOCK
 *	33		lakitu_f2			BLOCK
 *	34		spiny_ball_f1		BLOCK
 *	35		spiny_ball_f2		BLOCK
 *	36		spiny_f1			BLOCK
 *	37		spiny_f2			BLOCK
 *	38		koopas_f1			BLOCK
 *	39		koopas_f2			BLOCK
 *	40		koopas_ball			BLOCK
 *	41		firewall			BLOCK
 *	42		logo				BLOCK
 */

 /*-----------function declaration-------------*/

int TransData(char temp);		/*transform data into correct info*/

void DrawCell(int y, int x, int shiftx, int shifty, int flag, int upsidedown);		/*print a basic part of a pixel painting*/

void OpenModelFile();		/*open the model file*/

void FindModel(int index);		/*find the location of the needed data through its index*/

void DrawModel(int x, int y, int index, int flag, int type, int upsidedown);		/*draw the whole pixel painting*/

void ErasePicture(int x, int y, int width, int height);		/*erase the previous picture*/

#endif