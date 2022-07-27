/**
 * Based on this tutorial: https://www.journaldev.com/35238/hash-table-in-c-plus-plus
 * 
 */


#include "datastructures.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**
 * @brief a hash function that sums up the ascii value of a string
 * 
 * @param str 
 * @return unsigned long 
 */
unsigned long hashFunction(char* str){
    unsigned long i = 0;
    for(int j=0; str[j]; j++){
        i += str[j];
    }
    return i % CAPACITY;
}

/**
 * @brief Creates a pointer to a new hash table item
 * 
 * @param key 
 * @param value 
 * @return Ht_item* 
 */
HtItem* createItem(char* key, char* value) {
    HtItem* item = (HtItem*) malloc (sizeof(HtItem));
    item->key = (char*) malloc (strlen(key) + 1);
    item->value = (char*) malloc (strlen(value) + 1);
     
    strcpy(item->key, key);
    strcpy(item->value, value);
 
    return item;
}

/**
 * @brief create overflow buckets
 * 
 * @param table the hash table
 * @return LinkedList** the buckets
 */
LinkedList** createOverflowbuckets(HashTable *table){
    LinkedList **buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    for(int i=0; i < table->size; i++){
        buckets[i] = NULL;
    }
    return buckets;
}


/**
 * @brief Create a new hash table; an array of linked lists
 * 
 * @param size 
 * @return HashTable* 
 */
HashTable* createTable(int size){
    HashTable *table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (HtItem**) calloc (table->size, sizeof(HtItem*));

    for (int i=0; i < table->size; i++)
        table->items[i] = NULL;
    
    table->overflowBuckets = createOverflowbuckets(table);

    return table;
    
}

/**
 * @brief frees an item
 * 
 * @param item 
 */
void freeItem(HtItem* item) {
    free(item->key);
    free(item->value);
    free(item);
    item = NULL;
}

/**
 * @brief frees all the overflow bucket lists
 * 
 * @param table 
 */
void freeOverflowBuckets(HashTable* table){
    LinkedList **buckets = table->overflowBuckets;
    for(int i=0; i < table->size; i++){
        freeLinkedlist(buckets[i]);
    }
    free(buckets);
    buckets = NULL;
}
 
/**
 * @brief frees the table
 * 
 * @param table 
 */
void freeTable(HashTable* table) {
    for (int i=0; i < table->size; i++) {
        HtItem* item = table->items[i];
        if (item != NULL)
            freeItem(item);
    }

    freeOverflowBuckets(table);
    free(table->items);
    free(table);
    table = NULL;
}



// insert


/**
 * @brief takes care of collisions
 * 
 * @param table 
 * @param index 
 * @param item 
 */
void handleCollision(HashTable* table, unsigned long index, HtItem* item) {
    LinkedList *head = table->overflowBuckets[index];

    if(head == NULL){
        // create the list
        head = allocateList();
        head->item = item; 
        head->next = NULL;
        table->overflowBuckets[index] = head;
    }else{
        // insert into the list
        table->overflowBuckets[index] = linkedlistInsert(head, item);
    }
}


/**
 * @brief inserts an item into the hash table
 * 
 * @param table the hash table
 * @param key the key of the item
 * @param value the value of the item
 */
void htInsert(HashTable *table, char *key, char *value){
    // create item
    HtItem *item = createItem(key, value);
    
    // compute the index
    unsigned long index = hashFunction(key);

    HtItem *currentItem = table->items[index];
    if(currentItem == NULL){
        // key does not exist
        if(table->count == table->size){
            // hash table full
            printf("Insert Error: Hash Table is full\n");
            freeItem(item);
            return;
        }

        // Insert directly
        table->items[index] = item;
        table->count++;
    }else{
        // Scenario 1: We only need to update value (key is the same)
        if(strcmp(currentItem->key, key) == 0){
            strcpy(table->items[index]->value, value);
            return;
        }else{
            // Scenario 2: Collision
            handleCollision(table, index, item);
            return;
        }
    }
}

/**
 * @brief searches for an item by checking if the key exists.
 * If it does exist, the corresponding value will be returned.
 * 
 * @param table the hash table
 * @param key the key of the item
 * @return char* the value of the item or NULL
 */
char* htSearch(HashTable *table, char *key){
    int index = hashFunction(key);
    HtItem *item = table->items[index];
    LinkedList *head = table->overflowBuckets[index];

    while(item != NULL){
        if (strcmp(item->key, key) == 0){
            return item->value;
        }
        if(head == NULL){
            return NULL;
        }
        item = head->item;
        head = head->next;
    }
    return NULL;
}


// delete


void htDelete(HashTable *table, char *key){
    int index = hashFunction(key);
    HtItem *item = table->items[index];
    LinkedList *head = table->overflowBuckets[index];

    if(item == NULL){
        // does not exist
        return;
    }else{
        if(head == NULL && strcmp(item->key, key) == 0){

            // no collision chain
            table->items[index] == NULL;

            freeItem(item);
            table->count--;
            return;

        }else if(head != NULL){
            // collision chain exists
            if(strcmp(item->key, key) == 0){
                
                // remove this item (at the front of the list) 
                // and set the head of the list as the new item
                
                freeItem(item);
                LinkedList *node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = createItem(node->item->key, node->item->value);
                freeLinkedlist(node);
                table->overflowBuckets[index] = head;

                return;
            }


            LinkedList *curr = head;
            LinkedList *prev = NULL;

            while(curr){
                if(strcmp(curr->item->key, key) == 0){
                    if(prev == NULL){
                        // first element of the chain. Remove the chain
                        freeLinkedlist(head);
                        table->overflowBuckets[index] = NULL;
                        return;
                    }else{
                        // ... somewhere in the chain...
                        prev->next = curr->next;
                        curr->next = NULL;
                        freeLinkedlist(curr);
                        table->overflowBuckets[index] = head;
                        return;
                    }
                }
                curr = curr->next;
                prev = curr;
            }
        }
    }
}






/**
 * @brief prints the entire hash table
 * 
 * @param table the hash table
 */
void printTable(HashTable* table) {
    printf("\n------- HashTable ------------\n");
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s", i, table->items[i]->key, table->items[i]->value);
            if (table->overflowBuckets[i]) {
                printf(" => Overflow Bucket => ");
                LinkedList* head = table->overflowBuckets[i];
                while (head) {
                    printf("Key:%s, Value:%s ", head->item->key, head->item->value);
                    head = head->next;
                }
            }
            printf("\n");
        }
    }
    printf("---------- End ---------------\n");
}



void printSearch(HashTable* table, char* key) {
    char* val;
    if ((val = htSearch(table, key)) == NULL) {
        printf("%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}



