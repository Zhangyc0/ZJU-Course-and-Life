#ifndef _music_h
#define _music_h

/*basic resources*/
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <tchar.h>

#pragma comment(lib, "Winmm.lib")
/*note: if you use DEV-C++ as the coppiler, you should enter
menu bar-tool-complication-the second fram and input the
command"-static-libgcc -lwinmm"*/

#define IVName "test1.mp3"
/*the file name of indication voice*/
#define IVContinueTime 100
/*the continue time of indication voice, in ms*/

#define MAX_BGM_NUMBER 10
/*the total number of BGM*/

#define BGM1 "test1.mp3"
#define BGM2 "test2.mp3" 
#define BGM3 "test3.mp3"
#define BGM4 "test4.mp3"
#define BGM5 "test5.mp3"
#define BGM6 "test6.mp3"
#define BGM7 "test7.mp3"
#define BGM8 "test8.mp3"
#define BGM9 "test9.mp3"
#define BGM10 "test10.mp3"
/*the file name of BGM*/

#define TIME1 200*1000
#define TIME2 200*1000
#define TIME3 200*1000
#define TIME4 200*1000
#define TIME5 200*1000
#define TIME6 200*1000
#define TIME7 200*1000
#define TIME8 200*1000
#define TIME9 200*1000
#define TIME10 200*1000
/*the continue time of BGM, in ms*/

#define BGMCountinueTime 500*1000
/*make delays to prevent stopping as soon as you play*/

/*function declaration*/
void Play_Music(char *MusicName, double ContinueTime);/* play a piece of music */
void Play_Indication_voice();/* play indication voice*/
void Play_BGM_Repeat(char *RepeatBGM);/*play a piece of BGM repeatly*/
void Play_BGM_Random();/*play a list of BGM randomly*/
void Play_BGM_Order();/*play a list of BGM orderly*/
void Stop_Music(char* MusicName);

#endif