#pragma once
#include <stdlib.h>
typedef struct
{
	float x;
	float y;
	float z;
}Vertex;


void initVertex(char* line, Vertex* v);
void transformV(Vertex* v);
char* vertexToString(Vertex* v);
void printVerToFile(Vertex v,FILE* f);
void printVerToBin(Vertex v, FILE* f);
void loadVerFromBin(Vertex* v, FILE* f);
