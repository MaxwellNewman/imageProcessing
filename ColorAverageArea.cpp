#include "ColorAverageArea.h"
#include <iostream>

ColorAverageArea::ColorAverageArea(uint row, uint col, unsigned char radius){
	this->radius = radius;
	this->color = color;
	findLimits(row, col);

	//std::cout << radius << std::endl;
}

void ColorAverageArea::setColor(uint color){
	this->color = color;
}

void ColorAverageArea::findLimits(uint row, uint col){
	int lowerRow = row-radius;
	int lowerCol = col-radius;
	int upperRow = row+radius;
	int upperCol = col+radius;


	minimumRow = std::max(0, lowerRow);
	minimumCol = std::max(0, lowerCol);
	maximumRow = std::min(IMAGE_SIZE, upperRow);
	maximumCol = std::min(IMAGE_SIZE, upperCol);
	totalArea = (maximumCol - minimumCol) * (maximumRow - minimumRow);
}

uint ColorAverageArea::computeColorSum(unsigned char*** colorArray){
	uint colorSum = 0;

	for(uint i = minimumRow; i<maximumRow; ++i){
		for(uint j = minimumCol; j<maximumCol; ++j){
			colorSum += colorArray[i][j][color];
		}
	}

	return colorSum;
}

unsigned char ColorAverageArea::findAverageColor(unsigned char*** colorArray){
	uint colorSum = computeColorSum(colorArray);

	return colorSum / totalArea;
}