#!/bin/bash

./fusee-launcher-new/fusee-launcher.py ./payloads/patch_irom.bin

sleep 1

./utils/nvflash_v3.08.1700 --getbct --bct current.bct --configfile ./utils/flash.cfg
