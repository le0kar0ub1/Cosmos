/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_MEM_VMM_H_
# define _KERNEL_MEM_VMM_H_

# include <cosmos.h>
# include <kernel/mem/memory.h>

enum _def_mmap_attribs {
    MMAP_DEFAULT = 1 << 0, /* Kernel space, read only, no exec */
    MMAP_USER    = 1 << 1, /* Page belongs to user space */
    MMAP_WRITE   = 1 << 2, /* Page is writtable */
    MMAP_EXEC    = 1 << 3, /* Page is executable */
    MMAP_REMAP   = 1 << 4, /* Remap if virt addr is already taken */
};

# define MASK_MMAP_DEFAULT(x)   ((bool)(x & MMAP_DEFAULT))
# define MASK_MMAP_USER(x)      ((bool)(x & MMAP_USER))
# define MASK_MMAP_WRITE(x)     ((bool)(x & MMAP_WRITE))
# define MASK_MMAP_EXEC(x)      ((bool)(x & MMAP_EXEC))
# define MASK_MMAP_REMAP(x)     ((bool)(x & MMAP_REMAP))

typedef uint mmap_attrib_t;

enum _def_munmap_attribs {
    MUNMAP_DEFAULT  = 1 << 0,  /* Free frames */
    MUNMAP_DONTFREE = 1 << 1,  /* Do not free the corresponding frames */
};

# define MASK_MUNMAP_DEFAULT(x)     ((bool)(x & MUNMAP_DEFAULT))
# define MASK_MUNMAP_DONTFREE(x)    ((bool)(x & MUNMAP_DONTFREE))

typedef uint munmap_attrib_t;

void vmm_init(void);
virtaddr_t vmm_mmap(virtaddr_t virt, size_t sz, mmap_attrib_t attrib);
void vmm_unmap(virtaddr_t virt, size_t sz, mmap_attrib_t attrib);
bool vmm_is_mapped(virtaddr_t virt);
virtaddr_t vmm_mmap_dev(virtaddr_t virt, physaddr_t phys, size_t size, mmap_attrib_t attrib);

/*
** Arch-depend prototypes
*/

bool x86_64_vmm_is_mapped(virtaddr_t virt);
physaddr_t x86_64_vmm_get_mapped_frame(virtaddr_t virt);
result_t x86_64_vmm_map_phys(virtaddr_t virt, physaddr_t phys, mmap_attrib_t attrib);
result_t x86_64_vmm_map_virt(virtaddr_t virt, mmap_attrib_t attrib);
void x86_64_vmm_unmap(virtaddr_t virt, munmap_attrib_t attrib);
void x86_64_vmm_init(void);

#endif /* _KERNEL_MEM_VMM_H_ */
