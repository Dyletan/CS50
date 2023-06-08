def what_season(month, season):
    if month > 0 and month < 4:
        print(season[0])
    elif month > 3 and month < 7:
        print(season[1])
    elif month > 6 and month < 10:
        print(season[2])
    elif month > 5 and month < 13:
        print(season[3])
    else:
        print("No such month")


season = ["winter", "spring", "Summer", "Autumn"]
month = int(input("Month: "))

what_season(month, season)