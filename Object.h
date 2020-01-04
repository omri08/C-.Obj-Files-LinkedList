#pragma once
#include <stdio.h>
#include "Vertex.h"
#include "Face.h"

typedef struct {
	// Array of all Vertexes
	int numberOfVertexes;
	Vertex* vertexes;
	// Array of all Faces
	int  numberOfFaces;
	Face* faces;
	char* name;
} Object;

void initFacesAndVerts(FILE* fToRead, Object* o, char* line);
Object* initObjectProps(Object* o);
Object* createObject(char* filename);
void transformObject(char* originalObjectFileName, char* deformedObjectFileName);
void printFaces(Object* ptr, void* numberOfTriangularFaces);
void printVertexes(Object* ptr, void* numberOfVertexes);
void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces);
void printAll(Object* ptr);
