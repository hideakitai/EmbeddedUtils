#pragma once

#include <cstddef>
#include <exception>

template<typename T, typename size_type = int>
class RingQueue
{
public:
    RingQueue(size_type size = DEFAULT_MAX_SIZE)
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

    static constexpr size_type DEFAULT_MAX_SIZE = 128;
};
