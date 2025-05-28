#ifndef BLUEPRINT_STYLETYPE_H
#define BLUEPRINT_STYLETYPE_H

#include <map>
#include <string>
#include <QColor>
#include <QBrush>

namespace Paint {
    #define ColorToStr(x) #x
    #define ColorToStyleM(x) {ColorToStr(x), x}

    inline std::map<std::string, Qt::GlobalColor> ColorQtStyle {
            ColorToStyleM(Qt::color0),
            ColorToStyleM(Qt::color1),
            ColorToStyleM(Qt::black),
            ColorToStyleM(Qt::white),
            ColorToStyleM(Qt::darkGray),
            ColorToStyleM(Qt::gray),
            ColorToStyleM(Qt::lightGray),
            ColorToStyleM(Qt::red),
            ColorToStyleM(Qt::green),
            ColorToStyleM(Qt::blue),
            ColorToStyleM(Qt::cyan),
            ColorToStyleM(Qt::magenta),
            ColorToStyleM(Qt::yellow),
            ColorToStyleM(Qt::darkRed),
            ColorToStyleM(Qt::darkGreen),
            ColorToStyleM(Qt::darkBlue),
            ColorToStyleM(Qt::darkCyan),
            ColorToStyleM(Qt::darkMagenta),
            ColorToStyleM(Qt::darkYellow),
            ColorToStyleM(Qt::transparent)
    };

    inline std::map<std::string, Qt::BrushStyle> BrushQtStyle {
            ColorToStyleM(Qt::NoBrush),
            ColorToStyleM(Qt::SolidPattern),
            ColorToStyleM(Qt::Dense1Pattern),
            ColorToStyleM(Qt::Dense2Pattern),
            ColorToStyleM(Qt::Dense3Pattern),
            ColorToStyleM(Qt::Dense4Pattern),
            ColorToStyleM(Qt::Dense5Pattern),
            ColorToStyleM(Qt::Dense6Pattern),
            ColorToStyleM(Qt::Dense7Pattern),
            ColorToStyleM(Qt::HorPattern),
            ColorToStyleM(Qt::VerPattern),
            ColorToStyleM(Qt::CrossPattern),
            ColorToStyleM(Qt::BDiagPattern),
            ColorToStyleM(Qt::FDiagPattern),
            ColorToStyleM(Qt::DiagCrossPattern),
            ColorToStyleM(Qt::LinearGradientPattern),
            ColorToStyleM(Qt::RadialGradientPattern),
            ColorToStyleM(Qt::ConicalGradientPattern),
            ColorToStyleM(Qt::TexturePattern)
    };

    inline std::map<std::string, Qt::AlignmentFlag> AlignmentFlagQtStyle {
            ColorToStyleM(Qt::AlignLeft),
            ColorToStyleM(Qt::AlignLeading),
            ColorToStyleM(Qt::AlignRight),
            ColorToStyleM(Qt::AlignTrailing),
            ColorToStyleM(Qt::AlignHCenter),
            ColorToStyleM(Qt::AlignJustify),
            ColorToStyleM(Qt::AlignAbsolute),
            ColorToStyleM(Qt::AlignHorizontal_Mask),
            ColorToStyleM(Qt::AlignTop),
            ColorToStyleM(Qt::AlignBottom),
            ColorToStyleM(Qt::AlignVCenter),
            ColorToStyleM(Qt::AlignBaseline),
            ColorToStyleM(Qt::AlignVertical_Mask),
            ColorToStyleM(Qt::AlignCenter)
    };
}
#endif //BLUEPRINT_STYLETYPE_H
