#ifndef BLUEPRINT_BLUEPRINTFONT_H
#define BLUEPRINT_BLUEPRINTFONT_H

#include <QFont>

namespace Blueprint {
    class BlueprintFont {

    public:
        BlueprintFont();
        ~BlueprintFont();

        void SetFont(const QFont &font) noexcept;
        [[nodiscard]] QFont GetFont() const noexcept;

    private:
        QFont m_font;
    };
}

#endif //BLUEPRINT_BLUEPRINTFONT_H
