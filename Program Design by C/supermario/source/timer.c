/**
 * \brief		global timer module
 * \author		PrinzyW(Wang You)
 * \file		timer.c
 */
/*********************************************************************************/

#include"timer.h"

extern monsters *head;
extern monsters *tail;

extern bonus *bhead;
extern bonus *btail;

extern condition mario;

int timerIDbackup = 0;
int timerIDs[5];
static int killcoinx = 0, killcoiny = 0;

/*
 * usage: initialize the timer process
 * note: none
 */
void InitTimer()
{
	registerTimerEvent(GlobalTimerEventProcess);
}

/*
 * usage: return the corrected shift X of mario or monsters to avoid runnig out of map or into blocks
 * note: used with SideCheck in control module
 */
void ShiftX(int shiftx, int flag)
{
	shiftx = SideCheck(px, py, shiftx);
	if (px + shiftx > windowwidth * 3 / 5 && flag > 0)
	{
		if(mario.world == 1)
			mapx = (mapx + shiftx) % 0x7ffffff8;
		else
			px = px + shiftx;
	}
	else if (px + shiftx < 10 && flag < 0);
	else
		px = px + shiftx;
}

/*
 * usage: break up timerID for various uses
 * note: abolished function
 */
void TimerIDAnalyse()
{
	timerIDs[0] = timerIDbackup & 0x3f;
	timerIDs[1] = ((timerIDbackup & 0xfc0) >> 6) & 0x3f;
	timerIDs[2] = ((timerIDbackup & 0x3f000) >> 12) & 0x3f;
	timerIDs[3] = ((timerIDbackup & 0xfc0000) >> 18) & 0x3f;
	timerIDs[4] = ((timerIDbackup & 0x3f000000) >> 24) & 0x3f;
}

/*
 * usage: the timer process for the whole program
 * note: none
 */
void GlobalTimerEventProcess(int timerID)
{
	static int counter = 1;
	counter = (counter + 1) % 24;
	
	TimerIDAnalyse();

	/*draw name box*/
	if (mario.world == 0)
	{
		ErasePicture(8, 130, 120, 28);
		NameText(8, 134);
	}

	/*print the status information*/
	if (mario.world == 1 && (counter == 0 || counter == 12))
		StatusPrint();

	/*check if start the game*/
	if (mario.world == 0 && py < 0)
	{
		Play_BGM_Repeat("background.mp3");
		ErasePicture(windowwidth / 2, 0, windowwidth, windowheight);
		mario.condition = STATE_BIG;
		mario.life = 0;
		mario.grade = 0;
		mario.invincible = 0;
		mario.strong = 0;
		mario.world = 1;
		px = windowwidth / 2;
		py = windowheight + 32;
		/*get system time*/
		time(&nowtime);
		return;
	}

	/*check if dead*/
	/*already dead*/
	if (py < 16 && mario.world == 1 && mario.condition != STATE_DEAD)
	{
		py += 128;
		ErasePicture(prex, prey + 1, 16, 31 - mario.condition * 16);
		mario.condition = STATE_DEAD;
		Stop_Music("background.mp3");
		Stop_Music("invincible.mp3");
		Play_Music("die.mp3", 0);
	}
	/*realy dead*/
	if (mario.world == 1 && py <= 0)
	{
		ErasePicture(windowwidth / 2, 0, windowwidth, windowheight);
		mario.condition = STATE_BIG;
		mario.life = 1;
		mario.grade = 0;
		mario.invincible = 0;
		mario.strong = 0;
		mario.world = 0;
		px = windowwidth / 2;
		py = windowheight + 32;
		prex = 0;
		prey = windowheight;
		if(mapx > mario.lastmapx)
			mario.lastmapx = mapx;
		mapx = 0;
		CreateMonstersLink();
		CreateBonusLink();
		return;
	}

	/*grade check*/
	static int pregrade = 0;
	if (mario.grade - pregrade >= 1000)
	{
		pregrade = mario.grade;
		mario.life++;
	}

	/*timer for map*/
	MapTimer(counter);

	/*timer for monsters*/
	MonstersTimer(counter);

	/*timer for control*/
	if ((counter + 1) % 2 == 0)
		ControlTimer(counter);
}

/*
 * usage: print player's status : life  grade  distance
 * note: none
 */
