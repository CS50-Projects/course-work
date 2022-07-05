from cs50 import get_string


def main():

    text = get_string("GIVE ME SENTENCE: ")

    letters = 0
    words = 1
    sentences = 0
    grade = 0

    for letter in text:
        if letter.isalpha():
            letters += 1

    for word in text:
        if word == " ":
            words += 1

    for sentence in text:
        if sentence == "!" or sentence == "?" or sentence == ".":
            sentences += 1

    L = (letters / words) * 100
    S = (sentences / words) * 100

    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade >= 16:
        print("Grade: 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade: {grade}")


main()