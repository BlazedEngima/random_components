# Use the Fedora Minimal image
FROM registry.fedoraproject.org/fedora-minimal:latest

# Install necessary dependencies
RUN microdnf -y update && microdnf install -y \
    gcc \
    gcc-c++ \
    cmake \
    make \
    openssl-devel \
    libcurl-devel \
    websocketpp-devel \
    && microdnf clean all

# Set the working directory in the Docker image
WORKDIR /app

# Copy the current directory contents into the Docker image
COPY . /app

# Run make clean to build the project
RUN make clean

# Set the command to run your application when the Docker container starts
CMD ["build/listener", "config.json"]