#!/bin/bash

# Create a build directory if it doesn't exist
mkdir -p build
cd build

# Configure the project with CMake (adjust your CMake options as needed)
cmake ..

# Build the project with make (you can specify the number of CPU cores with -j)
make -j

cd ..
# Run the application (replace 'your_application' with the actual executable name)
./run.sh
