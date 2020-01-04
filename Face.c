#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include <math.h>
#include "Face.h"
#include "def.h"


void initFace(char* line, Face* f)
{
	int num;
	int i = 0; // the amount of space between 2 integers
	int realSize = 0;
	f->size = 2; // temp size
	f->vertex = (int*)malloc(sizeof(int) * f->size);
	removeAllButIndexes(line);

	while (sscanf(line, "%*c%d%n", &num, &i) == 1) {

		if (realSize == f->size) {
			f->size *= 2;
			f->vertex = (int*)realloc(f->vertex, sizeof(int) * f->size);
		}
		f->vertex[realSize++] = num;

		line += i;

	}
	f->size = realSize;

}

void removeAllButIndexes(char* line)
{

	int len = strlen(line);
	for (int i = 0; i < len; i++)
	{
		if (line[i] == '/')
			i = removeUntilWhiteSpace(line, i);
	}
}

//delete until whiteSpace
int removeUntilWhiteSpace(char* line, int index)
{
	while (line[index] != ' ' && index < strlen(line))
	{
		line[index] = ' ';
		index++;
	}
	return index;
}
BOOL checkXVert(Face f, int x)
{

	if (f.size == x) 
		return True;
	
	else
		return False;
}

float calAreaOfTrianFace(Vertex a, Vertex b, Vertex c)
{
	float ab = distance(a.x, a.y, a.z, b.x, b.y, b.z);
	float ac = distance(a.x, a.y, a.z, c.x, c.y, c.z);
	float bc = distance(b.x, b.y, b.z, c.x, c.y, c.z);
	float s = (ab + bc + ac) / 2;
	float area = sqrt(s * (s - ab) * (s - bc) * (s - ac));
	return area;

}

float distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float d = sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) +
		pow(z2 - z1, 2) * 1.0);
	return d;
}
