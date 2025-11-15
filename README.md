# QEMU-TEST

This is mainly a test repo for messing around with embedded development using QEMU.

## Requirements
docker-compose

## How to Use
1. `sudo ./container.sh` to initialize the development environment.
2. `make` to build the firmware.
3. `make qemu` to run the firmware on emulated hardware.
4. `make disasm` to view the raw assembly.
