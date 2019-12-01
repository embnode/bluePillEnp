#ifndef _STATIC_BUFFERS_H
#define _STATIC_BUFFERS_H

//Template for ring buffer. Need type and size
namespace staticBuffersTmpl
{
    template <class T, int SIZE>
    class RingBuff
    {
    
        T buff[SIZE];
        volatile uint32_t head;
        volatile uint32_t tail;
        uint32_t error;
    public:
        static const int ERROR_NO = 0;
        static const int ERROR_OVERFLOW = 1;
        RingBuff()
        {
            head = 0;
            tail = 0;
            error = ERROR_NO;
        }
        void put(T value) // Copy value in the head
        {
            buff[head] = value;
            head = (head + 1);
            if(head >= SIZE)
            {
                head = 0;
            }
            if(head == tail) // Error if buffer is full
            {
                error |= ERROR_OVERFLOW;
            }
        }
        T get(void)
        {
            return buff[tail];
        }
        void pop(void) // pop tail
        {
            if (head != tail)
            {
                tail = (tail + 1);
                if(tail >= SIZE)
                {
                    tail = 0;
                }
            }
        }
        int size(void) // get size of data in buffer
        {
            int ret;
            ret = head >= tail ? head - tail : SIZE - tail + head;
            return ret;
        }
        int getError(void)
        {
            return error;
        }
    };
}


#endif