/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_IO_DSP_H_
# define _KERNEL_IO_DSP_H_

# include <cosmos.h>

enum dsp_function_target_type
{
	DSP_FUNCTION_FRAMEBUFFER,
	DSP_FUNCTION_TEXT,
	DSP_FUNCTION_UART,
};

enum dsp_function_type
{
	DSP_FUNCTION_PRINTF,
	DSP_FUNCTION_VPRINTF,
	DSP_FUNCTION_PUTS
};

/*
 * A display printf fonction
 */
struct dsp_fnct
{
	void (*function)(char const *format, ...);
	enum dsp_function_type type;
	enum dsp_function_target_type tgt;
	char const *name;
};

# define REGISTER_DSP_FNCT(mfunc, mtype, mtgt)		        		\
    __aligned(sizeof(void *)) __used __section(".cosmos_io_dsp")    \
    static const struct dsp_fnct mname = {	                        \
        .function = mfunc,                                          \
        .type 	  = mtype,                                          \
        .tgt      = mtgt,											\
        .name     = #mfunc,                                       	\
    };

#endif /* !_KERNEL_IO_DSP_H_ */
