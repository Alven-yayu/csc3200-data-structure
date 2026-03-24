
#ifndef STUDENT_VECTOR_H
#define STUDENT_VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <iterator>

namespace student_std {

template<typename T>
class vector {
public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    class iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;

        // 默认构造
        iterator() : ptr_(nullptr) {}
        // 构造函数：接受 T* 指针
        explicit iterator(pointer ptr) : ptr_(ptr) {}
        // 拷贝构造
        iterator(const iterator& other) : ptr_(other.ptr_) {}

        // 赋值操作
        iterator& operator=(const iterator& other) {
            if (this != &other) ptr_ = other.ptr_;
            return *this;
        }

        // 解引用
        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        // 前缀自增
        iterator& operator++() { ++ptr_; return *this; }
        // 前缀自减
        iterator& operator--() { --ptr_; return *this; }
        // 后缀自增
        iterator operator++(int) { iterator tmp(*this); ++ptr_; return tmp; }
        // 后缀自减
        iterator operator--(int) { iterator tmp(*this); --ptr_; return tmp; }

        // 比较运算
        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
        bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
        bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

        // 算术运算
        iterator operator+(difference_type n) const { return iterator(ptr_ + n); }
        iterator operator-(difference_type n) const { return iterator(ptr_ - n); }
        difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }

        // 复合赋值
        iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }

        // 随机访问
        reference operator[](difference_type n) const { return ptr_[n]; }

    private:
        pointer ptr_;
        friend class vector<T>;
    };

private:
    T* data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;

    void grow() {
        size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        T* new_data = new T[new_capacity];
        for (size_type i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    vector() = default;

    vector(const vector& other) : data_(nullptr), size_(0), capacity_(0) {
        if (other.size_ > 0) {
            data_ = new T[other.capacity_];
            for (size_type i = 0; i < other.size_; ++i) {
                data_[i] = other.data_[i];
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
    }

    vector& operator=(const vector& other) {
        if (this == &other) return *this;
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        if (other.size_ > 0) {
            data_ = new T[other.capacity_];
            for (size_type i = 0; i < other.size_; ++i) {
                data_[i] = other.data_[i];
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    ~vector() { delete[] data_; }

    size_type size() const { return size_; }
    size_type capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    T* data() { return data_; }
    const T* data() const { return data_; }

    T& at(size_type pos) {
        if (pos >= size_) throw std::out_of_range("out of range");
        return data_[pos];
    }
    const T& at(size_type pos) const {
        if (pos >= size_) throw std::out_of_range("out of range");
        return data_[pos];
    }

    T& operator[](size_type pos) { return data_[pos]; }
    const T& operator[](size_type pos) const { return data_[pos]; }

    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }
    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    void push_back(const T& value) {
        if (size_ >= capacity_) grow();
        data_[size_++] = value;
    }

    void pop_back() { if (size_ > 0) --size_; }

    void resize(size_type count, const T& value = T()) {
        if (count > capacity_) reserve(count);
        for (size_type i = size_; i < count; ++i) {
            data_[i] = value;
        }
        size_ = count;
    }

    void reserve(size_type new_capacity) {
        if (new_capacity <= capacity_) return;
        T* new_data = new T[new_capacity];
        for (size_type i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void clear() { size_ = 0; }

    void swap(vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // 返回指向第一个元素的迭代器
    iterator begin() { return iterator(data_); }

    // 返回指向最后一个元素之后位置的迭代器
    iterator end() { return iterator(data_ + size_); }

iterator erase(iterator pos) {
    // 将 [pos+1, end) 的元素向前移动一位
    for (auto it = pos; it != end() - 1; ++it) {
        *it = *(it + 1);
    }
    --size_; 
    return pos; 
}

// 删除范围 [first, last)
iterator erase(iterator first, iterator last) {
    if (first == last) return first;
    
    // 将 [last, end) 的元素移动到 [first, ...)
    iterator result = first;
    for (iterator src = last; src != end(); ++src, ++result) {
        *result = *src;
    }
    
    size_ -= (last - first); // 更新大小
    return first; // 返回原起始位置
}

// 在 pos 前插入元素
iterator insert(iterator pos, const T& value) {
    if (size_ == capacity_) {
        size_type offset = pos - begin();
        grow();
        pos = begin() + offset; 
    }
    
    // 将 [pos, end) 的元素向后移动一位
    for (auto it = end(); it != pos; --it) {
        *it = *(it - 1);
    }
    
    *pos = value; 
    ++size_; 
    return pos; // 返回新元素的迭代器
}
};

} 
#endif 