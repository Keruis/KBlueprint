#include "../include/BlueprintPort.h"

import BlueprintType;

void BlueprintPort::Initialization() noexcept {
    m_font = new BlueprintFont;
}

void BlueprintPort::Shutdown() noexcept {
    if (m_font) {
        delete m_font;
        m_font = nullptr;
    }
}
