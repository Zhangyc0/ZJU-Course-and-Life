/**
 * \brief		music module
 * \author		Wei Haoming
 * \file		music.c
 */
/*********************************************************************************/

#include "music.h"

/*
* usage: play a piece of music
* note: the music file need to be put in the same paper file with this program.
*/

void Play_Music(char* MusicName, double ContinueTime)
{

	TCHAR fileName[1000];
	_tcscpy(fileName, MusicName);
	TCHAR shortName[MAX_PATH];
	GetShortPathName(fileName, shortName, sizeof(shortName) / sizeof(TCHAR));
	TCHAR cmd[MAX_PATH + 10];
	wsprintf(cmd, "play %s", shortName);
	mciSendString(cmd, NULL, 0, NULL);
	//Sleep(ContinueTime);
}

void Stop_Music(char* MusicName)
{

	TCHAR fileName[1000];
	_tcscpy(fileName, MusicName);
	TCHAR shortName[MAX_PATH];
	GetShortPathName(fileName, shortName, sizeof(shortName) / sizeof(TCHAR));
	TCHAR cmd[MAX_PATH + 10];
	wsprintf(cmd, "stop %s", shortName);
	mciSendString(cmd, NULL, 0, NULL);
}

/*
* usage: play a indication voice
* note: none
*/
void Play_Indication_voice()
{
	Play_Music(IVName, IVContinueTime);
}

/*
* usage: play a piece of music repeatly
* note: the music file need to be put in the same paper file with this program.
*/
void Play_BGM_Repeat(char *RepeatBGM)
{
	TCHAR fileName[1000];
	_tcscpy(fileName, RepeatBGM);
	TCHAR shortName[MAX_PATH];
	GetShortPathName(fileName, shortName, sizeof(shortName) / sizeof(TCHAR));
	TCHAR cmd[MAX_PATH + 10];
	wsprintf(cmd, "play %s repeat", shortName);
	mciSendString(cmd, NULL, 0, NULL);
	//Sleep(BGMCountinueTime);
}

/*
* usage: play a list of music randomly
* note: none
*/
void Play_BGM_Random()
{
	int i;
	int random_num;
	for (i = 0; i < 1000; ++i)
	{
		random_num = rand() % MAX_BGM_NUMBER + 1;
		switch (random_num)
		{
		case(1) : Play_Music(BGM1, TIME1); 	break;
		case(2) : Play_Music(BGM2, TIME2); 	break;
		case(3) : Play_Music(BGM3, TIME3); 	break;
		case(4) : Play_Music(BGM4, TIME4); 	break;
		case(5) : Play_Music(BGM5, TIME5); 	break;
		case(6) : Play_Music(BGM6, TIME6); 	break;
		case(7) : Play_Music(BGM7, TIME7); 	break;
		case(8) : Play_Music(BGM8, TIME8); 	break;
		case(9) : Play_Music(BGM9, TIME9); 	break;
		case(10) : Play_Music(BGM10, TIME10);	break;
		};

	}
}

/*
* usage: play a list of music orderly
* note: none
*/
void Play_BGM_Order()
{
	int i;
	for (i = 1; i <= MAX_BGM_NUMBER; ++i)
	{

		switch (i)
		{
		case(1) : Play_Music(BGM1, TIME1); 	break;
		case(2) : Play_Music(BGM2, TIME2); 	break;
		case(3) : Play_Music(BGM3, TIME3); 	break;
		case(4) : Play_Music(BGM4, TIME4); 	break;
		case(5) : Play_Music(BGM5, TIME5); 	break;
		case(6) : Play_Music(BGM6, TIME6); 	break;
		case(7) : Play_Music(BGM7, TIME7); 	break;
		case(8) : Play_Music(BGM8, TIME8); 	break;
		case(9) : Play_Music(BGM9, TIME9); 	break;
		case(10) : Play_Music(BGM10, TIME10);	break;
		};
		if (i == MAX_BGM_NUMBER)
			i = 0;

	}
}












