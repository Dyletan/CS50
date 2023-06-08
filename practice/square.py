from math import sqrt

def square(x):
    print(f"Perimetr: {x * 4}" )
    print(f"Ploshad: {x ** 2}")
    print(f"Diagonal: {round(sqrt(2 * x ** 2), 3)}")
    
x = int(input("Side of square: "))

square(x)
   