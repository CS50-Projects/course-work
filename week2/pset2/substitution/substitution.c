#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string argument = argv[1];
    int argumentLength = strlen(argv[1]);
    string plainText;

    // Check length
    if (argumentLength == 26)
    {
        // Loop through every char in the argument
        for (int i = 0; i < argumentLength; i++)
        {
            for (int j = 1 + i; j < argumentLength; j++)
            {
                // Check for duplicate characters
                if (argv[1][i] == argv[1][j])
                {
                    printf("No matching characters\n");
                    return 1;
                }
            }

            // Check if every character is alphabetical
            if (!isalpha(argv[1][i]))
            {
                printf("Please only use letters\n");
                return 1;
            }
        }

        plainText = get_string("plaintext: ");

    }
    else
    {
        printf("Please input the right number of characters\n");
        return 1;
    }

    // Initialize an array the length of the alphabet
    int alphabet[26] = {};

    // Place ASCII character numbers in the alphabet array
    for (int letter = 0; letter < 26; letter++)
    {
        alphabet[letter] = 'a' + letter;
    }

    // Initialize cypherText array. Set it's size to the length of plainText
    char cypherText[strlen(plainText)];

    // Loop through every character of the given plain text
    for (int counter = 0, n = strlen(plainText); counter < n; counter++)
    {

        // Loop the length of the key
        for (int z = 0; z < argumentLength; z++)
        {
            // Compares the characters in plaintext to the alphabet array (case-insensitive).
            // Use the position of Z from the match to find it's equivalent in the key.
            if (plainText[counter] == alphabet[z] || plainText[counter] == (alphabet[z] - 32))
            {
                // Maintains lowercase from plaintext to cyphertext
                if (islower(plainText[counter]))
                {
                    cypherText[counter] = tolower(argument[z]);
                }

                // Maintains uppercase from plaintext to cyphertext
                else if (isupper(plainText[counter]))
                {
                    cypherText[counter] = toupper(argument[z]);
                }
            }
        }

        // Leave non-alphabetical characters as-is
        if (!isalpha(plainText[counter]))
        {
            cypherText[counter] = plainText[counter];
        }

    }

    printf("ciphertext: %s\n", cypherText);


};