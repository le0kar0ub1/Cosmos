# Cosmos

Another birth of a x86_64 kernel named COSmOS (yeah, word count double).

## Dependencies

  * `make` (dev under v4.3)
  * `grub-mkrescue` (dev under v2.04)
  * `mtools` (GNU mtools) (dev under 4.0.24)
  * `libisoburn`

## Install

Cosmos use his own cross-compiler, build it by executing the following command-line.
The dependencies are also checked-up.

`./mktoolchain/mktoolchain`

## Build

The only arch-target of Cosmos is x64, then the keyword `TARGET` is used here to control the build.

| Target     | Effect                 |
|------------|------------------------|
| debug      | build kernel for debug |
| release    | build kernel release   |

Inspired from cargo (and others) philosophy.

### Kernel build

`make kernel [TARGET=$Target]`

output: `elf` file.

### ISO build

`make [iso] [TARGET=$Target]`

output: `iso` file.

## Run

A configured *QEMU* run is provided.

`make run`

## ROADMAP

let's go again.

- [X] Kernel loaded higher-half
- [ ] Kernel architecture
- [ ] Boot(strap)
  - [X] Multiboot 2
  - [X] Paging setup
  - [X] GDT setup
  - [X] IDT setup
  - [X] Interrupts
  - [ ] TSS setup
  - [ ] SMP init
- [ ] Early drivers
  - [X] VGA
  - [X] UART
  - [ ] Timer
- [ ] Memory
  - [X] Physical Memory Management
  - [ ] Virtual Memory Management
  - [ ] kernel allocator
  - [ ] Memory Abstractor
- [ ] ELF Loader
- [ ] Syscall interface and userspace
- [ ] Middle driver
  - [ ] RTC
  - [ ] PS/2 Keyboard
- [ ] Multi-threads
  - [ ] Virtual
    - [ ] Basic Scheduling
    - [ ] User Threads
    - [ ] Kernel threads
    - [ ] Processes
  - [ ] Physical
    - [ ] Handling ?
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