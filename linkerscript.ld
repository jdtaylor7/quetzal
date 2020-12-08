OUTPUT_FORMAT(elf32-littlearm)
OUTPUT_ARCH(arm)

LD_FEATURE ("SANE_EXPR")

MEMORY {
    FLASH : ORIGIN = 0x08000000, LENGTH = 64K
}

SECTIONS {
    .vectors : {
        KEEP(*(.vectors))
    } > FLASH

    .text : {
        *(.text*)
    } > FLASH

    .rodata : {
        *(*.rodata*)
    } > FLASH

    /* Error on unknown sections. */
    .unmatched : {
        KEEP("linker stubs"(*)) /* .glue_7 .glue_7t .vfp11_veneer .v4_bx */
        KEEP(*(.iplt))
        KEEP(*(.rel.iplt))
        KEEP(*(.igot.plt))
    } > FLASH

    ASSERT(SIZEOF(.unmatched) == 0, "allocated sections not matched")

    /DISCARD/ : {
        *(.note.GNU-stack)
        *(.gnu_debuglink)
        *(.gnu.lto_*)
        *(.comment)
        *(.ARM.attributes)
    }
}
