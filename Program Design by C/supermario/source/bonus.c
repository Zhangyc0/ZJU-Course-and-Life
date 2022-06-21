/**
 * \brief		bonus module
 * \author		PrinzyW(Wang You)
 * \file		bonus.c
 */
/*********************************************************************************/

#include"bonus.h"

condition mario = { 1, 1, 0 };
bonus *bhead = NULL;
bonus *btail = NULL;

/*
 * usage: create the head node of bonus link
 * note: none
 */
void CreateBonusLink()
{
	bhead = (bonus*)malloc(sizeof(bonus));
	bhead->next = NULL;
	btail = bhead;
}

/*
 * usage: add a node into bonus link
 * note: none
 */
void AddBonus(int btype, int bx, int by)
{
	bonus *bnewnode = (bonus*)malloc(sizeof(bonus));
	btail->next = bnewnode;
	bnewnode->next = NULL;
	bnewnode->type = btype;
	bnewnode->x = bx;
	bnewnode->y = by;
	bnewnode->prey = by;
	bnewnode->condition = Unbroken;
	btail = btail->next;
	bnewnode->premapx = mapx;
	if (btype == 23)
		bnewnode->condition = (bx / 64) % 3 + 5;
}
