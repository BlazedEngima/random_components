#!/bin/bash

# Exit script on error
set -e

# Catch errors in pipes
set -o pipefail

# Check if the installation directory is not empty
if [ "$(ls -A lib/mysql-cpp-connector)" ]; then
   echo "Directory lib/mysql-cpp-connector is not empty, exiting"
   exit 0
fi

# Remove the cloned repository on exit
trap 'rm -rf mysql-connector-cpp' EXIT

# Clone the mysql-connector-cpp repository
git clone https://github.com/mysql/mysql-connector-cpp.git

# Navigate into the cloned repository
cd mysql-connector-cpp

# Create the installation directory if it doesn't exist
mkdir -p ../lib/mysql-cpp-connector

# Configure the project
cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=../lib/mysql-cpp-connector \
    -DCMAKE_INSTALL_LIBDIR=lib \
    -DCMAKE_INSTALL_INCLUDEDIR=include \
    -- -j4

# Build the project
cmake --build build

# Install the project
cmake --install build


cd ..
rm -rf mysql-connector-cpp
