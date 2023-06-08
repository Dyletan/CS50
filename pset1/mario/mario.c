poiog#include <stdio.h>
#include <cs50.h>

int main(void)
{
  int pyramid_height;

  // Prompt user for pyramid height and check if value is
  // between 0 and 8

  do
  {
      pyramid_height = get_int("Pyramid height: ");
  }
  while (pyramid_height < 0 || pyramid_height > 8);

  // Printing pyramid and adding space and #

  for (int x = 0; x < pyramid_height; x++)
  {
          int y;

      // Left Pyramid

      for (y = 0; y < (pyramid_height - x) - 1; y++)
      {
              printf(" ");
      }

      for (int r = 0; r < (pyramid_height) - y; r++)
      {
          printf("#");
      }

      // Space Between Pyramids

      for (int q = 0; q < 2; q++)
      {
            printf(" ");
      }

      // Right Pyramid
      for (int r = 0; r < (pyramid_height) - y; r++)
      {
          printf("#");
      }

      printf("\n");
  }
}