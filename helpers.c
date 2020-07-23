#include "helpers.h"
#include <math.h>

int cap (int x);
RGBTRIPLE rowend (RGBTRIPLE x, RGBTRIPLE y);
RGBTRIPLE row (RGBTRIPLE x, RGBTRIPLE y, RGBTRIPLE z);
RGBTRIPLE corner (RGBTRIPLE x, RGBTRIPLE y, RGBTRIPLE z, RGBTRIPLE a);
RGBTRIPLE edge (RGBTRIPLE x, RGBTRIPLE y, RGBTRIPLE z, RGBTRIPLE a, RGBTRIPLE b, RGBTRIPLE c);
RGBTRIPLE middle (RGBTRIPLE x, RGBTRIPLE y, RGBTRIPLE z, RGBTRIPLE a, RGBTRIPLE b, RGBTRIPLE c, RGBTRIPLE d, RGBTRIPLE e, RGBTRIPLE f);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //gets each row of the image
    {
        for (int j = 0; j < width; j++) //gets each pixel in each row
        {
            int k = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0); //divides by float to get float value, which it then rounds
            image[i][j].rgbtBlue = k;
            image[i][j].rgbtGreen = k;
            image[i][j].rgbtRed = k;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //gets each row of the image
    {
        for (int j = 0; j < width; j++) //gets each pixel in each row
        {
            //applies formula, but saves new value in a separate variable. Rounds and caps at 255.
            int blue = cap(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));
            int green = cap(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
            int red = cap(round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue));

            //moves value from temp variable back to array
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtRed = red;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; //new temp array to store backwards values

    for (int i = 0; i < height; i++) //gets each row of the image
    {
        for (int j = 0; j < width; j++) //gets each pixel in each row
        {
            temp[i][j] = image[i][width - (j + 1)]; //sets temp array to 'reflected' image array
        }
    }

    for (int i = 0; i < height; i++) //gets each row of the image
    {
        for (int j = 0; j < width; j++) //gets each pixel in each row
        {
            image[i][j] = temp[i][j]; //sets image values as temp array values
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int sumblue;
    int sumgreen;
    int sumred;
    float counter;
    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumblue = 0;
            sumgreen = 0;
            sumred = 0;
            counter = 0.00;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
           for (int m = -1; m < 2; m++)  // loop thru row of pixel matrix 3x3 -1 0 1
           {
               for (int n = -1; n < 2; n++) // loop thru column of pixel matrix 3x3 -1 0 1
               {
                   if (i + m < 0 || i + m > height - 1)
                   {
                       continue;
                   }
                   if (j + n < 0 || j + n > width - 1)
                   {
                       continue;
                   }

                   sumblue += image[i + m][j + n ].rgbtBlue; // sum of blue values of all pixels in 3x3 for that particular pixel looped into m,n and then i,j
                   sumgreen += image[i + m][j + n].rgbtGreen;
                   sumred += image[i + m][j + n].rgbtRed;
                   counter++; // after the rbg values of that particular pixel is added(adding for neighboring values of it) increase counter  and move to next m,n and then i,j


                   // take avg by sum/ counter and store it in temp rgbtriple
                   temp[i][j].rgbtBlue = round(sumblue / counter);
                   temp[i][j].rgbtGreen = round(sumgreen / counter);
                   temp[i][j].rgbtRed = round(sumred / counter);
               }
           }
        }
    }
    // copy that into actual pixel for every pixel from all values of i and j
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
}

//caps sepia values at 255
int cap (int x) //takes an x value as input
{
    if (x > 255) //if x is higher than 255, returns 255
    {
        return 255;
    }
    else //if x isn't higher than 255, returns x
    {
        return x;
    }
}


RGBTRIPLE rowend (RGBTRIPLE x, RGBTRIPLE y)
{
    RGBTRIPLE e;
    e.rgbtBlue = round((x.rgbtBlue + y.rgbtBlue) / 2.0);
    e.rgbtGreen = round((x.rgbtGreen + y.rgbtGreen) / 2.0);
    e.rgbtRed = round((x.rgbtRed + y.rgbtRed) / 2.0);
    return e;
}

//gets new RGB values for single row pixels
RGBTRIPLE row (RGBTRIPLE x, RGBTRIPLE y, RGBTRIPLE z)
{
    RGBTRIPLE r;
    r.rgbtBlue = round((x.rgbtBlue + y.rgbtBlue + z.rgbtBlue) / 3.0);
    r.rgbtGreen = round((x.rgbtGreen + y.rgbtGreen + z.rgbtGreen) / 3.0);
    r.rgbtRed = round((x.rgbtRed + y.rgbtRed + z.rgbtRed) / 3.0);
    return r;
}

//gets new RGB values for corner pixels
RGBTRIPLE corner (RGBTRIPLE x, RGBTRIPLE y, RGBTRIPLE z, RGBTRIPLE a)
{
    RGBTRIPLE f;
    f.rgbtBlue = round((x.rgbtBlue + y.rgbtBlue + z.rgbtBlue + a.rgbtBlue) / 4.0);
    f.rgbtGreen = round((x.rgbtGreen + y.rgbtGreen + z.rgbtGreen + a.rgbtGreen) / 4.0);
    f.rgbtRed = round((x.rgbtRed + y.rgbtRed + z.rgbtRed + a.rgbtRed) / 4.0);
    return f;
}

//gets new RGB values for edge pixels
RGBTRIPLE edge (RGBTRIPLE x, RGBTRIPLE y, RGBTRIPLE z, RGBTRIPLE a, RGBTRIPLE b, RGBTRIPLE c)
{
    RGBTRIPLE s;
    s.rgbtBlue = round((x.rgbtBlue + y.rgbtBlue + z.rgbtBlue + a.rgbtBlue + b.rgbtBlue + c.rgbtBlue) / 6.0);
    s.rgbtGreen = round((x.rgbtGreen + y.rgbtGreen + z.rgbtGreen + a.rgbtGreen + b.rgbtGreen + c.rgbtGreen) / 6.0);
    s.rgbtRed = round((x.rgbtRed + y.rgbtRed + z.rgbtRed + a.rgbtRed + b.rgbtRed + c.rgbtRed) / 6.0);
    return s;
}

//gets new RGB values for middle pixels
RGBTRIPLE middle (RGBTRIPLE x, RGBTRIPLE y, RGBTRIPLE z, RGBTRIPLE a, RGBTRIPLE b, RGBTRIPLE c, RGBTRIPLE d, RGBTRIPLE e, RGBTRIPLE f)
{
    RGBTRIPLE n;
    n.rgbtBlue = round((x.rgbtBlue + y.rgbtBlue + z.rgbtBlue + a.rgbtBlue + b.rgbtBlue + c.rgbtBlue + d.rgbtBlue + e.rgbtBlue + f.rgbtBlue) / 9.0);
    n.rgbtGreen = round((x.rgbtGreen + y.rgbtGreen + z.rgbtGreen + a.rgbtGreen + b.rgbtGreen + c.rgbtGreen + d.rgbtGreen + e.rgbtGreen + f.rgbtGreen) / 9.0);
    n.rgbtRed = round((x.rgbtRed + y.rgbtRed + z.rgbtRed + a.rgbtRed + b.rgbtRed + c.rgbtRed + d.rgbtRed + e.rgbtRed + f.rgbtRed) / 9.0);
    return n;
}