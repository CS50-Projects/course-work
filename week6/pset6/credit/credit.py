from cs50 import get_int
import math


def main():

    # Get credit card integer from user, convert to string
    creditCard = str(get_int("Credit card number: "))

    length = len(creditCard)

    finalSum = 0

    checkSum = False

    # Loop through the credit card string, start at the 2nd last digit
    for i in range(length - 2, -1, -2):

        # Multiply each of those digits by 2
        i = int(creditCard[i]) * 2

        # If, after multiplication, that number is two digits long, split the digits and then add them together
        if i > 9:
            a = math.trunc(i / 10)
            b = i % 10
            i = a + b

        # Add the resulting number to the finalSum variable
        finalSum += i

    # Go through every left over number in the credit card string, and add them to the finalSum variable
    for i in range(length - 1, -1, -2):

        finalSum += int(creditCard[i])

    # Check if the final digit of the finalSum variable is zero, if true set checkSum to true
    if finalSum % 10 == 0:

        checkSum = True

    # Print out the type of card
    if checkSum:

        if creditCard[0] == '4':
            print("VISA")
        elif creditCard[0] == '5':
            print("MASTERCARD")
        elif creditCard[0] == '3':
            print("AMEX")

    else:
        print("INVALID")


main()