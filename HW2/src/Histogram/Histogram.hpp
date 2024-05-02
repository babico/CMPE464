#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

class Histogram
{
private:
    cv::Mat image = cv::Mat(256, 256, CV_8UC3);
    std::string image_path;
    std::string image_name;

    std::vector<cv::Mat> bgr_channels;

    int HISTOGRAM_SIZE;
    std::array<float, 2> RANGE[2] = {0, 255};

    cv::Mat gray_image;
    cv::Mat normal_histogram;

    cv::Mat equalized_image;
    cv::Mat equalized_histogram;

    cv::Mat equalized_local_image;
    cv::Mat equalized_local_histogram;

public:
    // Default constructor with random image
    Histogram();
    // Constructor with parameters
    Histogram(std::string const &_image_path, std::string const &image_name, int HISTOGRAM_SIZE, std::array<float, 2> const &_RANGE);

    // Convert image to grayscale
    void convertToGrayscale();

    // Calculate histogram
    void calculateHistogram();

    // Equalize
    void equalize();
    // Calculate histogram of equalized image
    void calculateEqualizedHistogram();

    // Local Equalize
    void localEqualize();
    // Calculate histogram of local equalized image
    void calculateLocalEqualizedHistogram();

    // Get Image Name
    std::string getImageName() const;
    // Get Image
    cv::Mat getImage() const;
    // Get histogram
    cv::Mat getHistogram() const;

    // Get Equalized Image
    cv::Mat getEqualizedImage() const;
    // Get Equalized Histogram
    cv::Mat getEqualizedHistogram() const;

    // Get Equalized Local Image
    cv::Mat getEqualizedLocalImage() const;
    // Get Equalized Local Histogram
    cv::Mat getEqualizedLocalHistogram() const;

    // Get X coordinates for histogram
    std::vector<int> getPlotXCoordinates() const;
    // Get Y coordinates for histogram
    std::vector<double> getPlotYCoordinates(cv::Mat) const;
};