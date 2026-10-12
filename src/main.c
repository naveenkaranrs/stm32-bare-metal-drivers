#include <stdint.h>

/* Memory-Mapped Base Addresses */
#define PERIPH_BASE       (0x40000000UL)
#define APB2PERIPH_BASE   (PERIPH_BASE + 0x10000UL)
#define AHBPERIPH_BASE    (PERIPH_BASE + 0x20000UL)

#define RCC_BASE          (AHBPERIPH_BASE + 0x1000UL)
#define GPIOA_BASE        (APB2PERIPH_BASE + 0x0800UL)

/* RCC & GPIO Register Structs */
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_TypeDef;

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

#define RCC   ((RCC_TypeDef *)RCC_BASE)
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)

/* Software Delay Routine */
static void delay_cycles(volatile uint32_t count) {
    while (count--) {
        __asm__ volatile ("nop");
    }
}

int main(void) {
    /* 1. Enable GPIOA Peripheral Clock (Bit 2 in APB2ENR) */
    RCC->APB2ENR |= (1 << 2);

    /* 2. Configure PA5 (Nucleo-64 User LED) as General Purpose Output Push-Pull (50MHz max) */
    /* Clear CNF5[1:0] (0b00) and set MODE5[1:0] to 0b11 (Output 50MHz) */
    GPIOA->CRL &= ~(0xF << 20);
    GPIOA->CRL |= (0x3 << 20);

    /* 3. Blink Superloop using atomic Bit Set / Reset registers */
    while (1) {
        GPIOA->BSRR = (1 << 5);         /* Turn PA5 HIGH */
        delay_cycles(800000);
        GPIOA->BRR  = (1 << 5);         /* Turn PA5 LOW */
        delay_cycles(800000);
    }

    return 0;
}
