#!/bin/bash
cd "$(dirname "$0")" || exit 1
gcc -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -nostdlib -c syscall.c -o syscall.o
gcc -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -nostdlib -c init.c -o init.o
ld syscall.o init.o -o init -T linker.ld -nostdlib --no-dynamic-linker --strip-all