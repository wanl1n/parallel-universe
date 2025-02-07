#include "RTImage.h"

RTImage::RTImage(const int imageWidth, const int imageHeight)
{
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;

	// In OpenCV, RGB images are written as BGR.
	this->pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(this->imageHeight, this->imageWidth, CV_8UC3));
}

void RTImage::setPixel(int x, int y, int r, int g, int b)
{
    this->guard.lock();

    cv::Mat imgChannels[3];
    cv::split(*this->pixels, imgChannels);

    imgChannels[0].at<uchar>(this->imageHeight - 1 - y, x) = b;
    imgChannels[1].at<uchar>(this->imageHeight - 1 - y, x) = g;
    imgChannels[2].at<uchar>(this->imageHeight - 1 - y, x) = r;

    cv::merge(imgChannels, 3, *this->pixels);

    this->guard.unlock();
}

void RTImage::saveImage(cv::String& fileName)
{
    this->guard.lock();

    cv::Mat finalImage;
    cv::flip(*this->pixels, finalImage, 0);
    cv::imwrite(fileName, finalImage);

    this->guard.unlock();
}
