#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <deque>

template <class A_Type> class RingBuffer
{
public:
    RingBuffer(int len)
    {
        this->dataque.resize(len, 0);
    }

    ~RingBuffer()
    {

    }

    A_Type insert(A_Type in)
    {
        A_Type out = this->dataque.pop_front();
        dataque.push_back(in);
        return out;
    }

    void resize(int len)
    {
        this->dataque.clear();
        this->dataque.resize(len, 0);
    }


    std::deque<A_Type> dataque;

private:
    int length;
};

#endif // RINGBUFFER_H
