#include <iostream>
#include "Histogram/Histogram.hpp"
#include <matplot/matplot.h>

// Necessary for this project
const std::string IMAGES_PATH = "/home/babico/Projects/CMPE464-Github/HW2/images/";

// int main(int argc, char const *argv[])
int main()
{
	using namespace matplot;
	// Array of images
	std::vector<Histogram> images = {
		Histogram(),
		Histogram(IMAGES_PATH, "city.jpg", 256, {0, 255}),
		Histogram(IMAGES_PATH, "soldier.bmp", 256, {0, 255}),
	};
	// Calculate histograms of all images
	for (auto& image : images) {
		// Calculate histogram of image
		image.calculateHistogram();

		// Equalize the image
		image.equalize();
		// Calculate histogram of equalized image
		image.calculateEqualizedHistogram();

		// Local Equalize the image
		image.localEqualize();
		// Calculate histogram of local equalized image
		image.calculateLocalEqualizedHistogram();
	}

	// Save images
	for (auto const& image : images) {
		// Create folder for images
		std::string image_name = image.getImageName().substr(0, image.getImageName().find("."));
		std::string IMAGE_PATH = IMAGES_PATH + image_name + "/";
		std::string command = "mkdir -p " + IMAGE_PATH;
		system(command.c_str());

		// Matplot++ instance
		auto plotinstance = matplot::figure(true);

		// Create plot for histogram
		plot(image.getPlotXCoordinates(), image.getPlotYCoordinates(image.getHistogram()));
		plotinstance->save(IMAGE_PATH + "histogram_" + image_name + ".png");

		// Save equalized image
		cv::imwrite(IMAGE_PATH + "equalized_" + image_name + ".png", image.getEqualizedImage());

		// Save equalized histogram of image
		plot(image.getPlotXCoordinates(), image.getPlotYCoordinates(image.getEqualizedHistogram()));
		plotinstance->save(IMAGE_PATH + "equalized_histogram_" + image_name + ".png");

		// Save local equalized image
		cv::imwrite(IMAGE_PATH + "equalized_local_" + image_name + ".png", image.getEqualizedLocalImage());

		// Save local equalized histogram of image
		plot(image.getPlotXCoordinates(), image.getPlotYCoordinates(image.getEqualizedLocalHistogram()));
		plotinstance->save(IMAGE_PATH + "equalized_local_histogram_" + image_name + ".png");
	}

	return 0;
}
