#ifndef BLUEPRINT_STYLETYPE_H
#define BLUEPRINT_STYLETYPE_H

#include <map>
#include <string>
#include <QColor>

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
}
#endif //BLUEPRINT_STYLETYPE_H
