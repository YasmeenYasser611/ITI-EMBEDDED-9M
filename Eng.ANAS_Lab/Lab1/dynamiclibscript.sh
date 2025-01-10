#!/bin/bash

# Define directories
BUILD_DIR="1_build"
LIB_DIR="4_dynamic_lib"
OBJ_DIR="3_obj"

# Create directories if they don't exist
mkdir -p $BUILD_DIR $LIB_DIR $OBJ_DIR

# Now call run.sh to perform any additional actions
if [ -f "Logs/run.sh" ]; then
    echo "Calling run.sh..."
    /home/yasmeen/ITI_9M_EMBEDDED_systems/ITI-EMBEDDED-9M/Eng.ANAS_Lab/Lab1/Logs/run.sh  # Run the script
else
    echo "run.sh not found in Logs directory!"
fi

# Compile object files from source files and place them in the obj directory
aarch64-rpi3_Yasmeen-linux-gnu-gcc -c Source/Pressure.c -o $OBJ_DIR/Pressure.o -I Includes
aarch64-rpi3_Yasmeen-linux-gnu-gcc -c Source/Temp.c -o $OBJ_DIR/Temp.o -I Includes
aarch64-rpi3_Yasmeen-linux-gnu-gcc -c main.c -o $OBJ_DIR/main.o -I Includes

# Create dynamic libraries from object files and place them in the lib directory
aarch64-rpi3_Yasmeen-linux-gnu-gcc -shared -fPIC -o $LIB_DIR/libTemp.so $OBJ_DIR/Temp.o
aarch64-rpi3_Yasmeen-linux-gnu-gcc -shared -fPIC -o $LIB_DIR/libPressure.so $OBJ_DIR/Pressure.o

# Link main.c with the dynamic libraries and place the executable in the build directory
aarch64-rpi3_Yasmeen-linux-gnu-gcc -o $BUILD_DIR/Dynamicapp.elf $OBJ_DIR/main.o $LIB_DIR/libPressure.so $LIB_DIR/libTemp.so

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful! Executable: $BUILD_DIR/Dynamicapp.elf"
else
    echo "Build failed."
fi
