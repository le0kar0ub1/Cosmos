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
    CCFLAGS			+= -O2
else
    TARGET_PATH		:= $(TARGET_PATH)/debug
    CCFLAGS			+= -g3
endif

TARGET_OBJECTS :=

sinclude $(PROJECT_PATH)/src/arch/$(ARCH)/Makefile
sinclude $(PROJECT_PATH)/src/drivers/Makefile
sinclude $(PROJECT_PATH)/src/kernel/Makefile

TARGET_OBJECTS	:=	$(patsubst $(PROJECT_PATH)%, $(TARGET_PATH)%, $(TARGET_OBJECTS))
TARGET_DEPS		:= 	$(TARGET_OBJECTS:.o=.d)

.PHONY: all
all: $(TARGET_BINKRN)

$(TARGET_BINKRN):	$(TARGET_OBJECTS)
	$(CC) $(TARGET_OBJECTS) $(CCFLAGS) $(LDFLAGS) -o $(TARGET_PATH)/$(TARGET_BINKRN)
	$(call BUILD_LOG,LD)

-include $(TARGET_DEPS)
$(TARGET_PATH)%$(EXTENSION_OBJ): $(PROJECT_PATH)%$(EXTENSION_CC)
	mkdir -p $(shell dirname $@)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(call BUILD_LOG,CC)

-include $(TARGET_DEPS)
$(TARGET_PATH)/%$(EXTENSION_OBJ): $(PROJECT_PATH)/%$(EXTENSION_ASM)
	mkdir -p $(shell dirname $@)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(call BUILD_LOG,AS)