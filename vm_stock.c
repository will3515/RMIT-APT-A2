/**
 * File: vm_stock.c
 * Author: William Cohen
 * Student no.: s3660470
 * Course: Advanced Programming Techniques
 * Year: 2017
 **/
#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

/* Creates a list and returns the pointer */
List * createList() {
    List * list = malloc(sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;
}

/* Creates a new node in a safe state */
Node * createNode() {
    Node * node = malloc(sizeof(Node));
    node->data = NULL;
    node->next = NULL;

    return node;
}

/* Adds a new item into the item linked list */
Boolean listAdd(List * list, Stock * item) {

    Node * current = list->head;
    Node * previous = NULL;
    Node * new = createNode(); 

    switch(list->size) {
        case 0:
            /* Empty List */
            list->head = new;
            if (list->head == NULL) return FALSE; /* Something went wrong */
            list->head->data = item;
            list->head->next = NULL;
            break;
        case 1:
            /* Only the head makes up the list */
            if (strcmp(item->name, current->data->name) > 0) {
                /* Append to end of list */	
                current->next = new;
                new->data = item;
                new->next = NULL;
            } else {
                /* Append to beginning */
                list->head = new;
                new->data = item;
                new->next = current;
            }
            break;
        default:
            /* Add in the middle somewhere */
            while (current->next != NULL) {
                if (strcmp(item->name, current->data->name) < 0) {
                    break;
                }
                previous = current;
                current = current->next;
            }
            previous->next = new;
            new->next = current;
            new->data = item;
            break;
    }
    list->size++;
    return TRUE;

}

/* Remove item from linked list by ID */
Boolean listRemove(List * list, const char * id) { 

    Node * current = NULL;
    Node * previous = NULL;

    current = list->head;
    while (current != NULL && (strcmp(current->data->id,id) != 0)) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return FALSE;

    if (previous == NULL) {
        list->head = current->next; 
    } else {
        previous->next = current->next;	
    }

    list->size--;

    free(current->data);
    free(current);

    return TRUE; 
} 
/* Return a pointer to the item with specified ID
 * Or return NULL if no such item was found */
Node * getItemWithId(List * list, const char * id) {
    Node * item;
    item = list->head;
    while (item != NULL && (strcmp(item->data->id,id) != 0)) {
        item = item->next;
    }
    return item;

}

/* Frees any dynamic memory for the linked list */
void freeList(List * list) {
    Node * current = list->head;
    Node * temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(list);
}

/* Prints all the item details in the list */
void printList(List * list) {
    Node * current = list->head;
    int idWidth=strlen("ID"), nameWidth=strlen("Name"), stockWidth=strlen("Available");
    int temp;
    while(current != NULL) {
        temp = strlen(current->data->id);
        idWidth = (idWidth > temp ? idWidth : temp); 

        temp = strlen(current->data->name);
        nameWidth = (nameWidth > temp ? nameWidth : temp);  

        temp = (int) countDigits(current->data->onHand);
        stockWidth = (stockWidth > temp ? stockWidth : temp);  

        current = current->next;
    } 

    current = list->head;

    printf("Items Menu\n\n");

    printf("%-*s | %-*s | %-*s | %s\n", 
            idWidth,"ID",
            nameWidth,"Name",
            stockWidth,"Available",
            "Price");
    printf("--------------------------------------------------\n");

    while (current != NULL) {
        printf("%-*s | %-*s | %-*u | $ %u.%02u\n", 
                idWidth,current->data->id,
                nameWidth,current->data->name,
                stockWidth,current->data->onHand,
                current->data->price.dollars,
                current->data->price.cents);
        current = current->next;
    }
    printf("\n");
}

