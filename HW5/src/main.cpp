#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

const std::string IMAGES_PATH = "/home/babico/Projects/CMPE464-Github/HW5/images/";
const int 		  IMAGES_NUM  = 80;

int main()
{
	cv::Mat imagesSum;

	// Get the sum of all images
	for (size_t i = 1; i <= IMAGES_NUM; i++)
	{
		// Load the image as colored
		cv::Mat img = cv::imread(IMAGES_PATH + "PIC" + std::to_string(i) + ".jpg", cv::IMREAD_COLOR);

		// Check sum image is initialized. If not, initialize as same size with the first image
		if (imagesSum.empty())
		{
			// Initialize imagesSum with the same size and type as img, but filled with zeros and 32-bit float
			imagesSum = cv::Mat::zeros(img.size(), CV_32FC3);
		}
		// Convert the image to 32-bit float
        cv::Mat imgFloat;
        img.convertTo(imgFloat, CV_32FC3);

		// Sum all images pixel-wise
        imagesSum += imgFloat;
	}

	// Calculate the average of all images
	imagesSum = imagesSum / (double)IMAGES_NUM;

    // Convert the averaged image to 8-bit for more sharpness
    cv::Mat _8bitImage;
	imagesSum.convertTo(_8bitImage, CV_8UC3);

	// Convert the averaged image to 16-bit for more precision
	cv::Mat _16bitImage;
	imagesSum.convertTo(_16bitImage, CV_16UC3);

	// Convert the averaged image to 64-bit for more precision
	cv::Mat _64bitImage;
	imagesSum.convertTo(_64bitImage, CV_64FC3);

	// Save the results
	cv::imwrite(IMAGES_PATH + "average_image_8bit.jpg", _8bitImage);
	cv::imwrite(IMAGES_PATH + "average_image_16bit.jpg", _16bitImage);
	cv::imwrite(IMAGES_PATH + "average_image_32bit.jpg", imagesSum);

	// Log the results
	std::cout << "Average image is saved as average_image_8bit.jpg, average_image_16bit.jpg and average_image_32bit.jpg" << std::endl;

	return 0;
}