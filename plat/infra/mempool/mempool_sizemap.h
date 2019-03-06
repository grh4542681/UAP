#ifndef __MEMPOOL_SIZEMAP_H__
#define __MEMPOOL_SIZEMAP_H__

#include <sys/types.h>


namespace mempool {

/**
* @brief - Small obejct size map.
*/
class MemPoolSizeMap {
private:
    /**
    * @brief - Small object size map element.
    */
    struct MemPoolSizeClass {
        size_t mem_size_;      ///< The memory size corresponding to this object.
        size_t page_size_;     ///< How many pages of memory does an object need.
        size_t num_to_move_;   ///< How many times each application or recycling.
    };
public:
    static const size_t g_size_class_split_size = 1024; ///< if size little than 1024, it will aligned with 8 byte. Otherwise aligned with 128.
    static const size_t g_mem_alignment = 8;   ///< Memory alignment default size.(8B)
    static const size_t g_max_small_object_size = (256 * 1024);  ///< Largest small object defalue size.(256KB)
    static const size_t g_class_array_size = ((g_max_small_object_size + 127 + (120 << 7)) >> 7) + 1;   ///< Size of size class array.

    MemPoolSizeMap();
    ~MemPoolSizeMap();


private:
    struct MemPoolSizeClass size_class_array_[g_class_array_size];  ///< Size class array.

    size_t SmallSizeClass(size_t s) {
        return (static_cast<uint32_t>(s) + 7) >> 3;
    }
    size_t LargeSizeClass(size_t s) {
        return (static_cast<uint32_t>(s) + 127 + (120 << 7)) >> 7;
    }
};

} //namespace end


#endif
