/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_DEF_GENERATOR_H_
# define _KERNEL_DEF_GENERATOR_H_

# include <kernel/def/def.h>

# define _CONCAT(a, b)  a##b
# define CONCAT(a, b)   _CONCAT(a, b)

# define _STRINGIFY(a)  #a
# define STRINGIFY(a)   _STRINGIFY(a)

# define ARCH_HEADER(x)  <arch/ARCH/x>

# define ARCH_FUNCTION_MAPPING(x)  CONCAT(ARCH, CONCAT(_, x))

# define ARCH_FUNCTION_ALIASING(x) __alias(STRINGIFY(ARCH_FUNCTION_MAPPING(x)))

#endif /* !_KERNEL_DEF_GENERATOR_H_ */
