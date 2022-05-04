/**
 * \brief		monsters feedback module
 * \author		PrinzyW(Wang You)
 * \file		monsters.c
 */
/*********************************************************************************/

#include"monsters.h"

monsters *head = NULL;
monsters *tail = NULL;

extern condition mario;

/*
 * usage: create the head node of monsters link
 * note: none
 */
void CreateMonstersLink()
{
	head = (monsters*)malloc(sizeof(monsters));
	head->next = NULL;
	tail = head;
}

/*
 * usage: add a node into monsters link
 * note: none
 */
void AddMonster(int mtype, int mx, int my, int mheight, int mwidth, int flag)
{
	monsters *newnode = (monsters*)malloc(sizeof(monsters));
	tail->next = newnode;
	newnode->next = NULL;
	newnode->type = mtype;
	newnode->x = mx;
	newnode->y = my;
	newnode->prey = my;
	newnode->prex = mx;
	newnode->condition = ALIVE;
	tail = tail->next;
	newnode->height = mheight;
	newnode->width = mwidth;
	newnode->premapx = mapx;
	newnode->mflag = flag;
}

/*
 * usage: check if the monsters are interacted : hit or hitted
 * note: none
 */
int CheckMonsters()
{
	monsters *temp = head;
	monsters *ttemp = head;
	int hitcheck = 0;
	while (temp->next != NULL && temp != NULL)
	{
		temp = temp->next;
		if (temp->condition == DEAD || temp->x - mapx < 0 || temp->y < 0 || temp->y > windowheight || temp->x - mapx > windowwidth * 2)
		{
			if (temp->next == NULL)
				tail = ttemp;
			if(temp->type == FIREWALL)
				ErasePicture(temp->x - temp->premapx + 8, temp->prey - 5, 20, 30);
			else
				ErasePicture(temp->prex - temp->premapx, temp->y + 1, temp->width, temp->height);
			temp = temp->next;
			free(ttemp->next);
			ttemp->next = temp;
			break;
		}
		if (temp->type == GOOMBAS || temp->type == CCHEEP || temp->type == BULLET_BILL || temp->type == SPINY || temp->type == LAKITU)
		{
			if (temp->x != temp->prex)
				hitcheck = (temp->y - temp->prey) / (temp->x - temp->prex) * (px - temp->x + mapx) + temp->y;
			else
				hitcheck = temp->y;
			if (temp->type != SPINY && mario.condition == STATE_BIG && state == MARIO_JUMP_END && px + 8 > min(temp->x, temp->prex) - mapx - temp->width / 2 && px - 8 < max(temp->x, temp->prex) - mapx + temp->width / 2 && py < hitcheck + temp->height && py > hitcheck)
			{
				Stop_Music("hit.mp3");
				Play_Music("hit.mp3", 0);
				mario.grade += 100;
				temp->condition = DEAD;
				ErasePicture(temp->prex - temp->premapx, temp->y + 1, temp->width, temp->height - 1);
				if(temp->type == GOOMBAS)
					DrawModel(temp->x - mapx, temp->y, temp->type + 1, 1, BLOCK, 1);
				return 2;
			}
			if (temp->condition != ALREADYDEAD && state != MARIO_JUMP_END && px + 8 > min(temp->x, temp->prex) - mapx - temp->width / 2 && px - 8 < max(temp->x, temp->prex) - mapx + temp->width / 2 && py < hitcheck + temp->height && py + 32 - 16 * mario.condition > hitcheck)
			{
				if (mario.strong == 0)
				{
					Stop_Music("hitted.mp3");
					Play_Music("hitted.mp3", 0);
					if (px > temp->x - mapx)
						return 1;
					else
						return -1;
				}
				else
				{
					Stop_Music("hit.mp3");
					Play_Music("hit.mp3", 0);
					temp->condition = ALREADYDEAD;
					temp->y += 32;
					mario.grade += 100;
					return 0;
				}
			}
		}
		if (temp->type == FIREWALL)
		{
			if (px + 16 > temp->x - mapx + 4 - temp->width / 2 && px - 16 < temp->x - mapx - 4 + temp->width / 2 && py < temp->y + temp->height && py + 32 - 16 * mario.condition > temp->y)
			{
				if (mario.strong == 0)
				{
					Stop_Music("hitted.mp3");
					Play_Music("hitted.mp3", 0);
					if (px > temp->x - mapx)
						return 1;
					else
						return -1;
				}
			}
		}
		if (temp->type == KOOPAS)
		{
			if (temp->x != temp->prex)
				hitcheck = (temp->y - temp->prey) * 1.0 / (temp->x - temp->prex) * (px - temp->x + mapx) + temp->y;
			else
				hitcheck = temp->y;
			if (temp->condition != ALREADYDEAD && mario.condition == STATE_BIG && state == MARIO_JUMP_END && px + 8 > temp->x - mapx - temp->width / 2 && px - 8 < temp->x - mapx + temp->width / 2 && py < hitcheck + temp->height && py > hitcheck)
			{
				Stop_Music("hit.mp3");
				Play_Music("hit.mp3", 0);
				mario.grade += 100;
				temp->condition = ALREADYDEAD;
				temp->mflag = 0;
				ErasePicture(temp->prex - temp->premapx, temp->y + 1, temp->width, temp->height - 1);
				DrawModel(temp->x - mapx, temp->y, temp->type + 2, 1, BLOCK, 1);
				return 2;
			}
			if (temp->condition == ALREADYDEAD && temp->mflag)
			{
				monsters *tttemp = head;
				while (tttemp->next != NULL)
				{
					tttemp = tttemp->next;
					hitcheck = temp->y;
					if (tttemp->condition != ALREADYDEAD && tttemp->x + 8 > min(temp->x, temp->prex) - temp->width / 2 && tttemp->x - 8 < max(temp->x, temp->prex) + temp->width / 2 && tttemp->y < temp->y + temp->height && tttemp->y + tttemp->height > temp->y)
					{
						Stop_Music("hit.mp3");
						Play_Music("hit.mp3", 0);
						mario.grade += 100;
						tttemp->condition = ALREADYDEAD;
						tttemp->y += 40;
					}
				}
			}
			if (temp->condition == ALREADYDEAD && px + 8 > temp->x - mapx - temp->width / 2 && px - 8 < temp->x - mapx + temp->width / 2 && py < hitcheck + temp->height && py + 32 - 16 * mario.condition > hitcheck)
			{
				Stop_Music("bound.mp3");
				Play_Music("bound.mp3", 0);
				if (px > temp->x - mapx)
					temp->mflag = 1;
				else
					temp->mflag = -1;
				break;
			}
			if (temp->condition != ALREADYDEAD && state != MARIO_JUMP_END && px + 8 > temp->x - mapx - temp->width / 2 && px - 8 < temp->x - mapx + temp->width / 2 && py < hitcheck + temp->height && py + 32 - 16 * mario.condition > hitcheck)
			{
				if (mario.strong == 0)
				{
					Stop_Music("hitted.mp3");
					Play_Music("hitted.mp3", 0);
					if (px > temp->x - mapx)
						return 1;
					else
						return -1;
				}
				else
				{
					Stop_Music("hit.mp3");
					Play_Music("hit.mp3", 0);
					mario.grade += 100;
					temp->condition = ALREADYDEAD;
					temp->mflag = 0;
					temp->y += 40;
					return 0;
				}
			}
		}
		if (temp->type == PIRHANA)
		{
			/*if mario hits a pirhana*/
			if (mario.condition == STATE_BIG && state == MARIO_JUMP_END && py <= temp->y + temp->height + 2 && py >= temp->y && px > temp->x - mapx - temp->width / 2 - 2 && px < temp->x - mapx + temp->width / 2 + 2)
			{
				Play_Music("hit.mp3", 0);
				mario.grade += 100;
				temp->condition = DEAD;
				return 2;
			}
			/*if mario is hitted by a pirhana*/
			if (state != MARIO_JUMP_END && px > temp->x - mapx - temp->width / 2 && px < temp->x - mapx + temp->width / 2 && temp->y >= py - temp->height && temp->y <= py + 32)
			{
				if (mario.strong == 0)
				{
					Stop_Music("hitted.mp3");
					Play_Music("hitted.mp3", 0);
					if (px > temp->x - mapx)
						return 1;
					else
						return -1;
				}
				else
				{
					mario.grade += 100;
					temp->condition = DEAD;
					return 0;
				}
			}
		}
		if (temp->type == COIN)
		{
			if (temp->condition == ALREADYDEAD && temp->mflag == 0)
			{
				temp->condition = DEAD;
			}
			if (px != prex)
				hitcheck = (py - prey) * 1.0 / (px - prex) * (temp->x - px - mapx) + py;
			else
				hitcheck = py;
			if (temp->condition != DEAD && temp->condition != ALREADYDEAD && temp->x - mapx >= min(px, prex) - 8 && temp->x - mapx <= max(px, prex) + 8 && temp->y <= hitcheck + 32 - 16 * mario.condition && temp->y >= hitcheck)
			{
				Stop_Music("coin.mp3");
				Play_Music("coin.mp3", 0);
				mario.grade += 100;
				temp->mflag = 3;
				temp->condition = ALREADYDEAD;
			}
		}
		ttemp = ttemp->next;
	}
	return 0;
}

