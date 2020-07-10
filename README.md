# Cosmos

Another birth of an x86 kernel named COSmOS (yeah, word count double).

## Dependencies

  * `make` (dev under v4.3)
  * `grub-mkrescue` (dev under v2.04)

## Build

The only arch-target of Cosmos is x64, then the keyword `TARGET` is used here to control the build.

| Target     | Effect                 |
|------------|------------------------|
| debug      | build kernel for debug |

### Kernel build

`make kernel [TARGET=$TARGET]`

output: `elf` file.

### ISO build

`make [iso] [TARGET=$TARGET]`

output: `iso` file.

## Run

A configured *QEMU* run is provided.

`make run`

## ROADMAP

let's go again

- [ ] Kernel loaded higher-half
- [ ] Boot
  - [ ] Multiboot 2
  - [ ] Paging setup
  - [ ] GDT setup
  - [ ] IDT setup
  - [ ] TSS setup
  - [ ] SMP setup
- [ ] Early drivers
  - [ ] VGA
  - [ ] PS/2 Keyboard
  - [ ] Timer
- [ ] Memory
  - [ ] Physical Memory Management
  - [ ] Virtual Memory Management
  - [ ] Memory Abstractor
  - [ ] Kernel heap
- [ ] ELF Loader
- [ ] Syscall interface and userspace
- [ ] Middle driver
  - [ ] RTC
- [ ] Multi process / threads
  - [ ] Basic Scheduling
  - [ ] User Threads
  - [ ] Kernel threads
  - [ ] Processes
- [ ] Initrd
- [ ] Filesystem
  - [ ] ...
- [ ] TTY
  - [ ] ...

Not in the current scope:

- [ ] GUI
- [ ] late driver
  - [ ] PS/2 Mouse

## Epilogue

Feel free to fork, use, improve.