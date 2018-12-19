#pragma once

#ifndef RINGQUEUE_H
#define RINGQUEUE_H

#include <cstddef>
#include <exception>
#include <type_traits>

template<typename T, size_t QUEUE_SIZE, typename size_type = uint32_t>
class RingQueue
{
public:
    struct Exception : public std::exception {
        Exception() {}
        virtual const char *what() const noexcept {
            return "RingQueue is Empty";
        }
    };

    inline size_type capacity() const { return size_; };
    inline size_type size() const { return (tail_ - head_); };
    inline bool empty() const { return tail_ == head_; };
    inline void clear() { head_ = 0; tail_ = 0; };
    inline void pop()
    {
        if (size() == 0) return;
        if (size() == 1) clear();
        else head_++;
    };
    inline void push(const T& data)
    {
        queue_[(tail_++) % QUEUE_SIZE] = data;
        if      (size() > QUEUE_SIZE) head_++;
    };

    inline const T& front() const throw(Exception)
    {
        if(empty()) throw Exception();
        return *(queue_ + head_ % QUEUE_SIZE);
    };
    inline T front() throw(Exception)
    {
        if(empty()) throw Exception();
        return *(queue_ + head_ % QUEUE_SIZE);
    };

    inline const T& back() const throw(Exception)
    {
        if(empty()) throw Exception();
        return *(queue_ + (QUEUE_SIZE + tail_ - 1) % QUEUE_SIZE);
    }
    inline T back() throw(Exception)
    {
        if(empty()) throw Exception();
        return *(queue_ + (QUEUE_SIZE + tail_ - 1) % QUEUE_SIZE);
    }

    inline const T& operator[] (const size_type index) const
    {
        return *(queue_ + (head_ + index) % QUEUE_SIZE);
    }
    inline T operator[] (const size_type index)
    {
        return *(queue_ + (head_ + index) % QUEUE_SIZE);
    }

private:

    volatile size_type head_ {0};
    volatile size_type tail_ {0};
    T queue_[QUEUE_SIZE];
};

#endif
