#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

const std::string IMAGES_PATH = "../images/";

int main(int argc, char const *argv[])
{
    // Read soldier.bmp image file
    cv::Mat soldier = cv::imread(IMAGES_PATH + "soldier.bmp", cv::IMREAD_COLOR);

    // Read city.jpg image file
    cv::Mat city = cv::imread(IMAGES_PATH + "city.jpg", cv::IMREAD_COLOR);

    return 0;
}
