#ifndef BLUEPRINT_VECTOR_H
#define BLUEPRINT_VECTOR_H

#include <cstdio>
#include <initializer_list>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <cstdlib>
#else
    static_assert(false, "Vector");
#endif

#include <type_traits>
#include <algorithm>

template <typename Ty, std::size_t Align = 32>
class Vector {
public:
    using ValueType = Ty;
    using Iterator = ValueType*;
    using Const_Iterator = const Iterator;

    Vector();
    explicit Vector(std::size_t n);
    explicit Vector(std::size_t n, const ValueType& val);
    Vector(std::initializer_list<ValueType> init);
    Vector(const Vector& other);
    ~Vector();

public:
    Vector& operator=(Vector&& other) noexcept ;
    ValueType& operator[](std::size_t i) noexcept ;
    const ValueType& operator[](std::size_t i) const noexcept ;

    Iterator data() noexcept ;
    Const_Iterator data() const noexcept ;

    std::size_t size() const noexcept ;
    std::size_t capacity() const noexcept ;

    void clear() noexcept ;
    bool empty() const noexcept ;

    Iterator begin() noexcept ;
    Const_Iterator begin() const noexcept ;

    Iterator end() noexcept ;
    Const_Iterator end() const noexcept ;

    void resize(std::size_t new_size) noexcept ;
    void resize(std::size_t new_size, ValueType val) noexcept ;
    void reserve(std::size_t new_capacity) noexcept ;

    Iterator erase(Const_Iterator pos) noexcept;
    Iterator erase(Const_Iterator first, Const_Iterator last) noexcept;

    void swap(Vector& other) noexcept ;

    void push_back(const ValueType& val) noexcept ;
    void push_back(ValueType&& val) noexcept ;
    void pop_back() noexcept ;

private:
    Iterator AllocateAligned(std::size_t n) noexcept ;
    void DeallocateAligned() noexcept ;

    void defaultInitialize(Iterator data, std::size_t count) noexcept ;
    void fillInitialize(Iterator data, std::size_t count, const ValueType& val) noexcept ;
    void copyInitialize(Iterator dest, Const_Iterator src, std::size_t count) noexcept ;
    void moveInitialize(Iterator dest, Iterator src, std::size_t count) noexcept ;
    void destroyElements(Iterator data, std::size_t count) noexcept ;

private:
    Iterator m_data;
    std::size_t m_size;
    std::size_t m_capacity;
};

#include "Vector.tpp"

#endif //BLUEPRINT_VECTOR_H
