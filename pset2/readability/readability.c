//программа по определению уровня сложности текста 
//формуда, исользуемая для определения сложности index = 0.0588 * L - 0.296 * S - 15.8
//где L - это среднее число букв на 100 слов, а S - среднее число предложений на 100 слов 
//программа должна считать колво слов, букв и предложений. Буквы в пределе a-z и A-Z, буквы разделенные пробелом - это слова,
//а в каждом месте, где используется . ! или ? - конец предложения
//в конце программа пишет Grade ? который округлен 
//если уровень больше 16 нужно писать Grade 16+ если он меньше 1, то Before Grade 1

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    //запрос текста у пользователя
    string text = get_string("Text: ");
    //декларация переменных
    float len = strlen(text);//колво символов
    float let = 0;//колво букв
    float words = 1;//колво слов
    float sent = 0;//колво преложений
   
    for (int i = 0; i<len; i++)
    {
        //считает колво букв
        if ((text[i]>= 'a' && text[i]<='z') || (text[i]>= 'A' && text[i]<='Z'))
        {
            let++;
        }
        //считает колво слов
        else if (text[i] == ' ')
        {
            words++;
        }
        //считает колво предложений
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sent++;
        }
    }
    //составляем формулу определения сложности текста
    float L = (let * 100) / words;
    float S = (sent * 100) / words;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
   
    if (index < 17 && index > 1)
    {
    printf("Grade %i\n", index);
    }
   
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    
    else
    {
        printf("Before Grade 1\n");
    }
    
}

 
 