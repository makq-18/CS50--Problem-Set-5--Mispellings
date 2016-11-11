/**
 * dictionary.c
 *
 * Mohammed Qureshi
 * 
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// SIZE to define pointers
#define SIZE   26
// REDUCE to shift alphabets to zero index
#define REDUCE   97
// LENGTH for max size of word to read
#define LENGTH   45

typedef struct node
{
    // check will be true if word exists or else false.
    bool check;
    //26+1 pointers to read all alphabets and apostrophe '
    struct node* next[SIZE + 1];
}
node;

//dictionary size variable to calcualte no of words in dictionary
unsigned int dictionarySize = 0;
//new node to point first node as a root
struct node* new = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* last = NULL;
    last = new;
    // variable a to read a character from input file
    unsigned int a = 0;
    // variable i to read elements from input word
    int i = 0;
    a = tolower(word[i]);
    
    while(a != '\0')
    {
        a = tolower(word[i]);

        // as in speller.c, only allow alpha or apostrophe
        if((isalpha(a)) || (a == '\''))
        {
            // apostrophe is placed at the end of the next
            if(!isalpha(a))
            {
                 a = SIZE + REDUCE;
            }

            if(last->next[a - REDUCE] == NULL)
            {
                return false;
            }
            else
            {
                last = last->next[a - REDUCE];
            }
        }
        
        i++;
    }
    
    return last->check;
}

// function to create a new node
node* createNode(void)
{
    return (node*) malloc(sizeof(node));
}

// Loads dictionary into memory.  Returns true if successful else false.
 
bool load(const char* dictionary)
{
    // open input file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }
    // create first node
    new = createNode();
    // to read characters from input file
    unsigned int a = 0;
    //last node to traverse
    node* last = new;
    
    while(a != EOF)
    {
        a = fgetc(fp);
        if(a != '\n' && a != EOF)
        {
            if(a == '\'')
            {
                a = SIZE + REDUCE;  
            }

            if(last->next[a - REDUCE] == NULL)
            {
                last->next[a - REDUCE] = createNode();
            }
            last = last->next[a - REDUCE];
        }

        // set last pointer to node where new is pointing
        else if(a == '\n')
        {
            last->check = true;
            dictionarySize++;
            last = new;
        }
    }
    
    
    fclose(fp);
    
    return true;
}

// returns no of words in dictionary counted in above function
unsigned int size(void)
{
    return dictionarySize;
}

// unloads the dictionary pointers used in load function

void unloadNode(node* last)
{
    // traverse through each of the node which is not pointing to NULL
    for(int i = 0; i < SIZE; i++)
    {
        if(last->next[i] != NULL)
        {
            //using recursive function untill pointers are not pointing to NULL
            unloadNode(last->next[i]);
        }
    }
    
    // once the next nodes are freed, free this node
    free(last);
}

// unloads dictionary from memory using above functuon unloadNode

bool unload(void)
{
    unloadNode(new);
    return true;
}