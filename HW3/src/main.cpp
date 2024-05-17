#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <matplot/matplot.h>

// Necessary for this project

class NoisyImage
{
public:
	std::string image_ext;
	std::string image_name;

	int HISTOGRAM_SIZE = 256;
	std::array<float, 2> RANGE[2] = {0, 255};

	cv::Mat denoised_image;

	cv::Mat image;
	cv::Mat image_gray;
	cv::Mat image_histogram;
	cv::Mat image_bgr_channels[3];

	cv::Rect selected_part;
	cv::Mat selected_part_image;
	cv::Mat selected_part_image_bgr_channels[3];
	cv::Mat selected_part_image_histogram;

	NoisyImage() {}
	NoisyImage(std::string _image_path, std::string _image_name, cv::Rect _selected_part) : selected_part(_selected_part)
	{
		// Get the image name and extension
		this->image_name = _image_name.substr(0, _image_name.find("."));
		this->image_ext = _image_name.substr(_image_name.find("."), _image_name.size());

		// Read the image
		this->image = cv::imread(_image_path + this->image_name + this->image_ext, cv::IMREAD_COLOR);

		// Convert image to gray
		cv::cvtColor(this->image, this->image_gray, cv::COLOR_BGR2GRAY);

		// Split image into bgr channels
		cv::split(this->image_gray, this->image_bgr_channels);

		// Get the selected part of the image
		this->selected_part_image = this->image_gray(this->selected_part);

		// Split selected part image into bgr channels
		cv::split(this->selected_part_image, this->selected_part_image_bgr_channels);

		// Calculate histogram of image
		std::array<const float *, 1> histRange = {this->RANGE->data()};
		cv::calcHist(&this->image_bgr_channels[0], 1, 0, cv::Mat(), this->image_histogram, 1, &this->HISTOGRAM_SIZE, histRange.data());

		// Calculate histogram of selected part of image
		cv::calcHist(&this->selected_part_image_bgr_channels[0], 1, 0, cv::Mat(), this->selected_part_image_histogram, 1, &this->HISTOGRAM_SIZE, histRange.data());
	}
	// Get X coordinates for histogram
	std::vector<int> getPlotXCoordinates() const
	{
		// Create x coordinates
		std::vector<int> x(256);
		for (int i = 0; i < 256; ++i)
		{
			x[i] = i;
		}

		return x;
	}
	// Get Y coordinates for histogram
	std::vector<double> getPlotYCoordinates(cv::Mat hist) const
	{
		// Create plot data
		std::vector<double> y;
		for (int i = 0; i < 256; ++i)
		{
			y.push_back(hist.at<float>(i));
		}

		return y;
	}

	~NoisyImage() {}
};

// int main(int argc, char const *argv[])
int main()
{
	using namespace matplot;
	const std::string IMAGES_PATH = "/home/babico/Projects/CMPE464-Github/HW3/images/";

	std::vector<NoisyImage> noisy_images = {
		NoisyImage(IMAGES_PATH, "noisy1.jpg", cv::Rect(325, 100, 450 - 325, 300 - 100)),
		NoisyImage(IMAGES_PATH, "noisy2.jpg", cv::Rect(0, 0, 115, 415)),
		NoisyImage(IMAGES_PATH, "noisy3.jpg", cv::Rect(0, 0, 112, 48)),
		NoisyImage(IMAGES_PATH, "noisy4.jpg", cv::Rect(0, 450, 200, 50)),
		NoisyImage(IMAGES_PATH, "noisy5.jpg", cv::Rect(0, 0, 224, 78)),
	};

	// Create a histogram for each image
	for (auto &noisy_image : noisy_images)
	{
		// Matplot++ instance
		auto plotinstance = figure(true);

		// Create plot for histogram
		plot(noisy_image.getPlotXCoordinates(), noisy_image.getPlotYCoordinates(noisy_image.image_histogram));
		plotinstance->save(IMAGES_PATH + "histogram_" + noisy_image.image_name + ".png");

		// Save selected part of image
		cv::imwrite(IMAGES_PATH + "selected_part_" + noisy_image.image_name + ".png", noisy_image.selected_part_image);

		// Create plot for histogram of selected part of image
		plot(noisy_image.getPlotXCoordinates(), noisy_image.getPlotYCoordinates(noisy_image.selected_part_image_histogram));
		plotinstance->save(IMAGES_PATH + "selected_part_histogram_" + noisy_image.image_name + ".png");
	}

	// noisy1, noisy3 and noisy5 rayleigh noise denoising with wavelet denoising
	cv::fastNlMeansDenoising(noisy_images[0].image, noisy_images[0].denoised_image, 20, 4);
	cv::imwrite(IMAGES_PATH + "denoised_" + noisy_images[0].image_name + ".png", noisy_images[0].denoised_image);

	cv::fastNlMeansDenoising(noisy_images[2].image, noisy_images[2].denoised_image, 20, 4);
	cv::imwrite(IMAGES_PATH + "denoised_" + noisy_images[2].image_name + ".png", noisy_images[2].denoised_image);

	cv::fastNlMeansDenoising(noisy_images[4].image, noisy_images[4].denoised_image, 20, 4);
	cv::imwrite(IMAGES_PATH + "denoised_" + noisy_images[4].image_name + ".png", noisy_images[4].denoised_image);

	// noisy2 and noisy4 gaussian noise denoising with gaussian filter
	cv::GaussianBlur(noisy_images[1].image, noisy_images[1].denoised_image, cv::Size(5, 5), 0);
	cv::imwrite(IMAGES_PATH + "denoised_" + noisy_images[1].image_name + ".png", noisy_images[1].denoised_image);

	cv::GaussianBlur(noisy_images[3].image, noisy_images[3].denoised_image, cv::Size(5, 5), 0);
	cv::imwrite(IMAGES_PATH + "denoised_" + noisy_images[3].image_name + ".png", noisy_images[3].denoised_image);

	return 0;
}