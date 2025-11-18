FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install ARM toolchain, qemu and other useful tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    gdb-multiarch \
    qemu-system-arm \
    make \
    git \
    vim \
    nano \
    curl \
    ca-certificates \
    procps \
    && rm -rf /var/lib/apt/lists/*

ARG GCC_URL=https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz

# Download and install the ARM GNU toolchain
RUN wget -q "$GCC_URL" -O /tmp/arm-none-eabi-gcc.tar.xz && \
    cd /tmp && \
    tar -xf arm-none-eabi-gcc.tar.xz && \
    mv arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi /opt/arm-none-eabi-gcc && \
    rm /tmp/arm-none-eabi-gcc.tar.xz && \
    rm -rf /tmp/*

# Add toolchain to PATH
ENV PATH="/opt/arm-none-eabi-gcc/bin:$PATH"

WORKDIR /workspace

# Use the container's default shell for interactive use
CMD ["/bin/bash"]
