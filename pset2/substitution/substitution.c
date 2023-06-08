//программа по шифровке с помощью алфавита заменителя
//получаем алфавит заменитель
//он должен быть только из букв в колве 26 букв
//запрашиваем текст который будет шифроваться
//применяем алфавит заменитель
//выводим зашифрованный текст

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 
bool is_valid_key(string s);//проверщик правильности ключа
 
int main(int argc, string argv[])
{
//если в командной строке не два значения, то выдается ошибка
if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //выдается совет, если ключ состоит не из 26 неповторяющихся букв
    if (!is_valid_key(argv[1]))
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    
    //запрос текста для шифровки 
    string s = get_string("plaintext: ");
    
    string diff = argv[1];//строка алфавита-шифровщика
    //определяем разницу между буквами
    for (int i = 'A'; i <= 'Z'; i++)
    {
        diff[i - 'A'] = toupper(diff[i - 'A']) - i;
    }
    //вывод зашифрованного текста
    printf("ciphertext: ");
    //заменяем буквы на шифратор
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isalpha(s[i]))
            s[i] = s[i] + diff[s[i] - (isupper(s[i]) ? 'A' : 'a')];
        printf("%c", s[i]);
        
        
    }
    printf("\n");
}

//функция по определению правильности ключа-шифратора    
bool is_valid_key(string s)
{
    int len = strlen(s);
    //если букв не 26 то шлем нахер
    if (len != 26)
    {
        return false;
    }
   
    int freq[26] = { 0 };
    
    for (int i = 0; i < len; i++)
    {   //если не буквы, то шдем нахер
        if (!isalpha(s[i]))
        {
            return false;
        }
         
        int index = toupper(s[i]) - 'A';
        //если буква повторилась дважды, то шлем нахер
        if (freq[index] > 0)
        {
            return false;
           
        } 
        freq[index]++;
    }
    return true;
}
   