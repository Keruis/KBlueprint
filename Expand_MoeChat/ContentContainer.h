#ifndef BLUEPRINT_CONTENTCONTAINER_H
#define BLUEPRINT_CONTENTCONTAINER_H

#include <QWidget>

class ContentContainer : public QWidget {
public:
    using QWidget::QWidget;

    std::function<void(QResizeEvent*)> onResize;

protected:
    void resizeEvent(QResizeEvent* event) override;
};


#endif //BLUEPRINT_CONTENTCONTAINER_H
