# TODO

import cs50
from sys import argv, exit

# Make sure that the correct commandline argument is used
while len(argv) > 2 or len(argv) < 2:
    print("Usage: [house name]")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

# Output the details from the database using the users inputed house
rows = db.execute("SELECT first, middle, last, house, birth FROM students WHERE house= :inputu ORDER BY last ASC, first ASC", inputu=argv[1])
for row in rows:
    if row['middle'] == None:
        print(row['first'], row['last'], "born", row['birth'])
    else:
        print(row['first'], row['middle'], row['last'], "born", row['birth'])
