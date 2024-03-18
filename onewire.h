#ifndef ONEWIRE_H
#define ONEWIRE_H

#include "pico/stdlib.h"
#include "pindefs.h"
#include "modules/pico-onewire/api/one_wire.h"

// One_wire one_wire(ONE_WIRE_BUS);
// rom_address_t address{};

// void init_onewire(){
//     one_wire.init();
// }


float read_temp(One_wire& one_wires, rom_address_t& addr);

#endif