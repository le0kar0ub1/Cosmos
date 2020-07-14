###############################################################################
##
##  This file is part of the Cosmos project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

sinclude $(PROJECT_PATH)/mkhelper/macro.mk

TARGET_OBJECTS	=

sinclude $(PROJECT_PATH)/src/arch/$(ARCH)/Makefile
# sinclude $(PROJECT_PATH)/src/drivers/Makefile
# sinclude $(PROJECT_PATH)/src/kernel/Makefile

sinclude $(PROJECT_PATH)/mkhelper/builder.mk


TARGET_OBJECTS	:=	$(patsubst $(PROJECT_PATH)%, $(TARGET_PATH)%, $(TARGET_OBJECTS))

.PHONY: all
all: debugobj #$(TARGET_BINKRN)

debugobj: $(TARGET_OBJECTS)
	echo " $(PROJECT_PATH) -> $(TARGET_PATH)"
	echo "TARGET BUILD $(TARGET_OBJECTS) -> $(TARGET_OBJECTS)"

$(TARGET_BINKRN):	$(TARGET_OBJECTS)
	$(CC) $(TARGET_OBJECTS) $(CCFLAGS) $(LDFLAGS) -o $(TARGET_BINKRN)
	$(call BUILD_LOG,LD,$(TARGET_BINKRN))

# $(TARGET_PATH)%$(EXTENSION_OBJ): $(PROJECT_PATH)%$(EXTENSION_CC)
# 	mkdir -p $(shell dirname $@)
# 	$(CC) $(CCFLAGS) -c $< -o $@
# 	$(call BUILD_LOG,CC,$@)

$(TARGET_PATH)/%$(EXTENSION_OBJ): $(PROJECT_PATH)/%$(EXTENSION_ASM)
	mkdir -p $(shell dirname $@)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(call BUILD_LOG,AS,$@)