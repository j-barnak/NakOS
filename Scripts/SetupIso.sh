#!/bin/sh

if ! test -f build/nak; then
    echo "Make sure to have built the image using Scripts/build.sh"
else
    cp build/nak IsoDir/boot
    grub-mkrescue -o NakOS.iso IsoDir
fi