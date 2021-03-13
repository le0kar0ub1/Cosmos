###############################################################################
##
##  This file is part of the Cosmos project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

sinclude $(PROJECT_PATH)/mkhelper/macro.mk

# Build directory, defaulting to debug
ifeq ($(TARGET),release)
    TARGET_PATH		:= $(TARGET_PATH)/release
else
    TARGET_PATH		:= $(TARGET_PATH)/debug
    CCFLAGS			+= -g3
endif

TARGET_OBJECTS :=

sinclude $(PROJECT_PATH)/src/arch/$(ARCH)/Makefile
sinclude $(PROJECT_PATH)/src/drivers/Makefile
sinclude $(PROJECT_PATH)/src/kernel/Makefile
sinclude $(PROJECT_PATH)/src/lib/Makefile
sinclude $(PROJECT_PATH)/src/hardware/Makefile

TARGET_OBJECTS	:=	$(patsubst $(PROJECT_PATH)%, $(TARGET_PATH)%, $(TARGET_OBJECTS))
TARGET_DEPS		:= 	$(TARGET_OBJECTS:.o=.d)

.PHONY: all
all: $(TARGET_ISOKRN)

.PHONY: kernel
kernel: $(TARGET_BINKRN)

$(TARGET_BINKRN):	$(TARGET_OBJECTS)
	$(CC) $(TARGET_OBJECTS) $(CCFLAGS) $(LDFLAGS) -o $(TARGET_PATH)/$(TARGET_BINKRN) -T $(PROJECT_PATH)/$(COSMOS_LINKER)
	$(call BUILD_LOG,[LD]     )

$(TARGET_ISOKRN):	$(TARGET_BINKRN)
	mkdir -p $(TARGET_PATH)/isobld/boot/grub
	cp $(TARGET_PATH)/$(TARGET_BINKRN) $(TARGET_PATH)/isobld/boot/cosmos.bin
	cp $(PROJECT_PATH)/$(GRUB_CONFIG) $(TARGET_PATH)/isobld/boot/grub
	grub-mkrescue -o $(TARGET_PATH)/$(TARGET_ISOKRN) $(TARGET_PATH)/isobld 2> /dev/null
	rm -r $(TARGET_PATH)/isobld
	$(call BUILD_LOG,[GRUB]   )

-include $(TARGET_DEPS)
$(TARGET_PATH)%$(EXTENSION_OBJ): $(PROJECT_PATH)%$(EXTENSION_CC)
	mkdir -p $(shell dirname $@)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(call BUILD_LOG,[CC]     )

-include $(TARGET_DEPS)
$(TARGET_PATH)/%$(EXTENSION_OBJ): $(PROJECT_PATH)/%$(EXTENSION_ASM)
	mkdir -p $(shell dirname $@)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(call BUILD_LOG,[AS]     )
