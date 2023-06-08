from cs50 import get_int
from sys import exit

while True:
    cc = get_int("Credit card number: ")
    if cc >= 0:
        break
count = 0

ccNum = cc

while cc >= 1:
    cc = cc / 10
    count += 1

if (count != 13 and count != 15 and count != 16):
    print("INVALID")
    exit(1)

sum1 = 0
sum2 = 0

for i in range(count):
    factor = 10 ** i
    if i % 2 == 0:
         digit = int((ccNum / factor) % 10)
         sum1 += int(digit)
    else:
        digit = int((int(ccNum) / factor) % 10)
        multi = int(digit) * 2

        if multi > 9: #разбивает двузначное число на два однозначных
            num1 = int(multi) % 10
            num2 = int(int(multi) / 10)
            multi = num1 + num2

        sum2 += int(multi)

# Define which card type
test = int(ccNum / (10 ** (count - 2)))
if count == 16 and int(test / 10) == 4:
    card = "VISA"

elif count == 16 and test >= 51 and test <= 55:
    card = "MASTERCARD"

elif count == 15 and (test == 34 or test == 37):
    card = "AMEX"

else:
    card = "INVALID"

result = sum1 + sum2
  #Final verification
if result % 10 == 0:
    print(card)

else:
    print("INVALID")




