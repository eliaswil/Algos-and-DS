#ifndef DATA_STRUCTURES_DOT_H
#define DATA_STRUCTURES_DOT_H


#define CAPACITY 5000 // size of the hash table

typedef struct HtItem HtItem;
typedef struct HashTable HashTable;
typedef struct LinkedList LinkedList;
 
struct HtItem{
    char *key;
    char *value;
};

// Define the Linkedlist here
struct LinkedList {
    HtItem* item; 
    LinkedList* next;
};

struct HashTable{
    HtItem **items; // array of pointers
    LinkedList **overflowBuckets;
    int size;
    int count;
};



unsigned long hashFunction(char* str);


HtItem* createItem(char* key, char* value);
LinkedList** createOverflowbuckets(HashTable *table);
HashTable* createTable(int size);
void freeItem(HtItem* item);
void freeOverflowBuckets(HashTable* table);
void freeTable(HashTable* table);
void handleCollision(HashTable* table, unsigned long index, HtItem* item);
void htInsert(HashTable *table, char *key, char *value);
char* htSearch(HashTable *table, char *key);
void htDelete(HashTable *table, char *key);
void printTable(HashTable* table);
void printSearch(HashTable* table, char* key);

LinkedList* allocateList ();
LinkedList* linkedlistInsert(LinkedList* list, HtItem* item);
HtItem* linkedlistRemove(LinkedList* list);
void freeLinkedlist(LinkedList* list);



#endif

