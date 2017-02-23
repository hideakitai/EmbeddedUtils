#pragma once
#define DEFAULT_MAX_SIZE    128

template<typename T>
class RingQueue
{
public:
    RingQueue(unsigned int size = DEFAULT_MAX_SIZE)
    : size_(size)
    {
        head_ = tail_ = 0;
        queue_ = new T[size_];
    };
    ~RingQueue()  { delete[] queue_; };

    inline int  size()  { return  (tail_ - head_); };
    inline bool empty() { return !(tail_ - head_); };
    inline void clear() { head_ = 0; tail_ = 0; };
    inline void pop()   { head_++; };
    inline void push(T data)
    {
        if (size() >= size_) return;
        queue_[(tail_++) % size_] = data;
        if      (size() >= size_) head_++;
        else if (size() <  0)     clear();
    };

    inline T& front()
    {
        return *(empty() ? NULL : queue_ + head_ % size_);
    };

    inline T& back()
    {
        return *(empty() ? NULL : queue_ + (tail_ - 1) % size_);
    }

    inline T& operator[] (int index)
    {
        return *(empty() ? NULL : queue_ + head_ % size_ + index);
    }

private:

    volatile unsigned int head_;
    volatile unsigned int tail_;
    const unsigned int size_;
    T* queue_;

};
