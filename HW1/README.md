# Homework #01

## Homework Instruct

For a given image (a sample image is given (peppers.png), or you may use an image that you wish). For the given image, do the followings:

- First of all resize the images to 256x256 pixels.
- Convert to images to grayscale.
- Convert to images to binary using different thresholds.
- Tile the image to form 4 quadrants where – The top left quadrant is the original image, The top right is the red channel of the original image,  The bottom left is the green channel. The bottom right is the blue channel (other channels set to zero).
- Then, write a short paragraph explaining your results. What do you see when you plot  red / green / blue channels separetely? Why=

Secondly, produce the symmetry of the input image according to the

- midline on the vertical axis.
- midline on the horizontal axis.

## Prerequisite

Please note that the specified versions are not definitive, as the code has not been tested with other versions of the prerequisites. But it is still recommended to use the specified versions. However, it is important to note that this code will not work on Windows as CMake is not configured for it.

- OpenCV ^4.9.0
- g++ ^13.0.0
- cmake ^3.27.0
- Ubuntu 23.10

## Build

```bash
mkdir build
cd build
cmake ..
make
cd ..
```

## Run

```bash
cd bin
./main
```
