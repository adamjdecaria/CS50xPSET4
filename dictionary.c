/*
*
*   CS50x 2019
*   Problem Set 4 -> dictionary.c
*
*   Implements a dictionary's functionality using a hash table
*
*   Adam DeCaria
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Count of words added to the dictionary
int dictionary_count= 0;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // create a "head" of the linked list, and set its next value to NULL
    node *head = malloc(sizeof(node));

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(new_node->word, word);
            int table_position = hash(new_node->word);
            head = hashtable[table_position];
            new_node->next = head;
            head = new_node;
            dictionary_count++;
        }
    }

    free(head);

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *head = malloc(sizeof(node));
    head = hashtable[hash(word)];

    node *cursor = head;

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    free(head);

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *head = malloc(sizeof(node));

    for (int i = 0; i < N; i++)
    {
        head = hashtable[i];
        node *cursor = head;

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    free(head);

    return true;
}
