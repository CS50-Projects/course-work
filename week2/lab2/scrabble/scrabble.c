#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
}

int compute_score(string word)
{

    // Initialize an array the length of the alphabet
    int alphabet[26] = {};

    // Place ASCII character numbers in the alphabet array
    for (int i = 0; i < 26; i++)
    {
        alphabet[i] = 'a' + i;
    }

    int score = 0;

    // Loop through each character in the word
    for (int j = 0, n = strlen(word); j < n; j++)
    {
        // Changes uppercase to lowercase
        if (word[j] >= 'A' && word[j] <= 'Z')
        {
            word[j] += 32;
        }

        // Find the position within the alphabet array that there's a match with the character from word
        // Use that position in the POINTS array and add the value to score
        for (int counter = 0; counter < 26; counter++)
        {
            if (word[j] == alphabet[counter])
            {
                score += POINTS[counter];
            }
        }

    }

    return score;

}
