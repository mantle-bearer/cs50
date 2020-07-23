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

    RGBTRIPLE blurred [height][width]; //declare temp array to hold blurred values


    //middle rows and columns
    if (height > 2 && width > 2) //check that middle rows exist
    {
        for (int i = 1; i < (height - 1); i++) //middle rows
        {
            for (int j = 1; j < (width - 1); j++) //gets middle pixel in each middle row
            {
                blurred[i][j] = middle(image[i - 1][j - 1], image[i - 1][j], image[i - 1][j + 1], image[i][j - 1], image[i][j], image[i][j + 1], image[i+1][j - 1], image[i + 1][j], image[i + 1][j + 1]);
            }
        }
    }


    //top and bottom rows
    if (width > 2 && height > 1)
    {
        for (int i = 1; i < (width - 1); i++)
        {
            blurred[0][i] = edge(image[0][i - 1], image[0][i], image[0][i+1], image[1][i - 1], image[1][i], image[1][i + 1]);
            blurred[height - 1][i] = edge(image[height - 1][i - 1], image[height - 1][i], image[height - 1][i + 1], image[height - 2][i - 1], image[height - 2][i], image[height - 2][i + 1]);
        }
    }


    //left and right columns
    if (height > 2 && width > 1)
    {
        for (int i = 1; i < (height - 1); i++)
        {
            blurred[i][0] = edge(image[i - 1][0], image[i][0], image[i + 1][0], image[i - 1][1], image[i][1], image[i + 1][1]);
            blurred[i][width - 1] = edge(image[i - 1][width - 1], image[i][width - 1], image[i + 1][width - 1], image[i - 1][width - 2], image[i][width - 2], image[i + 1][width - 2]);
        }
    }


    //corner values
    if (height > 2 && width > 2)
    {
        blurred[0][0] = corner(image[0][0], image[0][1], image[1][0], image[1][1]);
        blurred[0][width - 1] = corner(image[0][width - 1], image[0][width - 2], image[1][width - 1], image[1][width - 2]);
        blurred[height - 1][0] = corner(image[height - 1][0], image[height - 1][1], image[height - 2][0], image[height - 2][1]);
        blurred[height - 1][width - 1] = corner(image[height - 1][width - 1], image[height - 1][width - 1], image[height - 2][width - 2], image[height - 2][width - 2]);
    }


    //single row values
    if (height == 1 && width > 2)
    {
        for (int i = 1; i < (width - 1); i++)
        {
            blurred[0][i] = row(image[0][i - 1], image[0][i], image[0][i + 1]);
        }
    }

    //single row end, or two pixel horizontal array
    if (height == 1)
    {
        blurred[0][0] = rowend(image[0][0], image[0][1]);
        blurred[0][width - 1] = rowend(image[0][width - 1], image[0][width - 2]);
    }

    //single column values
    if (width == 1 && height > 2)
    {
        for (int i = 0; i < (width - 1); i++)
        {
            blurred[i][0] = row(image[i - 1][0], image[i][0], image[i + 1][0]);
        }
    }

    //single column end, or two pixel vertical array
    if (width == 1)
    {
        blurred[0][0] = rowend(image[0][0], image[1][0]);
        blurred[height - 1][0] = rowend(image[height - 1][0], image[height - 2][0]);
    }

    //transfer temp array values into image array
    for (int i = 0; i < height; i++) //gets each row of the image
    {
        for (int j = 0; j < width; j++) //gets each pixel in each row
        {
            image[i][j] = blurred[i][j];
        }
    }
    return;
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