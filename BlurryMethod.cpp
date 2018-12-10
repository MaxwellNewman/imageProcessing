#include "BlurryMethod.h"

void BlurryMethod::makeBlurry(){
	//nothing
}

BlurryMethod::BlurryMethod(){
	inputImage = new unsigned char**[IMAGE_SIZE];
	outputImage = new unsigned char**[IMAGE_SIZE];

	for(uint i=0; i<IMAGE_SIZE; ++i){
		inputImage[i] = new unsigned char* [IMAGE_SIZE];
		outputImage[i] = new unsigned char* [IMAGE_SIZE];

		for(uint j=0; j<IMAGE_SIZE; ++j){
			inputImage[i][j] = new unsigned char[RGB];
			outputImage[i][j] = new unsigned char[RGB];

			for(uint k=0; k<RGB; ++k){
				inputImage[i][j][k] = 0;
				outputImage[i][j][k] = 0;
			}
		}
	}


	//inputImage = new unsigned char[IMAGE_SIZE][IMAGE_SIZE][RGB];
	//outputImage = new unsigned char[IMAGE_SIZE][IMAGE_SIZE][RGB];
}

void BlurryMethod::convertFilenameToInputImage(std::string filename){
	if(readRGBBMP(filename.c_str(), inputImage)){
		std::cout << "Error reading file: " << filename << std::endl;
	}
}

void BlurryMethod::setInputFilename(std::string inputFilename){
	this->inputFilename = inputFilename;
}

void BlurryMethod::setOutputFilename(std::string outputFilename){
	this->outputFilename = outputFilename;
}

bool BlurryMethod::readInputImage(){
	if(readRGBBMP(inputFilename.c_str(), inputImage)){
		std::cout << "Error reading input file: " << inputFilename << std::endl;
		return false;
	}
	return true;
}

bool BlurryMethod::writeOutputImage(){
	if(writeRGBBMP(outputFilename.c_str(), outputImage)){
		std::cout << "Error writing to output file: " << outputFilename << std::endl;
		return false;
	}
	return true;
}