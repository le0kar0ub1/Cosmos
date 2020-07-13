###############################################################################
##
##  This file is part of the Cosmos project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

sinclude $(PROJECT_PATH)/mkhelper/def.mk

define RAISE
	@echo -e "[$(BoldRed)ABORTED$(Blank)]$(1)"
	@exit 1
endef

define LOG
	@echo -e "[$(BoldBlue)$(PROJECT)$(Blank)]$(1)"
endef

define EvalToolChainExistence
	$(if $(filter $(PROJECT_PATH)/$(2), $(wildcard $(PROJECT_PATH)/$(2)/..)), $(call RAISE, "No GNU $(1) toolchain -- make toolchain"), $(call LOG, "GNU $(1) toolchain found"))
endef

define EvalBinaryExistence
	$(if $(shell which $(1) 2> /dev/null),$(call LOG, Dependency found $(BoldMagenta)$(shell basename $(1))$(Blank)),$(call RAISE, Dependency not found $(BoldRed)$(shell basename $(1))$(Blank)))
endef