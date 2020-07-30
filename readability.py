from cs50 import get_string

text = get_string("Text: ")

words = 1
letters = 0
sentence = 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    elif text[i] == " ":
        words += 1
    elif text[i] in [".", "!", "?"]:
        sentence += 1

L = (float(letters) / float(words)) * 100
S = (float(sentence) / float(words)) * 100

index = (0.0588 * float(L)) - (0.296 * float(S)) - 15.8

if index > 16:
    print("Grade 16+")

elif index < 1:
    print("Before Grade 1")

else:
    grade = round(index)
    print(f"Grade {grade}")