#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "Scene.h"
#include "stdarg.h"
#include "Object.h"



Scene* createScene(char* fileName, ...)
{
	Scene* s = (Scene*)malloc(sizeof(Scene));
	if (!s)
		return NULL;
	if (L_init(&s->lst) == False)
	{
		free(s);
		return NULL;
	}

	NODE* ptr = &s->lst.head;
	va_list allNames;
	char* currentName;

	va_start(allNames, fileName);
	currentName = fileName;
	while (currentName)
	{
		ptr = L_insert(ptr, createObject(currentName));
		currentName = va_arg(allNames, char*);
		int num;
	}

	va_end(allNames);
	return s;
}

void perform(Scene* s, void (*funcPtr)(Object*, void*), char* type, char* line)
{
	NODE* ptr = s->lst.head.next;
	void* res = createVar(type);
    
	
	while (ptr)
	{
		funcPtr(ptr->key, res);
		ptr = ptr->next;
		
	}
	printRes(line, type, res);
}

void printRes(char* line, char* type, void* res)
{
	char* in = "INT";
	char* db = "DOUBLE";
	char* s = "STR";
   
	if (strcmp(type, in) == 0) 
		printf("%s %d\n", line, *(int*)res);
	
	else if (strcmp(type, db) == 0)
		printf("%s %lf\n", line, *(double*)res);
	else if (strcmp(type, s) == 0)
		printf("%s %s\n", line, (char*)res);
	else
		printf("%s %c\n", line, *(char*)res);
}

void* createVar(char* type)
{
	char* in = "INT";
	char* db = "DOUBLE";
	char* s = "STR";
	void* res;

	if (strcmp(type, in) == 0)
	{
		res = calloc(1,sizeof(int));
		return res;
	}
	else if (strcmp(type, db) == 0)
	{
		res = calloc(1,sizeof(double));
		return res;
	}
		
	else if (strcmp(type, s) == 0)
	{
		res = malloc(sizeof(char) * 128);
		return res;
	}
		
	else
	{
		res = malloc(sizeof(char));
		return res;
	}
		
}

void saveScene(Scene* scene, char* fileName, enum FileType type)
{
	if (scene == NULL)
		return;
	if (type == 0)
		saveSceneToText(scene, fileName);
	else
		saveSceneToBin(scene, fileName);
}

void saveSceneToBin(Scene* s, char* fileName)
{
	int numOfObjects = 0;
	FILE* f = fopen(fileName, "wb");
	if (!f)
		return;
	
	NODE* ptr = s->lst.head.next;

	while (ptr)
	{
		numOfObjects++;
		ptr = ptr->next;
	}

	ptr = s->lst.head.next;
	fwrite(&numOfObjects, sizeof(int), 1, f);
	while (ptr)
	{
		printObjToBin(ptr->key, f);
		ptr = ptr->next;
	}
	fclose(f);
}

void saveSceneToText(Scene* s, char* fileName)
{
	if (!s->lst.head.next)
		return;
	NODE* ptr = s->lst.head.next;
	FILE* f = fopen(fileName, "w");
	
	while (ptr)
	{
		printObjToFile(ptr->key, f);
		ptr = ptr->next;
	}
	
	fclose(f);
}

Scene* loadScene(char* fileName, enum FileType type)
{
	Scene* s;
	if (type == 0)
		s = loadSceneFromText(fileName);
	else
		s = loadSceneFromBin(fileName);

}

Scene* loadSceneFromBin(char* fileName)
{
	Scene* s = (Scene*)malloc(sizeof(Scene));
	if (!s)
		return NULL;

	if (L_init(&s->lst) == False)
	{
		free(s);
		return NULL;
	}

	FILE* f = fopen(fileName, "rb");
	if (!f) {
		free(s);
		return NULL;
	}
    
	int numOfObjects;
	fread(&numOfObjects, sizeof(int), 1, f);
	NODE* ptr = &s->lst.head;
	for (int i = 0; i < numOfObjects; i++)
		ptr = L_insert(ptr, loadObjFromBin(f));

	return s;
	
		
}


Scene* loadSceneFromText(char* fileName)
{
	Scene* s = (Scene*)malloc(sizeof(Scene));
	char line[300];
	if (!s)
		return NULL;
	FILE* f = fopen(fileName, "r");
	if (!f)
	{
		free(s);
		return NULL;
	}

	if (L_init(&s->lst) == False)
	{
		free(s);
		fclose(f);
		return NULL;
	}

	NODE* ptr = &s->lst.head;
		while (fgets(line, 300, f))
		{
			fseek(f, -1, SEEK_CUR); // to make sure we dont read important line
			Object* o = (Object*)malloc(sizeof(Object));
			if (!initObjectProps(o))
			{
				free(s);
				free(o);
				fclose(f);
				return NULL;
			}
			initFacesAndVerts(f, o, line);
			ptr = L_insert(ptr, o);
		}
	fclose(f);
	return s;
}