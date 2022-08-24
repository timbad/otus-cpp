#pragma once

#include <memory>
#include <array>


template<typename T, size_t N>
class my_allocator_t
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    template<typename U>
    struct rebind {
        using other = my_allocator_t<U, N>;
    };

    bool operator == (const my_allocator_t<T, N>&) { return false; }
    bool operator != (const my_allocator_t<T, N>&) { return true; }

    pointer allocate(size_t n) {
        if (n == 0) {
            return nullptr;
        }
        if (offset_ + n > N) {
            throw std::bad_alloc();
        }
        pointer cur_ptr = &buffer_[offset_];
        offset_ += n;
        return cur_ptr;
    }

    void deallocate(pointer, size_t n) {
        offset_ -= std::min(offset_, n);
    }

    template<typename U, typename ...Args>
    void construct(U *ptr, Args &&...args) {
        new(ptr) U(std::forward<Args>(args)...);
    }

    void destroy(pointer ptr) {
        ptr->~T();
    }

private:
    std::array<T, N> buffer_;
    size_t offset_{0};
};
