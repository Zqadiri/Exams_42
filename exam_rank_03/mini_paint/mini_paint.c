#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

struct      data
{
	int     w;
	int     h;
	char    c;
}           data;

struct  circle
{
	float X;    // a float, the horizontal position of the center of the circle
	float Y;    // a float, the vertical position of the center of the circle
	float R;    // RADIUS: a positive float but not 0, the radius of the circle
	char  C;    // the character c
	char CHAR;  // the char use to draw the circle  
}       circle;

int     quit(FILE *fp)
{
	write(1, "Error: Operation file corrupted\n", 32);
	if (fp)
		fclose(fp);
	return (1);
}

int fill_circle(int x, int y, struct circle *circle)
{
	float x1 = x;
	float y1 = y;
	float x2 = circle->X;
	float y2 = circle->Y;
	float dist;

	dist = sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if (dist >  circle->R)
		return (0);
	if (circle->R - dist <  1)
		return (1);
	if (circle->C == 'C')
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	struct circle circle;
	struct data data;
	char result[90000]; // 300 * 300
	FILE *fp;
	int ret = 0; // fscanf returns the number of items of the argument list successfully filled.

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(fp = fopen(argv[1] ,"r")))
		return (quit(fp));
	if (fscanf(fp, "%d %d %c ", &data.w, &data.h, &data.c) != 3)
		return (quit(fp));
	if (data.w <= 0 || data.w > 300 || data.h <= 0 || data.h > 300) 
		return (quit(fp));
	memset (result, data.c, data.w * data.h);
	while ((ret = fscanf(fp, "%c %f %f %f %c\n", &circle.C, &circle.X,
	&circle.Y, &circle.R, &circle.CHAR)) == 5)
	{
		if (circle.R <= 0.000000000 || (circle.C != 'c' && circle.C != 'C'))
			return (quit(fp));
		for (int y = 0; y < data.h; y++)
		{
			for (int x = 0; x < data.w; x++)
			{
				if (fill_circle(x, y, &circle))
					result[y * data.w + x]  = circle.CHAR;
			}
		}
	}
	if (ret != EOF)
		return (quit(fp));
	for (int i = 0; i < data.h; i++)
	{
		write(1, result + data.w * i, data.w);
		write(1, "\n", 1);
	}
	fclose(fp);
	return (0);
}