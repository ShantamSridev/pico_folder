#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>
#include <cstddef> // for size_t

template<typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity)
        : buffer(capacity), head(0), tail(0), full(false) {}

    void push(T item) {
        buffer[tail] = item;
        tail = (tail + 1) % buffer.size();
        full = tail == head;
        if (full) {
            head = (head + 1) % buffer.size(); // Overwrite oldest data
        }
    }

    T pop() {
        if (isEmpty()) {
            printf("Attempt to pop from empty buffer");
            return 0;
        }
        auto val = buffer[head];
        head = (head + 1) % buffer.size();
        full = false;
        return val;
    }

    bool isEmpty() const {
        return (!full && (head == tail));
    }

    void resize(size_t new_size) {
        std::vector<T> new_buffer(new_size);
        size_t currentSize = size();
        for (size_t i = 0; i < currentSize; i++) {
            new_buffer[i] = pop(); // This also moves head
        }
        buffer.swap(new_buffer);
        head = 0;
        tail = currentSize % new_size;
        full = tail == 0 && new_size <= currentSize;
    }

    size_t size() const {
        if (full) {
            return buffer.size();
        }
        if (tail >= head) {
            return tail - head;
        }
        return buffer.size() + tail - head;
    }

private:
    std::vector<T> buffer;
    size_t head, tail;
    bool full;
};

#endif