#include "blurry.h"

int main(){
	std::string inputImage = getInputImageName();
	std::string outputImage = getOutputImageName():

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