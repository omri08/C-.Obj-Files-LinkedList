#define _CRT_SECURE_NO_WARNINGS
#include "Scene.h"
void main()
{
	Scene* scene = createScene("GoingMerry.obj", "Donald.obj", "Pony_cartoon.obj", NULL);
	// Print out all Vertexes
	perform(scene, printVertexes, "INT","The number of vertexes of all objects is");

	// Count the number of all Triangular faces of all objects in Scene 
	perform(scene, printFaces, "INT", "The number of Triangular faces of all objects is");

	// Count the total area of all Triangular faces of all objects in Scene 
	perform(scene, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");
	saveScene(scene, "s.txt", BinaryFormat);

	Scene* s1 = loadScene("s.txt", BinaryFormat);
	printf("-----------\n");
	// Print out all Vertexes
	perform(s1, printVertexes, "INT", "The number of vertexes of all objects is");

	// Count the number of all Triangular faces of all objects in Scene 
	perform(s1, printFaces, "INT", "The number of Triangular faces of all objects is");

	// Count the total area of all Triangular faces of all objects in Scene 
	perform(s1, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");
	

	
}