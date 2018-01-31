/**
 * File: vm_stock.h
 * Author: William Cohen
 * Student no.: s3660470
 * Course: Advanced Programming Techniques
 * Year: 2017
 **/
#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"


/* Returns a pointer to a list in a safe state */
List * createList();


/* Creates an empty node */
Node * createNode();

/* Frees memory allocated to node */
void freeNode(Node * node);

/* Adds a new item into the item linked list */
Boolean listAdd(List * list, Stock * item); 

/* Remove item from linked list by ID */
Boolean listRemove(List * list, const char * id);

/* Returns a pointer to the item with specified ID */
Node * getItemWithId(List * list, const char * id);

/* Frees any dynamic memory for the linked list */
void freeList(List * list);

/* Prints all the items in the list */
void printList(List * list);

#endif
