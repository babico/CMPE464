#include <string>
#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <unordered_map>
#include <opencv2/opencv.hpp>

const int THRESHOLD_MAX = 1024;
const int GRAYSCALE_MAX = 255;
const std::string IMAGES_PATH = "../images/";
const cv::Size size256x256 = cv::Size(256, 256);
const std::string BINARY_IMAGES_PATH = "../images/binary/";
const cv::Mat zeroMatix = cv::Mat::zeros(size256x256, CV_8U); // Zero matrix
const std::vector<cv::Rect> pieces{
	// 4 piece of an image
	cv::Rect(0, 0, 128, 128),	  // top left // (x, y, width, height)
	cv::Rect(128, 0, 128, 128),	  // top right // (x, y, width, height)
	cv::Rect(0, 128, 128, 128),	  // bottom left // (x, y, width, height)
	cv::Rect(128, 128, 128, 128), // bottom right // (x, y, width, height)
};

int main(int argc, char const *argv[])
{
	// Read peppers.png image file
	cv::Mat img = cv::imread(IMAGES_PATH + "_peppers.png", cv::IMREAD_COLOR);

	// Check is image loaded
	if (img.empty())
	{
		std::cerr << "Image load failed!" << std::endl;
		return -1;
	}

	// Print success message and image size
	std::cout << "Image loaded successfully!" << std::endl;
	std::cout << "Image size: " << img.size() << std::endl;

	// Resize image to 256x256
	cv::resize(img, img, size256x256);

	// Save resized image to peppers_resized.png
	cv::imwrite(IMAGES_PATH + "peppers_256x256.png", img);

	// Print success message and image size
	std::cout << "Resized image saved successfully!" << std::endl;
	std::cout << "Image size: " << img.size() << std::endl;

	// Convert image to grayscale
	cv::Mat gray;
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

	// Save grayscale image to peppers_grayscale.png
	cv::imwrite(IMAGES_PATH + "peppers_grayscale.png", gray);

	// Print success message
	std::cout << "Grayscale image saved successfully!" << std::endl;

	// Define matrix
	cv::Mat binaries[THRESHOLD_MAX];

	// Crate folder for binary convertion
	mkdir(BINARY_IMAGES_PATH.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	for (size_t i = 0; i < THRESHOLD_MAX; i++)
	{
		// Convert image to binary using different thresholds
		cv::threshold(img, binaries[i], i, THRESHOLD_MAX, cv::THRESH_BINARY);

		// Save binary converted image
		cv::imwrite(BINARY_IMAGES_PATH + "peppers_threshold_" + std::to_string(i) + ".png", binaries[i]);
	}

	// Print success message
	std::cout << "Threshold images saved successfully!" << std::endl;

	// Get color channels of image
	cv::Mat channels[3]; // color order Blue Green Red
	cv::split(img, channels);

	cv::Mat results[4]; // image order onlyBlue onlyGreen onlyRed
	results[0] = img;
	std::vector<cv::Mat> colors[3]{
		// color order onlyBlue onlyGreen onlyRed
		std::vector<cv::Mat>{zeroMatix, zeroMatix, channels[2]},
		std::vector<cv::Mat>{zeroMatix, channels[1], zeroMatix},
		std::vector<cv::Mat>{channels[0], zeroMatix, zeroMatix},
	};

	for (size_t i = 0; i < 3; i++)
	{
		// Convert vectors to image
		cv::merge(colors[i], results[i + 1]);

		// Save the result
		cv::imwrite(IMAGES_PATH + "peppers_color_filtered_" + std::to_string(i) + "_colors.png", results[i + 1]);
	}

	// Print success message
	std::cout << "Color filtered image saved successfully!" << std::endl;

	// Extract each images squares
	cv::Mat img_pieces[4];
	for (size_t i = 0; i < pieces.size(); i++)
	{
		img_pieces[i] = results[i](pieces[i]);
	}

	// Create a blank image to merge the ROIs onto
	cv::Mat merged_image(size256x256, CV_8UC3);

	// Place each piece onto the appropriate position in the merged image
	for (size_t i = 0; i < pieces.size(); i++)
	{
		img_pieces[i].copyTo(merged_image(pieces[i]));
	}

	// Save merged image
	cv::imwrite(IMAGES_PATH + "peppers_color_merged.png", merged_image);

	// Print success message
	std::cout << "Color filtered merged image saved successfully!" << std::endl;

	// Create a new image with the same dimensions as the input image
	cv::Mat verticalSymmetric(size256x256, img.type());
	cv::Mat horizantalSymmetric(size256x256, img.type());

	// Get left half of the image
	cv::Mat verticalLeftHalf = img(cv::Rect(0, 0, size256x256.width / 2, size256x256.height));

	// Get upper half of the image
	cv::Mat horizontalUpperHalf = img(cv::Rect(0, 0, size256x256.width, size256x256.height / 2));

	// Flip the left half of the image vertically directly to the output image
	cv::flip(verticalLeftHalf, verticalSymmetric(cv::Rect(size256x256.width / 2, 0, size256x256.width / 2, size256x256.height)), 1);
	// Copy left half to output image
	verticalLeftHalf.copyTo(verticalSymmetric(cv::Rect(0, 0, size256x256.width / 2, size256x256.height)));

	// Flip the upper half of the image horizontally to the output image
	cv::flip(horizontalUpperHalf, horizantalSymmetric(cv::Rect(0, size256x256.height / 2, size256x256.width, size256x256.height / 2)), 0);
	// Copy upper half to output image
	horizontalUpperHalf.copyTo(horizantalSymmetric(cv::Rect(0, 0, size256x256.width, size256x256.height / 2)));

	// Save symmetric images
	cv::imwrite(IMAGES_PATH + "peppers_vertical.png", verticalSymmetric);
	cv::imwrite(IMAGES_PATH + "peppers_horizontal.png", horizantalSymmetric);
	
	// Print success message
	std::cout << "Symmetric images saved successfully!" << std::endl;

	return 0;
}
