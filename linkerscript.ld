OUTPUT_FORMAT(elf32-littlearm)
OUTPUT_ARCH(arm)

LD_FEATURE ("SANE_EXPR")

MEMORY {
    FLASH : ORIGIN = 0x08000000, LENGTH = 64K
    RAM :   ORIGIN = 0x20000000, LENGTH = 20K
}

__stack_size = 0x400;

SECTIONS {
    .vectors : {
        KEEP(*(.vectors))
    } > FLASH

    .text : {
        *(.text*)
    } > FLASH

    .rodata : {
        *(.rodata*)
    } > FLASH

    .stack : {
        __stack_start = .;
        . = . + __stack_size;
        __stack_end = .;
    } > RAM

    .bss : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    } > RAM

    .data : {
        *(.data*)
        . = ALIGN(4);
    } > RAM AT>FLASH

    __data_start_flash = LOADADDR(.data);
    __data_start_ram = ADDR(.data);
    __data_size = SIZEOF(.data);

    /* Debug info. */
    .debug_info 0 : { *(.debug_info*) }
    .debug_abbrev 0 : { *(.debug_abbrev*) }
    .debug_loc 0 : { *(.debug_loc*) }
    .debug_aranges 0 : { *(.debug_aranges*) }
    .debug_ranges 0 : { *(.debug_ranges*) }
    .debug_macro 0 : { *(.debug_macro*) }
    .debug_line 0 : { *(.debug_line*) }
    .debug_str 0 : { *(.debug_str*) }
    .debug_frame 0 : { *(.debug_frame*) }

    /DISCARD/ : {
        *(.note.GNU-stack)
        *(.gnu_debuglink)
        *(.gnu.lto_*)
        *(.comment)
        *(.ARM.attributes)
    }

    /* Error on unknown sections. */
    .unmatched : {
        KEEP("linker stubs"(*)) /* .glue_7 .glue_7t .vfp11_veneer .v4_bx */
        KEEP(*(.iplt))
        KEEP(*(.rel.iplt))
        KEEP(*(.igot.plt))
    } > FLASH
    ASSERT(SIZEOF(.unmatched) == 0, "allocated sections not matched")
}
