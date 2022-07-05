from cs50 import get_int


def main():

    f = get_int("Height: ")

    if f < 1 or f > 8:
        f = get_int("Height: ")

    for i in range(f):

        print(" " * (f - (i + 1)), end="")

        print("#" * (i + 1), end="")

        print(" " * 2, end="")

        print("#" * (i + 1), end="")

        print()


main()