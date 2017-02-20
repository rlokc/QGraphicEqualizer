#include "ringbuffer.h"

template <class A_Type> RingBuffer<A_Type>::~RingBuffer()
{

}

template <class A_Type> RingBuffer<A_Type>::RingBuffer(int len)
{
    this->dataque.resize(len, 0);
}

template <class A_Type> void RingBuffer<A_Type>::resize(int len)
{
    this->dataque.resize(len, 0);
}

template <class A_Type> A_Type RingBuffer<A_Type>::insert(A_Type in)
{
    A_Type out = this->dataque.pop_front();
    dataque.push_back(in);
    return out;
}


