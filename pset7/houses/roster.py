import csv
import sys
from cs50 import SQL

if len(sys.argv) != 2:
    exit(1)

houses = ["slytherin", "gryffindor", "ravenclaw", "hufflepuff"]
name = sys.argv[1].lower()
if name not in houses:
    sys.exit("provide house name: Gryffindor, Hufflepuff, Slytherin or Ravenclaw.")


db = SQL("sqlite:///students.db")

house_list = db.execute(
    "SELECT first, middle, last, birth FROM students WHERE LOWER(house) = (?) ORDER BY last, first", name)

for row in house_list:
    if row["middle"] == None:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))