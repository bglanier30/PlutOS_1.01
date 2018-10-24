#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/pluto.kernel isodir/boot/pluto.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "pluto" {
	multiboot /boot/pluto.kernel
}
EOF
grub-mkrescue -o pluto.iso isodir

