GCC = gcc
GCC_FLAG = -ffreestanding -m32 -c -Wno-implicit-function-declaration -fno-stack-protector -nostdlib

NASM = nasm
NASM_FLAG = -f elf32

LD = ld
LD_FILE = linker.ld

GRUB = grub-mkrescue
GRUB_FLAG = -o
MULTIBOOT = multiboot_header.o

KERNEL_START = 0x1000

KERNEL_BIN = kernel.bin
KERNEL_OBJ = kernel.o

ISO = osb.iso

all: $(ISO)

$(KERNEL_OBJ): kernel.c
	$(GCC) $(GCC_FLAG) $< -o $@

$(MULTIBOOT): multiboot_header.asm
	$(NASM) $(NASM_FLAG) $< -o $@

$(KERNEL_BIN): $(MULTIBOOT) $(KERNEL_OBJ)
	$(LD) -m elf_i386 -T $(LD_FILE) -Ttext $(KERNEL_START) -o $@ $^

$(ISO): $(KERNEL_BIN)
	mkdir -p iso/boot/grub
	cp $(KERNEL_BIN) iso/boot/$(KERNEL_BIN)
	#cp -r /usr/lib/grub/i386-efi iso/boot/grub/
	echo 'set timeout=1' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "CORE kernel" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/$(KERNEL_BIN)' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	$(GRUB) $(GRUB_FLAG) $(ISO) iso

clean:
	rm -rf $(KERNEL_BIN) $(KERNEL_OBJ) $(MULTIBOOT) $(ISO)
	rm -rf iso

.PHONY: all clean
