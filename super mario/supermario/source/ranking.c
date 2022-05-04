/**
 * \brief		ranking module
 * \author		PrinzyW(Wang You)
 * \file		ranking.c
 */
/*********************************************************************************/

#include"ranking.h"

extern condition mario;
extern struct node nd;

char name[80] = "Player";

/*
 * usage: draw the name text box
 * note: none
 */
void NameText(int bx, int by)
{
	double x = FROMPIXEL(bx);
	double y = FROMPIXEL(by);

	SetPenColor("Black");
	MovePen(x, y + FROMPIXEL(12) + FROMPIXEL(10));
	DrawTextString("Your Name");
	textbox(GenUIID(0), x, y + FROMPIXEL(10), FROMPIXEL(48), GetFontHeight() * 2, name, sizeof(name));
	button(GenUIID(0), x + FROMPIXEL(32), y, FROMPIXEL(16), GetFontHeight() * 2, "Done");
}

/*
 * usage: get mouse coordination for name box
 * note: none
 */
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
}

/*
 * usage: print player's score and rankings of players
 * note: none
 */
void Ranking(int bx, int by)
{
	int i;
	char grade[50] = { 0 };
	char temp[9][10] = { "一着", "二着", "三着", "四着", "五着", "六着", "七着", "八着", "九着" };
	double x = FROMPIXEL(bx);
	double y = FROMPIXEL(by);
	static int lastscore = 0;

	/*player's score*/
	MovePen(x, y + FROMPIXEL(12) + FROMPIXEL(10));
	SetPenColor("Black");
	DrawTextString("Your Greast Score");
	MovePen(x, y + FROMPIXEL(16));
	sprintf(grade, "%d meters", mario.lastmapx);
	DrawTextString(grade);

	/*print ranking title*/
	MovePen(x + FROMPIXEL(16), y);
	SetPenColor("Red");
	DrawTextString("Ranking");
	readScore();
	if (mario.lastmapx > lastscore)
	{
		lastscore = mario.lastmapx;
		insert(mario.lastmapx, name);
		writeScore();
	}
	/*print the rankings*/
	for (i = 0; i < min(9, nd.num); i++)
	{
		SetPenColor("Black");
		MovePen(x - FROMPIXEL(6), y - (i + 1) * FROMPIXEL(8));
		sprintf(grade, "%s   %s", temp[i], nd.name[i]);
		DrawTextString(grade);
		MovePen(x + FROMPIXEL(48), y - (i + 1) * FROMPIXEL(8));
		sprintf(grade, "%d", nd.sc[i]);
		DrawTextString(grade);
	}
}