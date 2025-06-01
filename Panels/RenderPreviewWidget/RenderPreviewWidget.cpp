#include "RenderPreviewWidget.h"

RenderPreviewWidget::RenderPreviewWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: #1e1e1e;");
}

void RenderPreviewWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::gray);
    painter.setFont(QFont("Consolas", 12));
    painter.drawText(rect(), Qt::AlignCenter, "Render Preview");
}