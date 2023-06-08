// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
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
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int n = strlen(word);
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    word_copy[n] = '\0';
    int h = hash(word_copy);
    node *cursor = table[h];
    
    while (cursor != NULL)
    {
        // If strcasecmp returns true, then word has been found
        if (strcmp(cursor->word, word_copy) == 0)
        {
            return true;
        }
        // Else word has not yet been found, advance cursor
        else
        {
            cursor = cursor->next;
        }
    }
    // Cursor has reached end of list and word has not been found in dictionary so it must be misspelled
    return false;
}

//Hashes word to a number
//taken from: https://stackoverflow.com/questions/47546904/why-do-bit-shift-operators-make-my-hash-function-so-fast
unsigned int hash(const char *word)
{
    unsigned int index = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        index = (index << 2) ^ word[i];
    }
    return index % 10000;
}

unsigned int word_count = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open the dictionary
    FILE *file = fopen(dictionary, "r");
    //проверить есть ли файл
    if (file == NULL)
    {
        printf("Error, could not open the dictionary");
        return 1;
    }
    //read words from it one at a time
    char word[LENGTH + 1];//переменная для слова
    //пройтись через весь словарь
    while (fscanf(file, "%s", word) != EOF)
    {
        //создает ноуд для каждого отдельного слова
        node *new_node = malloc(sizeof(node));
        //если недосаточно памяти для маллок то ОШИБКА
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        //копируем и храним слово из ноуд в переменную word
        strcpy(new_node->word, word);
        //прохэшировать это слово используя хэш функцию чтобы получить его хэш значение
        int index = hash(word);
        //делает так чтобы node *head указывал на хэш-таблицу с соответствующим ей хэш-номером
        node *head = table[index];
        //если до этого не было подобной ячейки хэш-таблицы, то мы добавляем его в хэш-таблицу
        if (head == NULL)
        {
            table[index] = new_node;
            word_count++;
        }
        //если эта ячейка хэш-таблицы уже существует, то мы объединяем их в одну группу
        else
        {
            new_node->next = table[index];//мы сначала берем и присваиваем указателю new_node указатель к первому члену хэш-таблтицы
            table[index] = new_node;
            word_count++;
        }
    }
    fclose(file);
    return true;
    unload();
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 10000; i++)
    {
        free(table[10000-i]);
        return true;
    }
    return false;
}
