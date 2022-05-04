#ifndef _score_h
#define _score_h

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct node {
	int sc[10];
	char name[10][1024];
	int num;
};
void readScore();
void writeScore();
void insert(int score, char nm[]);
void isInsert(int score, char nm[]);


#endif