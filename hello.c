// A program that gets input from user and says hello to them with their input
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get input from user
    string name = get_string("What is your name?\n");

    // Print Hello to user plugin in the user input
    printf("hello, %s\n", name);
}