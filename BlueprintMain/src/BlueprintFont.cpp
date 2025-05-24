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