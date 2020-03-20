# Blue Pill Embedded node protocol demo

This project created for demonstration working ENP on blue pill board.
Blue pill is popular board with STMF103 microcontroller.

## Build

Project use gcc-arm-none-eabi compiler.
You can download it [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) 

build:
make -j GCC_PATH="path to arm-gcc-none-eabi/bin" TARGET = bluePill_ENP

if your compiller was added in the path:
make -j TARGET = bluePill_ENP
