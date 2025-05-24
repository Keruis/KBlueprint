module;
#include <type_traits>
#include <algorithm>

export module ContainerDetail;

namespace detail {
    // 默认构造（适用于非平凡类型）
    export template <typename Iterator, typename ValueType>
    void defaultConstruct(Iterator first, Iterator last) noexcept(
    std::is_nothrow_default_constructible_v<ValueType>) {
        using T = std::remove_reference_t<decltype(*first)>;
        if constexpr (!std::is_trivially_default_constructible_v<T>) {
            for (; first != last; ++first)
                new (&*first) T();
        }
    }

    // 填充构造（适用于非平凡类型）
    export template <typename Iterator, typename ValueType, typename U>
    void fillConstruct(Iterator first, Iterator last, const U& value) noexcept(
    std::is_nothrow_copy_constructible_v<ValueType>) {
        using T = std::remove_reference_t<decltype(*first)>;
        if constexpr (std::is_trivially_copy_constructible_v<T>) {
            std::fill(first, last, static_cast<T>(value));
        } else {
            for (; first != last; ++first)
                new (&*first) T(value);
        }
    }

    // 拷贝构造（适用于非平凡类型）
    export template <typename IteratorDest, typename IteratorSrc>
    void copyConstruct(IteratorDest destFirst, IteratorDest destLast, IteratorSrc srcFirst) noexcept(
    std::is_nothrow_copy_constructible_v<std::iter_value_t<IteratorDest>>) {
        using T = std::iter_value_t<IteratorDest>;
        if constexpr (std::is_trivially_copy_constructible_v<T>) {
            std::copy(srcFirst, srcFirst + (destLast - destFirst), destFirst);
        } else {
            for (; destFirst != destLast; ++destFirst, ++srcFirst)
                new (&*destFirst) T(*srcFirst);
        }
    }

    // 移动构造（适用于非平凡类型）
    export template <typename IteratorDest, typename IteratorSrc>
    void moveConstruct(IteratorDest destFirst, IteratorDest destLast, IteratorSrc srcFirst) noexcept(
    std::is_nothrow_move_constructible_v<std::iter_value_t<IteratorDest>>) {
        using T = std::iter_value_t<IteratorDest>;
        if constexpr (std::is_trivially_move_constructible_v<T>) {
            std::move(srcFirst, srcFirst + (destLast - destFirst), destFirst);
        } else {
            for (; destFirst != destLast; ++destFirst, ++srcFirst)
                new (&*destFirst) T(std::move(*srcFirst));
        }
    }

    // 析构（适用于非平凡类型）
    export template <typename Iterator>
    void destroy(Iterator first, Iterator last) noexcept {
        using T = std::remove_reference_t<decltype(*first)>;
        if constexpr (!std::is_trivially_destructible_v<T>) {
            for (; first != last; ++first)
                first->~T();
        }
    }
}