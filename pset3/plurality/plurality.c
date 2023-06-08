#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define MAX 9//установить, что МАХ равен 9
//функции
bool vote(string name);
void print_winner(void);
//вид данных, хранящий имя кандидата и колво его голосов
typedef struct
{
    string name;
    int  votes;
}
candidate;
//список кандидатов, не более 9
candidate candidates[MAX];

int candidate_count;//колво кондидатов в данных выборах

int main(int argc, string argv[])
{
    //колво кандитатов не более 9 и не менее 1
    if (argc > MAX || argc < 2)
    {
        printf("Usage: ./plurality [candidate ... ]\n");
        return false;
    }
    //определяем колво кандидатов
    candidate_count = argc - 1;
    //выдаем ошибку если их более 9
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return false;
    }
    //присваиваем имена и колво голосов списку candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }
    //колво голосующих
    int voter_count = get_int("Number of voters: ");
    //запрашиваем у голосующих их голос
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        //если такого кандидата нет, то шлем нахер
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    //выводи имя победителя
    print_winner();
    
}
//функция для определения колва голосов каждого кандидата
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
       if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
        
    }
    return false;
}
//Функция для определения кто победитель выборов
void print_winner(void)
{
    int most = 0;
    string winner;

    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes > most - 1)
        {
            most = candidates[i].votes;
            winner = candidates[i].name;
            printf("%s\n", winner);
        }
        
        else if (candidates[i].votes == most)
        {
            printf("%s\n", winner);
            printf("%s\n", candidates[i].name);
        }
    }
    
}