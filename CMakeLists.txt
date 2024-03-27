set(PROJECT hello_usb_cpp)

cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(${PROJECT} C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT}
    main.cpp
    pid.cpp
    encoder.cpp
    onewire.cpp
    current.cpp
    pwm.cpp
    velocity.cpp
    angle.cpp
    i2c.cpp
    structure.cpp
    RBCurrentVolt.cpp
    modules/MiniPID/MiniPID.cpp
)

pico_enable_stdio_usb(${PROJECT} 0)
pico_enable_stdio_uart(${PROJECT} 1)

pico_add_extra_outputs(${PROJECT})

# Include directories for i2c_slave
target_include_directories(${PROJECT} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/modules/pico_i2c_slave/i2c_slave/include)

add_subdirectory(modules/pico-onewire)
add_subdirectory(modules/pico_i2c_slave)

target_link_libraries(${PROJECT} 
    pico_stdlib 
    pico_multicore
    hardware_pwm 
    hardware_gpio
    hardware_timer
    hardware_adc
    pico_time
    pico_one_wire
    pico_i2c_slave
)
