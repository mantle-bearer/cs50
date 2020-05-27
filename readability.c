// A program that computes the Coleman-Liau index of text to know the grade level of the text

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Gets text from user
    string text = get_string("Text: ");
    
    //Initialize leteers, words and sentences
    int letters = 0;
    int words = 1;
    int sentences = 0;

    // Count letters, words and sentences
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        
    }

    {
        // Calculates the average of L and S per 100 words
        float L = ((float)letters / (float)words * 100);
        float S = ((float)sentences / (float)words * 100);
        
        // Calculates the grade of the text using coleman-liu formular
        float index = (0.0588 * L - 0.296 * S - 15.8);
        
        // Prints the grade of the text depending of the result of colman-liu formular
        if (index >= 16)
        {
            printf("Grade 16+\n");
        }
        else if (index < 1)
        {
            printf("Before Grade 1\n");
        }
        else
        {
            int grade = roundf(index);
            printf("Grade %i\n", grade);
        }
    }
}