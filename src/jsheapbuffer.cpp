#include "jsheapbuffer.h"
#include <emscripten.h>

void JSHeapBuffer::write(const uint8_t* pData, size_t size, size_t offset) const {
    if (!pData || !size) return;

    // js去HEAP8中取数据
    EM_ASM(
        { jsMemoryTable.memcpyToJS($0, $1, $2, $3); },
        m_handle,
        pData,
        size,
        offset
    );
    return;
}

void JSHeapBuffer::read(uint8_t* pData, size_t size, size_t offset) const {
    if (!pData || !size) return;

    // js把数据写入HEAP8中
    EM_ASM(
        { jsMemoryTable.memcpyFromJS($0, $1, $2, $3); },
        pData,
        m_handle,
        size,
        offset
    );
    return;
}
