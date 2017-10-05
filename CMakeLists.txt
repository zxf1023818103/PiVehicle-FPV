cmake_minimum_required(VERSION 3.5.1)
project(PiVehicle_FPV)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} cmake)

set(SRC_FPV_CAMERA pifpv.h IFpvCamera.h IFpvCamera.cc)
set(SRC_FPV_ENCODER query_fpv_encoder.cc)
set(SRC_FPV_STREAMSERVER query_fpv_stream_server.cc)

if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(SRC_FPV_CAMERA ${SRC_FPV_CAMERA} query_fpv_camera_windows.cc create_fpv_camera_windows.cc)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(SRC_FPV_CAMERA ${SRC_FPV_CAMERA} query_fpv_camera_linux.cc create_fpv_camera_linux.cc
            FpvCameraLinux.h FpvCameraLinux.cc)
else()
    message(FATAL_ERROR "Sytem Not Supported: " ${CMAKE_SYSTEM_NAME})
endif()

add_library(fpv_camera STATIC ${SRC_FPV_CAMERA})
add_library(fpv_encoder STATIC ${SRC_FPV_ENCODER})
add_library(fpv_stream_server STATIC ${SRC_FPV_STREAMSERVER})

add_executable(pifpvd main.cc)
target_link_libraries(pifpvd fpv_camera fpv_encoder fpv_stream_server)
