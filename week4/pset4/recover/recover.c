#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
const int CHUNK = 512;

int main(int argc, char *argv[])
{
    // Check that appropriate number of arguments passed
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    };

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open");
        return 2;
    }

    int imageCounter = 0;

    // Set variable for the output jpg files
    char *name = malloc(8);

    FILE *output;

    // Create an array with datatype BYTE, and give it a maximum value of CHUNK (512)
    BYTE buffer[CHUNK];

    // Read the memory card
    while (fread(&buffer, CHUNK, 1, input) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Check if the first 000.jpg exists
            if (imageCounter == 0)
            {
                sprintf(name, "%03i.jpg", imageCounter);
                output = fopen(name, "w");
                imageCounter += 1;
            }
            else
            {
                fclose(output);
                sprintf(name, "%03i.jpg", imageCounter);
                output = fopen(name, "w");
                imageCounter += 1;
            }

            fwrite(&buffer, CHUNK, 1, output);
        }

        else if (imageCounter > 0)
        {
            fwrite(&buffer, CHUNK, 1, output);
        }
    }

    free(name);
    fclose(input);
    fclose(output);
}