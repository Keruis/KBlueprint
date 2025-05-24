#include "../include/BlueprintPort.h"

import BlueprintType;

BlueprintPort::BlueprintPort()
    : m_font(std::make_unique<BlueprintFont>())
{

}

BlueprintPort::~BlueprintPort() = default;

void BlueprintPort::Initialization() noexcept {

}

void BlueprintPort::Shutdown() noexcept {

}
