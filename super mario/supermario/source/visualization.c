/**
 * \brief		visualization module
 * \author		PrinzyW(Wang You)
 * \file		visualizatin.c
 */
/*********************************************************************************/

#include"visualization.h"

/*
 * usage: transform data into correct ifo
 * note: this program use char to get color and coordination ifo from model file,
 *       while when it comes to a number bigger than 127 it would get negative,
 *		 that's why we need to transform it into correct form.
 */
int TransData(char temp)
{
	if (temp >= 0)
		return (int)(temp);
	else
	{
		temp = temp & 0x7f;
		return (int)((temp) + 0x80);
	}
}

/*
 * usage: print a basic part of a pixel painting
 * note: draw a rectangle started at (x,y) with x coordination shifting a certain distance
 */
void DrawCell(int y, int x, int shiftx, int shifty, int flag, int upsidedown)
{
	double l = 0.04;
	
	SetPenSize(1);
	MovePen(GetCurrentX() + FROMPIXEL(x), GetCurrentY() + FROMPIXEL(y));
	StartFilledRegion(1);
	DrawLine(l * shiftx * flag, 0);
	DrawLine(0, l * shifty * upsidedown);
	DrawLine(-l * shiftx * flag, 0);
	DrawLine(0, -l * shifty * upsidedown);
	EndFilledRegion();
}

/*
 * usage: open the model file
 * note: send an error message when not finding the file
 */
void OpenModelFile()
{
	DefineColor("white", 0, 0, 0);
	if ((models = fopen("model.mds", "rb")) == NULL)
	{
		int ErrorMessage = MessageBox(NULL, TEXT("model file not found!"), TEXT("Error"), MB_OK);
		exit(0);
	}
}

/*
 * usage: find the location of the needed data through its index
 * note: read 3 chars a time
 */
void FindModel(int index)
{
	char temp[4];
	
	rewind(models);
	fread(temp, sizeof(char), 3, models);
	while ((int)(temp[0]) != index)
		fread(temp, sizeof(char), 3, models);
	rewind(models);
	fseek(models, TransData((int)(temp[1])) * 256 + TransData((int)(temp[2])), SEEK_SET);
}

/*
 * usage: draw the whole pixel painting through picture info in the file
 * note: read 3 / 4 chars a time
 */
void DrawModel(int x, int y, int index, int flag, int type, int upsidedown)
{
	/*color library*/
	static char colors[255][4] = { 0 };
	char temp[4], colorname[4];
	int isColor = 1, pwidth, pheight, i = 0;
	
	FindModel(index);
	
	if (type == MARIO)
	{
		fread(temp, sizeof(char), 3, models);		/*read the width and height of the picture first*/
		pwidth = (int)(temp[1]);
		pheight = (int)(temp[2]);
		while (1)
		{
			fread(temp, sizeof(char), 3, models);
			if ((int)(temp[0]) == 0 && (int)(temp[1]) == 0 && (int)(temp[2]) == 0)  /*end the painting of the picture*/
				break;
			if ((int)(temp[0]) == -1 && (int)(temp[1]) == -1 && (int)(temp[2]) == -1)  /*end the painting of current color*/
			{
				isColor = 1;
				continue;
			}
			if (isColor == 1)  /*read the RGB color info*/
			{
				isColor = 0;
				colorname[0] = temp[0];
				colorname[1] = temp[1];
				colorname[2] = temp[2];
				colorname[3] = '\0';
				for (i = 0; !(colors[i][0] == 0 && colors[i][1] == 0 && colors[i][2] == 0); i++)
					if (!strcmp(colors[i], colorname))
						break;
				
				if (colors[i][0] == 0 && colors[i][1] == 0 && colors[i][2] == 0)
				{
					DefineColor(colorname, TransData(temp[0]) * 1.0 / 255, TransData(temp[1]) * 1.0 / 255, TransData(temp[2]) * 1.0 / 255);
					memcpy(colors[i], colorname, 4 * sizeof(char));
				}
				SetPenColor(colorname);
				continue;
			}
			/*draw a part of the picture*/
			MovePen(FROMPIXEL(x), FROMPIXEL(y - pheight * (upsidedown - 1) / 2));
			DrawCell((pheight - (int)(temp[0])) * upsidedown, flag * ((int)(temp[1]) - pwidth / 2), (int)(temp[2]), 1, flag, upsidedown);
		}
	}
	else if (type == BLOCK)
	{
		fread(temp, sizeof(char), 4, models);		/*read the width and height of the picture first*/
		pwidth = (int)(temp[1]);
		pheight = (int)(temp[2]);
		while (1)
		{
			fread(temp, sizeof(char), 4, models);
			if ((int)(temp[0]) == 0 && (int)(temp[1]) == 0 && (int)(temp[2]) == 0 && (int)(temp[3]) == 0)  /*end the painting of the picture*/
				break;
			if ((int)(temp[0]) == -1 && (int)(temp[1]) == -1 && (int)(temp[2]) == -1 && (int)(temp[3] == -1))  /*end the painting of current color*/
			{
				isColor = 1;
				continue;
			}
			if (isColor == 1)  /*read the RGB color info*/
			{
				isColor = 0;
				colorname[0] = temp[0];
				colorname[1] = temp[1];
				colorname[2] = temp[2];
				colorname[3] = '\0';
				for (i = 0; !(colors[i][0] == 0 && colors[i][1] == 0 && colors[i][2] == 0); i++)
					if (!strcmp(colors[i], colorname))
						break;

				if (colors[i][0] == 0 && colors[i][1] == 0 && colors[i][2] == 0)
				{
					DefineColor(colorname, TransData(temp[0]) * 1.0 / 255, TransData(temp[1]) * 1.0 / 255, TransData(temp[2]) * 1.0 / 255);
					memcpy(colors[i], colorname, 4 * sizeof(char));
				}
				SetPenColor(colorname);
				continue;
			}
			/*draw a part of the picture*/
			MovePen(FROMPIXEL(x), FROMPIXEL(y - pheight * (upsidedown - 1) / 2));
			if (index != 42)
				DrawCell((pheight - (int)(temp[0])) * upsidedown, flag * ((int)(temp[1]) - pwidth / 2), (int)(temp[2]), (int)(temp[3]), flag, upsidedown);
			else
				DrawCell((pheight - (int)(temp[0])) * upsidedown * 2, flag * ((int)(temp[1]) - pwidth / 2) * 2, (int)(temp[2]) * 2, (int)(temp[3]) * 2, flag, upsidedown);
		}
	}
}

/*
 * usage: erase the previous picture
 * note: none
 */
void ErasePicture(int x, int y, int width, int height)
{
	if (x == 0 && y == 0)
		return;
	MovePen(FROMPIXEL(x) - FROMPIXEL(width) / 2, FROMPIXEL(y));
	SetEraseMode(1);
	StartFilledRegion(1);
	DrawLine(FROMPIXEL(width + 1), 0);
	DrawLine(0, FROMPIXEL(height + 1));
	DrawLine(-FROMPIXEL(width + 1), 0);
	DrawLine(0, -FROMPIXEL(height + 1));
	EndFilledRegion();
	SetEraseMode(0);
}

