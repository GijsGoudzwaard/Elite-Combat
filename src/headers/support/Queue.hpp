#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
    public:
    Queue();

    void addToQueue(uint8_t index, uint8_t status);

    uint8_t takeFromQueue();

    uint8_t queueSize();
    
    uint8_t arr[];

    uint8_t index;

    uint8_t qSize;
};

#endif
