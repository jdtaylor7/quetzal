#!/bin/sh

# Cygwin.
# ST-LINK_CLI.exe -c
# ST-LINK_CLI.exe -P build/quetzal.bin 0x08000000
# ST-LINK_CLI.exe -Rst

# Arch Linux.
st-flash --reset write build/quetzal 0x08000000
