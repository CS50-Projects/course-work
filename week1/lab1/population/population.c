#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startingPopulation;

    do
    {
        startingPopulation = get_int("Starting population size?\n");
    }
    while (startingPopulation < 9);

    // TODO: Prompt for end size

    int endingPopulation;

    do
    {
        endingPopulation = get_int("Desired ending population size?\n");
    }
    while (endingPopulation < startingPopulation);


    // TODO: Calculate number of years until we reach threshold

    int years = 0;

    for (int yearsPassed = 1; startingPopulation < endingPopulation; yearsPassed++)
    {
        startingPopulation += ((startingPopulation / 3) - (startingPopulation / 4));

        years = yearsPassed;
    }

    // TODO: Print number of years

    printf("Years: %i\n", years);

}