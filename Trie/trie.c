#include <stdio.h>
#include <math.h>

typedef struct TrieNode TrieNode;

struct TrieNode{

    char key;
    
    /**
     * @brief e.g. end of word / binary number
     * ---
     * 0 ... is the end
     * 1 ... is not the end
     */
    unsigned int end:1; 

    /**
     * @brief the total number of all descendants
     */
    unsigned int totalChildren;

    /**
     * @brief 
     * 
     */
    TrieNode *children[26];
    TrieNode *parent;

};

void insertWord(TrieNode *parent, char **word){
    TrieNode *current = parent;


}




int main(int argc, char **argv){
    printf("This is a trie !!!!\n");
    
    TrieNode aTrie;
    TrieNode aChild;
    aChild.end = 1;
    aTrie.totalChildren = 1;
    aTrie.children[0] = &aChild;

    printf("child: %d\n", aTrie.children[0]->end);
    
    return 0;
}