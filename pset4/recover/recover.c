#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#define BLOCK 512//задаем размер блока как 512 байт
#define FILE_NAME_SIZE 8//задаем размер имени файла как 8 байтов

typedef uint8_t BYTE;//новый вид информации хранящий байт информации
bool found_jpg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    //ТОЛЬКО 2 слова к промпте
    if (argc != 2)
    {
        printf("Poshel v jeby\n");
        return 1;
    }
    //открываем данный нам пользователе файл
    FILE *infile = fopen(argv[1], "r");
    //если данного файла нет то ошибка
    if (infile == NULL)
    {
        printf("Watch what you are typing");
        return 2;
    }
    //выделяем буферу 512 байтов
    BYTE buffer[BLOCK];
    //переменная горящая нашли ли мы уже файл жпг или еще нет
    bool found_first_jpg = false;
    FILE *outfile;
    int counter = 0;
    //пока возможно чтение будем выполнять следующее
    while (fread(buffer, BLOCK, 1, infile))
    {
        //если нашли начало жпг то делаем следующее
        if (found_jpg(buffer))
        {
            //если жпг еще не был обнаружен до этого то ставим пометку, что нашли его
            if (!found_first_jpg)
            {
                found_first_jpg = true;
            }
            //если он был до этого обнаружен то закрываем файл
            else
            {
                fclose(outfile);
            }
            char filename[FILE_NAME_SIZE];//в нем будет хранится имя жпг
            sprintf(filename, "%03i.jpg", counter);//присваиваем имя этой жпг
            counter++;
            outfile = fopen(filename, "w");//открываем жпг
            fwrite(buffer, BLOCK, 1, outfile);//записываем в него все что находится в буфере
        }
        //если жпг уже был обнаружен, то продолжаем его заполнение
        else if (found_first_jpg)
        {
            fwrite(buffer, BLOCK, 1, outfile);
        }

    }
    fclose(outfile);
    fclose(infile);
}
//функция для нахождения начала файла жпг
bool found_jpg(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}