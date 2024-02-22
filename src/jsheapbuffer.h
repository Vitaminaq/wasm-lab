#ifndef JSHEAPBUFFER_H
#define JSHEAPBUFFER_H

#include <vector>

using BufferHandle = uint32_t;

class JSHeapBuffer {
    public:
        void read(uint8_t* pData, size_t size, size_t offset);
        void write(const uint8_t* pData, size_t size, size_t offset);
};
