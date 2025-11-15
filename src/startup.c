/**
 * @file startup.c
 */

#include <stdint.h>
#include <string.h>

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
void NMI_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void);
void MemManage_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)       __attribute__((weak, alias("Default_Handler")));

// LM3S6965 peripheral interrupts
void GPIO_PortA_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void GPIO_PortB_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void GPIO_PortC_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void GPIO_PortD_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void GPIO_PortE_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void UART0_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void UART1_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void SSI0_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void I2C0_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void PWM0_Fault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void PWM0_Gen0_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PWM0_Gen1_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PWM0_Gen2_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void QEI0_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void ADC0_Seq0_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void ADC0_Seq1_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void ADC0_Seq2_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void ADC0_Seq3_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void Watchdog_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void Timer0A_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void Timer0B_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void Timer1A_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void Timer1B_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void Timer2A_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void Timer2B_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void Analog_Comp0_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void Analog_Comp1_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void System_Control_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Flash_Control_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIO_PortF_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void GPIO_PortG_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void UART2_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void Timer3A_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void Timer3B_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void I2C1_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void QEI1_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void Ethernet_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void Hibernate_Handler(void)     __attribute__((weak, alias("Default_Handler")));

// Vector table (47 entries for LM3S6965)
__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void))(&_stack_top),       // 0: Initial stack pointer
    Reset_Handler,                       // 1: Reset handler
    NMI_Handler,                         // 2: Non-Maskable Interrupt
    HardFault_Handler,                   // 3: Hard Fault
    MemManage_Handler,                   // 4: Memory Management
    BusFault_Handler,                    // 5: Bus Fault
    UsageFault_Handler,                  // 6: Usage Fault
    0, 0, 0, 0,                          // 7-10: Reserved
    SVC_Handler,                         // 11: SVCall
    DebugMon_Handler,                    // 12: Debug Monitor
    0,                                   // 13: Reserved
    PendSV_Handler,                      // 14: PendSV
    SysTick_Handler,                     // 15: SysTick
    // Peripheral interrupts (16-47)
    GPIO_PortA_Handler,                  // 16: GPIO Port A
    GPIO_PortB_Handler,                  // 17: GPIO Port B
    GPIO_PortC_Handler,                  // 18: GPIO Port C
    GPIO_PortD_Handler,                  // 19: GPIO Port D
    GPIO_PortE_Handler,                  // 20: GPIO Port E
    UART0_Handler,                       // 21: UART0
    UART1_Handler,                       // 22: UART1
    SSI0_Handler,                        // 23: SSI0
    I2C0_Handler,                        // 24: I2C0
    PWM0_Fault_Handler,                  // 25: PWM0 Fault
    PWM0_Gen0_Handler,                   // 26: PWM0 Generator 0
    PWM0_Gen1_Handler,                   // 27: PWM0 Generator 1
    PWM0_Gen2_Handler,                   // 28: PWM0 Generator 2
    QEI0_Handler,                        // 29: QEI0
    ADC0_Seq0_Handler,                   // 30: ADC0 Sequence 0
    ADC0_Seq1_Handler,                   // 31: ADC0 Sequence 1
    ADC0_Seq2_Handler,                   // 32: ADC0 Sequence 2
    ADC0_Seq3_Handler,                   // 33: ADC0 Sequence 3
    Watchdog_Handler,                    // 34: Watchdog Timer
    Timer0A_Handler,                     // 35: Timer 0A
    Timer0B_Handler,                     // 36: Timer 0B
    Timer1A_Handler,                     // 37: Timer 1A
    Timer1B_Handler,                     // 38: Timer 1B
    Timer2A_Handler,                     // 39: Timer 2A
    Timer2B_Handler,                     // 40: Timer 2B
    Analog_Comp0_Handler,                // 41: Analog Comparator 0
    Analog_Comp1_Handler,                // 42: Analog Comparator 1
    0,                                   // 43: Reserved
    System_Control_Handler,              // 44: System Control (PLL, OSC, Watchdog)
    Flash_Control_Handler,               // 45: Flash Memory Control
    GPIO_PortF_Handler,                  // 46: GPIO Port F
    GPIO_PortG_Handler,                  // 47: GPIO Port G (not on LM3S6965)
    0,                                   // 48: Reserved
    UART2_Handler,                       // 49: UART2
    0,                                   // 50: Reserved
    Timer3A_Handler,                     // 51: Timer 3A
    Timer3B_Handler,                     // 52: Timer 3B
    I2C1_Handler,                        // 53: I2C1
    QEI1_Handler,                        // 54: QEI1
    0, 0, 0,                             // 55-57: Reserved
    Ethernet_Handler,                    // 58: Ethernet
    Hibernate_Handler,                   // 59: Hibernate
};

// Reset handler - entry point
void Reset_Handler(void)
{
    // Copy data section from flash to RAM
    size_t data_size = (size_t)(&_edata - &_sdata);
    if (data_size > 0)
    {
        memcpy(&_sdata, &_sidata, (data_size * sizeof(uint32_t)));
    }
    
    // Zero out BSS section
    size_t bss_size = (size_t)(&_ebss - &_sbss);
    if (bss_size > 0)
    {
        memset(&_sbss, 0, (bss_size * sizeof(uint32_t)));
    }
    
    // Call main
    main();
    
    // Hang if main returns
    while (1);
}

void HardFault_Handler(void)
{
    asm volatile ("bkpt #0");
    while (1);
}
