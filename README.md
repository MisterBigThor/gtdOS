# gtdOS
A basic OS for the RASPI3 B. 

## Developing enviroment
For develop an OS, certain tools needed:

### Compiling, emulating and debugging
<compiler text here>
  
The lastest versions of QEMU-aarch64 emulates raspi2 and raspi3 models. In my experience, with the XX version of the QEMU the same image of the OS didn't works equaly respect the real raspi3.
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
A good practice is attach this to a script and run ``gdb-multiarch -x setupDBG`` or a bash/shell script.
## Rasberry Pi specifications

## UART communication & GPIO

For setting up the periphericals of the Raspi, I have read the documentation for the [BCM 2835](/documentation/BCM2835-ARM-Peripherals.pdf), the model of my raspberry.
...

For the GPIO I wrote a simple library, according to the reference BCM manual, to manage the functionality.
## Syscalls and timers

## Memory Managment
