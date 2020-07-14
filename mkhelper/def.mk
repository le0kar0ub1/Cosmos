###############################################################################
##
##  This file is part of the Cosmos project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

export PROJECT		:= Cosmos
export PROJECT_PATH	:= $(realpath .)

# File extension norm
export EXTENSION_BIN	:=	bin
export EXTENSION_ISO	:=	iso
export EXTENSION_CC		:=	.c
export EXTENSION_OBJ	:=	.o
export EXTENSION_ASM	:=	.S
export EXTENSION_LIB	:=	.a

# Versionning
export VERSION			:=	0.1.0

export TARGET_PATH		=	$(PROJECT_PATH)/target

# Build directory, defaulting to debug
ifeq ($(TARGET),release)
    TARGET_PATH		= $(TARGET_PATH)/release
else
    TARGET_PATH		= $(TARGET_PATH)/debug
endif

# Build target
export TARGET_BINKRN	:=	$(PROJECT)-$(VERSION).$(BIN_EXTENSION)
export TARGET_ISOKRN	:=	$(PROJECT)-$(VERSION).$(ISO_EXTENSION)

# Output color
export Red			:= \e[0;31m
export BoldRed		:= \e[1;31m
export Green		:= \e[0;32m
export BoldGreen	:= \e[1;32m
export Yellow		:= \e[0;33m
export BoldYellow	:= \e[1;33m
export Blue			:= \e[0;34m
export BoldBlue		:= \e[1;34m
export Magenta		:= \e[0;35m
export BoldMagenta 	:= \e[1;35m
export Cyan			:= \e[0;36m
export BoldCyan		:= \e[1;36m
export Blank		:= \e[0m