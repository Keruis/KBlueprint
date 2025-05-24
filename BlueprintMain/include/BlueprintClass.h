#ifndef BLUEPRINT_BLUEPRINTCLASS_H
#define BLUEPRINT_BLUEPRINTCLASS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QMenu>
#include <QWheelEvent>
#include <memory>

#include "BlueprintNode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BlueprintClass; }
QT_END_NAMESPACE

class BlueprintClass : public QGraphicsView {
    Q_OBJECT

public:
    explicit BlueprintClass(QWidget *parent = nullptr) ;
    ~BlueprintClass() override ;

    void Initialization() noexcept ;
    void Shutdown() noexcept ;

private:
    void setupRendering() noexcept ;
    void setupInteraction() noexcept ;
    void setupAppearance() noexcept ;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    std::unique_ptr<Ui::BlueprintClass> m_ui;
    std::unique_ptr<QGraphicsScene> m_scene;
};


#endif //BLUEPRINT_BLUEPRINTCLASS_H
