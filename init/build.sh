#!/bin/bash
CC="${CC:-gcc}"
LD="${LD:-ld}"
cd "$(dirname "$0")" || exit 1
$CC -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -nostdlib -c syscall.c -o syscall.o
$CC -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -nostdlib -c init.c -o init.o
$LD syscall.o init.o -o init -T linker.ld -nostdlib --no-dynamic-linker --strip-all