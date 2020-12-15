#include "handlers.hpp"

extern char __stack_end;

extern "C" void default_handler_wrapper()
{
    default_handler();
}

#define DEFINE_HANDLER(name) void name ## _handler() \
    __attribute__ ((weak, alias("default_handler_wrapper")));

#define irq0_handler     wwdg_handler
#define irq1_handler     pvd_handler
#define irq2_handler     tamper_handler
#define irq3_handler     rtc_handler
#define irq4_handler     flash_handler
#define irq5_handler     rcc_handler
#define irq6_handler     exti0_handler
#define irq7_handler     exti1_handler
#define irq8_handler     exti2_handler
#define irq9_handler     exti3_handler
#define irq10_handler    exti4_handler
#define irq11_handler    dma1_channel1_handler
#define irq12_handler    dma1_channel2_handler
#define irq13_handler    dma1_channel3_handler
#define irq14_handler    dma1_channel4_handler
#define irq15_handler    dma1_channel5_handler
#define irq16_handler    dma1_channel6_handler
#define irq17_handler    dma1_channel7_handler
#define irq18_handler    adc1_2_handler
#define irq19_handler    usb_hp_can_tx_handler
#define irq20_handler    usb_hp_can_rx0_handler
#define irq21_handler    can_rx1_handler
#define irq22_handler    can_sce_handler
#define irq23_handler    exti9_5_handler
#define irq24_handler    tim1_brk_handler
#define irq25_handler    tim1_up_handler
#define irq26_handler    tim1_trg_com_handler
#define irq27_handler    tim1_cc_handler
#define irq28_handler    tim2_handler
#define irq29_handler    tim3_handler
#define irq30_handler    tim4_handler
#define irq31_handler    i2c1_ev_handler
#define irq32_handler    i2c1_er_handler
#define irq33_handler    i2c2_ev_handler
#define irq34_handler    i2c2_er_handler
#define irq35_handler    spi1_handler
#define irq36_handler    spi2_handler
#define irq37_handler    usart1_handler
#define irq38_handler    usart2_handler
#define irq39_handler    usart3_handler
#define irq40_handler    exti15_10_handler
#define irq41_handler    rtc_alarm_handler
#define irq42_handler    usb_wakeup_handler
#define irq43_handler    tim8_brk_handler
#define irq44_handler    tim8_up_handler
#define irq45_handler    tim8_trg_com_handler
#define irq46_handler    tim8_cc_handler
#define irq47_handler    adc3_handler
#define irq48_handler    fsmC_handler
#define irq49_handler    sdiO_handler
#define irq50_handler    tim5_handler
#define irq51_handler    spi3_handler
#define irq52_handler    usart4_handler
#define irq53_handler    usart5_handler
#define irq54_handler    tim6_handler
#define irq55_handler    tim7_handler
#define irq56_handler    dma2_channel1_handler
#define irq57_handler    dma2_channel2_handler
#define irq58_handler    dma2_channel3_handler
#define irq59_handler    dma2_channel4_5_handler

