from cs50 import get_float

quarter = 25
dime = 10
nickel = 5
penny = 1
coins = 0
remain = 0

while True:
    n = get_float("Change owed: ")
    if n > 0:
        break
    
cents = round(n * 100)

if cents >= 25:
    remain = cents % quarter
    temp = cents - remain
    coins = temp / quarter
    cents = remain
    
if cents >= 10:
    remain = cents % dime
    temp = cents - remain
    coins += temp / dime
    cents = remain

if cents >= 5:
    remain = cents % nickel
    temp = cents - remain
    coins += temp / nickel
    cents = remain
    
if cents >= 1:
    remain = cents % penny
    temp = cents - remain
    coins += temp / penny
    cents = remain
    
print(int(coins))
    
    
    

    

    
    
    