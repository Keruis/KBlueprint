#ifndef BLUEPRINT_VARTYPE_H
#define BLUEPRINT_VARTYPE_H

#include <variant>
#include <string>
#include <iostream>

class VariantData {
    using Variant = std::variant<int, float, double, bool>;

private:
    Variant m_data;

public:
    // 设置数据，自动根据类型推导
    template <typename T>
    void setData(const T& data) {
        m_data = data;
    }

    // 获取数据，返回指定类型的数据
    template <typename T>
    T getData() const {
        return std::get<T>(m_data);  // 抛出异常如果类型不匹配
    }

    // 获取当前存储的数据类型的名称
    [[nodiscard]] std::string getDataTypeName() const {
        // 定义访问者，用于返回类型名称
        struct TypeNameVisitor {
            std::string operator()(int) const { return "int"; }
            std::string operator()(float) const { return "float"; }
            std::string operator()(double) const { return "double"; }
            std::string operator()(bool) const { return "bool"; }
        };

        // 使用 std::visit 访问当前类型并获取名称
        return std::visit(TypeNameVisitor{}, m_data);
    }

    // 打印数据值（对于调试）
    void printData() const {
        std::visit([](auto&& arg) {
            std::cout << arg << std::endl;
        }, m_data);
    }
};

#endif // BLUEPRINT_VARTYPE_H