DEFINE_HANDLER(nmi)
DEFINE_HANDLER(hard_fault)
DEFINE_HANDLER(mem_manage)
DEFINE_HANDLER(bus_fault)
DEFINE_HANDLER(usage_fault)
DEFINE_HANDLER(sv_call)
DEFINE_HANDLER(debug_monitor)
DEFINE_HANDLER(pend_sv)
DEFINE_HANDLER(systick)
DEFINE_HANDLER(irq0)
DEFINE_HANDLER(irq1)
DEFINE_HANDLER(irq2)
DEFINE_HANDLER(irq3)
DEFINE_HANDLER(irq4)
DEFINE_HANDLER(irq5)
DEFINE_HANDLER(irq6)
DEFINE_HANDLER(irq7)
DEFINE_HANDLER(irq8)
DEFINE_HANDLER(irq9)
DEFINE_HANDLER(irq10)
DEFINE_HANDLER(irq11)
DEFINE_HANDLER(irq12)
DEFINE_HANDLER(irq13)
DEFINE_HANDLER(irq14)
DEFINE_HANDLER(irq15)
DEFINE_HANDLER(irq16)
DEFINE_HANDLER(irq17)
DEFINE_HANDLER(irq18)
DEFINE_HANDLER(irq19)
DEFINE_HANDLER(irq20)
DEFINE_HANDLER(irq21)
DEFINE_HANDLER(irq22)
DEFINE_HANDLER(irq23)
DEFINE_HANDLER(irq24)
DEFINE_HANDLER(irq25)
DEFINE_HANDLER(irq26)
DEFINE_HANDLER(irq27)
DEFINE_HANDLER(irq28)
DEFINE_HANDLER(irq29)
DEFINE_HANDLER(irq30)
DEFINE_HANDLER(irq31)
DEFINE_HANDLER(irq32)
DEFINE_HANDLER(irq33)
DEFINE_HANDLER(irq34)
DEFINE_HANDLER(irq35)
DEFINE_HANDLER(irq36)
DEFINE_HANDLER(irq37)
DEFINE_HANDLER(irq38)
DEFINE_HANDLER(irq39)
DEFINE_HANDLER(irq40)
DEFINE_HANDLER(irq41)
DEFINE_HANDLER(irq42)
DEFINE_HANDLER(irq43)
DEFINE_HANDLER(irq44)
DEFINE_HANDLER(irq45)
DEFINE_HANDLER(irq46)
DEFINE_HANDLER(irq47)
DEFINE_HANDLER(irq48)
DEFINE_HANDLER(irq49)
DEFINE_HANDLER(irq50)
DEFINE_HANDLER(irq51)
DEFINE_HANDLER(irq52)
DEFINE_HANDLER(irq53)
DEFINE_HANDLER(irq54)
DEFINE_HANDLER(irq55)
DEFINE_HANDLER(irq56)
DEFINE_HANDLER(irq57)
DEFINE_HANDLER(irq58)
DEFINE_HANDLER(irq59)

/*
 * Set up the vector table.
 *
 * "__attribute__ ((section(".vectors")))" defines a variable attribute which
 * instructs GCC to emit this variable into the beginning of the .vectors
 * section. This is later found by the linker.
 *
 * Type is vector of (void (*)()) because table is filled with (mostly) function
 * pointers.
 *
 * Since this table never changes and is stored in flash, it's declared const.
 *
 * Const-qualification of a non-local non-volatile variable gives it internal
 * linkage. To provide it with external linkage, declare as extern. This allows
 * the structure to be accessed from other translation units.
 *
 * First entry contains the reset value of the stack pointer. Since the stack
 * grows towards lower addresses and the start of SRAM is at 0x20000000,
 * <address value> - 0x20000000 specifies the stack size.
 *
 * The second entry corresponds to the reset handler, which is where program
 * execution starts once the microcontroller resets/powers on.
 */
typedef void (* const const_func_ptr_t)();
extern const_func_ptr_t vectors[] __attribute__ ((section(".vectors"))) =
{
    (void (*)())&__stack_end,
    reset_handler,
    nmi_handler,
    hard_fault_handler,
    mem_manage_handler,
    bus_fault_handler,
    usage_fault_handler,
    0,
    0,
    0,
    0,
    sv_call_handler,
    debug_monitor_handler,
    0,
    pend_sv_handler,
    systick_handler,
    irq0_handler,
    irq1_handler,
    irq2_handler,
    irq3_handler,
    irq4_handler,
    irq5_handler,
    irq6_handler,
    irq7_handler,
    irq8_handler,
    irq9_handler,
    irq10_handler,
    irq11_handler,
    irq12_handler,
    irq13_handler,
    irq14_handler,
    irq15_handler,
    irq16_handler,
    irq17_handler,
    irq18_handler,
    irq19_handler,
    irq20_handler,
    irq21_handler,
    irq22_handler,
    irq23_handler,
    irq24_handler,
    irq25_handler,
    irq26_handler,
    irq27_handler,
    irq28_handler,
    irq29_handler,
    irq30_handler,
    irq31_handler,
    irq32_handler,
    irq33_handler,
    irq34_handler,
    irq35_handler,
    irq36_handler,
    irq37_handler,
    irq38_handler,
    irq39_handler,
    irq40_handler,
    irq41_handler,
    irq42_handler,
    irq43_handler,
    irq44_handler,
    irq45_handler,
    irq46_handler,
    irq47_handler,
    irq48_handler,
    irq49_handler,
    irq50_handler,
    irq51_handler,
    irq52_handler,
    irq53_handler,
    irq54_handler,
    irq55_handler,
    irq56_handler,
    irq57_handler,
    irq58_handler,
    irq59_handler,
};
