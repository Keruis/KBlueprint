#ifndef BLUEPRINT_AVATARWIDGET_H
#define BLUEPRINT_AVATARWIDGET_H

#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>

class AvatarWidget : public QWidget {
    Q_OBJECT

public:
    AvatarWidget(const QString& imagePath, int size = 40, QWidget* parent = nullptr);

    void setAvatar(const QString& imagePath);

    void setSize(int size);

protected:
    void paintEvent(QPaintEvent*) override ;

private:
    QPixmap m_avatar;
    int m_size;
};


#endif //BLUEPRINT_AVATARWIDGET_H
