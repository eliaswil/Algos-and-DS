#include "datastructures.h"
#include <stdlib.h>
#include <string.h>

 
LinkedList* allocateList () {
    // Allocates memory for a Linkedlist pointer
    LinkedList* list = (LinkedList*) malloc (sizeof(LinkedList));
    return list;
}
 
LinkedList* linkedlistInsert(LinkedList* list, HtItem* item) {
    // Inserts the item onto the Linked List
    if (!list) {
        LinkedList* head = allocateList();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } 
     
    else if (list->next == NULL) {
        LinkedList* node = allocateList();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }
 
    LinkedList* temp = list;
    while (temp->next->next) {
        temp = temp->next;
    }
     
    LinkedList* node = allocateList();
    node->item = item;
    node->next = NULL;
    temp->next = node;
     
    return list;
}
 
HtItem* linkedlistRemove(LinkedList* list) {
    // Removes the head from the linked list
    // and returns the item of the popped element
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    HtItem* it = NULL;
    memcpy(temp->item, it, sizeof(HtItem));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}
 
void freeLinkedlist(LinkedList* list) {
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}