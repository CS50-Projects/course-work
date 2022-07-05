// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Word counter
int wordCounter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashPosition = hash(word);

    node *cursor = table[hashPosition];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }

        cursor = cursor -> next;
    }

    return false;
}

// Hash function modified from: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *str)
{
    unsigned long hash = 5381;
    int c = 0;

    while (c == *str++)
    {
        hash = ((hash << 5) + hash) + c;    /* hash * 33 + c */
    }

    hash = tolower(hash);

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens dictionary file
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    // Sets a string variable
    char buffer[LENGTH + 1];

    // Scan each string of the dictionary file
    while (fscanf(input, "%s", buffer) != EOF)
    {

        // Add one to word counter
        wordCounter += 1;

        // Allocate memory for each word read from the dictionary
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        };

        // Create node
        strcpy(n -> word, buffer);
        n -> next = NULL;

        // Find the hash position of each word using the hash function
        int hashPosition = hash(buffer);

        // Check if list empty, if it is, have the hash table point to it.
        if (table[hashPosition] == NULL)
        {
            // Point the hash table to the new node
            table[hashPosition] = n;
        }
        else
        {
            // Set new variable equal to the head of old linked list
            node *prev = table[hashPosition];

            // Point the new node to the old head
            n -> next = prev;

            // Point the hash table to the new node, creating a new head
            table[hashPosition] = n;
        }
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;

            cursor = cursor -> next;
            free(tmp);
        }

        // If it makes it to the end
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }

    return false;
}
