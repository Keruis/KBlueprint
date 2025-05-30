#include <iostream>
#include <cstring>

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Iterator Vector<Ty, Align>::AllocateAligned(std::size_t n) noexcept {
    void* ptr = nullptr;
#if defined(_WIN32)
    ptr = _aligned_malloc(n * sizeof(ValueType), Align);
#elif defined(__linux__)
    posix_memalign(&ptr, Align, n * sizeof(ValueType));
#else
    static_assert(false, "Vector");
#endif
    return reinterpret_cast<Iterator>(ptr);
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::DeallocateAligned() noexcept {
    if (m_data) {
#if defined(_WIN32)
        _aligned_free(m_data);
#elif defined(__linux__)
        free(m_data);
#else
            static_assert(false, "Vector");
#endif
        m_data = nullptr;
    }
}

#include "../Module/Detail.h"

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::defaultInitialize(Vector::Iterator data, std::size_t count) noexcept {
    if constexpr (!std::is_trivially_default_constructible_v<ValueType>) {
        for (std::size_t i = 0; i < count; i++)
            new (data + i) ValueType();
    }
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::fillInitialize(Vector::Iterator data, std::size_t count,
                                       const Vector::ValueType &val) noexcept {
    if constexpr (std::is_trivially_copy_constructible_v<ValueType>) {
        std::fill(data, data + count, val);
    } else {
        for (std::size_t i = 0; i < count; i++)
            new (data + i) ValueType(val);
    }
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::copyInitialize(Vector::Iterator dest, Vector::Const_Iterator src,
                                       std::size_t count) noexcept {
    if constexpr (std::is_trivially_copy_constructible_v<ValueType>) {
        std::copy(src, src + count, dest);
    } else {
        for (std::size_t i = 0; i < count; i++)
            new (dest + i) ValueType(src[i]);
    }
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::moveInitialize(Vector::Iterator dest, Vector::Iterator src,
                                       std::size_t count) noexcept {
    if constexpr (std::is_trivially_move_constructible_v<ValueType>) {
        std::move(src, src + count, dest);
    } else {
        for (std::size_t i = 0; i < count; i++)
            new (dest + i) ValueType(std::move(src[i]));
    }
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::destroyElements(Vector::Iterator data, std::size_t count) noexcept {
    if constexpr (std::is_trivially_destructible_v<ValueType>) {
        for (std::size_t i = 0; i < count; i++)
            data[i].~ValueType();
    }
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Vector()
    : m_data(nullptr),
      m_size(0),
      m_capacity(0)
{

}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Vector(std::size_t n)
    : m_size(n),
      m_capacity(n)
{
    m_data = AllocateAligned(n);
    defaultInitialize(m_data, n);
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Vector(std::size_t n, const Vector::ValueType &val)
    : m_size(n),
      m_capacity(n)
{
    m_data = AllocateAligned(n);
    fillInitialize(m_data, n, val);
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Vector(std::initializer_list<ValueType> init)
    : m_size(init.size()),
      m_capacity(init.size())
{
    m_data = AllocateAligned(m_capacity);
    moveInitialize(m_data, const_cast<Iterator>(init.begin(), m_size));
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Vector(const Vector<Ty, Align> &other)
    : m_data(nullptr),
      m_size(other.m_size),
      m_capacity(other.m_capacity)
{
    if (m_capacity > 0) {
        m_data = AllocateAligned(m_capacity);
        copyInitialize(m_data, other.m_data, m_size);
    }
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::~Vector() {
    //destroyElements(m_data, m_size);
    DeallocateAligned();
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align> &Vector<Ty, Align>::operator=(Vector<Ty, Align> &&other) noexcept {
    if (this != &other) {
        destroyElements(m_data, m_size);
        DeallocateAligned();

        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::ValueType &Vector<Ty, Align>::operator[](std::size_t i) noexcept {
    return m_data[i];
}

template <typename Ty, std::size_t Align>
const Vector<Ty, Align>::ValueType &Vector<Ty, Align>::operator[](std::size_t i) const noexcept {
    return m_data[i];
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Iterator Vector<Ty, Align>::data() noexcept {
    return m_data;
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Const_Iterator Vector<Ty, Align>::data() const noexcept {
    return m_data;
}

template <typename Ty, std::size_t Align>
std::size_t Vector<Ty, Align>::size() const noexcept {
    return m_size;
}

template <typename Ty, std::size_t Align>
std::size_t Vector<Ty, Align>::capacity() const noexcept {
    return m_capacity;
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::clear() noexcept {
    destroyElements(m_data, m_size);
    m_size = 0;
}

template <typename Ty, std::size_t Align>
bool Vector<Ty, Align>::empty() const noexcept {
    return m_size == 0;
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Iterator Vector<Ty, Align>::begin() noexcept {
    return m_data;
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Const_Iterator Vector<Ty, Align>::begin() const noexcept {
    return m_data;
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Iterator Vector<Ty, Align>::end() noexcept {
    return m_data + m_size;
}

template <typename Ty, std::size_t Align>
Vector<Ty, Align>::Const_Iterator Vector<Ty, Align>::end() const noexcept {
    return m_data + m_size;
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::resize(std::size_t new_size) noexcept {
    if (new_size > m_size) {
        reserve(new_size);
        defaultInitialize(m_data + m_size, new_size - m_size);
    } else if (new_size < m_size) {
        destroyElements(m_data + new_size, m_size - new_size);
    }
    m_size = new_size;
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::resize(std::size_t new_size, Vector::ValueType val) noexcept {
    if (new_size > m_size) {
        reserve(new_size);
        defaultInitialize(m_data + m_size, new_size - m_size);
        fillInitialize(m_data + m_size, new_size - m_size, val);
    } else if (new_size < m_size) {
        destroyElements(m_data + new_size, m_size - new_size);
        fillInitialize(m_data + m_size, new_size - m_size, val);
    }
    m_size = new_size;
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::reserve(std::size_t new_capacity) noexcept {
    if (new_capacity <= m_capacity) return;

    std::cerr << "Reserving from " << m_capacity << " to " << new_capacity << "\n";

    Iterator new_data = AllocateAligned(new_capacity);
    if (!new_data) {
        std::cerr << "Allocation failed!\n";
        std::terminate(); // 或抛出异常（但违反 noexcept）
    }

    moveInitialize(new_data, m_data, m_size);
    destroyElements(m_data, m_size);
    DeallocateAligned();

    m_data = new_data;
    m_capacity = new_capacity;
}

template<typename Ty, std::size_t Align>
Vector<Ty, Align>::Iterator Vector<Ty, Align>::erase(Vector::Const_Iterator pos) noexcept {
    Iterator non_const_pos = const_cast<Iterator>(pos);
    Iterator next = non_const_pos + 1;

    if (next != end()) {
        Container::detail::moveAssign(non_const_pos, next, end());
    }

    destroyElements(end() - 1, 1);
    --m_size;
    return non_const_pos;
}

template<typename Ty, std::size_t Align>
Vector<Ty, Align>::Iterator Vector<Ty, Align>::erase(Vector::Const_Iterator first,
                                                     Vector::Const_Iterator last) noexcept {
    auto non_const_first = const_cast<Iterator>(first);
    auto non_const_last = const_cast<Iterator>(last);
    std::size_t count = non_const_last - non_const_first;

    if (non_const_last != end()) {
        Container::detail::moveAssign(non_const_first, non_const_last, end());
    }

    destroyElements(end() - count, count);
    m_size -= count;
    return non_const_first;
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::swap(Vector<Ty, Align> &other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::push_back(const Vector::ValueType &val) noexcept {
    // 检查容量
    if (m_size >= m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }

    if constexpr (std::is_trivially_copy_constructible_v<ValueType>) {
        // 平凡类型直接拷贝
        std::memcpy(&m_data[m_size], &val, sizeof(ValueType));
        ++m_size;
    } else {
        // 非平凡类型构造
        new (&m_data[m_size]) ValueType(val);
        ++m_size;
    }
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::push_back(Vector::ValueType &&val) noexcept {
    if (m_size >= m_capacity) reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    if constexpr (std::is_trivially_move_constructible_v<ValueType>) {
        m_data[m_size++] = std::move(val);
    } else {
        new (m_data + m_size++) ValueType (std::move(val));
    }
}

template <typename Ty, std::size_t Align>
void Vector<Ty, Align>::pop_back() noexcept {
    if (m_size > 0) {
        if constexpr (!std::is_trivially_destructible_v<ValueType>) {
            m_data[m_size-1].~ValueType();
        }
        m_size--;
    }
}