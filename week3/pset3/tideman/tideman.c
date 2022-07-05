#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Set ranks at rank position equal to the i position of the candidate
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int index = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[index].winner = i;
                pairs[index].loser = j;
                index += 1;
                pair_count += 1;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int bubbleCounter = 1;

    // Run this loop until the counter is equal to zero, and the array is sorted
    for (int j = 0; bubbleCounter != 0; j++)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            bubbleCounter = 0;

            int winner = pairs[i].winner;
            int loser = pairs[i].loser;

            int winner2 = pairs[i + 1].winner;
            int loser2 = pairs[i + 1].loser;

            // Find the total difference in preference in a pair of pairs
            int firstTotal = preferences[winner][loser] - preferences[loser][winner];
            int secondTotal = preferences[winner2][loser2] - preferences[loser2][winner2];

            // Bubble sort descending
            if (firstTotal < secondTotal)
            {
                pair temp = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = temp;
                bubbleCounter += 1;
            }
        }
    }

    return;
}

// Recursive function to search through the locked pairs for a loop
bool loop_check(loser, winner)
{
    // Base -- If after several iterations, a chain can link back to the originally tested pair, this creates a loop, so return true.
    if (loser == winner)
    {
        return true;
    }

    // Recursive call
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop through the current truthful locked values and search for a match
        if (locked[loser][i])
        {
            // If there is a match, run the loop_check function again.
            // Use the loser of the locked match as the first argument of this new function call to search down the chain.
            if (loop_check(i, winner))
            {
                return true;
            };
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through pairs
    for (int i = 0; i < pair_count; i++)
    {
        // If loop check returns false, this means no loops were created, and this pair is safe to lock
        if (!loop_check(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{

    string winner;

    int truthCounter[candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        truthCounter[i] = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                truthCounter[i] = 1;
            }
        }

        if (truthCounter[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }

    }
    return;
}

