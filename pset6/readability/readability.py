from cs50 import get_string

text = get_string("Text: ")
let = sent = 0
words = 1

for i in range(len(text)):
    if text[i].isalpha():
        let += 1
    elif text[i] == ' ':
        words += 1
    elif text[i] == '.' or text[i] == '!' or text[i] == '?':
        sent += 1

L = let * 100 / words
S = sent * 100 / words
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 16 and index > 1:
    print(f"Grade {index}")
elif index < 1:
    print("Before grade 1")
elif index >= 16:
    print("Grade 16+")



