set(PROJECT hello_usb_cpp)

cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(${PROJECT} C CXX)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT}
    main.cpp
)

target_sources(${PROJECT} PRIVATE
        main.cpp
        one_wire.cpp
        one_wire.h
        )

pico_enable_stdio_usb(${PROJECT} 0)
pico_enable_stdio_uart(${PROJECT} 1)

pico_add_extra_outputs(${PROJECT})

target_link_directories(${PROJECT} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

#add_subdirectory(modules/pico-onewire)

target_link_libraries(${PROJECT} 
    pico_stdlib 
    hardware_pwm 
    hardware_gpio
    hardware_timer
    hardware_adc
    pico_time
    #pico_one_wire
)
