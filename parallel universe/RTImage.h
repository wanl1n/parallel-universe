#pragma once
#include "opencv2/core.hpp"
#include <opencv2/imgcodecs.hpp> 

class RTImage
{
public:
	RTImage(const int imageWidth, const int imageHeight);
	void setPixel(int x, int y, int r, int g, int b);
	void saveImage(cv::String& fileName) const;

private:
	std::unique_ptr<cv::Mat> pixels;
	int imageWidth;
	int imageHeight;
};

