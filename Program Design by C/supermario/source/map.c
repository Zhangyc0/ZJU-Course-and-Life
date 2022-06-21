/**
 * \brief		map generating module
 * \author		PrinzyW(Wang You)
 * \file		map.c
 */
/*********************************************************************************/

#include"map.h"

int mapx, mapy;
int premapx[4];
int movingground[12][2] = { 0 };

extern bonus *bhead;
extern bonus *btail;
extern condition mario;

/*
 * usage: initialize the map generating module
 * note: none
 */
void InitMap()
{
	mapx = 0;
	mapy = 0;
	startTimer(MAP_ROLLING, 25);
	timerIDbackup = (timerIDbackup & 0xfffff03f) | ((MAP_ROLLING & 0x3f) << 6);			/*abolished*/
}

/*
 * usage: generate a series of random number through mapx and starttime
 * note: none
 */
int* GenerateRand(int x)
{
	x /= 64;
	int m = 137;
	int i, rand = 1, temp = 1, ttemp = 1;
	int result[3] = { 0 };
	for (i = 0; i < (x + 1) % 5 + 1; i++)
	{
		if (i % 2 == 0)
			rand = (x * rand + (nowtime >> 1 & 0x3ff) + ttemp) % m + 1;
		else
			rand = (x * rand + (nowtime & 0x3ff) + ttemp) % m + 1;
		ttemp = temp;
		temp = rand;
	}
	result[0] = rand & 0xf;
	result[1] = rand >> 1 & 0xf;
	result[2] = rand >> 2 & 0xf;
	return result;
}

/*
 *	  ground type
 *
 *	0	void
 *	1	ground
 *	2	moving ground
 *	3	chemney_head
 *	4	chemney_body
 *	5	launcher_head
 *	6	launcher_body
 */
 
 /*
  * usage: make ground or read ground info through mapx by randomized number
  * note: none
  */
