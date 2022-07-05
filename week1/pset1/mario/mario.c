#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Choose a number between 1 and 8: ");
    }
    while (n < 1 || n > 8);

    for (int column = 1; column <= n; column++) /* Initial loop creating columns and break lines */
    {
        for (int space = n - column; 1 <= space ; space--) /* Makes indentations for left-side pyramid */
        {
            printf(" ");
        }

        for (int row = 0; row < column; row++) /* Left-side pyramid blocks */
        {
            printf("#");
        }

        for (int gap = 0; gap < 1; gap++) /* Gap between pyramids */
        {
            printf("  ");
        }

        for (int right = 0; right < column; right++) /* Right-side pyramid */
        {
            printf("#");
        }

        printf("\n");
    }
}
