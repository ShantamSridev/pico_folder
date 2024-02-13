#include "modules/pico-onewire/api/one_wire.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

One_wire one_wire(3);
rom_address_t address{};

void init_onewire(int ONE_WIRE_BUS){
    One_wire one_wire(ONE_WIRE_BUS);
    one_wire.init();
    rom_address_t address{};
}

float read_temp(){
    one_wire.single_device_read_rom(address);
    printf("Device Address: %02x%02x%02x%02x%02x%02x%02x%02x\n", address.rom[0], address.rom[1], address.rom[2], address.rom[3], address.rom[4], address.rom[5], address.rom[6], address.rom[7]);
    one_wire.convert_temperature(address, true, false);
    return one_wire.temperature(address);
}
