#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    //
    int dollar = 100;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    
    int remainder;
    int quarter_count, dime_count, nickel_count, penny_count;
    int coins;

    float user_input;
    // Do while loop to reprompt user when negative input is typed
    do
    {
        user_input = get_float("How much change is owed: ");
    }
    while (user_input < 0);
    return user_input;

    int change = round(user_input * 100);

    // Remove hundreds so that only coins combinations remains


    // Divide by 25 to get number of quarters and save by the remainder
    quarter_count = change / quarter;
    remainder = change % quarter;

    // Divide by 10 to get number of dime to save remainder
    dime_count = remainder / dime;
    remainder = remainder % dime;

    //Divide by 5 to get number of nickel to save remainder
    nickel_count = remainder / nickel;
    penny_count = remainder % nickel;


}
