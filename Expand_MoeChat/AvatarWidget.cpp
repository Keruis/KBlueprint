#include "AvatarWidget.h"

AvatarWidget::AvatarWidget(const QString& imagePath, int size, QWidget* parent)
        : QWidget(parent), m_size(size)
{
    setFixedSize(m_size, m_size);
    setAvatar(imagePath);
}

void AvatarWidget::setAvatar(const QString& imagePath) {
    QPixmap pix(imagePath);
    m_avatar = pix.scaled(m_size, m_size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    update();
}

void AvatarWidget::setSize(int size) {
    m_size = size;
    setFixedSize(m_size, m_size);
    m_avatar = m_avatar.scaled(m_size, m_size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    update();
}

void AvatarWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addEllipse(0, 0, m_size, m_size);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, m_avatar);
}