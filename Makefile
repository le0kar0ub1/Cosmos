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

# Build directory, defaulting to debug
ifeq ($(TARGET),release)
    TARGET_PATH		:= $(TARGET_PATH)/release
else ifeq ($(TARGET),debug)
    TARGET_PATH		:= $(TARGET_PATH)/debug
else
    $(call RAISE,Invalid given target)
endif

.PHONY: all
all: _kernel

.PHONY: _kernel
_kernel: toolchain
	$(MAKE) -C src

.PHONY: toolchain
toolchain:
	$(call EvalFatToolChainExistence)

.PHONY: clean
clean:
	rm -rf $(TARGET_BASE_PATH)

.PHONY: re
re: clean all

.PHONY: run
run:
	qemu-system-x86_64