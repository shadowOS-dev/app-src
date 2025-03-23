#!/bin/bash
cd "$(dirname "$0")" || exit 1
CC="${CC:-gcc}"
LD="${LD:-ld}"
$CC -ffreestanding -fno-builtin -fno-stack-protector -fno-pic -mno-red-zone -nostdlib -c init.c -o init.o
$LD syscall.o init.o -o init -T linker.ld -nostdlib --no-dynamic-linker --strip-all