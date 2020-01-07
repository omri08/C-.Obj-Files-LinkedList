#pragma once
#include "Vertex.h"
typedef struct {
	int size;	// Number of vertexes of the face	
	int* vertex;	// Array of Ids of the vertexes
} Face;

void initFace(char* line, Face* f);
void removeAllButIndexes(char* line);
int removeUntilWhiteSpace(char* line, int index);
int checkXVert(Face f, int x);
float calAreaOfTrianFace(Vertex a, Vertex b, Vertex c);
float distance(float x1, float y1, float z1, float x2, float y2, float z2);
void printFaceToFile(const Face fp, FILE* f);
void printFaceToBin(Face fp, FILE* f);
void loadFaceFromBin(Face* fp, FILE* f);