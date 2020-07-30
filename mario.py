# get input from user
h = int(input("Height: "))

# Ensure that users typed in a positive integer between 1 and 8, inclusive.
while h < 1 or h > 8:
    print("provide a positive integer between 1 and 8, inclusive.")
    h = int(input("Height: "))

# Draw a pyramid of height h
for i in range(h):
    for j in range(i+1, h, 1):
        print(" ", end="")
    for k in range(i+1):
        print("#", end="")
    print(sep="")
