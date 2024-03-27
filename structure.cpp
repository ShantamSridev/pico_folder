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
        case 0: {
            // Action for addin = 0
            break;
        }
        case I2C_GET_ANGLE: {
            // Action for addin = I2C_GET_ANGLE
            //No value needs to be read
            angle.runAngleInit(pid);
            break;
        }
        case I2C_SETANGLE: {
            float Requiredangle = memToFloat(I2C_SETANGLE);
            printf("ANGLE %f\n",Requiredangle);
            angle.setAngle(Requiredangle, pid);
            multicore_mem[I2C_SETANGLE] = Requiredangle;
            break;
        }
        case I2C_SETSPEED: {
            float target = memToFloat(I2C_SETSPEED);
            pid.setTarget(target);
            pid.run();
            multicore_mem[I2C_SETSPEED] = target;
            break;
        }
        case I2C_SETP: {
            float P = memToFloat(I2C_SETP);
            pid.setP(P);
            multicore_mem[I2C_SETP] = P;
            break;
        }
        case I2C_SETI: {
            float I = memToFloat(I2C_SETI);
            pid.setI(I);
            multicore_mem[I2C_SETI] = I;
            break;
        }
        case I2C_SETD: {
            float D = memToFloat(I2C_SETD);
            pid.setD(D);
            multicore_mem[I2C_SETD] = D;
            break;
        }
        case I2C_SETPIDRATE: {
            // Action for addin = 36
            float rate = memToFloat(I2C_SETPIDUP);
            pid.setOutputRampRate(rate);
            multicore_mem[I2C_SETPIDUP] = rate;
            break;
        }
        case I2C_SETPIDUP: {
            // Action for addin = 40
            float upper = memToFloat(I2C_SETPIDUP);
            float lower = memToFloat(I2C_SETPIDLOW);

            pid.setOutputLimits(upper,lower);
            multicore_mem[I2C_SETPIDUP] = upper;
            multicore_mem[I2C_SETPIDLOW] = lower;
            break;
        }
        case I2C_SETPIDLOW: {
            // Action for addin = 44
            float upper = memToFloat(I2C_SETPIDUP);
            float lower = memToFloat(I2C_SETPIDLOW);

            pid.setOutputLimits(upper,lower);
            multicore_mem[I2C_SETPIDUP] = upper;
            multicore_mem[I2C_SETPIDLOW] = lower;
            break;
        }
        case 52: {
            // Action for addin = 52
            break;
        }
        case 68: {
            // Action for addin = 68
            break;
        }
        case 72: {
            // Action for addin = 72
            break;
        }
        case 100: {
            // Action for addin = 100
            break;
        }
        case 104: {
            // Action for addin = 104
            break;
        }
        case I2C_SETFREQTEMP: {
            // Action for addin = 116

            break;
        }
        case I2C_SETLENGTHTEMP: {
            // Action for addin = 120
            break;
        }
        case I2C_SETFREQ_A_V: {
            // Action for addin = 132
            float frequency = memToFloat(I2C_SETFREQ_A_V);
            set_timer_CurrAndVolt(uint32_t(frequency));
            multicore_mem[I2C_SETFREQ_A_V] = frequency;
            break;
        }
        case I2C_SETLENGTH_A_V: {
            // Action for addin = 136
            float length = memToFloat(I2C_SETLENGTH_A_V);
            RBCurrent.resize(uint32_t(length));
            RBVoltage.resize(uint32_t(length));
            multicore_mem[I2C_SETLENGTH_A_V] = length;
            break;
        }
        case 148: {
            // Action for addin = 148
            break;
        }
        case 152: {
            // Action for addin = 152
            break;
        }
        case 156: {
            // Action for addin = 156
            break;
        }
        case 160: {
            // Action for addin = 160
            break;
        }
        case 164: {
            // Action for addin = 164
            break;
        }
        case 168: {
            // Action for addin = 168
            break;
        }
        case 172: {
            // Action for addin = 172
            break;
        }
        case 176: {
            // Action for addin = 176
            break;
        }
        case 180: {
            // Action for addin = 180
            break;
        }
        case 184: {
            // Action for addin = 184
            break;
        }
        case 188: {
            // Action for addin = 188
            break;
        }
        case 192: {
            // Action for addin = 192
            break;
        }
        case 196: {
            // Action for addin = 196
            break;
        }
        case 200: {
            // Action for addin = 200
            break;
        }
        case 204: {
            // Action for addin = 204
            break;
        }
        case 208: {
            // Action for addin = 208
            break;
        }
        case 212: {
            // Action for addin = 212
            break;
        }
        case 216: {
            // Action for addin = 216
            break;
        }
        case 220: {
            // Action for addin = 220
            break;
        }
        case 224: {
            // ONWARDS RESERVED FOR REQUEST
            break;
        }
        default: {
            printf("DONE GOOFED. Non-writtable address used.");
            break;
        }
    }
}

