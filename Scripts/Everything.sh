#!/usr/bin/sh

cmake --build build

if ! test -f build/nak; then
    echo "Make sure to have built the image using Scripts/build.sh"
else
    cp build/nak IsoDir/boot
    grub-mkrescue -o NakOS.iso IsoDir
fi

if ! test -f NakOS.iso; then
    echo "Make sure to have built the iso using Scripts/SetupIso.sh"
else
    qemu-system-i386 -cdrom NakOS.iso
fi
