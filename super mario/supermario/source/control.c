/**
 * \brief		control module
 * \author		PrinzyW(Wang You)
 * \file		control.c
 */
/*********************************************************************************/

#include"control.h"

extern condition mario;

/*present moving state of Mario*/
int state = 0;
int prestate = 0;

/*which side mario face*/
int flag = 1;

/*the degree of jumping*/
int jumptimer = -1;

/*
* usage: initialize the control module
* note: none
*/
void InitControler()
{
	InitGraphics();
	OpenModelFile();
	registerMouseEvent(MouseEventProcess);
	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	prex = px;		/*initialize prex, prey*/
	prey = py;
}

/*
* usage: control through keyboard
* note: mainly works when a key is up
*/
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI»ñÈ¡¼üÅÌ
	if ((prestate == MARIO_RUN_FORWARD || state == MARIO_RUN_FORWARD) && event == KEY_UP && (key == 'd' || key == 'D'))
		prestate = -2;
	if ((prestate == MARIO_RUN_BACK || state == MARIO_RUN_BACK) && event == KEY_UP && (key == 'a' || key == 'A'))
		prestate = -2;
	switch (event)
	{
	case KEY_UP:
	{
		if (key == ' ' && py > GroundCheck(px, py) && state != MARIO_JUMP_END)
		{
			jumptimer = 0;
			cancelTimer(state);
			state = MARIO_JUMP_END;
			startTimer(MARIO_JUMP_END, 25);
			timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_JUMP_END & 0x3f);
			ErasePicture(prex, prey, 16, 32);
			DrawModel(px, py, 5 + 11 * mario.condition, flag, mario.condition, 1);
			prex = px;
			prey = py;
			break;
		}
		if ((state != MARIO_RUN_FORWARD && state != MARIO_RUN_BACK) || key == ' ')
			break;
		cancelTimer(state);
		startTimer(-1, 25);
		timerIDbackup = (timerIDbackup & 0xffffffc0);
		prestate = -1;
		state = MARIO_STAND;
		ErasePicture(prex, prey + 1, 16, 32);
		DrawModel(px, py, 4 + 11 * mario.condition, flag, mario.condition, 1);
		prex = px;
		prey = py;
	}
	}
}

/*
* usage: control through char input
* note: define the moving when you input a specific char
*/
void CharEventProcess(char c)
{
	uiGetChar(c); // GUI×Ö·ûÊäÈë
	switch (c)
	{
		case ' ':
		{
			if (state == MARIO_JUMP_END)
				break;
			if (state != MARIO_JUMP)
			{
				Stop_Music("jump.mp3");
				Play_Music("jump.mp3", 0);
				jumptimer = 0;
				if (state != MARIO_STAND)
					cancelTimer(state);
				startTimer(MARIO_JUMP, 25);
				timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_JUMP & 0x3f);
				prestate = state;
				state = MARIO_JUMP;
			}
			break;
		}
		case 'd':
		case 'D':
		{
			if (state == MARIO_JUMP || state == MARIO_JUMP_END)
				break;
			if (state != MARIO_RUN_FORWARD)
			{
				if (state != MARIO_STAND)
					cancelTimer(state);
				startTimer(MARIO_RUN_FORWARD, 25);
				timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_RUN_FORWARD & 0x3f);
				prestate = state;
				state = MARIO_RUN_FORWARD;
			}
			break;
		}
		case 'a':
		case 'A':
		{
			if (state == MARIO_JUMP || state == MARIO_JUMP_END)
				break;
			if (state != MARIO_RUN_BACK)
			{
				if (state != MARIO_STAND)
					cancelTimer(state);
				startTimer(MARIO_RUN_BACK, 25);
				timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_RUN_BACK & 0x3f);
				prestate = state;
				state = MARIO_RUN_BACK;
			}
			break;
		}
	}
}

/*
 * usage: return the nearest stage ground
 * note: need to be used with map info together
 */
