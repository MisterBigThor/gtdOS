# GTDos: basic OS for the Raspberry Pi 

In this project I'm going to develop and test a real time OS that run pre-compiled tasks in a round robin scheduling. 

For achieve this, we need some configuration for:

* UART communication 

* API to work with the GPIO pins
* Memory Managment

* Timers and interrupts managment

* Task managment and scheduling

* Support for multithreading (In a future).

[USB Drivers from rsta2](https://github.com/rsta2/uspi)

# Developing enviroment

### Compiling, emulating and debugging
To compile is necessary a cross-compiler, because the architecture is diferent than my developing enviroment. For this project I'm going to use the aarch64-elf-gcc, but any other cross-compiler that can target the aarch64 will work.

The compiler output is a .elf, we will need to convert this file to a .img file for use in the real raspi.

For emulating, is needed a diferent linker file because QEMU loads the kernel at address 0x80000

The lastest versions of QEMU-aarch64 emulates raspi2 and raspi3 models. In my experience, with the 2.12.0 version of the QEMU the same image of the OS didn't works equaly respect the real raspi3.
Every directory contains a file to run the qemu.
````
qemu-system-aarch64 -M raspi3 -kernel kernel-qemu.img -serial stdio
````
For debugging I'm going to use the gdb (with multiarch support). For setup a debug session is important to compile with the -g flag (generates debugging info) and stop the QEMU before the execution of the first instruction (with -s -S options).
````
qemu-system-aarch64 -s -S -M raspi3 -kernel kernel-qemu.img -serial stdio &
gdb-multiarch
(gdb) target-remote localhost:1234
(gdb) file ~/build/kernel-qemu.elf
(gdb) continue
````

# Rasberry Pi start-up
In my particular case, I'm working with the Raspberry Pi 3 Model B (rev. 1.2). In this model, the booting process reads from the SD card the kernel8.img file. 

Inside this file there is the code of the OS to be executed. With this information, we can work with the assembler and C to boot a hello world. 

The peripherals/devices included in the board are mapped in the memory following the reference of the ARM peripherals manual [ARM peripheral manual](documentation/BCM2835-ARM-Peripherals.pdf).

In the following sections I go further with the diferent components to complete an OS interface.

# Stages of development

### [UART and GPIO](/01_UART/uart.md)

### [Multicore](/02_MULTICORE/multicore.md)

### [Entry the OS](/03_ENTRY/entry.md)

For setting up the periphericals of the Raspi, I have read the documentation for the [BCM 2835](/documentation/BCM2835-ARM-Peripherals.pdf), the model of my raspberry.
...

For the GPIO I wrote a simple library, according to the reference BCM manual, to manage the functionality.
#### [SCHEDULING](/04_SCHED/sched.md)


# bibliography and reference
Some code is from the following repositories:

* [Matyukevich repo](https://github.com/s-matyukevich/raspberry-pi-os) there is a design for a Raspberry pi general porpuse OS.

* [bztsrc repo](https://github.com/bztsrc/raspi3-tutorial) contains some OS concepts.

In the other hand, the round robin scheduling implementation is from [ZeOS-SO2](https://github.com/MisterBigThor/so2FIB), a OS designed and developed for a subject int UPC-Facultat Informatica de Barcelona.
