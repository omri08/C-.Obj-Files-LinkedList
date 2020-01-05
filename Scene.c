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
		printRes(line, type, res);
		ptr = ptr->next;
	}
}

void printRes(char* line, char* type, void* res)
{
	char* in = "INT";
	char* db = "DOUBLE";
	char* s = "STR";
   
	if (strcmp(type, in) == 0) 
		printf("%s %d\n", line, *(int*)res);
	
	else if (strcmp(type, db) == 0)
		printf("%s %f\n", line, *(float*)res);
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
		res = malloc(sizeof(int));
		return res;
	}
	else if (strcmp(type, db) == 0)
	{
		res = malloc(sizeof(double));
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
	FILE* f = fopen(fileName, "wb");
	if (!f)
		return;
	fwrite(s, sizeof(Scene), 1, f);
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