# Blue Pill Embedded node protocol demo

This project created for demonstration working ENP on blue pill board.
Blue pill is popular board with STMF103 microcontroller.
It simple can help to understand ENP protocol.

# HEX file
You can take compiled hex file in releases folder.
bluePill_last.hex is the last version.

# Quick start
* Download hex file in the BluePill. 
* Connect USB connector to your computer.
* Start EmbeddedNode Configurator.
* Choose the COM port of the bluePill.
* Enter 1 in device ID field and click connect.
* Application have to load node configuration from BluePill.

# Nodes 
Root node is BluePill node. It have 3 field.
* Error code - it is simple field. Id do nothing.
* Device id - Identificator in th ENP network.
* Up time - time from bluePill start.

Led node be able to control led on PC13.
* Mode - 0 is blink. Other value is light solid.
* Delay - delay between toggle PC13.

## Build

Project use gcc-arm-none-eabi compiler.
You can download it [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) 

build:  
make -j GCC_PATH="path to arm-gcc-none-eabi/bin" TARGET = bluePill_ENP

if your compiller was added in the path:  
make -j TARGET = bluePill_ENP
