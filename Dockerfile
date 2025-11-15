FROM ubuntu:22.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install basic tools and ARM toolchain
RUN apt-get update && apt-get install -y \
    gcc-arm-none-eabi \
    gdb-multiarch \
    qemu-system-arm \
    make \
    git \
    vim \
    nano \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]
