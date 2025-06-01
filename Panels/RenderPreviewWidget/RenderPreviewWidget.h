#ifndef BLUEPRINT_RENDERPREVIEWWIDGET_H
#define BLUEPRINT_RENDERPREVIEWWIDGET_H

#include <QWidget>
#include <QPainter>

class RenderPreviewWidget : public QWidget {
    Q_OBJECT

public:
    explicit RenderPreviewWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override ;
};


#endif //BLUEPRINT_RENDERPREVIEWWIDGET_H
