#ifndef BLUEPRINT_IMAGEDATATYPE_H
#define BLUEPRINT_IMAGEDATATYPE_H
#include <algorithm>
#include "Attributes.h"
#include "../../../Container/Vec/Vector.h"

#define NAMESPACE_SIP namespace IP {
#define NAMESPACE_EIP }

NAMESPACE_SIP

using uc = unsigned char;
using usi = unsigned short int;

struct ImageSize {
    std::size_t width;
    std::size_t height;
    int channel;
    ImageSize() noexcept = default;
    ImageSize(std::size_t w, std::size_t h, int c) noexcept
            : width(w), height(h), channel(c) {}
};

struct ImageData {
private:
    ImageSize size;
    usi errCode;
    Vector<uc, 32> ud;
    Vector<uc, 32> rd;
    Vector<uc, 32> gd;
    Vector<uc, 32> bd;
    Vector<uc, 32> ad;
    Vector<float, 32> normd;

public:
    #define DEFINE_SETTER(NAME, FIELD)                          \
        template <typename Ty>                                  \
        requires std::assignable_from<decltype(FIELD)&, Ty>     \
        ALWAYS_INLINE void set##NAME##Data(Ty&& data) noexcept {\
            FIELD = std::forward<Ty>(data);                     \
        }
    #define DEFINE_GETTER(NAME, FIELD) \
        decltype(auto) get##NAME##Data() & { return (FIELD); } \
        decltype(auto) get##NAME##Data() const& { return (FIELD); } \
        decltype(auto) get##NAME##Data() && { return std::move(FIELD); }

    DEFINE_SETTER(Norm , normd)
    DEFINE_SETTER(Alpha,    ad)
    DEFINE_SETTER(Blue ,    bd)
    DEFINE_SETTER(Green,    gd)
    DEFINE_SETTER(Red  ,    rd)
    DEFINE_SETTER(U    ,    ud)

    DEFINE_GETTER(Norm , normd)
    DEFINE_GETTER(Alpha,    ad)
    DEFINE_GETTER(Blue ,    bd)
    DEFINE_GETTER(Green,    gd)
    DEFINE_GETTER(Red  ,    rd)
    DEFINE_GETTER(U    ,    ud)

    [[nodiscard]] std::size_t getTotalPixels() const noexcept { return size.width * size.height * size.channel; }\
    [[nodiscard]] std::size_t getSizeWidth() const noexcept { return size.width; }
    [[nodiscard]] std::size_t getSizeHeight() const noexcept { return size.height; }
    [[nodiscard]] std::size_t getSizeChannel() const noexcept { return size.channel; }
    [[nodiscard]] ImageSize getSize() const noexcept { return size; }
    void setSize(ImageSize s) noexcept { size = s; }
    [[nodiscard]] usi getErrorCode() const noexcept { return errCode; }
    void setErrorCode(usi code) noexcept { errCode = code; }
};

NAMESPACE_EIP

#endif //BLUEPRINT_IMAGEDATATYPE_H
