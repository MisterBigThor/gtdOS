# gtdOS
A basic OS for the RASPI3 B. 

## Developing enviroment
### compiler

### QEMU for AARCH64
The lastest versions of QEMU-aarch64 emulates raspi2 and raspi3 models. In my experience, with the XX version of the QEMU the same image of the OS didn't works equaly respect the real raspi3.
Every directory contains a file to run the qemu.
````
qemu-system-aarch64 -M raspi3 -kernel kernel-qemu.img -serial stdio
````

### Debugging with gdb-multiarch and QEMU
For debugging in the Qemu we need to compile with the -g option and do the following steps:
````
gdb-multiarch
(gdb) target-remote localhost:1234
(gdb) file ~/build/kernel-qemu.elf
(gdb) continue
````
I attach this to a gdb script and add a option to the QEMU (inside a [script](/01_UART/gdbscript)), also I added some usefull gdb defines for the debugging.
## Rasberry Pi specifications

## UART communication & GPIO

For setting up the periphericals of the Raspi, I have read the documentation for the [BCM 2835](/documentation/BCM2835-ARM-Peripherals.pdf), the model of my raspberry.
...

For the GPIO I wrote a simple library, according to the reference BCM manual, to manage the functionality.
## Syscalls and timers

## Memory Managment
