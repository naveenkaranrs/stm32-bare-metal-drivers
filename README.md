# STM32F103 Bare-Metal Peripheral Driver Suite ⚡

[![Build Firmware](https://github.com/naveenkaranrs/stm32-bare-metal-drivers/actions/workflows/build.yml/badge.svg)](https://github.com/naveenkaranrs/stm32-bare-metal-drivers/actions/workflows/build.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Target: STM32F103RB](https://img.shields.io/badge/Target-STM32F103RB-002B49?logo=stmicroelectronics)](https://www.st.com/en/microcontrollers-microprocessors/stm32f103rb.html)
[![Core: ARM Cortex-M3](https://img.shields.io/badge/Core-ARM%20Cortex--M3-0091BD?logo=arm)](https://developer.arm.com/Processors/Cortex-M3)

A production-grade, zero-HAL, register-level peripheral driver library developed from scratch for the **STM32F103RB** (ARM Cortex-M3, Nucleo-64) microcontroller.

This repository demonstrates bare-metal firmware development principles without relying on STM32Cube HAL, SPL, or Arduino abstractions. Every peripheral register is configured through memory-mapped addresses, bitmasks, and CMSIS definitions.

---

## 🎯 Architecture & Design Highlights

- **Pure Register Access:** Direct memory manipulation via base addresses and peripheral offset structs.
- **Custom Linker Script (`stm32f103rb.ld`):** Explicit memory map layout for 128 KB FLASH and 20 KB SRAM with stack pointer and interrupt vector placements.
- **Modular Driver Hierarchy:**
  - `rcc.h / rcc.c`: High-speed internal/external oscillator selection, APB1/APB2 peripheral bus clock gating.
  - `gpio.h / gpio.c`: Port configuration (Input Floating, Pull-Up/Pull-Down, Output Push-Pull, Alternate Function).
  - `systick.h / systick.c`: 24-bit core system timer configuration for microsecond/millisecond calibrated delay loops.
  - `usart.h / usart.c`: Asynchronous serial transmitter/receiver with polling and interrupt-driven circular buffers.
- **Automated CI Pipeline:** GitHub Actions workflow building the firmware on every push with `arm-none-eabi-gcc`.

---

## 📂 Memory Layout (STM32F103RB)

```
0x0800_0000 ┌───────────────────────────┐ ◄── FLASH Start (128 KB)
            │ Vector Table (.isr_vector)│
            ├───────────────────────────┤
            │ Program Code (.text)      │
            ├───────────────────────────┤
            │ Read-Only Data (.rodata)  │
0x0802_0000 └───────────────────────────┘
            
0x2000_0000 ┌───────────────────────────┐ ◄── SRAM Start (20 KB)
            │ Initialized Data (.data)  │
            ├───────────────────────────┤
            │ Zero-Init Data (.bss)     │
            ├───────────────────────────┤
            │ Heap Space (grows up)     │
            │          ▼                │
            │          ▲                │
            │ Stack Space (grows down)  │
0x2000_5000 └───────────────────────────┘ ◄── Initial Stack Pointer (MSP)
```

---

## 🛠️ Building & Verification

### Prerequisites
- `arm-none-eabi-gcc` toolchain (v10.3+)
- GNU `make`
- `openocd` or `st-flash` (for hardware flashing)

### Compilation
```bash
# Clone the repository
git clone https://github.com/naveenkaranrs/stm32-bare-metal-drivers.git
cd stm32-bare-metal-drivers

# Compile the firmware image (.elf, .bin, .hex)
make all

# Output artifacts
ls -l build/
# firmware.elf
# firmware.bin
# firmware.hex
```

---

## 📄 License
Released under the [MIT License](LICENSE).
