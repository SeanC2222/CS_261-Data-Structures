#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
	lst->size = 0;
	lst->firstLink = malloc(sizeof(struct DLink));
	lst->firstLink->value = -1;
	lst->firstLink->prev = NULL;

	lst->lastLink = malloc(sizeof(struct DLink));
	lst->lastLink->value = -1;
	lst->lastLink->next = NULL;

	lst->firstLink->next = lst->lastLink;
	lst->lastLink->prev = lst->firstLink;

	return;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	struct DLink* temp;
	temp = malloc(sizeof(struct DLink));
	temp->value = v;
	temp->next = l;
	temp->prev = l->prev;
	l->prev->next = temp;
	l->prev = temp;
	return;

}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
	struct DLink* temp = malloc(sizeof(struct DLink));
	temp->value = e;
	temp->next = lst->firstLink->next;
	temp->prev = lst->firstLink;
	lst->firstLink->next = temp;
	return;
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {
  
	struct DLink* temp = malloc(sizeof(struct DLink));
	temp->value = e;
	temp->next = lst->lastLink;
	temp->prev = lst->lastLink->prev;
	lst->lastLink->prev = temp;
	return;

}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
	return lst->firstLink->next->value;
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	return lst->lastLink->prev->value;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{
	struct DLink* temp;
	temp = l->next;
	temp->prev->prev->next = temp;
	temp->prev = temp->prev->prev;
	free(l);
	return;
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
   	_removeLink(lst, lst->firstLink->next);
   	return;
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{	
	_removeLink(lst, lst->lastLink->prev);
	
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
 	if (lst->size == 0){
 		return 1;
 	}
 	return 0;
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	struct DLink* temp;
	temp = lst->firstLink;
	for (int i = 0; i < lst->size; i++){
		temp = temp->next;
		printf("%i\n", temp->value);
	}
	return;
}

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
	_addLinkBefore(lst, lst->lastLink, v);
	return;
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
	struct DLink* temp;
	temp = lst->firstLink;

	while(temp != lst->lastLink){
		if (temp->value == e){
			return 1;
		}
		temp = temp->next;
	}
	return 0;

}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
	struct DLink* temp;
	temp = lst->firstLink;

	while(temp != lst->lastLink){
		if (temp->value == e){
			_removeLink(lst, temp);
			return;
		}
	}
	return;
}
