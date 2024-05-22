#!/bin/bash

# Define directories
SRC_DIR="src"
INCLUDE_DIR="include"
BUILD_DIR="build"

# Create build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Compile source files
g++ -std=c++20 -I $INCLUDE_DIR -o $BUILD_DIR/main $SRC_DIR/*.cpp

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Built successfully."
    echo "_________________________________"
    echo ""
    $BUILD_DIR/main "$@"
else
    echo "Build failed."
fi
