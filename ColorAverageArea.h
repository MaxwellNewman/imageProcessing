#include <sys/types.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "stdlib.h"
#include <time.h>

class ColorAverageArea{
public:
	ColorAverageArea(uint row, uint col, unsigned char radius);
	unsigned char findAverageColor(unsigned char*** colorArray);
	void setColor(uint color);
	std::pair<uint,uint> selectRandomCell();

private:
	uint minimumRow;
	uint minimumCol;
	uint maximumRow;
	uint maximumCol;
	uint totalArea;
	uint color;
	unsigned char radius;
	const int IMAGE_SIZE = 256;

	void findLimits(uint row, uint col);
	uint computeColorSum(unsigned char*** colorArray);
	uint selectRandomRow();
	uint selectRandomColumn();
};