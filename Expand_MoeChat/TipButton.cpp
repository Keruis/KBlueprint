#include "TipButton.h"

bool TipButton::event(QEvent* event) {
    if (event->type() == QEvent::ToolTip) {
        auto* helpEvent = static_cast<QHelpEvent*>(event);
        QToolTip::showText(helpEvent->globalPos(), m_tip, this);
        return true;
    }
    return QPushButton::event(event);
}