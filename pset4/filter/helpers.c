#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray;
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            gray = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = gray;


        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = width / 2;
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            while(j < half)
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = temp;
                break;
            }
        }
    }
}

bool is_valid_pixel(int i, int j, int height, int width)
{
    if (i >= 0 && i < height && j >= 0 && j < width)
    {
        return true;
    }
    return false;

}

RGBTRIPLE get_blurred_pixel(int i, int j, int width, int height,  RGBTRIPLE image[height][width])
{
    int red, green, blue; red = green = blue = 0;
    float counter = 0.00;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            int new_i = i + x;
            int new_j = j + y;
            if (is_valid_pixel(new_i, new_j, height, width))
            {
                red += image[new_i][new_j].rgbtRed;
                green += image[new_i][new_j].rgbtGreen;
                blue += image[new_i][new_j].rgbtBlue;
                counter++;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtRed = round((float)red / counter);
    blurred_pixel.rgbtGreen = round((float)green / counter);
    blurred_pixel.rgbtBlue = round((float)blue / counter);
    return blurred_pixel;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            new_image[i][j] = get_blurred_pixel(i, j, width, height, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}

int limit(int rgb)
{
    if (rgb > 255)
    {
        rgb = 255;
    }
    return rgb;
}

RGBTRIPLE get_edged_pixel(int i, int j, int width, int height,  RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int redx = 0;
    int greenx = 0;
    int bluex = 0;
    int redy = 0;
    int greeny = 0;
    int bluey = 0;

    RGBTRIPLE edged_pixel;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            int new_i = i + x - 1;
            int new_j = j + y - 1;
            if (is_valid_pixel(new_i, new_j, height, width))
            {
                redx += image[new_i][new_j].rgbtRed * Gx[x][y];
                greenx += image[new_i][new_j].rgbtGreen * Gx[x][y];
                bluex += image[new_i][new_j].rgbtBlue * Gx[x][y];

                redy += image[new_i][new_j].rgbtRed * Gy[x][y];
                greeny += image[new_i][new_j].rgbtGreen * Gy[x][y];
                bluey += image[new_i][new_j].rgbtBlue * Gy[x][y];
                
                edged_pixel.rgbtRed = limit(round(sqrt((redx * redx) + (redy * redy))));
                edged_pixel.rgbtGreen = limit(round(sqrt((greenx * greenx) + (greeny * greeny))));
                edged_pixel.rgbtBlue = limit(round(sqrt((bluex * bluex) + (bluey * bluey))));
            }
        }
    }
    return edged_pixel;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            new_image[i][j] = get_edged_pixel(i, j, width, height, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    
}
