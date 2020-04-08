# gtdOS
A basic OS for the RASPI3 B.

## DEBUGGING WITH gdb-multiarch
For debugging in the Qemu we need to compile with the -g option and do the following steps:
``
gdb-multiarch
(gdb) target-remote localhost:1234
(gdb) file ~/build/kernel-qemu.elf
(gdb) continue
``
I attach this to a gdb script.

## UART COMMUNICATIO
ToDo: Comunicacion uart/serial


Code completion


## Memory Managment
