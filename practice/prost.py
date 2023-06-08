def prost(x):
    while x < 1000 and x > 0:
        for i in range(1, x):
            z = x / i
            if z % 1 == 0:
                print("Ne prostoe")
                
            else:
                print("Prostoe")
                return True
                
            
x = int(input("Number: "))

prost(x)
    