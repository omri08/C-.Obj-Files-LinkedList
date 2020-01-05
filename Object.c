#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include "Object.h"
#include "../Project2/def.h"


void transformObject(char* originalObjectFileName, char* deformedObjectFileName)
{
	char line[300];
	FILE* fToRead = fopen(originalObjectFileName, "r");
	FILE* fToWrite = fopen(deformedObjectFileName, "w+");
	// handling errors
	if (fToRead == NULL)
		return;
	if (fToWrite == NULL) {
		fclose(fToRead);
		return;
	}
	while (fgets(line, 128, fToRead) != NULL) {
		if (line[0] == 'v' && line[1] != 'n' && line[1] != 't') {
			Vertex v;
			initVertex(line, &v);
			transformV(&v);
			fprintf(fToWrite, "%s\n", vertexToString(&v));
		}
		else {
			fprintf(fToWrite, "%s", line);
		}
	}
	fclose(fToRead);
	fclose(fToWrite);

}

Object* initObjectProps(Object* o)
{
	o->numberOfFaces = 2; // temp size
	o->numberOfVertexes = 2; // temp size
	o->faces = (Face*)malloc(sizeof(Face) * o->numberOfFaces);
	if (!o->faces)
		return NULL;
	o->vertexes = (Vertex*)malloc(sizeof(Vertex) * o->numberOfVertexes);
	if (!o->vertexes) {
		free(o->faces);
		return NULL;
	}
}

void initFacesAndVerts(FILE* fToRead, Object* o, char* line)
{
	if (!initObjectProps(o))
		return NULL;

	int realNumOfFaces = 0;
	int realNumOfVer = 0;

	while (fgets(line, 300, fToRead)) {

		if (realNumOfFaces == o->numberOfFaces) {
			o->numberOfFaces *= 2;
			o->faces = (Face*)realloc(o->faces, sizeof(Face) * o->numberOfFaces);
		}

		if (realNumOfVer == o->numberOfVertexes) {
			o->numberOfVertexes *= 2;
			o->vertexes = (Vertex*)realloc(o->vertexes, sizeof(Vertex) * o->numberOfVertexes);
		}

		if (line[0] == 'f') {
			Face f;
			initFace(line, &f);
			o->faces[realNumOfFaces++] = f;

		}

		if (line[0] == 'v' && line[1] == ' ') {
			Vertex v;
			initVertex(line, &v);
			o->vertexes[realNumOfVer++] = v;
		}

	}

	o->numberOfFaces = realNumOfFaces; // final size
	o->numberOfVertexes = realNumOfVer; // final size

}

Object* createObject(char* filename)
{
	// handling basics inits
	Object* o = (Object*)malloc(sizeof(Object));
	
	if (!o)
		return NULL;


	char* line = (char*)malloc(sizeof(char) * 350);
	if (!line)
		return NULL;



	FILE* fToRead = fopen(filename, "r");
	if (!fToRead) {
		free(line);
		return NULL;
	}

	initFacesAndVerts(fToRead, o, line);

	free(line);
	fclose(fToRead);
	return o;
}



void printFaces(Object* ptr, void* numberOfTriangularFaces)
{
	*(int*)numberOfTriangularFaces = 0;
	for (int i = 0; i < ptr->numberOfFaces; i++)
	{
		if (checkXVert(ptr->faces[i], 3) == True)
			*(int*)numberOfTriangularFaces += 1;
	}


}

void printVertexes(Object* ptr, void* numberOfVertexes)
{
	*(int*)numberOfVertexes = ptr->numberOfVertexes;

}

void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces)
{
	*(float*)totalAreaOfTriangularFaces = 0;
	for (int i = 0; i < ptr->numberOfFaces; i++) {
		if (checkXVert(ptr->faces[i], 3) == True)
		{
			int index1 = ptr->faces[i].vertex[0] - 1;
			int index2 = ptr->faces[i].vertex[1] - 1;
			int index3 = ptr->faces[i].vertex[2] - 1;
			*(float*)totalAreaOfTriangularFaces +=
				calAreaOfTrianFace(ptr->vertexes[index1], ptr->vertexes[index2], ptr->vertexes[index3]);
		}
	}

}

void printObjToFile(Object* ptr, FILE* f)
{

	
	printAllVerToFile(ptr->vertexes, ptr->numberOfVertexes, f);
	printAllFacesToFile(ptr->faces, ptr->numberOfFaces, f);
	fprintf(f,"newObject\n");
}

void printAllVerToFile(Vertex* arr, int size, FILE* f)
{
	for (int i = 0; i < size; i++)
		printVerToFile(arr[i], f);
}

void printAllFacesToFile(Face* arr, int size, FILE* f)
{
	for (int i = 0; i < size; i++)
		printFaceToFile(arr[i], f);
}