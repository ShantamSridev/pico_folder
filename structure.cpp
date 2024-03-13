#include "structure.h"

// Define the shared FIFO instance
SharedFIFO fifo;

void process_from_fifo() { //CORE0
    while (fifo.readIndex != fifo.writeIndex) {
        // There is data in the FIFO
        int item = fifo.buffer[fifo.readIndex];
        fifo.readIndex = (fifo.readIndex + 1) % FIFO_SIZE;

        // Process the item
        // For example, just print it out
        printf("Processing item: %d\n", item);

        // Call specific function here
    }
}


void add_to_fifo(int item) { //CORE1
    auto nextIndex = (fifo.writeIndex + 1) % FIFO_SIZE;
    while (nextIndex == fifo.readIndex) {
        // Buffer is full, wait or handle this condition
        printf("Buffer is full, WAITING with item : %d\n", item);
    }

    // Add the item to the buffer and update the write index
    fifo.buffer[fifo.writeIndex] = item;
    fifo.writeIndex = nextIndex;
}


void getstruct(uint8_t addin){
    switch(addin){
        case 0:
            break;
        case 4:
            break;
        case 8:
            
            break;
    }
}