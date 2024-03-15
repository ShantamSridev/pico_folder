#include "structure.h"

// Define the shared FIFO instance
SharedFIFO fifo;

void process_from_fifo(MyPID& pid, MyAngle& angle) { //CORE0
    while (fifo.readIndex != fifo.writeIndex) {
        // There is data in the FIFO
        int item = fifo.buffer[fifo.readIndex];
        fifo.readIndex = (fifo.readIndex + 1) % FIFO_SIZE;

        // Process the item
        // For example, just print it out
        printf("Processing item: %d\n", item);
        getstruct(uint8_t(item), pid, angle);
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


void getstruct(uint8_t addin, MyPID& pid, MyAngle& angle){
    switch(addin){
        case 0:
            // Action for addin = 0
            break;
        case I2C_GET_ANGLE:
            // Action for addin = 4
            break;
        case 8:
            // Action for addin = 8
            break;
        case 12:
            // Action for addin = 12
            break;
        case I2C_SETANGLE:
            // Action for addin = 16
            float Requiredangle = memToFloat(I2C_SETANGLE);
            angle.setAngle(Requiredangle,pid);
            multicore_mem[I2C_SETANGLE] = Requiredangle;
            break;
        case I2C_SETSPEED:
            // Action for addin = 20
            float target = memToFloat(I2C_SETSPEED);
            pid.setTarget(target);
            multicore_mem[I2C_SETSPEED] = target;
            break;
        case I2C_SETP:
            // Action for addin = 24
            float P = memToFloat(I2C_SETP);
            pid.setP(P);
            multicore_mem[I2C_SETP] = P;
            break;
        case I2C_SETI:
            // Action for addin = 28
            float I = memToFloat(I2C_SETI);
            pid.setI(I);
            multicore_mem[I2C_SETI] = I;
            break;
        case I2C_SETD:
            // Action for addin = 32
            float D = memToFloat(I2C_SETD);
            pid.setD(D);
            multicore_mem[I2C_SETD] = D;
            break;
        case 36:
            // Action for addin = 36
            break;
        case 40:
            // Action for addin = 40
            break;
        case 44:
            // Action for addin = 44
            break;
        case 48:
            // Action for addin = 48
            break;
        case 52:
            // Action for addin = 52
            break;
        case 56:
            // Action for addin = 56
            break;
        case 60:
            // Action for addin = 60
            break;
        case 64:
            // Action for addin = 64
            break;
        case 68:
            // Action for addin = 68
            break;
        case 72:
            // Action for addin = 72
            break;
        case 76:
            // Action for addin = 76
            break;
        case 80:
            // Action for addin = 80
            break;
        case 84:
            // Action for addin = 84
            break;
        case 88:
            // Action for addin = 88
            break;
        case 92:
            // Action for addin = 92
            break;
        case 96:
            // Action for addin = 96
            break;
        case 100:
            // Action for addin = 100
            break;
        case 104:
            // Action for addin = 104
            break;
        case 108:
            // Action for addin = 108
            break;
        case 112:
            // Action for addin = 112
            break;
        case 116:
            // Action for addin = 116
            break;
        case 120:
            // Action for addin = 120
            break;
        case 124:
            // Action for addin = 124
            break;
        case 128:
            // Action for addin = 128
            break;
        case 132:
            // Action for addin = 132
            break;
        case 136:
            // Action for addin = 136
            break;
        case 140:
            // Action for addin = 140
            break;
        case 144:
            // Action for addin = 144
            break;
        case 148:
            // Action for addin = 148
            break;
        case 152:
            // Action for addin = 152
            break;
        case 156:
            // Action for addin = 156
            break;
        case 160:
            // Action for addin = 160
            break;
        case 164:
            // Action for addin = 164
            break;
        case 168:
            // Action for addin = 168
            break;
        case 172:
            // Action for addin = 172
            break;
        case 176:
            // Action for addin = 176
            break;
        case 180:
            // Action for addin = 180
            break;
        case 184:
            // Action for addin = 184
            break;
        case 188:
            // Action for addin = 188
            break;
        case 192:
            // Action for addin = 192
            break;
        case 196:
            // Action for addin = 196
            break;
        case 200:
            // Action for addin = 200
            break;
        case 204:
            // Action for addin = 204
            break;
        case 208:
            // Action for addin = 208
            break;
        case 212:
            // Action for addin = 212
            break;
        case 216:
            // Action for addin = 216
            break;
        case 220:
            // Action for addin = 220
            break;
        case 224:
            // ONWARDS RESERVED FOR REQUEST
            break;
        default:
            // Default action if addin is not a multiple of 4 or out of range
            printf("DONE GOOFED. Not a multiple of 4 or accessing somethign wrong.");
            break;
    }
}