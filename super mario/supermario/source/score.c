/**
 * \brief		score module
 * \author		Tian Chengzhuo
 * \file		score.c
 */
/*********************************************************************************/

#include"score.h"

struct node nd;
void readScore() 
{//读文件
	FILE *fp;
	char line;
	nd.num = 0;
	char ap[2] = "0";
	if ((fp = fopen("read.txt", "rb")) == NULL) 
	{ 
		fp = fopen("read.txt", "wb"); 
		fscanf(fp, "%d %s", &nd.num, &ap[0]); 
		return; 
	}
	while (!feof(fp)) 
	{
		fscanf(fp, "%d %s", &nd.sc[nd.num], &nd.name[nd.num]);
		nd.num++;
	}
	if (nd.num > 0)
		nd.num--;
	fclose(fp);
}//99 a 98 b 97 c 96 d 95 e 94 f 92 g 91 h 90 i 89 k

void writeScore() 
{//写文件
	FILE *fp;
	int i = 0;
	if ((fp = fopen("read.txt", "wb")) == NULL) 
		return; 

	for (i = 0; i<nd.num - 1; i++) 
		fprintf(fp, "%d %s\n", nd.sc[i], nd.name[i]);

	fclose(fp);
}

void insert(int score, char nm[]) 
{//
	if (score == 0)
		return;
	int i = 0, j = 0;
	if (nd.num == 0) 
	{
		nd.sc[0] = score;
		strcpy(nd.name[0], nm);
		nd.num++;
	}
	else if (nd.num>0 && nd.num<10) 
	{
		for (i = 0; i<nd.num; i++) 
			if (nd.sc[i] < score)
				break;
		for (j = nd.num - 1; j>=i; j--) 
		{
			nd.sc[j + 1] = nd.sc[j];
			strcpy(nd.name[j + 1], nd.name[j]);
		}
		nd.sc[i] = score;
		strcpy(nd.name[i], nm);
		nd.num++;
	}
	else {
		for (i = 0; i<10; i++)
			if (nd.sc[i] < score)
				break;
		for (j = 8; j >= i; j--) 
		{
			nd.sc[j + 1] = nd.sc[j];
			strcpy(nd.name[j + 1], nd.name[j]);
		}
			nd.sc[i] = score;
			strcpy(nd.name[i], nm);
		}
}

void isInsert(int score, char nm[]) 
{//判断是否插入
	int i = 0, j = 0;
	//char name[1024];
	if (nd.num == 0) 
	{
		//printf("请输入你的姓名：\n");
		//scanf("%s", &name);
		//getchar();
		insert(score, nm);
		return;
	}
	else 
	{
		for (i = 0; i<=nd.num; i++) 
		{
			if (nd.sc[i] >= score&&nd.sc[i + 1]<score) 
			{
				//printf("请输入你的姓名：\n");
				//gets(name);
				//scanf("%s", &name);
				insert(score, nm);
				return;
			}
		}
	}
}

void printScore() {//打印成绩
	printf("目前前10分数排名：\n");
	int i = 0;
	for (i = 0; i<nd.num; i++) 
		printf("%d %s\n", nd.sc[i], nd.name[i]);
}