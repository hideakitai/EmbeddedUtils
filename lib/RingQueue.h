#pragma once

#include <cstddef>
#include <exception>

template<typename T, typename size_type = int>
class RingQueue
{
public:
    struct Exception : public std::exception {
        Exception() {}
        virtual const char *what() const noexcept {
            return "RingQueue is Empty";
        }
    };

    RingQueue(size_type size = DEFAULT_MAX_SIZE)
    : size_(size)
    {
        head_ = tail_ = 0;
        queue_ = new T[size_];
    };
    ~RingQueue()  { delete[] queue_; };

    inline size_type size() const { return (tail_ - head_); };
    inline bool empty() const { return tail_ == head_; };
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

    volatile size_type head_;
    volatile size_type tail_;
    const    size_type size_;
    T* queue_;

    static constexpr size_type DEFAULT_MAX_SIZE = 128;
};
