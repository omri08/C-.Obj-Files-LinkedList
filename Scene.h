#pragma once
#include "list.h"
#include "Object.h"
typedef struct {

	LIST lst;

} Scene;

enum FileType { TextFormat, BinaryFormat };

Scene* createScene(char* fileName, ...);
void printRes(char* line, char* type, void* res);
void perform(Scene* s, void (*funcPtr)(Object*, void*), char* type, char* line);
void* createVar(char* type);
void saveScene(Scene* scene, char* fileName, enum FileType type);
void saveSceneToBin(Scene* s, char* fileName);
void saveSceneToText(Scene* s, char* fileName);
Scene* loadScene(char* fileName, enum FileType type);
Scene* loadSceneFromBin(char* fileName);
Scene* loadSceneFromText(char* fileName);
void freeScene(Scene* scene);

