[TOC]

## STR - mini project by Victor Correal

## Project coordination

### Project Motivation

The aim of this project is to build a Real Time Kernel to run in a Rasperry Pi 3 (in my case, Raspberry Pi 3 model B rev1.2).

The kernel will be able to schedule tasks (with freeRTOS), work with serial line, GPIO's ports and to receive instructions through the Ethernet RJ45 connection. In *Sistemes Operatius 2* we built a similar operating system in C (with a few syscalls to allocate data, create threads), based in Linux kernel, for this reason I consider it would be affordable to implement this Real Time Kernel.

I also want to create a tool to measure, in function of the assembly code the expected time of execution of a program, internaly in the OS. For testing, I can use and Arduino Uno to use as an oscyloscope to watch over the times.

I am motivated and eager to work with the ARM architecture inside the raspberry Pi, because in the future I want to build a raspberry cluster at home with 3 or 4 raspberry.

I append a tutorial that I would use in the begging of the project to set up a development enviroment: https://jsandler18.github.io/ .

### Initial implementations steps

1. Set up the development enviroment.
2. Learn about the ARM architecture and the instructions set.
3. Build the instructions tool measure.
4. Import FreeRTOS (or adapt) on the basic OS.
5. Performance analytic.
6. Implement serial line comunication.
7. Implement Ethernet comunication

### Dietari

Dia 22/03/2020: Instal·lació de la màquina virtual, compilador i entorn. Primers passos en la implementacio de la gestio de memoria.
Dia 23/03/2020: Primeres passes en el Sistema operatiu en la gestio de memoria. He decidit en aquest punt parar l'implementació i estudiar sobre la gestió
de memoria i l'arquitectua del procesador ARM, el codi de jsandler18 no m'ha acabat de convencer.

https://github.com/bztsrc/raspi3-tutorial

https://github.com/s-matyukevich/raspberry-pi-os

## ARMv8 architecture
A few architecture features:
* Have 4 exception levels(the least one is the 0) the ELx contains the current exception level
* General purpose registers (X0-X30)
* Store/Load model for data memory

### Entering the system ARMv8 arch
The 'trap' for enter the OS (and change the EL) is called `svc`. The process is similar as others OS:
1. Current PC saved in ELR_ELn (Exception link register)
2. Current state saved in SPSR_ELn (Saved Program Status Register) and the general porpuse registers (stack)
3. Exception handler
4. Return from exception

## Processor Start up
* When boot, the exception level should be 3.

## UART Serial communication

##
