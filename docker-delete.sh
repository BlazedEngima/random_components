#!/bin/bash

# Set the container name
CONTAINER_NAME="listener"

# Stop the Docker container
docker stop $CONTAINER_NAME

# Remove the Docker container
docker rm $CONTAINER_NAME