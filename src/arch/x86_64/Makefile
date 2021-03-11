###############################################################################
##
##  This file is part of the Cosmos project, and is made available under
##  the terms of the GNU General Public License version 3.
##
##  Copyright (C) 2020 - Leo Karoubi
##
###############################################################################

local := $(CALLED_LOCAL_DIRECTORY)

TARGET_OBJECTS	+= $(addprefix $(local),	\
						@config.o			\
					)

sinclude $(local)/boot/Makefile				\
		 $(local)/smp/Makefile				\
		 $(local)/system/Makefile			\
		 $(local)/interrupts/Makefile		\
		 $(local)/mem/Makefile				\
		 $(local)/hooks/Makefile			\