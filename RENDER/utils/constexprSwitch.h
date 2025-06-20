#ifndef BLUEPRINT_CONSTEXPRSWITCH_H
#define BLUEPRINT_CONSTEXPRSWITCH_H

#include <iostream>
#include <type_traits>
#include <utility>
#include "../../Attribute.h"

template <auto Value>
struct ConstValue {
    static constexpr auto value = Value;
};

template <auto MatchValue, typename Func>
struct Case {
    static constexpr auto value = MatchValue;
    Func func;

    template <auto Input>
    ALWAYS_INLINE void try_run() const {
        if constexpr (Input == MatchValue) {
            func();
        }
    }
};

template <auto InputValue, typename... Cases>
struct ConstexprSwitch;

template <auto InputValue>
struct ConstexprSwitch<InputValue> {
    template <auto MatchValue, typename Func>
    ALWAYS_INLINE auto case_(Func func) const {
        return ConstexprSwitch<InputValue, Case<MatchValue, Func>>{ Case<MatchValue, Func>{func} };
    }

    template <typename Func>
    ALWAYS_INLINE void default_(Func func) const {
        func();
    }
};

template <auto InputValue, typename FirstCase, typename... Rest>
struct ConstexprSwitch<InputValue, FirstCase, Rest...> {
    std::tuple<FirstCase, Rest...> cases;

    template <auto MatchValue, typename Func>
    ALWAYS_INLINE auto case_(Func func) const {
        return ConstexprSwitch<InputValue, FirstCase, Rest..., Case<MatchValue, Func>>{ std::tuple_cat(cases, std::make_tuple(Case<MatchValue, Func>{func})) };
    }

    template <typename Func>
    ALWAYS_INLINE void default_(Func func) const {
        bool matched = false;
        std::apply([&](const auto&... cs) {
            ((cs.template try_run<InputValue>()), ...);
        }, cases);
        if constexpr (InputValue != InputValue) func();
    }
};

template <auto Value>
constexpr ALWAYS_INLINE auto constexpr_switch() {
    return ConstexprSwitch<Value>{};
}

#endif //BLUEPRINT_CONSTEXPRSWITCH_H
