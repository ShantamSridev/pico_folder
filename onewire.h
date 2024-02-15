#include "one_wire.h"
#include "pico/stdlib.h"
#include "pindefs.h"

One_wire one_wire(ONE_WIRE_BUS);
rom_address_t address{};

void init_onewire(){
    one_wire.init();
}

float read_temp(){
    one_wire.single_device_read_rom(address);
    printf("Device Address: %02x%02x%02x%02x%02x%02x%02x%02x\n", address.rom[0], address.rom[1], address.rom[2], address.rom[3], address.rom[4], address.rom[5], address.rom[6], address.rom[7]);
    one_wire.convert_temperature(address, true, false);
    return one_wire.temperature(address);
}

// float readTemp() {
//     // Send the command to get temperatures
//   sensors.requestTemperatures(); 

//   //print the temperature in Celsius
//   //Serial.print("Temperature: ");
//   float newtemp = sensors.getTempCByIndex(0);
//   if (newtemp>0){
//     return newtemp;
//   }
//   else{
//     return 0;
//   }
//   //Serial.print(newtemp);
//   //Serial.print("C  |  ");
// }
