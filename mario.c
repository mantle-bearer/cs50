// Draws a pyramid using iteration

#include <cs50.h>
#include <stdio.h>

int get_positive_int(void);

int main(void)
{
    // Get height of pyramid form user
    int h = get_positive_int();

    // Draw pyramid using user's input
    for (int i = 1; i <= h; i++)
    {
        for (int k = i; k < h; k++)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// Prompt user for positive integer within one and eight
int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}
