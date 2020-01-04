/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#pragma once

#include "def.h"


/*** Definitions ***/

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

BOOL L_delete(NODE* pNode);					// erase node after *pNode

NODE* L_find(NODE* pNode, DATA Value);		// return a pointer to the node 

BOOL L_free(LIST* pList);					// free list memory

int L_print(LIST* pList);					// print the list content

