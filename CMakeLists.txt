cmake_minimum_required(VERSION 3.5.1)
project(PiVehicle_FPV)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. SOURCE_FILES)
add_executable(Pi_FPV ${SOURCE_FILES})
