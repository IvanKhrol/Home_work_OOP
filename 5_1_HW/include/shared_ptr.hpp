#ifndef __shared_ptr_hpp__
#define __shared_ptr_hpp__

#include <iostream>
#include <utility>

namespace custom_classes {

template <typename data_t>
struct shared_ptr final {
private:
    data_t* ptr_;
    size_t *ref_counter_;
public:
    shared_ptr(data_t *ptr = nullptr) :
        ptr_(ptr) {
            if (ptr == nullptr) return;
            try { ref_counter_ = new size_t {1}; }
            catch (...) { delete ptr; throw; }
        }
    //=======================================================================
    shared_ptr(const shared_ptr &other) :
        ptr_(other.ptr_),
        ref_counter_(other.ref_counter_) { ++(*ref_counter_); }
    // move constructor is equal to constructor:const T&
    //=======================================================================
    shared_ptr &operator= (const shared_ptr& other) noexcept{
        ~shared_ptr();
        ptr_ = other.ptr_;
        ref_counter_ = other.ref_counter_;
        ++(*ref_counter_);
        return *this;
    }
    // move assign is equal to operator=:const T&
    //=======================================================================
    ~shared_ptr() {
        if (--(*ref_counter_) == 0) {
            delete ref_counter_;
            delete ptr_;
        }
    }
    //=======================================================================
    data_t &operator*() const noexcept { return *ptr_;}
    data_t *operator->() const noexcept { return ptr_; }
    size_t use_count() const noexcept { return *ref_counter_; }
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <typename data_t>
struct shared_ptr<data_t *> final {
private:
    data_t *ptr_;
    size_t *ref_counter_;
public:
    shared_ptr(data_t *ptr = nullptr) :
        ptr_(ptr) {
            if (ptr == nullptr) return;
            try { ref_counter_ = new size_t {1}; }
            catch (...) { delete [] ptr; throw; }
        }
    //=======================================================================
    shared_ptr(const shared_ptr &other) :
        ptr_(other.ptr_),
        ref_counter_(other.ref_counter_) { ++(*ref_counter_); }
    // move constructor is equal to constructor:const T&
    //=======================================================================
    shared_ptr &operator= (const shared_ptr& other) {
        ~shared_ptr();
        ptr_ = other.ptr_;
        ref_counter_ = other.ref_counter_;
        ++(*ref_counter_);
        return *this;
    }
    // move assign is equal to operator=:const T&
    //=======================================================================
    ~shared_ptr() {
        if (--(*ref_counter_) == 0) {
            delete ref_counter_;
            delete [] ptr_;
        }
    }
    //=======================================================================
    data_t &operator*() { return *ptr_;}
    data_t *operator->() { return ptr_; }
    data_t &operator[](const size_t offset) { return *(ptr_ + offset); }
    size_t use_count() const noexcept { return *ref_counter_; }
};

}
#endif