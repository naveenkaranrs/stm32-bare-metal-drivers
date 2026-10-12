# Makefile for STM32F103RB Bare-Metal Firmware
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

MCU     = -mcpu=cortex-m3 -mthumb
CFLAGS  = $(MCU) -Wall -Wextra -Werror -O2 -g3 -std=c99 -ffreestanding \
          -fdata-sections -ffunction-sections -Iinclude
LDFLAGS = $(MCU) -Tstm32f103rb.ld -nostartfiles -Wl,--gc-sections -Wl,-Map=build/firmware.map

SRCS    = src/main.c src/startup.c
OBJS    = $(patsubst src/%.c, build/%.o, $(SRCS))
TARGET  = build/firmware

.PHONY: all clean

all: $(TARGET).bin $(TARGET).hex
	@$(SIZE) $(TARGET).elf

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -rf build
