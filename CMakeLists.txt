set(PROJECT hello_usb_cpp)

cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(${PROJECT} C CXX ASM)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT}
    main.cpp
)

pico_enable_stdio_usb(${PROJECT} 1)
pico_enable_stdio_uart(${PROJECT} 0)

pico_add_extra_outputs(${PROJECT})

target_link_directories(${PROJECT} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT} pico_stdlib)
