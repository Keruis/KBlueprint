#ifndef BLUEPRINT_IP_H
#define BLUEPRINT_IP_H

#include <immintrin.h>

#include <memory>
#include "Attributes.h"
#include "ImageDataType.h"

NAMESPACE_SIP

class IP {
public:
    IP() : m_data(std::make_unique<ImageData>()) {}

    explicit IP(const ImageData& data)
            : m_data(std::make_unique<ImageData>(data)) {}

    explicit IP(ImageData&& data)
            : m_data(std::make_unique<ImageData>(std::move(data))) {}

    ~IP() = default;

    ImageData& data() { return *m_data; }
    [[nodiscard]] const ImageData& data() const { return *m_data; }

    OPTIMIZE_O3 TARGET_AVX2
    IP& ConvertToGray() noexcept ;

private:
    std::unique_ptr<ImageData> m_data;
};

NAMESPACE_EIP

#endif //BLUEPRINT_IP_H
