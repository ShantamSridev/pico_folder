![image](https://github.com/ShantamSridev/pico_folder/assets/50525078/32ce31c1-5891-42cf-b1c6-f7b33097b34c)

sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential

MINICOM

ls /dev/tty* | grep USB

sudo minicom -D /dev/ttyUSB0

cp hello_usb_cpp.uf2 /media/paco/RPI-RP2/


cmake -DPICO_BOARD=pico_w ..
