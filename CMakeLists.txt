# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Project name
project(arnold_shader_dev)

# Set the path to the Arnold SDK
set(ARNOLD_PATH "/mnt/c/DEV/arnold_sdk/Arnold-7.2.4.1-linux" CACHE PATH "Path to Arnold SDK")

# Define the shader source file
set(SHADER_SOURCE shaders/simple_shader/simple_shader.cpp)

# Create a shared library for the shader
add_library(simple_shader SHARED ${SHADER_SOURCE})

# Compiler flags
target_compile_options(simple_shader PRIVATE -Wall -O2 -fPIC)

# Include directories
target_include_directories(simple_shader PRIVATE ${ARNOLD_PATH}/include)

# Link against the Arnold library
target_link_libraries(simple_shader PRIVATE ${ARNOLD_PATH}/bin/libai.so)