#include "BlurryMethod.h"
#include "ColorAverageArea.h"

class AreaAverageMethod : public BlurryMethod {
public:
	AreaAverageMethod();
	void makeBlurry();
	void setColorRadius(unsigned char colorRadius);
private:
	unsigned char colorRadius;
	unsigned char findColorAverageOf(ColorAverageArea* currentArea, unsigned char*** colorArray, uint color);
	void averageSingleCell(uint row, uint col);
};