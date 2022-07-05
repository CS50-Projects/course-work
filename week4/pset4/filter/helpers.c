#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;
            int average = round(round(blue + green + red) / 3);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            int sepiaRed = round((.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue));
            int sepiaGreen = round((.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue));
            int sepiaBlue = round((.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            };

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            };

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            };

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j != width - j && j < width / 2)
            {
                RGBTRIPLE tmp = image[i][width - j - 1];
                image[i][width - j - 1] = image[i][j];
                image[i][j] = tmp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int oldBlue[height][width];
    int oldGreen[height][width];
    int oldRed[height][width];

    // Create new 2-dimensional array with old RGB values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oldBlue[i][j] = image[i][j].rgbtBlue;
            oldGreen[i][j] = image[i][j].rgbtGreen;
            oldRed[i][j] = image[i][j].rgbtRed;
        }
    }

    // Loop through all array, if neighbors are present, add one to the counter, and add that number to the average calculator for that color
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int averageCounter = 0;
            int blueAverage = 0;
            int greenAverage = 0;
            int redAverage = 0;

            for (int k = -1; k < 2; k++) // Check the rows surrounding the current pixel
            {
                for (int p = -1; p < 2; p++) // Check the columns surrounding the current pixel
                {
                    if (i + k >= 0 && i + k < height) // Check to make sure the surrounding pixels fall within the boundaries of height of the image
                    {
                        if (j + p >= 0 && j + p < width) // Check to make sure the surrounding pixels fall within the boundaries of width of the image
                        {
                            blueAverage += oldBlue[i + k][j + p];
                            greenAverage += oldGreen[i + k][j + p];
                            redAverage += oldRed[i + k][j + p];
                            averageCounter += 1;
                        }
                    }
                }
            }

            image[i][j].rgbtBlue = round(round(blueAverage) / averageCounter);
            image[i][j].rgbtGreen = round(round(greenAverage) / averageCounter);
            image[i][j].rgbtRed = round(round(redAverage) / averageCounter);

        }
    }
    return;
}
