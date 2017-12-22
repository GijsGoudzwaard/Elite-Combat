#include <stdint.h>
#include "../headers/support/Queue.hpp"


Queue::Queue()
{
arr[3];
index = 0;
qSize = 0; 
}

void Queue::addToQueue(uint8_t index, uint8_t status)
{
    this->arr[index] = status; 
    qSize =+ 1;
}

uint8_t Queue::takeFromQueue()
{
    uint8_t outQueue;
    outQueue = this->arr[0];

    for (uint8_t i = 0; i<qSize;i++){
        this->arr[i] = this->arr[i+1];
    }
    qSize =- 1;
    return outQueue;
}

uint8_t Queue::queueSize()
{
    return qSize;
}