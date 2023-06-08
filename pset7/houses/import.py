import cs50
from sys import argv, exit
import csv

if len(argv) != 2:

    print("Usage: python import.py characters.csv")

    exit(1)

db = cs50.SQL("sqlite:///students.db")

no = None

with open(argv[1]) as data:

    table = list(csv.DictReader(data))

    ID = 0
    none = None

    for row in table:

        name = row["name"]
        x = name.split(" ")
        print(x)
        print(len(x))
        house = row["house"]
        birth = row["birth"]

        if len(x) == 3:
            first = x[0]
            middle = x[1]
            last = x[2]

            db.execute(
                f"INSERT INTO students (id, first, middle, last, house, birth) VALUES ('{ID}', '{first}', '{middle}', '{last}', '{house}', '{birth}');")

            ID += 1

        elif len(x) == 2:
            first = x[0]
            last = x[1]

            db.execute(
                f"INSERT INTO students (id, first, middle, last, house, birth) VALUES ('{ID}', '{first}', NULL, '{last}', '{house}', '{birth}');")

            ID += 1

print("finished")