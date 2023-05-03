#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
using namespace std;

const int inputsize = 100;

int bintoint(int n) // Function for transforming binary measurements to int
{
  int num = n;
  int dec_value = 0;

  int base = 1;

  int temp = num;
  while (temp)
  {
    int last_digit = temp % 10;
    temp = temp / 10;

    dec_value += last_digit * base;

    base = base * 2;
  }

  return dec_value;
}

class Md_create 

public:
  double xl, xu, yl, yu;
  int nxs, nxl, nys, nyl, ck;
  Md_create(double x0, double y0, double x1, double y1,
            double inputint[inputsize][inputsize], double xmin, double ymin, double xmax,
            double ymax, double xwidth, double ywidth, int rows, int cols, const int inputsize)
  {

    if (x0 > x1)
    {
      xl = x1;
      xu = x0;
    }
    else
    {
      xl = x0;
      xu = x1;
    }

    if (y0 > y1)
    {
      yl = y1;
      yu = y0;
    }
    else
    {
      yl = y0;
      yu = y1;
    }

    nxs = (xl - xmin) / xwidth;
    nxl = (xu - xmin) / xwidth;
    nys = (yl - ymin) / ywidth;
    nyl = (yu - ymin) / ywidth;

    const int sizexmd = nxl - nxs;
    const int sizeymd = nyl - nys;

    double *trim = new double[sizexmd * sizeymd];
    for (int k1 = 0; k1 < sizexmd; k1++)
    {
      for (int k2 = 0; k2 < sizeymd; k2++)
      {
        ck = ck + 1;
        trim[ck] = inputint[nxs + k1][nys + k2];
      }
    }
  }
};

int main()

{
  const int inputsize = 100;
  double inputarr[inputsize][inputsize]; // Array for value z featuring random binary measurements
  double inputint[inputsize][inputsize]; // Array for value z transformed to integets 
  double xwidth = 0.5; // Distance between X elements
  double ywidth = 0.5; // Distance between Y elements
  int rows = inputsize;
  int cols = inputsize;
  int strsize = 6; // Number of digits that gain value for binary measurements

  for (int k1 = 0; k1 < rows; k1++) // This for loop generates random binary measurements for (x,y)
  {
    for (int k2 = 0; k2 < cols; k2++)
    {
      int x;
      int x10;
      int x00;
      srand(time(NULL));
      for (int i = 0; i < strsize; i++)
      { // Used multiplication int-based algorithm below 
      // for generating random measurements instead of 'string' to increase code speed
        x00 = x;
        x10 = ((int)rand() % 2);
        x = x10 + 10 * x00;
      }

      inputarr[k1][k2] = x;
      x = 0; 
    }
  }
cout<< inputarr[5][5];
  for (int k1 = 0; k1 < rows; k1++) // This loop transforms measurements to integer
  {
    for (int k2 = 0; k2 < cols; k2++)
    {

      inputint[k1][k2] = bintoint(inputarr[k1][k2]);

      if (inputint[k1][k2]>4096){ // Threshold set to 4096 per instructions
        inputint[k1][k2]=4096;
      }
    }
  }

  double xmin = 0; // Setting the origin to (0,0)
  double ymin = 0;
  double xmax = xmin + (rows - 1) * xwidth; // Maximum value decided automatically based on previous values
  double ymax = ymin + (cols - 1) * ywidth;
  double x0, y0, x1, y1;
  double xl, xu, yl, yu;
  int nxs, nxl, nys, nyl;

  x0 = 8; // Selection of parmeters for window (this is essentially 'cin'. Change as per desired)
  y0 = 2; // Selection of parmeters for window (this is essentially 'cin'. Change as per desired)
  x1 = 5; // Selection of parmeters for window (this is essentially 'cin'. Change as per desired)
  y1 = 4; // Selection of parmeters for window (this is essentially 'cin'. Change as per desired)
  double sumval, average;

  if (x0 > x1) // These if statements do parameter order correction if necessary, as was required in problem statement
  {
    xl = x1;
    xu = x0;
  }
  else
  {
    xl = x0;
    xu = x1;
  }

  if (y0 > y1)
  {
    yl = y1;
    yu = y0;
  }
  else
  {
    yl = y0;
    yu = y1;
  }


  if (xu == xl, yu == yl) // Assigning the trivial zero value to sum and average if inputs are identical
  {
    sumval = 0;
    average = 0;
  }
  else // Now for the real calculations...
  {
    nxs = (xl - xmin) / xwidth; // For calculating number of elements in the window
    nxl = (xu - xmin) / xwidth;
    nys = (yl - ymin) / ywidth;
    nyl = (yu - ymin) / ywidth;

    const int sizexmd = nxl - nxs; // ^^
    const int sizeymd = nyl - nys;

    int ck = 0;
    double *trim = new double[sizexmd * sizeymd]; // Dynamic array with size equal to number of elements in window
    for (int k1 = 0; k1 < sizexmd; k1++) // For filling out the dynamic array
    {
      for (int k2 = 0; k2 < sizeymd; k2++)
      {
        ck += 1;
        if (xu <= xmax, yu <= ymax, xl >= xmin, yl >= ymin)
        {
          trim[ck] = inputint[nxs + k1][nys + k2]; // Accepts values from measurements if they are in the window
        }
        else
        {
          trim[ck] = 0; // If measurements are outside of the window, value of zero will be assigned, as per instructions.
        }

        sumval += inputint[nxs + k1][nys + k2]; // Summation of values in window
      }
    }

    average = sumval / (sizexmd * sizeymd); // Average of values in window
  }

  cout << "Sum value " << sumval << "Average value " << average; // OutputC

  return 0;
}