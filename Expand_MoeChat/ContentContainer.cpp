#include "ContentContainer.h"

void ContentContainer::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (onResize) onResize(event);
}