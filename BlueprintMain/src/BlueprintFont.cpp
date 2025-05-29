#include "../include/BlueprintFont.h"

using namespace Blueprint;

BlueprintFont::BlueprintFont() {

}

BlueprintFont::~BlueprintFont() {

}

QFont BlueprintFont::GetFont() const noexcept {
    return m_font;
}

void BlueprintFont::SetFont(const QFont &font) noexcept {
    m_font = font;
}

void BlueprintFont::SetSize(const qreal fontSize) noexcept {
    m_font.setPointSize(fontSize);
}

qreal BlueprintFont::GetSize() noexcept {
    return 0;
}
