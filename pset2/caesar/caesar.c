//программа по шифровке
//запрашиваем ключ у пользователя
//получаем незашифрованный текст
//зашифровываем применяя ключ
//выводим зашифрованный текст

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
    
bool is_valid_key(string s);

int main(int argc, string argv[])
{
    //чтобы в коммандной строке не было больше 2 значениц 
    if (argc != 2 || !is_valid_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
   
    //если 1 значение, то заебца
    else if (argc == 2 && isdigit(*argv[1]))
    {
        printf("Success\n");
    }
    
    int k = atoi(argv[1]);//перевод аргв в цифру
    
    //если цифра отрицательная, шлем нахер
    if (k < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    //шифратор 
    else
    {
        //запрашиваем текст который нужно зашифровать
        string plain = get_string("Plaintext: ");
        
        printf("ciphertext: ");
        //луп для шифровки 
        for (int i = 0, n = strlen(plain); i < n; i++)
            {
                //маленькие букавки шифруются
                if islower(plain[i])
                {
                    printf("%c", (((plain[i] + k) - 97) % 26) + 97);
                }
                
                else if isupper(plain[i])
                {
                    printf("%c", (((plain[i] + k) - 65) % 26) + 65);
                }
                //if neither then just print whatever it is
            
                else
                    printf("%c", plain[i]);
            }
            printf("\n");
            return 0;
        
    }
}

 bool is_valid_key(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        char ch = s[i];
        if (!isdigit(ch))
        {
            return false;
        }
    }
    return true;
}