int GroundCheck(int x, int y)
{
	int i, currentx = mapx - mapx % (16 * 4);
	for (; !(x >= currentx - mapx - 8 && x <= currentx - mapx + 16 * 4 - 8); currentx += 16 * 4);
	int groundheight = -100;
	int ground[12][3] = { 0 };
	memcpy(ground, MakeGround(currentx, OP_READ), sizeof(int) * 36);
	for (i = 0; i < 12; i++)
	{
		if ((ground[i][0] == 1 || ground[i][0] == 2) && ground[i][1] + 16 <= y && ground[i][1] + 16 > groundheight)
			groundheight = max(groundheight, ground[i][1] + 16);
		if (ground[i][0] == 3 && ground[i][1] + 16 <= y && ground[i][1] + 16 > groundheight)
			if (x + 10 > currentx - mapx + 18 && x - 16 < currentx + 16 * 4 - mapx - 29)
				groundheight = max(groundheight, ground[i][1] + 16);
		if (ground[i][0] == 5 && ground[i][1] + 16 <= y && ground[i][1] + 16 > groundheight)
			if (x > currentx - mapx + 19 && x < currentx - mapx + 24 + 27)
				groundheight = max(groundheight, ground[i][1] + 16);

	}
	return groundheight;
}

/*
 * usage: return the nearest stage top
 * note: need to be used with map info together
 */
int TopCheck(int x, int y)
{
	int i, currentx = mapx - mapx % (16 * 4);
	for (; !(x >= currentx - mapx - 8 && x <= currentx - mapx + 16 * 4 - 8); currentx += 16 * 4);
	int topheight = windowheight + 64;
	int ground[12][3] = { 0 };
	memcpy(ground, MakeGround(currentx, OP_READ), sizeof(int) * 36);
	for (i = 11; i >= 0; i--)
		if ((ground[i][0] == 1 || ground[i][0] == 2) && ground[i][1] >= y && ground[i][1] < topheight)
			topheight = ground[i][1];
	return topheight;
}

/*
 * usage: return the nearest stage side
 * note: need to be used with map info together
 */
int SideCheck(int x, int y, int shiftx)
{
	int i, currentx = mapx - mapx % (16 * 4), flag = 1;
	int newshiftx = shiftx;
	if (shiftx < 0)
		flag = -1;
	
	for (; !(x >= currentx - mapx - 8 && x <= currentx - mapx + 16 * 4 - 8); currentx += 16 * 4);
	currentx += 16 * 4 * flag;
	
	int ground[12][3] = { 0 };
	memcpy(ground, MakeGround(currentx, OP_READ), sizeof(int) * 36);
	for (i = 11; y < windowheight - (11 - i) * 16; i--)
		if (y + 32 - 16 * mario.condition > windowheight - (12 - i) * 16)
		{
			if (ground[i][0] == 1 || ground[i][0] == 2)
			{
				if (flag >= 0)
					newshiftx = min(newshiftx, currentx - x - mapx - 16);
				else
					newshiftx = -1 * min(abs(newshiftx), abs(x + mapx - currentx - 16 * 4));
			}
		}

	currentx -= 16 * 4 * flag;
	memcpy(ground, MakeGround(currentx, OP_READ), sizeof(int) * 36);
	for (i = 11; y < windowheight - (11 - i) * 16; i--)
		if (y + 32 - 16 * mario.condition > windowheight - (12 - i) * 16)
		{
			if ((ground[i][0] == 3 || ground[i][0] == 4) && flag >= 0 && x <= currentx - mapx + 32 - 24 && x + shiftx >= currentx - mapx + 32 - 24)
				newshiftx = min(newshiftx, currentx - mapx + 32 - 24 - (x));

			if ((ground[i][0] == 3 || ground[i][0] == 4) && flag < 0 && x >= currentx - mapx + 32 + 16 + 3 && x + shiftx <= currentx - mapx + 32 + 16 + 3)
				newshiftx = -1 * min(abs(newshiftx), abs(x - (currentx - mapx + 32 + 16 + 3)));

			if ((ground[i][0] == 5 || ground[i][0] == 6) && flag >= 0 && x <= currentx - mapx + 32 - 13 && x + shiftx >= currentx - mapx + 32 - 13)
				newshiftx = min(newshiftx, currentx - mapx + 32 - 13 - (x));

			if ((ground[i][0] == 5 || ground[i][0] == 6) && flag < 0 && x >= currentx - mapx + 32 + 3 && x + shiftx <= currentx - mapx + 32 + 16 + 3)
				newshiftx = -1 * min(abs(newshiftx), abs(x - (currentx - mapx + 32 + 16 + 3)));
		}
	return newshiftx;
}
