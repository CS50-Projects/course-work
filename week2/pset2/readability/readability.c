#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{

    string sentence = get_string("Text: ");

    int letters = 0;

    // Starting with one makes up for the last word not being counted in the text.
    int words = 1;
    int sentences = 0;
    int grade = 0;

    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        // Function that checks if characters are alphabetical
        if (isalpha(sentence[i]))
        {
            letters += 1;
        }

        // For every space, 1 is added to the word count
        if (sentence[i] == 32)
        {
            words += 1;
        }

        if (sentence[i] == 33 || sentence[i] == 46 || sentence[i] == 63)
        {
            sentences += 1;
        }
    }

    // The average number of letters per 100 words
    float L = ((float)letters / words) * 100;

    // The average number of sentences per 100 words
    float S = ((float)sentences / words) * 100;

    // Coleman-Liau formula
    grade = round(0.0588 * L - 0.296 * S - 15.8);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}