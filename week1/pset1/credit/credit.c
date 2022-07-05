#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{

    long int credit = get_long("Number: ");

    int firstSum;
    int finalSum;

    bool checkSum = false;
    bool cardChecked = false;

    // Takes every second number, starting with the second from last, multiplies them by 2, and returns the sum.
    for (long int i = 10; i < credit; i *= 100)
    {

        int firstSumNumber = (trunc((credit / i) % 10)) * 2;

        // If any of the sums are a two digit number, split them into individual digits and add them.
        if (firstSumNumber > 9)
        {
            int a = trunc(firstSumNumber / 10);
            int b = firstSumNumber % 10;
            firstSumNumber = (a + b);
        }

        firstSum = firstSum + firstSumNumber;

    }

    finalSum = firstSum;

    // Takes all remaining numbers from the credit card and finds their sum.
    for (long int j = 1; j < credit; j *= 100)
    {

        finalSum += (trunc((credit / j) % 10));

    }

    // If the final digit of this last sum is equal to 0, the credit card is valid.
    if (finalSum % 10 == 0)
    {
        checkSum = true;
    }

    if (checkSum == true)
    {
        // AMEX check
        // Check if the first digit is 3, the second digit is 4 or 7, and if the length of the card number is 15 digits
        if (trunc(credit / pow(10, 14)) == 3)
        {
            int amexCheck = trunc(credit / pow(10, 13));

            if (amexCheck % 10 == 4 || amexCheck % 10 == 7)
            {
                printf("AMEX\n");
                cardChecked = true;
            }
            else
            {
                printf("INVALID\n");
                cardChecked = true;
            }
        }

        // Mastercard check
        // Check whether the first digit is 5, the second digit is between 1 and 5, and if the length of the card number is 16 digits
        if (trunc(credit / pow(10, 15)) == 5)
        {
            int mastercardCheck = trunc(credit / pow(10, 14));

            if (mastercardCheck % 10 > 0 && mastercardCheck % 10 < 6)
            {
                printf("MASTERCARD\n");
                cardChecked = true;

            }
            else
            {
                printf("INVALID\n");
                cardChecked = true;

            }
        }

        // Visa check
        // Check whether the first digit is 4, and if the length of the card number is 13 or 16 digits
        if (trunc(credit / pow(10, 12)) == 4 || trunc(credit / pow(10, 15)) == 4)
        {
            printf("VISA\n");
            cardChecked = true;
        }

        // Sets a back up value if the number passes the sumcheck test, but doesn't match any of the cards
        if (cardChecked == false)
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }
}



