#pragma once


template<typename T, typename Allocator = std::allocator<T> >
class my_list_t {
public:
    struct node_t {
        explicit node_t(const T& value): value_(value), next_(nullptr) {}
        explicit node_t(T&& value): value_(std::move(value)), next_(nullptr) {}

        T value_;
        node_t* next_;
    };

    using allocator_t = typename Allocator::template rebind<node_t>::other;

    class iterator_t {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit iterator_t(node_t* ptr): ptr_(ptr) {}

        reference operator*() const {
            return ptr_->value_;
        }
        pointer operator->() {
            return &ptr_->value_;
        }
        iterator_t& operator++() {
            ptr_ = ptr_->next_;
            return *this;
        }
        iterator_t operator++(int) {
            iterator_t tmp = *this;
            ptr_ = ptr_->next_;
            return tmp;
        }
        friend bool operator!=(const iterator_t& lhs, const iterator_t& rhs) { return lhs.ptr_ != rhs.ptr_; }
        friend bool operator==(const iterator_t& lhs, const iterator_t& rhs) { return lhs.ptr_ == rhs.ptr_; }
    private:
        node_t* ptr_;
    };

    my_list_t() = default;
    ~my_list_t() {
        clear();
    }
    explicit my_list_t(const my_list_t<T, allocator_t>& rhs) {
        *this = rhs;
    }
    my_list_t& operator=(const my_list_t<T, allocator_t>& rhs) {
        for (auto it = rhs.begin(); it != rhs.end(); ++it) {
            push_back(*it);
        }
    }
    explicit my_list_t(my_list_t<T, allocator_t>&& rhs) = delete;
    my_list_t& operator=(my_list_t<T, allocator_t>&& rhs) = delete;

    iterator_t begin() const { return iterator_t(head_); }
    iterator_t end() const { return iterator_t(nullptr); }

    T& front() const { return *head_->value_; }
    T& back() const { return *tail_->value_; }

    bool empty() const {
        return !head_;
    }

    size_t size() const {
        return head_ ? static_cast<size_t>(tail_ - head_) : 0;
    }

    void push_back(const T& value) {
        auto node = allocator_.allocate(1);
        if (!node) {
            throw std::runtime_error("Failed to allocate memory in my_list_t::push_back");
        }
        allocator_.construct(node, value);
        if (head_) {
            tail_->next_ = node;
        } else {
            head_ = node;
        }
        tail_ = node;
    }

    void pop_back() {
        auto del_node = tail_;
        auto it = begin();
        for (; it->next_ != tail_; ++it) {}
        tail_ = *it;
        allocator_.destroy(del_node);
        allocator_.deallocate(del_node, 1);
    }

    void clear() {
        auto cur = head_;
        while (cur != nullptr) {
            auto next = cur->next_;
            allocator_.destroy(cur);
            allocator_.deallocate(cur, 1);
            cur = next;
        }
    }

private:
    node_t* head_{nullptr};
    node_t* tail_{nullptr};
    allocator_t allocator_;
};
