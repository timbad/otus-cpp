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

    my_allocator_t() = default;
    ~my_allocator_t() {
        if (buffer_) {
            std::free(buffer_);
        }
    }

    bool operator == (const my_allocator_t<T, N>&) { return false; }
    bool operator != (const my_allocator_t<T, N>&) { return true; }

    pointer allocate(size_t n) {
        if (n == 0) {
            return nullptr;
        }
        if (!buffer_) {
            capacity_ = N;
            auto old_buffer = buffer_;
            buffer_ = reinterpret_cast<T*>(std::malloc(capacity_ * sizeof(T)));
            if (!buffer_) {
                std::cerr << "my_allocator_t failed to allocate memory!\n";
                if (old_buffer) { std::free(old_buffer); }
                throw std::bad_alloc();
            }
        }
        if (size_ + n > capacity_) {
            capacity_ = 2 * N;
            auto old_buffer = buffer_;
            buffer_ = reinterpret_cast<T*>(std::realloc(buffer_, capacity_ * sizeof(T)));
            if (!buffer_) {
                std::cerr << "my_allocator_t failed to reallocate memory!\n";
                if (old_buffer) { std::free(old_buffer); }
                throw std::bad_alloc();
            }
        }
        pointer cur_ptr = &buffer_[size_];
        size_ += n;
        return cur_ptr;
    }

    void deallocate(pointer, size_t n) {
        size_ -= std::min(size_, n);
    }

    template<typename U, typename ...Args>
    void construct(U *ptr, Args &&...args) {
        new(ptr) U(std::forward<Args>(args)...);
    }

    void destroy(pointer ptr) {
        ptr->~T();
    }

private:
    T* buffer_{nullptr};
    size_t size_{0};
    size_t capacity_{0};
};
