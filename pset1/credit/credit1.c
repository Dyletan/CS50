#include <stdio.h>
#include <cs50.h>
#include <math.h>

// MASTERCARD: 16-Digit #'s, Start with: 51, 52, 53, 54, or 55
// VISA: 13-16-Digit #'s, Start with: 4
// AMEX: 15-Digit #'s, Star with: 34 or 37

// Luhn's Algorithm:
// 1. Multiply every other digit by 2, starting with the second number to the last
// 2. Add the sum of those digits
// 3. Add the sum of the other digits
// 4. If the total sum ends with a 0, it is valid!

int main(void)
{
 int count = 0; // count - количество цифр в кредитной карте
 long cc; //cc - номер кредитки
 
//запрос номера кредитки
 do
 {
    cc = get_long("Credit card number: ");
 }
 while (cc<=0);
 
  //вычистление колва цифр в карте
  while (cc > 0) 
  {
        cc = cc / 10;
        count++;
  }
  //отсеивание неподходящих карт
  if (count != 13 && count != 15 && count != 16) 
    {
        printf("INVALID\n");
    } 
    
    long digit;
    int multi;
    int sum1 = 0;
    int sum2 = 0;
    int result;
    
    for (int i = 0; i < count; i++) 
  {
        // Create factor 
        long factor = pow(10, i);
    
    if (i % 2 == 0) //с помощь этого условия выходит брать цифры через одну
   {
    digit = (cc / factor) % 10;
    sum1 += digit;
   }
    
  else //взяты все другие числа,не вошедшие в прошлый луп
  {
      digit = (cc / factor) % 10;
      multi = digit * 2;
       
      if (multi > 9) //разбивает двузначное число на два однозначных
      {
        int num1 = multi % 10;
        int num2 = multi / 10;
        multi = num1 + num2;
      }
      sum2 += multi;
  }
  }

// Define which card type
string card;
int test = cc / pow(10, count - 2);
if (count == 16 && test / 10 == 4)
{
    card = "VISA";
}
else if ((count == 16) && test >= 51 && test <= 55)
{
    card = "MASTERCARD";
}
else if (count == 15 && (test == 34 || test == 37))
{
    card = "AMEX";
}
else
{
    card = "INVALID";
}

result = sum1 + sum2;
  // Final verification
  if (result % 10 == 0) 
  {
      printf("%s\n", card);
  }
  else 
  {
      printf("INVALID\n");
  }
  
}
