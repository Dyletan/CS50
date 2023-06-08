def year_leap(x):
    if x % 4 == 0:
        print("This is visokosniy year")
        return True
    else:
        print ("This is not a visokosniy year")
        return False
        
year = int(input("Year: "))

year_leap(year)