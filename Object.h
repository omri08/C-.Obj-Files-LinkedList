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
	
} Object;

void initFacesAndVerts(FILE* fToRead, Object* o, char* line);
Object* initObjectProps(Object* o);
Object* createObject(char* filename);
void transformObject(char* originalObjectFileName, char* deformedObjectFileName);
void printFaces(Object* ptr, void* numberOfTriangularFaces);
void printVertexes(Object* ptr, void* numberOfVertexes);
void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces);
void printObjToFile(Object* ptr, FILE* f);
void printObjToBin(Object* ptr, FILE* f);
void printAllVerToFile(Vertex* arr, int size, FILE* f);
void printAllFacesToFile(Face* arr, int size, FILE* f);
Object* loadObjFromBin(FILE* f);

