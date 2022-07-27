#include "datastructures.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void testHashTable(){
    HashTable* table = createTable(CAPACITY);
    htInsert(table, "0", "zeroth address");
    htInsert(table, "1", "First address");
    htInsert(table, "2", "Second address");
    htInsert(table, "Hel", "Third address");
    htInsert(table, "Cau", "Fourth address");
    printSearch(table, "1");
    printSearch(table, "2");
    printSearch(table, "3");
    printSearch(table, "Hel");
    printSearch(table, "Cau");  // Collision!
    printTable(table);
    htDelete(table, "1");
    htDelete(table, "2");
    htDelete(table, "Cau");
    printTable(table);
    freeTable(table);

    printf("here\n");
}

int main(int argc, char **argv){

    testHashTable();

    return 0;
}