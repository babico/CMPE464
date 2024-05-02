#include "Histogram.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

// Default constructor with random image
Histogram::Histogram() : image_path{"../images/"}, image_name("random_image.jpg"), HISTOGRAM_SIZE(256)
{
	// Check if image path exists
	if (this->image_path.empty())
	{
		// Create folder for images
		std::string command = "mkdir -p " + this->image_path;
		system(command.c_str());
	}

	// Fill image with random values
	cv::randu(this->image, cv::Scalar::all(0), cv::Scalar::all(255));

	// Save image
	cv::imwrite(this->image_path + this->image_name, this->image);

	// Split image into bgr channels
	cv::split(this->image, this->bgr_channels);
}
// Constructor with parameters
Histogram::Histogram(std::string const &_image_path, std::string const &image_name, int HISTOGRAM_SIZE, std::array<float, 2> const &_RANGE)
	: image_path{_image_path}, image_name{image_name}, HISTOGRAM_SIZE{HISTOGRAM_SIZE}, RANGE{_RANGE}
{
	// Read image
	this->image = cv::imread(this->image_path + this->image_name, cv::IMREAD_COLOR);

	// Split image into bgr channels
	cv::split(this->image, this->bgr_channels);
}

// Convert image to grayscale
void Histogram::convertToGrayscale()
{
	// Convert image to grayscale
	cv::cvtColor(this->image, this->gray_image, cv::COLOR_BGR2GRAY);
}

// Calculate histogram
void Histogram::calculateHistogram()
{
	// Calculate histogram of image
	std::array<const float *, 1> histRange = {this->RANGE->data()};
	cv::calcHist(&this->bgr_channels[0], 1, 0, cv::Mat(), this->normal_histogram, 1, &this->HISTOGRAM_SIZE, histRange.data());
}

// Equalize image
void Histogram::equalize()
{
	// Convert image to grayscale
	this->convertToGrayscale();

	// Equalize histogram of image
	cv::equalizeHist(this->gray_image, equalized_image);
}
// Calculate histogram of equalized image
void Histogram::calculateEqualizedHistogram()
{
	// Calculate histogram of equalized image
	std::array<const float *, 1> histRange = {this->RANGE->data()};
	cv::calcHist(&this->equalized_image, 1, 0, cv::Mat(), this->equalized_histogram, 1, &this->HISTOGRAM_SIZE, histRange.data());
}

// Local Equalize histogram
void Histogram::localEqualize()
{
	// Convert image to grayscale
	this->convertToGrayscale();

	// Apply local histogram equalization to the image
	// Create a CLAHE object with 4.0 contrast limiting factor and 8x8 grid size
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(4.0, cv::Size(8, 8));
	clahe->setClipLimit(4); // Set the clip limit for contrast limiting

	// Apply local histogram equalization to the image
	clahe->apply(this->gray_image, this->equalized_local_image);
}
// Calculate histogram of local equalized image
void Histogram::calculateLocalEqualizedHistogram()
{
	// Calculate histogram of local equalized image
	std::array<const float *, 1> histRange = {this->RANGE->data()};
	cv::calcHist(&this->equalized_local_image, 1, 0, cv::Mat(), this->equalized_local_histogram, 1, &this->HISTOGRAM_SIZE, histRange.data());
}

// Get Image Name
std::string Histogram::getImageName() const
{
	return this->image_name;
}
// Get Image
cv::Mat Histogram::getImage() const
{
	return this->image;
}
// Get histogram
cv::Mat Histogram::getHistogram() const
{
	return this->normal_histogram;
}

// Get Equalized Image
cv::Mat Histogram::getEqualizedImage() const
{
	return this->equalized_image;
}
// Get Equalized Histogram
cv::Mat Histogram::getEqualizedHistogram() const
{
	return this->equalized_histogram;
}

// Get Equalized Local Image
cv::Mat Histogram::getEqualizedLocalImage() const
{
	return this->equalized_local_image;
}
// Get Equalized Local Histogram
cv::Mat Histogram::getEqualizedLocalHistogram() const
{
	return this->equalized_local_histogram;
}

// Get X coordinates for histogram
std::vector<int> Histogram::getPlotXCoordinates() const
{
	// Create x coordinates
	std::vector<int> x(this->HISTOGRAM_SIZE);
	for (int i = 0; i < this->HISTOGRAM_SIZE; ++i)
	{
		x[i] = i;
	}

	return x;
}
// Get Y coordinates for histogram
std::vector<double> Histogram::getPlotYCoordinates(cv::Mat hist) const
{
	// Create plot data	
	std::vector<double> y;
	for (int i = 0; i < this->HISTOGRAM_SIZE; ++i)
	{
		y.push_back(hist.at<float>(i));
	}

	return y;
}