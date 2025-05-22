#include "../include/BlueprintFont.h"

QFont BlueprintFont::GetFont() const noexcept {
    return m_font;
}

void BlueprintFont::SetFont(const QFont &font) noexcept {
    m_font = font;
}