void StatusPrint()
{

	char strlife[20], strgrade[20], strdistance[20];
	sprintf(strlife, "LIFE  %d", mario.life);
	sprintf(strgrade, "GRADE  %d", mario.grade);
	sprintf(strdistance, "DISTANCE  %d", mapx);
	ErasePicture(windowwidth - 16, 0, 32, 32);
	SetPenColor("Red");
	MovePen(FROMPIXEL(windowwidth - 36), FROMPIXEL(20));
	DrawTextString(strlife);
	MovePen(FROMPIXEL(windowwidth - 36), FROMPIXEL(12));
	DrawTextString(strgrade);
	MovePen(FROMPIXEL(windowwidth - 36), FROMPIXEL(4));
	DrawTextString(strdistance);
}

/*
 * usage: generate map
 * note: generate different stages for different counter ( in different frames )
 */
void MapTimer(int counter)
{
	if ((counter + 1) % 2 != 0 && (counter + 1) % 3 == 0)
	{
		monsters *temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
			/*how does a pirhana work*/
			if (temp->type == PIRHANA)
			{
				if (temp->y == temp->prey)
					temp->condition = -1;
				if (temp->y <= temp->prey - 48)
					temp->condition = 1;
				temp->y += temp->condition * 3;
				/*draw the pirhana*/
				ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 23);
				DrawModel(temp->x - mapx, temp->y, PIRHANA + temp->mflag, 1, BLOCK, 1);
				temp->mflag = (temp->mflag + 1) % 2;
				temp->prex = temp->x;
				temp->premapx = mapx;
			}
		}
	}
	/*basic floor*/
	if ((counter + 1) % 2 != 0 && counter % 6 == 0)
	{
		DrawGround(0);
		premapx[0] = mapx;
	}
	/*upper floor*/
	if ((counter + 1) % 2 != 0 && (counter + 1) % 3 == 0)
	{
		DrawGround(1);
		premapx[1] = mapx;
		DrawGround(2);
		premapx[2] = mapx;
		DrawGround(3);
		premapx[3] = mapx;
		/*about the bonus box*/
		bonus *btemp = bhead;
		bonus *bttemp = bhead;
		while (btemp->next != NULL && btemp != NULL)
		{
			btemp = btemp->next;
			/*delete the unneeded link node*/
			if (btemp->x - mapx < 0)
			{
				if (btail == btemp)
					btail = bttemp;
				bttemp->next = btemp->next;
				btemp = bttemp;
				free(bttemp->next);
				continue;
			}
			/*check if interacted*/
			if (btemp->y == btemp->prey && (state == MARIO_JUMP || state == MARIO_JUMP_END) && py + 32 - 16 * mario.condition >= btemp->y - 8 && py + 16 - 16 * mario.condition <= btemp->y + 8 && px >= btemp->x - mapx - 8 && px <= btemp->x - mapx + 8)
			{
				if (btemp->condition)
				{
					if (btemp->type == BONUS_BIG)
						AddMonster(BONUS_MUSHROOM, btemp->x, btemp->y + 16, 16, 16, 1);
					else if (btemp->type == BONUS_STRONG)
						AddMonster(BONUS_STAR, btemp->x, btemp->y + 16, 16, 16, 1);
					else if (btemp->type == BONUS_COIN)
					{
						mario.grade += 100;
						Stop_Music("coin.mp3");
						Play_Music("coin.mp3", 0);
						AddMonster(BONUS_COIN, btemp->x, btemp->y + 16, 14, 8, -1);
					}
				}
				btemp->prey = btemp->y;
				btemp->y += 8;
				if (btemp->condition)
					DrawModel(btemp->x - mapx, btemp->y, 9, 1, BLOCK, 1);
				else
					DrawModel(btemp->x - mapx, btemp->y, 9 + 1, 1, BLOCK, 1);
				btemp->premapx = mapx;
				bttemp = bttemp->next;
				continue;
			}
			/*draw the bonus box*/
			if (btemp->prey != btemp->y)
			{
				btemp->y -= 8;
				if (btemp->condition != 0)
					btemp->condition--;

				ErasePicture(btemp->x - btemp->premapx, btemp->y + 16, 16, 8);
			}
			if (btemp->condition)
				DrawModel(btemp->x - mapx, btemp->y, 9, 1, BLOCK, 1);
			else
				DrawModel(btemp->x - mapx, btemp->y, 9 + 1, 1, BLOCK, 1);
			btemp->premapx = mapx;
			bttemp = bttemp->next;
		}
	}
}

