if ! test -f NakOS.iso; then
    echo "Make sure to have built the iso using Scripts/SetupIso.sh"
else
    qemu-system-i386 -cdrom NakOS.iso
fi
