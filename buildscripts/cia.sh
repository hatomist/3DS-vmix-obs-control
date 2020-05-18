../buildscripts/gen_icon.sh
../buildscripts/gen_banner.sh
makerom -f cia -o 3DSBuildTemplate.cia -DAPP_ENCRYPTED=false -rsf ../resources/template.rsf -target t -exefslogo -elf 3DSBuildTemplate -icon icon.icn -banner banner.bnr -DAPP_TITLE="shit"  -DAPP_ROMFS="../romfs" -DAPP_SYSTEM_MODE="64MB" -DAPP_SYSTEM_MODE_EXT="Legacy" -major "0" -minor "0" -micro "1"
