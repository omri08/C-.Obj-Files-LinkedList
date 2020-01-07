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

BOOL L_delete(NODE* pNode, void (*freeKey)(void*));					// erase node after *pNode

BOOL L_free(LIST* pList, void (*freeKey)(void*));					// free list memory

