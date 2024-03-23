#!/bin/bash

# Set the image name
IMAGE_NAME="listener-arm64"

# Run a container from the built image
CONTAINER_NAME="listener"
docker run -d --name $CONTAINER_NAME -p 8080:8080 $IMAGE_NAME