# TODO

import csv
import cs50
from sys import argv, exit

while len(argv) > 2 or len(argv) < 2:
    print("Usage error!")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

csv_file = argv[1]

with open(csv_file, "r") as file:
    reader = csv.reader(file)

    for row in reader:
        name = row[0].split()
        house = row[1]
        birth = row[2]
        if len(name) > 1:
            if len(name) > 2:
                db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[0], name[1], name[2], house, birth)
                #print("Big: ", name[0], name[1], name[2], house, birth)
            else:
                empty = None
                db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[0], empty, name[1], house, birth)
                #print("Small: ", name[0], name[1], house, birth)
        #else:
            #print("Smallest: ", name[0], house, birth)