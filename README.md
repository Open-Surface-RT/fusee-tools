# fusee-tools
Useful tools for Fusee Gelee on T20 / T30 / T114
# Usage
apt install build-essential gcc-arm-none-eabi python3-usb git.. etc

git clone https://github.com/Open-Surface-RT/fusee-tools
cd fusee-tools
git submodule init
git submodule update
chmod +x *.sh
cd payloads
# modify payloads/Makefile " LDFLAGS = -nostdlib -L /usr/lib/gcc/arm-none-eabi/X.X.X -lgcc " replacing X.X.X with installed version number. (ls /usr/lib/gcc/arm-none-eabi)
make ARCH=arm CROSS_COMPILE=arm-none-eabi-

# Executing exploit - plug in device via usb to host linux pc usb 3 port and enter RCM with vol up + power on.
# modify ./get_bct.sh ./fusee-launcher-new/fusee-launcher.py ./payloads/patch_irom.bin to use correct patch in payloads/ eg T30_patch_iron.bin
./get_bct.sh 
