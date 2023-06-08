#include "helpers.h"
#include <math.h>
#include <cs50.h>

//серый фильтр
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray;//переменная для нового серого пикселя

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            //вычисляем оттенок серого с помощбю следующей формулы
            gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //присваиваем оттенок серого пикселю
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}
//функция для ограничения значения числа 255
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}
//старый (красно-коричневый) фильтр
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaBlue;
    int sepiaRed;
    int sepiaGreen;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            sepiaRed = limit(round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue));
            sepiaGreen = limit(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
            sepiaBlue = limit(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
     return;
}

//отражение изображения по оси Ох
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Scan height
    for (int i = 0; i < height; i++)
    {
        int halfWidth = round((float)1/2 * width);
        for (int j = 0; j < width; j++)
        {

            while (j < halfWidth)
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
    if ( i >= 0 && i < height && j >= 0 && j < width)
    {
        return true;
    }
    return false;
}

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue; red = green = blue = 0;
    float counter = 0.0;
    for (int k = -1; k <= 1; k++)
    {
        for (int h = -1; h <= 1; h++)
        {
            int new_i = i + k;
            int new_j = j + h;
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

//Фильтр размытия
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            new_image[i][j] = get_blurred_pixel(i, j, height, width, image);
        }
    }
   
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            image[i][j] = new_image[i][j];
        }
   
    }
}
