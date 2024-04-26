cmake_minimum_required(VERSION 3.5)
project(HW1)

# Set the directory for the executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include/opencv4")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source file
add_executable(main src/main.cpp)

# Link libraries
target_link_libraries(main 
    opencv_gapi 
    opencv_stitching 
    opencv_aruco 
    opencv_bgsegm 
    opencv_bioinspired 
    opencv_ccalib 
    opencv_dnn_objdetect 
    opencv_dnn_superres 
    opencv_dpm 
    opencv_face 
    opencv_fuzzy 
    opencv_hfs 
    opencv_img_hash 
    opencv_intensity_transform 
    opencv_line_descriptor 
    opencv_mcc 
    opencv_quality 
    opencv_rapid 
    opencv_reg 
    opencv_rgbd 
    opencv_saliency 
    opencv_stereo 
    opencv_structured_light 
    opencv_phase_unwrapping 
    opencv_superres 
    opencv_optflow 
    opencv_surface_matching 
    opencv_tracking 
    opencv_highgui 
    opencv_datasets 
    opencv_text 
    opencv_plot 
    opencv_videostab 
    opencv_videoio 
    opencv_wechat_qrcode 
    opencv_xfeatures2d 
    opencv_shape 
    opencv_ml 
    opencv_ximgproc 
    opencv_video 
    opencv_xobjdetect 
    opencv_objdetect 
    opencv_calib3d 
    opencv_imgcodecs 
    opencv_features2d 
    opencv_dnn 
    opencv_flann 
    opencv_xphoto 
    opencv_photo 
    opencv_imgproc 
    opencv_core
)
