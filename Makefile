###############################################################################
##
##  This file is part of the Cosmos project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

sinclude mkhelper/def.mk
sinclude mkhelper/macro.mk
sinclude mkhelper/toolchain.mk

.PHONY: all iso
all iso: toolchain
	$(MAKE) -C src

.PHONY: kernel
kernel: toolchain
	$(MAKE) kernel -C src

.PHONY: toolchain
toolchain:
	$(call EvalFatToolChainExistence)
	$(call EvalBinaryToolChainExistence,gcc)
	$(call EvalBinaryToolChainExistence,ld)
	$(call EvalBinaryExistence,grub-mkrescue)
	$(call EvalBinaryExistence,xorriso)

.PHONY: clean
clean:
	rm -rf $(TARGET_BASE_PATH)

.PHONY: re
re: clean all

ifeq ($(debug),soft)
    QEMUOPT = -monitor stdio --no-reboot
else ifeq ($(debug),gdb)
    QEMUOPT = -s -S
else
    QEMUOPT = -serial stdio 
endif
.PHONY: run
run: iso
	qemu-system-x86_64 -cdrom $(TARGET_BASE_PATH)/debug/$(TARGET_ISOKRN) 	\
						-enable-kvm											\
						-m 4G												\
						$(QEMUOPT)											\