int* MakeGround(int x, int operration) 
{
	int globalground[12][3] = { 0 };
	int i;
	static int blast = 0, mlast = 0, clast = 0, llast = 0, mglast = 0;
	if (mario.world == 0)
		blast = 0, mlast = 0, clast = 0, llast = 0, mglast = 0;
	if (mario.world == 1)
	{
		/*generate randomized number from x*/
		int rand[3], lastrand[3], nextrand[3];
		memcpy(rand, GenerateRand(x + 64), 3 * sizeof(int));
		memcpy(lastrand, GenerateRand(x), 3 * sizeof(int));
		memcpy(nextrand, GenerateRand(x + 128), 3 * sizeof(int));

		/*create basic floor*/
		if (rand[0] == 0 && lastrand[0] != 0 && x > windowwidth)
			globalground[0][0] = 0;
		else
			globalground[0][0] = 1;

		/*create second floor*/
		if (rand[0] % 3 == 0 && nextrand[0] % 7 != 0 && rand[0] != 1)
			globalground[4][0] = 1;

		/*crate third floor*/
		if (rand[0] != 1 && (lastrand[0] % 3 == 0 || nextrand[0] % 3 == 0 || rand[0] % 3 == 0) && rand[0] % 7 != 0 && lastrand[0] % 7 != 0 && (rand[1] % 2 == 0 || rand[2] % 2 == 0) && !((rand[0] % 7 == 0 || lastrand[0] % 7 == 0) && (nextrand[0] == 0 || nextrand[0] == 1)) && !(rand[0] % 3 == 0 && (nextrand[0] == 1 || nextrand[0] == 0)))
			globalground[8][0] = 1;

		/*create moving floor*/
		if (rand[0] == 1)
		{
			if ((operration == OP_READ && x == mglast) || (operration == OP_MAKE && (x >= mglast + windowwidth + 64 || x == mglast)))
			{
				if (operration == OP_MAKE && x != mglast)
					mglast = x;
				globalground[0][0] = 2;
				if (rand[1] % 2 == 0)
					globalground[4][0] = 2;
			}
		}

		/*create chemney*/
		/*the middle one*/
		if (rand[0] != 1 && rand[0] != 0 && rand[0] % 7 == 0)
		{
			if (lastrand[0] != 1 && lastrand[0] != 1 && lastrand[0] % 2 == 0 && rand[1] % 2 == 0)
			{
				/*high*/
				globalground[1][0] = 4;
				globalground[2][0] = 4;
				globalground[3][0] = 4;
				globalground[4][0] = 4;
				globalground[5][0] = 3;
			}
			else if (rand[0] % 3 != 0 && rand[1] % 3 == 0)
			{
				/*medium*/
				globalground[1][0] = 4;
				globalground[2][0] = 4;
				globalground[3][0] = 4;
				globalground[4][0] = 3;
			}
			else if (rand[0] % 3 != 0)
			{
				/*short*/
				globalground[1][0] = 4;
				globalground[2][0] = 4;
				globalground[3][0] = 3;
			}
		}
		/*the left one*/
		if (rand[0] != 0 && rand[0] != 1 && nextrand[0] % 7 == 0 && rand[0] % 2 == 0)
		{
			if (rand[1] % 3 != 0)
			{
				/*medium*/
				globalground[1][0] = 4;
				globalground[2][0] = 4;
				globalground[3][0] = 4;
				globalground[4][0] = 3;
			}
			else
			{
				/*short*/
				globalground[1][0] = 4;
				globalground[2][0] = 4;
				globalground[3][0] = 3;
			}
		}
		/*the right one*/
		if (rand[0] != 0 && rand[0] != 1 && lastrand[0] % 7 == 0 && rand[1] % 2 == 0 && rand[0] % 2 == 0)
		{
			if (lastrand[1] % 2 != 0 && rand[1] % 3 == 0)
			{
				/*high*/
				globalground[1][0] = 4;
				globalground[2][0] = 4;
				globalground[3][0] = 4;
				globalground[4][0] = 4;
				globalground[5][0] = 4;
				globalground[6][0] = 3;
			}
			else if (rand[1] % 2 == 0)
			{
				/*short*/
				globalground[1][0] = 4;
				globalground[2][0] = 4;
				globalground[3][0] = 3;
			}
			else
			{
				/*medium*/
				globalground[1][0] = 4;
				globalground[2][0] = 4;
				globalground[3][0] = 4;
				globalground[4][0] = 3;
			}
		}
		/*terrain*/
		for (i = 0; i < 12; i++)
		{
			if (i < 11 && globalground[i][0] == 3 && globalground[i + 1][0] == 1)
				globalground[i + 1][0] = 0;
			if (i == 0 && globalground[i][0] == 1 && (nextrand[0] == 0 || nextrand[0] == 1))
			{
				globalground[i + 1][0] = 0;
				globalground[i + 2][0] = 0;
				globalground[i + 3][0] = 0;
				globalground[i + 4][0] = 0;
				globalground[i + 5][0] = 0;
				globalground[i + 6][0] = 0;
			}
			/*create bullet bill*/
			if (globalground[i][0] == 1 && globalground[i + 1][0] == 0)
			{
				if (rand[1] % (i + 6) == 0 && rand[2] % 3 == 0)
				{
					if (rand[2] % 2 == 0 && (i == 8 || globalground[i + 4][0] == 0))
					{
						globalground[i + 1][0] = 6;
						globalground[i + 2][0] = 5;
					}
					else
					{
						globalground[i + 1][0] = 5;
					}
				}
			}
		}
		/*input ground height*/
		for (i = 0; i < 12; i++)
		{
			/*nomal ground*/
			if (globalground[i][0] && globalground[i][0] != 2)
				globalground[i][1] = windowheight - (12 - i) * 16;
			/*moving ground*/
			if (globalground[i][0] == 2)
			{
				if (operration == OP_MAKE)
				{
					globalground[i][1] = (movingground[i][0] - 2) % windowheight;
					if (globalground[i][1] < 0)
						globalground[i][1] += windowheight;
					movingground[i][0] = globalground[i][1];
				}
				else if (operration == OP_READ)
					globalground[i][1] = movingground[i][0];
			}
		}
		/*create monsters*/
		for (i = 0; i < 12; i++)
		{
			/*firewall*/
			if (rand[1] % 2 != 0 && rand[0] != 0 && (i == 0 || i == 4) && globalground[i][0] == 1 && globalground[i + 4][0] == 1 && x > mlast)
			{
				if ((i == 0 || i == 4) && rand[2] % 2 == 0 && globalground[i + 1][0] == 0 && lastrand[0] != 0 && lastrand[0] != 1 && nextrand[0] != 0 && nextrand[0] != 1)
				{
					mlast = x;
					AddMonster(FIREWALL, x + 8, globalground[i][1] + 8, 8, 32, globalground[i][1] + 16);
				}
			}
			/*create launcher*/
			if (globalground[i][0] == 5 && operration == OP_MAKE && x - llast >= windowwidth - 64)
			{
				llast = x;
				if (rand[2] % 3 == 0)
				{
					AddMonster(LAUNCHER, x + 34, globalground[i][1], 16, 16, -1);
					Stop_Music("bullet_bill.mp3");
					Play_Music("bullet_bill.mp3", 0);
					AddMonster(BULLET_BILL, x + 34, globalground[i][1], 16, 16, -1);
				}
				else
				{
					AddMonster(LAUNCHER, x + 34, globalground[i][1], 16, 16, 1);
					Stop_Music("bullet_bill.mp3");
					Play_Music("bullet_bill.mp3", 0);
					AddMonster(BULLET_BILL, x + 34, globalground[i][1], 16, 16, 1);
				}
			}
			/*create lakitu*/
			if (x > windowwidth && rand[2] % 6 == 0 && rand[1] % 2 == 0 && x > mlast && operration == OP_MAKE)
			{
				mlast = x;
				AddMonster(LAKITU, windowwidth - 16, windowheight - 32, 16, 16, 1);
				printf("generate lakitu\n");
			}
			/*create koopas*/
			if (x > windowwidth && rand[1] % (i + 5) == 0 && globalground[i][0] == 1 && globalground[i + 1][0] == 0 && x > mlast && operration == OP_MAKE)
			{
				mlast = x;
				AddMonster(KOOPAS, x + 8, globalground[i][1] + 16, 16, 23, 1);
			}
			/*create goombas*/
			if (x > windowwidth && rand[1] % (i + 4) == 0 && globalground[i][0] == 1 && globalground[i + 1][0] == 0 && x > mlast && operration == OP_MAKE)
			{
				mlast = x;
				AddMonster(GOOMBAS, x + 8, globalground[i][1] + 16, 16, 16, 1);
			}
			/*create pirhana plants*/
			if (x > windowwidth && globalground[i][0] == 3 && globalground[i + 1][0] == 0 && x - mlast > 64 && operration == OP_MAKE && nextrand[0] % 5 != 0)
			{
				mlast = x;
				AddMonster(PIRHANA, x + 32, globalground[i][1] + 16, 23, 16, 1);
			}
			/*create bullet_bill*/
			if (x > windowwidth && rand[0] % 4 == 0 && rand[1] % 4 == 0 && rand[2] % 4 == 0 && x > mlast && operration == OP_MAKE)
			{
				mlast = x;
				AddMonster(BULLET_BILL, x + windowwidth, py, 16, 16, 1);
			}
			/*create coin*/
			if ((globalground[i][0] == 1 || globalground[i][0] == 3) && x > clast && operration == OP_MAKE)
			{
				if (i != 0 && i + 4 <= 11 && (globalground[i][0] == 1 || globalground[i][0] == 3) && globalground[i + 4][0] == 0 && rand[1] % 2 == 0)
				{
					clast = x;
					AddMonster(COIN, x + 24, globalground[i][1] + 16 * 4, 14, 8, 1);
				}
				if (i == 0 && globalground[i][0] != 0 && rand[1] % 8 == 0 || (i == 4 || i == 8) && rand[2] % 4 == 0)
				{
					clast = x;
					AddMonster(COIN, x + 8, globalground[i][1] + 16, 14, 8, 1);
				}
				if (i == 8 && globalground[i][0] == 1 && rand[2] % 2 != 0)
				{
					clast = x;
					AddMonster(COIN, x + 8, globalground[i][1] + 16 * 3, 14, 8, 1);
				}
			}
		}
		/*create cheep-cheep*/
		if (x > windowwidth && x > mlast && operration == OP_MAKE && rand[1] % 2 == 0 && rand[2] % 3 == 0)
		{
			mlast = x;
			AddMonster(CCHEEP, mapx + px - 64, 8, 16, 16, 1);
		}
		/*create bonus*/
		{
			/*second floor*/
			if (globalground[0][0] != 0 && globalground[4][0] == 1 && rand[1] % 2 == 0 && x - blast > windowwidth + 64 && operration == OP_MAKE)
			{
				blast = x;
				if (rand[2] % 2 == 0)
					AddBonus(BONUS_BIG, x + ((x % 3) + 1) * 16, globalground[4][1]);
				else if (rand[2] % 3 == 0)
					AddBonus(BONUS_STRONG, x + ((x % 3) + 1) * 16, globalground[4][1]);
				else
					AddBonus(BONUS_COIN, x + ((x % 3) + 1) * 16, globalground[4][1]);
				globalground[4][2] = (x % 3) + 1;
			}
			if (globalground[0][0] != 0 && globalground[4][0] == 1 && rand[1] % 2 == 0 && (operration == OP_READ || operration == OP_MAKE && x == blast))
				globalground[4][2] = (x % 3) + 1;

			/*third floor*/
			if (globalground[4][0] != 0 && globalground[8][0] == 1 && rand[1] % 3 == 0 && x - blast > windowwidth + 64 && operration == OP_MAKE)
			{
				blast = x;
				if (rand[2] % 2 == 0)
					AddBonus(BONUS_BIG, x + ((x % 3) + 1) * 16, globalground[8][1]);
				else
					AddBonus(BONUS_COIN, x + ((x % 3) + 1) * 16, globalground[8][1]);
				globalground[8][2] = (x % 3) + 1;
			}
			if (globalground[4][0] != 0 && globalground[8][0] == 1 && rand[1] % 3 == 0 && (operration == OP_READ || operration == OP_MAKE && x == blast))
				globalground[8][2] = (x % 3) + 1;
		}
	}
	else 
	{
		if(x < windowwidth * 3 / 4)
		globalground[8][0] = 1;
		/*input ground height*/
		for (i = 0; i < 12; i++)
		{
			/*nomal ground*/
			if (globalground[i][0] && globalground[i][0] != 2)
				globalground[i][1] = windowheight - (12 - i) * 16;
		}
	}
	return globalground;
}

