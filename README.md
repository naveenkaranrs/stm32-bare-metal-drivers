# STM32F103 Bare-Metal Peripheral Driver Suite

**Register-Level Embedded Firmware Development | ARM Cortex-M3 | Embedded C**

A bare-metal firmware engineering project implementing low-level peripheral drivers for the **STM32F103RB microcontroller** based on the **ARM Cortex-M3** architecture.

The goal of this project is to understand and implement the microcontroller hardware-software interface through direct register-level programming without relying on:

- STM32 HAL
- Standard Peripheral Library (SPL)
- Arduino frameworks

The project focuses on peripheral control, memory-mapped I/O, clock configuration, startup initialization, linker scripts, and automated firmware builds.

> **Engineering Focus:** Understand the hardware at the register level, build firmware from source, inspect generated binaries, and verify peripheral behavior on real hardware.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Hardware and Software Stack](#hardware-and-software-stack)
- [Firmware Architecture](#firmware-architecture)
- [Peripheral Driver Modules](#peripheral-driver-modules)
- [Startup and Memory Architecture](#startup-and-memory-architecture)
- [Build and Flash Workflow](#build-and-flash-workflow)
- [Debugging and Verification](#debugging-and-verification)
- [Engineering Concepts Demonstrated](#engineering-concepts-demonstrated)
- [Development Roadmap](#development-roadmap)
- [Repository Structure](#repository-structure)
- [References](#references)
- [License](#license)

---

# Project Overview

Microcontroller firmware requires precise control over peripheral registers, clock domains, memory regions, and execution flow.

This project explores those mechanisms by implementing a modular bare-metal driver framework for the STM32F103RB.

Unlike high-level frameworks that abstract hardware details, these drivers expose the underlying register operations used directly by the microcontroller.

## Design Objectives

- Register-level peripheral configuration
- Modular and reusable driver architecture
- Explicit hardware initialization
- Custom linker-script based memory management
- Toolchain-independent reproducible builds
- Automated firmware validation through CI/CD

---

# Hardware and Software Stack

| Component | Specification |
|------------|--------------|
| Development Board | STM32 Nucleo-F103RB |
| MCU | STM32F103RB |
| Core | ARM Cortex-M3 |
| Instruction Set | Thumb / Thumb-2 |
| Language | Embedded C |
| Peripheral Access | Direct Register-Level Programming |
| Device Definitions | CMSIS |
| Compiler | arm-none-eabi-gcc |
| Build System | GNU Make |
| Debugger | GDB |
| Flash Tool | ST-LINK / OpenOCD |
| CI Platform | GitHub Actions |

## Hardware Resources

| Resource | Description |
|-----------|------------|
| Flash | 128 KB |
| SRAM | 20 KB |
| GPIO | Digital Inputs/Outputs |
| RCC | Reset & Clock Control |
| SysTick | Cortex-M3 System Timer |
| USART | Serial Communication |

---

# Firmware Architecture

The firmware follows a layered architecture:

```text
+---------------------------+
|      Application Layer    |
|          main.c           |
+------------+--------------+
             |
+------------v--------------+
|   Peripheral Interfaces   |
| gpio.h rcc.h usart.h      |
+------------+--------------+
             |
+------------v--------------+
| Driver Implementations    |
| gpio.c rcc.c usart.c      |
+------------+--------------+
             |
+------------v--------------+
| CMSIS Device Definitions  |
+------------+--------------+
             |
+------------v--------------+
| STM32F103RB Hardware      |
+---------------------------+
```

Additional build components:

- Startup Code
- Interrupt Vector Table
- GNU Linker Script
- ELF/BIN/HEX Firmware Artifacts

---

# Peripheral Driver Modules

## RCC (Reset and Clock Control)

**Files**
- `rcc.h`
- `rcc.c`

### Responsibilities

- Enable peripheral clocks
- Configure AHB/APB clock domains
- Manage peripheral reset operations

### Engineering Concepts

- Clock trees
- Peripheral bus architecture
- Reset management

---

## GPIO (General Purpose Input Output)

**Files**
- `gpio.h`
- `gpio.c`

### Responsibilities

- Configure input/output modes
- Read and write GPIO states
- Configure alternate-function pins

### Engineering Concepts

- Memory-mapped I/O
- Atomic bit manipulation
- Pin multiplexing

---

## SysTick

**Files**
- `systick.h`
- `systick.c`

### Responsibilities

- Configure Cortex-M3 system timer
- Generate software delays
- Support timing operations

### Engineering Concepts

- Timer reload calculations
- Timing accuracy
- Clock-dependent operation

---

## USART

**Files**
- `usart.h`
- `usart.c`

### Responsibilities

- Serial communication configuration
- Data transmission and reception
- Polling and interrupt-driven communication

### Engineering Concepts

- Baud-rate generation
- Interrupt handling
- Serial protocol fundamentals

---

# Startup and Memory Architecture

The firmware uses a custom linker script:

```text
stm32f103rb.ld
```

## Memory Map

| Region | Start Address | Size |
|----------|--------------|---------|
| Flash | 0x08000000 | 128 KB |
| SRAM | 0x20000000 | 20 KB |

### Firmware Layout

```text
FLASH
│
├── Vector Table
├── .text
├── .rodata
└── Data Load Image

SRAM
│
├── .data
├── .bss
├── Heap (Optional)
└── Stack
```

### Responsibilities

- Define MCU memory regions
- Place code and constants in Flash
- Allocate runtime variables in SRAM
- Initialize stack and runtime environment

---

# Build and Flash Workflow

## Prerequisites

Install:

- GNU Arm Embedded Toolchain
- GNU Make
- Arm GDB
- OpenOCD
- Git

## Clone Repository

```bash
git clone https://github.com/naveenkaranrs/stm32-bare-metal-drivers.git

cd stm32-bare-metal-drivers
```

## Build Firmware

```bash
make all
```

Expected artifacts:

```text
build/
├── firmware.elf
├── firmware.bin
└── firmware.hex
```

## Inspect Firmware

```bash
arm-none-eabi-size build/firmware.elf

arm-none-eabi-objdump -h build/firmware.elf

arm-none-eabi-objdump -d build/firmware.elf
```

---

## Flash Using OpenOCD

Start OpenOCD:

```bash
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
```

Open another terminal:

```bash
arm-none-eabi-gdb build/firmware.elf
```

Inside GDB:

```gdb
target extended-remote localhost:3333

monitor reset halt

load

monitor reset init

continue
```

---

# Debugging and Verification

| Verification | Objective |
|-------------|------------|
| Build Validation | Confirm compilation and linking |
| ELF Inspection | Verify sections and symbols |
| Register Inspection | Validate register configuration |
| GPIO Testing | Verify pin behavior |
| USART Testing | Validate communication |
| Timing Validation | Verify timing accuracy |

## Recommended Checks

- Ensure clocks are enabled before peripheral access
- Validate register masks
- Verify timer reload calculations
- Confirm USART baud-rate configuration
- Inspect vector table placement
- Review firmware size and memory boundaries

---

# Engineering Concepts Demonstrated

- Bare-metal firmware development
- ARM Cortex-M3 architecture
- Register-level peripheral programming
- GPIO configuration
- Clock management
- USART communication
- SysTick timer usage
- Linker script development
- Startup code implementation
- Embedded memory organization
- GCC cross-compilation
- ELF, HEX and BIN inspection
- GDB debugging
- GitHub Actions CI/CD

---

# Development Roadmap

- [ ] API documentation
- [ ] GPIO examples
- [ ] USART examples
- [ ] Interrupt-driven communication
- [ ] EXTI driver
- [ ] Timer driver
- [ ] PWM driver
- [ ] SPI driver
- [ ] I2C driver
- [ ] UART timeout/error handling
- [ ] Automated unit testing
- [ ] CI artifact publishing

---

# Repository Structure

```text
stm32-bare-metal-drivers/
├── .github/
│   └── workflows/
│       └── build.yml
├── rcc.c
├── rcc.h
├── gpio.c
├── gpio.h
├── systick.c
├── systick.h
├── usart.c
├── usart.h
├── stm32f103rb.ld
├── Makefile
├── LICENSE
└── README.md
```

---

# References

- STM32F103RB Datasheet
- STM32F1 Reference Manual (RM0008)
- ARM Cortex-M3 Technical Reference Manual
- CMSIS Documentation
- GNU Arm Embedded Toolchain
- GNU GDB Documentation

---

# License

Distributed under the MIT License.

See the `LICENSE` file for details.

---

# Author

**Naveen Karan R. S.**

Electronics and Communication Engineering  
Embedded Systems & Bare-Metal Firmware Development

GitHub: **[@naveenkaranrs](https://github.com/naveenkaranrs)**

> Building
