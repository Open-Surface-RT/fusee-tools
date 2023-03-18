#!/bin/bash

./fusee-launcher-new/fusee-launcher.py payloads/patch_irom.bin

sleep 1

./utils/nvflash_v3.08.1700_miniloader_patched --setbct --bct current.bct --configfile ./utils/flash.cfg --bl ./uboot/u-boot-dtb-tegra.bin --go