/*
 * usage: draw the ground maked by MakeGround function
 * note: n = 0 -> stage 0
 *       n = 1 -> stage 1 - 4
 *		 n = 2 -> stage 5 - 8
 *       n = 3 -> stage 9 - 11
 */
void DrawGround(int n)
{
	int i, j;
	int currentx = mapx - mapx % (16 * 4);
	int prex = premapx[n] - premapx[n] % (16 * 4);
	int ground[12][3] = { 0 };

	/*draw logo & ranking*/
	if (mario.world == 0 && mario.life == 1)
	{
		mario.life = 0;
		DrawModel(windowwidth / 2, -16, 42, 1, BLOCK, 1);
		Ranking(8, 95);
	}

	//erase the previous ground
	while (prex - mapx < 375)
	{
		memcpy(ground, MakeGround(prex, OP_READ), sizeof(int) * 36);
		if (n == 0)
		{
			if (ground[0][0] == 1)
				ErasePicture(prex - premapx[n] + 24, ground[0][1], 16 * 4, 16);

			if (ground[0][0] == 2)
				ErasePicture(prex - premapx[n] + 24, movingground[0][1], 16 * 4, 16);
		}
		else
			for (j = 1 + 4 * (n - 1); j < 5 + 4 * (n - 1); j++)
			{
				if (ground[j][0] == 1)
					ErasePicture(prex - premapx[n] + 24, ground[j][1] + 1, 16 * 4, 15);

				if (ground[j][0] == 2)
					ErasePicture(prex - premapx[n] + 24, movingground[j][1], 16 * 4, 16);
				
				if (ground[j][0] == 3 || ground[j][0] == 4)
					ErasePicture(prex - premapx[n] + 32, ground[j][1] + 1, 16 * 2, 15);

				if (ground[j][0] == 5 || ground[j][0] == 6)
					ErasePicture(prex - premapx[n] + 35, ground[j][1] + 1, 16, 15);
			}
		prex += 16 * 4;
	}

	//draw the present ground
	while (currentx - mapx < 375)
	{
		memcpy(ground, MakeGround(currentx, OP_MAKE), sizeof(int) * 36);
		if (n == 0)
		{
			if (ground[0][0] == 1 || ground[0][0] == 2)
				for (i = 0; i < 4; i++)
					if (ground[0][2] != i || ground[0][2] == 0)
						DrawModel(currentx - mapx + i * 16, ground[0][1], 6, 1, MARIO, 1);

			if (ground[0][0] == 2)
				movingground[0][1] = ground[0][1];
		}
		else
			for (j = 1 + 4 * (n - 1); j < 5 + 4 * (n - 1); j++)
			{
				if (ground[j][0] == 1 || ground[j][0] == 2)
					for (i = 0; i < 4; i++)
						if (ground[j][2] != i || ground[j][2] == 0)
							DrawModel(currentx - mapx + i * 16, ground[j][1], 6, 1, MARIO, 1);

				if (ground[j][0] == 2)
					movingground[j][1] = ground[j][1];

				if (ground[j][0] == 3 || ground[j][0] == 4)
					DrawModel(currentx - mapx + 32,ground[j][1], 16 + ground[j][0], 1, BLOCK, 1);

				if (ground[j][0] == 5 || ground[j][0] == 6)
					DrawModel(currentx - mapx + 35, ground[j][1], 24 + ground[j][0], 1, BLOCK, 1);
			}
		currentx += 16 * 4;
	}
}
