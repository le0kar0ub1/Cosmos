/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <lib/krn.h>

/*
** Perform a 8 bits checksum on the given size
*/
u8_t checksum8(u8_t *buffer, size_t size)
{
	size_t i = 0;
	u8_t sum = 0;

	while (i < size)
	{
		sum += buffer[i];
		i += 1;
	}
	return (sum);
}

/*
** Perform a 16 bits checksum on the given size
*/
u16_t checksum16(u16_t *buffer, size_t size)
{
	size_t i = 0;
	u16_t sum = 0;

	while (i < size)
	{
		sum += buffer[i];
		i += 1;
	}
	return (sum);
}

/*
** Perform a 32 bits checksum on the given size
*/
u32_t checksum32(u32_t *buffer, size_t size)
{
	size_t i = 0;
	u32_t sum = 0;

	while (i < size)
	{
		sum += buffer[i];
		i += 1;
	}
	return (sum);
}

/*
** Perform a 64 bits checksum on the given size
*/
u64_t checksum64(u64_t *buffer, size_t size)
{
	size_t i = 0;
	u64_t sum = 0;

	while (i < size)
	{
		sum += buffer[i];
		i += 1;
	}
	return (sum);
}
