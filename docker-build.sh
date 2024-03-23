#!/bin/bash

IMAGE_NAME="listener-arm64"

export DOCKER_CLI_EXPERIMENTAL=enabled

# Create a new builder instance
docker buildx create --use --name builder

# Initialize the builder instance
docker buildx inspect --bootstrap

# Register QEMU with Docker
docker run --rm --privileged multiarch/qemu-user-static --reset -p yes

# Build the Docker image
docker buildx build --platform linux/arm64 -t $IMAGE_NAME . --load
