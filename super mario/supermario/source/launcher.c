/**
 * \brief		launcher of the game
 * \author		PrinzyW(Wang You)
 * \file		launcher.c
 */
/*********************************************************************************/

#include"launcher.h"

extern condition mario;

/*coordination of mario*/
int px, py;
int prex = 100, prey = 100;

int windowwidth, windowheight;
time_t nowtime;

void Main()
{
	/*set window title*/
	SetWindowTitle("Super Mario");
	
	/*get system time*/
	time(&nowtime);

	/*initialization*/
	InitControler();
	InitTimer();
	InitMap();

	/*initialize paranumber*/
	windowwidth = TOPIXEL(GetWindowWidth());
	windowheight = TOPIXEL(GetWindowHeight());
	px = TOPIXEL(GetWindowWidth() / 2);
	py = windowheight;

	/*create link*/
	CreateMonstersLink();
	CreateBonusLink();

	/*initialze mario's state*/
	mario.condition = STATE_BIG;
	mario.life = 1;
	mario.grade = 0;
	mario.invincible = 0;
	mario.strong = 0;
	mario.world = 0;
	mario.lastmapx = 0;
	return;
}
