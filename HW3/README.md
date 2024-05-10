# Homework #03

## Homework Instruct

Enclosed you will find five images (noisy1.jpg, ... noisy5.jpg). For the given noisy images; apply image enhancement techniques to obtain a more suitable image for visual perception.

Write your comments about the results...

## Prerequisite

Please note that the specified versions are not definitive, as the code has not been tested with other versions of the prerequisites. But it is still recommended to use the specified versions. However, it is important to note that this code will not work on Windows as CMake is not configured for it.

- OpenCV ^4.9.0
- g++ ^13.0.0
- cmake ^3.27.0
- Ubuntu 23.10

## Release 

### Compile

```bash
mkdir release
cd release
cmake ..
make -j$(nproc)
```

### Run

```bash
cd bin
./main
```

## Debug

### Compile

```bash
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=debug ..
make -j$(nproc)
```

### Run

```bash
cd bin
./main
```