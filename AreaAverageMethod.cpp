#include "AreaAverageMethod.h"

AreaAverageMethod::AreaAverageMethod():BlurryMethod(){
	setColorRadius(0);
}

AreaAverageMethod::AreaAverageMethod(unsigned char colorRadius):BlurryMethod(){
	setColorRadius(colorRadius);
}

void AreaAverageMethod::makeBlurry(){
	for(uint i=0; i<IMAGE_SIZE; ++i){
		for(uint j=0; j<IMAGE_SIZE; ++j){
			averageSingleCell(i, j);
		}
	}
}

void AreaAverageMethod::setColorRadius(unsigned char colorRadius){
	this->colorRadius = colorRadius;
}

unsigned char AreaAverageMethod::findColorAverageOf(ColorAverageArea* currentArea, unsigned char*** colorArray, uint color){
	currentArea->setColor(color);
	unsigned char colorAverage = currentArea->findAverageColor(inputImage);
	return colorAverage;
}

void AreaAverageMethod::averageSingleCell(uint row, uint col){
	ColorAverageArea* currentArea = new ColorAverageArea(row, col, colorRadius);

	outputImage[row][col][RED] = findColorAverageOf(currentArea, inputImage, RED);
	outputImage[row][col][GREEN] = findColorAverageOf(currentArea, inputImage, GREEN);
	outputImage[row][col][BLUE] = findColorAverageOf(currentArea, inputImage, BLUE);
}