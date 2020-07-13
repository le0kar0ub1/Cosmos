###############################################################################
##
##  This file is part of the Cosmos project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

export TOOLCHAN_GNUBASE := $(PROJECT_PATH)/mktoolchain/toolchain/x86_64-elf-

export CC		:=	$(TOOLCHAN_GNUBASE)gcc
export AS		:=	$(TOOLCHAN_GNUBASE)as
export AR		:=	$(TOOLCHAN_GNUBASE)ar
export LD		:=	$(TOOLCHAN_GNUBASE)ld
export OBJCPY	:=	$(TOOLCHAN_GNUBASE)objcopy
export OBJDMP	:=	$(TOOLCHAN_GNUBASE)objdump
export RDELF	:=	$(TOOLCHAN_GNUBASE)readelf