#include "onewire.h"

// One_wire one_wire(ONE_WIRE_BUS);
// rom_address_t address{};

// void init_onewire(){
//     one_wire.init();
// }


float read_temp(One_wire& one_wires, rom_address_t& addr){
    one_wires.single_device_read_rom(addr);
    printf("Device Address: %02x%02x%02x%02x%02x%02x%02x%02x\n", addr.rom[0], addr.rom[1], addr.rom[2], addr.rom[3], addr.rom[4], addr.rom[5], addr.rom[6], addr.rom[7]);
    one_wires.convert_temperature(addr, true, false);
    return float(one_wires.temperature(addr));
}
