template<typename T, unsigned int bufferSize>
class RingBuffer {
public:
    RingBuffer() : head(0), tail(0), full(false) {}

    bool push(const T &value) {
        if (full) {
            return false;
        }
        buffer[head] = value;
        head = (head + 1) % bufferSize;
        full = head == tail;
        return true;
    }

    bool pop(T &value) {
        if (isEmpty()) {
            return false;
        }
        value = buffer[tail];
        tail = (tail + 1) % bufferSize;
        full = false;
        return true;
    }

    bool isEmpty() const {
        return (!full && (head == tail));
    }

    bool isFull() const {
        return full;
    }

    void clear() {
        head = tail;
        full = false;
    }

    unsigned int size() const {
        if (full) {
            return bufferSize;
        }
        if (head >= tail) {
            return head - tail;
        }
        return bufferSize + head - tail;
    }

private:
    T buffer[bufferSize];
    unsigned int head, tail;
    bool full;
};