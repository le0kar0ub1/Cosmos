/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/


# include <cosmos.h>
# include <kernel/io/display.h>

extern uintptr_t __cosmos_io_display_start;
extern uintptr_t __cosmos_io_display_end;

virtaddr_t display_kernel_fetch_func(enum display_function_target_type tgt, enum display_function_type type)
{
	struct display_fnct *fnct = (struct display_fnct *)&__cosmos_io_display_start;

	while ((uintptr_t)fnct < (uintptr_t)&__cosmos_io_display_end)
	{
		if (fnct->tgt == tgt && fnct->type == type)
			return ((virtaddr_t)fnct->function);
	}
	return (NULL);
}
