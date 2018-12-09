/*********************************************************************
 File:     chromakey.cpp

 Author:   Maxwell Newman

 Email address: mdnewman@usc.edu

 Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input 
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and 
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold);

void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE]);

void replace(bool mask[][SIZE],
	     unsigned char inImage[][SIZE][RGB],
	     unsigned char bgImage[][SIZE][RGB],
	     unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[])
{
  // Image data array
  // Note:  DON'T use the static keyword except where we expressly say so.
  //        It puts the large array in a separate, fixed, area of memory. 
  //        It is bad practice. But useful until we have dynamic allocation.
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  double threshold;

  if (argc < 6) {
    cerr << "usage: program_name in.bmp background.bmp dist_threshold " 
         << "out1.bmp out2.bmp" << endl;
    return 0;
  }
	
  if (readRGBBMP(argv[1], inputImage)) {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  if (readRGBBMP(argv[2], bgrndImage)) {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }
  
  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
  threshold = atof(argv[3]);

  // Call Method 1 Function
  method1(inputImage, chromaMask, threshold);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage)) {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }	

  // Call Method 2 Function
  method2(inputImage, chromaMask);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage)) {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }	

  return 0;
}



// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold)
{
  //the colorSums record the total of each of the RGB values of the smaple
  //green pixels in order to calculate the average
  int redSum = 0;
  int greenSum = 0;
  int blueSum = 0;

  //the colorAverages reocrd the average of the RGB values for green pixels
  double redAvg = 0;
  double greenAvg = 0;
  double blueAvg = 0;

  //for loop iterates along the top, left, and right edges of the screen
  //in order to collect samples of green pixels
  for(int i=0; i<(SIZE); i++)
  {
    redSum += inImage[0][i][0] + inImage[i][SIZE-1][0] + inImage[i][0][0];
    greenSum += inImage[0][i][1] + inImage[i][SIZE-1][1] + inImage[i][0][1];
    blueSum += inImage[0][i][2] + inImage[i][SIZE-1][2] + inImage[i][0][2];
  }

  redAvg = redSum/(3*SIZE);
  greenAvg = greenSum/(3*SIZE);
  blueAvg = blueSum/(3*SIZE);

  //outer for loop to determine background and foreground
  //iterates through rows
  for(int i=0; i<SIZE; i++)
  {
    //inner for loop iterates through columns
    for(int j=0; j<SIZE; j++)
    {
      int redVal = inImage[i][j][0];
      int greenVal = inImage[i][j][1];
      int blueVal = inImage[i][j][2];

      //distance stores the RGB distance between the average "green" pixel
      //and the current pixel in the image
      double distance = sqrt(pow((redAvg-redVal),2) + 
        pow((greenAvg-greenVal),2) + pow((blueAvg-blueVal),2));

      //determines if the currrent pixel should be considered "green"
      //and thus replaced
      if(distance <= threshold)
      {
        mask[i][j] = 0;
      }
      else
      {
        mask[i][j] = 1;
      }
    }
  }
}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE])  
{
  //distance stores the distances between the average green pixel and each
  //of the green pixels along the top, left, and right edges of the image
  double* distance = new double[3*SIZE];

  //the color sum store the total RGB values of green pixels in order to find
  //the average pixels
  double redSum = 0;
  double greenSum = 0;
  double blueSum = 0;
  //the color averages store the RGB values of the average green pixel
  double redAvg = 0;
  double greenAvg = 0;
  double blueAvg = 0;

  //distanceAvg stores the average distance between the average green pixel
  //and the green pixels along the edge of the image.
  //distStdDev stores the standard deviation of this distance
  double distanceAvg = 0;
  double distanceSum = 0;
  double distDiffSum = 0;
  double distStdDev = 0;
  double threshold = 0;

  //distanceAvgTot stores the average distance between the average green
  //pixels and all other pixels in the image
  double distanceAvgTot = 0;
  double distanceSumTot = 0;
  double thresholdTot = 0;

  //for loop iterates through the top, left, and right edges of the screen
  //to find an average RGB value for green pixels
  for(int i=0; i<SIZE; i++)
  {
    redSum += inImage[0][i][0] + inImage[i][SIZE-1][0] + inImage[i][0][0];
    greenSum += inImage[0][i][1] + inImage[i][SIZE-1][1] + inImage[i][0][1];
    blueSum += inImage[0][i][2] + inImage[i][SIZE-1][2] + inImage[i][0][2];
  }

  //finds the average RGB value for the pixels
  redAvg = (redSum)/(3*SIZE);
  greenAvg = (greenSum)/(3*SIZE);
  blueAvg = (blueSum)/(3*SIZE);

  //iterates through the top, left, and right edges of the image again to
  //find the distance between the average green pixel and each green pixel
  //on the edge of the screen
  for(int i=0; i<SIZE; i++)
  {
    int r1 = inImage[0][i][0];
    int g1 = inImage[0][i][1];
    int b1 = inImage[0][i][2];

    int r2 = inImage[i][SIZE-1][0];
    int g2 = inImage[i][SIZE-1][1];
    int b2 = inImage[i][SIZE-1][2];

    int r3 = inImage[i][0][0];
    int g3 = inImage[i][0][1];
    int b3 = inImage[i][0][2];

    //calculates the distance between current and average green pixels
    distance[3*i] = sqrt(pow((redAvg-r1),2) + pow((greenAvg-g1),2)
     + pow((blueAvg - b1),2));
    distance[3*i+1] = sqrt(pow((redAvg-r2),2) + pow((greenAvg-g2),2) 
      + pow((blueAvg - b2),2));
    distance[3*i+2] = sqrt(pow((redAvg-r3),2) + pow((greenAvg-g3),2) 
      + pow((blueAvg - b3),2));

    //tracks the total distance
    distanceSum += distance[3*i];
    distanceSum += distance[3*i+1];
    distanceSum += distance[3*i+2];
  }

  //calculates the average distance
  distanceAvg = distanceSum/(3*SIZE);

  //iterates through each of the distances and calculates the numerator
  //of the standard deviation equation for distance
  for(int i=0; i<3*SIZE; i++)
  {
  	distDiffSum += pow((distance[i]-distanceAvg),2);
  }

  //calulates distance standard deviation
  distStdDev = sqrt(distDiffSum/(3*SIZE));
  //sets a threshold of 3 sigma width
  threshold = distanceAvg + 3.5*distStdDev;

  //outer for loop iterates along rows of image
  for(int i=0; i<SIZE; i++)
  {
    //inner for loop iterates along columns
    for(int j=0; j<SIZE; j++)
    {
      double redVal = inImage[i][j][0];
      double greenVal = inImage[i][j][1];
      double blueVal = inImage[i][j][2];
      
      //calculates the distance between current and average green pixels
      double pixelDist = sqrt(pow((redAvg-redVal),2) + 
        pow((greenAvg-greenVal),2) + pow((blueAvg-blueVal),2));

      distanceSumTot += pixelDist;
    }
  }
  //finds the average distance between every pixel and average green pixel
  distanceAvgTot = distanceSumTot/(pow(SIZE,2));
  //sets a second treshold to increase accuracy when identifying green pixels
  thresholdTot = distanceAvgTot;

  //iterates along rows
  for(int i=0; i<SIZE; i++)
  {
    //iterates along columns
    for(int j=0; j<SIZE; j++)
    {
      double redVal = inImage[i][j][0];
      double greenVal = inImage[i][j][1];
      double blueVal = inImage[i][j][2];
      
      //finds distance between current and average green pixels
      double pixelDist = sqrt(pow((redAvg-redVal),2) + 
        pow((greenAvg-greenVal),2) + pow((blueAvg-blueVal),2));

      //if either threshold or thresholdTot are true for the current pixel,
      //the pixel is designated as green and thus replaced by background
      if(pixelDist <= threshold || pixelDist <=thresholdTot)
      {
        mask[i][j] = 0;
      }
      else
      {
        mask[i][j] = 1;
      }
    }
  }
  //deallocating dynamically allocated memory
  delete [] distance;
}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
	     unsigned char inImage[SIZE][SIZE][RGB],
	     unsigned char bgImage[SIZE][SIZE][RGB],
	     unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image

  //out for loop, iterates along rows
  for(int i=0; i<SIZE; i++)
  {
    //inner for loop, iterates along columns
    for(int j=0; j<SIZE; j++)
    {
      if(mask[i][j] == 0)
      {
        outImage[i][j][0] = bgImage[i][j][0];
        outImage[i][j][1] = bgImage[i][j][1];
        outImage[i][j][2] = bgImage[i][j][2];
      }

      else
      {
        outImage[i][j][0] = inImage[i][j][0];
        outImage[i][j][1] = inImage[i][j][1];
        outImage[i][j][2] = inImage[i][j][2];
      }
    }
  }


}
