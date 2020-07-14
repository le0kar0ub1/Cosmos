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

# Target architecture
export ARCH := x86_64

# Make verbosity
MAKEFLAGS += --no-print-directory --silent

# File extension norm
export EXTENSION_BIN	:=	bin
export EXTENSION_ISO	:=	iso
export EXTENSION_CC		:=	.c
export EXTENSION_OBJ	:=	.o
export EXTENSION_ASM	:=	.S
export EXTENSION_LIB	:=	.a

# Versionning
export VERSION			:=	0.1.0

# Target
export TARGET_BASE_PATH	:=	$(PROJECT_PATH)/target
export TARGET 			?= 	debug
export TARGET_PATH		:=	$(PROJECT_PATH)/target

# Build target
export TARGET_BINKRN	:=	$(PROJECT)-$(VERSION).$(EXTENSION_BIN)
export TARGET_ISOKRN	:=	$(PROJECT)-$(VERSION).$(EXTENSION_ISO)

# Linker script & cfg
export COSMOS_LINKER	:=	src/arch/$(ARCH)/cosmos.ld
export GRUB_CONFIG		:=	src/arch/$(ARCH)/grub.cfg

# Cleaner as possible
export CCFLAGS	=	-isystem $(PROJECT_PATH)/inc		\
					-Wall								\
					-MD									\
					-pipe 								\
					-Wcast-align					    \
					-Wextra				 				\
					-Wnested-externs					\
					-Winline							\
					-Wpragmas							\
					-ffreestanding 						\
					-std=gnu11							\
					-Wuninitialized						\
					-Wno-missing-braces					\
					-Wcast-align						\
					-Wwrite-strings						\
					-Wparentheses						\
					-Wunreachable-code					\
					-Wunused							\
					-Wmissing-field-initializers		\
					-Wswitch-enum						\
					-Wshadow				 			\
					-fno-stack-protector				\
					-Wuninitialized				 		\
					-Wmissing-declarations				\
					-Wmissing-prototypes				\
					-Wstrict-prototypes					\
					-Wpointer-arith						\
					-static 							\
					-fms-extensions 					\
					-fno-omit-frame-pointer 			\

export LDFLAGS	=   -nostdlib							\
					-lgcc								\
					-z max-page-size=0x1000				\

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