/*
 * usage: the running logic of monsters
 * note: print different monsters for different counter ( in different frames )
 */
void MonstersTimer(int counter)
{
	monsters *temp = head;
	int shiftx = 0;
	int monstergroundcheck;
	while (temp->next != NULL)
	{
		temp = temp->next;
		if ((counter + 1) % 2 == 0 && (counter + 3) % 3 == 0)
		{
			/*how does a koopas work*/
			if (temp->type == KOOPAS)
			{
				/*being beated by invincible mario*/
				if (temp->condition == ALREADYDEAD)
				{
					monstergroundcheck = GroundCheck(temp->x - mapx, temp->y);
					if (temp->y > monstergroundcheck)
					{
						if (temp->y - 16 <= monstergroundcheck)
							temp->y = monstergroundcheck;
						else
							temp->y -= 16;
					}
					else
					{
						int tempshiftx = SideCheck(temp->x - mapx, temp->y, -1 * temp->mflag * 16);
						temp->x += tempshiftx;
						if (tempshiftx != -1 * temp->mflag * 16)
						{
							Stop_Music("bound.mp3");
							Play_Music("bound.mp3", 0);
							temp->mflag *= -1;
						}
					}

					ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 23);
					DrawModel(temp->x - mapx, temp->y, KOOPAS + 2, 1, BLOCK, 1);
					temp->prex = temp->x;
					temp->prey = temp->y;
					temp->premapx = mapx;
					continue;
				}
				/*logic of koopas*/
				if (abs(px - (temp->x - mapx)) < 64 && abs(py - temp->y) < 32)
				{
					monstergroundcheck = GroundCheck(temp->x - mapx, temp->y);
					/*falling*/
					if (temp->y > monstergroundcheck)
					{
						if (temp->y - 16 <= monstergroundcheck)
							temp->y = monstergroundcheck;
						else
							temp->y -= 16;
					}
					/*runnig after mario*/
					else
					{
						if (temp->x - mapx > px && temp->x - mapx - px >= 8)
							temp->mflag = -1;
						else if (temp->x - mapx - px < -8)
							temp->mflag = 1;
						temp->x += SideCheck(temp->x - mapx, temp->y, 4 * temp->mflag);
					}
				}
				else
				{
					/*patroling*/
					shiftx = SideCheck(temp->x - mapx, temp->y, 4 * temp->mflag);
					monstergroundcheck = GroundCheck(temp->x - mapx + shiftx, temp->y);
					if (monstergroundcheck != temp->y || abs(shiftx) < 4 || temp->x - mapx >= windowwidth + 64 || temp->x - mapx + 4 * temp->mflag <= 0)
						temp->mflag *= -1;
					temp->x += 4 * temp->mflag;
				}
				/*draw the koopas*/
				ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 23);
				DrawModel(temp->x - mapx, temp->y, KOOPAS + (temp->condition + 1) / 2, -1 * temp->mflag, BLOCK, 1);
				temp->condition *= -1;
				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
			/*timer for bonus item*/
			/*bonus item mushroom*/
			if (temp->type == BONUS_MUSHROOM)
			{
				/*if the mushroom has escaped*/
				if (temp->x - mapx < 0 || temp->x - mapx > windowwidth || temp->y < 0)
				{
					temp->condition = DEAD;
					continue;
				}
				/*if the mushroom is eated*/
				if (temp->x - mapx - 8 <= px + 8 && temp->x - mapx + 8 >= px - 8 && temp->y <= py + 32 - mario.condition * 16 && temp->y + 16 >= py)
				{
					temp->condition = DEAD;
					if (mario.condition == STATE_SMALL)
						mario.condition = STATE_BIG;
					else
						mario.life++;
					continue;
				}
				/*the mushroom is moving*/
				monstergroundcheck = GroundCheck(temp->x - mapx, temp->y);
				if (temp->y > monstergroundcheck)
				{
					if (temp->y - 16 <= monstergroundcheck)
						temp->y = monstergroundcheck;
					else
						temp->y -= 16;
				}
				else
				{
					if (temp->x - mapx > px && temp->x - mapx - px > 16)
						temp->mflag = 1;
					else if (temp->x - mapx - px < -16)
						temp->mflag = -1;
					temp->x += SideCheck(temp->x - mapx, temp->y, 9 * temp->mflag);
				}
				/*draw the mushroom*/
				ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 15);
				DrawModel(temp->x - mapx, temp->y, BONUS_MUSHROOM, 1, BLOCK, 1);
				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
			/*bonus item star*/
			if (temp->type == BONUS_STAR)
			{
				/*if the star has escaped*/
				if (temp->x - mapx < 0 || temp->x - mapx > windowwidth || temp->y < 0)
				{
					temp->condition = DEAD;
					continue;
				}
				/*if the star is eated*/
				if (temp->x - mapx - 8 <= px + 8 && temp->x - mapx + 8 >= px - 8 && temp->y <= py + 32 - mario.condition * 16 && temp->y + 16 >= py)
				{
					temp->condition = DEAD;
					mario.invincible += 600;
					if (mario.strong != 1 && mario.condition != STATE_DEAD)
					{
						Stop_Music("background.mp3");
						Play_BGM_Repeat("invincible.mp3");
					}
					mario.strong = 1;
					continue;
				}
				/*the star is moving*/
				monstergroundcheck = GroundCheck(temp->x - mapx, temp->y);
				if (temp->mflag == -1 && temp->y - 9 <= monstergroundcheck)
				{
					temp->y = monstergroundcheck - 9;
					temp->mflag = 1;
				}
				else if (temp->y > monstergroundcheck + 48)
					temp->mflag = -1;

				temp->x += SideCheck(temp->x - mapx, temp->y, 6);
				temp->y += temp->mflag * 9;
				/*draw the star*/
				ErasePicture(temp->prex - temp->premapx, temp->prey, 16, 16);
				DrawModel(temp->x - mapx, temp->y, BONUS_STAR, 1, BLOCK, 1);
				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
		}
		if ((counter + 1) % 4 == 0)
		{
			/*how does a cheep-cheep work*/
			if (temp->type == CCHEEP)
			{
				/*being beated by invincible mario*/
				if (temp->condition == ALREADYDEAD)
				{
					if (temp->y <= 0)
						temp->condition = DEAD;
					else
						temp->y -= 16;
					ErasePicture(temp->prex - temp->premapx, temp->prey - 1, 16, 17);
					DrawModel(temp->x - mapx, temp->y, CCHEEP, 1, BLOCK, -1);
					temp->prex = temp->x;
					temp->prey = temp->y;
					temp->premapx = mapx;
					continue;
				}
				/*runnig after mario*/
				else
				{
					temp->x += 3;
					temp->y += 12 * temp->mflag;
					if (temp->y >= windowheight - 32)
						temp->mflag = -1;
				}
				/*draw the cheep-cheep*/
				ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 15);
				DrawModel(temp->x - mapx, temp->y, CCHEEP + (temp->condition + 1) / 2, -1, BLOCK, 1);
				temp->condition *= -1;
				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
			/*how does a spiny work*/
			if (temp->type == SPINY)
			{
				monstergroundcheck = GroundCheck(temp->x - mapx, temp->y);
				/*being beated by invincible mario*/
				if (temp->condition == ALREADYDEAD)
				{
					if (temp->y <= 0)
						temp->condition = DEAD;
					else
						temp->y -= 16;
					ErasePicture(temp->prex - temp->premapx, temp->prey - 1, 16, 17);
					DrawModel(temp->x - mapx, temp->y, SPINY, 1, BLOCK, -1);
					temp->prex = temp->x;
					temp->prey = temp->y;
					temp->premapx = mapx;
					continue;
				}
				/*falling*/
				if (temp->y > monstergroundcheck)
				{
					if (temp->y - 16 <= monstergroundcheck)
					{
						temp->y = monstergroundcheck;
						temp->mflag = 0;
					}
					else
						temp->y -= 16;
					temp->x += SideCheck(temp->x - mapx, temp->y, temp->mflag);
				}
				/*runnig after mario*/
				else
					temp->x += SideCheck(temp->x - mapx, temp->y, -3);
				/*draw the goombas*/
				ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 15);
				if (temp->mflag)
					DrawModel(temp->x - mapx, temp->y, SPINY + (temp->condition + 1) / 2, 1, BLOCK, 1);
				else
					DrawModel(temp->x - mapx, temp->y, SPINY + 2 + (temp->condition + 1) / 2, 1, BLOCK, 1);
				temp->condition *= -1;
				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
			/*how does a lakitu work*/
			if (temp->type == LAKITU)
			{
				/*runnig after mario*/
				if (temp->x - mapx > px && temp->x - mapx - px > 32)
					temp->mflag = -1;
				else if (temp->x - mapx - px < -32)
					temp->mflag = 1;
				temp->x += 1 * temp->mflag;
				/*draw the lakitu*/
				ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 31);
				if (counter + 1 == 24)
				{
					if (temp->condition == 2 && temp->y != py)
						AddMonster(SPINY, temp->x, temp->y, 14, 16, (px - temp->x + mapx + 128) / (temp->y - py) * 16);
					temp->condition++;
				}
				if (temp->condition == 12)
					temp->condition = 1;
				if (temp->condition == 10 || temp->condition <= 3)
					DrawModel(temp->x - mapx, temp->y, LAKITU + 1, -1 * temp->mflag, BLOCK, 1);
				else
					DrawModel(temp->x - mapx, temp->y, LAKITU, -1 * temp->mflag, BLOCK, 1);
				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
		}
		if ((counter + 1) % 2 == 0 && (counter + 1) % 3 == 0)
		{
			/*how does a goombas work*/
			if (temp->type == GOOMBAS)
			{
				/*being beated by invincible mario*/
				if (temp->condition == ALREADYDEAD)
				{
					if (temp->y <= 0)
						temp->condition = DEAD;
					else
						temp->y -= 16;
					ErasePicture(temp->prex - temp->premapx, temp->prey - 1, 16, 17);
					DrawModel(temp->x - mapx, temp->y, GOOMBAS, 1, BLOCK, -1);
					temp->prex = temp->x;
					temp->prey = temp->y;
					temp->premapx = mapx;
					continue;
				}
				/*logic of goombas*/
				if (abs(px - (temp->x - mapx)) < 64 && abs(py - temp->y) < 32)
				{
					monstergroundcheck = GroundCheck(temp->x - mapx, temp->y);
					/*falling*/
					if (temp->y > monstergroundcheck)
					{
						if (temp->y - 16 <= monstergroundcheck)
							temp->y = monstergroundcheck;
						else
							temp->y -= 16;
					}
					/*runnig after mario*/
					else
					{
						if (temp->x - mapx > px && temp->x - mapx - px > 8)
							temp->mflag = -1;
						else if (temp->x - mapx - px < -8)
							temp->mflag = 1;
						temp->x += SideCheck(temp->x - mapx, temp->y, 4 * temp->mflag);
					}
				}
				else
				{
					/*patroling*/
					shiftx = SideCheck(temp->x - mapx, temp->y, 4 * temp->mflag);
					monstergroundcheck = GroundCheck(temp->x - mapx + shiftx, temp->y);
					if (monstergroundcheck != temp->y || abs(shiftx) < 4 || temp->x - mapx >= windowwidth + 64)
						temp->mflag *= -1;
					temp->x += 4 * temp->mflag;
				}
				/*draw the goombas*/
				ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 15);
				DrawModel(temp->x - mapx, temp->y, GOOMBAS, temp->condition, BLOCK, 1);
				temp->condition *= -1;
				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
			/*how does a launcher work*/
			if (temp->type == LAUNCHER)
			{
				if (counter + 1 == 24)
					temp->condition++;
				if (temp->condition == 8)
				{
					temp->condition = 1;
					Stop_Music("bullet_bill.mp3");
					Play_Music("bullet_bill.mp3", 0);
					AddMonster(BULLET_BILL, temp->x, temp->y, 16, 16, temp->mflag);
				}
			}
			/*how does a bullet_bill work*/
			if (temp->type == BULLET_BILL)
			{
				/*being beated by invincible mario*/
				if (temp->condition == ALREADYDEAD)
				{
					if (temp->y <= 0)
						temp->condition = DEAD;
					else
						temp->y -= 24;
					ErasePicture(temp->prex - temp->premapx, temp->prey - 1, 16, 17);
					DrawModel(temp->x - mapx, temp->y, BULLET_BILL, 1, BLOCK, -1);
					temp->prex = temp->x;
					temp->prey = temp->y;
					temp->premapx = mapx;
					continue;
				}
				/*runnig after mario*/
				else
					temp->x -= 14 * temp->mflag;
				/*draw the bullet_bill*/
				ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 16, 15);
				DrawModel(temp->x - mapx, temp->y, BULLET_BILL, temp->mflag, BLOCK, 1);
				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
		}
		if ((counter + 1) % 2 != 0 && (counter + 1) % 3 == 0)
		{
			/*how does a firewall work*/
			if (temp->type == FIREWALL)
			{
				if (temp->mflag != -1 && temp->mflag != 1)
				{
					temp->prex = temp->mflag;
					temp->mflag = 1;
				}
				if (temp->y >= temp->prex + 64 - 20)
					temp->condition = -1;
				if (temp->y <= temp->prex + 2)
					temp->condition = 1;
				temp->y += temp->condition * 3;
				/*draw the firewall*/
				ErasePicture(temp->x - temp->premapx, temp->prey - 2, 35, 10);
				DrawModel(temp->x - mapx, temp->y, FIREWALL, 1, BLOCK, temp->mflag);
				temp->mflag *= -1;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
		}
		if ((counter + 1) % 2 != 0 && (counter - 1) % 3 == 0)
		{
		/*about the coins*/
			if (temp->type == COIN)
			{
				/*dead coin flies*/
				if (temp->condition == ALREADYDEAD && temp->mflag > 0)
				{
					temp->y += 5;
					temp->mflag--;
					ErasePicture(temp->prex - temp->premapx, temp->prey, 8, 14);
				}
				else
					ErasePicture(temp->prex - temp->premapx, temp->prey + 1, 8, 14);
				/*auto beat coin*/
				if (temp->mflag < 0)
				{
					temp->condition = ALREADYDEAD;
					temp->mflag = 3;
				}
				/*draw the coin*/
				DrawModel(temp->x - mapx, temp->y, COIN + temp->mflag, 1, BLOCK, 1);
				if (temp->condition != ALREADYDEAD)
					temp->mflag = (temp->mflag + 1) % 4;

				temp->prex = temp->x;
				temp->prey = temp->y;
				temp->premapx = mapx;
			}
		}
	}
}

/*
 * usage: mario's movement feedback from controling
 * note: draw different frames of mario for appropriate counter
 */
void ControlTimer(int counter)
{
	int groundcheck, topcheck;
	int checkmonsters;
	/*if mario is dead*/
	if (mario.condition == STATE_DEAD)
	{
		py -= 2;
		ErasePicture(prex, prey, 16, 16);
		DrawModel(px, py, 17, flag, BLOCK, 1);
		prex = px;
		prey = py;
		return;
	}
	/*if invincible*/
	if (mario.invincible > 0)
	{
		mario.invincible--;
		if (mario.invincible == 0)
		{
			if (mario.strong == 1)
			{
				Stop_Music("invincible.mp3");
				Play_BGM_Repeat("background.mp3");
				mario.strong = 0;
			}
		}
	}
	groundcheck = GroundCheck(px, py);
	topcheck = TopCheck(px, py);
	checkmonsters = CheckMonsters();
	/*if chuan mo*/
	if (py == topcheck)
		py += 16;
	/*if mario hits a monster*/
	if (checkmonsters == 2)
	{
		py += 25;
		jumptimer = 0;
		cancelTimer(state);
		state = MARIO_JUMP;
		startTimer(MARIO_JUMP, 25);
		timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_JUMP & 0x3f);
	}
	if (py - groundcheck == 5)
	{
		py = groundcheck;
		ErasePicture(prex, prey, 16, 32 - mario.condition * 16);
		DrawModel(px, py, 4 + 11 * mario.condition, flag, mario.condition, 1);
		prex = px;
		prey = py;
		return;
	}
	/*if hitted by monsters*/
	if (mario.invincible == 0 && (checkmonsters == 1 || checkmonsters == -1))
	{
		if (mario.condition == STATE_SMALL)
		{
			py += 64;
			ErasePicture(prex, prey + 1, 16, 31 - mario.condition * 16);
			mario.condition = STATE_DEAD;
			Stop_Music("background.mp3");
			Stop_Music("invincible.mp3");
			Play_Music("die.mp3", 0);
			return;
		}
		mario.invincible = 40;
		if (mario.life > 0)
			mario.life--;
		else
			mario.condition = STATE_SMALL;
		ShiftX(8 * checkmonsters, checkmonsters);
		py += 5;
		ErasePicture(prex, prey, 16, 32);
		DrawModel(px, py, 4 + 11 * mario.condition, flag, mario.condition, 1);
		prex = px;
		prey = py;
		return;
	}
	if (py > groundcheck && py - groundcheck < 8)
		py = groundcheck;
	switch (timerIDs[0])		/*turn side*/
	{
	case MARIO_RUN_FORWARD:flag = 1; break;
	case MARIO_RUN_BACK:flag = -1; break;
	}

	switch (timerIDs[0])		/*moving*/
	{
	case MARIO_RUN_FORWARD:
	case MARIO_RUN_BACK:
	{
		if (py > groundcheck + 1)
		{
			jumptimer = 0;
			state = MARIO_JUMP_END;
			prestate = timerIDs[0];
			cancelTimer(MARIO_JUMP);
			startTimer(MARIO_JUMP_END, 25);
			timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_JUMP_END & 0x3f);
			break;
		}
		ShiftX(6 * flag, flag);
		ErasePicture(prex, prey + 1, 16, 32 - mario.condition * 16);
		DrawModel(px, py, (int)ceil((counter + 1) * 1.0 / 8) + 11 * mario.condition, flag, mario.condition, 1);
		prex = px;
		prey = py;
		break;
	}
	case MARIO_JUMP:
	{
		jumptimer++;
		if (jumptimer >= 10 || py + 31 - 16 * mario.condition >= topcheck)
		{
			jumptimer = 0;
			state = MARIO_JUMP_END;
			cancelTimer(MARIO_JUMP);
			startTimer(MARIO_JUMP_END, 25);
			timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_JUMP_END & 0x3f);
			break;
		}
		if (prestate == MARIO_RUN_FORWARD || prestate == MARIO_RUN_BACK || prestate == -2)
			ShiftX(6 * flag, flag);
		py = py + 13 - jumptimer;
		ErasePicture(prex, prey, 16, 32 - mario.condition * 16);
		DrawModel(px, py, 5 + 11 * mario.condition, flag, mario.condition, 1);
		prex = px;
		prey = py;
		break;
	}
	case MARIO_JUMP_END:
	{
		if (jumptimer < 8)
			jumptimer++;
		if (prestate == MARIO_RUN_FORWARD || prestate == MARIO_RUN_BACK)
		{
			ShiftX(6 * flag, flag);
			groundcheck = GroundCheck(px, py);
		}

		if (py - 3 - jumptimer <= groundcheck)
		{
			jumptimer = 0;
			py = groundcheck;
			cancelTimer(state);
			if (prestate == MARIO_RUN_FORWARD || prestate == MARIO_RUN_BACK)
			{
				state = prestate;
				startTimer(prestate, 25);
				timerIDbackup = (timerIDbackup & 0xffffffc0) | (prestate & 0x3f);
				prestate = MARIO_JUMP_END;
				break;
			}
			cancelTimer(state);
			startTimer(MARIO_STAND, 25);
			prestate = -1;
			state = MARIO_STAND;
			timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_STAND & 0x3f);
			ErasePicture(prex, prey, 16, 32);
			DrawModel(px, py, 4 + 11 * mario.condition, flag, mario.condition, 1);
			prex = px;
			prey = py;
			break;
		}
		else
			py = py - 3 - jumptimer;
		ErasePicture(prex, prey, 16, 32 - mario.condition * 16);
		DrawModel(px, py, 5 + 11 * mario.condition, flag, mario.condition, 1);
		prex = px;
		prey = py;
	}
	case MARIO_STAND:
	{
		if (groundcheck < py - 5)
		{
			cancelTimer(state);
			state = MARIO_JUMP_END;
			startTimer(MARIO_JUMP_END, 25);
			timerIDbackup = (timerIDbackup & 0xffffffc0) | (MARIO_JUMP_END & 0x3f);
			break;
		}
		ErasePicture(prex, prey + 1, 16, 31 - mario.condition * 16);
		DrawModel(px, py, 4 + 11 * mario.condition, flag, mario.condition, 1);
		prex = px;
		prey = py;
	}
	}
	/*if invincible make mario twinkle*/
	if (mario.invincible > 0 && (counter + 1) % 4 == 0)
		ErasePicture(prex, prey + 1, 16, 31 - mario.condition * 16);
}
