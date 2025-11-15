/**
 * @file startup.c
 */

#include <stdint.h> 

// Stack pointer and initial stack location
extern uint32_t _stack_top;
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;

// Main function prototype
extern int main(void);

// Default handler
void Default_Handler(void)
{
    while (1);
}

// Weak aliases for all interrupt handlers
void Reset_Handler(void);
void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__((weak, alias("Default_Handler")));

// Vector table
__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void))(&_stack_top),  // Initial stack pointer
    Reset_Handler,                  // Reset handler
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, 0, 0, 0,                     // Reserved
    SVC_Handler,
    0, 0,                           // Reserved
    PendSV_Handler,
    SysTick_Handler,
    // Add more peripheral interrupts as needed
};

// Reset handler - entry point
void Reset_Handler(void)
{
    // Copy data section from flash to RAM
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    while (dst < &_edata)
    {
        *dst++ = *src++;
    }
    
    // Zero out BSS section
    dst = &_sbss;
    while (dst < &_ebss)
    {
        *dst++ = 0;
    }
    
    // Call main
    main();
    
    // Hang if main returns
    while (1);
}
