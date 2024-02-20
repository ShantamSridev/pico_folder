#include <iostream>
#include <vector>

template<typename T, size_t Size>
class RingBuffer {
public:
    RingBuffer() : head(0), tail(0), full(false) {}

    bool push(const T& item) {
        if(full) {
            return false; // Buffer is full, cannot push
        }

        buffer[tail] = item;
        tail = (tail + 1) % Size;

        full = tail == head; // If tail catches up to head, buffer is full

        return true;
    }

    bool pop(T& item) {
        if(isEmpty()) {
            return false; // Buffer is empty, cannot pop
        }

        item = buffer[head];
        head = (head + 1) % Size;
        full = false; // Popping an item always makes the buffer not full

        return true;
    }

    bool isFull() const {
        return full;
    }

    bool isEmpty() const {
        return (!full && (head == tail));
    }

    void clear() {
        head = tail;
        full = false;
    }

    size_t size() const {
        if(full) {
            return Size;
        }

        if(tail >= head) {
            return tail - head;
        }

        return Size + tail - head;
    }

private:
    std::vector<T> buffer{Size};
    size_t head, tail;
    bool full;
};