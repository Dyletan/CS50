#include <stdio.h>
#include <cs50.h>
#include <math.h>

 //все виды монеток
 int const quarter = 25;
 int const dime = 10;
 int const nickel = 5;
 int const penny = 1;

int main(void)
{
    float i; //сумма в долларах
    //запрос у пользователя кол-ва сдачи
    do
    {
      i = get_float("Change owed: ");
    }
    while (i<=0);
    //программа для отслеживания использованных монет
    //программа для вычисления мин нужного колва монет

   int cents = round(i * 100);//сумма в цетнах
   int coins = 0;//колво использованных монеток
   int remain = 0;//остаток
   int tempNum;//колво задействованных центов

   

   //считает колво четвертаков
   if (cents >= quarter)
  {
      remain = cents % quarter;//вычисляем остаток
      tempNum = cents - remain;//выясняем сколько центов было задйствованно 
      coins = tempNum / quarter;//колво потраченных монет
      cents = remain;//колво оставшихся центов
  }

   //считает колво десяток
   if (cents >= dime)
  {
      remain = cents % dime;
      tempNum = cents - remain;
      coins = coins + (tempNum / dime);//приплюсовываем колво монет, потраченных в прошлом к нынешним тратам
      cents = remain;
  }
   //считает колво пятяков
   if (cents >= nickel)
  {
      remain = cents % nickel;
      tempNum = cents - remain;
      coins = coins + (tempNum / nickel);
      cents = remain;
  }
   //считает колво пенни
   if (cents >= penny)
  {
      remain = cents % penny;
      tempNum = cents - remain;
      coins = coins + (tempNum / penny);
      cents = remain;
  }

//выводит колво монет
 {
     printf ("%i\n", coins);
 }

}

 