#include <string>
#include <iostream>
#include "blurry.h"
#include "AreaAverageMethod.h"
#include "bmplib.h"

int main(){
	std::string inputFilename = getInputImageName();
	std::string outputFilename = getOutputImageName();

	unsigned char radius = 3;
	BlurryMethod* blurry = new AreaAverageMethod(radius);

	blurry->setInputFilename(inputFilename);
	blurry->setOutputFilename(outputFilename);
	blurry->readInputImage();
	blurry->makeBlurry();
	blurry->writeOutputImage();
}

std::string getInputImageName(){
	std::string inputImageName = "";
	std::cout << "What image do you want to make blurry?" << std::endl;
	std::cin >> inputImageName;

	return inputImageName;
}

std::string getOutputImageName(){
	std::string outputImageName = "";
	std::cout << "What do you want the name of the output image to be?" << std::endl;
	std::cin >> outputImageName;
	return outputImageName;
}