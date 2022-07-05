import csv
import sys
import re
from collections import Counter


def main():

    # Ensure right number of arguments are given in the terminal
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py file.csv file.txt")

    csvfile = sys.argv[1]
    textfile = sys.argv[2]

    # Read csv file into a dictionary
    people = []
    with open(csvfile) as database:

        reader = csv.DictReader(database)

        for row in reader:
            people.append(row)

    # Find the different combinations of STR's listed in csv file
    STRs = list(people[0].keys())

    # Take away the 'name' key from this list
    STRs.pop(0)

    # Find how many different combinations of STR that will need to be searched for in the text file
    numOfSTRs = len(STRs)

    # Read text file containing genetic info into variable named dna
    dna = ''
    with open(textfile) as sequences:

        reader = sequences.read()

        for letter in reader:
            dna += letter

    # Check specific STR combination from csv file against the dna variable
    counter = {}

    # For each STR, search through the text file for matches
    for i in range(0, numOfSTRs):

        # Find the length of each STR combination
        length = len(STRs[i])

        # Create arrays to store the start/end positions of the matches found
        indexes = []

        # Set maximum values
        maximumCount = 1
        maximum = 0

        # Find a match in the dna text file
        for match in re.finditer(STRs[i], dna):

            indexes.append(match.start())

        # Look through the start positions of matches, compare them one against the other
        for g in range(1, len(indexes)):

            # Check that the distance between start positions is equal to the length of the STR. Hence being consecutive.
            if (indexes[g] - indexes[g - 1]) == length:

                # If they are consecutive, add one to the counter
                maximumCount += 1

                # If the counter is greater than the current highest value, replace it with the counter
                if maximum < maximumCount:
                    maximum = maximumCount

            # If there is not a consecutive match, reset the count to one
            else:
                maximumCount = 1

        # If there is a STR count for the current STR, add that to the counter dict, and set the value as the highest STR count found
        if STRs[i] not in counter.keys() and maximum != 0:
            counter[STRs[i]] = maximum

    # Creates a variable to track the number of times a STR combination from the csv matches ones found in the counter dict
    winCount = 0

    # Creates an array large enough to hold a single number for every person in the csv file. The number is used to track how many times the STR from the count matches the csv file.
    matchCount = [0] * len(people)

    # Loop through all recorded SRTs from csv
    for i in range(numOfSTRs):

        # Check which SRTs are actually present in the count from the txt file
        if STRs[i] in counter:

            # Incease by one
            winCount += 1

            # Loop through every person in the people dictionary
            for a in range(len(people)):

                # Check if the SRT count from counter matches what is in the dictionary
                if int(counter[STRs[i]]) == int(people[a][STRs[i]]):

                    # If there is a match, add 1 to the count for that index
                    matchCount[a] += 1

    # Check that the STRs that are being searched for are actually present, and see that all STRs are accounted for
    if winCount != 0 and winCount in matchCount:

        for i in range(len(matchCount)):

            if winCount == matchCount[i]:
                print(people[i]['name'])

    else:
        print('No match')


main()

