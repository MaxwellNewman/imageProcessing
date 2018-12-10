#include <string>
#include <iostream>
#include "bmplib.h"

class BlurryMethod{
public:
	unsigned char*** inputImage;
	unsigned char*** outputImage;

	BlurryMethod();
	virtual void makeBlurry();
	void convertFilenameToInputImage(std::string filename);
	void setInputFilename(std::string inputFilename);
	void setOutputFilename(std::string outputFilename);
	bool readInputImage();
	bool writeOutputImage();

private:
	std::string inputFilename;
	std::string outputFilename;
};