void getReqstruct(uint8_t addin){
    switch(addin){
        case 0: {
            // Action for addin = 0
            break;
        }
        case I2C_REQANGLE: {
            // Action for addin = 8
            float angle = (rev_check)/0.6222222222; //Direct read cuz i can't use the class over multicore
            printf("rev_check %d\n", rev_check);
            printf("ANGLE %f\n",angle);
            feedFloatToMem(angle);
            break;
        }
        case I2C_REQSPEED: {
            // Action for addin = 12
            float vel = static_cast<float>(calc_velocity());
            feedFloatToMem(vel);
            break;
        }
        case 48: {
            // Action for addin = 48
            break;
        }
        case 52: {
            // Action for addin = 52
            break;
        }
        case 56: {
            // Action for addin = 56
            break;
        }
        case 60: {
            // Action for addin = 60
            break;
        }
        case 64: {
            // Action for addin = 64
            break;
        }
        case 68: {
            // Action for addin = 68
            break;
        }
        case 72: {
            // Action for addin = 72
            break;
        }
        case 76: {
            // Action for addin = 76
            break;
        }
        case 80: {
            // Action for addin = 80
            break;
        }
        case 84: {
            // Action for addin = 84
            break;
        }
        case 88: {
            // Action for addin = 88
            break;
        }
        case 92: {
            // Action for addin = 92
            break;
        }
        case 96: {
            // Action for addin = 96
            break;
        }
        case 100: {
            // Action for addin = 100
            break;
        }
        case 104: {
            // Action for addin = 104
            break;
        }
        case 108: {
            // Action for addin = 108
            break;
        }
        case 112: {
            // Action for addin = 112
            break;
        }
        case I2C_SETFREQTEMP: {
            // Action for addin = 116

            break;
        }
        case I2C_SETLENGTHTEMP: {
            // Action for addin = 120
            break;
        }
        case 124: {
            // Action for addin = 124
            break;
        }
        case 128: {
            // Action for addin = 128
            break;
        }
        case I2C_SETFREQ_A_V: {
            // Action for addin = 132
            break;
        }
        case I2C_SETLENGTH_A_V: {
            // Action for addin = 136
            break;
        }
        case 140: {
            // Action for addin = 140
            break;
        }
        case 144: {
            // Action for addin = 144
            break;
        }
        case 148: {
            // Action for addin = 148
            break;
        }
        case 152: {
            // Action for addin = 152
            break;
        }
        case 156: {
            // Action for addin = 156
            break;
        }
        case 160: {
            // Action for addin = 160
            break;
        }
        case 164: {
            // Action for addin = 164
            break;
        }
        case 168: {
            // Action for addin = 168
            break;
        }
        case 172: {
            // Action for addin = 172
            break;
        }
        case 176: {
            // Action for addin = 176
            break;
        }
        case 180: {
            // Action for addin = 180
            break;
        }
        case 184: {
            // Action for addin = 184
            break;
        }
        case 188: {
            // Action for addin = 188
            break;
        }
        case 192: {
            // Action for addin = 192
            break;
        }
        case 196: {
            // Action for addin = 196
            break;
        }
        case 200: {
            // Action for addin = 200
            break;
        }
        case 204: {
            // Action for addin = 204
            break;
        }
        case 208: {
            // Action for addin = 208
            break;
        }
        case 212: {
            // Action for addin = 212
            break;
        }
        case 216: {
            // Action for addin = 216
            break;
        }
        case 220: {
            // Action for addin = 220
            break;
        }
        case 224: {
            // ONWARDS RESERVED FOR REQUEST
            break;
        }
        default: {
            printf("REQ DONE GOOFED. Non-writtable address used.");
            break;
        }
    }
}