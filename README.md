# gtdOS: basic OS for the Raspberry Pi 

In this project is I'm going to develop and test a real time OS, with this features:



# Developing enviroment
For develop an OS, certain tools needed:

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

# Rasberry Pi specifications
In my particular case, I'm working with the Raspberry Pi 3 Model B (rev. 1.2). In this section I will make an introducction to the architecure details.
* Boot partition: The raspi load into memory a file like kernelX.img. If X = 8 then the raspi boots in 64 bits mode.
* Booting: The raspi boots through the GPU, the startup sequence can be modified by the config.txt. This method replace a UEFI/BIOS.
* The peripherals are mapped in memory.

With this information, we can work with the assembler and C to boot a hello world. In the following sections I go further with the diferent components to complete a OS.
# Develop Stages

## UART communication & GPIO

For setting up the periphericals of the Raspi, I have read the documentation for the [BCM 2835](/documentation/BCM2835-ARM-Peripherals.pdf), the model of my raspberry.
...

For the GPIO I wrote a simple library, according to the reference BCM manual, to manage the functionality.
## Syscalls and timers

## Memory Managment
