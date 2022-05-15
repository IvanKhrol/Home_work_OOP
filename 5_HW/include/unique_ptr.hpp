#ifndef __UNIQUE_PTR_HH__
#define __UNIQUE_PTR_HH__
#include <iostream>

namespace custom_classes {

// deletor functor for pointers on elements
template <typename data_t>
struct default_delete final {
    void operator()(data_t *ptr) noexcept { delete ptr; }
};

// deletor functor for pointers on arrays
template <typename data_t>
struct default_delete<data_t[]> final {
    void operator()(data_t *ptr) noexcept { delete [] ptr; }
};

// unique_ptr class for none arrays spec
template <typename data_t, typename Deleter = default_delete<data_t>>
struct unique_ptr final {
private:
    data_t  *ptr_;
    Deleter del_;
public:
    unique_ptr(data_t *ptr = nullptr) noexcept :
        ptr_(ptr) {}
    unique_ptr(const unique_ptr &other) = delete;

    unique_ptr &operator=(const unique_ptr &other) = delete;
    unique_ptr(unique_ptr &&other) noexcept :
        ptr_(other.ptr_) {
            other.ptr_ = nullptr;
        }
    unique_ptr &operator=(unique_ptr &&other) noexcept {
        del_(ptr_);
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }
    
    ~unique_ptr() { del_(ptr_); }
//==============================================================================
    data_t *operator->() { return ptr_; }
    data_t &operator*() { return *(ptr_); }
};

// unique_ptr class for arrays spec
template <typename data_t, typename Deleter>
struct unique_ptr<data_t[], Deleter> {
private:
    data_t  *ptr_;
    Deleter del_;
public:
    unique_ptr(data_t *ptr = nullptr) noexcept :
        ptr_(ptr) {}
    unique_ptr(const unique_ptr &other) = delete;
    unique_ptr &operator=(const unique_ptr &other) = delete;
    unique_ptr(unique_ptr &&other) noexcept :
        ptr_(other.ptr_) {
            other.ptr_ = nullptr;
        }
    unique_ptr &operator=(unique_ptr &&other) noexcept {
        del_(ptr_);
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }
    ~unique_ptr() { del_(ptr_); }
//==============================================================================
    data_t *operator->() { return ptr_; }
    data_t &operator*() { return *(ptr_); }
    data_t &operator[](const size_t num) { return *(ptr_ + num); }
};

}

#endif
