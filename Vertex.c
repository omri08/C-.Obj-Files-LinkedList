#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Vertex.h"



void initVertex(char* line, Vertex* v)
{

	if (sscanf(line, "v %f %f %f", &v->x, &v->y, &v->z) != 3)
		return;


}
void transformV(Vertex* v)
{
	v->x *= 0.3;
}
char* vertexToString(Vertex* v)
{
	char* str;
	str = (char*)malloc(sizeof(char) * 128);
	sprintf(str, "v %f %f %f", v->x, v->y, v->z);
	return str;
}

void printVerToFile(Vertex v, FILE* f)
{
	fprintf(f, "v  %f %f %f\n", v.x, v.y, v.z);
}

void printVerToBin(Vertex v, FILE* f)
{
	fwrite(&v.x, sizeof(float), 1, f);
	fwrite(&v.y, sizeof(float), 1, f);
	fwrite(&v.z, sizeof(float), 1, f);

}

void loadVerFromBin(Vertex* v, FILE* f)
{
	fread(&v->x, sizeof(float), 1, f);
	fread(&v->y, sizeof(float), 1, f);
	fread(&v->z, sizeof(float), 1, f);
		
}