/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/


# include <cosmos.h>
# include <kernel/io/dsp.h>

extern uintptr_t __cosmos_io_dsp_start;
extern uintptr_t __cosmos_io_dsp_end;

virtaddr_t get_dsp_kernel(enum dsp_function_target_type tgt, enum dsp_function_type type)
{
	struct dsp_fnct *fnct = (struct dsp_fnct *)&__cosmos_io_dsp_start;

	while ((uintptr_t)fnct < (uintptr_t)&__cosmos_io_dsp_end)
	{
		if (fnct->tgt == tgt && fnct->type == type)
			return ((virtaddr_t)fnct->function);
	}
	return (NULL);
}
