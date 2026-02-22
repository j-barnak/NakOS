#!/usr/bin/env bash

set -euo pipefail

readonly ISO_FILE="NakOS.iso"
readonly KERNEL_BINARY="Build/nak"
readonly GDB_PORT="1234"

readonly RED='\033[0;31m'
readonly GREEN='\033[0;32m'
readonly YELLOW='\033[1;33m'
readonly BLUE='\033[0;34m'
readonly CYAN='\033[0;36m'
readonly NC='\033[0m'

log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1" >&2
}

log_step() {
    echo -e "${CYAN}[STEP]${NC} $1"
}

show_help() {
    echo -e "${BLUE}Lettuce${NC}"
    echo ""
    echo -e "Usage: $(basename "$0") [COMMAND] [OPTIONS]"
    echo ""
    echo -e "${YELLOW}Commands:${NC}"
    echo "  (none), build       Build the kernel (default)"
    echo "  setup               Create the bootable ISO image"
    echo "  debug, d            Build and launch QEMU waiting for debugger"
    echo "  debug-start, ds     Build, launch QEMU, and auto-attach GDB"
    echo ""
    echo -e "${YELLOW}Options:${NC}"
    echo "  -h, --help          Show this help message"
    echo "  -n, --no-display    Run QEMU without display (headless mode)"
    echo ""
    echo -e "${YELLOW}Examples:${NC}"
    echo "  $(basename "$0")              # Just build the kernel"
    echo "  $(basename "$0") build        # Same as above"
    echo "  $(basename "$0") setup        # Create bootable ISO"
    echo "  $(basename "$0") debug -n     # Start QEMU in debug mode (headless)"
    echo "  $(basename "$0") ds -n        # Build, debug, and auto-attach GDB"
    echo ""
}

build_kernel() {
    log_step "Building NakOS kernel..."

    if ! cmake --build Build; then
        log_error "Build failed"
        exit 1
    fi

    if [[ ! -f "$KERNEL_BINARY" ]]; then
        log_error "Kernel binary not found after build: $KERNEL_BINARY"
        exit 1
    fi

    log_info "Build completed successfully: $KERNEL_BINARY"
}

create_iso() {
    log_step "Creating bootable ISO image..."

    build_kernel

    local iso_dir="Build/iso"
    local boot_dir="$iso_dir/boot"
    local grub_dir="$boot_dir/grub"

    log_info "Setting up ISO directory structure..."
    mkdir -p "$grub_dir"

    log_info "Copying kernel binary..."
    cp "$KERNEL_BINARY" "$boot_dir/nak"

    log_info "Creating GRUB configuration..."
    cat > "$grub_dir/grub.cfg" << 'GRUBCFG'
set timeout=0
set default=0

menuentry "NakOS" {
    multiboot /boot/nak
    boot
}
GRUBCFG

    log_info "Building ISO with grub-mkrescue..."
    if ! grub-mkrescue -o "$ISO_FILE" "$iso_dir" 2>/dev/null; then
        log_error "Failed to create ISO"
        log_error "Make sure grub-mkrescue is installed (package: grub-pc-bin or grub-common)"
        exit 1
    fi

    log_info "ISO created successfully: $ISO_FILE"

    local iso_size=$(du -h "$ISO_FILE" | cut -f1)
    log_info "ISO size: $iso_size"
}

launch_qemu_debug() {
    local auto_attach="$1"
    local no_display="$2"
    local qemu_args="-cdrom $ISO_FILE -s -S"

    if [[ ! -f "$ISO_FILE" ]]; then
        log_error "ISO file not found: $ISO_FILE"
        log_error "Make sure the kernel is built and ISO is created"
        exit 1
    fi

    if [[ "$no_display" == "true" ]]; then
        qemu_args+=" -display none -serial stdio -monitor none"
        log_info "Running in headless mode (serial output to stdio)"
    fi

    log_info "Launching QEMU in debug mode (waiting for debugger on port $GDB_PORT)..."

    qemu-system-i386 $qemu_args &
    local qemu_pid=$!

    if [[ "$auto_attach" == "false" ]]; then
        log_warn "QEMU is paused and waiting for debugger connection"
        log_warn "Connect with: gdb $KERNEL_BINARY"
        log_warn "Then run:"
        log_warn "  (gdb) target remote localhost:$GDB_PORT"
        log_warn "  (gdb) continue"
        log_info "QEMU PID: $qemu_pid"
        log_info "Press Ctrl+C to stop QEMU"

        wait $qemu_pid 2>/dev/null || true
    else
        sleep 1

        log_info "Starting GDB and attaching to QEMU..."

        local gdb_cmds=$(mktemp)
        cat > "$gdb_cmds" << 'GDBEOF'
# Connect to QEMU
target remote localhost:1234

# Set breakpoint at kernel entry
break _start

# Continue to _start
continue

# When we get here, we've hit _start
echo \nStopped at _start\n
x/10i $eip
GDBEOF

        gdb -q -x "$gdb_cmds" "$KERNEL_BINARY"

        rm -f "$gdb_cmds"

        log_info "GDB exited, stopping QEMU..."
        kill $qemu_pid 2>/dev/null || true
    fi
}

command="build"
no_display="false"

if [[ $# -gt 0 ]] && [[ "$1" != -* ]]; then
    command="$1"
    shift
fi

while [[ $# -gt 0 ]]; do
    case "$1" in
        -h|--help)
            show_help
            exit 0
            ;;
        -n|--no-display)
            no_display="true"
            shift
            ;;
        *)
            log_error "Unknown option: $1"
            echo ""
            show_help
            exit 1
            ;;
    esac
done

case "$command" in
    build|"")
        build_kernel
        ;;
    setup)
        create_iso
        ;;
    debug|d)
        build_kernel
        launch_qemu_debug "false" "$no_display"
        ;;
    debug-start|ds)
        build_kernel
        launch_qemu_debug "true" "$no_display"
        ;;
    go)
        no_display="true"
        build_kernel
        launch_qemu_debug "true" "$no_display"
        ;;
    *)
        log_error "Unknown command: $command"
        echo ""
        show_help
        exit 1
        ;;
esac
