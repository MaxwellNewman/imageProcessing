CSCI 103 Programming Assignment 3, Chroma Key, Fall 2017

Name: Maxwell Newman

Email Address: mdnewman@usc.edu

NOTE: You can delete the questions, we only need your responses.

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | (69,138,19)  |  n/a
Arm                  | (213,125,89)  |160.63
Vest                 | (27,27,27)  |118.95
Shirt                | (238,204,228)  |276.76

================================== Review ===================================
Response 1: I chose every pixel along the top, right, and left edges of the
picture to compute the average green pixel. I did so because we could reliably
assume that the edges of the screen would be green, and so would provide a good
background average. One could have taken pixels from a few more columns into
the screen in an effort to reduce variance, but doing so would have risked
hitting foreground pixels that aren't green, thus affecting the average. I
probably did not need to sample quite so many (3*256) pixels, but I wanted
to be sure to obtain a reliable average, which comes by sampling a large
number of pixels.

Response 2:

  Image                  Min Threshold           Max Threshold
  Colbert range:  from   70                to 80
  Bird range:     from   5                to 90

These ranges give reasonably crisp images with minimal green splotching. Any
deviance away from these ranges will start to yield larger flaws in the image.

Response 3: My method 2 utilized a twofold threshold when evaluating whether
a given pixel should be considered "green" and thus replaced. The first
threshold I computed was based on the standard deviation of the distance between
the average background (green) pixel and other background (green) pixels.
The threshold was defined as this average distance + 3.5*(the standard deviation
of this distance). In a perfectly normal distribution, the average plus 3*(the
standard deviation) captures over 99% of points within the distribution. In this
case, I wanted slightly higher accuracy, so increased the Std Dev's multiple
to 3.5. As such, any pixels within a distance (DistanceAvg + 3.5(distStdDev))
are considered green. This method is advantageous where the picture is generally
uniform across the picture, because the equation takes into consideration
the uniformity of "green" pixels with both the average distance and distance
standard deviation.

The problem with the above method is that if variation exists on the background
between the edge of the screen (from which the average is computed) and further
into the picture, some inner green pixels will fall outside the threshold. To
adjust for this, I also computed another threshold that is equal to the average
distance between every pixel on the image and the average background pixel.
Any pixel within this distance distanceAvgTot is also considered green. The
reason that this holds is because our images contain both a large number of
green pixels (which will be RGB spatially close to the average green pixel) and
a large number of non-green pixels (which will be RGB spatially far from the
average green pixels). The average distance will thus be between the distance
of most green pixels and the distance of most other pixels, and any points
below this second threshold will also be considered green.

I also considered a method that would find the maximum and minimum for each of
the RGB values, then would use an equation to adjust for tints and shades
based on these values. I ended up opting not to execute this method because
I felt it could be unduly influenced by outliers should they exist. A better
way to implement such a method may involve finding medians for each of the
RGB values. I also considered somehow developing a method that would detect
edges in the input image, which could help smooth out the pixels surrouunding
the foreground image. However, I realized that there was no easy way to help the
computer distinguish between edges between, on the one hand, the foreground
and green background, and on the other, edges within the foreground itself.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: About 7 hours.

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

: A large portion of my time was spent trying to increase the accuracy of my
method 2.  Especially around the perimeter of the bird, my method 2 wasn't
catching some green pixels, leading to a green outline around the figure. If I
adjusted my DistanceAvg/DistStdDev equation to broaden the definition of green,
other images suffered because the foreground would be classified as green and
thus replaced. I eventually solved the problem by introducing my second
threshold, which also compared pixels to the average distance of every pixel.

Do you have any other remarks?

: N/A
