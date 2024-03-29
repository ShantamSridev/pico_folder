    #include "encoder.h"

    // Definitions of external variables
    volatile int last_pos = 0;
    volatile double diff = 0;
    volatile int position = 0;
    volatile int rev_check = 0;
    volatile long oldT = 0;
    volatile int pulse = 0;

    void isr_pin_a() {
        bool stateB = gpio_get(ENCB); // Read the current state of pin B
        int i = 0;
        if(stateB>0) {
            i++; // Moving in one direction
        } else {
            i--; // Moving in the opposite direction
        }
        position = position - i;
        rev_check = rev_check - i;
    }

    void isr_pin_b() { //134.4 pulses per motor revolution and using 0.6666667:1 belt ratio
        //it comes to 224 pulses per rev of wheel

        //0.6222222222 degrees per pulse of wheel

        uint32_t int_status = save_and_disable_interrupts();

        long newT = time_us_32();
        if ((newT-oldT)>200000){
            diff = rev_check - last_pos;
            //printf("%d\n",rev_check);
            last_pos = rev_check;
            rev_check = 0;
            oldT = newT;
            pulse++;
        }
        restore_interrupts(int_status);
    }

    void gpio_callback(uint gpio, uint32_t events) {
        if (gpio == ENCA) {
            isr_pin_a();
        } else if (gpio == INDUCTIVE) {
            isr_pin_b();
        }
    }

    void init_encoder() {
        // Initialize GPIO pins for encoder A and B as inputs
        gpio_init(ENCA);
        gpio_set_dir(ENCA, GPIO_IN);
        gpio_pull_up(ENCA); // Optional: enable pull-up if necessary

        gpio_init(ENCB);
        gpio_set_dir(ENCB, GPIO_IN);
        gpio_pull_up(ENCB); // Optional: enable pull-up if necessary

        // Configure interrupt for pin A to trigger on rising edge
        gpio_set_irq_enabled_with_callback(ENCA, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);

        gpio_init(INDUCTIVE);
        gpio_set_dir(INDUCTIVE, GPIO_IN);
        gpio_pull_up(INDUCTIVE); // Optional: enable pull-up if necessary

        // // Configure interrupt for pin INDUCTIVE to trigger on rising edge
        gpio_set_irq_enabled_with_callback(INDUCTIVE, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    }
