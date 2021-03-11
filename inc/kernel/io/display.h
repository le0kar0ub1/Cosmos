/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_IO_DISPLAY_H_
# define _KERNEL_IO_DISPLAY_H_

# include <cosmos.h>

enum display_function_target_type
{
	DISPLAY_FUNCTION_FRAMEBUFFER,
	DISPLAY_FUNCTION_TEXT,
	DISPLAY_FUNCTION_UART,
};

enum display_function_type
{
	DISPLAY_FUNCTION_PRINTF,
	DISPLAY_FUNCTION_VPRINTF,
	DISPLAY_FUNCTION_PUTS
};

/*
 * A display printf fonction
 */
struct display_fnct
{
	void (*function)(char const *format, ...);
	enum display_function_type type;
	enum display_function_target_type tgt;
	char const *name;
};

# define REGISTER_DISPLAY_FNCT(mfunc, mtype, mtgt)		        		\
    __aligned(sizeof(void *)) __used __section(".cosmos_io_display")    \
    static const struct display_fnct mname = {	                    	\
        .function = mfunc,                                          	\
        .type 	  = mtype,                                          	\
        .tgt      = mtgt,												\
        .name     = #mfunc,                                       		\
    };

virtaddr_t display_kernel_fetch_func(enum display_function_target_type tgt, enum display_function_type type);

#endif /* !_KERNEL_IO_DISPLAY_H_ */
